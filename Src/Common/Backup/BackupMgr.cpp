#include "stdafx.h"
#include "BackupMgr.h"
#include "Log.h"

CBackupMgr g_backupMgr;

CBackupMgr::CBackupMgr()
{
	m_hThread = INVALID_HANDLE_VALUE;
	m_pLastBackupTime = NULL;
	m_bShouldExit = FALSE;
	m_bStarted = FALSE;
	m_csBackupFolder = DEFAULT_BACKUP_FOLDER;
}

CBackupMgr::~CBackupMgr()
{
	if (m_pLastBackupTime != NULL)
	{
		delete m_pLastBackupTime;
		m_pLastBackupTime = NULL;
	}
}

ERRCODE CBackupMgr::Start(LPTSTR lpMySQLInstallDir, 
							LPTSTR lpHost, 
							UINT16 iPort,
							LPTSTR lpUID, 
							LPTSTR lpPWD,
							LPTSTR lpDatabaseName,
							BOOL bAutoBackup,
							int iAutoBackupDate,
							int iAutoBackupDateUnit,
							int iAutoBackupTime)
{
	ERRCODE errRet = err_OK;

	m_csMySQLInstallDir = lpMySQLInstallDir; 
	m_csHost = lpHost;
	m_iPort = iPort;
	m_csUID = lpUID;
	m_csPWD = lpPWD;
	m_csDatabaseName = lpDatabaseName;
	m_bAutoBackup = bAutoBackup;
	m_iAutoBackupDate = iAutoBackupDate;
	m_iAutoBackupDateUnit = iAutoBackupDateUnit;
	m_iAutoBackupTime = iAutoBackupTime;

	//创建Backup Folder
	m_csBackupFolder.Trim();
	if (m_csBackupFolder == _T(""))
	{
		GetCurrentDirectory(MAX_PATH, m_csBackupFolder.GetBuffer(MAX_PATH));
		m_csBackupFolder.Append(_T("\\Backup"));
	}
	else
	{
		int nLen = m_csBackupFolder.GetLength();
		while (nLen && m_csBackupFolder.GetBuffer()[nLen - 1] == '\\')
		{
			m_csBackupFolder.GetBuffer()[nLen - 1] = 0;
			nLen--;
		}
	}
	CreateDirectory(m_csBackupFolder, NULL);
	WIN32_FIND_DATA wfd;
	HANDLE hFile = FindFirstFile(m_csBackupFolder, &wfd);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		GetCurrentDirectory(MAX_PATH, m_csBackupFolder.GetBuffer(MAX_PATH));
		m_csBackupFolder.Append(_T("\\Backup"));
		CreateDirectory(m_csBackupFolder, NULL);
	}
	FindClose(hFile);

	//启动线程
	if (bAutoBackup != FALSE)
	{
		if (m_hThread == INVALID_HANDLE_VALUE)
		{
			CWinThread *pThread = AfxBeginThread(BackupThreadFunc, this);
			if (!pThread)
			{
				return err_DB_Backup;
			}
			
			DuplicateHandle(::GetCurrentProcess(), 
							pThread->m_hThread, 
							::GetCurrentProcess(), 
							&m_hThread, 
							0, 
							FALSE, 
							DUPLICATE_SAME_ACCESS);
			m_bShouldExit = FALSE;
		}
	}
	else
	{

	}

	m_bStarted = TRUE;

	return err_OK;
}

ERRCODE CBackupMgr::Stop()
{
	m_bShouldExit = TRUE;

	if (m_hThread != INVALID_HANDLE_VALUE)
	{
		m_event.SetEvent();
		::WaitForSingleObject(m_hThread, INFINITE);

		::CloseHandle(m_hThread);
		m_hThread = INVALID_HANDLE_VALUE;
	}

	m_bStarted = FALSE;

	return err_OK;
}


//暂时未实现备份队列功能。自动备份由多线程处理，手动备份直接调用备份函数。
ERRCODE CBackupMgr::PushJob()
{
	if (m_bStarted != TRUE)
	{
		return err_InvalidParameter;
	}

	ERRCODE errRet = err_OK;

	errRet = Backup();

	errRet = CleanUp();

	return errRet;

	/*if (m_bAutoBackup == TRUE)
	{

	}
	else
	{
		return Backup();
	}

	return err_OK;*/
}


BOOL CBackupMgr::GetLastBackupTime(SYSTEMTIME &time)
{
	if (m_bStarted != TRUE)
	{
		return err_InvalidParameter;
	}

	if (m_pLastBackupTime == NULL)
	{
		return FALSE;
	}

	time = *m_pLastBackupTime;
	return TRUE;
}


ERRCODE CBackupMgr::Backup()
{
	if (m_bStarted != TRUE)
	{
		return err_InvalidParameter;
	}

	if (m_pLastBackupTime == NULL)
	{
		m_pLastBackupTime = new SYSTEMTIME;
	}
	GetLocalTime(m_pLastBackupTime);

	CString csExportPath;
	csExportPath.Format(_T("%s\\%04d%02d%02d-%02d%02d%02d.sql"), 
		DEFAULT_BACKUP_FOLDER, 
		m_pLastBackupTime->wYear,
		m_pLastBackupTime->wMonth,
		m_pLastBackupTime->wDay,
		m_pLastBackupTime->wHour,
		m_pLastBackupTime->wMinute,
		m_pLastBackupTime->wSecond);

	ERRCODE errRet = m_backupMgr.Backup(m_csMySQLInstallDir.GetBuffer(), 
		m_csHost.GetBuffer(), 
		m_iPort, 
		m_csUID.GetBuffer(), 
		m_csPWD.GetBuffer(), 
		m_csDatabaseName.GetBuffer(), 
		csExportPath.GetBuffer());
	if (errRet != err_OK)
	{
		return err_DB_Backup;
	}

	return err_OK;
}


ERRCODE CBackupMgr::CleanUp()
{
	if (m_bStarted != TRUE)
	{
		return err_InvalidParameter;
	}

	CTime time = CTime::GetCurrentTime();
	int nKeepYear = time.GetYear();
	int nKeepMonth = time.GetMonth() - DEFAULT_BACKUP_KEEP_BY_MONTH;
	if (nKeepMonth <= 0)
	{
		nKeepYear--;
		nKeepMonth += 12;
	}

	BOOL bResult = TRUE;
	WIN32_FIND_DATA findData;
	CString csFilePath;
	csFilePath.Format(_T("%s\\*.sql"), DEFAULT_BACKUP_FOLDER);

	HANDLE hFind = FindFirstFile(csFilePath.GetBuffer(), &findData);
	while ( (hFind != INVALID_HANDLE_VALUE) && (bResult == TRUE))
	{	
		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			if (strlen(findData.cFileName) == 19)
			{
				int  nYear = 0, nMonth = 0, nDay = 0, nHour = 0, nMin = 0, nSec = 0;   
				int iSuccusNum = sscanf_s(findData.cFileName, "%4d%2d%2d-%2d%2d%2d.sql", &nYear, &nMonth, &nDay, &nHour, &nMin, &nSec);   
				if (iSuccusNum == 6)
				{
					if ((nYear < nKeepYear) || 
						(nYear == nKeepYear && nMonth < nKeepMonth))
					{
						CString csDelFilePath;
						csDelFilePath.Format(_T("%s\\%s"), DEFAULT_BACKUP_FOLDER, findData.cFileName);
						DeleteFile(csDelFilePath);
					}
				}
			}
		
		}

		bResult = FindNextFile(hFind, &findData);
	}

	FindClose(hFind);

	return err_OK;
}

ERRCODE CBackupMgr::GetNextPlanTime(SYSTEMTIME &curSysTime, SYSTEMTIME &nextPlanTime)
{
	if (m_bStarted != TRUE)
	{
		return err_InvalidParameter;
	}

	nextPlanTime = curSysTime;

	if (m_iAutoBackupDateUnit == BACKUP_BY_DAY)
	{
		nextPlanTime.wHour = m_iAutoBackupTime;
		nextPlanTime.wMinute = 0;
		nextPlanTime.wSecond = 0;
		nextPlanTime.wMilliseconds = 0;

	}
	else// if (iDateUnit == BACKUP_BY_WEEK)
	{
		nextPlanTime.wHour = m_iAutoBackupTime;
		nextPlanTime.wMinute = 0;
		nextPlanTime.wSecond = 0;
		nextPlanTime.wMilliseconds = 0;
		if (1 - curSysTime.wDayOfWeek >= 0)
		{
			ChangeSysTime(nextPlanTime, 1 - curSysTime.wDayOfWeek, 0, 0, 0);
		}
		else
		{
			ChangeSysTime(nextPlanTime, 8 + 1 - curSysTime.wDayOfWeek, 0, 0, 0);
		}
	}

	if (curSysTime.wHour > nextPlanTime.wHour ||
		(curSysTime.wHour == nextPlanTime.wHour && curSysTime.wMinute >= nextPlanTime.wMinute))
	{
		ChangeSysTime(nextPlanTime, 1, 0, 0, 0);
	}

	return err_OK;
}


UINT BackupThreadFunc(LPVOID param)
{
	if (param == NULL)
	{
		return err_InvalidParameter;
	}
	CBackupMgr *pBackupMgr = (CBackupMgr*)param;
	ERRCODE errRet = err_OK;
	CString csMsg;
	DWORD dwSleepMS = INFINITE;
	SYSTEMTIME curTime, curPlanTime, nextPlanTime;

	GetLocalTime(&curTime);
	pBackupMgr->GetNextPlanTime(curTime, nextPlanTime);

	while(TRUE)
	{
		curPlanTime = nextPlanTime;
		GetLocalTime(&curTime);
		dwSleepMS = CmpTimeBySec(curTime, curPlanTime) * 1000;

		WaitForSingleObject(pBackupMgr->m_event.m_hObject, dwSleepMS);
		pBackupMgr->m_event.ResetEvent();
		
		GetLocalTime(&curTime);
		dwSleepMS = CmpTimeBySec(curTime, nextPlanTime) * 1000;
		pBackupMgr->GetNextPlanTime(curTime, nextPlanTime);
		if (dwSleepMS <= 0 || CmpTimeBySec(curPlanTime, nextPlanTime) > 0)
		{
			//Do job
			errRet = pBackupMgr->Backup();
			if (errRet != err_OK)
			{
				csMsg.Format(_T("backup thread failed with errRet=%d"), errRet);
				g_log.Write(csMsg);
			}

			errRet = pBackupMgr->CleanUp();
			if (errRet != err_OK)
			{
				csMsg.Format(_T("backup thread failed with errRet=%d"), errRet);
				g_log.Write(csMsg);
			}

			pBackupMgr->GetNextPlanTime(curTime, nextPlanTime);
		}

		if (pBackupMgr->m_bShouldExit == TRUE)
		{
			break;
		}
	}
	return err_OK;
}
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "Log.h"

using namespace std;

CLog g_log;
int g_dwMaxLogFileSizeByMB = 2;

CLog::CLog()
{
	m_bInitialized = FALSE;
	m_hFile = INVALID_HANDLE_VALUE;
}

CLog::~CLog()
{
	if (m_hFile != NULL &&
		m_hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}
}

ERRCODE CLog::Init(LPCTSTR pszLogFilePath)
{
	CSingleLock singleLock(&m_CritAccess);
	if (m_bInitialized == TRUE)
	{
		singleLock.Unlock();
		return err_OK;
	}

	m_csFilePath = LPTSTR(pszLogFilePath);		
/*
	while (m_strFilePath.size() != 0 && m_strFilePath.substr(m_strFilePath.size() - 1,1) == _T("\\"))
	{
		m_strFilePath = m_strFilePath.substr(0, m_strFilePath.size() - 1);		
	}*/

	m_hFile = CreateFile(m_csFilePath, 
						 GENERIC_READ | GENERIC_WRITE, 
						 FILE_SHARE_READ | FILE_SHARE_WRITE,
						 NULL, 
						 OPEN_ALWAYS, 
						 0, 
						 0);
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		singleLock.Unlock();
		return err_FILE_Open;
	}

	DWORD dwRet = SetFilePointer(m_hFile, 0, NULL, FILE_END);
	if (dwRet == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
	{
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
		singleLock.Unlock();
		return err_FILE_Open; 
	}

	m_bInitialized = TRUE;
	singleLock.Unlock();
	return err_OK;
}


ERRCODE CLog::BasicWrite(LPCTSTR pszBuf)
{
	CSingleLock singleLock(&m_CritAccess);
	if (m_bInitialized != TRUE)
	{
		singleLock.Unlock();
		return err_InvalidParameter;
	}

	DWORD dwSize = 0;
	LARGE_INTEGER liFileSize;
	BOOL bRet = FALSE;

	if (m_hFile == INVALID_HANDLE_VALUE || pszBuf == NULL || _tcslen(pszBuf) <= 0)
	{
		singleLock.Unlock();
		return err_FILE_Write;
	}

	bRet = WriteFile(m_hFile, pszBuf, sizeof(TCHAR) * _tcslen(pszBuf), &dwSize, NULL);
	if (bRet == FALSE)
	{
		singleLock.Unlock();
		return err_FILE_Write;
	}	

	liFileSize.QuadPart = 0;
	GetFileSizeEx(m_hFile, &liFileSize);
	if (liFileSize.QuadPart / 1024 / 1024 >= g_dwMaxLogFileSizeByMB)
	{
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;

		TCHAR szFilePath[MAX_PATH];
		memset(szFilePath, 0, MAX_PATH * sizeof(TCHAR));
		_stprintf_s(szFilePath, _T("%s_old"), m_csFilePath);
		DeleteFile(szFilePath);
		_trename(m_csFilePath, szFilePath);

		m_hFile = CreateFile(m_csFilePath, 
							 GENERIC_READ | GENERIC_WRITE, 
							 FILE_SHARE_READ | FILE_SHARE_WRITE,
							 NULL, 
							 CREATE_ALWAYS, 
							 0, 
							 0);
		if (m_hFile == INVALID_HANDLE_VALUE)
		{
			singleLock.Unlock();
			return err_FILE_Open;
		}

		if (SetFilePointer(m_hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
		{
			singleLock.Unlock();
			return err_FILE_Open; 
		}
	}

	singleLock.Unlock();
	return err_OK;
}

ERRCODE CLog::Write(LPCTSTR pszMessage, ERRCODE errCode)
{
	if (m_bInitialized != TRUE)
	{
		return err_InvalidParameter;
	}

	DWORD dwSize = 0;
	BOOL bRet = FALSE;
	SYSTEMTIME st;
	GetLocalTime(&st);
	TCHAR szMessage[1024];
	memset(szMessage, 0, 1024 * sizeof(TCHAR));

	if (errCode == err_OK)
	{
		_stprintf_s(szMessage,_T("<%04X|%4d-%02d-%02d,%02d:%02d:%02d>%s\r\n"), GetCurrentThreadId(),st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, pszMessage);
	}
	else
	{
		_stprintf_s(szMessage, _T("<%04X|%4d-%02d-%02d,%02d:%02d:%02d>%s, errCode=0x%X\r\n"), GetCurrentThreadId(),st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, pszMessage, errCode);
	}
	
	return BasicWrite(szMessage);
}

ERRCODE CLog::WriteNoChangeLine(LPCTSTR pszMessage)   
{   
	SYSTEMTIME st;
	GetLocalTime(&st);
	
	TCHAR tszBuf[MAX_PATH];
	memset(tszBuf, 0, sizeof(TCHAR)*MAX_PATH);

	_stprintf_s(tszBuf,_T("<%04X|%4d-%02d-%02d,%02d:%02d:%02d>%s "), GetCurrentThreadId(),st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, pszMessage);

	return BasicWrite(tszBuf); 
} 

ERRCODE CLog::WriteNoChangeLineNoTime(LPCTSTR pszMessage)   
{   
	return BasicWrite(pszMessage);   
}

ERRCODE CLog::ChangeLine()   
{   
	return BasicWrite(_T("\r\n"));//»Ø³µ»»ÐÐ   
} 

bool FileExist(const TCHAR* pszFileName)
{
	bool bExist = false;
	HANDLE hFile;

	if (NULL != pszFileName)
	{
		// Use the preferred Win32 API call and not the older OpenFile.
		hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, 0, 0);

		if (hFile != INVALID_HANDLE_VALUE)
		{
			// If the handle is valid then the file exists.
			CloseHandle(hFile);
			bExist = true;
		}
	}

	return (bExist);
}

bool FileNew(const TCHAR* pszFileName)
{
	bool bRet = false;
	HANDLE hFile;

	if (NULL != pszFileName)
	{
		// Use the preferred Win32 API call and not the older OpenFile.
		hFile = CreateFile(pszFileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, CREATE_ALWAYS, 0, 0);

		if (hFile != INVALID_HANDLE_VALUE)
		{
			// If the handle is valid then the file exists.
			CloseHandle(hFile);
			bRet = true;
		}
	}

	return (bRet);
}
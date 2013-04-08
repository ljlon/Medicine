#include "stdafx.h"
#include "MySQLBackup.h"
#include "Log.h"

CMySQLBackup::CMySQLBackup()
{

}

CMySQLBackup::~CMySQLBackup()
{

}

ERRCODE CMySQLBackup::Backup(LPTSTR lpMySQLInstallDir, 
							LPTSTR lpHost, 
							UINT16 iPort,
							LPTSTR lpUID, 
							LPTSTR lpPWD, 
							LPTSTR lpDatabaseName, 
							LPTSTR lpExportPath)
{
	CString csCMD, csMsg;

	HANDLE hStdOutRd, hStdOutWr, hStdInRd, hStdInWr;
	SECURITY_ATTRIBUTES saAttr; 
	// Set the bInheritHandle flag so pipe handles are inherited. 
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
	saAttr.bInheritHandle = TRUE; 
	saAttr.lpSecurityDescriptor = NULL; 

	// Create a pipe for the child process's STDOUT. 
	if (!CreatePipe(&hStdOutRd, &hStdOutWr, &saAttr, 0)) 
	{
		csMsg.Format(_T("Backup database fail with error %d"), GetLastError());
		g_log.Write(csMsg);
		return err_DB_Backup;
	}
	// Ensure the read handle to the pipe for STDOUT is not inherited.
	if (!SetHandleInformation(hStdOutRd, HANDLE_FLAG_INHERIT, 0))
	{
		csMsg.Format(_T("Backup database fail with error %d"), GetLastError());
		g_log.Write(csMsg);
		return err_DB_Backup;
	}

	// Create a pipe for the child process's STDIN. 
	if (! CreatePipe(&hStdInRd, &hStdInWr, &saAttr, 0)) 
	{
		csMsg.Format(_T("Backup database fail with error %d"), GetLastError());
		g_log.Write(csMsg);
		return err_DB_Backup;
	}
	// Ensure the write handle to the pipe for STDIN is not inherited. 
	if ( ! SetHandleInformation(hStdInWr, HANDLE_FLAG_INHERIT, 0) )
	{
		csMsg.Format(_T("Backup database fail with error %d"), GetLastError());
		g_log.Write(csMsg);
		return err_DB_Backup;
	}

	HANDLE hFile = CreateFile(lpExportPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		csMsg.Format(_T("Backup database fail with error %d"), GetLastError());
		g_log.Write(csMsg);
		return err_DB_Backup;
	}

	csCMD.Format(TEXT("\"%s\\bin\\mysqldump.exe\" --host=%s --port=%d --user=%s --password=%s --max_allowed_packet=%s --default-character-set=%s --routines --database %s > d:\\test"), 
		lpMySQLInstallDir, 
		lpHost, 
		iPort,
		lpUID, 
		lpPWD, 
		MAX_ALLOWED_PACKET,
		DEFAULT_CHARACTER_SET,
		lpDatabaseName);
		//lpExportPath);

	//csCMD.Format(TEXT("\"%s\\bin\\mysqldump.exe\""), lpMySQLInstallDir);

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	//si.dwFlags = STARTF_USESHOWWINDOW; 
	//si.wShowWindow = SW_HIDE; 
	si.hStdError = hStdOutWr;
	si.hStdOutput = hStdOutWr;
	//si.hStdInput = hStdInRd;
	si.dwFlags |= STARTF_USESTDHANDLES;
	

	if (!CreateProcess(NULL, csCMD.GetBuffer(), NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS,NULL, NULL, &si,&pi))
	{
		csMsg.Format(_T("Backup database fail with error %d"), GetLastError());
		g_log.Write(csMsg);
	
		CloseHandle(hFile);
		return err_DB_Backup;
	}
	DWORD dRet = WaitForSingleObject(pi.hProcess, INFINITE);
	if (dRet == WAIT_OBJECT_0)
	{
		DWORD dwExitCode=0;
		GetExitCodeProcess(pi.hProcess, &dwExitCode);
		if (dwExitCode != 0)
		{
			csMsg.Format(_T("Backup database fail with error %d"), dwExitCode);
			g_log.Write(csMsg);

			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			CloseHandle(hFile);
			return err_DB_Backup;
		}
	}
	else
	{
		csMsg.Format(_T("Backup database time out"));
		g_log.Write(csMsg);

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		CloseHandle(hFile);
		return err_DB_Backup;
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	CloseHandle(hStdInWr);
	CloseHandle(hStdOutWr);

	DWORD dwRead, dwWritten; 
	CHAR chBuf[4096]; 
	BOOL bSuccess = FALSE;

	while (TRUE)
	{
		bSuccess = ReadFile(hStdOutRd, chBuf, 4096, &dwRead, NULL);
		if(!bSuccess || dwRead == 0)
		{
			break; 
		}
		bSuccess = WriteFile(hFile, chBuf, dwRead, &dwWritten, NULL);
		if (!bSuccess) 
		{
			break; 
		}
	}

	CloseHandle(hFile);
	
	return err_OK;
}
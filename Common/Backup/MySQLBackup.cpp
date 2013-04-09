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

	SECURITY_ATTRIBUTES saAttr; 
	// Set the bInheritHandle flag so pipe handles are inherited. 
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
	saAttr.bInheritHandle = TRUE; 
	saAttr.lpSecurityDescriptor = NULL; 

	HANDLE hFile = CreateFile(lpExportPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, &saAttr, CREATE_ALWAYS, 0, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		csMsg.Format(_T("Backup database fail with error %d"), GetLastError());
		g_log.Write(csMsg);
		return err_DB_Backup;
	}

	csCMD.Format(TEXT("\"%s\\bin\\mysqldump.exe\" --host=%s --port=%d --user=%s --password=%s --max_allowed_packet=%s --default-character-set=%s --routines --database %s"), 
		lpMySQLInstallDir, 
		lpHost, 
		iPort,
		lpUID, 
		lpPWD, 
		MAX_ALLOWED_PACKET,
		DEFAULT_CHARACTER_SET,
		lpDatabaseName);

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW; 
	si.wShowWindow = SW_HIDE; 
	si.hStdOutput = hFile;
	si.dwFlags |= STARTF_USESTDHANDLES;
	
	if (!CreateProcess(NULL, csCMD.GetBuffer(), NULL,NULL,TRUE,0,NULL, NULL, &si,&pi))
	{
		csMsg.Format(_T("Backup database fail with error %d"), GetLastError());
		g_log.Write(csMsg);
	
		CloseHandle(hFile);
		return err_DB_Backup;
	}
	WaitForSingleObject( pi.hProcess, INFINITE );

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	CloseHandle(hFile);
	
	return err_OK;
}
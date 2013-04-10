#include "stdafx.h"
#include "Backup.h"
#include "Log.h"

CBackup::CBackup()
{
	
}

CBackup::~CBackup()
{
	
}

ERRCODE CBackup::Backup(LPTSTR lpMySQLInstallDir, 
	LPTSTR lpHost, 
	UINT16 iPort,
	LPTSTR lpUID, 
	LPTSTR lpPWD, 
	LPTSTR lpDatabaseName, 
	LPTSTR lpExportPath)
{
	if (lpExportPath == NULL || strlen(lpExportPath) == 0)
	{
		return err_InvalidParameter;
	}

	ERRCODE errRet = m_mySqlBackup.Backup(lpMySQLInstallDir, lpHost, iPort, lpUID, lpPWD, lpDatabaseName, lpExportPath);
	if (errRet != err_OK)
	{
		return err_DB_Backup;
	}

	return err_OK;
}

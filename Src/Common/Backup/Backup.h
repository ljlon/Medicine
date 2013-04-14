#pragma once
#include "ErrorCode.h"
#include "MySQLBackup.h"

class CBackup
{
public:
	CBackup();
	~CBackup();

	ERRCODE Backup(LPTSTR lpMySQLInstallDir, 
		LPTSTR lpHost, 
		UINT16 iPort,
		LPTSTR lpUID, 
		LPTSTR lpPWD, 
		LPTSTR lpDatabaseName, 
		LPTSTR lpExportPath);

protected:

	CMySQLBackup m_mySqlBackup;

private:

};

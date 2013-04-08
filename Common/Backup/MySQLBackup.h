#pragma once
#include "ErrorCode.h"

#define  MAX_ALLOWED_PACKET "1G"
#define  DEFAULT_CHARACTER_SET "utf8"

class CMySQLBackup
{
public:
	CMySQLBackup();
	~CMySQLBackup();

	ERRCODE Backup(LPTSTR lpMySQLInstallDir, 
					LPTSTR lpHost, 
					UINT16 iPort,
					LPTSTR lpUID, 
					LPTSTR lpPWD, 
					LPTSTR lpDatabaseName, 
					LPTSTR lpExportPath);
protected:

private:

};
#pragma once
#include "ErrorCode.h"
#include "Backup.h"

#define  DEFAULT_BACKUP_FOLDER "Backup"
#define  DEFAULT_BACKUP_KEEP_BY_MONTH 1

enum BACKUP_DATE_UNIT{
	BACKUP_BY_DAY,
	BACKUP_BY_WEEK,
};

class CBackupMgr
{
	friend UINT BackupThreadFunc(LPVOID param);

public:
	CBackupMgr();
	~CBackupMgr();

	ERRCODE Start(LPTSTR lpMySQLInstallDir, 
					LPTSTR lpHost, 
					UINT16 iPort,
					LPTSTR lpUID, 
					LPTSTR lpPWD,
					LPTSTR lpDatabaseName,
					BOOL bAutoBackup = FALSE,
					int iAutoBackupDate = 0,
					int iAutoBackupDateUnit = 0,
					int iAutoBackupTime = 0);
	ERRCODE Stop();

	ERRCODE PushJob();

	BOOL GetLastBackupTime(SYSTEMTIME &time);


protected:
	HANDLE m_hThread;
	BOOL   m_bStarted;
	CEvent m_event;
	CBackup m_backupMgr;
	SYSTEMTIME *m_pLastBackupTime;
	BOOL m_bShouldExit;

	CString m_csMySQLInstallDir;
	CString m_csHost;
	UINT16 m_iPort;
	CString m_csUID; 
	CString m_csPWD;
	CString m_csDatabaseName;
	BOOL m_bAutoBackup;
	int m_iAutoBackupDate;
	int m_iAutoBackupDateUnit;
	int m_iAutoBackupTime;

	ERRCODE Backup();
	ERRCODE CleanUp();
	ERRCODE GetNextPlanTime(SYSTEMTIME &curSysTime, SYSTEMTIME &nextPlanTime);

private:

};

UINT BackupThreadFunc(LPVOID param);

extern CBackupMgr g_backupMgr;
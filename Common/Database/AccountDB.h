#pragma once
#include "StdHead.h"
#include "Database.h"

#define  GLOBAL_RANDOM_KEY _T("AB67C9DE");
#define PROCEDURE_ACCOUNTCHECKPWD _T("account_check_pwd")
#define PROCEDURE_ACCOUNTGETRANDOMKEY _T("account_get_randomKey")
#define PROCEDURE_ACCOUNTUPDATEPWD _T("account_update_pwd")

class CAccountDB
{
public:
	CAccountDB();
	~CAccountDB();

	ERRCODE CheckPWD(LPTSTR lpUID, LPTSTR lpPwd);
	ERRCODE UpdatePassword(LPTSTR lpID, LPTSTR lpPwd);
	ERRCODE GetMD5PWD(LPSTR lpPWD, LPSTR lpRandomKey, OUT BYTE *pbyMD5PWD);

protected:
	ERRCODE GetRandomNumFromDB(LPTSTR lpUID, TCHAR **ppRandomKey);
	ERRCODE CheckPWDFromDB(LPTSTR lpUID, LPTSTR pbyMD5PWD);

private:
	CDatabase m_database;
};
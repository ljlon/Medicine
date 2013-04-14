#include "stdafx.h"
#include "UserDB.h"
#include "AccountDB.h"

CUserDB::CUserDB()
{

}

CUserDB::~CUserDB()
{

}

ERRCODE CUserDB::AddUser(LPTSTR lpUID, LPTSTR lpPassword, LPTSTR lpName, DWORD dwRole)
{
	ERRCODE errRet = err_OK;

	//check user id exist or not
	BOOL bExist = FALSE;
	errRet = CheckUserExit(lpUID, bExist);
	if (errRet != err_OK)
	{
		return errRet;
	}

	if (bExist == TRUE)
	{
		return err_User_AlreadyExist;
	}

	//create user random key and user password
	CAccountDB accountDB;
	TCHAR pszRandomKey[MAX_PATH];
	BYTE pbyMD5PWD[MAX_PATH];
	memset(pszRandomKey, 0, MAX_PATH * sizeof(TCHAR));
	memset(pbyMD5PWD, 0, MAX_PATH * sizeof(BYTE));
	CreateRandom(pszRandomKey, 8);

	errRet = accountDB.GetMD5PWD(lpPassword, pszRandomKey, (BYTE*)&pbyMD5PWD);
	if (errRet)
	{
		return err_User_AddFail;
	}

	//execute procedure
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_USER_ADD) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userUID", adVarChar, adParamInput, lpUID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userPassword", adVarChar, adParamInput, pbyMD5PWD) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userName", adVarChar, adParamInput, lpName) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userRandom", adVarChar, adParamInput, pszRandomKey) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userRole", adInteger, adParamInput, &dwRole) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("returnVal", adInteger, adParamOutput) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	if (m_database.ProcedureExecute() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	int iRet = 0;
	if (m_database.ProcedureGetOutParam("returnVal", adInteger, &iRet) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if(iRet == 0)
	{
		return err_User_AddFail;
	}
	return err_OK;
}


ERRCODE CUserDB::UpdateUser(LPTSTR lpID, LPTSTR lpUID, LPTSTR lpName, DWORD dwRole)
{
	ERRCODE errRet = err_OK;

	BOOL bExist = FALSE;
	errRet = CheckUserExit(lpUID, bExist);
	if (errRet != err_OK)
	{
		return errRet;
	}

	if (bExist == FALSE)
	{
		return err_User_NotExist;
	}


	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_USER_UPDATE) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userID", adVarChar, adParamInput, lpID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userUID", adVarChar, adParamInput, lpUID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userName", adVarChar, adParamInput, lpName) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userTelephone", adInteger, adParamInput, &dwRole) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("returnVal", adInteger, adParamOutput) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	if (m_database.ProcedureExecute() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	int iRet = 0;
	if (m_database.ProcedureGetOutParam("returnVal", adInteger, &iRet) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if(iRet == 0)
	{
		return err_User_UpdateFail;
	}
	return err_OK;
}

ERRCODE CUserDB::CheckUserExit(LPTSTR lpUID, BOOL& bExist)
{
	bExist = FALSE;

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_USER_CHECKEXIST) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userUID", adVarChar, adParamInput, lpUID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("exist", adInteger, adParamOutput) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	if (m_database.ProcedureExecute() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	int iRet = 0;
	if (m_database.ProcedureGetOutParam("exist", adInteger, &iRet) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if(iRet == 1)
	{
		bExist = TRUE;
	}
	return err_OK;
}

ERRCODE CUserDB::GetUser(LPTSTR lpUID, User* pUser)
{
	if (pUser == NULL)
	{
		return err_InvalidParameter;
	}

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_USER_SELECT) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userUID", adVarChar, adParamInput, lpUID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	if (m_database.ProcedureExecute() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	MYSQL_RES *pResults = m_database.ProcedureGetResult();
	if (pResults== NULL)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	MYSQL_ROW row;

	if((row = mysql_fetch_row(pResults)))   
	{ 
		int iFieldNum = mysql_num_fields(pResults);
		if (iFieldNum < 5)
		{
			g_log.Write(_T("UserDB Error:Num fields not match!"));

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		pUser->csID = LPSTR(row[0]); 
		pUser->csUID = LPSTR(row[1]); 
		pUser->csName = LPSTR(row[2]);
		pUser->csRole = LPSTR(row[3]);
		pUser->csCreateTime = LPSTR(row[4]);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return err_OK;
}

ERRCODE CUserDB::GetUsers(DWORD dwPageNum, DWORD dwNumPerPage, DWORD &dwTotalPage, DWORD &dwTotalNum, vector<User*> &vctUsers, LPTSTR lpMatchSubString, EnumUserRole userRole)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_USER_GET) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("subName", adVarChar, adParamInput, lpMatchSubString) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userRole", adInteger, adParamInput, &userRole) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("numPerPage", adInteger, adParamInput, &dwNumPerPage) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("pageNum", adInteger, adParamInput, &dwPageNum) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("totalNum", adInteger, adParamOutput) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("totalPage", adInteger, adParamOutput) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	if (m_database.ProcedureExecute() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	MYSQL_RES *pResults = m_database.ProcedureGetResult();
	if (pResults== NULL)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	MYSQL_ROW row;
	
	while((row = mysql_fetch_row(pResults)))   
	{ 
		int iFieldNum = mysql_num_fields(pResults);
		if (iFieldNum < 5)
		{
			g_log.Write(_T("UserDB Error:Num fields not match!"));
			for (unsigned int i = 0; i < vctUsers.size(); i++)
			{
				delete vctUsers[i];
				vctUsers[i] = NULL;
			}
			vctUsers.clear();

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		User *pUser = new User;
		pUser->csID = LPSTR(row[0]); 
		pUser->csUID = LPSTR(row[1]);
		pUser->csName = LPSTR(row[2]);
		pUser->csRole = LPSTR(row[3]);
		pUser->csCreateTime = LPSTR(row[4]);
		vctUsers.push_back(pUser);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	if (m_database.ProcedureGetOutParam("totalNum", adInteger, &dwTotalNum) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctUsers.size(); i++)
		{
			delete vctUsers[i];
			vctUsers[i] = NULL;
		}
		vctUsers.clear();
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureGetOutParam("totalPage", adInteger, &dwTotalPage) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctUsers.size(); i++)
		{
			delete vctUsers[i];
			vctUsers[i] = NULL;
		}
		vctUsers.clear();
		return err_DB_Proc_Execute;
	}

	return err_OK;
}

ERRCODE CUserDB::DeleteUser(LPTSTR lpID)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_USER_DELETE) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userID", adVarChar, adParamInput, lpID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("returnVal", adInteger, adParamOutput) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	if (m_database.ProcedureExecute() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	int iRet = 0;
	if (m_database.ProcedureGetOutParam("returnVal", adInteger, &iRet) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if(iRet == 0)
	{
		return err_User_DeleteFail;
	}
	return err_OK;
}

ERRCODE CUserDB::GetUserRoles(vector<UserRole*> &vctUserRoles)
{
	vctUserRoles.clear();
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_USER_ROLE_GET) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	if (m_database.ProcedureExecute() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	MYSQL_RES *pResults = m_database.ProcedureGetResult();
	if (pResults== NULL)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	MYSQL_ROW row;

	while((row = mysql_fetch_row(pResults)))   
	{ 
		//mysql_num_fields(pResults);

		UserRole *pUserRole = new UserRole;
		pUserRole->csID = LPSTR(row[0]); 
		pUserRole->csName = LPSTR(row[1]); 
		vctUserRoles.push_back(pUserRole);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return err_OK;

	return err_OK;
}
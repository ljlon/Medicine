#include "stdafx.h"
#include "AccountDB.h"
#include "md5.h"
#include "UserDB.h"

CAccountDB::CAccountDB()
{

}

CAccountDB::~CAccountDB()
{

}

ERRCODE CAccountDB::CheckPWD(LPTSTR lpUID, LPTSTR lpPwd)
{
	ERRCODE errRet = err_OK;
	CString csMsg;

	BOOL bExist = FALSE;
	CUserDB userDB;
	errRet = userDB.CheckUserExit(lpUID, bExist);
	if (errRet != err_OK)
	{
		return errRet;
	}

	if (bExist != TRUE)
	{
		return err_Account_InvalidPwd;
	}

	//获取RandomKey
	TCHAR *pRandomKey = NULL;
	errRet = GetRandomNumFromDB(lpUID, &pRandomKey);
	if (errRet != err_OK || pRandomKey == NULL)
	{
		g_log.Write(_T("获取用户信息失败"), errRet);
		return errRet;
	}

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	//将密码字符串进行MD5加密
	BYTE pbyMD5PWD[MAX_PATH];
	memset(pbyMD5PWD, 0, MAX_PATH * sizeof(BYTE));
	errRet = GetMD5PWD(lpPwd, pRandomKey, (BYTE*)&pbyMD5PWD);
	if (errRet)
	{
		csMsg.Format(_T("密码无效,错误：%d"), errRet);
		g_log.Write(csMsg);
		return err_Account_InvalidPwd;
	}

	//释放RandomKey内存
	if (pRandomKey != NULL)
	{
		delete pRandomKey;
		pRandomKey = NULL;
	}

	//查询密码是否正确
	errRet = CheckPWDFromDB(lpUID, (LPSTR)pbyMD5PWD);
	if (errRet != err_OK)
	{
		return errRet;
	}

	return err_OK;
}

ERRCODE CAccountDB::GetMD5PWD(LPSTR lpPWD, LPSTR lpRandomKey, OUT BYTE *pbyMD5PWD)
{
	if (lpPWD == NULL || lpRandomKey == NULL || pbyMD5PWD == NULL)
	{
		return err_InvalidParameter;
	}
	CString csMsg;
	CString csCombinPWD = lpPWD;
	csCombinPWD += GLOBAL_RANDOM_KEY;
	csCombinPWD += lpRandomKey;

	//将组合字符串MD5加密
	DWORD dwRet = MD5String(csCombinPWD.GetBuffer(), (uchar*)pbyMD5PWD);
	if (dwRet)
	{
		csMsg.Format(_T("密码无效,错误：%d"), dwRet);
		g_log.Write(csMsg);
		return err_Account_InvalidPwd;
	}

	char szChar[MAX_PATH];
	memset(szChar, 0, MAX_PATH);
	ChangeByteToChar(pbyMD5PWD, strlen((char*)pbyMD5PWD), szChar, MAX_PATH);

	memset(pbyMD5PWD, 0, strlen((char*)pbyMD5PWD));
	memcpy(pbyMD5PWD, (BYTE*)szChar, strlen(szChar));

	return err_OK;
}

ERRCODE CAccountDB::GetRandomNumFromDB(LPTSTR lpUID, TCHAR **ppRandomKey)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_ACCOUNTGETRANDOMKEY) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userid", adVarChar, adParamInput, lpUID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("randomKey", adVarChar, adParamOutput) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	if (m_database.ProcedureExecute() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	TCHAR *pRandomKey = NULL;
	if (m_database.ProcedureGetOutParam("randomKey", adVarChar, &pRandomKey) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if(pRandomKey == NULL)
	{
		return err_Account_InvalidRandomKey;
	}

	*ppRandomKey = pRandomKey;

	return err_OK;
}

ERRCODE CAccountDB::CheckPWDFromDB(LPTSTR lpUID, LPTSTR pbyMD5PWD)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_ACCOUNTCHECKPWD) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userid", adVarChar, adParamInput, lpUID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("password", adVarChar, adParamInput, pbyMD5PWD) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("invalid", adInteger, adParamOutput) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	if (m_database.ProcedureExecute() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	int iInvalid = FALSE;
	if (m_database.ProcedureGetOutParam("invalid", adInteger, &iInvalid) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if(iInvalid == 0)
	{
		return err_Account_InvalidPwd;
	}
	return err_OK;
}


ERRCODE CAccountDB::UpdatePassword(LPTSTR lpUID, LPTSTR lpPwd)
{
	ERRCODE errRet = err_OK;
	CString csMsg;

	//获取RandomKey
	TCHAR *pRandomKey = NULL;
	errRet = GetRandomNumFromDB(lpUID, &pRandomKey);
	if (errRet != err_OK || pRandomKey == NULL)
	{
		g_log.Write(_T("获取用户信息失败"), errRet);
		return err_Account_InvalidPwd;
	}

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	//将密码字符串进行MD5加密
	BYTE pbyMD5PWD[MAX_PATH];
	memset(pbyMD5PWD, 0, MAX_PATH * sizeof(BYTE));
	errRet = GetMD5PWD(lpPwd, pRandomKey, (BYTE*)&pbyMD5PWD);
	if (errRet)
	{
		csMsg.Format(_T("密码无效,错误：%d"), errRet);
		g_log.Write(csMsg);
		return err_Account_InvalidPwd;
	}

	//释放RandomKey内存
	if (pRandomKey != NULL)
	{
		delete pRandomKey;
		pRandomKey = NULL;
	}

	//更新密码
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_ACCOUNTUPDATEPWD) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("accountID", adVarChar, adParamInput, lpUID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("accountPWD", adVarChar, adParamInput, pbyMD5PWD) != TRUE)
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

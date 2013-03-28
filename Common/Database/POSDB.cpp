#include "stdafx.h"
#include "POSDB.h"

CPOSDB::CPOSDB()
{

}

CPOSDB::~CPOSDB()
{

}


ERRCODE CPOSDB::AddPOS(POS *pPOS)
{
	if (pPOS == NULL)
	{
		return err_InvalidParameter;
	}

	ERRCODE errRet = err_OK;

	//check pos be exist or not
	if (pPOS->csPCMAC == _T(""))
	{
		return err_POS_AddFail;
	}

	BOOL bExist = TRUE;
	errRet = CheckPOSExist(pPOS->csPCMAC.GetBuffer(), bExist);
	if (errRet != err_OK)
	{
		return errRet;
	}

	if (bExist == TRUE)
	{
		return err_POS_AlreadyExist;
	}

	//connect database
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	//procedure
	if (m_database.ProcedureInit(PROCEDURE_POS_ADD) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("MAC", adVarChar, adParamInput, pPOS->csPCMAC.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("posID", adInteger, adParamOutput) != TRUE)
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

	LONG lPOSID = 0;
	if (m_database.ProcedureGetOutParam("posID", adInteger, &lPOSID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	LONG lRet = 0;
	if (m_database.ProcedureGetOutParam("returnVal", adInteger, &lRet) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if(lRet == 0)
	{
		return err_POS_AddFail;
	}
	return err_OK;
}


ERRCODE CPOSDB::GetPOSs(DWORD dwPageNum, 
											DWORD dwNumPerPage, 
											DWORD &dwTotalPage, 
											DWORD &dwTotalNum, 
											vector<POS*> &vctPOS)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_POS_GET) != TRUE)
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
	int iItem = 0;;
	while((row = mysql_fetch_row(pResults)))   
	{ 
		int iFieldNum = mysql_num_fields(pResults);
		if (iFieldNum < 3)
		{
			g_log.Write(_T("POSDB Error:Num fields not match!"));
			for (unsigned int i = 0; i < vctPOS.size(); i++)
			{
				delete vctPOS[i];
				vctPOS[i] = NULL;
			}
			vctPOS.clear();

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		iItem = 0;
		POS *pPOS = new POS;
		pPOS->csID = LPSTR(row[iItem++]); 
		pPOS->csPCID = LPSTR(row[iItem++]); 
		pPOS->csPCMAC = LPSTR(row[iItem++]); 
		vctPOS.push_back(pPOS);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	if (m_database.ProcedureGetOutParam("totalNum", adInteger, &dwTotalNum) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctPOS.size(); i++)
		{
			delete vctPOS[i];
			vctPOS[i] = NULL;
		}
		vctPOS.clear();
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureGetOutParam("totalPage", adInteger, &dwTotalPage) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctPOS.size(); i++)
		{
			delete vctPOS[i];
			vctPOS[i] = NULL;
		}
		vctPOS.clear();
		return err_DB_Proc_Execute;
	}

	return err_OK;
}

ERRCODE CPOSDB::GetPOS(LPTSTR lpMAC, POS* pPOS)
{
	if (pPOS == NULL)
	{
		return err_InvalidParameter;
	}
	ERRCODE errRet = err_OK;
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_POS_SELECT) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("MAC", adVarChar, adParamInput, lpMAC) != TRUE)
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
	int iItem = 0;
	if((row = mysql_fetch_row(pResults)))   
	{ 
		int iFieldNum = mysql_num_fields(pResults);
		if (iFieldNum < 3)
		{
			g_log.Write(_T("POSDB Error:Num fields not match!"));
			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		iItem = 0;
		pPOS->csID = LPSTR(row[iItem++]); 
		pPOS->csPCID = LPSTR(row[iItem++]); 
		pPOS->csPCMAC = LPSTR(row[iItem++]); 
	} 
	else
	{
		errRet = err_POS_NotExist;
	}
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return errRet;
}

ERRCODE CPOSDB::CheckPOSExist(LPTSTR lpMAC, BOOL& bExist)
{
	bExist = TRUE;

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_POS_CHECKEXIST_BYMAC) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("MAC", adVarChar, adParamInput, lpMAC) != TRUE)
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
	if(iRet == 0)
	{
		bExist = FALSE;
	}
	return err_OK;
}

ERRCODE CPOSDB::CheckPOSExist(LONG lID, BOOL& bExist)
{
	bExist = TRUE;

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_POS_CHECKEXIST) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("posID", adInteger, adParamInput, &lID) != TRUE)
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
	if(iRet == 0)
	{
		bExist = FALSE;
	}
	return err_OK;
}

ERRCODE CPOSDB::UpdatePOS(LONG lOldID, POS *pPOS)
{
	if (pPOS == NULL)
	{
		return err_InvalidParameter;
	}

	ERRCODE errRet = err_OK;

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_POS_UPDATE) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("oldID", adInteger, adParamInput, &lOldID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	LONG lPosID = atol(pPOS->csID);
	if (m_database.ProcedureAddParam("posID", adInteger, adParamInput, &lPosID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	LONG lPCID = atol(pPOS->csPCID);
	if (m_database.ProcedureAddParam("pcID", adInteger, adParamInput, &lPCID) != TRUE)
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
		return err_POS_UpdateFail;
	}
	return err_OK;
}
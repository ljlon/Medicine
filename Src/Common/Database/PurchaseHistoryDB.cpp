#include "stdafx.h"
#include "PurchaseHistoryDB.h"

TCHAR *g_tszPurchaseOperationIDName[] ={
	_T("Ìí¼Ó"),
	_T("ÐÞ¸Ä"),
	_T("É¾³ý")
};

CString GetPurchaseOperationIDName(PurchaseOperationID operationID)
{
	if (operationID < 0 || operationID >= PurOpr_End)
	{
		return _T("");
	}

	return g_tszPurchaseOperationIDName[operationID];
}

CPurchaseHistoryDB::CPurchaseHistoryDB()
{

}

CPurchaseHistoryDB::~CPurchaseHistoryDB()
{

}

ERRCODE CPurchaseHistoryDB::AddPurchaseHistory(LONG lUserID, LONG lMedicineID, PurchaseOperationID dwOperationID, LPTSTR lpOperationDetail)
{
	ERRCODE errRet = err_OK;

	//connect database
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	//procedure
	if (m_database.ProcedureInit(PROCEDURE_PURCHASE_HISTORY_ADD) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userID", adInteger, adParamInput, &lUserID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adInteger, adParamInput, &lMedicineID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("operationID", adInteger, adParamInput, &dwOperationID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("operationDetail", adVarChar, adParamInput, lpOperationDetail) != TRUE)
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
		return err_PurchaseHistory_AddFail;
	}
	return err_OK;
}


ERRCODE CPurchaseHistoryDB::GetPurchaseHistories(DWORD dwPageNum, DWORD dwNumPerPage, DWORD &dwTotalPage, DWORD &dwTotalNum, vector<PurchaseHistory*> &vctPurchaseHistories)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_PURCHASE_HISTORY_GET) != TRUE)
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
		if (iFieldNum < 10)
		{
			g_log.Write(_T("PurchaseDB Error:Num fields not match!"));
			for (unsigned int i = 0; i < vctPurchaseHistories.size(); i++)
			{
				delete vctPurchaseHistories[i];
				vctPurchaseHistories[i] = NULL;
			}
			vctPurchaseHistories.clear();

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		PurchaseHistory *pPurchaseHistory = new PurchaseHistory;
		int iItem = 0;
		pPurchaseHistory->csID = LPSTR(row[iItem++]); 
		pPurchaseHistory->csUserID = LPSTR(row[iItem++]);
		pPurchaseHistory->csUserUID = LPSTR(row[iItem++]);
		pPurchaseHistory->csUserName = LPSTR(row[iItem++]);
		pPurchaseHistory->csMedicineID = LPSTR(row[iItem++]);
		pPurchaseHistory->csMedicineSN = LPSTR(row[iItem++]);
		pPurchaseHistory->csMedicineName = LPSTR(row[iItem++]);
		pPurchaseHistory->csOperationID = LPSTR(row[iItem++]);
		pPurchaseHistory->csOperationDetail = LPSTR(row[iItem++]);
		pPurchaseHistory->csCreateTime = LPSTR(row[iItem++]);
		vctPurchaseHistories.push_back(pPurchaseHistory);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	if (m_database.ProcedureGetOutParam("totalNum", adInteger, &dwTotalNum) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureGetOutParam("totalPage", adInteger, &dwTotalPage) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	return err_OK;
}

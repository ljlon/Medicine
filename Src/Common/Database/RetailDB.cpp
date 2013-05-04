#include "stdafx.h"
#include "RetailDB.h"

CRetailDB::CRetailDB()
{

}

CRetailDB::~CRetailDB()
{

}

ERRCODE CRetailDB::GetRetails(DWORD dwPageNum, 
												DWORD dwNumPerPage, 
												DWORD &dwTotalPage, 
												DWORD &dwTotalNum, 
												double &dbTotalPrice, 
												vector<Retail*> &vctRetail,
												LPTSTR lpPosID,
												LPTSTR lpUserID,
												LPTSTR lpRetailDateBegin,
												LPTSTR lpRetailDateEnd)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_RETAIL_GET) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("posID", adVarChar, adParamInput, lpPosID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userID", adVarChar, adParamInput, lpUserID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("retailDateBegin", adVarChar, adParamInput,  lpRetailDateBegin) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("retailDateEnd", adVarChar, adParamInput,  lpRetailDateEnd) != TRUE)
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
	if (m_database.ProcedureAddParam("totalPrice", adDouble, adParamOutput) != TRUE)
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
		if (iFieldNum < 12)
		{
			g_log.Write(_T("StoreDB Error:Num fields not match!"));
			for (unsigned int i = 0; i < vctRetail.size(); i++)
			{
				delete vctRetail[i];
				vctRetail[i] = NULL;
			}
			vctRetail.clear();

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		Retail *pRetail = new Retail;
		int iItem = 0;
		pRetail->csID = LPSTR(row[iItem++]); 
		pRetail->csSN = LPSTR(row[iItem++]);
		pRetail->csUserID = LPSTR(row[iItem++]);
		pRetail->csUserUID = LPSTR(row[iItem++]); 
		pRetail->csUserName= LPSTR(row[iItem++]); 
		pRetail->csCreateTime = LPSTR(row[iItem++]); 
		pRetail->csTotalPrcie = LPSTR(row[iItem++]); 
		pRetail->csInPrice = LPSTR(row[iItem++]);
		pRetail->csOutPrice = LPSTR(row[iItem++]);
		pRetail->csPOSID = LPSTR(row[iItem++]);
		pRetail->csPCID = LPSTR(row[iItem++]);
		pRetail->csPCMAC = LPSTR(row[iItem++]);

		vctRetail.push_back(pRetail);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	if (m_database.ProcedureGetOutParam("totalNum", adInteger, &dwTotalNum) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctRetail.size(); i++)
		{
			delete vctRetail[i];
			vctRetail[i] = NULL;
		}
		vctRetail.clear();
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureGetOutParam("totalPage", adInteger, &dwTotalPage) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctRetail.size(); i++)
		{
			delete vctRetail[i];
			vctRetail[i] = NULL;
		}
		vctRetail.clear();
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureGetOutParam("totalPrice", adDouble, &dbTotalPrice) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctRetail.size(); i++)
		{
			delete vctRetail[i];
			vctRetail[i] = NULL;
		}
		vctRetail.clear();
		return err_DB_Proc_Execute;
	}

	return err_OK;
}

ERRCODE CRetailDB::GetRetail(LPTSTR lpID, Retail* pRetail)
{
	if (pRetail == NULL)
	{
		return err_InvalidParameter;
	}

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_RETAIL_SELECT) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("retailID", adVarChar, adParamInput, lpID) != TRUE)
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
		if (iFieldNum < 12)
		{
			g_log.Write(_T("RetailDB Error:Num fields not match!"));

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		int iItem = 0;
		pRetail->csID = LPSTR(row[iItem++]); 
		pRetail->csSN = LPSTR(row[iItem++]);
		pRetail->csUserID = LPSTR(row[iItem++]); 
		pRetail->csUserUID = LPSTR(row[iItem++]); 
		pRetail->csUserName= LPSTR(row[iItem++]); 
		pRetail->csCreateTime = LPSTR(row[iItem++]); 
		pRetail->csTotalPrcie = LPSTR(row[iItem++]); 
		pRetail->csInPrice = LPSTR(row[iItem++]);
		pRetail->csOutPrice = LPSTR(row[iItem++]);
		pRetail->csPOSID = LPSTR(row[iItem++]);
		pRetail->csPCID = LPSTR(row[iItem++]);
		pRetail->csPCMAC = LPSTR(row[iItem++]);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return err_OK;
}

ERRCODE CRetailDB::AddRetail(Retail *pRetail)
{
	ERRCODE errRet = err_OK;

	if (pRetail == NULL)
	{
		return err_InvalidParameter;
	}

	//connect database
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	//procedure
	if (m_database.ProcedureInit(PROCEDURE_RETAIL_ADD) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("pcID", adVarChar, adParamInput, pRetail->csPCID.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("retailSN", adVarChar, adParamInput, pRetail->csSN.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userID", adVarChar, adParamInput, pRetail->csUserID.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("totalPrice", adVarChar, adParamInput, pRetail->csTotalPrcie.GetBuffer())!= TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("inPrice", adVarChar, adParamInput, pRetail->csInPrice.GetBuffer())!= TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("outPrice", adVarChar, adParamInput, pRetail->csOutPrice.GetBuffer())!= TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	if (m_database.ProcedureAddParam("retailID", adInteger, adParamOutput) != TRUE)
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

	LPTSTR lpRetailID = NULL;
	if (m_database.ProcedureGetOutParam("retailID", adVarChar, &lpRetailID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	pRetail->csID.Format(_T("%s"), lpRetailID);
	delete lpRetailID;
	lpRetailID = NULL;

	int iRet = 0;
	if (m_database.ProcedureGetOutParam("returnVal", adInteger, &iRet) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if(iRet == 0)
	{
		return err_Purchase_AddFail;
	}
	return err_OK;
}

ERRCODE CRetailDB::AddRetailItem(RetailItem *pRetailItem)
{
	ERRCODE errRet = err_OK;

	if (pRetailItem == NULL)
	{
		return err_InvalidParameter;
	}

	//connect database
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	//procedure
	if (m_database.ProcedureInit(PROCEDURE_RETAIL_ITEM_ADD) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("retailID", adVarChar, adParamInput, pRetailItem->csRetailID.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adVarChar, adParamInput, pRetailItem->csMedicineID.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicinePrice", adVarChar, adParamInput, pRetailItem->csMedicinePrice.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineNum", adVarChar, adParamInput, pRetailItem->csMedicineNumber.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("retailPrice", adVarChar, adParamInput, pRetailItem->csRetailPrice.GetBuffer()) != TRUE)
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
		return err_Purchase_AddFail;
	}
	return err_OK;
}

ERRCODE CRetailDB::GetRetailItems(LPTSTR lpRetailID, vector<RetailItem*> &vctRetailItem)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_RETAIL_ITEM_GET) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("retailID", adVarChar, adParamInput, lpRetailID) != TRUE)
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
		if (iFieldNum < 9)
		{
			g_log.Write(_T("StoreDB Error:Num fields not match!"));
			for (unsigned int i = 0; i < vctRetailItem.size(); i++)
			{
				delete vctRetailItem[i];
				vctRetailItem[i] = NULL;
			}
			vctRetailItem.clear();

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		RetailItem *pRetailItem = new RetailItem;

		int iItem = 0;
		pRetailItem->csID = LPSTR(row[iItem++]); 
		pRetailItem->csRetailID = LPSTR(row[iItem++]); 
		pRetailItem->csMedicineID = LPSTR(row[iItem++]); 
		pRetailItem->csMedicineSN = LPSTR(row[iItem++]); 
		pRetailItem->csMedicineName = LPSTR(row[iItem++]); 
		pRetailItem->csMedicineSpec = LPSTR(row[iItem++]); 
		pRetailItem->csMedicineUnitName = LPSTR(row[iItem++]); 
		pRetailItem->csMedicinePrice = LPSTR(row[iItem++]);
		pRetailItem->csMedicineNumber = LPSTR(row[iItem++]); 
		pRetailItem->csRetailPrice = LPSTR(row[iItem++]);
		
		vctRetailItem.push_back(pRetailItem);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return err_OK;
}
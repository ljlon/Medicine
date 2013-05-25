#include "stdafx.h"
#include "PurchaseDB.h"

CPurchaseDB::CPurchaseDB()
{

}

CPurchaseDB::~CPurchaseDB()
{

}

ERRCODE CPurchaseDB::AddPurchase(Purchase *pPurchase)
{
	if (pPurchase == NULL)
	{
		return err_InvalidParameter;
	}

	ERRCODE errRet = err_OK;

	//connect database
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	//procedure
	if (m_database.ProcedureInit(PROCEDURE_PURCHASE_ADD) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("userID", adVarChar, adParamInput,pPurchase->csUserID.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("supplierID", adVarChar, adParamInput, pPurchase->csSupplierID.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("purchaseDate", adVarChar, adParamInput, pPurchase->csPurchaseTime.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adVarChar, adParamInput, pPurchase->csMedicineID.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("number", adVarChar, adParamInput, pPurchase->csNumber.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("purPrice", adVarChar, adParamInput, pPurchase->csPurPrice.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("batchNum", adVarChar, adParamInput, pPurchase->csBatchNum.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("productDate", adVarChar, adParamInput, pPurchase->csProductDate.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("expireDate", adVarChar, adParamInput, pPurchase->csExpireDate.GetBuffer()) != TRUE)
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

ERRCODE CPurchaseDB::GetPurchase(LPTSTR lpID, Purchase* pPurchase)
{
	if (pPurchase == NULL)
	{
		return err_InvalidParameter;
	}
	ERRCODE errRet = err_OK;
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_PURCHASE_SELECT) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("purchaseID", adVarChar, adParamInput, lpID) != TRUE)
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
		if (iFieldNum < 19)
		{
			g_log.Write(_T("PurchaseDB Error:Num fields not match!"));

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		int iItem = 0;
		pPurchase->csID = LPSTR(row[iItem++]); 
		pPurchase->csUserID = LPSTR(row[iItem++]);
		pPurchase->csUserUID = LPSTR(row[iItem++]);
		pPurchase->csUserName = LPSTR(row[iItem++]);
		pPurchase->csMedicineID = LPSTR(row[iItem++]);
		pPurchase->csMedicineSN = LPSTR(row[iItem++]);
		pPurchase->csMedicineName = LPSTR(row[iItem++]);
		pPurchase->csMedicineSpec = LPSTR(row[iItem++]);
		pPurchase->csMedicineVendorName = LPSTR(row[iItem++]);
		pPurchase->csNumber = LPSTR(row[iItem++]);
		pPurchase->csMedicineUnit = LPSTR(row[iItem++]);
		pPurchase->csPurPrice = LPSTR(row[iItem++]);
		pPurchase->csCreateTime = LPSTR(row[iItem++]);
		pPurchase->csPurchaseTime = LPSTR(row[iItem++]);
		pPurchase->csBatchNum = LPSTR(row[iItem++]);
		pPurchase->csProductDate = LPSTR(row[iItem++]);
		pPurchase->csExpireDate = LPSTR(row[iItem++]);
		pPurchase->csSupplierID = LPSTR(row[iItem++]);
		pPurchase->csSupplierName = LPSTR(row[iItem++]);
	} 
	else
	{
		errRet = err_Medicine_NotExist;
	}
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return errRet;
}

ERRCODE CPurchaseDB::GetPurchases(DWORD dwPageNum, 
								DWORD dwNumPerPage, 
								DWORD &dwTotalPage, 
								DWORD &dwTotalNum, 
								double &dbTotalPrice, 
								vector<Purchase*> &vctPurchases,
								LPTSTR lpPurDateBegin,
								LPTSTR lpPurDateEnd,
								LPTSTR lpMedicineSN,
								LPTSTR lpMedicineName,
								LPTSTR lpMedicineBatchNum,
								LPTSTR lpSupplierID)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_PURCHASE_GET) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("purDateBegin", adVarChar, adParamInput,  lpPurDateBegin) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("purDateEnd", adVarChar, adParamInput,  lpPurDateEnd) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineSN", adVarChar, adParamInput,  lpMedicineSN) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineName", adVarChar, adParamInput,  lpMedicineName) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineBatchNum", adVarChar, adParamInput,  lpMedicineBatchNum) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("supplierID", adVarChar, adParamInput,  lpSupplierID) != TRUE)
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
		if (iFieldNum < 19)
		{
			g_log.Write(_T("PurchaseDB Error:Num fields not match!"));
			for (unsigned int i = 0; i < vctPurchases.size(); i++)
			{
				delete vctPurchases[i];
				vctPurchases[i] = NULL;
			}
			vctPurchases.clear();

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		Purchase *pPurchase = new Purchase;
		int iItem = 0;
		pPurchase->csID = LPSTR(row[iItem++]); 
		pPurchase->csUserID = LPSTR(row[iItem++]);
		pPurchase->csUserUID = LPSTR(row[iItem++]);
		pPurchase->csUserName = LPSTR(row[iItem++]);
		pPurchase->csMedicineID = LPSTR(row[iItem++]);
		pPurchase->csMedicineSN = LPSTR(row[iItem++]);
		pPurchase->csMedicineName = LPSTR(row[iItem++]);
		pPurchase->csMedicineSpec = LPSTR(row[iItem++]);
		pPurchase->csMedicineVendorName = LPSTR(row[iItem++]);
		pPurchase->csNumber = LPSTR(row[iItem++]);
		pPurchase->csMedicineUnit = LPSTR(row[iItem++]);
		pPurchase->csPurPrice = LPSTR(row[iItem++]);
		pPurchase->csCreateTime = LPSTR(row[iItem++]);
		pPurchase->csPurchaseTime = LPSTR(row[iItem++]);
		pPurchase->csBatchNum = LPSTR(row[iItem++]);
		pPurchase->csProductDate = LPSTR(row[iItem++]);
		pPurchase->csExpireDate = LPSTR(row[iItem++]);
		pPurchase->csSupplierID = LPSTR(row[iItem++]);
		pPurchase->csSupplierName = LPSTR(row[iItem++]);
		vctPurchases.push_back(pPurchase);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	if (m_database.ProcedureGetOutParam("totalNum", adInteger, &dwTotalNum) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctPurchases.size(); i++)
		{
			delete vctPurchases[i];
			vctPurchases[i] = NULL;
		}
		vctPurchases.clear();
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureGetOutParam("totalPage", adInteger, &dwTotalPage) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctPurchases.size(); i++)
		{
			delete vctPurchases[i];
			vctPurchases[i] = NULL;
		}
		vctPurchases.clear();
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureGetOutParam("totalPrice", adDouble, &dbTotalPrice) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctPurchases.size(); i++)
		{
			delete vctPurchases[i];
			vctPurchases[i] = NULL;
		}
		vctPurchases.clear();
		return err_DB_Proc_Execute;
	}

	return err_OK;
}

ERRCODE CPurchaseDB::DeletePurchase(LPTSTR lpID)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_PURCHASE_DELETE) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("purchaseID", adVarChar, adParamInput, lpID) != TRUE)
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
		return err_Purchase_DeleteFail;
	}
	return err_OK;
}
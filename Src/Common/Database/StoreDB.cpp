#include "stdafx.h"
#include "StoreDB.h"

CStoreDB::CStoreDB()
{

}

CStoreDB::~CStoreDB()
{

}

ERRCODE CStoreDB::GetMedicineStores(DWORD dwPageNum, 
									DWORD dwNumPerPage, 
									DWORD &dwTotalPage, 
									DWORD &dwTotalNum, 
									vector<MedicineStore*> &vctMedicineStore,
									LPTSTR lpMedicineSN,
									LPTSTR lpMedicineName,
									LPTSTR lpExpireDate,
									LPTSTR lpMedicineVendorID)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_STORE_GET) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	CString csMedicineName = _T("");
	if (lpMedicineName&&strlen(lpMedicineName))
	{
		csMedicineName.Format(_T("%%%s%%"), lpMedicineName);
	}

	if (m_database.ProcedureAddParam("medicineSN", adVarChar, adParamInput, lpMedicineSN) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineName", adVarChar, adParamInput, csMedicineName.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("expireDate", adVarChar, adParamInput, lpExpireDate) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineVendorID", adVarChar, adParamInput, lpMedicineVendorID) != TRUE)
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
		if (iFieldNum < 15)
		{
			g_log.Write(_T("StoreDB Error:Num fields not match!"));
			for (unsigned int i = 0; i < vctMedicineStore.size(); i++)
			{
				delete vctMedicineStore[i];
				vctMedicineStore[i] = NULL;
			}
			vctMedicineStore.clear();

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		int iItem = 0;
		MedicineStore *pMedicineStore = new MedicineStore;
		pMedicineStore->csID = LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineID = LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineSN = LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineName= LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineSpec= LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineVendorID= LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineVendorName= LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineRetailPrice= LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineUnitID = LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineUnitName = LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineNum = LPSTR(row[iItem++]);
		pMedicineStore->csMedicineProductDate = LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineExpireDate = LPSTR(row[iItem++]); 
		pMedicineStore->csCreateTime = LPSTR(row[iItem++]); 
		pMedicineStore->csModifyTime = LPSTR(row[iItem++]); 
		vctMedicineStore.push_back(pMedicineStore);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	if (m_database.ProcedureGetOutParam("totalNum", adInteger, &dwTotalNum) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctMedicineStore.size(); i++)
		{
			delete vctMedicineStore[i];
			vctMedicineStore[i] = NULL;
		}
		vctMedicineStore.clear();
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureGetOutParam("totalPage", adInteger, &dwTotalPage) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctMedicineStore.size(); i++)
		{
			delete vctMedicineStore[i];
			vctMedicineStore[i] = NULL;
		}
		vctMedicineStore.clear();
		return err_DB_Proc_Execute;
	}

	return err_OK;
}

ERRCODE CStoreDB::GetMedicineStore(LPTSTR lpMedicineSN, MedicineStore* pMedicineStore)
{
	if (pMedicineStore == NULL)
	{
		return err_InvalidParameter;
	}
	ERRCODE errRet = err_OK;
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_STORE_SELECT) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineSN", adVarChar, adParamInput, lpMedicineSN) != TRUE)
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
		if (iFieldNum < 15)
		{
			g_log.Write(_T("StoreDB Error:Num fields not match!"));

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		int iItem = 0;
		pMedicineStore->csID = LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineID = LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineSN = LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineName= LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineSpec= LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineVendorID= LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineVendorName= LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineRetailPrice= LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineUnitID = LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineUnitName = LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineNum = LPSTR(row[iItem++]);
		pMedicineStore->csMedicineProductDate = LPSTR(row[iItem++]); 
		pMedicineStore->csMedicineExpireDate = LPSTR(row[iItem++]); 
		pMedicineStore->csCreateTime = LPSTR(row[iItem++]); 
		pMedicineStore->csModifyTime = LPSTR(row[iItem++]); 
	} 
	else
	{
		errRet = err_Medicine_Store_NotExist;
	}
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return errRet;
}

ERRCODE CStoreDB::DeleteMedicineStore(LPTSTR lMedicineSN)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_STORE_DELETE) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (lMedicineSN && strlen(lMedicineSN) != 0)
	{
		if (m_database.ProcedureAddParam("medicineSN", adVarChar, adParamInput, lMedicineSN) != TRUE)
		{
			g_log.Write(m_database.GetLastErrorMsg());
			return err_DB_Proc_Execute;
		}
	}
	else
	{
		if (m_database.ProcedureAddParam("medicineSN", adVarChar, adParamInput, NULL) != TRUE)
		{
			g_log.Write(m_database.GetLastErrorMsg());
			return err_DB_Proc_Execute;
		}
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
		return err_Medicine_Store_Delete;
	}
	return err_OK;
}

ERRCODE CStoreDB::GetMedicineBatchStores(DWORD dwPageNum, 
															DWORD dwNumPerPage, 
															DWORD &dwTotalPage, 
															DWORD &dwTotalNum, 
															vector<MedicineBatchStore*> &vctMedicineBatchStore,
															LPTSTR lpMedicineSN,
															LPTSTR lpMedicineName,
															LPTSTR lpExpireDate)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_BATCHSTORE_GET) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	
	CString csMedicineName = _T("");
	if (lpMedicineName&&strlen(lpMedicineName))
	{
		csMedicineName.Format(_T("%%%s%%"), lpMedicineName);
	}

	if (m_database.ProcedureAddParam("medicineSN", adVarChar, adParamInput, lpMedicineSN) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineName", adVarChar, adParamInput, csMedicineName.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("expireDate", adVarChar, adParamInput, lpExpireDate) != TRUE)
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
		if (iFieldNum < 15)
		{
			g_log.Write(_T("StoreDB Error:Num fields not match!"));
			for (unsigned int i = 0; i < vctMedicineBatchStore.size(); i++)
			{
				delete vctMedicineBatchStore[i];
				vctMedicineBatchStore[i] = NULL;
			}
			vctMedicineBatchStore.clear();

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		int iItem = 0;
		MedicineBatchStore *pMedicineBatchStore = new MedicineBatchStore;
		pMedicineBatchStore->csID = LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineID = LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineSN = LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineName= LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineSpec= LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineVendorName= LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineBatchNum= LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineProductDate= LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineExpireDate= LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineRetailPrice= LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineUnitID = LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineUnitName = LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineNum = LPSTR(row[iItem++]); 
		pMedicineBatchStore->csCreateTime = LPSTR(row[iItem++]); 
		pMedicineBatchStore->csModifyTime = LPSTR(row[iItem++]); 
		vctMedicineBatchStore.push_back(pMedicineBatchStore);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	if (m_database.ProcedureGetOutParam("totalNum", adInteger, &dwTotalNum) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctMedicineBatchStore.size(); i++)
		{
			delete vctMedicineBatchStore[i];
			vctMedicineBatchStore[i] = NULL;
		}
		vctMedicineBatchStore.clear();
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureGetOutParam("totalPage", adInteger, &dwTotalPage) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctMedicineBatchStore.size(); i++)
		{
			delete vctMedicineBatchStore[i];
			vctMedicineBatchStore[i] = NULL;
		}
		vctMedicineBatchStore.clear();
		return err_DB_Proc_Execute;
	}

	return err_OK;
}

ERRCODE CStoreDB::GetMedicineBatchStore(LPTSTR lpID, MedicineBatchStore* pMedicineBatchStore)
{
	if (pMedicineBatchStore == NULL)
	{
		return err_InvalidParameter;
	}
	ERRCODE errRet = err_OK;
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_BATCHSTORE_SELECT) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("storeID", adVarChar, adParamInput, lpID) != TRUE)
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
		if (iFieldNum < 15)
		{
			g_log.Write(_T("MedicineDB Error:Num fields not match!"));
			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		iItem = 0;
		pMedicineBatchStore->csID = LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineID = LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineSN = LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineName= LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineSpec= LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineVendorName= LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineBatchNum= LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineProductDate= LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineExpireDate= LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineRetailPrice= LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineUnitID = LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineUnitName = LPSTR(row[iItem++]); 
		pMedicineBatchStore->csMedicineNum = LPSTR(row[iItem++]); 
		pMedicineBatchStore->csCreateTime = LPSTR(row[iItem++]); 
		pMedicineBatchStore->csModifyTime = LPSTR(row[iItem++]); 
	} 
	else
	{
		errRet = err_Medicine_Store_NotExist;
	}
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return errRet;
}

ERRCODE CStoreDB::UpdateMedicineBatchStore(LPTSTR lpID, LONG lMedicineNum)
{
	if (lMedicineNum < 0)
	{
		return err_InvalidParameter;
	}

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_BATCHSTORE_UPDATE) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adVarChar, adParamInput, lpID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineNum", adInteger, adParamInput, &lMedicineNum) != TRUE)
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

	LONG lReturnVal = 0;
	if (m_database.ProcedureGetOutParam("returnVal", adInteger, &lReturnVal) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if(lReturnVal == 0)
	{
		return err_Medicine_Batch_UpdateFail;
	}
	return err_OK;
}

ERRCODE CStoreDB::DeleteMedicineBatchStore(LPTSTR lpID)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_BATCHSTORE_DELETE) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("storeID", adVarChar, adParamInput, lpID) != TRUE)
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
		return err_Medicine_Store_Delete;
	}
	return err_OK;
}

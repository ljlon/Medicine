#include "stdafx.h"
#include "MedicineBatchDB.h"

CMedicineBatchDB::CMedicineBatchDB()
{

}

CMedicineBatchDB::~CMedicineBatchDB()
{

}

ERRCODE CMedicineBatchDB::GetMedicineBatch(LPTSTR lpMedicineID, LPTSTR lMedicineBatchNum, MedicineBatch* pMedicineBatch)
{
	if (pMedicineBatch == NULL)
	{
		return err_InvalidParameter;
	}
	ERRCODE errRet = err_OK;
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINE_BATCH_SELECT) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adVarChar, adParamInput, lpMedicineID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineBatchNum", adVarChar, adParamInput, lMedicineBatchNum) != TRUE)
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
		if (iFieldNum < 5)
		{
			g_log.Write(_T("MedicineBatchDB Error:Num fields not match!"));
			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		iItem = 0;
		pMedicineBatch->csID = LPSTR(row[iItem++]); 
		pMedicineBatch->csMedicineID = LPSTR(row[iItem++]); 
		pMedicineBatch->csBatchNum = LPSTR(row[iItem++]); 
		pMedicineBatch->csProductDate = LPSTR(row[iItem++]); 
		pMedicineBatch->csExpireDate = LPSTR(row[iItem++]); 
	} 
	else
	{
		errRet = err_Medicine_NotExist;
	}
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return errRet;
}

ERRCODE CMedicineBatchDB::DeleteMedicineBatchs(LPTSTR lpMedicineID)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINE_BATCH_DELETE_BY_MID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adVarChar, adParamInput, lpMedicineID) != TRUE)
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
		return err_Medicine_Batch_Delete;
	}
	return err_OK;
}


ERRCODE CMedicineBatchDB::GetMedicineBatchs(DWORD dwPageNum, 
											DWORD dwNumPerPage, 
											DWORD &dwTotalPage, 
											DWORD &dwTotalNum, 
											vector<MedicineBatch*> &vctMedicineBatch, 
											LPTSTR lpMedicineID, 
											LPTSTR lpBatchNum)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINE_BATCH_GET) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("batchNum", adVarChar, adParamInput, lpBatchNum) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adVarChar, adParamInput, lpMedicineID) != TRUE)
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
		if (iFieldNum < 5)
		{
			g_log.Write(_T("MedicineDB Error:Num fields not match!"));
			for (unsigned int i = 0; i < vctMedicineBatch.size(); i++)
			{
				delete vctMedicineBatch[i];
				vctMedicineBatch[i] = NULL;
			}
			vctMedicineBatch.clear();

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		iItem = 0;
		MedicineBatch *pMedicineBatch = new MedicineBatch;
		pMedicineBatch->csID = LPSTR(row[iItem++]); 
		pMedicineBatch->csMedicineID = LPSTR(row[iItem++]); 
		pMedicineBatch->csBatchNum = LPSTR(row[iItem++]);
		pMedicineBatch->csProductDate = LPSTR(row[iItem++]); 
		pMedicineBatch->csExpireDate = LPSTR(row[iItem++]); 
		vctMedicineBatch.push_back(pMedicineBatch);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	if (m_database.ProcedureGetOutParam("totalNum", adInteger, &dwTotalNum) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctMedicineBatch.size(); i++)
		{
			delete vctMedicineBatch[i];
			vctMedicineBatch[i] = NULL;
		}
		vctMedicineBatch.clear();
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureGetOutParam("totalPage", adInteger, &dwTotalPage) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctMedicineBatch.size(); i++)
		{
			delete vctMedicineBatch[i];
			vctMedicineBatch[i] = NULL;
		}
		vctMedicineBatch.clear();
		return err_DB_Proc_Execute;
	}
	return err_OK;
}

ERRCODE CMedicineBatchDB::UpdateMedicineBatch(LPTSTR lpMedicineID, LPTSTR lMedicineBatchNum, MedicineBatch* pMedicineBatch)
{
	if (lMedicineBatchNum == NULL || pMedicineBatch == NULL)
	{
		return err_InvalidParameter;
	}

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINE_BATCH_UPDATE) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adVarChar, adParamInput, lpMedicineID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("batchNum", adVarChar, adParamInput, lMedicineBatchNum) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("productDate", adVarChar, adParamInput, pMedicineBatch->csProductDate.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("productDate", adVarChar, adParamInput, pMedicineBatch->csExpireDate.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("batchID", adInteger, adParamOutput) != TRUE)
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

	if (m_database.ProcedureGetOutParam("batchID", adInteger, NULL) != TRUE)
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
#include "stdafx.h"
#include "SupplierMedicineDB.h"

CSupplierMedicineDB::CSupplierMedicineDB()
{

}

CSupplierMedicineDB::~CSupplierMedicineDB()
{

}

ERRCODE CSupplierMedicineDB::AddSupplierMedicine(SupplierMedicine *pSupplierMedicne)
{
	if (pSupplierMedicne == NULL)
	{
		return err_InvalidParameter;
	}
	
	ERRCODE errRet = err_OK;

	CMedicineDB medicineDB;
	BOOL bExist = TRUE;
	errRet = medicineDB.CheckMedicineExist(pSupplierMedicne->medicine.csID.GetBuffer(), bExist);
	if (errRet != err_OK)
	{
		return errRet;
	}

	if (bExist == FALSE)
	{

		return errRet;
	}

	errRet = CheckSupplierMedicineExist(pSupplierMedicne->medicine.csID.GetBuffer(), 
										pSupplierMedicne->csSupplierID.GetBuffer(), bExist);
	if (errRet != err_OK)
	{
		return errRet;
	}
	if (bExist == TRUE)
	{
		return err_Medicine_AlreadyExist;
	}

	//connect database
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	//procedure
	if (m_database.ProcedureInit(PROCEDURE_SUPPLIERMEDICINE_ADD) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adVarChar, adParamInput, pSupplierMedicne->medicine.csID.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineSupplierID", adVarChar, adParamInput, pSupplierMedicne->csSupplierID.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	double dbPurPrice = atof(pSupplierMedicne->csPurPrice.GetBuffer());
	if (m_database.ProcedureAddParam("purPrice", adDouble, adParamInput, &dbPurPrice) != TRUE)
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
		return err_Medicine_AddFail;
	}
	return err_OK;
}


ERRCODE CSupplierMedicineDB::UpdateSupplierMedicine(SupplierMedicine *pSupplierMedicne)
{
	if (pSupplierMedicne == NULL)
	{
		return err_InvalidParameter;
	}
	
	ERRCODE errRet = err_OK;

	CMedicineDB medicineDB;
	BOOL bExist = TRUE;
	errRet = medicineDB.CheckMedicineExist(pSupplierMedicne->medicine.csID.GetBuffer(), bExist);
	if (errRet != err_OK)
	{
		return errRet;
	}

	if (bExist == FALSE)
	{
		return err_Medicine_NotExist;
	}

	CSupplierDB supplierDB;
	errRet = supplierDB.CheckSupplierExist(pSupplierMedicne->csSupplierID.GetBuffer(), NULL, bExist);
	if (errRet != err_OK)
	{
		return errRet;
	}
	if (bExist == FALSE)
	{
		return err_Medicine_NotExist;
	}

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_SUPPLIERMEDICINE_UPDATE) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("supplierMedicineId", adVarChar, adParamInput, pSupplierMedicne->csID.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adVarChar, adParamInput, pSupplierMedicne->medicine.csID.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineSupplierID", adVarChar, adParamInput, pSupplierMedicne->csSupplierID.GetBuffer()) != TRUE)
	{ 
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	double dbPurPrice = atof(pSupplierMedicne->csPurPrice.GetBuffer());
	if (m_database.ProcedureAddParam("purPrice", adDouble, adParamInput, &dbPurPrice) != TRUE)
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
		return err_Medicine_UpdateFail;
	}
	return err_OK;
}

ERRCODE CSupplierMedicineDB::CheckSupplierMedicineExist(LPTSTR lpId, BOOL& bExist)
{
	bExist = TRUE;

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_SUPPLIERMEDICINE_CHECKEXIST_BY_MID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("supplierMedicineID", adVarChar, adParamInput, lpId) != TRUE)
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

ERRCODE CSupplierMedicineDB::CheckSupplierMedicineExist(LPTSTR lpMedicineID, LPTSTR lpSupplierID, BOOL& bExist)
{
	bExist = TRUE;

	if (lpMedicineID == NULL || strlen(lpMedicineID) == 0 || 
		lpSupplierID == NULL || strlen(lpSupplierID) == 0)
	{
		bExist = FALSE;
		return err_OK;
	}

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_SUPPLIERMEDICINE_CHECKEXIST) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adVarChar, adParamInput, lpMedicineID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("supplierID", adVarChar, adParamInput, lpSupplierID) != TRUE)
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

ERRCODE CSupplierMedicineDB::GetSupplierMedicine(LPTSTR lpID, SupplierMedicine* pSupplierMedicine)
{
	ERRCODE errRet = err_OK;

	if (pSupplierMedicine == NULL)
	{
		return err_InvalidParameter;
	}

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_SUPPLIERMEDICINE_SELECT) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	if (m_database.ProcedureAddParam("suppliermedicineID", adVarChar, adParamInput, lpID) != TRUE)
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
	CMedicineDB medicineDB;
	if((row = mysql_fetch_row(pResults)))   
	{ 
		int iFieldNum = mysql_num_fields(pResults);
		if (iFieldNum < 6)
		{
			g_log.Write(_T("SupplierMedicineDB Error:Num fields not match!"));
			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		pSupplierMedicine->csID = LPSTR(row[0]); 
		pSupplierMedicine->medicine.csID = LPSTR(row[1]);
		pSupplierMedicine->csSupplierID = LPSTR(row[2]);
		pSupplierMedicine->csCreateTime = LPSTR(row[3]);
		pSupplierMedicine->csModifyTime = LPSTR(row[4]);
		pSupplierMedicine->csPurPrice = LPSTR(row[5]);

	} 
	else
	{
		errRet = err_Medicine_NotExist;
	}
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return errRet;
}

ERRCODE CSupplierMedicineDB::GetSupplierMedicine(LPTSTR lpMedicineID, LPTSTR lpSupplierID, SupplierMedicine* pSupplierMedicine)
{
	ERRCODE errRet = err_OK;

	if (pSupplierMedicine == NULL)
	{
		return err_InvalidParameter;
	}

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_SUPPLIERMEDICINE_SELECT_BY_MID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adVarChar, adParamInput, lpMedicineID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("supplierID", adVarChar, adParamInput, lpSupplierID) != TRUE)
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
	CMedicineDB medicineDB;
	if((row = mysql_fetch_row(pResults)))   
	{ 
		int iFieldNum = mysql_num_fields(pResults);
		if (iFieldNum < 6)
		{
			g_log.Write(_T("SupplierMedicineDB Error:Num fields not match!"));
			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		pSupplierMedicine->csID = LPSTR(row[0]); 
		pSupplierMedicine->medicine.csID = LPSTR(row[1]);
		pSupplierMedicine->csSupplierID = LPSTR(row[2]);
		pSupplierMedicine->csCreateTime = LPSTR(row[3]);
		pSupplierMedicine->csModifyTime = LPSTR(row[4]);
		pSupplierMedicine->csPurPrice = LPSTR(row[5]);
	} 
	else
	{
		errRet = err_Medicine_NotExist;
	}
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return errRet;
}

ERRCODE CSupplierMedicineDB::GetSupplierMedicines(DWORD dwPageNum, 
													DWORD dwNumPerPage, 
													DWORD &dwTotalPage, 
													DWORD &dwTotalNum, 
													vector<SupplierMedicine*> &vctSupplierMedicines, 
													LPTSTR lpSupplierID, 
													LPTSTR lpMedicineSN,
													LPTSTR lpMedicineName, 
													LPTSTR lpMedicineVendorID)
{
	ERRCODE errRet = err_OK;

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_SUPPLIERMEDICINE_GET) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("supplierID", adVarChar, adParamInput, lpSupplierID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineSN", adVarChar, adParamInput, lpMedicineSN) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineName", adVarChar, adParamInput, lpMedicineName) != TRUE)
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
	CMedicineDB medicineDB;
	Medicine medicine;
	while((row = mysql_fetch_row(pResults)))   
	{ 
		int iFieldNum = mysql_num_fields(pResults);
		if (iFieldNum < 21)
		{
			g_log.Write(_T("SupplierMedicineDB Error:Num fields not match!"));
			for (unsigned int i = 0; i < vctSupplierMedicines.size(); i++)
			{
				delete vctSupplierMedicines[i];
				vctSupplierMedicines[i] = NULL;
			}
			vctSupplierMedicines.clear();

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		int iItem = 0;
		SupplierMedicine *pSupplierMedicine = new SupplierMedicine;
		pSupplierMedicine->csID = LPSTR(row[iItem++]); 
		pSupplierMedicine->csSupplierID = LPSTR(row[iItem++]);
		pSupplierMedicine->csPurPrice = LPSTR(row[iItem++]);
		pSupplierMedicine->csCreateTime = LPSTR(row[iItem++]);
		pSupplierMedicine->csModifyTime = LPSTR(row[iItem++]);
		pSupplierMedicine->medicine.csID = LPSTR(row[iItem++]); 
		pSupplierMedicine->medicine.csSN = LPSTR(row[iItem++]); 
		pSupplierMedicine->medicine.csName = LPSTR(row[iItem++]); 
		pSupplierMedicine->medicine.csSpec = LPSTR(row[iItem++]); 
		pSupplierMedicine->medicine.csVendorID = LPSTR(row[iItem++]);
		pSupplierMedicine->medicine.csVendorName = LPSTR(row[iItem++]); 
		pSupplierMedicine->medicine.csCreateTime = LPSTR(row[iItem++]); 
		pSupplierMedicine->medicine.csModifyTime = LPSTR(row[iItem++]); 
		pSupplierMedicine->medicine.util.csID = LPSTR(row[iItem++]); 
		pSupplierMedicine->medicine.util.csName = LPSTR(row[iItem++]); 
		pSupplierMedicine->medicine.csRetailPrice = LPSTR(row[iItem++]); 
		pSupplierMedicine->medicine.type.csID = LPSTR(row[iItem++]); 
		pSupplierMedicine->medicine.medicineClass.csID = LPSTR(row[iItem++]); 
		pSupplierMedicine->medicine.OTC.csID = LPSTR(row[iItem++]); 
		pSupplierMedicine->medicine.form.csID = LPSTR(row[iItem++]); 
		pSupplierMedicine->medicine.csSupplierCount =  LPSTR(row[iItem++]); 

		vctSupplierMedicines.push_back(pSupplierMedicine);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	if (m_database.ProcedureGetOutParam("totalNum", adInteger, &dwTotalNum) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctSupplierMedicines.size(); i++)
		{
			delete vctSupplierMedicines[i];
			vctSupplierMedicines[i] = NULL;
		}
		vctSupplierMedicines.clear();
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureGetOutParam("totalPage", adInteger, &dwTotalPage) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctSupplierMedicines.size(); i++)
		{
			delete vctSupplierMedicines[i];
			vctSupplierMedicines[i] = NULL;
		}
		vctSupplierMedicines.clear();
		return err_DB_Proc_Execute;
	}

	return err_OK;
}

ERRCODE CSupplierMedicineDB::DeleteSupplierMedicine(LPTSTR lpID)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_SUPPLIERMEDICINE_DELETE) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("supplierMedicineID", adVarChar, adParamInput, lpID) != TRUE)
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
		return err_Medicine_DeleteFail;
	}
	return err_OK;
}

ERRCODE CSupplierMedicineDB::DeleteSupplierMedicinesByMID(LPTSTR lpMedicineID)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_SUPPLIERMEDICINE_DELETE_BY_MID) != TRUE)
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
		return err_Medicine_DeleteFail;
	}
	return err_OK;
}

ERRCODE CSupplierMedicineDB::DeleteSupplierMedicinesBySID(LPTSTR lpSupplierID)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_SUPPLIERMEDICINE_DELETE_BY_SID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("supplierID", adVarChar, adParamInput, lpSupplierID) != TRUE)
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
		return err_Medicine_DeleteFail;
	}
	return err_OK;
}

ERRCODE CSupplierMedicineDB::DeleteSupplierMedicine(LPTSTR lpMedicineID, LPTSTR lpSupplierID)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_SUPPLIERMEDICINE_DELETE_BY_MSID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adVarChar, adParamInput, lpMedicineID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("supplierID", adVarChar, adParamInput, lpSupplierID) != TRUE)
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
		return err_Medicine_DeleteFail;
	}
	return err_OK;
}
#include "stdafx.h"
#include "MedicineDB.h"

const CHAR *c_szMedicType[]={
	"中成药",
	"保健药",
	"中草药",
	"西药",
	"医疗器械",
};

LPCSTR GetMedicTypeName(EnumMedicTypeID id)
{
	return c_szMedicType[id];
}

CMedicineDB::CMedicineDB()
{

}

CMedicineDB::~CMedicineDB()
{

}

ERRCODE CMedicineDB::AddMedicine(Medicine *pMedicine)
{
	if (pMedicine == NULL)
	{
		return err_InvalidParameter;
	}

	ERRCODE errRet = err_OK;

	//check medicine be exist or not
	BOOL bExist = TRUE;
	errRet = CheckMedicineExistBySN(pMedicine->csSN.GetBuffer(), bExist);
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
	if (m_database.ProcedureInit(PROCEDURE_MEDICINE_ADD) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineSN", adVarChar, adParamInput, pMedicine->csSN.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineName", adVarChar, adParamInput, pMedicine->csName.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineSpec", adVarChar, adParamInput, pMedicine->csSpec.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineVendorID", adVarChar, adParamInput, pMedicine->csVendorID.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	DWORD dwUnitID = atol(pMedicine->unit.csID.GetBuffer());
	if (m_database.ProcedureAddParam("unitID", adInteger, adParamInput, &dwUnitID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	double dbRetailPrice = atof(pMedicine->csRetailPrice.GetBuffer());
	if (m_database.ProcedureAddParam("retailPrice", adDouble, adParamInput, &dbRetailPrice) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	DWORD dwTypeID = atol(pMedicine->type.csID.GetBuffer());
	if (m_database.ProcedureAddParam("typeID", adInteger, adParamInput, &dwTypeID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	DWORD dwOTCID = atol(pMedicine->OTC.csID.GetBuffer());
	if (m_database.ProcedureAddParam("OTCID", adInteger, adParamInput, &dwOTCID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	DWORD dwFormID = atol(pMedicine->form.csID.GetBuffer());
	if (m_database.ProcedureAddParam("formID", adInteger, adParamInput, &dwFormID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("regNum", adVarChar, adParamInput, pMedicine->csRegNum.GetBuffer()) != TRUE)
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


ERRCODE CMedicineDB::UpdateMedicine(LPTSTR lpID, Medicine *pMedicine)
{
	if (pMedicine == NULL)
	{
		return err_InvalidParameter;
	}

	ERRCODE errRet = err_OK;

	/*if (_tcscmp(lpOldID, pMedicine->csSN.GetBuffer()))
	{
		BOOL bExist = TRUE;

		errRet = CheckMedicineExistBySN(pMedicine->csSN.GetBuffer(), bExist);
		if (errRet != err_OK)
		{
			return errRet;
		}

		if (bExist == TRUE)
		{
			return err_Medicine_AlreadyExist;
		}
	}*/

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINE_UPDATE) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("oldID", adVarChar, adParamInput, lpID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adVarChar, adParamInput, pMedicine->csID.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineSN", adVarChar, adParamInput, pMedicine->csSN.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineName", adVarChar, adParamInput, pMedicine->csName.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineSpec", adVarChar, adParamInput, pMedicine->csSpec.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineVendorID", adVarChar, adParamInput, pMedicine->csVendorID.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}

	LONG lUnitID = atol(pMedicine->unit.csID.GetBuffer());
	if (m_database.ProcedureAddParam("unitID", adInteger, adParamInput, &lUnitID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	double dbRetailPrice = atof(pMedicine->csRetailPrice.GetBuffer());
	if (m_database.ProcedureAddParam("retailPrice", adDouble, adParamInput, &dbRetailPrice) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	DWORD dwTypeID = atol(pMedicine->type.csID.GetBuffer());
	if (m_database.ProcedureAddParam("typeID", adInteger, adParamInput, &dwTypeID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	DWORD dwOTCID = atol(pMedicine->OTC.csID.GetBuffer());
	if (m_database.ProcedureAddParam("OTCID", adInteger, adParamInput, &dwOTCID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	DWORD dwFormID = atol(pMedicine->form.csID.GetBuffer());
	if (m_database.ProcedureAddParam("formID", adInteger, adParamInput, &dwFormID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("regNum", adVarChar, adParamInput, pMedicine->csRegNum.GetBuffer()) != TRUE)
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

ERRCODE CMedicineDB::UpdateMedicineRetailPrice(LPTSTR lpID, double dbRetailPrice)
{
	if (dbRetailPrice < 0)
	{
		return err_InvalidParameter;
	}

	ERRCODE errRet = err_OK;

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINE_UPDATE_RETAILPRICE) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adVarChar, adParamInput, lpID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("retailPrice", adDouble, adParamInput, &dbRetailPrice) != TRUE)
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

ERRCODE CMedicineDB::CheckMedicineExist(LPTSTR lpMedicineID, BOOL& bExist)
{
	bExist = TRUE;

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINE_CHECKEXIST) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adVarChar, adParamInput, lpMedicineID) != TRUE)
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

ERRCODE CMedicineDB::CheckMedicineExistBySN(LPTSTR lpMedicineSN, BOOL& bExist)
{
	bExist = TRUE;

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINE_CHECKEXIST_BYSN) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineSN", adVarChar, adParamInput, lpMedicineSN) != TRUE)
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


ERRCODE CMedicineDB::GetMedicine(LPTSTR lpID, Medicine* pMedicine)
{
	if (pMedicine == NULL)
	{
		return err_InvalidParameter;
	}
	ERRCODE errRet = err_OK;
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINE_SELECT) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adVarChar, adParamInput, lpID) != TRUE)
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
		if (iFieldNum < 18)
		{
			g_log.Write(_T("MedicineDB Error:Num fields not match!"));
			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		iItem = 0;
		pMedicine->csID = LPSTR(row[iItem++]); 
		pMedicine->csSN = LPSTR(row[iItem++]); 
		pMedicine->csName = LPSTR(row[iItem++]); 
		pMedicine->csSpec = LPSTR(row[iItem++]); 
		pMedicine->csVendorID = LPSTR(row[iItem++]);
		pMedicine->csVendorName = LPSTR(row[iItem++]); 
		pMedicine->csCreateTime = LPSTR(row[iItem++]); 
		pMedicine->csModifyTime = LPSTR(row[iItem++]); 
		pMedicine->unit.csID = LPSTR(row[iItem++]); 
		pMedicine->unit.csName = LPSTR(row[iItem++]); 
		pMedicine->csRetailPrice = LPSTR(row[iItem++]); 
		pMedicine->type.csID = LPSTR(row[iItem++]); 
		pMedicine->medicineClass.csID = LPSTR(row[iItem++]); 
		pMedicine->OTC.csID = LPSTR(row[iItem++]); 
		pMedicine->form.csID = LPSTR(row[iItem++]); 
		pMedicine->form.csName = LPSTR(row[iItem++]);
		pMedicine->csSupplierCount =  LPSTR(row[iItem++]); 
		pMedicine->csRegNum = LPSTR(row[iItem++]);
	} 
	else
	{
		errRet = err_Medicine_NotExist;
	}
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return errRet;
}

ERRCODE CMedicineDB::GetMedicineBySN(LPTSTR lpSN, Medicine* pMedicine)
{
	if (pMedicine == NULL)
	{
		return err_InvalidParameter;
	}
	ERRCODE errRet = err_OK;
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINE_SELECT_BYSN) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineSN", adVarChar, adParamInput, lpSN) != TRUE)
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
		if (iFieldNum < 18)
		{
			g_log.Write(_T("MedicineDB Error:Num fields not match!"));
			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		iItem = 0;
		pMedicine->csID = LPSTR(row[iItem++]); 
		pMedicine->csSN = LPSTR(row[iItem++]); 
		pMedicine->csName = LPSTR(row[iItem++]); 
		pMedicine->csSpec = LPSTR(row[iItem++]); 
		pMedicine->csVendorID = LPSTR(row[iItem++]); 
		pMedicine->csVendorName = LPSTR(row[iItem++]); 
		pMedicine->csCreateTime = LPSTR(row[iItem++]); 
		pMedicine->csModifyTime = LPSTR(row[iItem++]); 
		pMedicine->unit.csID = LPSTR(row[iItem++]); 
		pMedicine->unit.csName = LPSTR(row[iItem++]); 
		pMedicine->csRetailPrice = LPSTR(row[iItem++]); 
		pMedicine->type.csID = LPSTR(row[iItem++]); 
		pMedicine->medicineClass.csID = LPSTR(row[iItem++]); 
		pMedicine->OTC.csID = LPSTR(row[iItem++]); 
		pMedicine->form.csID = LPSTR(row[iItem++]);
		pMedicine->form.csName = LPSTR(row[iItem++]);
		pMedicine->csSupplierCount =  LPSTR(row[iItem++]); 
		pMedicine->csRegNum = LPSTR(row[iItem++]);
	} 
	else
	{
		errRet = err_Medicine_NotExist;
	}
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return errRet;
}

ERRCODE CMedicineDB::GetMedicines(DWORD dwPageNum, 
								DWORD dwNumPerPage, 
								DWORD &dwTotalPage, 
								DWORD &dwTotalNum, 
								vector<Medicine*> &vctMedicines, 
								LPTSTR lpMedicineSN, 
								LPTSTR lpMedicineName,
								LPTSTR lpVendorID)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINE_GET) != TRUE)
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
	if (m_database.ProcedureAddParam("medicineVendorID", adVarChar, adParamInput, lpVendorID) != TRUE)
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
		if (iFieldNum < 18)
		{
			g_log.Write(_T("MedicineDB Error:Num fields not match!"));
			for (unsigned int i = 0; i < vctMedicines.size(); i++)
			{
				delete vctMedicines[i];
				vctMedicines[i] = NULL;
			}
			vctMedicines.clear();

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		iItem = 0;
		Medicine *pMedicine = new Medicine;
		pMedicine->csID = LPSTR(row[iItem++]); 
		pMedicine->csSN = LPSTR(row[iItem++]); 
		pMedicine->csName = LPSTR(row[iItem++]);
		pMedicine->csSpec = LPSTR(row[iItem++]); 
		pMedicine->csVendorID = LPSTR(row[iItem++]); 
		pMedicine->csVendorName = LPSTR(row[iItem++]); 
		pMedicine->csCreateTime = LPSTR(row[iItem++]); 
		pMedicine->csModifyTime = LPSTR(row[iItem++]); 
		pMedicine->unit.csID = LPSTR(row[iItem++]); 
		pMedicine->unit.csName = LPSTR(row[iItem++]); 
		pMedicine->csRetailPrice = LPSTR(row[iItem++]); 
		pMedicine->type.csID = LPSTR(row[iItem++]); 
		pMedicine->medicineClass.csID = LPSTR(row[iItem++]); 
		pMedicine->OTC.csID = LPSTR(row[iItem++]); 
		pMedicine->form.csID = LPSTR(row[iItem++]); 
		pMedicine->form.csName = LPSTR(row[iItem++]);
		pMedicine->csSupplierCount =  LPSTR(row[iItem++]); 
		pMedicine->csRegNum = LPSTR(row[iItem++]);
		vctMedicines.push_back(pMedicine);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	if (m_database.ProcedureGetOutParam("totalNum", adInteger, &dwTotalNum) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctMedicines.size(); i++)
		{
			delete vctMedicines[i];
			vctMedicines[i] = NULL;
		}
		vctMedicines.clear();
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureGetOutParam("totalPage", adInteger, &dwTotalPage) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctMedicines.size(); i++)
		{
			delete vctMedicines[i];
			vctMedicines[i] = NULL;
		}
		vctMedicines.clear();
		return err_DB_Proc_Execute;
	}

	return err_OK;
}

ERRCODE CMedicineDB::DeleteMedicine(LPTSTR lpID)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINE_DELETE) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("medicineID", adVarChar, adParamInput, lpID) != TRUE)
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

ERRCODE CMedicineDB::GetMedicineUnit(int iUnitID, MedicineUtil* pMedicineUtil)
{
	if (pMedicineUtil == NULL)
	{
		return err_InvalidParameter;
	}

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINEUNIT_SELECT) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("unitID", adInteger, adParamInput, &iUnitID) != TRUE)
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
	if (row = mysql_fetch_row(pResults))
	{ 
		int iFieldNum = mysql_num_fields(pResults);
		if (iFieldNum < 2)
		{
			g_log.Write(_T("MedicineDB Error:Medicine Util Num fields not match!"));

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		iItem = 0;
		pMedicineUtil->csID = LPSTR(row[iItem++]); 
		pMedicineUtil->csName = LPSTR(row[iItem++]);  
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return err_OK;
}


ERRCODE CMedicineDB::GetMedicineUnits(vector<MedicineUtil*> &vctMedicineUtils)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINEUNIT_GET) != TRUE)
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
	while(row = mysql_fetch_row(pResults))  
	{ 
		int iFieldNum = mysql_num_fields(pResults);
		if (iFieldNum < 2)
		{
			g_log.Write(_T("MedicineDB Error:Medicine Util Num fields not match!"));
			for (unsigned int i = 0; i < vctMedicineUtils.size(); i++)
			{
				delete vctMedicineUtils[i];
				vctMedicineUtils[i] = NULL;
			}
			vctMedicineUtils.clear();

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		iItem = 0;
		MedicineUtil *pMedicineUtil = new MedicineUtil;
		pMedicineUtil->csID = LPSTR(row[iItem++]); 
		pMedicineUtil->csName = LPSTR(row[iItem++]);  
		vctMedicineUtils.push_back(pMedicineUtil);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return err_OK;
}

ERRCODE CMedicineDB::GetMedicineType(int iTypeID, MedicineType* pMedicineType)
{
	if (pMedicineType == NULL)
	{
		return err_InvalidParameter;
	}

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINETYPE_SELECT) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("typeID", adInteger, adParamInput, &iTypeID) != TRUE)
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
	if (row = mysql_fetch_row(pResults))
	{ 
		int iFieldNum = mysql_num_fields(pResults);
		if (iFieldNum < 2)
		{
			g_log.Write(_T("MedicineDB Error:Medicine Type Num fields not match!"));

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		iItem = 0;
		pMedicineType->csID = LPSTR(row[iItem++]); 
		pMedicineType->csName = LPSTR(row[iItem++]);  
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return err_OK;
}


ERRCODE CMedicineDB::GetMedicineTypes(vector<MedicineType*> &vctMedicineTypes)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINETYPE_GET) != TRUE)
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
	while(row = mysql_fetch_row(pResults))  
	{ 
		int iFieldNum = mysql_num_fields(pResults);
		if (iFieldNum < 2)
		{
			g_log.Write(_T("MedicineDB Error:Medicine Type Num fields not match!"));
			for (unsigned int i = 0; i < vctMedicineTypes.size(); i++)
			{
				delete vctMedicineTypes[i];
				vctMedicineTypes[i] = NULL;
			}
			vctMedicineTypes.clear();

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		iItem = 0;
		MedicineType *pMedicineType = new MedicineType;
		pMedicineType->csID = LPSTR(row[iItem++]); 
		pMedicineType->csName = LPSTR(row[iItem++]);  
		vctMedicineTypes.push_back(pMedicineType);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return err_OK;
}

ERRCODE CMedicineDB::GetMedicineOTC(int iOTCID, MedicineOTC* pMedicineOTC)
{
	if (pMedicineOTC == NULL)
	{
		return err_InvalidParameter;
	}

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINEOTC_SELECT) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("OTCID", adInteger, adParamInput, &iOTCID) != TRUE)
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
	if (row = mysql_fetch_row(pResults))
	{ 
		int iFieldNum = mysql_num_fields(pResults);
		if (iFieldNum < 2)
		{
			g_log.Write(_T("MedicineDB Error:Medicine OTC Num fields not match!"));

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		iItem = 0;
		pMedicineOTC->csID = LPSTR(row[iItem++]); 
		pMedicineOTC->csName = LPSTR(row[iItem++]);  
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return err_OK;
}


ERRCODE CMedicineDB::GetMedicineOTCs(vector<MedicineOTC*> &vctMedicineOTCs)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINEOTC_GET) != TRUE)
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
	while(row = mysql_fetch_row(pResults))  
	{ 
		int iFieldNum = mysql_num_fields(pResults);
		if (iFieldNum < 2)
		{
			g_log.Write(_T("MedicineDB Error:Medicine OTC Num fields not match!"));
			for (unsigned int i = 0; i < vctMedicineOTCs.size(); i++)
			{
				delete vctMedicineOTCs[i];
				vctMedicineOTCs[i] = NULL;
			}
			vctMedicineOTCs.clear();

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		iItem = 0;
		MedicineOTC *pMedicineOTC = new MedicineOTC;
		pMedicineOTC->csID = LPSTR(row[iItem++]); 
		pMedicineOTC->csName = LPSTR(row[iItem++]);  
		vctMedicineOTCs.push_back(pMedicineOTC);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return err_OK;
}

ERRCODE CMedicineDB::GetMedicineForm(int iFormID, MedicineForm* pMedicineForm)
{
	if (pMedicineForm == NULL)
	{
		return err_InvalidParameter;
	}

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINEFORM_SELECT) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("formID", adInteger, adParamInput, &iFormID) != TRUE)
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
	if (row = mysql_fetch_row(pResults))
	{ 
		int iFieldNum = mysql_num_fields(pResults);
		if (iFieldNum < 2)
		{
			g_log.Write(_T("MedicineDB Error:Medicine Form Num fields not match!"));

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		iItem = 0;
		pMedicineForm->csID = LPSTR(row[iItem++]); 
		pMedicineForm->csName = LPSTR(row[iItem++]);  
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return err_OK;
}


ERRCODE CMedicineDB::GetMedicineForms(vector<MedicineForm*> &vctMedicineForms)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_MEDICINEFORM_GET) != TRUE)
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
	while(row = mysql_fetch_row(pResults))  
	{ 
		int iFieldNum = mysql_num_fields(pResults);
		if (iFieldNum < 2)
		{
			g_log.Write(_T("MedicineDB Error:Medicine Form Num fields not match!"));
			for (unsigned int i = 0; i < vctMedicineForms.size(); i++)
			{
				delete vctMedicineForms[i];
				vctMedicineForms[i] = NULL;
			}
			vctMedicineForms.clear();

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		iItem = 0;
		MedicineForm *pMedicineForm = new MedicineForm;
		pMedicineForm->csID = LPSTR(row[iItem++]); 
		pMedicineForm->csName = LPSTR(row[iItem++]);  
		vctMedicineForms.push_back(pMedicineForm);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return err_OK;
}
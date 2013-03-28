#include "stdafx.h"
#include "VendorDB.h"

CVendorDB::CVendorDB()
{

}

CVendorDB::~CVendorDB()
{

}

ERRCODE CVendorDB::AddVendor(Vendor *pVendor)
{
	ERRCODE errRet = err_OK;
	if (pVendor == NULL)
	{
		return err_InvalidParameter;
	}

	BOOL bAvaliable = FALSE;
	errRet = CheckVendorNameAvaliable(NULL, pVendor->csName.GetBuffer(), bAvaliable);
	if (errRet != err_OK)
	{
		return errRet;
	}

	if (bAvaliable == FALSE)
	{
		return err_Vendor_AlreadyExist;
	}

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_VENDOR_ADD) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("vendorName", adVarChar, adParamInput, pVendor->csName.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("vendorTelephone", adVarChar, adParamInput, pVendor->csTelephone.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("vendorAddress", adVarChar, adParamInput, pVendor->csAddress.GetBuffer()) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("vendorID", adInteger, adParamOutput) != TRUE)
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

	LPTSTR lpVendorID = NULL;
	if (m_database.ProcedureGetOutParam("vendorID", adVarChar, &lpVendorID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	pVendor->csID.Format(_T("%s"), lpVendorID);
	delete lpVendorID;
	lpVendorID = NULL;

	int iRet = 0;
	if (m_database.ProcedureGetOutParam("returnVal", adInteger, &iRet) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if(iRet == 0)
	{
		return err_Vendor_AddFail;
	}
	return err_OK;
}


ERRCODE CVendorDB::UpdateVendor(LPTSTR lpID, LPTSTR lpName, LPTSTR lpTelephone, LPTSTR lpAddress)
{
	ERRCODE errRet = err_OK;

	BOOL bAvaliable = FALSE;
	errRet = CheckVendorNameAvaliable(lpID, lpName, bAvaliable);
	if (errRet != err_OK)
	{
		return errRet;
	}

	if (bAvaliable == FALSE)
	{
		return err_Vendor_AlreadyExist;
	}

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_VENDOR_UPDATE) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("vendorID", adVarChar, adParamInput, lpID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("vendorName", adVarChar, adParamInput, lpName) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("vendorTelephone", adVarChar, adParamInput, lpTelephone) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("vendorAddress", adVarChar, adParamInput, lpAddress) != TRUE)
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
		return err_Vendor_UpdateFail;
	}
	return err_OK;
}

ERRCODE CVendorDB::CheckVendorExit(LPTSTR lpID, LPTSTR lpName, BOOL& bExist)
{
	bExist = FALSE;

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_VENDOR_CHECKEXIST) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("vendorID", adVarChar, adParamInput, lpID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("vendorName", adVarChar, adParamInput, lpName) != TRUE)
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

ERRCODE CVendorDB::CheckVendorNameAvaliable(LPTSTR lpCurrentID, LPTSTR lpName, BOOL& bAvaliable)
{
	bAvaliable = FALSE;

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_VENDOR_CHECKOTHERSEXIST) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("currentID", adVarChar, adParamInput, lpCurrentID) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("vendorName", adVarChar, adParamInput, lpName) != TRUE)
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
		bAvaliable = TRUE;
	}
	return err_OK;
}

ERRCODE CVendorDB::GetVendor(LPTSTR lpID, Vendor* pVendor)
{
	if (pVendor == NULL)
	{
		return err_InvalidParameter;
	}

	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_VENDOR_SELECT) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("vendorID", adVarChar, adParamInput, lpID) != TRUE)
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
		if (iFieldNum < 7)
		{
			g_log.Write(_T("VendorDB Error:Num fields not match!"));

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		pVendor->csID = LPSTR(row[0]); 
		pVendor->csName = LPSTR(row[1]);
		pVendor->csTelephone = LPSTR(row[2]);
		pVendor->csAddress = LPSTR(row[3]);
		pVendor->csMedicineCount = LPSTR(row[4]);
		pVendor->csCreateTime = LPSTR(row[5]);
		pVendor->csModifyTime = LPSTR(row[6]);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	return err_OK;
}

ERRCODE CVendorDB::GetVendors(DWORD dwPageNum, DWORD dwNumPerPage, DWORD &dwTotalPage, DWORD &dwTotalNum, vector<Vendor*> &vctVendors, LPTSTR lpMatchSubString)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_VENDOR_GET) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("subName", adVarChar, adParamInput, lpMatchSubString) != TRUE)
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
		if (iFieldNum < 7)
		{
			g_log.Write(_T("Vendor Error:Num fields not match!"));
			for (unsigned int i = 0; i < vctVendors.size(); i++)
			{
				delete vctVendors[i];
				vctVendors[i] = NULL;
			}
			vctVendors.clear();

			mysql_free_result(pResults);
			m_database.FreeOtherResults();
			return err_DB_NumFieldNotMatch;
		}

		Vendor *pVendor = new Vendor;
		pVendor->csID = LPSTR(row[0]); 
		pVendor->csName = LPSTR(row[1]);
		pVendor->csTelephone = LPSTR(row[2]);
		pVendor->csAddress = LPSTR(row[3]);
		pVendor->csMedicineCount = LPSTR(row[4]);
		pVendor->csCreateTime = LPSTR(row[5]);
		pVendor->csModifyTime = LPSTR(row[6]);
		vctVendors.push_back(pVendor);
	} 
	mysql_free_result(pResults);
	m_database.FreeOtherResults();

	if (m_database.ProcedureGetOutParam("totalNum", adInteger, &dwTotalNum) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctVendors.size(); i++)
		{
			delete vctVendors[i];
			vctVendors[i] = NULL;
		}
		vctVendors.clear();
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureGetOutParam("totalPage", adInteger, &dwTotalPage) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());

		for (unsigned int i = 0; i < vctVendors.size(); i++)
		{
			delete vctVendors[i];
			vctVendors[i] = NULL;
		}
		vctVendors.clear();
		return err_DB_Proc_Execute;
	}

	return err_OK;
}

ERRCODE CVendorDB::DeleteVendor(LPTSTR lpID)
{
	if (m_database.Connect() != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Open;
	}

	if (m_database.ProcedureInit(PROCEDURE_VENDOR_DELETE) != TRUE)
	{
		g_log.Write(m_database.GetLastErrorMsg());
		return err_DB_Proc_Execute;
	}
	if (m_database.ProcedureAddParam("vendorID", adVarChar, adParamInput, lpID) != TRUE)
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
		return err_Vendor_DeleteFail;
	}
	return err_OK;
}
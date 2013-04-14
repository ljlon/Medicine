#pragma once
#include "StdHead.h"
#include "Database.h"

//Retail
#define PROCEDURE_RETAIL_GET _T("retail_get")
#define PROCEDURE_RETAIL_ADD _T("retail_add")
#define PROCEDURE_RETAIL_SELECT _T("retail_select")

#define PROCEDURE_RETAIL_ITEM_ADD _T("retail_item_add")
#define PROCEDURE_RETAIL_ITEM_GET _T("retail_item_get")

typedef struct _Retail
{
	CString csID;
	CString csSN;
	CString csUserID;
	CString csUserUID;
	CString csUserName;
	CString csCreateTime;
	CString csTotalPrcie;
	CString csInPrice;
	CString csOutPrice;
	CString csPOSID;
	CString csPCID;
	CString csPCMAC;
}Retail;

typedef struct _RetailItem
{
	CString csID;
	CString csRetailID;
	CString csMedicineID;
	CString csMedicineSN;
	CString csMedicineName;
	CString csMedicinePrice;
	CString csMedicineUnitName;
	CString csMedicineNumber;
	CString csRetailPrice;
}RetailItem;

class CRetailDB
{
public:
	CRetailDB();
	~CRetailDB();
	ERRCODE GetRetails(DWORD dwPageNum, 
									DWORD dwNumPerPage, 
									DWORD &dwTotalPage, 
									DWORD &dwTotalNum, 
									double &dbTotalPrice, 
									vector<Retail*> &vctRetail,
									LPTSTR lpPosID = NULL,
									LPTSTR lpUserID = NULL,
									LPTSTR lpRetailDateBegin = NULL,
									LPTSTR lpRetailDateEnd = NULL);
	ERRCODE GetRetail(LPTSTR lpID, Retail* pRetail);

	ERRCODE AddRetail(Retail *pRetail);
	ERRCODE AddRetailItem(RetailItem *pRetailItem);
	ERRCODE GetRetailItems(LPTSTR lpRetailID, vector<RetailItem*> &vctRetailItem);

private:
	CDatabase m_database;
};
#pragma once
#include "StdHead.h"
#include "Database.h"
#include "SupplierDB.h"
#include "MedicineDB.h"
#include "MedicineBatchDB.h"

//Medicne)
#define PROCEDURE_PURCHASE_ADD _T("purchase_add")
#define PROCEDURE_PURCHASE_DELETE _T("purchase_delete")
#define PROCEDURE_PURCHASE_GET _T("purchase_get")
#define PROCEDURE_PURCHASE_SELECT _T("purchase_select")

typedef struct _Purchase
{
	CString csID;
	CString csUserID;
	CString csUserUID;
	CString csUserName;
	CString csSupplierID;
	CString csSupplierName;
	Medicine medicine;
	CString csNumber;
	CString csPurPrice;
	MedicineBatch medicineBatch;
	CString csCreateTime;
	CString csPurchaseTime;
}Purchase;

class CPurchaseDB
{
public:
	CPurchaseDB();
	~CPurchaseDB();

	ERRCODE AddPurchase(Purchase *pPurchase);
	ERRCODE GetPurchases(DWORD dwPageNum, 
										DWORD dwNumPerPage, 
										DWORD &dwTotalPage, 
										DWORD &dwTotalNum, 
										double &dbTotalPrice, 
										vector<Purchase*> &vctPurchases,
										LPTSTR lpPurDateBegin = _T(""),
										LPTSTR lpPurDateEnd = _T(""),
										LPTSTR lpMedicineSN = _T(""),
										LPTSTR lpMedicineName = _T(""),
										LPTSTR lpMedicineTypeID = _T(""),
										LPTSTR lpMedicineBatchNum = _T(""),
										LPTSTR lpSupplierID = _T(""));
	ERRCODE GetPurchase(LPTSTR lpID, Purchase* pPurchase);
	ERRCODE DeletePurchase(LPTSTR lpID);

private:
	CDatabase m_database;
};
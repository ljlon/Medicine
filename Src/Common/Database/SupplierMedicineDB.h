#pragma once
#include "StdHead.h"
#include "Database.h"
#include "MedicineDB.h"
#include "SupplierDB.h"

#define PROCEDURE_SUPPLIERMEDICINE_GET _T("suppliermedicine_get")
#define PROCEDURE_SUPPLIERMEDICINE_SELECT _T("suppliermedicine_select")
#define PROCEDURE_SUPPLIERMEDICINE_SELECT_BY_MID _T("suppliermedicine_select_by_mid")
#define PROCEDURE_SUPPLIERMEDICINE_ADD _T("suppliermedicine_add")
#define PROCEDURE_SUPPLIERMEDICINE_UPDATE _T("suppliermedicine_update")
#define PROCEDURE_SUPPLIERMEDICINE_CHECKEXIST_BY_MID _T("suppliermedicine_check_exist_by_mid")
#define PROCEDURE_SUPPLIERMEDICINE_CHECKEXIST _T("suppliermedicine_check_exist")
#define PROCEDURE_SUPPLIERMEDICINE_DELETE _T("suppliermedicine_delete")
#define PROCEDURE_SUPPLIERMEDICINE_DELETE_BY_MSID _T("suppliermedicine_delete_by_msid")
#define PROCEDURE_SUPPLIERMEDICINE_DELETE_BY_MID _T("suppliermedicine_delete_by_mid")
#define PROCEDURE_SUPPLIERMEDICINE_DELETE_BY_SID _T("suppliermedicine_delete_by_sid")

typedef struct _SupplierMedicine
{
	CString csID;
	CString csSupplierID;
	CString csPurPrice;
	CString csCreateTime;
	CString csModifyTime;
	Medicine medicine;
}SupplierMedicine;

class CSupplierMedicineDB
{
public:
	CSupplierMedicineDB();
	~CSupplierMedicineDB();

	ERRCODE GetSupplierMedicine(LPTSTR lpID, SupplierMedicine* pSupplierMedicine);
	ERRCODE GetSupplierMedicine(LPTSTR lpMedicineID, LPTSTR lpSupplierID, SupplierMedicine* pSupplierMedicine);
	ERRCODE GetSupplierMedicines(DWORD dwPageNum, 
								DWORD dwNumPerPage, 
								DWORD &dwTotalPage, 
								DWORD &dwTotalNum, 
								vector<SupplierMedicine*> &vctSupplierMedicines, 
								LPTSTR lpSupplierID = NULL, 
								LPTSTR lpMedicineSN = NULL,
								LPTSTR lpMedicineName = NULL, 
								LPTSTR lpMedicineVendorID = NULL);
	ERRCODE AddSupplierMedicine(SupplierMedicine *pSupplierMedicne);
	ERRCODE UpdateSupplierMedicine(SupplierMedicine *pSupplierMedicne);
	ERRCODE DeleteSupplierMedicine(LPTSTR lpID);
	ERRCODE DeleteSupplierMedicine(LPTSTR lpMedicineID, LPTSTR lpSupplierID);
	ERRCODE DeleteSupplierMedicinesByMID(LPTSTR lpMedicineID);
	ERRCODE DeleteSupplierMedicinesBySID(LPTSTR lpSupplierID);

	ERRCODE CheckSupplierMedicineExist(LPTSTR lpMedicineID, LPTSTR lpSupplierID, BOOL& bExist);
	ERRCODE CheckSupplierMedicineExist(LPTSTR lpId, BOOL& bExist);

private:
	CDatabase m_database;
};
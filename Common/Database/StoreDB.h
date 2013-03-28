#pragma once
#include "StdHead.h"
#include "Database.h"

#define PROCEDURE_STORE_GET _T("store_get")
#define PROCEDURE_STORE_SELECT _T("store_select")
#define PROCEDURE_STORE_DELETE _T("store_delete")

#define PROCEDURE_BATCHSTORE_GET _T("store_batch_get")
#define PROCEDURE_BATCHSTORE_SELECT _T("store_batch_select")
#define PROCEDURE_BATCHSTORE_UPDATE _T("store_batch_update")
#define PROCEDURE_BATCHSTORE_DELETE _T("store_batch_delete")

typedef struct _MedicineStore
{
	CString csID;
	CString csMedicineID;
	CString csMedicineSN;
	CString csMedicineName;
	CString csMedicineSpec;
	CString csMedicineVendorID;
	CString csMedicineVendorName;
	CString csMedicineRetailPrice;
	CString csMedicineUnitID;
	CString csMedicineUnitName;
	CString csMedicineNum;
	CString csMedicineProductDate;
	CString csMedicineExpireDate;
	CString csCreateTime;
	CString csModifyTime;
}MedicineStore;

typedef struct _MedicineBatchStore
{
	CString csID;
	CString csMedicineID;
	CString csMedicineSN;
	CString csMedicineName;
	CString csMedicineSpec;
	CString csMedicineVendorName;
	CString csMedicineRetailPrice;
	CString csMedicineUnitID;
	CString csMedicineUnitName;
	CString csMedicineNum;
	CString csMedicineBatchNum;
	CString csMedicineProductDate;
	CString csMedicineExpireDate;
	CString csCreateTime;
	CString csModifyTime;
}MedicineBatchStore;

class CStoreDB
{
public:
	CStoreDB();
	~CStoreDB();

	ERRCODE GetMedicineStores(DWORD dwPageNum, 
		DWORD dwNumPerPage, 
		DWORD &dwTotalPage, 
		DWORD &dwTotalNum, 
		vector<MedicineStore*> &vctMedicineStore,
		LPTSTR lpMedicineSN = NULL,
		LPTSTR lpMedicineName = NULL,
		LPTSTR lpExpireDate = NULL,
		LPTSTR lpMedicineVendorID = NULL);
	ERRCODE GetMedicineStore(LPTSTR lMedicineSN, MedicineStore* pMedicineStore);

	ERRCODE DeleteMedicineStore(LPTSTR lMedicineSN);

	ERRCODE GetMedicineBatchStores(DWORD dwPageNum, 
												DWORD dwNumPerPage, 
												DWORD &dwTotalPage, 
												DWORD &dwTotalNum, 
												vector<MedicineBatchStore*> &vctMedicineBatchStore,
												LPTSTR lpMedicineSN = _T(""),
												LPTSTR lpMedicineName = _T(""),
												LPTSTR lpExpireDate = _T(""));

	ERRCODE GetMedicineBatchStore(LPTSTR lpID, MedicineBatchStore* pMedicineBatchStore);

	ERRCODE UpdateMedicineBatchStore(LPTSTR lpID, LONG lMedicineNum);

	ERRCODE DeleteMedicineBatchStore(LPTSTR lpID);

protected:
	

private:
	CDatabase m_database;
};
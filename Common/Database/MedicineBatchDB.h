#pragma once
#include "StdHead.h"
#include "Database.h"

#define PROCEDURE_MEDICINE_BATCH_GET _T("medicine_batch_get")
#define PROCEDURE_MEDICINE_BATCH_SELECT _T("medicine_batch_select")
#define PROCEDURE_MEDICINE_BATCH_DELETE_BY_MID  _T("medicine_batch_delete_by_mid")
#define PROCEDURE_MEDICINE_BATCH_UPDATE _T("medicine_batch_update")

typedef struct _MedicineBatch
{
	CString csID;
	CString csMedicineID;
	CString csBatchNum;
	CString csProductDate;
	CString csExpireDate;
}MedicineBatch;

class CMedicineBatchDB
{
public:
	CMedicineBatchDB();
	~CMedicineBatchDB();

	ERRCODE GetMedicineBatch(LPTSTR lpMedicineID, LPTSTR lMedicineBatchNum, MedicineBatch* pMedicineBatch);
	ERRCODE GetMedicineBatchs(DWORD dwPageNum, 
								DWORD dwNumPerPage, 
								DWORD &dwTotalPage, 
								DWORD &dwTotalNum, 
								vector<MedicineBatch*> &vctMedicineBatch, 
								LPTSTR lpMedicineID, 
								LPTSTR lpBatchNum = NULL);
	ERRCODE DeleteMedicineBatchs(LPTSTR lpMedicineID);
	ERRCODE UpdateMedicineBatch(LPTSTR lpMedicineID, LPTSTR lMedicineBatchNum, MedicineBatch *pMedicineBatch);
	
private:
	CDatabase m_database;
};
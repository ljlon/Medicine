#pragma once
#include "StdHead.h"
#include "Database.h"


#define PROCEDURE_PURCHASE_HISTORY_ADD _T("purchase_history_add")
#define PROCEDURE_PURCHASE_HISTORY_DELETE _T("purchase_history_delete")
#define PROCEDURE_PURCHASE_HISTORY_GET _T("purchase_history_get")

#define PROCEDURE_PURCHASE_OPERATION_GET _T("purchase_Operation_get")

enum PurchaseOperationID
{
	PurOpr_Add = 0,
	PurOpr_Edit = 1,
	PurOpr_Del = 2,
	PurOpr_End = 3
};

CString GetPurchaseOperationIDName(PurchaseOperationID operationID);

typedef struct _PurchaseHistory
{
	CString csID;
	CString csUserID;
	CString csUserUID;
	CString csUserName;
	CString	csMedicineID;
	CString csMedicineSN;
	CString csMedicineName;
	CString csOperationID;
	CString csOperationDetail;
	CString csCreateTime;
}PurchaseHistory;

class CPurchaseHistoryDB
{
public:
	CPurchaseHistoryDB();
	~CPurchaseHistoryDB();

	ERRCODE AddPurchaseHistory(LONG lUserID, LONG lMedicineID, PurchaseOperationID operationID, LPTSTR lpOperationDetail);
	ERRCODE GetPurchaseHistories(DWORD dwPageNum, DWORD dwNumPerPage, DWORD &dwTotalPage, DWORD &dwTotalNum, vector<PurchaseHistory*> &vctPurchaseHistories);

private:
	CDatabase m_database;
};
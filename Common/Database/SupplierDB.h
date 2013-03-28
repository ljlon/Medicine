#pragma once
#include "StdHead.h"
#include "Database.h"

#define PROCEDURE_SUPPLIER_GET _T("supplier_get")
#define PROCEDURE_SUPPLIER_SELECT _T("supplier_select")
#define PROCEDURE_SUPPLIER_ADD _T("supplier_add")
#define PROCEDURE_SUPPLIER_UPDATE _T("supplier_update")
#define PROCEDURE_SUPPLIER_CHECKOTHERSEXIST _T("supplier_check_others_exist")
#define PROCEDURE_SUPPLIER_DELETE _T("supplier_delete")
#define PROCEDURE_SUPPLIER_CHECKEXIST _T("supplier_check_exist")

typedef struct _Supplier
{
	CString csID;
	CString csName;
	CString csContact;
	CString csTelephone;
	CString csAddress;
	CString csMedicineCount;
	CString csCreateTime;
	CString csModifyTime;
}Supplier;

class CSupplierDB
{
public:
	CSupplierDB();
	~CSupplierDB();

	ERRCODE GetSupplier(LPTSTR lpSupplierID, Supplier* pSupplier);
	ERRCODE GetSuppliers(DWORD dwPageNum, DWORD dwNumPerPage, DWORD &dwTotalPage, DWORD &dwTotalNum, vector<Supplier*> &vctSuppliers, LPTSTR lpMatchSubString = _T(""));
	ERRCODE AddSupplier(LPTSTR lpSupplierName, LPTSTR lpContact, LPTSTR lpTelephone, LPTSTR lpAddress);
	ERRCODE UpdateSupplier(LPTSTR lpID, LPTSTR lpSupplierName, LPTSTR lpContact, LPTSTR lpTelephone, LPTSTR lpAddress);
	ERRCODE DeleteSupplier(LPTSTR lpID);
	ERRCODE CheckSupplierExist(LPTSTR lpID, LPTSTR lpSupplierName, BOOL& bExist);

protected:
	ERRCODE CheckSupplierNameAvaliable(LPTSTR lpCurrentSupplierID, LPTSTR lpSupplierName, BOOL& bAvaliable);

private:
	CDatabase m_database;
};
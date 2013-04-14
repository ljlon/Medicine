#pragma once
#include "StdHead.h"
#include "Database.h"

#define PROCEDURE_VENDOR_GET _T("vendor_get")
#define PROCEDURE_VENDOR_SELECT _T("vendor_select")
#define PROCEDURE_VENDOR_SELECT_BY_NAME _T("vendor_select_by_name")
#define PROCEDURE_VENDOR_ADD _T("vendor_add")
#define PROCEDURE_VENDOR_UPDATE _T("vendor_update")
#define PROCEDURE_VENDOR_CHECKOTHERSEXIST _T("vendor_check_others_exist")
#define PROCEDURE_VENDOR_DELETE _T("vendor_delete")
#define PROCEDURE_VENDOR_CHECKEXIST _T("vendor_check_exist")

typedef struct _Vendor
{
	CString csID;
	CString csName;
	CString csTelephone;
	CString csAddress;
	CString csMedicineCount;
	CString csCreateTime;
	CString csModifyTime;
}Vendor;

class CVendorDB
{
public:
	CVendorDB();
	~CVendorDB();

	ERRCODE GetVendor(LPTSTR lpID, Vendor* pVendor);
	ERRCODE GetVendorByName(LPTSTR lpName, Vendor* pVendor);
	ERRCODE GetVendors(DWORD dwPageNum, DWORD dwNumPerPage, DWORD &dwTotalPage, DWORD &dwTotalNum, vector<Vendor*> &vctVendors, LPTSTR lpMatchSubString = _T(""));
	ERRCODE AddVendor(Vendor *pVendor);
	ERRCODE UpdateVendor(LPTSTR lpID, LPTSTR lpName, LPTSTR lpTelephone, LPTSTR lpAddress);
	ERRCODE DeleteVendor(LPTSTR lpID);
	ERRCODE CheckVendorExit(LPTSTR lpID, LPTSTR lpName, BOOL& bExist);

protected:
	ERRCODE CheckVendorNameAvaliable(LPTSTR lpCurrentID, LPTSTR lpName, BOOL& bAvaliabel);

private:
	CDatabase m_database;
};
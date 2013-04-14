#pragma once
#include "StdHead.h"
#include "Database.h"

#define PROCEDURE_POS_ADD _T("pos_add")
#define PROCEDURE_POS_UPDATE _T("pos_update")
#define PROCEDURE_POS_GET _T("pos_get")
#define PROCEDURE_POS_SELECT _T("pos_select")
#define PROCEDURE_POS_CHECKEXIST _T("pos_check_exist")
#define PROCEDURE_POS_CHECKEXIST_BYMAC _T("pos_check_exist_by_mac")

typedef struct _POS
{
	CString csID;
	CString csPCID;
	CString csPCMAC;
}POS;

class CPOSDB
{
public:
	CPOSDB();
	~CPOSDB();

	ERRCODE AddPOS(POS *pPOS);
	ERRCODE GetPOSs(DWORD dwPageNum, 
								DWORD dwNumPerPage, 
								DWORD &dwTotalPage, 
								DWORD &dwTotalNum, 
								vector<POS*> &vctPOS);
	ERRCODE GetPOS(LPTSTR lpMAC, POS* pPOS);
	ERRCODE CheckPOSExist(LONG lID, BOOL& bExist);
	ERRCODE CheckPOSExist(LPTSTR lpMAC, BOOL& bExist);
	ERRCODE UpdatePOS(LONG lOldID, POS *pPOS);

protected:


private:
	CDatabase m_database;
};
#pragma once
#include "StdHead.h"
#include "Database.h"

#define PROCEDURE_USER_GET _T("user_get")
#define PROCEDURE_USER_SELECT _T("user_select")
#define PROCEDURE_USER_ADD _T("user_add")
#define PROCEDURE_USER_UPDATE _T("user_update")
#define PROCEDURE_USER_CHECKOTHERSEXIST _T("user_check_others_exist")
#define PROCEDURE_USER_DELETE _T("user_delete")
#define PROCEDURE_USER_CHECKEXIST _T("user_check_exist")
#define PROCEDURE_USER_ROLE_GET _T("user_role_get")

enum EnumUserRole{
	Role_ALL = -1,
	Role_Supper = 0,
	Role_Manager,
	Role_DataEntryClerk,
	Role_Cashier,
	Role_None
};

typedef struct _User
{
	CString csID;
	CString csUID;
	CString csName;
	CString csRole;
	CString csCreateTime;
}User;

typedef struct _UserRole
{
	CString csID;
	CString csName;
}UserRole;

class CUserDB
{
public:
	CUserDB();
	~CUserDB();

	ERRCODE GetUser(LPTSTR lpUID, User* pUser);
	ERRCODE GetUsers(DWORD dwPageNum, DWORD dwNumPerPage, DWORD &dwTotalPage, DWORD &dwTotalNum, vector<User*> &vctUsers, LPTSTR lpMatchSubString = _T(""), EnumUserRole userRole = Role_ALL);
	ERRCODE AddUser(LPTSTR lpUID,  LPTSTR lpPassword, LPTSTR lpName, DWORD dwRole);
	ERRCODE UpdateUser(LPTSTR lpID, LPTSTR lpUID, LPTSTR lpName, DWORD dwRole);
	ERRCODE DeleteUser(LPTSTR lpID);
	ERRCODE CheckUserExit(LPTSTR lpUID, BOOL& bExist);

	ERRCODE GetUserRoles(vector<UserRole*> &vctUserRoles);

protected:

private:
	CDatabase m_database;
};
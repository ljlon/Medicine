#pragma once
#include "UserDB.h"
#include "ManagerDoc.h"

// CUserAddView form view

class CUserAddView : public CFormView
{
	DECLARE_DYNCREATE(CUserAddView)

public:
	CUserAddView();           // protected constructor used by dynamic creation
	virtual ~CUserAddView();

public:
	enum { IDD = IDD_USER_ADD };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	void AdjustLayout();
	void DisplayUserInfo(LPTSTR lpUserUID);
	BOOL BeCancel();

protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonUserAddOk();
	afx_msg void OnBnClickedButtonUserCancel();
	afx_msg void OnEnChangeEditUserID();
	afx_msg void OnEnChangeEditUserName();
	afx_msg void OnCbnSelchangeComboUserRole();

	BOOL AddUser();

	EnumViewType m_viewType;
	BOOL m_bDataChanged;
	User m_user;
	vector<UserRole*> m_vctUserRoles;

};



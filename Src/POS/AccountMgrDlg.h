#pragma once
#include "UserDB.h"

// CAccountMgrView form view

class CAccountMgrDlg : public CDialogEx
{
	DECLARE_DYNCREATE(CAccountMgrDlg)

public:
	CAccountMgrDlg();           // protected constructor used by dynamic creation
	virtual ~CAccountMgrDlg();

public:
	enum { IDD = IDD_ACCOUNT_MANAGE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	void AdjustLayout();
	void DisplayUserInfo(LPTSTR lpUserID);

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnEnChangeEditAccountName();


	BOOL UpdateAccount();

	BOOL m_bDataChanged;
	vector<UserRole*> m_vctUserRoles;
public:
	afx_msg void OnBnClickedButtonModifyName();
	afx_msg void OnBnClickedButtonNewPassword();
};



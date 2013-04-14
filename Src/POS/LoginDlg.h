#pragma once
#include "afxwin.h"
#include "StdHead.h"
#include "resource.h"
#include "UserDB.h"

// CLoginDlg dialog

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoginDlg();

// Dialog Data 
	enum { IDD = IDD_LOGIN };

	void SetWelcomeMsg(LPTSTR lpMsg);
	void SetAllowUserRole(EnumUserRole userRole);
	void AddAllowUserRole(EnumUserRole userRole);

	User m_curUser;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_csTitle;
	CString m_csWelcomeMsg;
	vector<EnumUserRole> m_vctAllowUserRole;
	CEdit m_editUID;
	CEdit m_editPWD;
};

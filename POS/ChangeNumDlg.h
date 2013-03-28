#pragma once
#include "afxwin.h"


// CChangeNum dialog

class CChangeNumDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeNumDlg)

public:
	CChangeNumDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CChangeNumDlg();

// Dialog Data
	enum { IDD = IDD_CHANGE_NUM };

	int m_iRow;
	int m_iNum;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnOK();

public:
	CEdit m_editRow;
	CEdit m_editNum;
	afx_msg void OnEnChangeEditNum();
	afx_msg void OnEnChangeEditRow();
};

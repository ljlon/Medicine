#pragma once
#include "afxwin.h"


// CDeleteOneRowDlg dialog

class CDeleteOneRowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteOneRowDlg)

public:
	CDeleteOneRowDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDeleteOneRowDlg();

// Dialog Data
	enum { IDD = IDD_DELETE_ITEM };

	int m_iRow;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnOK();
	afx_msg void OnEnChangeEditRow();
public:
	CEdit m_editRow;
};

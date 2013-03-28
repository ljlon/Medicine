#pragma once
#include "afxwin.h"

// CCfgPrinterFormatDlg dialog

class CCfgPrintFormatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCfgPrintFormatDlg)

public:
	CCfgPrintFormatDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCfgPrintFormatDlg();

// Dialog Data
	enum { IDD = IDD_CFG_PRINT_FORMAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	void ResizeDlg();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnClose();
public:
	CEdit m_editText;
	CStatic m_staticText;
	afx_msg void OnEnChangeEditFormat();
	afx_msg void OnEnKillfocusEditFormat();
	afx_msg void OnBnClickedButtonPresee();
	CButton m_btnPresee;
	BOOL    m_bDataChange;
};

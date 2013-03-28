#pragma once
#include "afxwin.h"
#include "PrinterManager.h"

// CCfgPrinterDlg dialog

class CCfgPrinterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCfgPrinterDlg)

public:
	CCfgPrinterDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCfgPrinterDlg();

// Dialog Data
	enum { IDD = IDD_CFG_PRINTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	ERRCODE ApplyCfg(Config &config);

	CComboBox m_cmbPrinters;
	vector<PrinterInfo> m_vctAllPrinters;
	int m_iSelPrinterIdx;

protected:
	afx_msg void OnCbnSelchangeComboPrinter();
	afx_msg void OnCbnDropdownComboPrinter();
public:
	afx_msg void OnCbnCloseupComboPrinter();
	afx_msg void OnBnClickedButtonPrintFormat();
};

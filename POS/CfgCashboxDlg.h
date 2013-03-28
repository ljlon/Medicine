#pragma once
#include "afxwin.h"


// CCfgCashboxDlg dialog

class CCfgCashboxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCfgCashboxDlg)

public:
	CCfgCashboxDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCfgCashboxDlg();

// Dialog Data
	enum { IDD = IDD_CFG_CASHBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	ERRCODE ApplyCfg(Config &config);

	CComboBox m_cbCashbox;
	vector<CString> m_vctAllCashbox;
	int m_iSelCashboxIdx;

	afx_msg void OnCbnDropdownComboCashbox();
	afx_msg void OnCbnSelchangeComboCashbox();
	afx_msg void OnCbnCloseupComboCashbox();
};

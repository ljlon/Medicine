#pragma once
#include "Config.h"

// CCfgCustomerDisplayDlg dialog

class CCfgCustomerDisplayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCfgCustomerDisplayDlg)

public:
	CCfgCustomerDisplayDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCfgCustomerDisplayDlg();

// Dialog Data
	enum { IDD = IDD_CFG_CUSTOMER_DISPLAY };

	ERRCODE ApplyCfg(Config &config);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	vector<CString> m_vctAllCustomerDisplay;
	int m_iSelCustomerDisplayIdx;
	CComboBox m_cbCom;
	afx_msg void OnCbnDropdownComboCom();
public:
	afx_msg void OnCbnSelchangeComboCom();
	afx_msg void OnCbnCloseupComboCom();
};

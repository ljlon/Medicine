#pragma once
#include "afxwin.h"
#include "POSConfig.h"

// CCfgGeneralDlg 对话框

class CCfgGeneralDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCfgGeneralDlg)

public:
	CCfgGeneralDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCfgGeneralDlg();

// 对话框数据
	enum { IDD = IDD_CFG_GENERAL };

	ERRCODE ApplyCfg(POSConfig &config);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editCompanyName;
	CEdit m_editPOSID;
};

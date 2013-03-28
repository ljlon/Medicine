#pragma once
#include "afxwin.h"


// CCfgDatabaseDlg 对话框

class CCfgDatabaseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCfgDatabaseDlg)

public:
	CCfgDatabaseDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCfgDatabaseDlg();

// 对话框数据
	enum { IDD = IDD_CFG_DATABASE };


	ERRCODE ApplyCfg(Config &config);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cbHost;
	CEdit m_editPort;
	CEdit m_editDBName;
	CEdit m_editUID;
	CEdit m_editPWD;
};

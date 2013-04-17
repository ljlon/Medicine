#pragma once
#include "MgrConfig.h"
#include "afxfontcombobox.h"
#include "afxwin.h"

// CCfgGeneralDlg 对话框

class CCfgGeneralDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCfgGeneralDlg)

public:
	CCfgGeneralDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCfgGeneralDlg();

// 对话框数据
	enum { IDD = IDD_CFG_GENERAL };

	ERRCODE ApplyCfg(MgrConfig &config);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editFontName;
	CEdit m_editFontHeight;
};

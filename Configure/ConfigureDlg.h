
// ConfigureDlg.h : 头文件
//
#pragma once

#include "CfgDatabaseDlg.h"
#include "afxwin.h"

// CConfigureDlg 对话框
class CConfigureDlg : public CDialogEx
{
// 构造
public:
	CConfigureDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CConfigureDlg();

// 对话框数据
	enum { IDD = IDD_CONFIGURE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	//HICON m_hIcon;

	CCfgDatabaseDlg *m_pCfgDatabaseDlg;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_staticView;
	afx_msg void OnBnClickedOk();
};

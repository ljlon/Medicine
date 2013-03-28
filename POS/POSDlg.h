
// POSDlg.h : 头文件
//

#pragma once
#include "RetailListDlg.h"

// CPOSDlg 对话框
class CPOSDlg : public CDialogEx
{
// 构造
public:
	CPOSDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_POS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	CRetailListDlg m_retailListDlg;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCfg();
	afx_msg void OnBnClickedBtnSale();
	afx_msg void OnBnClickedBtnHelp();
	afx_msg void OnBnClickedBtnHistory();
	afx_msg void OnBnClickedBtnAccount();
};

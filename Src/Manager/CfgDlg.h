#pragma once
#include "CfgGeneralDlg.h"
#include <map>

enum EnumCfgItem
{
	CfgItem_Begin = -1,
	CfgItem_General = 0,
	CfgItem_End
};

// CCfgDlg 对话框

class CCfgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCfgDlg)

public:
	CCfgDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCfgDlg();

// 对话框数据
	enum { IDD = IDD_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
	void ShowRightPanel(EnumCfgItem cftItem, int nCmdShow, CRect *pRect);

	DECLARE_MESSAGE_MAP()

	CTreeCtrl m_treeItem;
	CImageList m_treeItemIcons;
	CStatic m_staticDetail;
	map<HTREEITEM, EnumCfgItem> m_mapTreeItem;
	EnumCfgItem m_activeCftItem;
	CCfgGeneralDlg *m_pCfgGeneralDlg;

	afx_msg void OnBnClickedOk();
	afx_msg void OnTvnSelchangedTreeItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
};

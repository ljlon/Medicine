#pragma once
#include <map>
#include "afxcmn.h"
#include "afxwin.h"
#include "CfgGeneralDlg.h"
#include "CfgPrinterDlg.h"
#include "CfgCashboxDlg.h"
#include "CfgCustomerDisplayDlg.h"

using namespace std;

enum EnumCfgItem
{
	CfgItem_Begin = -1,
	CfgItem_General = 0,
	CfgItem_Device,
	CfgItem_Printer,
	CfgItem_Cashbox,
	CfgItem_Customer_Display,
	CfgItem_End
};

// CCfgDlg dialog

class CCfgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCfgDlg)

public:
	CCfgDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCfgDlg();

// Dialog Data
	enum { IDD = IDD_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
	void ShowRightPanel(EnumCfgItem cftItem, int nCmdShow, CRect *pRect);

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_treeItem;
	CImageList m_treeItemIcons;
	CStatic m_staticDetail;

	map<HTREEITEM, EnumCfgItem> m_mapTreeItem;
	EnumCfgItem m_activeCftItem;
	CCfgGeneralDlg *m_pCfgGeneralDlg;
	CCfgPrinterDlg *m_pCfgPrinterDlg;
	CCfgCashboxDlg *m_pCfgCashboxDlg;
	CCfgCustomerDisplayDlg *m_pCfgCustomerDisplayDlg;

	afx_msg void OnBnClickedOk();
	afx_msg void OnTvnSelchangedTreeItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
};

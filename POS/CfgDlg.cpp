// CfgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "POS.h"
#include "CfgDlg.h"
#include "afxdialogex.h"

TCHAR *g_pszTreeItemName[] = 
{
	_T("常规"),
	_T("设备"),
	_T("打印机"),
	_T("钱箱"),
	_T("顾客显示屏")
};

LPTSTR GetTreeItemName(EnumCfgItem cftItem)
{
	if (cftItem <= CfgItem_Begin || cftItem >= CfgItem_End)
	{
		return NULL;
	}

	return g_pszTreeItemName[cftItem];
}

// CCfgDlg dialog

IMPLEMENT_DYNAMIC(CCfgDlg, CDialogEx)

CCfgDlg::CCfgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCfgDlg::IDD, pParent)
{
	m_activeCftItem = CfgItem_Begin;
	m_pCfgGeneralDlg = NULL;
	m_pCfgPrinterDlg = NULL;
	m_pCfgCashboxDlg = NULL;
	m_pCfgCustomerDisplayDlg = NULL;
}

CCfgDlg::~CCfgDlg()
{
	m_mapTreeItem.clear();

	if (m_pCfgGeneralDlg != NULL)
	{
		delete m_pCfgGeneralDlg;
		m_pCfgGeneralDlg = NULL;
	}

	if (m_pCfgPrinterDlg != NULL)
	{
		delete m_pCfgPrinterDlg;
		m_pCfgPrinterDlg = NULL;
	}

	if (m_pCfgCashboxDlg != NULL)
	{
		delete m_pCfgCashboxDlg;
		m_pCfgCashboxDlg = NULL;
	}

	if (m_pCfgCustomerDisplayDlg != NULL)
	{
		delete m_pCfgCustomerDisplayDlg;
		m_pCfgCustomerDisplayDlg = NULL;
	}
}

void CCfgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_ITEM, m_treeItem);
	DDX_Control(pDX, IDC_STATIC_DETAIL, m_staticDetail);
}


BEGIN_MESSAGE_MAP(CCfgDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDOK, &CCfgDlg::OnBnClickedOk)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_ITEM, &CCfgDlg::OnTvnSelchangedTreeItem)
	ON_BN_CLICKED(IDCANCEL, &CCfgDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCfgDlg message handlers
BOOL CCfgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_treeItemIcons.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_treeItem.SetImageList(&m_treeItemIcons, TVSIL_NORMAL);

	m_mapTreeItem.clear();
	//General
	EnumCfgItem cftItem = CfgItem_General;
	HTREEITEM hParentItem = m_treeItem.InsertItem(GetTreeItemName(cftItem), 0, 0);
	m_mapTreeItem.insert(map<HTREEITEM, EnumCfgItem>::value_type(hParentItem, cftItem));
	m_treeItem.Expand(hParentItem, TVE_EXPAND);

	//Device
	cftItem = CfgItem_Device;
	hParentItem = m_treeItem.InsertItem(GetTreeItemName(cftItem), 0, 0);
	m_mapTreeItem.insert(map<HTREEITEM, EnumCfgItem>::value_type(hParentItem, cftItem));

	cftItem = CfgItem_Printer;
	HTREEITEM hItem = m_treeItem.InsertItem(GetTreeItemName(cftItem), 2, 2, hParentItem);
	m_mapTreeItem.insert(map<HTREEITEM, EnumCfgItem>::value_type(hItem, cftItem));

	cftItem = CfgItem_Cashbox;
	hItem = m_treeItem.InsertItem(GetTreeItemName(cftItem), 2, 2, hParentItem);
	m_mapTreeItem.insert(map<HTREEITEM, EnumCfgItem>::value_type(hItem, cftItem));

	cftItem = CfgItem_Customer_Display;
	hItem = m_treeItem.InsertItem(GetTreeItemName(cftItem), 2, 2, hParentItem);
	m_mapTreeItem.insert(map<HTREEITEM, EnumCfgItem>::value_type(hItem, cftItem));

	m_treeItem.Expand(hParentItem, TVE_EXPAND);

	m_pCfgGeneralDlg = new CCfgGeneralDlg;
	m_pCfgGeneralDlg->Create(CCfgGeneralDlg::IDD, this);

	m_pCfgPrinterDlg = new CCfgPrinterDlg;
	m_pCfgPrinterDlg->Create(CCfgPrinterDlg::IDD, this);

	m_pCfgCashboxDlg = new CCfgCashboxDlg;
	m_pCfgCashboxDlg->Create(CCfgCashboxDlg::IDD, this);

	m_pCfgCustomerDisplayDlg = new CCfgCustomerDisplayDlg;
	m_pCfgCustomerDisplayDlg->Create(CCfgCustomerDisplayDlg::IDD, this);

	return TRUE;
}

void CCfgDlg::OnPaint()
{
	CPaintDC dc(this);

	if (m_activeCftItem <= CfgItem_Begin || m_activeCftItem >= CfgItem_End)
	{
		return;
	}

	CRect rect;
	m_staticDetail.GetWindowRect(&rect);
	ScreenToClient(&rect);

	ShowRightPanel(m_activeCftItem, SW_SHOW, &rect);
}

void CCfgDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	OnPaint();
}

void CCfgDlg::ShowRightPanel(EnumCfgItem cftItem, int nCmdShow, CRect *pRect)
{
	if (cftItem == CfgItem_General && m_pCfgGeneralDlg != NULL)
	{
		if (pRect != NULL)
		{
			m_pCfgGeneralDlg->MoveWindow(pRect);
		}
		m_pCfgGeneralDlg->ShowWindow(nCmdShow);
	}
	else if (cftItem == CfgItem_Printer && m_pCfgPrinterDlg != NULL)
	{
		if (pRect != NULL)
		{
			m_pCfgPrinterDlg->MoveWindow(pRect);
		}
		m_pCfgPrinterDlg->ShowWindow(nCmdShow);
	}
	else 	if (cftItem == CfgItem_Cashbox && m_pCfgCashboxDlg != NULL)
	{
		if (pRect != NULL)
		{
			m_pCfgCashboxDlg->MoveWindow(pRect);
		}
		m_pCfgCashboxDlg->ShowWindow(nCmdShow);
	}
	else 	if (cftItem == CfgItem_Customer_Display && m_pCfgCustomerDisplayDlg != NULL)
	{
		if (pRect != NULL)
		{
			m_pCfgCustomerDisplayDlg->MoveWindow(pRect);
		}
		m_pCfgCustomerDisplayDlg->ShowWindow(nCmdShow);
	}
}

void CCfgDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	ERRCODE errRet = err_OK;

	if (m_pCfgGeneralDlg != NULL)
	{
		errRet = m_pCfgGeneralDlg->ApplyCfg(g_config);
		if (errRet != err_OK)
		{
			//MessageBox(_T("保存常规配置错误"), _T(""), MB_ICONERROR);
			return;
		}
	}

	if (m_pCfgPrinterDlg != NULL)
	{
		errRet = m_pCfgPrinterDlg->ApplyCfg(g_config);
		if (errRet != err_OK)
		{
			//MessageBox(_T("保存打印机设置错误"), _T(""), MB_ICONERROR);
			return;
		}
	}

	if (m_pCfgCashboxDlg != NULL)
	{
		errRet = m_pCfgCashboxDlg->ApplyCfg(g_config);
		if (errRet != err_OK)
		{
			//MessageBox(_T("保存钱箱设置错误"), _T(""), MB_ICONERROR);
			return;
		}
	}

	if (m_pCfgCustomerDisplayDlg != NULL)
	{
		errRet = m_pCfgCustomerDisplayDlg->ApplyCfg(g_config);
		if (errRet != err_OK)
		{
			//MessageBox(_T("保存顾客显示屏设置错误"), _T(""), MB_ICONERROR);
			return;
		}
	}

	errRet = g_config.Save();
	if (errRet != err_OK)
	{
		MessageBox(_T("保存设置错误"), _T(""), MB_ICONERROR);
		return;
	}

	CDialogEx::OnOK();
}


void CCfgDlg::OnTvnSelchangedTreeItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//m_treeItem.SetCheck(pNMTreeView->itemNew.hItem, TRUE);

	map<HTREEITEM, EnumCfgItem>::iterator it = m_mapTreeItem.find(pNMTreeView->itemNew.hItem);
	if (it != m_mapTreeItem.end())
	{
		ShowRightPanel(m_activeCftItem, SW_HIDE, NULL);

		m_activeCftItem = it->second;
		OnPaint();
	}
}

void CCfgDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here

	ERRCODE errRet = g_config.Load();
	if (errRet != err_OK)
	{
		MessageBox(_T("取消设置错误"), _T(""), MB_ICONERROR);
		return;
	}

	CDialogEx::OnCancel();
}

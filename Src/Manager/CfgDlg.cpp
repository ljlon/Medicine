// CfgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "CfgDlg.h"
#include "afxdialogex.h"

TCHAR *g_pszTreeItemName[] = 
{
	_T("常规"),
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
}

CCfgDlg::~CCfgDlg()
{
	m_mapTreeItem.clear();

	if (m_pCfgGeneralDlg != NULL)
	{
		delete m_pCfgGeneralDlg;
		m_pCfgGeneralDlg = NULL;
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

	CFont *pFont = g_theme.GetFont();
	if (pFont != NULL)
	{
		SetFont(pFont);
		CWnd *pw = GetWindow(GW_CHILD);
		while(pw != NULL)
		{
			pw->SetFont(pFont);
			pw = pw->GetWindow(GW_HWNDNEXT);
		};
	}

	m_treeItemIcons.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_treeItem.SetImageList(&m_treeItemIcons, TVSIL_NORMAL);

	m_mapTreeItem.clear();
	//General
	EnumCfgItem cftItem = CfgItem_General;
	HTREEITEM hParentItem = m_treeItem.InsertItem(GetTreeItemName(cftItem), 0, 0);
	m_mapTreeItem.insert(map<HTREEITEM, EnumCfgItem>::value_type(hParentItem, cftItem));
	m_treeItem.Expand(hParentItem, TVE_EXPAND);

	m_pCfgGeneralDlg = new CCfgGeneralDlg;
	m_pCfgGeneralDlg->Create(CCfgGeneralDlg::IDD, this);

	m_treeItem.SelectItem(hParentItem);
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
}

void CCfgDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	ERRCODE errRet = err_OK;

	if (m_pCfgGeneralDlg != NULL)
	{
		errRet = m_pCfgGeneralDlg->ApplyCfg(g_MgrCfg);
		if (errRet != err_OK)
		{
			//MessageBox(_T("保存常规配置错误"), _T(""), MB_ICONERROR);
			return;
		}
	}

	errRet = g_MgrCfg.Save();
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
	ERRCODE errRet = g_MgrCfg.Load();
	if (errRet)
	{
		MessageBox(_T("取消设置错误"), _T(""), MB_ICONERROR);
		return;
	}

	CDialogEx::OnCancel();
}

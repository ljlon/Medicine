// PurchaseMgrView.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "PurchaseMgrView.h"
#include "MainFrm.h"

// CPurchaseMgrView

IMPLEMENT_DYNCREATE(CPurchaseMgrView, CFormView)

CPurchaseMgrView::CPurchaseMgrView()
	: CFormView(CPurchaseMgrView::IDD)
{

}

CPurchaseMgrView::~CPurchaseMgrView()
{
}

void CPurchaseMgrView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPurchaseMgrView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CPurchaseMgrView::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_LIST, &CPurchaseMgrView::OnBnClickedButtonList)
	ON_BN_CLICKED(IDC_BUTTON_HISTORY, &CPurchaseMgrView::OnBnClickedButtonHistory)
END_MESSAGE_MAP()

void CPurchaseMgrView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CString csMsg;
	csMsg.Format("%s-%s", APP_NAME, APP_MANAGER);
	AfxGetApp()->GetMainWnd()->SetWindowText(csMsg);

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
}


// CVendorMgrView diagnostics

#ifdef _DEBUG
void CPurchaseMgrView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPurchaseMgrView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CPurchaseMgrView message handlers
void CPurchaseMgrView::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_PURCHASE_ADD;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}


void CPurchaseMgrView::OnBnClickedButtonList()
{
	// TODO: Add your control notification handler code here

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_PURCHASE_LIST;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}


void CPurchaseMgrView::OnBnClickedButtonHistory()
{
	// TODO: Add your control notification handler code here

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	//TreeMenuID leftPanelID = TREE_PURCHASE_HISTORY;
	//pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}
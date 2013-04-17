// BasicMgrView.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "BasicMgrView.h"
#include "MainFrm.h"

// CBasicMgrView

IMPLEMENT_DYNCREATE(CBasicMgrView, CFormView)

CBasicMgrView::CBasicMgrView()
	: CFormView(CBasicMgrView::IDD)
{

}

CBasicMgrView::~CBasicMgrView()
{
}

void CBasicMgrView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBasicMgrView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_SUPPLIER, &CBasicMgrView::OnBnClickedButtonSupplier)
	ON_BN_CLICKED(IDC_BUTTON_VENDOR, &CBasicMgrView::OnBnClickedButtonVendor)
	ON_BN_CLICKED(IDC_BUTTON_MEDICINE, &CBasicMgrView::OnBnClickedButtonMedicine)
END_MESSAGE_MAP()

void CBasicMgrView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

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

	CString csMsg;
	csMsg.Format("%s-%s", APP_NAME, APP_MANAGER);
	AfxGetApp()->GetMainWnd()->SetWindowText(csMsg);
}

// CBasicMgrView diagnostics

#ifdef _DEBUG
void CBasicMgrView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBasicMgrView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBasicMgrView message handlers


void CBasicMgrView::OnBnClickedButtonSupplier()
{
	// TODO: Add your control notification handler code here

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_SUPPLIER_ID;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}


void CBasicMgrView::OnBnClickedButtonVendor()
{
	// TODO: Add your control notification handler code here

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_VENDOR_ID;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}


void CBasicMgrView::OnBnClickedButtonMedicine()
{
	// TODO: Add your control notification handler code here

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_MEDICINE_ID;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}

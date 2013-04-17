
#include "stdafx.h"
#include "mainfrm.h"
#include "MenuView.h"
#include "Resource.h"
#include "Manager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenuView

IMPLEMENT_DYNCREATE(CMenuView, CView)

BEGIN_MESSAGE_MAP(CMenuView, CView)
	//{{AFX_MSG_MAP(CTextView)
	ON_REGISTERED_MESSAGE(WM_MENUVIEW, OnMenuView)
	ON_WM_MOUSEACTIVATE()
	//ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_CLICK, IDC_TREE_MENU, OnNMClickMenuTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextView construction/destruction

CMenuView::CMenuView()
{
	m_curMenuID = TREE_ROOT_ID;
	m_preMenuID = TREE_ROOT_ID;
}

CMenuView::~CMenuView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTextView drawing

void CMenuView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CString csMsg;
	csMsg.Format("%s-%s", APP_NAME, APP_MANAGER);
	AfxGetApp()->GetMainWnd()->SetWindowText(csMsg);

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_SHOWSELALWAYS | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndMenuView.Create(dwViewStyle, rectDummy, this, IDC_TREE_MENU))
	{
		TRACE0("未能创建文件视图\n");
		return;      // 未能创建
	}

	// 加载视图图像:
	m_MenuViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndMenuView.SetImageList(&m_MenuViewImages, TVSIL_NORMAL);

	OnChangeVisualStyle();

	// 填入一些静态树视图数据(此处只需填入虚拟代码，而不是复杂的数据)
	FillMenuView();
	AdjustLayout();

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

 LRESULT CMenuView::OnMenuView(WPARAM wParam, LPARAM lParam)
 {
	 switch (wParam)
	 {
	 case WM_MENUVIEW_SETITEM:
		 if (lParam == NULL)
		 {
			 break;
		 }
		 SetMenuItem((TreeMenuID)lParam);
		 break;
	 case WM_MENUVIEW_SETPREITEM:
		 SetMenuItem(m_preMenuID);
		 break;
	 }
	 return 0;
 }


 BOOL CMenuView::PreTranslateMessage(MSG* pMsg) 
 {
	 if(WM_KEYDOWN == pMsg->message)
	 {
		 
	 }

	 return CView::PreTranslateMessage(pMsg);
 }


 void CMenuView::SetMenuItem(TreeMenuID menuID)
 {
	 if (GetSafeHwnd() == NULL)
	 {
		 return;
	 }

	 HTREEITEM hItem = m_wndMenuView.GetRootItem();    
	 while(hItem)
	 {
		 if (m_wndMenuView.GetItemText(hItem) == GetMenuName(menuID))
		 {
			 m_wndMenuView.SelectItem(hItem);
			 if (menuID != m_curMenuID)
			 {
				 m_preMenuID = m_curMenuID;
			     m_curMenuID =  menuID;
			 }
			 break;
		 }

		 hItem=m_wndMenuView.GetNextItem(hItem, TVGN_NEXTVISIBLE);
	 }
 }


void CMenuView::OnDraw(CDC* pDC)
{
	CView::OnDraw(pDC);
}


int CMenuView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// side-step CView's implementation since we don't want to activate
	//  this view
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CMenuView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CMenuView::FillMenuView()
{
	CManagerDoc* pDoc = GetDocument();
	if (pDoc == NULL)
	{
		return;
	}

	TreeStruct *pMenuTreeInfo = &(pDoc->m_menuTree);
	HTREEITEM hRootItem = m_wndMenuView.InsertItem(pMenuTreeInfo->csNodeName, 0, 0);
	for (unsigned int i = 0; i < pMenuTreeInfo->vctChildTree.size(); i++)
	{
		HTREEITEM hItem = m_wndMenuView.InsertItem(pMenuTreeInfo->vctChildTree[i]->csNodeName, 0, 0, hRootItem);
		for (unsigned int j = 0; j < pMenuTreeInfo->vctChildTree[i]->vctChildTree.size(); j++)
		{
			HTREEITEM hSubItem = m_wndMenuView.InsertItem(pMenuTreeInfo->vctChildTree[i]->vctChildTree[j]->csNodeName, 2, 2, hItem);
		}
		m_wndMenuView.Expand(hItem, TVE_EXPAND);
	}
	m_wndMenuView.Expand(hRootItem, TVE_EXPAND);
}

void CMenuView::OnNMClickMenuTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	ASSERT_VALID(&m_wndMenuView);

	CString csMsg;
	DWORD dwPos = GetMessagePos();            
	CPoint point( LOWORD(dwPos), HIWORD(dwPos));   

	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项:
		CPoint ptTree = point;
		m_wndMenuView.ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = m_wndMenuView.HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			csMsg = m_wndMenuView.GetItemText(hTreeItem);
			m_wndMenuView.SelectItem(hTreeItem);

			CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
			if (pMain == NULL)
			{
				return;
			}
			TreeMenuID leftPanelID = GetMenuID(csMsg.GetBuffer());

			if (leftPanelID != m_curMenuID)
			{
				m_preMenuID = m_curMenuID;
				m_curMenuID =  leftPanelID;
			}

			pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
		}
	}

	*pResult = 0;
}


void CMenuView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	m_wndMenuView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + 1, rectClient.Width() - 2, rectClient.Height() - 2,  SWP_NOZORDER); // SWP_NOACTIVATE
}

void CMenuView::OnChangeVisualStyle()
{

	m_MenuViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("无法加载位图: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_MenuViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_MenuViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndMenuView.SetImageList(&m_MenuViewImages, TVSIL_NORMAL);
}

CManagerDoc* CMenuView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CManagerDoc)));
	return (CManagerDoc*)m_pDocument;
}

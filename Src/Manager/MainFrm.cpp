
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "Manager.h"
#include "MainFrm.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_REGISTERED_MESSAGE(WM_MAINFRM, &CMainFrame::OnMainFrm)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_PAINT()
	ON_WM_SETTINGCHANGE()
	ON_MESSAGE(MY_WM_NOTIFYICON, &CMainFrame::OnNotifyIcon)    
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_WINDOWS_7);
	m_rightViewID = TREE_ROOT_ID;
	m_bAuthorized = TRUE;
}


CMainFrame::~CMainFrame()
{
	m_listPreRightViewID.clear();
}


LRESULT CMainFrame::OnMainFrm(WPARAM wParam, LPARAM lParam)
{
	list<TreeMenuID>::iterator listPreRightViewIDIt;
	switch(wParam)
	{
	case WM_MAINFRM_SETRIGHTPANE:
		if (SetLeftViewMenu((TreeMenuID)lParam) != TRUE)
		{
			break;
		}
		if (ShowRightView((TreeMenuID)lParam) != TRUE)
		{
			break;
		}
		break;

	case WM_MAINFRM_SETPRERIGHTPANE:
		if (m_listPreRightViewID.size())
		{
			listPreRightViewIDIt = m_listPreRightViewID.end();
			listPreRightViewIDIt--;	
			TreeMenuID preRightViewID = *listPreRightViewIDIt;
			m_listPreRightViewID.erase(listPreRightViewIDIt);
			if (ShowRightView(preRightViewID, FALSE))
			{
				break;
			}
		}
		break;
	default:
		break;
	}
	return 0;
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	/*
	m_ntIcon.cbSize = sizeof(NOTIFYICONDATA);						//该结构体变量的大小
	m_ntIcon.hIcon = AfxGetApp()->LoadIconA(IDR_MAINFRAME);			//图标，通过资源ID得到
	m_ntIcon.hWnd = this->m_hWnd;									//接收托盘图标通知消息的窗口句柄								
	sprintf_s(m_ntIcon.szTip, "%s-%s", APP_NAME, APP_MANAGER);		//鼠标设上面时显示的提示            
	m_ntIcon.uCallbackMessage = MY_WM_NOTIFYICON;					//应用程序定义的消息ID号
	m_ntIcon.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;					//图标的属性：设置成员uCallbackMessage、hIcon、szTip有效
	::Shell_NotifyIconA(NIM_ADD, &m_ntIcon);						//在系统通知区域增加这个图标
	*/

	return 0;
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	m_wndSplitter.CreateStatic(this, 1, 2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMenuView), CSize(200, 600), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CRootView), CSize(0, 0), pContext);

	return TRUE;
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

/*
	int cxScreen = ::GetSystemMetrics(SM_CXSCREEN);//获得屏幕宽
	int cyScreen = ::GetSystemMetrics(SM_CYSCREEN);// 获得屏幕高
	cs.cx = cxScreen; 
	cs.cy = cyScreen;*/

	return TRUE;
}


void CMainFrame::OnDestroy()
{
	::Shell_NotifyIcon(NIM_DELETE, &m_ntIcon);
	CFrameWndEx::OnDestroy();
}


BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	if(WM_KEYDOWN == pMsg->message)
	{
		int nState = GetKeyState(VK_CONTROL);
		if(nState < 0)
		{	
			int  ch = (int) pMsg->wParam ;
			if('x' == ch || 'X' == ch)	
			{
				::SendMessage(GetFocus()->GetSafeHwnd(),WM_CUT,ID_EDIT_CUT,0);
				return TRUE;
			}
			if('c' == ch || 'C' == ch)	
			{
				::SendMessage(GetFocus()->GetSafeHwnd(),WM_COPY,ID_EDIT_CUT,0);
				return TRUE;
			}
			if('v' == ch || 'V' == ch)	
			{
				::SendMessage(GetFocus()->GetSafeHwnd(),WM_PASTE,ID_EDIT_CUT,0);
				return TRUE;
			}
		}	
	}

	return CFrameWndEx::PreTranslateMessage(pMsg);
}


LRESULT CMainFrame::OnNotifyIcon(WPARAM wparam, LPARAM lparam)
{
	if(lparam == WM_LBUTTONDOWN)
	{
		if (AfxGetMainWnd()->IsWindowVisible())
		{
			OnClose();
		}
		else
		{
			AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED);
		}
	}
	else if(lparam == WM_RBUTTONDOWN)
	{
		if (AfxGetMainWnd()->IsWindowVisible())
		{
			OnClose();
		}
		else
		{
			AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED);
		}
	}
	return 0;
}


void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFrameWndEx::OnShowWindow(bShow, nStatus);
}


void CMainFrame::OnPaint()
{
	CFrameWndEx::OnPaint();
}


BOOL CMainFrame::SetLeftViewMenu(TreeMenuID id)
{
	if (m_bAuthorized != TRUE && id != TREE_ROOT_ID)
	{
		if (m_loginDlg.DoModal() != IDOK)
		{
			return FALSE;
		}
		theApp.m_curUser = m_loginDlg.m_curUser;
		m_bAuthorized = TRUE;
	}

	int iRole = atoi(theApp.m_curUser.csRole);
	if (iRole != Role_Supper && iRole != Role_Manager)
	{
		if (id == TREE_USER_ID || id == TREE_USER_ADD)
		{
			return FALSE;
		}
	}

	CMenuView *pMenuView = (CMenuView*)m_wndSplitter.GetPane(0,0);
	pMenuView->PostMessage(WM_MENUVIEW, WM_MENUVIEW_SETITEM, (LPARAM)id);

	return TRUE;
}

BOOL CMainFrame::ShowRightView(TreeMenuID id,  BOOL bRememberPreID)
{
	if (m_bAuthorized != TRUE && id != TREE_ROOT_ID)
	{
		return FALSE;
	}

	if (m_rightViewID == id)
	{
		return TRUE;
	}

	if (BeRightViewQuit() != TRUE)
	{
		CMenuView *pMenuView = (CMenuView*)m_wndSplitter.GetPane(0,0);
		pMenuView->PostMessage(WM_MENUVIEW, WM_MENUVIEW_SETPREITEM);
		return FALSE;
	}

	TreeMenuID preRightViewID = m_rightViewID;
	m_rightViewID = id;

	CView* pView = (CView*)m_wndSplitter.GetPane(0,1);
	CRect rcRight,rcFrame;     
	pView->GetClientRect(&rcRight);     
	GetClientRect(&rcFrame);

	if (m_rightViewID == TREE_ROOT_ID)
	{
		m_listPreRightViewID.clear();
		if (!pView->IsKindOf(RUNTIME_CLASS(CRootView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CRootView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}
	}
	else if (m_rightViewID == TREE_BASIC_ID)
	{
		m_listPreRightViewID.clear();
		if (!pView->IsKindOf(RUNTIME_CLASS(CBasicMgrView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CBasicMgrView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}        
	}         
	else if (m_rightViewID == TREE_SUPPLIER_ID)
	{
		m_listPreRightViewID.clear();
		if (!pView->IsKindOf(RUNTIME_CLASS(CSupplierMgrView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CSupplierMgrView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}        
	}
	else if (m_rightViewID == TREE_SUPPLIER_ADD)
	{
		if (bRememberPreID == TRUE)
		{
			m_listPreRightViewID.push_back(preRightViewID);
		}
		if (!pView->IsKindOf(RUNTIME_CLASS(CSupplierAddView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CSupplierAddView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}        
	}
	else if (m_rightViewID == TREE_VENDOR_ID)
	{
		m_listPreRightViewID.clear();
		if (!pView->IsKindOf(RUNTIME_CLASS(CVendorMgrView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CVendorMgrView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}        
	}
	else if (m_rightViewID == TREE_VENDOR_ADD)
	{
		if (bRememberPreID == TRUE)
		{
			m_listPreRightViewID.push_back(preRightViewID);
		}
		if (!pView->IsKindOf(RUNTIME_CLASS(CVendorAddView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CVendorAddView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}        
	}
	else if (m_rightViewID == TREE_MEDICINE_ID)
	{
		m_listPreRightViewID.clear();
		if (!pView->IsKindOf(RUNTIME_CLASS(CMedicineMgrView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CMedicineMgrView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}        
	}
	else if (m_rightViewID == TREE_MEDICINE_ADD)
	{
		if (bRememberPreID == TRUE)
		{
			m_listPreRightViewID.push_back(preRightViewID);
		}
		if (!pView->IsKindOf(RUNTIME_CLASS(CMedicineAddView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CMedicineAddView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}        
	}
	else if (m_rightViewID == TREE_PURCHASE_ID)
	{
		m_listPreRightViewID.clear();
		if (!pView->IsKindOf(RUNTIME_CLASS(CPurchaseMgrView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CPurchaseMgrView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}        
	}
	else if (m_rightViewID == TREE_PURCHASE_ADD)
	{
		if (bRememberPreID == TRUE)
		{
			m_listPreRightViewID.push_back(preRightViewID);
		}
		if (!pView->IsKindOf(RUNTIME_CLASS(CPurchaseAddView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CPurchaseAddView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}        
	}
	else if (m_rightViewID == TREE_PURCHASE_LIST)
	{
		m_listPreRightViewID.clear();
		if (!pView->IsKindOf(RUNTIME_CLASS(CPurchaseListView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CPurchaseListView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}        
	}
	else if (m_rightViewID == TREE_RETAIL_ID)
	{
		m_listPreRightViewID.clear();
		if (!pView->IsKindOf(RUNTIME_CLASS(CRetailMgrView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CRetailMgrView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}        
	}
	else if (m_rightViewID == TREE_STORE_ID)
	{
		m_listPreRightViewID.clear();
		if (!pView->IsKindOf(RUNTIME_CLASS(CStoreMgrView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CStoreMgrView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}        
	}
	else if (m_rightViewID == TREE_STORE_EDIT_ID)
	{
		if (bRememberPreID == TRUE)
		{
			m_listPreRightViewID.push_back(preRightViewID);
		}
		if (!pView->IsKindOf(RUNTIME_CLASS(CStoreEditView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CStoreEditView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}        
	}
	else if (m_rightViewID == TREE_USER_ID)
	{
		m_listPreRightViewID.clear();
		int iRole = atoi(theApp.m_curUser.csRole);
		if (iRole != Role_Supper && iRole != Role_Manager)
		{
			MessageBox(_T("对不起，您没有足够权限！"), "", MB_ICONWARNING);
			return FALSE;
		}
		if (!pView->IsKindOf(RUNTIME_CLASS(CUserMgrView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CUserMgrView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}        
	}
	else if (m_rightViewID == TREE_USER_ADD)
	{
		if (bRememberPreID == TRUE)
		{
			m_listPreRightViewID.push_back(preRightViewID);
		}
		int iRole = atoi(theApp.m_curUser.csRole);
		if (iRole != Role_Supper && iRole != Role_Manager)
		{
			MessageBox(_T("对不起，您没有足够权限！"), "", MB_ICONWARNING);
			return FALSE;
		}
		if (!pView->IsKindOf(RUNTIME_CLASS(CUserAddView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CUserAddView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}        
	}
	else if (m_rightViewID == TREE_ACCOUNT_ID)
	{
		m_listPreRightViewID.clear();
		if (!pView->IsKindOf(RUNTIME_CLASS(CAccountMgrView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CAccountMgrView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}        
	}
	else if (m_rightViewID == TREE_ACCOUNT_NEWPWS)
	{
		if (bRememberPreID == TRUE)
		{
			m_listPreRightViewID.push_back(preRightViewID);
		}
		if (!pView->IsKindOf(RUNTIME_CLASS(CPasswordMgrView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CPasswordMgrView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}        
	}
	else if (m_rightViewID == TREE_BACKUP_ID)
	{
		m_listPreRightViewID.clear();
		if (!pView->IsKindOf(RUNTIME_CLASS(CBackupMgrView)))
		{
			m_wndSplitter.DeleteView(0, 1);
			m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CBackupMgrView), CSize(0, 0), NULL);
			m_wndSplitter.RecalcLayout();
		}    
	}

	return TRUE;
}

BOOL CMainFrame::BeRightViewQuit()
{
	CView* pView = (CView*)m_wndSplitter.GetPane(0,1);
	if (pView->IsKindOf(RUNTIME_CLASS(CMedicineAddView)))
	{
		if (((CMedicineAddView*)pView)->BeCancel() != TRUE)
		{
			return FALSE;
		}
	}
	else if (pView->IsKindOf(RUNTIME_CLASS(CVendorAddView)))
	{
		if (((CVendorAddView*)pView)->BeCancel() != TRUE)
		{
			return FALSE;
		}
	}
	else if (pView->IsKindOf(RUNTIME_CLASS(CSupplierAddView)))
	{
		if (((CSupplierAddView*)pView)->BeCancel() != TRUE)
		{
			return FALSE;
		}
	}
	else if (pView->IsKindOf(RUNTIME_CLASS(CPurchaseAddView)))
	{
		if (((CPurchaseAddView*)pView)->BeCancel() != TRUE)
		{
			return FALSE;
		}
	}
	else if (pView->IsKindOf(RUNTIME_CLASS(CStoreEditView)))
	{
		if (((CStoreEditView*)pView)->BeCancel() != TRUE)
		{
			return FALSE;
		}
	}
	else if (pView->IsKindOf(RUNTIME_CLASS(CUserAddView)))
	{
		if (((CUserAddView*)pView)->BeCancel() != TRUE)
		{
			return FALSE;
		}
	}
	else if (pView->IsKindOf(RUNTIME_CLASS(CPasswordMgrView)))
	{
		if (((CPasswordMgrView*)pView)->BeCancel() != TRUE)
		{
			return FALSE;
		}
	}

	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// 基类将执行真正的工作

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	return TRUE;
}

void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
}


void CMainFrame::OnClose()
{
	if (SetLeftViewMenu(TREE_ROOT_ID) != TRUE)
	{
		return;
	}
	if (ShowRightView(TREE_ROOT_ID) != TRUE)
	{
		return;
	}
	m_listPreRightViewID.clear();

	ShowWindow(SW_HIDE);

	m_bAuthorized = FALSE;

	//CFrameWndEx::OnClose();
}

// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "ManagerView.h"
#include "ExSplitterWnd.h"
#include "RootView.h"
#include "MenuView.h"
#include "BasicMgrView.h"
#include "SupplierMgrView.h"
#include "SupplierAddView.h"
#include "VendorMgrView.h"
#include "VendorAddView.h"
#include "MedicineMgrView.h"
#include "UserMgrView.h"
#include "UserAddView.h"
#include "AccountMgrView.h"
#include "PasswordMgrView.h"
#include "PurchaseMgrView.h"
#include "PurchaseAddView.h"
#include "PurchaseListView.h"
#include "RetailMgrView.h"
#include "StoreMgrView.h"
#include "StoreEditView.h"
#include "BackupMgrView.h"
#include "LoginDlg.h"
#include <list>

const UINT WM_MAINFRM = ::RegisterWindowMessage(_T("WM_MAINFRM"));
const UINT WM_MAINFRM_SETRIGHTPANE = 1;
const UINT WM_MAINFRM_SETPRERIGHTPANE = 2;

#define MY_WM_NOTIFYICON (WM_USER+1001)

class CMainFrame : public CFrameWndEx
{
	
public: // 仅从序列化创建
	CMainFrame();
	virtual ~CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

	virtual BOOL PreTranslateMessage(MSG* pMsg);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL SetLeftViewMenu(TreeMenuID id);
	BOOL ShowRightView(TreeMenuID id, BOOL bRememberPreID = TRUE);
	BOOL BeRightViewQuit();

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

	CMFCStatusBar      m_wndStatusBar;
	TreeMenuID		   m_rightViewID;
	list<TreeMenuID>   m_listPreRightViewID;

	CExSplitterWnd m_wndSplitter;
	NOTIFYICONDATA m_ntIcon;
	CLoginDlg m_loginDlg;
	BOOL m_bAuthorized;

// 生成的消息映射函数
protected:
	afx_msg LRESULT OnMainFrm(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnPaint();
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg LRESULT OnNotifyIcon(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};



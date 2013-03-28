// UserMgrView.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "UserMgrView.h"
#include "mainfrm.h"
#include "UserDB.h"

// CUserMgrView

IMPLEMENT_DYNCREATE(CUserMgrView, CFormView)

	CUserMgrView::CUserMgrView()
	: CFormView(CUserMgrView::IDD)
{
	m_dwCurPage = 0;
	m_dwTotalPage = 0;
	m_dwTotalNum = 0;
}

CUserMgrView::~CUserMgrView()
{
}

void CUserMgrView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USER, m_listUser);
	DDX_Control(pDX, IDC_STATIC_PAGE, m_staticPageInfo);
	DDX_Control(pDX, IDC_BTN_PREPAGE, m_btnPrePage);
	DDX_Control(pDX, IDC_BTN_NEXTPAGE, m_btnNextPage);
	DDX_Control(pDX, IDC_BUTTON_USER_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_BUTTON_USER_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BUTTON_USER_DEL, m_btnDel);
}

BEGIN_MESSAGE_MAP(CUserMgrView, CFormView)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_USER, &CUserMgrView::OnLvnItemchangedListUser)
	ON_BN_CLICKED(IDC_BUTTON_USER_ADD, &CUserMgrView::OnBnClickedButtonUserAdd)
	ON_BN_CLICKED(IDC_BUTTON_USER_EDIT, &CUserMgrView::OnBnClickedButtonUserEdit)
	ON_BN_CLICKED(IDC_BUTTON_USER_DEL, &CUserMgrView::OnBnClickedButtonUserDel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_USER, &CUserMgrView::OnNMDblclkListUser)
	ON_BN_CLICKED(IDC_BTN_PREPAGE, &CUserMgrView::OnBnClickedBtnPrepage)
	ON_BN_CLICKED(IDC_BTN_NEXTPAGE, &CUserMgrView::OnBnClickedBtnNextpage)
END_MESSAGE_MAP()

void CUserMgrView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	ERRCODE errRet = err_OK;
	CString csMsg;
	csMsg.Format("%s-%s", APP_NAME, APP_MANAGER);
	AfxGetApp()->GetMainWnd()->SetWindowText(csMsg);

	m_listUser.SetExtendedStyle(LVS_EX_FLATSB    // 扁平风格滚动
		| LVS_EX_FULLROWSELECT    // 允许整行选中
		| LVS_EX_HEADERDRAGDROP    // 允许标题拖拽
		| LVS_EX_GRIDLINES    // 画出网格线
		);
	m_listUser.InsertColumn(0, "编号", LVCFMT_LEFT, 0, 0);
	m_listUser.InsertColumn(1, "工号", LVCFMT_LEFT, 80, 0);
	m_listUser.InsertColumn(2, "姓名", LVCFMT_LEFT, 150, 0);
	m_listUser.InsertColumn(3, "角色", LVCFMT_LEFT, 150, 0);
	m_listUser.InsertColumn(4, "创建时间", LVCFMT_LEFT, 150, 0);

	DisplayUsers();
}

void CUserMgrView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CUserMgrView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	int iWidth = 0, iHeight = 0;
	CRect clientRect;
	GetClientRect(clientRect);

	CRect nextBtnRect;
	CButton *pBtnNextPage = (CButton*)GetDlgItem(IDC_BTN_NEXTPAGE);
	if (pBtnNextPage->GetSafeHwnd() != NULL)
	{
		pBtnNextPage->GetClientRect(nextBtnRect);
		iWidth = nextBtnRect.Width();
		iHeight = nextBtnRect.Height();
		nextBtnRect.right = clientRect.Width() - 7;
		nextBtnRect.left = nextBtnRect.right - iWidth;
		nextBtnRect.top = clientRect.top + 15;
		nextBtnRect.bottom =  nextBtnRect.top + iHeight;
		pBtnNextPage->SetWindowPos(NULL, nextBtnRect.left, nextBtnRect.top, nextBtnRect.Width(),  nextBtnRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect preBtnRect;
	CButton *pBtnPrePage = (CButton*)GetDlgItem(IDC_BTN_PREPAGE);
	if (pBtnPrePage->GetSafeHwnd() != NULL)
	{
		pBtnPrePage->GetClientRect(preBtnRect);
		iWidth = preBtnRect.Width();
		iHeight = preBtnRect.Height();
		preBtnRect.right =  nextBtnRect.left;
		preBtnRect.left = preBtnRect.right - iWidth;
		preBtnRect.top = clientRect.top + 15;
		preBtnRect.bottom =  preBtnRect.top + iHeight;
		pBtnPrePage->SetWindowPos(NULL, preBtnRect.left, preBtnRect.top, preBtnRect.Width(),  preBtnRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect pageInfoRect;
	CStatic *pStaticPageInfo = (CStatic*)GetDlgItem(IDC_STATIC_PAGE);
	if (pStaticPageInfo->GetSafeHwnd() != NULL)
	{
		pStaticPageInfo->GetClientRect(pageInfoRect);
		iWidth = pageInfoRect.Width();
		iHeight = pageInfoRect.Height();
		pageInfoRect.right =  preBtnRect.left;
		pageInfoRect.left = pageInfoRect.right - iWidth;
		pageInfoRect.top = clientRect.top + 20;
		pageInfoRect.bottom =  pageInfoRect.top + iHeight;
		pStaticPageInfo->SetWindowPos(NULL, pageInfoRect.left, pageInfoRect.top, pageInfoRect.Width(),  pageInfoRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CListCtrl *pUserList = (CListCtrl*)GetDlgItem(IDC_LIST_USER);
	if (pUserList->GetSafeHwnd() != NULL)
	{
		pUserList->SetWindowPos(NULL, clientRect.left + 5, clientRect.top + 50, clientRect.Width() - 10, clientRect.Height() - 55, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

// CUserMgrView diagnostics

#ifdef _DEBUG
void CUserMgrView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserMgrView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CUserMgrView::DisplayUsers()
{
	ERRCODE errRet = err_OK;
	CString csMsg;
	CUserDB userDB;

	errRet = userDB.GetUserRoles(m_vctUserRoles);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取用户信息错误！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("用户管理"), MB_ICONERROR);
		return;
	}

	vector<User*> vctUsers;
	switch(atoi(theApp.m_curUser.csRole))
	{
	case Role_Supper:
		{
			errRet = userDB.GetUsers(m_dwCurPage, g_ciNumPerPage, m_dwTotalPage, m_dwTotalNum, vctUsers);
			if (errRet != err_OK)
			{
				csMsg.Format(_T("获取用户信息错误！%s"), GetErrMsg(errRet));
				MessageBox(csMsg, _T("用户管理"), MB_ICONERROR);
				return;
			}

			break;
		}
	case Role_Manager:
		{
			for (unsigned int j = Role_Manager; j < Role_None; j++)
			{
				errRet = userDB.GetUsers(m_dwCurPage, g_ciNumPerPage, m_dwTotalPage, m_dwTotalNum, vctUsers,  _T(""), (EnumUserRole) j);
				if (errRet != err_OK)
				{
					csMsg.Format(_T("获取用户信息错误！%s"), GetErrMsg(errRet));
					MessageBox(csMsg, _T("用户管理"), MB_ICONERROR);
					return;
				}
			}

			break;
		}
	default:
		break;
	}

	DisplayUserList(vctUsers);

	for (unsigned int i = 0; i < vctUsers.size(); i++)
	{
		delete vctUsers[i];
		vctUsers[i] = NULL;
	}
	vctUsers.clear();

	for (unsigned int i = 0; i < m_vctUserRoles.size(); i++)
	{
		delete m_vctUserRoles[i];
		m_vctUserRoles[i] = NULL;
	}
	m_vctUserRoles.clear();
}

void CUserMgrView::DisplayUserList(vector<User*> vctUsers)
{
	CString csMsg;

	csMsg.Format(_T("第%d-%d项，共%d项"), m_dwTotalNum>0?m_dwCurPage * g_ciNumPerPage + 1:0, m_dwCurPage * g_ciNumPerPage +  vctUsers.size(), m_dwTotalNum);
	m_staticPageInfo.SetWindowText(csMsg);
	if (m_dwCurPage == 0)
	{
		m_btnPrePage.EnableWindow(FALSE);
	}
	else
	{
		m_btnPrePage.EnableWindow(TRUE);
	}
	if (m_dwCurPage + 1 >= m_dwTotalPage)
	{
		m_btnNextPage.EnableWindow(FALSE);
	}
	else
	{
		m_btnNextPage.EnableWindow(TRUE);
	}

	m_listUser.DeleteAllItems();

	for (unsigned int i = 0; i < vctUsers.size(); i++)
	{
		DisplayUserListItem(i, vctUsers[i]);
	}
}

void CUserMgrView::DisplayUserListItem(int iItem, User *pUser)
{
	m_listUser.InsertItem(iItem, pUser->csID);
	m_listUser.SetItemText(iItem, 1, pUser->csUID);
	m_listUser.SetItemText(iItem, 2, pUser->csName);

	int iRoleID = atoi(pUser->csRole);
	if (iRoleID >= 0 && iRoleID < (int)m_vctUserRoles.size())
	{
		m_listUser.SetItemText(iItem, 3, m_vctUserRoles[iRoleID]->csName);
	}

	m_listUser.SetItemText(iItem, 4, pUser->csCreateTime);
}

// CUserMgrView message handlers


void CUserMgrView::OnLvnItemchangedListUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CString csMsg;

	int iTotalSelected = m_listUser.GetSelectedCount();
	POSITION pos = m_listUser.GetFirstSelectedItemPosition();
	int iSelected = m_listUser.GetNextSelectedItem(pos);
	if (iTotalSelected != 1 || iSelected == -1)
	{
		m_btnEdit.EnableWindow(FALSE);
		m_btnDel.EnableWindow(FALSE);
		return;
	}

	CString csID = m_listUser.GetItemText(iSelected, 0);
	csID.Trim();
	theApp.m_curUser.csID.Trim();
	if (theApp.m_curUser.csID == csID)
	{
		m_btnEdit.EnableWindow(FALSE);
		m_btnDel.EnableWindow(FALSE);
		return;
	}

	m_btnEdit.EnableWindow(TRUE);
	m_btnDel.EnableWindow(TRUE);
}


void CUserMgrView::OnBnClickedButtonUserAdd()
{
	// TODO: Add your control notification handler code here

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}
	pDoc->m_viewType = VIEW_NEW;
	pDoc->m_csUserUID = _T("");

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_USER_ADD;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}


void CUserMgrView::OnBnClickedButtonUserEdit()
{
	// TODO: Add your control notification handler code here

	CString csMsg;

	POSITION pos = m_listUser.GetFirstSelectedItemPosition();
	int iSelected = m_listUser.GetNextSelectedItem(pos);
	if (iSelected == -1)
	{
		return;
	}
	
	CString csID = m_listUser.GetItemText(iSelected, 0);
	csID.Trim();
	theApp.m_curUser.csID.Trim();
	if (theApp.m_curUser.csID == csID)
	{
		return;
	}

	CString csUID = m_listUser.GetItemText(iSelected, 1);

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}
	pDoc->m_viewType = VIEW_EDIT;
	pDoc->m_csUserUID = csUID;

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_USER_ADD;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}


void CUserMgrView::OnBnClickedButtonUserDel()
{
	// TODO: Add your control notification handler code here

	ERRCODE errRet = err_OK;
	CString csMsg;

	POSITION pos = m_listUser.GetFirstSelectedItemPosition();
	int iSelected = m_listUser.GetNextSelectedItem(pos);
	if (iSelected == -1)
	{
		return;
	}

	CString csID = m_listUser.GetItemText(iSelected, 0);
	CString csUID = m_listUser.GetItemText(iSelected, 1);
	CString csName = m_listUser.GetItemText(iSelected, 2);
	csMsg.Format(_T("您确认删除用户'%s'吗？"), csUID);
	if (IDCANCEL == MessageBox(csMsg, _T("用户管理"), MB_ICONQUESTION|MB_OKCANCEL))
	{
		return;
	}

	CUserDB userDB;
	errRet = userDB.DeleteUser(csID.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("删除用户失败，%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("用户管理"), MB_ICONERROR);
		return;
	}

	m_listUser.DeleteItem(iSelected);
}


void CUserMgrView::OnNMDblclkListUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	OnBnClickedButtonUserEdit();

	*pResult = 0;
}

void CUserMgrView::OnBnClickedBtnPrepage()
{
	// TODO: Add your control notification handler code here
	if (m_dwCurPage <= 0)
	{
		return;
	}

	m_dwCurPage--;
	DisplayUsers();
}

void CUserMgrView::OnBnClickedBtnNextpage()
{
	// TODO: Add your control notification handler code here
	if (m_dwCurPage + 1 >= m_dwTotalNum)
	{
		return;
	}

	m_dwCurPage++;
	DisplayUsers();
}
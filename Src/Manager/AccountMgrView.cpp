// UserAddView.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "AccountMgrView.h"
#include "MainFrm.h"

// CAccountMgrView

IMPLEMENT_DYNCREATE(CAccountMgrView, CFormView)

	CAccountMgrView::CAccountMgrView()
	: CFormView(CAccountMgrView::IDD)
{

}

CAccountMgrView::~CAccountMgrView()
{
	for (unsigned int i = 0; i < m_vctUserRoles.size(); i++)
	{
		delete m_vctUserRoles[i];
		m_vctUserRoles[i] = NULL;
	}
	m_vctUserRoles.clear();
}

void CAccountMgrView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAccountMgrView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_OK, &CAccountMgrView::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CAccountMgrView::OnBnClickedButtonCancel)
	ON_EN_CHANGE(IDC_EDIT_ACCOUNT_NAME, &CAccountMgrView::OnEnChangeEditAccountName)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_NAME, &CAccountMgrView::OnBnClickedButtonModifyName)
	ON_BN_CLICKED(IDC_BUTTON_NEWPASSWORD, &CAccountMgrView::OnBnClickedButtonNewPassword)
END_MESSAGE_MAP()


// CAccountMgrView diagnostics

#ifdef _DEBUG
void CAccountMgrView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAccountMgrView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAccountMgrView message handlers

void CAccountMgrView::OnInitialUpdate()
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

	DisplayUserInfo(theApp.m_curUser.csUID.GetBuffer());
}


void CAccountMgrView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CAccountMgrView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	CStatic *pStaticGroup = (CStatic*)GetDlgItem(IDC_STATIC_GROUP_DETAIL);
	if (pStaticGroup->GetSafeHwnd() != NULL)
	{
		pStaticGroup->SetWindowPos(NULL, rectClient.left + 5, rectClient.top + 60, rectClient.Width() - 10, rectClient.Height() - 55, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}


void CAccountMgrView::DisplayUserInfo(LPTSTR lpUserID)
{
	CUserDB userDB;
	CString csMsg;

	ERRCODE errRet = userDB.GetUserRoles(m_vctUserRoles);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取用户信息错误！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("用户管理"), MB_ICONERROR);
		return;
	}

	errRet = userDB.GetUser(lpUserID, &theApp.m_curUser);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取用户信息错误！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("用户管理"), MB_ICONERROR);
		return;
	}

	int iRole = atoi(theApp.m_curUser.csRole);
	SetDlgItemText(IDC_EDIT_ACCOUNT_ID, theApp.m_curUser.csUID);
	SetDlgItemText(IDC_EDIT_ACCOUNT_NAME, theApp.m_curUser.csName);

	if ((unsigned int)iRole >= 0 && (unsigned int)iRole < m_vctUserRoles.size())
	{
		SetDlgItemText(IDC_EDIT_ACCOUNT_ROLE, m_vctUserRoles[iRole]->csName);
	}
}


void CAccountMgrView::OnBnClickedButtonOk()
{
	// TODO: Add your control notification handler code here

	CString csMsg;
	if (m_bDataChanged == TRUE)
	{
		csMsg.Format(_T("是否保存对该账户信息的修改？"));

		int iRet = MessageBox(csMsg, _T("账户管理"), MB_ICONQUESTION|MB_YESNO);
		if (iRet == IDYES)
		{
			if (UpdateAccount() != TRUE)
			{
				return;
			}
			GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
			//GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(FALSE);
		}
	}
}


void CAccountMgrView::OnBnClickedButtonCancel()
{
	// TODO: Add your control notification handler code here
	CString csMsg;
	if (m_bDataChanged == TRUE)
	{
		csMsg.Format(_T("是否取消对账户信息的修改？"));

		int iRet = MessageBox(csMsg, _T("账户管理"), MB_ICONQUESTION|MB_YESNO);
		if (iRet != IDYES)
		{
			return;
		}
	}
	((CEdit*)(GetDlgItem(IDC_EDIT_ACCOUNT_NAME)))->SetReadOnly(TRUE);
	GetDlgItem(IDC_BUTTON_MODIFY_NAME)->ShowWindow(SW_SHOW);
	DisplayUserInfo(theApp.m_curUser.csUID.GetBuffer());
	GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(FALSE);
}


void CAccountMgrView::OnEnChangeEditAccountName()
{
	CString csName;
	GetDlgItemText(IDC_EDIT_ACCOUNT_NAME, csName);
	csName.Trim();
	if (csName == theApp.m_curUser.csName)
	{
		m_bDataChanged = FALSE;
		GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(FALSE);
	}
	else
	{
		m_bDataChanged = TRUE;
		GetDlgItem(IDC_BUTTON_OK)->EnableWindow(TRUE);
		//GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(TRUE);
	}
}


BOOL CAccountMgrView::UpdateAccount()
{
	ERRCODE errRet = err_OK;
	CString csMsg;
	CString csName;
	GetDlgItemText(IDC_EDIT_ACCOUNT_NAME, csName);
	csName.Trim();

	if (csName == _T(""))
	{
		csMsg.Format("账户名称不能为空！");
		MessageBox(csMsg, _T("账户管理"), MB_ICONERROR);
		return FALSE;
	}

	CUserDB userDB;
	errRet = userDB.UpdateUser(theApp.m_curUser.csID.GetBuffer(), theApp.m_curUser.csUID.GetBuffer(), csName.GetBuffer(), atol(theApp.m_curUser.csRole));
	if (errRet == err_User_AlreadyExist)
	{
		csMsg.Format(_T("账户名称已经存在，请重新输入"));
		MessageBox(csMsg, _T("账户管理"), MB_ICONINFORMATION);
		return FALSE;
	}
	else if (errRet != err_OK)
	{
		csMsg.Format(_T("修改账户失败，%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("账户管理"), MB_ICONERROR);
		return FALSE;
	}

	theApp.m_curUser.csName = csName;

	((CEdit*)(GetDlgItem(IDC_EDIT_ACCOUNT_NAME)))->SetReadOnly(TRUE);
	GetDlgItem(IDC_BUTTON_MODIFY_NAME)->ShowWindow(SW_SHOW);

	return TRUE;
}

void CAccountMgrView::OnBnClickedButtonModifyName()
{
	// TODO: 在此添加控件通知处理程序代码
	((CEdit*)(GetDlgItem(IDC_EDIT_ACCOUNT_NAME)))->SetReadOnly(FALSE);
	((CEdit*)(GetDlgItem(IDC_EDIT_ACCOUNT_NAME)))->SetFocus();
	GetDlgItem(IDC_BUTTON_MODIFY_NAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(TRUE);
}

void CAccountMgrView::OnBnClickedButtonNewPassword()
{
	// TODO: 在此添加控件通知处理程序代码

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_ACCOUNT_NEWPWS;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}

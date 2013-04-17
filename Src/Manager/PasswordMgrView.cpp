// PasswordMgrView.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "PasswordMgrView.h"
#include "MainFrm.h"
#include "AccountDB.h"

// CPasswordMgrView

IMPLEMENT_DYNCREATE(CPasswordMgrView, CFormView)

CPasswordMgrView::CPasswordMgrView()
	: CFormView(CPasswordMgrView::IDD)
{

}

CPasswordMgrView::~CPasswordMgrView()
{
}

void CPasswordMgrView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPasswordMgrView, CFormView)
	ON_EN_CHANGE(IDC_EDIT_ACCOUNT_CURRENTPASSWORD, &CPasswordMgrView::OnEnChangeEditAccountCurrentPassword)
	ON_EN_CHANGE(IDC_EDIT_ACCOUNT_NEWPASSWORD, &CPasswordMgrView::OnEnChangeEditAccountNewPassword)
	ON_EN_CHANGE(IDC_EDIT_ACCOUNT_AGAINNEWPASSWORD, &CPasswordMgrView::OnEnChangeEditAccountAgainnewPassword)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CPasswordMgrView::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CPasswordMgrView::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CPasswordMgrView 诊断

#ifdef _DEBUG
void CPasswordMgrView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPasswordMgrView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPasswordMgrView 消息处理程序

void CPasswordMgrView::OnInitialUpdate()
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

	GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(TRUE);
}


void CPasswordMgrView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CPasswordMgrView::AdjustLayout()
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
		pStaticGroup->SetWindowPos(NULL, rectClient.left + 5, rectClient.top + 50, rectClient.Width() - 10, rectClient.Height() - 55, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void CPasswordMgrView::OnEnChangeEditAccountCurrentPassword()
{
	CString csCurrentPwd;
	GetDlgItemText(IDC_EDIT_ACCOUNT_CURRENTPASSWORD, csCurrentPwd);
	csCurrentPwd.Trim();
	if (csCurrentPwd == _T(""))
	{
		GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(FALSE);
		return;
	}

	CString csNewPwd;
	GetDlgItemText(IDC_EDIT_ACCOUNT_NEWPASSWORD, csNewPwd);
	csNewPwd.Trim();
	if (csNewPwd == _T(""))
	{
		GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(FALSE);
		return;
	}

	CString csAgainPwd;
	GetDlgItemText(IDC_EDIT_ACCOUNT_AGAINNEWPASSWORD, csAgainPwd);
	csAgainPwd.Trim();
	if (csAgainPwd == _T(""))
	{
		GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(FALSE);
		return;
	}

	GetDlgItem(IDC_BUTTON_OK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(TRUE);
}


void CPasswordMgrView::OnEnChangeEditAccountNewPassword()
{
	CString csCurrentPwd;
	GetDlgItemText(IDC_EDIT_ACCOUNT_CURRENTPASSWORD, csCurrentPwd);
	csCurrentPwd.Trim();
	if (csCurrentPwd == _T(""))
	{
		GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(FALSE);
		return;
	}

	CString csNewPwd;
	GetDlgItemText(IDC_EDIT_ACCOUNT_NEWPASSWORD, csNewPwd);
	csNewPwd.Trim();
	if (csNewPwd == _T(""))
	{
		GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(FALSE);
		return;
	}

	CString csAgainPwd;
	GetDlgItemText(IDC_EDIT_ACCOUNT_AGAINNEWPASSWORD, csAgainPwd);
	csAgainPwd.Trim();
	if (csAgainPwd == _T(""))
	{
		GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(FALSE);
		return;
	}

	GetDlgItem(IDC_BUTTON_OK)->EnableWindow(TRUE);
	//GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(TRUE);
}


void CPasswordMgrView::OnEnChangeEditAccountAgainnewPassword()
{
	CString csCurrentPwd;
	GetDlgItemText(IDC_EDIT_ACCOUNT_CURRENTPASSWORD, csCurrentPwd);
	csCurrentPwd.Trim();
	if (csCurrentPwd == _T(""))
	{
		GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(FALSE);
		return;
	}

	CString csNewPwd;
	GetDlgItemText(IDC_EDIT_ACCOUNT_NEWPASSWORD, csNewPwd);
	csNewPwd.Trim();
	if (csNewPwd == _T(""))
	{
		GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(FALSE);
		return;
	}

	CString csAgainPwd;
	GetDlgItemText(IDC_EDIT_ACCOUNT_AGAINNEWPASSWORD, csAgainPwd);
	csAgainPwd.Trim();
	if (csAgainPwd == _T(""))
	{
		GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(FALSE);
		return;
	}

	GetDlgItem(IDC_BUTTON_OK)->EnableWindow(TRUE);
	//GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(TRUE);
}


void CPasswordMgrView::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码

	if (UpdatePassword() != TRUE)
	{
		return;
	}
	GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_ACCOUNT_ID;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}


BOOL CPasswordMgrView::BeCancel()
{
	CString csMsg;
	if (GetDlgItem(IDC_BUTTON_OK)->IsWindowEnabled() == TRUE)
	{
		csMsg.Format(_T("密码信息已经修改，是否进行保存？"));
		int iRet = MessageBox(csMsg, _T("账户管理"), MB_ICONQUESTION|MB_YESNOCANCEL);
		if (iRet == IDCANCEL)
		{
			return FALSE;
		}
		else if (iRet == IDYES)
		{
			if (UpdatePassword() != TRUE)
			{
				return FALSE;
			}
		}
	}

	GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
	return TRUE;
}


void CPasswordMgrView::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BeCancel() != TRUE)
	{
		return;
	}

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_ACCOUNT_ID;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}

BOOL CPasswordMgrView::UpdatePassword()
{
	CString csMsg;
	CString csCurPwd, csNewPwd, csAgainPwd;

	GetDlgItemText(IDC_EDIT_ACCOUNT_CURRENTPASSWORD, csCurPwd);
	GetDlgItemText(IDC_EDIT_ACCOUNT_NEWPASSWORD, csNewPwd);
	GetDlgItemText(IDC_EDIT_ACCOUNT_AGAINNEWPASSWORD, csAgainPwd);

	csCurPwd.Trim();
	csNewPwd.Trim();
	csAgainPwd.Trim();
	if (csCurPwd == _T(""))
	{
		csMsg.Format(_T("当前密码不能为空！"));
		MessageBox(csMsg, _T("账户管理"), MB_ICONERROR);
		GetDlgItem(IDC_EDIT_ACCOUNT_CURRENTPASSWORD)->SetFocus();
		return FALSE;
	}
	if (csNewPwd == _T(""))
	{
		csMsg.Format(_T("新密码不能为空！"));
		MessageBox(csMsg, _T("账户管理"), MB_ICONERROR);
		GetDlgItem(IDC_EDIT_ACCOUNT_NEWPASSWORD)->SetFocus();
		return FALSE;
	}
	if (csAgainPwd == _T(""))
	{
		csMsg.Format(_T("确认密码不能为空！"));
		MessageBox(csMsg, _T("账户管理"), MB_ICONERROR);
		GetDlgItem(IDC_EDIT_ACCOUNT_AGAINNEWPASSWORD)->SetFocus();
		return FALSE;
	}
	if (csNewPwd != csAgainPwd)
	{
		csMsg.Format(_T("两次输入的新密码不一致！"));
		MessageBox(csMsg, _T("账户管理"), MB_ICONERROR);
		GetDlgItem(IDC_EDIT_ACCOUNT_NEWPASSWORD)->SetFocus();
		return FALSE;
	}

	if (csCurPwd == csNewPwd)
	{
		csMsg.Format(_T("请设置与当前密码不同的新密码！"));
		MessageBox(csMsg, _T("账户管理"), MB_ICONERROR);
		GetDlgItem(IDC_EDIT_ACCOUNT_NEWPASSWORD)->SetFocus();
		return FALSE;
	}

	CAccountDB accountDB;
	ERRCODE errRet = accountDB.CheckPWD(theApp.m_curUser.csUID.GetBuffer(), csCurPwd.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("当前密码不正确，请重新输入！"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("账户管理"), MB_ICONERROR);
		GetDlgItem(IDC_EDIT_ACCOUNT_CURRENTPASSWORD)->SetFocus();
		return FALSE;
	}

	errRet = accountDB.UpdatePassword(theApp.m_curUser.csUID.GetBuffer(), csNewPwd.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("更新密码失败，%s！"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("账户管理"), MB_ICONERROR);
		return FALSE;
	}
	
	return TRUE;
}
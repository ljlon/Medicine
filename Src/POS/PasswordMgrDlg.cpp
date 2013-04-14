// PasswordMgrView.cpp : 实现文件
//

#include "stdafx.h"
#include "POS.h"
#include "PasswordMgrDlg.h"
#include "AccountDB.h"

// CPasswordMgrDlg

IMPLEMENT_DYNCREATE(CPasswordMgrDlg, CDialogEx)

CPasswordMgrDlg::CPasswordMgrDlg()
	: CDialogEx(CPasswordMgrDlg::IDD)
{

}

CPasswordMgrDlg::~CPasswordMgrDlg()
{
}

void CPasswordMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPasswordMgrDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_ACCOUNT_CURRENTPASSWORD, &CPasswordMgrDlg::OnEnChangeEditAccountCurrentPassword)
	ON_EN_CHANGE(IDC_EDIT_ACCOUNT_NEWPASSWORD, &CPasswordMgrDlg::OnEnChangeEditAccountNewPassword)
	ON_EN_CHANGE(IDC_EDIT_ACCOUNT_AGAINNEWPASSWORD, &CPasswordMgrDlg::OnEnChangeEditAccountAgainnewPassword)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CPasswordMgrDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CPasswordMgrDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CPasswordMgrDlg 诊断

#ifdef _DEBUG
void CPasswordMgrDlg::AssertValid() const
{
	CDialogEx::AssertValid();
}

#ifndef _WIN32_WCE
void CPasswordMgrDlg::Dump(CDumpContext& dc) const
{
	CDialogEx::Dump(dc);
}
#endif
#endif //_DEBUG


// CPasswordMgrDlg 消息处理程序

BOOL CPasswordMgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString csMsg;
	csMsg.Format("%s-%s", APP_NAME, APP_POS);
	//SetWindowText(csMsg);

	GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(TRUE);

	return TRUE;
}


void CPasswordMgrDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CPasswordMgrDlg::AdjustLayout()
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

void CPasswordMgrDlg::OnEnChangeEditAccountCurrentPassword()
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


void CPasswordMgrDlg::OnEnChangeEditAccountNewPassword()
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


void CPasswordMgrDlg::OnEnChangeEditAccountAgainnewPassword()
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


void CPasswordMgrDlg::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码

	if (UpdatePassword() != TRUE)
	{
		return;
	}
	GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);

	CDialogEx::OnOK();
}


BOOL CPasswordMgrDlg::BeCancel()
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


void CPasswordMgrDlg::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BeCancel() != TRUE)
	{
		return;
	}

	CDialogEx::OnCancel();
}

BOOL CPasswordMgrDlg::UpdatePassword()
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
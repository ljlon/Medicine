// UserAddView.cpp : implementation file
//

#include "stdafx.h"
#include "POS.h"
#include "AccountMgrDlg.h"
#include "PasswordMgrDlg.h"

// CAccountMgrDlg

IMPLEMENT_DYNCREATE(CAccountMgrDlg, CDialogEx)

	CAccountMgrDlg::CAccountMgrDlg()
	: CDialogEx(CAccountMgrDlg::IDD)
{

}

CAccountMgrDlg::~CAccountMgrDlg()
{
	for (unsigned int i = 0; i < m_vctUserRoles.size(); i++)
	{
		delete m_vctUserRoles[i];
		m_vctUserRoles[i] = NULL;
	}
	m_vctUserRoles.clear();
}

void CAccountMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAccountMgrDlg, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_OK, &CAccountMgrDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CAccountMgrDlg::OnBnClickedButtonCancel)
	ON_EN_CHANGE(IDC_EDIT_ACCOUNT_NAME, &CAccountMgrDlg::OnEnChangeEditAccountName)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_NAME, &CAccountMgrDlg::OnBnClickedButtonModifyName)
	ON_BN_CLICKED(IDC_BUTTON_NEWPASSWORD, &CAccountMgrDlg::OnBnClickedButtonNewPassword)
END_MESSAGE_MAP()


// CAccountMgrDlg diagnostics

#ifdef _DEBUG
void CAccountMgrDlg::AssertValid() const
{
	CDialogEx::AssertValid();
}

#ifndef _WIN32_WCE
void CAccountMgrDlg::Dump(CDumpContext& dc) const
{
	CDialogEx::Dump(dc);
}
#endif
#endif //_DEBUG


// CAccountMgrDlg message handlers

BOOL CAccountMgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString csMsg;
	csMsg.Format("%s-%s", APP_NAME, APP_POS);
	//SetWindowText(csMsg);

	DisplayUserInfo(theApp.m_curUser.csUID.GetBuffer());

	return TRUE;
}


void CAccountMgrDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CAccountMgrDlg::AdjustLayout()
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


void CAccountMgrDlg::DisplayUserInfo(LPTSTR lpUserID)
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


void CAccountMgrDlg::OnBnClickedButtonOk()
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

	CDialogEx::OnOK();
}


void CAccountMgrDlg::OnBnClickedButtonCancel()
{
	// TODO: Add your control notification handler code here
	CString csMsg;
	((CEdit*)(GetDlgItem(IDC_EDIT_ACCOUNT_NAME)))->SetReadOnly(TRUE);
	GetDlgItem(IDC_BUTTON_MODIFY_NAME)->ShowWindow(SW_SHOW);
	DisplayUserInfo(theApp.m_curUser.csUID.GetBuffer());
	GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(FALSE);

	CDialogEx::OnCancel();
}


void CAccountMgrDlg::OnEnChangeEditAccountName()
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


BOOL CAccountMgrDlg::UpdateAccount()
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

void CAccountMgrDlg::OnBnClickedButtonModifyName()
{
	// TODO: 在此添加控件通知处理程序代码
	((CEdit*)(GetDlgItem(IDC_EDIT_ACCOUNT_NAME)))->SetReadOnly(FALSE);
	((CEdit*)(GetDlgItem(IDC_EDIT_ACCOUNT_NAME)))->SetFocus();
	GetDlgItem(IDC_BUTTON_MODIFY_NAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(TRUE);
}

void CAccountMgrDlg::OnBnClickedButtonNewPassword()
{
	// TODO: 在此添加控件通知处理程序代码

	CPasswordMgrDlg passwordDlg;
	passwordDlg.DoModal();
}

// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "AccountDB.h"
#include "UserDB.h"

// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_UID, m_editUID);
	DDX_Control(pDX, IDC_EDIT_PWD, m_editPWD);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLoginDlg message handlers

BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString csMsg;
	csMsg.Format("%s-%s", APP_NAME, APP_MANAGER);
	SetWindowText(csMsg);

	csMsg.Format(_T("»¶Ó­Ê¹ÓÃ%s"), APP_NAME);
	GetDlgItem(IDC_STATIC_WELCOME)->SetWindowText(csMsg);

	return FALSE;
}

void CLoginDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	ERRCODE errRet = err_OK;
	CString csMsg;

	CString csUID, csPWD;
	m_editUID.GetWindowText(csUID);
	m_editPWD.GetWindowText(csPWD);
	csUID.Trim();
	csPWD.Trim();
	if (csUID == _T("") || csPWD == _T(""))
	{
		csMsg.Format(" ÕË»§»òÃÜÂë²»ÄÜÎª¿Õ£¡");
		MessageBox(csMsg, _T("µÇÂ¼"), MB_ICONERROR);
		return;
	}

	CAccountDB accountDb;
	errRet = accountDb.CheckPWD(csUID.GetBuffer(), csPWD.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("µÇÂ¼Ê§°Ü£¬%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("µÇÂ¼"), MB_ICONERROR);
		return;
	}

	CUserDB userDb;
	errRet = userDb.GetUser(csUID.GetBuffer(), &m_curUser);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("µÇÂ¼Ê§°Ü£¬%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("µÇÂ¼"), MB_ICONERROR);
		return;
	}

	int iRole = atoi(m_curUser.csRole);
	if (iRole != Role_Supper && iRole != Role_Manager && iRole != Role_DataEntryClerk)
	{
		csMsg.Format(_T("µÇÂ¼Ê§°Ü£¬¸ÃÕË»§Ã»ÓÐÈ¨ÏÞ"));
		MessageBox(csMsg, _T("µÇÂ¼"), MB_ICONERROR);
		return;
	}

	CDialogEx::OnOK();
}


void CLoginDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

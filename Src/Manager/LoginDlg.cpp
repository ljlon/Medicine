// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "AccountDB.h"
#include "UserDB.h"
#include "Config.h"

// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
{
	m_iShowWindow = SW_SHOW;
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
	ON_WM_SIZE()
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLoginDlg message handlers

BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString csMsg;
	csMsg.Format("%s-µÇÂ½", APP_MANAGER);
	SetWindowText(csMsg);

	csMsg.Format(_T("»¶Ó­Ê¹ÓÃ%s"), APP_NAME);
	GetDlgItem(IDC_STATIC_WELCOME)->SetWindowText(csMsg);

	return FALSE;
}


LRESULT CLoginDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{ 
	ERRCODE errRet = err_OK;

    if (message == 133)
     {
		if (m_iShowWindow == SW_HIDE)
		{
			ShowWindow(SW_HIDE);
			return TRUE;
		}
	}
	else if (message == LOGINDLG_SHOWWINDOW)
	{
		m_iShowWindow = SW_SHOW;

		errRet = g_config.Load();
		if (errRet)
		{
			g_log.Write(_T("Load config fail"), errRet);
			return FALSE;
		}
    } 
    
	return CDialogEx::DefWindowProc(message, wParam, lParam); 
} 


void CLoginDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
}


void CLoginDlg::OnBnClickedOk()
{
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

	m_editUID.SetWindowText(_T(""));
	m_editPWD.SetWindowText(_T(""));
	m_editUID.SetFocus();


	CDialogEx::OnCancel();
}

void CLoginDlg::SetShowWindow(int iShowWindow)
{
	m_iShowWindow = iShowWindow;
}
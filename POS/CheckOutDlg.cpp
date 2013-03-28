// CheckOutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "POS.h"
#include "RetailDlg.h"
#include "CheckOutDlg.h"
#include "afxdialogex.h"


// CCheckOutDlg dialog

IMPLEMENT_DYNAMIC(CCheckOutDlg, CDialogEx)

CCheckOutDlg::CCheckOutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCheckOutDlg::IDD, pParent)
{
	m_iStatus = CheckOut_Status_1;
	m_pCustomerDisplay = NULL;
}

CCheckOutDlg::~CCheckOutDlg()
{
}

void CCheckOutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCheckOutDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_IN, &CCheckOutDlg::OnEnChangeEditIn)
END_MESSAGE_MAP()

BOOL CCheckOutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString csMsg;
	csMsg.Format(_T("%0.2f"), m_dbTotalPrice);
	SetDlgItemText(IDC_EDIT_TOTAL, csMsg);
	SetDlgItemText(IDC_EDIT_IN,  _T(""));
	SetDlgItemText(IDC_EDIT_OUT,  _T("0.00"));
	GetDlgItem(IDC_EDIT_IN)->SetFocus();

	return FALSE;
}

// CCheckOutDlg message handlers

BOOL CCheckOutDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || 
			pMsg->wParam == g_config.key_checkout[0] || 
			pMsg->wParam == g_config.key_checkout[1])
		{
			if (m_iStatus == CheckOut_Status_1)
			{
				if (m_dbIn < m_dbTotalPrice)
				{
					MessageBox(_T("实收金额小于应付金额！"), _T(""), MB_OK | MB_ICONWARNING);
					GetDlgItem(IDC_EDIT_IN)->SetFocus();
					return TRUE;
				}

				if (m_pCustomerDisplay != NULL)
				{
					m_pCustomerDisplay->Display(CDisplayType_Out, m_dbOut);
				}

				this->GetParent()->SendMessage(MESSAGE_RETAILDLG, MESSAGE_RETAILDGL_UPDATEINPRICE, (LPARAM)&m_dbIn);
				CEdit* pEditIn = (CEdit*)GetDlgItem(IDC_EDIT_IN);
				pEditIn->SetReadOnly(TRUE);

				m_iStatus = CheckOut_Status_2;
				return TRUE;
			}
			else if (m_iStatus == CheckOut_Status_2)
			{
				CDialogEx::OnOK();
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CCheckOutDlg::OnOK()
{
	CDialogEx::OnOK();
}

void CCheckOutDlg::OnEnChangeEditIn()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CString csMsg;
	GetDlgItemText(IDC_EDIT_IN, csMsg);
	m_dbIn = atof(csMsg);

	m_dbOut = m_dbIn - m_dbTotalPrice;
	csMsg.Format(_T("%0.2f"), m_dbOut);
	SetDlgItemText(IDC_EDIT_OUT, csMsg);

	this->GetParent()->SendMessage(MESSAGE_RETAILDLG, MESSAGE_RETAILDGL_UPDATEINPRICE, (LPARAM)&m_dbIn);
}

// DeleteOneRowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "POS.h"
#include "DeleteOneRowDlg.h"
#include "afxdialogex.h"


// CDeleteOneRowDlg dialog

IMPLEMENT_DYNAMIC(CDeleteOneRowDlg, CDialogEx)

CDeleteOneRowDlg::CDeleteOneRowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDeleteOneRowDlg::IDD, pParent)
{

}

CDeleteOneRowDlg::~CDeleteOneRowDlg()
{
}

void CDeleteOneRowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ROW, m_editRow);
}


BEGIN_MESSAGE_MAP(CDeleteOneRowDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CDeleteOneRowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString csMsg;

	csMsg.Format(_T("%d"), m_iRow);
	m_editRow.SetWindowText(csMsg);

	return TRUE;
}

// CDeleteOneRowDlg message handlers
void CDeleteOneRowDlg::OnOK()
{
	CDialogEx::OnOK();

	CString csMsg;

	m_editRow.GetWindowText(csMsg);
	m_iRow = atol(csMsg.GetBuffer());
}

void CDeleteOneRowDlg::OnEnChangeEditRow()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CString csMsg;

	m_editRow.GetWindowText(csMsg);
	int iRow = atol(csMsg.GetBuffer());

	if (iRow < 1 || iRow > m_iRow)
	{
		csMsg.Format(_T("%d"), m_iRow);
		m_editRow.SetWindowText(csMsg);
	}
}

// ChangeNum.cpp : implementation file
//

#include "stdafx.h"
#include "POS.h"
#include "ChangeNumDlg.h"
#include "afxdialogex.h"


// CChangeNumDlg dialog

IMPLEMENT_DYNAMIC(CChangeNumDlg, CDialogEx)

CChangeNumDlg::CChangeNumDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChangeNumDlg::IDD, pParent)
{

}

CChangeNumDlg::~CChangeNumDlg()
{
}

void CChangeNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ROW, m_editRow);
	DDX_Control(pDX, IDC_EDIT_NUM, m_editNum);
}


BEGIN_MESSAGE_MAP(CChangeNumDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_NUM, &CChangeNumDlg::OnEnChangeEditNum)
	ON_EN_CHANGE(IDC_EDIT_ROW, &CChangeNumDlg::OnEnChangeEditRow)
END_MESSAGE_MAP()

BOOL CChangeNumDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString csMsg;

	csMsg.Format(_T("%d"), m_iRow);
	m_editRow.SetWindowText(csMsg);

	csMsg.Format(_T("%d"), m_iNum);
	m_editNum.SetWindowText(csMsg);

	return TRUE;
}

// CChangeNumDlg message handlers
void CChangeNumDlg::OnOK()
{
	CDialogEx::OnOK();

	CString csMsg;
	
	m_editRow.GetWindowText(csMsg);
	m_iRow = atol(csMsg.GetBuffer());

	m_editNum.GetWindowText(csMsg);
	m_iNum = atol(csMsg.GetBuffer());
}

void CChangeNumDlg::OnEnChangeEditNum()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CString csMsg;

	m_editNum.GetWindowText(csMsg);
	int iNum = atol(csMsg.GetBuffer());
	if (iNum <= 0)
	{
		csMsg.Format(_T("%d"), m_iNum);
		m_editNum.SetWindowText(csMsg);
	}
}


void CChangeNumDlg::OnEnChangeEditRow()
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

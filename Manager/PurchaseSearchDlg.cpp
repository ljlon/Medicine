// PurchaseSearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "PurchaseSearchDlg.h"
#include "afxdialogex.h"


// CPurchaseSearchDlg 对话框

IMPLEMENT_DYNAMIC(CPurchaseSearchDlg, CDialogEx)

CPurchaseSearchDlg::CPurchaseSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPurchaseSearchDlg::IDD, pParent)
{

}

CPurchaseSearchDlg::~CPurchaseSearchDlg()
{
}

void CPurchaseSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_PURCHASE_DATE, m_btnPurDate);
	DDX_Control(pDX, IDC_DATE_PUR_BEGIN, m_datePurBegin);
	DDX_Control(pDX, IDC_DATE_PUR_END, m_datePurEnd);
}


BEGIN_MESSAGE_MAP(CPurchaseSearchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_PURCHASE_DATE, &CPurchaseSearchDlg::OnBnClickedCheckPurchaseDate)
	ON_BN_CLICKED(IDOK, &CPurchaseSearchDlg::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL CPurchaseSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	BOOL bHasDate = FALSE;
	if (m_csPurBeginDate != _T("") && m_csPurEndDate != _T(""))
	{
		bHasDate = TRUE;
		m_btnPurDate.SetCheck(TRUE);
		m_datePurBegin.EnableWindow(TRUE);
		m_datePurEnd.EnableWindow(TRUE);

		SYSTEMTIME time;
		if (ChangeDate(m_csPurBeginDate.GetBuffer(), time) == TRUE)
		{
			m_datePurBegin.SetTime(&time);
		}
		if (ChangeDate(m_csPurEndDate.GetBuffer(), time) == TRUE)
		{
			m_datePurEnd.SetTime(&time);
		}
	}

	return FALSE;
}

// CPurchaseSearchDlg 消息处理程序


void CPurchaseSearchDlg::OnBnClickedCheckPurchaseDate()
{
	// TODO: Add your control notification handler code here
	if (m_btnPurDate.GetCheck() == TRUE)
	{
		m_datePurBegin.EnableWindow(TRUE);
		m_datePurEnd.EnableWindow(TRUE);
		m_datePurBegin.SetFocus();
	}
	else
	{
		m_datePurBegin.EnableWindow(FALSE);
		m_datePurEnd.EnableWindow(FALSE);
	}
}


void CPurchaseSearchDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	m_csPurBeginDate = _T("");
	m_csPurEndDate = _T("");
	if (m_btnPurDate.GetCheck() == TRUE)
	{
		m_datePurBegin.GetWindowText(m_csPurBeginDate);
		m_datePurEnd.GetWindowText(m_csPurEndDate);
		m_csPurBeginDate.Trim();
		m_csPurEndDate.Trim();

		if (m_csPurBeginDate > m_csPurEndDate)
		{
			m_csPurEndDate = m_csPurBeginDate;
		}
	}

	CDialogEx::OnOK();
}

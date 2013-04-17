// RetailSearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "RetailSearchDlg.h"
#include "afxdialogex.h"


// CRetailSearchDlg 对话框

IMPLEMENT_DYNAMIC(CRetailSearchDlg, CDialogEx)

CRetailSearchDlg::CRetailSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRetailSearchDlg::IDD, pParent)
{

}

CRetailSearchDlg::~CRetailSearchDlg()
{
}

void CRetailSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_RETAIL_DATE, m_btnRetailDate);
	DDX_Control(pDX, IDC_DATE_RETAIL_BEGIN, m_dateRetailBegin);
	DDX_Control(pDX, IDC_DATE_RETAIL_END, m_dateRetailEnd);
}


BEGIN_MESSAGE_MAP(CRetailSearchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_RETAIL_DATE, &CRetailSearchDlg::OnBnClickedCheckRetailDate)
	ON_BN_CLICKED(IDOK, &CRetailSearchDlg::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL CRetailSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	BOOL bHasDate = FALSE;
	if (m_csRetailBeginDate != _T("") && m_csRetailEndDate != _T(""))
	{
		bHasDate = TRUE;
		m_btnRetailDate.SetCheck(TRUE);
		m_dateRetailBegin.EnableWindow(TRUE);
		m_dateRetailEnd.EnableWindow(TRUE);

		SYSTEMTIME time;
		if (ChangeDate(m_csRetailBeginDate.GetBuffer(), time) == TRUE)
		{
			m_dateRetailBegin.SetTime(&time);
		}
		if (ChangeDate(m_csRetailEndDate.GetBuffer(), time) == TRUE)
		{
			m_dateRetailEnd.SetTime(&time);
		}
	}

	return FALSE;
}

// CRetailSearchDlg 消息处理程序


void CRetailSearchDlg::OnBnClickedCheckRetailDate()
{
	// TODO: Add your control notification handler code here
	if (m_btnRetailDate.GetCheck() == TRUE)
	{
		m_dateRetailBegin.EnableWindow(TRUE);
		m_dateRetailEnd.EnableWindow(TRUE);
		m_dateRetailBegin.SetFocus();
	}
	else
	{
		m_dateRetailBegin.EnableWindow(FALSE);
		m_dateRetailEnd.EnableWindow(FALSE);
	}
}


void CRetailSearchDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	m_csRetailBeginDate = _T("");
	m_csRetailEndDate = _T("");
	if (m_btnRetailDate.GetCheck() == TRUE)
	{
		m_dateRetailBegin.GetWindowText(m_csRetailBeginDate);
		m_dateRetailEnd.GetWindowText(m_csRetailEndDate);
		m_csRetailBeginDate.Trim();
		m_csRetailEndDate.Trim();

		if (m_csRetailBeginDate > m_csRetailEndDate)
		{
			m_csRetailEndDate = m_csRetailBeginDate;
		}
	}

	CDialogEx::OnOK();
}

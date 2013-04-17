// SupplierSearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "SupplierSearchDlg.h"
#include "afxdialogex.h"


// CSupplierSearchDlg 对话框

IMPLEMENT_DYNAMIC(CSupplierSearchDlg, CDialogEx)

CSupplierSearchDlg::CSupplierSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSupplierSearchDlg::IDD, pParent)
{

}

CSupplierSearchDlg::~CSupplierSearchDlg()
{
}

void CSupplierSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_NAME, m_cbName);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
}


BEGIN_MESSAGE_MAP(CSupplierSearchDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSupplierSearchDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSupplierSearchDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_NAME, &CSupplierSearchDlg::OnBnClickedCheckName)
END_MESSAGE_MAP()

BOOL CSupplierSearchDlg::OnInitDialog()
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

	m_cbName.SetCheck(TRUE);
	m_editName.SetFocus();

	if (m_csName != _T(""))
	{
		m_editName.SetWindowText(m_csName);
		m_editName.SetFocus();
	}

	return FALSE;
}

// CSupplierSearchDlg 消息处理程序


void CSupplierSearchDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();

	m_csName = _T("");
	if (m_cbName.GetCheck() == TRUE)
	{
		m_editName.GetWindowText(m_csName);
		m_csName.Trim();
	}
}


void CSupplierSearchDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CSupplierSearchDlg::OnBnClickedCheckName()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_cbName.GetCheck() == TRUE)
	{
		m_editName.EnableWindow(TRUE);
		m_editName.SetFocus();
	}
	else
	{
		m_editName.EnableWindow(FALSE);
	}
}

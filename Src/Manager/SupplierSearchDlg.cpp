// SupplierSearchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "SupplierSearchDlg.h"
#include "afxdialogex.h"


// CSupplierSearchDlg �Ի���

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

// CSupplierSearchDlg ��Ϣ�������


void CSupplierSearchDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CSupplierSearchDlg::OnBnClickedCheckName()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

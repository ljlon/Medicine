// VendorSearchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "VendorSearchDlg.h"
#include "afxdialogex.h"


// CVendorSearchDlg �Ի���

IMPLEMENT_DYNAMIC(CVendorSearchDlg, CDialogEx)

CVendorSearchDlg::CVendorSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVendorSearchDlg::IDD, pParent)
{

}

CVendorSearchDlg::~CVendorSearchDlg()
{
}

void CVendorSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_NAME, m_cbName);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
}


BEGIN_MESSAGE_MAP(CVendorSearchDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CVendorSearchDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CVendorSearchDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_NAME, &CVendorSearchDlg::OnBnClickedCheckName)
END_MESSAGE_MAP()


BOOL CVendorSearchDlg::OnInitDialog()
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

// CVendorSearchDlg ��Ϣ�������


void CVendorSearchDlg::OnBnClickedOk()
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


void CVendorSearchDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CVendorSearchDlg::OnBnClickedCheckName()
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

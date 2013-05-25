// InputBatchNum.cpp : implementation file
//

#include "stdafx.h"
#include "POS.h"
#include "BatchNumDlg.h"
#include "afxdialogex.h"


// CInputBatchNum dialog

IMPLEMENT_DYNAMIC(CBatchNumDlg, CDialogEx)

CBatchNumDlg::CBatchNumDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBatchNumDlg::IDD, pParent)
{

}

CBatchNumDlg::~CBatchNumDlg()
{
}

void CBatchNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_BATCHNUM, m_editBatchNum);
}


BEGIN_MESSAGE_MAP(CBatchNumDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CBatchNumDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;
}

// CBatchNumDlg message handlers
void CBatchNumDlg::OnOK()
{
	CDialogEx::OnOK();
	
	m_editBatchNum.GetWindowText(m_csBatchNum);
	m_csBatchNum.Trim();
}
// CfgGeneralDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "CfgGeneralDlg.h"
#include "afxdialogex.h"


// CCfgGeneralDlg 对话框

IMPLEMENT_DYNAMIC(CCfgGeneralDlg, CDialogEx)

CCfgGeneralDlg::CCfgGeneralDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCfgGeneralDlg::IDD, pParent)
{

}

CCfgGeneralDlg::~CCfgGeneralDlg()
{
}

void CCfgGeneralDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FONT, m_editFontName);
	DDX_Control(pDX, IDC_EDIT_FONT_HEIGHT, m_editFontHeight);
}


BEGIN_MESSAGE_MAP(CCfgGeneralDlg, CDialogEx)
END_MESSAGE_MAP()


BOOL CCfgGeneralDlg::OnInitDialog()
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

	CString csMsg;
	csMsg.Format(_T("%d"), g_MgrCfg.theme_font_height);
	m_editFontHeight.SetWindowText(csMsg);

	m_editFontName.SetWindowText(g_MgrCfg.theme_font_name);

	return TRUE;
}

// CCfgGeneralDlg 消息处理程序
ERRCODE CCfgGeneralDlg::ApplyCfg(MgrConfig &config)
{
	ERRCODE errRet = err_OK;

	CString csMsg;

	m_editFontName.GetWindowText(csMsg);
	if (csMsg != _T(""))
	{
		config.theme_font_name = csMsg;
	}

	m_editFontHeight.GetWindowText(csMsg);
	csMsg.Trim();
	if (csMsg != _T(""))
	{
		config.theme_font_height = atol(csMsg.GetBuffer());
	}


	return errRet;
}

// CCfgGeneralDlg 消息处理程序

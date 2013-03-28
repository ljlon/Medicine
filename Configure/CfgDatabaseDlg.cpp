// CfgDatabaseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Configure.h"
#include "CfgDatabaseDlg.h"
#include "afxdialogex.h"
#include "Config.h"

// CCfgDatabaseDlg 对话框

IMPLEMENT_DYNAMIC(CCfgDatabaseDlg, CDialogEx)

CCfgDatabaseDlg::CCfgDatabaseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCfgDatabaseDlg::IDD, pParent)
{

}

CCfgDatabaseDlg::~CCfgDatabaseDlg()
{
}

void CCfgDatabaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbHost);
	DDX_Control(pDX, IDC_EDIT1, m_editPort);
	DDX_Control(pDX, IDC_EDIT2, m_editDBName);
	DDX_Control(pDX, IDC_EDIT3, m_editUID);
	DDX_Control(pDX, IDC_EDIT4, m_editPWD);
}


BEGIN_MESSAGE_MAP(CCfgDatabaseDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CCfgDatabaseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString csMsg;
	m_cbHost.SetWindowText(g_config.database_host);
	csMsg.Format(_T("%d"), g_config.database_port);
	m_editPort.SetWindowText(csMsg);
	m_editDBName.SetWindowText(g_config.database_dbname);
	m_editUID.SetWindowText(g_config.database_uid);
	m_editPWD.SetWindowText(g_config.database_pwd);
	
	return TRUE;
}

// CCfgDatabaseDlg 消息处理程序

ERRCODE CCfgDatabaseDlg::ApplyCfg(Config &config)
{
	ERRCODE errRet = err_OK;

	CString csHost, csPort, csDBName, csUID, csPWD;
	m_cbHost.GetWindowText(csHost);
	csHost.Trim();
	if (csHost == _T(""))
	{
		MessageBox(_T("主机不能为空！"), _T(""), MB_ICONERROR);
		return err_InvalidParameter;
	}

	m_editPort.GetWindowText(csPort);
	csPort.Trim();
	if (csPort == _T(""))
	{
		MessageBox(_T("端口不能为空！"), _T(""), MB_ICONERROR);
		return err_InvalidParameter;
	}

	m_editDBName.GetWindowText(csDBName);
	csDBName.Trim();
	if (csDBName == _T(""))
	{
		MessageBox(_T("数据库名称不能为空！"), _T(""), MB_ICONERROR);
		return err_InvalidParameter;
	}

	m_editUID.GetWindowText(csUID);
	csUID.Trim();
	if (csUID == _T(""))
	{
		MessageBox(_T("数据库账户不能为空！"), _T(""), MB_ICONERROR);
		return err_InvalidParameter;
	}

	m_editPWD.GetWindowText(csPWD);
	csPWD.Trim();
	if (csPWD == _T(""))
	{
		MessageBox(_T("密码不能为空！"), _T(""), MB_ICONERROR);
		return err_InvalidParameter;
	}

	config.database_host = csHost;
	config.database_port = atoi(csPort);
	config.database_dbname = csDBName;
	config.database_uid = csUID;
	config.database_pwd = csPWD;

	return errRet;
}
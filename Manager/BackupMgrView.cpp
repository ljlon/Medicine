// BackupMgrView.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "BackupMgrView.h"
#include "Config.h"
#include "MySQLBackup.h"

// CBackupMgrView

IMPLEMENT_DYNCREATE(CBackupMgrView, CFormView)

CBackupMgrView::CBackupMgrView()
	: CFormView(CBackupMgrView::IDD)
{

}

CBackupMgrView::~CBackupMgrView()
{
}

void CBackupMgrView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBackupMgrView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_BACKUP, &CBackupMgrView::OnBnClickedButtonBackup)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE, &CBackupMgrView::OnBnClickedButtonRestore)
END_MESSAGE_MAP()


// CBackupMgrView 诊断

#ifdef _DEBUG
void CBackupMgrView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBackupMgrView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBackupMgrView 消息处理程序


void CBackupMgrView::OnBnClickedButtonBackup()
{
	// TODO: 在此添加控件通知处理程序代码

	CMySQLBackup backup;
	ERRCODE errRet = backup.Backup(_T("C:\\Program Files (x86)\\MySQL\\MySQL Server 5.5"),
		g_config.database_host.GetBuffer(),
		g_config.database_port,
		g_config.database_uid.GetBuffer(),
		g_config.database_pwd.GetBuffer(),
		g_config.database_dbname.GetBuffer(),
		_T("Backup\\Backup.sql"));

	if (errRet != err_OK)
	{
		MessageBox(_T("备份数据库失败！"), _T("数据安全"), MB_ICONERROR);
		return;
	}

	MessageBox(_T("备份数据库成功！"), _T("数据安全"), MB_ICONINFORMATION);
}


void CBackupMgrView::OnBnClickedButtonRestore()
{
	// TODO: 在此添加控件通知处理程序代码
}

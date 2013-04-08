// BackupMgrView.cpp : ʵ���ļ�
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


// CBackupMgrView ���

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


// CBackupMgrView ��Ϣ�������


void CBackupMgrView::OnBnClickedButtonBackup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
		MessageBox(_T("�������ݿ�ʧ�ܣ�"), _T("���ݰ�ȫ"), MB_ICONERROR);
		return;
	}

	MessageBox(_T("�������ݿ�ɹ���"), _T("���ݰ�ȫ"), MB_ICONINFORMATION);
}


void CBackupMgrView::OnBnClickedButtonRestore()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

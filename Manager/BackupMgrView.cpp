// BackupMgrView.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "BackupMgrView.h"
#include "MgrConfig.h"
#include "BackupMgr.h"

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
	DDX_Control(pDX, IDC_CHECK_AUTO_BACKUP, m_cbAutoBackup);
	DDX_Control(pDX, IDC_EDIT_BACKUP_DATE, m_editAutoDate);
	DDX_Control(pDX, IDC_COMBO_BACKUP_DATE_UNIT, m_comboAutoDateUnit);
	DDX_Control(pDX, IDC_COMBO_BACKUP_TIME, m_comboAutoTime);
	DDX_Control(pDX, IDC_STATIC_BACKUP_INFO, m_staticBackupInfo);
}

BEGIN_MESSAGE_MAP(CBackupMgrView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_BACKUP, &CBackupMgrView::OnBnClickedButtonBackup)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE, &CBackupMgrView::OnBnClickedButtonRestore)
END_MESSAGE_MAP()


void CBackupMgrView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CString csMsg;
	csMsg.Format("%s-%s", APP_NAME, APP_MANAGER);
	AfxGetApp()->GetMainWnd()->SetWindowText(csMsg);

	SYSTEMTIME lastBackupTime;
	if (g_backupMgr.GetLastBackupTime(lastBackupTime) == TRUE)
	{
		csMsg.Format(_T("最后一次备份时间：%04d年%02d月%02d日 %02d:%02d:%02d"), 
			lastBackupTime.wYear,
			lastBackupTime.wMonth,
			lastBackupTime.wDay,
			lastBackupTime.wHour,
			lastBackupTime.wMinute,
			lastBackupTime.wSecond);
	}
	else
	{
		csMsg = _T("");
	}
	m_staticBackupInfo.SetWindowText(csMsg);

	if (g_MgrCfg.backup_auto == 0)
	{
		m_cbAutoBackup.SetCheck(0);
	}
	else
	{
		m_cbAutoBackup.SetCheck(1);
	}

	csMsg.Format(_T("%d"), g_MgrCfg.backup_auto_date);
	m_editAutoDate.SetWindowText(csMsg);

	m_comboAutoDateUnit.AddString(_T("天"));
	m_comboAutoDateUnit.AddString(_T("周"));
	m_comboAutoDateUnit.AddString(_T("月"));
	m_comboAutoDateUnit.SetCurSel(g_MgrCfg.backup_auto_date_unit);

	for (int i = 0; i < 24; i++)
	{
		csMsg.Format(_T("%d:00"), i);
		m_comboAutoTime.AddString(csMsg);
	}
	m_comboAutoTime.SetCurSel(g_MgrCfg.backup_auto_time);
}


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


void CBackupMgrView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CBackupMgrView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	int iHeight;
	CRect rectClient;
	GetClientRect(rectClient);

	CRect staticGroupManuRect;
	CStatic *pStaticGroupManu = (CStatic*)GetDlgItem(IDC_STATIC_GROUP_MANU);
	if (pStaticGroupManu->GetSafeHwnd() != NULL)
	{
		pStaticGroupManu->GetClientRect(staticGroupManuRect);
		iHeight = staticGroupManuRect.Height();
		staticGroupManuRect.left = rectClient.left + 5;
		staticGroupManuRect.top = rectClient.top + 10;
		staticGroupManuRect.right = rectClient.right - 5;
		staticGroupManuRect.bottom = staticGroupManuRect.top + iHeight;
		pStaticGroupManu->SetWindowPos(NULL, staticGroupManuRect.left, staticGroupManuRect.top, staticGroupManuRect.Width(), staticGroupManuRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect staticGroupAutoRect;
	CStatic *pStaticGroupAuto = (CStatic*)GetDlgItem(IDC_STATIC_GROUP_AUTO);
	if (pStaticGroupAuto->GetSafeHwnd() != NULL)
	{
		pStaticGroupAuto->GetClientRect(staticGroupAutoRect);
		iHeight = staticGroupAutoRect.Height();
		staticGroupAutoRect.left = staticGroupManuRect.left;
		staticGroupAutoRect.top = staticGroupManuRect.bottom + 15;
		staticGroupAutoRect.right = staticGroupManuRect.right;
		staticGroupAutoRect.bottom = staticGroupAutoRect.top + iHeight;
		pStaticGroupAuto->SetWindowPos(NULL, staticGroupAutoRect.left, staticGroupAutoRect.top, staticGroupAutoRect.Width(), staticGroupAutoRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}
}


void CBackupMgrView::OnBnClickedButtonBackup()
{
	// TODO: 在此添加控件通知处理程序代码
	ERRCODE errRet = g_backupMgr.PushJob();
	if (errRet != err_OK)
	{
		MessageBox(_T("备份数据库失败！"), _T("数据安全"), MB_ICONERROR);
		return;
	}

	CString csMsg;
	SYSTEMTIME lastBackupTime;
	if (g_backupMgr.GetLastBackupTime(lastBackupTime) == TRUE)
	{
		csMsg.Format(_T("最后一次备份时间：%04d年%02d月%02d日 %02d:%02d:%02d"), 
			lastBackupTime.wYear,
			lastBackupTime.wMonth,
			lastBackupTime.wDay,
			lastBackupTime.wHour,
			lastBackupTime.wMinute,
			lastBackupTime.wSecond);
	}
	else
	{
		csMsg = _T("");
	}
	m_staticBackupInfo.SetWindowText(csMsg);

	MessageBox(_T("备份数据库成功！"), _T("数据安全"), MB_ICONINFORMATION);
}


void CBackupMgrView::OnBnClickedButtonRestore()
{
	// TODO: 在此添加控件通知处理程序代码
}

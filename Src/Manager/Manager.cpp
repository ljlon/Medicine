
// Manager.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Manager.h"
#include "MainFrm.h"
#include "LoginDlg.h"
#include "Database.h"
#include "Version.h"
#include "ManagerDoc.h"
#include "ManagerView.h"
#include "MgrConfig.h"
#include "BackupMgr.h"
#include "CfgDlg.h"
#include "Theme.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CManagerApp

BEGIN_MESSAGE_MAP(CManagerApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CManagerApp::OnAppAbout)
	ON_COMMAND(ID_APP_CFG, &CManagerApp::OnAppCfg)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CManagerApp ����

CManagerApp::CManagerApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Manager.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CManagerApp ����

CManagerApp theApp;


// CManagerApp ��ʼ��

BOOL CManagerApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	//���������в���
	BOOL bConsole = FALSE;
	if (__argc >= 2)
	{
		if (!strcmp(__argv[1], _T("-console")))
		{
			bConsole = TRUE;
		}
	}

	//�����Ƿ�����Ѵ�ʵ��
	HANDLE hEvent = CreateEvent(NULL,FALSE,FALSE,_T("������ҽҩ����ϵͳ-��̨����.exe"));
	if(hEvent != INVALID_HANDLE_VALUE)
	{
		if(ERROR_ALREADY_EXISTS==GetLastError())
		{
			if (bConsole == TRUE)
			{
				return FALSE;
			}

			CString csMsg;
			csMsg.Format("%s-%s", APP_NAME, APP_MANAGER);
			HWND hwnd = ::FindWindow(NULL, csMsg);
			if (hwnd != NULL) 
			{
				// Another Instance is already running.
				::ShowWindow(hwnd, SW_SHOWMAXIMIZED);
				::UpdateWindow(hwnd);
				::SetForegroundWindow(hwnd);
				return FALSE;
			}
			csMsg.Format("%s-��½", APP_MANAGER);
			hwnd = ::FindWindow(NULL, csMsg);
			if (hwnd != NULL) 
			{
				// Another Instance is already running.
				::SendMessage(hwnd, LOGINDLG_SHOWWINDOW, 0, 0);
				::ShowWindow(hwnd, SW_SHOW);
				::UpdateWindow(hwnd);
				::SetForegroundWindow(hwnd);
				return FALSE;
			}

			return FALSE;
		}
	}

	//�Զ����ʼ��
	ERRCODE errRet = err_OK;
	CString csMsg;

	errRet = g_log.Init(_T("Manager.log"));
	if (errRet)
	{
		return FALSE;
	}

	VS_FIXEDFILEINFO *pFileVersion = g_version.GetVersionInfo(_T("Manager.exe"));
	csMsg.Format(_T("%s v%d.%d.%d.%d %s"), 
		_T("Manager.exe"), 
		HIWORD(pFileVersion->dwProductVersionMS), 
		LOWORD(pFileVersion->dwProductVersionMS),
		HIWORD(pFileVersion->dwProductVersionLS), 
		LOWORD(pFileVersion->dwProductVersionLS), 
		_T(" by Jinlong Liu."));
	g_log.Write(csMsg);

	//��ȡȫ��������Ϣ
	errRet = g_config.Load();
	if (errRet)
	{
		g_log.Write(_T("Load config fail"), errRet);
		return FALSE;
	}

	CLoginDlg loginDlg;
	BOOL bAuthorized = FALSE;
	while(TRUE)
	{
		//��ȡManager������Ϣ
		errRet = g_MgrCfg.Load();
		if (errRet)
		{
			g_log.Write(_T("Load MgrConfig fail"), errRet);
			return FALSE;
		}

		g_theme.Init(g_MgrCfg.theme_font_name.GetBuffer(), g_MgrCfg.theme_font_height);

		//����ģ��
		errRet = g_backupMgr.Start(g_MgrCfg.mysql_install_folder.GetBuffer(),
									g_config.database_host.GetBuffer(),
									g_config.database_port,
									g_config.database_uid.GetBuffer(),
									g_config.database_pwd.GetBuffer(),
									g_config.database_dbname.GetBuffer(),
									g_MgrCfg.backup_auto,
									g_MgrCfg.backup_auto_date,
									g_MgrCfg.backup_auto_date_unit,
									g_MgrCfg.backup_auto_time);
		if (errRet != err_OK)
		{
			g_log.Write(_T("Start backupMgr fail"), errRet);
			return FALSE;
		}

		//�Ƿ���Ȩ��½
		if (bAuthorized == TRUE)
		{
			break;
		}

		//��½����
		if (bConsole == TRUE)
		{
			loginDlg.SetShowWindow(SW_HIDE);
		}
	    INT_PTR nResponse = loginDlg.DoModal();
		if (nResponse == IDOK)
		{
			bAuthorized = TRUE;
			theApp.m_curUser = loginDlg.m_curUser;
		}
		else if (nResponse == IDCANCEL)
		{
			loginDlg.SetShowWindow(SW_HIDE);
		}
	}

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate = NULL;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CManagerDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CManagerView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	csMsg.Format("%s-%s", APP_NAME, APP_MANAGER);
	m_pMainWnd->SetWindowText(csMsg);
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	return TRUE;
}

int CManagerApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	g_backupMgr.Stop();

	return CWinAppEx::ExitInstance();
}

// CManagerApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString csMsg;
	csMsg.Format("���� %s", APP_NAME);
	SetWindowText(csMsg);

	VS_FIXEDFILEINFO *pFileVersion = g_version.GetVersionInfo(_T("Manager.exe"));
	csMsg.Format(_T("%s-%s\r�汾��%d.%d.%d.%d\r%s\r%s"), 
		APP_NAME, 
		APP_MANAGER,
		HIWORD(pFileVersion->dwProductVersionMS), 
		LOWORD(pFileVersion->dwProductVersionMS),
		HIWORD(pFileVersion->dwProductVersionLS), 
		LOWORD(pFileVersion->dwProductVersionLS), 
		_T("by Jinlong Liu"),
		_T("Copyright (C) 2012"));
	SetDlgItemText(IDC_STATIC_APP, csMsg);

	return FALSE;
}

// �������жԻ����Ӧ�ó�������
void CManagerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CManagerApp::OnAppCfg()
{
	CCfgDlg cfgDlg;
	cfgDlg.DoModal();

	g_theme.Init(g_MgrCfg.theme_font_name.GetBuffer(), g_MgrCfg.theme_font_height);
}

// CManagerApp �Զ������/���淽��

void CManagerApp::PreLoadState()
{

}

void CManagerApp::LoadCustomState()
{
}

void CManagerApp::SaveCustomState()
{
}

// CManagerApp ��Ϣ�������




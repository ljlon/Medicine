
// Manager.cpp : 定义应用程序的类行为。
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
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CManagerApp 构造

CManagerApp::CManagerApp()
{
	m_bHiColorIcons = TRUE;

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Manager.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CManagerApp 对象

CManagerApp theApp;


// CManagerApp 初始化

BOOL CManagerApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	//分析命令行参数
	BOOL bConsole = FALSE;
	if (__argc >= 2)
	{
		if (!strcmp(__argv[1], _T("-console")))
		{
			bConsole = TRUE;
		}
	}

	//查找是否存在已打开实例
	HANDLE hEvent = CreateEvent(NULL,FALSE,FALSE,_T("福瑞堂医药管理系统-后台管理.exe"));
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
			csMsg.Format("%s-登陆", APP_MANAGER);
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

	//自定义初始化
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

	//读取全局配置信息
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
		//读取Manager配置信息
		errRet = g_MgrCfg.Load();
		if (errRet)
		{
			g_log.Write(_T("Load MgrConfig fail"), errRet);
			return FALSE;
		}

		g_theme.Init(g_MgrCfg.theme_font_name.GetBuffer(), g_MgrCfg.theme_font_height);

		//备份模块
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

		//是否授权登陆
		if (bAuthorized == TRUE)
		{
			break;
		}

		//登陆界面
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

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate = NULL;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CManagerDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CManagerView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	csMsg.Format("%s-%s", APP_NAME, APP_MANAGER);
	m_pMainWnd->SetWindowText(csMsg);
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生
	return TRUE;
}

int CManagerApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	g_backupMgr.Stop();

	return CWinAppEx::ExitInstance();
}

// CManagerApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

// 实现
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
	csMsg.Format("关于 %s", APP_NAME);
	SetWindowText(csMsg);

	VS_FIXEDFILEINFO *pFileVersion = g_version.GetVersionInfo(_T("Manager.exe"));
	csMsg.Format(_T("%s-%s\r版本：%d.%d.%d.%d\r%s\r%s"), 
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

// 用于运行对话框的应用程序命令
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

// CManagerApp 自定义加载/保存方法

void CManagerApp::PreLoadState()
{

}

void CManagerApp::LoadCustomState()
{
}

void CManagerApp::SaveCustomState()
{
}

// CManagerApp 消息处理程序




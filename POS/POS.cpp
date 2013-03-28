
// POS.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "POS.h"
#include "POSDlg.h"
#include "LoginDlg.h"
#include "Config.h"
#include "PrintFormat.h"
#include "PrinterManager.h"
#include "Version.h"
#include "Adapter.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPOSApp

BEGIN_MESSAGE_MAP(CPOSApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPOSApp 构造

CPOSApp::CPOSApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CPOSApp 对象

CPOSApp theApp;


// CPOSApp 初始化

BOOL CPOSApp::InitInstance()
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

	CWinApp::InitInstance();


	AfxEnableControlContainer();


	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	ERRCODE errRet = err_OK;
	CString csMsg;
	BYTE pbyBuf[MAX_PATH];
	DWORD dwByteLen;

	//Init Log
	errRet = g_log.Init(_T("POS.log"));
	if (errRet)
	{
		return FALSE;
	}

	VS_FIXEDFILEINFO *pFileVersion = g_version.GetVersionInfo(_T("POS.exe"));
	csMsg.Format(_T("%s v%d.%d.%d.%d %s"), 
		_T("POS.exe"), 
		HIWORD(pFileVersion->dwProductVersionMS), 
		LOWORD(pFileVersion->dwProductVersionMS),
		HIWORD(pFileVersion->dwProductVersionLS), 
		LOWORD(pFileVersion->dwProductVersionLS), 
		_T(" by Jinlong Liu."));
	g_log.Write(csMsg);

	//Init Config
	errRet = g_config.Load();
	if (errRet)
	{
		csMsg.Format(_T("Load config fail with errCode=%d"), errRet);
		g_log.Write(csMsg);
		return FALSE;
	}

	//Init Printer Format
	errRet = g_printFormat.Load();
	if (errRet)
	{
		//return FALSE;
	}

	//Init POS Info
	CAdapter adapter;
	memset(pbyBuf, 0, MAX_PATH);
	dwByteLen = MAX_PATH;
	errRet = adapter.GetMacAddressByChar((CHAR*)pbyBuf, dwByteLen);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("Get mac address fail with errCode=%d"), errRet);
		g_log.Write(csMsg);
		return errRet;
	}
	CPOSDB POSDB;
	errRet = POSDB.GetPOS(LPTSTR(pbyBuf), &m_curPOS);
	if (errRet != err_OK)
	{
		m_curPOS.csPCMAC = LPTSTR(pbyBuf);
		errRet = POSDB.AddPOS(&m_curPOS);
		if (errRet != err_OK)
		{
			csMsg.Format(_T("Add POS fail with errCode=%d"), errRet);
			g_log.Write(csMsg);
			return errRet;
		}
		errRet = POSDB.GetPOS(LPTSTR(pbyBuf), &m_curPOS);
		if (errRet != err_OK)
		{
			csMsg.Format(_T("Get POS fail with errCode=%d"), errRet);
			g_log.Write(csMsg);
			return errRet;
		}
	}

	//登陆界面
	CLoginDlg loginDlg;
	INT_PTR nResponse = loginDlg.DoModal();
	if (nResponse == IDOK)
	{
		theApp.m_curUser = loginDlg.m_curUser;
	}
	else if (nResponse == IDCANCEL)
	{
		return FALSE;
	}

	CPOSDlg dlg;
	m_pMainWnd = &dlg;
	nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}


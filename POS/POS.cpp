
// POS.cpp : ����Ӧ�ó��������Ϊ��
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


// CPOSApp ����

CPOSApp::CPOSApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CPOSApp ����

CPOSApp theApp;


// CPOSApp ��ʼ��

BOOL CPOSApp::InitInstance()
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

	CWinApp::InitInstance();


	AfxEnableControlContainer();


	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

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

	//��½����
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
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}


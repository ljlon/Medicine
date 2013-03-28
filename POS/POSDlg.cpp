
// POSDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POS.h"
#include "POSDlg.h"
#include "afxdialogex.h"
#include "RetailDlg.h"
#include "CfgDlg.h"
#include "LoginDlg.h"
#include "AccountMgrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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

	VS_FIXEDFILEINFO *pFileVersion = g_version.GetVersionInfo(_T("POS.exe"));
	csMsg.Format(_T("%s-%s\r版本：%d.%d.%d.%d\r%s\r%s"), 
		APP_NAME, 
		APP_POS,
		HIWORD(pFileVersion->dwProductVersionMS), 
		LOWORD(pFileVersion->dwProductVersionMS),
		HIWORD(pFileVersion->dwProductVersionLS), 
		LOWORD(pFileVersion->dwProductVersionLS), 
		_T("by Jinlong Liu"),
		_T("Copyright (C) 2012"));
	SetDlgItemText(IDC_STATIC_APP, csMsg);

	return TRUE;
}

// CPOSDlg 对话框

CPOSDlg::CPOSDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPOSDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPOSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPOSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_APP_ABOUT, &CPOSDlg::OnBnClickedBtnHelp)
	ON_BN_CLICKED(IDC_BTN_CFG, &CPOSDlg::OnBnClickedBtnCfg)
	ON_BN_CLICKED(IDC_BTN_SALE, &CPOSDlg::OnBnClickedBtnSale)
	ON_BN_CLICKED(IDC_BTN_HISTORY, &CPOSDlg::OnBnClickedBtnHistory)
	ON_BN_CLICKED(IDC_BTN_ACCOUNT, &CPOSDlg::OnBnClickedBtnAccount)
END_MESSAGE_MAP()


// CPOSDlg 消息处理程序

BOOL CPOSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString csMsg;
	csMsg.Format(_T("%s-%s"), APP_NAME, APP_POS);
	SetWindowText(csMsg);

	CMenu sysMenu;
	sysMenu.LoadMenu(IDR_MAINFRAME);
	SetMenu(&sysMenu);

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);			// 设置小图标

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

int CPOSDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 基于持久值设置视觉管理器和样式
	//CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
	//CDockingManager::SetDockingMode(DT_SMART);

	return 0;
}

void CPOSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPOSDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPOSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPOSDlg::OnBnClickedBtnCfg()
{
	// TODO: 在此添加控件通知处理程序代码

	CLoginDlg loginDlg;
	loginDlg.SetWelcomeMsg(_T("请使用管理员帐户登陆"));
	loginDlg.SetAllowUserRole(Role_Supper);
	loginDlg.AddAllowUserRole(Role_Manager);
	if (IDOK != loginDlg.DoModal())
	{
		return;
	}

	CCfgDlg cfgDlg;
	cfgDlg.DoModal();
}


void CPOSDlg::OnBnClickedBtnSale()
{
	// TODO: 在此添加控件通知处理程序代码

	CRetailDlg retailDlg;
	ERRCODE errRet = retailDlg.Init();
	if (g_config.factory_mode != 0 && errRet != err_OK)
	{
		return;
	}

	retailDlg.DoModal();
}


void CPOSDlg::OnBnClickedBtnHelp()
{
	// TODO: 在此添加控件通知处理程序代码

	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


void CPOSDlg::OnBnClickedBtnHistory()
{
	// TODO: Add your control notification handler code here

	m_retailListDlg.DoModal();
}


void CPOSDlg::OnBnClickedBtnAccount()
{
	// TODO: Add your control notification handler code here
	CAccountMgrDlg accountMgrDlg;
	accountMgrDlg.DoModal();
}

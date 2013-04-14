
// ConfigureDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Configure.h"
#include "ConfigureDlg.h"
#include "afxdialogex.h"

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


// CConfigureDlg 对话框

CConfigureDlg::CConfigureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfigureDlg::IDD, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pCfgDatabaseDlg = NULL;
}

CConfigureDlg::~CConfigureDlg()
{
	if (m_pCfgDatabaseDlg != NULL)
	{
		delete m_pCfgDatabaseDlg;
		m_pCfgDatabaseDlg = NULL;
	}
}

void CConfigureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_VIEW, m_staticView);
}

BEGIN_MESSAGE_MAP(CConfigureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CConfigureDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CConfigureDlg 消息处理程序

BOOL CConfigureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString csMsg;
	csMsg.Format(_T("%s-%s"), APP_NAME, APP_CONFIGURE);
	SetWindowText(csMsg);

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	//SetIcon(m_hIcon, TRUE);			// 设置大图标
	//SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CRect rect;
	m_staticView.GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_pCfgDatabaseDlg = new CCfgDatabaseDlg;
	m_pCfgDatabaseDlg->Create(CCfgDatabaseDlg::IDD, this);
	m_pCfgDatabaseDlg->MoveWindow(&rect);
	m_pCfgDatabaseDlg->ShowWindow(SW_SHOW);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CConfigureDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CConfigureDlg::OnPaint()
{
	CRect rect;
	m_staticView.GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_pCfgDatabaseDlg->MoveWindow(&rect);
	m_pCfgDatabaseDlg->ShowWindow(SW_SHOW);
}

void CConfigureDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	OnPaint();
}

void CConfigureDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CConfigureDlg::OnQueryDragIcon()
{
	//return static_cast<HCURSOR>(m_hIcon);
	return CDialogEx::OnQueryDragIcon();
}

void CConfigureDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	ERRCODE errRet = err_OK;
	Config tempConfig = g_config;

	if (m_pCfgDatabaseDlg != NULL)
	{
		errRet = m_pCfgDatabaseDlg->ApplyCfg(tempConfig);
		if (errRet != err_OK)
		{
			MessageBox(_T("保存数据库配置失败"), _T(""), MB_ICONERROR);
			return;
		}
	}

	g_config = tempConfig;
	errRet = g_config.Save();
	if (errRet != err_OK)
	{
		MessageBox(_T("保存配置失败"), _T(""), MB_ICONERROR);
		return;
	}

	CDialogEx::OnOK();
}

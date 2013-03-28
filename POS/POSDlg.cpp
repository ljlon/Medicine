
// POSDlg.cpp : ʵ���ļ�
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

	VS_FIXEDFILEINFO *pFileVersion = g_version.GetVersionInfo(_T("POS.exe"));
	csMsg.Format(_T("%s-%s\r�汾��%d.%d.%d.%d\r%s\r%s"), 
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

// CPOSDlg �Ի���

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


// CPOSDlg ��Ϣ�������

BOOL CPOSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString csMsg;
	csMsg.Format(_T("%s-%s"), APP_NAME, APP_POS);
	SetWindowText(csMsg);

	CMenu sysMenu;
	sysMenu.LoadMenu(IDR_MAINFRAME);
	SetMenu(&sysMenu);

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);			// ����Сͼ��

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

int CPOSDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ���ڳ־�ֵ�����Ӿ�����������ʽ
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPOSDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPOSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPOSDlg::OnBnClickedBtnCfg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CLoginDlg loginDlg;
	loginDlg.SetWelcomeMsg(_T("��ʹ�ù���Ա�ʻ���½"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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


// ConfigureDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Configure.h"
#include "ConfigureDlg.h"
#include "afxdialogex.h"

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


// CConfigureDlg �Ի���

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


// CConfigureDlg ��Ϣ�������

BOOL CConfigureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString csMsg;
	csMsg.Format(_T("%s-%s"), APP_NAME, APP_CONFIGURE);
	SetWindowText(csMsg);

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	//SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	//SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CRect rect;
	m_staticView.GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_pCfgDatabaseDlg = new CCfgDatabaseDlg;
	m_pCfgDatabaseDlg->Create(CCfgDatabaseDlg::IDD, this);
	m_pCfgDatabaseDlg->MoveWindow(&rect);
	m_pCfgDatabaseDlg->ShowWindow(SW_SHOW);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CConfigureDlg::OnQueryDragIcon()
{
	//return static_cast<HCURSOR>(m_hIcon);
	return CDialogEx::OnQueryDragIcon();
}

void CConfigureDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	ERRCODE errRet = err_OK;
	Config tempConfig = g_config;

	if (m_pCfgDatabaseDlg != NULL)
	{
		errRet = m_pCfgDatabaseDlg->ApplyCfg(tempConfig);
		if (errRet != err_OK)
		{
			MessageBox(_T("�������ݿ�����ʧ��"), _T(""), MB_ICONERROR);
			return;
		}
	}

	g_config = tempConfig;
	errRet = g_config.Save();
	if (errRet != err_OK)
	{
		MessageBox(_T("��������ʧ��"), _T(""), MB_ICONERROR);
		return;
	}

	CDialogEx::OnOK();
}

// CustomerDisplayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "POS.h"
#include "CfgCustomerDisplayDlg.h"
#include "afxdialogex.h"
#include "DeviceManager.h"

// CCustomerDisplayDlg dialog

IMPLEMENT_DYNAMIC(CCfgCustomerDisplayDlg, CDialogEx)

CCfgCustomerDisplayDlg::CCfgCustomerDisplayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCfgCustomerDisplayDlg::IDD, pParent)
{
	m_iSelCustomerDisplayIdx = -1;
}

CCfgCustomerDisplayDlg::~CCfgCustomerDisplayDlg()
{
}

void CCfgCustomerDisplayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COM, m_cbCom);
}


BEGIN_MESSAGE_MAP(CCfgCustomerDisplayDlg, CDialogEx)
	ON_CBN_DROPDOWN(IDC_COMBO_COM, &CCfgCustomerDisplayDlg::OnCbnDropdownComboCom)
	ON_CBN_SELCHANGE(IDC_COMBO_COM, &CCfgCustomerDisplayDlg::OnCbnSelchangeComboCom)
	ON_CBN_CLOSEUP(IDC_COMBO_COM, &CCfgCustomerDisplayDlg::OnCbnCloseupComboCom)
END_MESSAGE_MAP()

BOOL CCfgCustomerDisplayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_vctAllCustomerDisplay.resize(1);
	m_vctAllCustomerDisplay[0] = g_config.customerdispay_name;
	m_iSelCustomerDisplayIdx = 0;
	m_cbCom.AddString(m_vctAllCustomerDisplay[0]);
	m_cbCom.SetCurSel(0);

	return TRUE;
}

ERRCODE CCfgCustomerDisplayDlg::ApplyCfg(Config &config)
{
	ERRCODE errRet = err_OK;

	if (m_iSelCustomerDisplayIdx < 0 || m_iSelCustomerDisplayIdx >= (int)m_vctAllCustomerDisplay.size())
	{
		config.customerdispay_name = _T("");
	}
	else
	{
		config.customerdispay_name = m_vctAllCustomerDisplay[m_iSelCustomerDisplayIdx];
	}

	return errRet;
}

// CCustomerDisplayDlg message handlers
void CCfgCustomerDisplayDlg::OnCbnDropdownComboCom()
{
	// TODO: Add your control notification handler code here
	ERRCODE errRet = err_OK;

	CString csPreSelName = _T("");
	if (m_iSelCustomerDisplayIdx != -1)
	{
		csPreSelName = m_vctAllCustomerDisplay[m_iSelCustomerDisplayIdx];
	}
	m_vctAllCustomerDisplay.clear();

	m_cbCom.ResetContent();

	vector<PORT_INFO*>* pVctAllPorts = g_deviceMgr.GetAllCOMPorts();
	if (pVctAllPorts == NULL || pVctAllPorts->size() == 0)
	{
		return;
	}

	for (unsigned int i = 0; i < pVctAllPorts->size(); i++)
	{
		m_vctAllCustomerDisplay.push_back(pVctAllPorts->at(i)->csPortName);
		m_cbCom.AddString(pVctAllPorts->at(i)->csPortName);
		if (csPreSelName != _T("") && csPreSelName == pVctAllPorts->at(i)->csPortName)
		{
			m_iSelCustomerDisplayIdx = i;
		}
	}
}

void CCfgCustomerDisplayDlg::OnCbnSelchangeComboCom()
{
	// TODO: Add your control notification handler code here
	int iSel = m_cbCom.GetCurSel();
	if (iSel != -1)
	{
		m_iSelCustomerDisplayIdx = iSel;
	}
}


void CCfgCustomerDisplayDlg::OnCbnCloseupComboCom()
{
	// TODO: Add your control notification handler code here
	int iSel = m_cbCom.GetCurSel();
	if (iSel == -1)
	{
		if (m_iSelCustomerDisplayIdx != -1)
		{
			m_cbCom.SetCurSel(m_iSelCustomerDisplayIdx);
		}
	}
}

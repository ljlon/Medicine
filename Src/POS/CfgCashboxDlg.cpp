// CfgCashboxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "POS.h"
#include "CfgCashboxDlg.h"
#include "afxdialogex.h"
#include "DeviceManager.h"

// CCfgCashboxDlg dialog


IMPLEMENT_DYNAMIC(CCfgCashboxDlg, CDialogEx)


CCfgCashboxDlg::CCfgCashboxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCfgCashboxDlg::IDD, pParent)
{
	m_iSelCashboxIdx = -1;
}


CCfgCashboxDlg::~CCfgCashboxDlg()
{

}


void CCfgCashboxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CASHBOX, m_cbCashbox);
}


BEGIN_MESSAGE_MAP(CCfgCashboxDlg, CDialogEx)
	ON_CBN_DROPDOWN(IDC_COMBO_CASHBOX, &CCfgCashboxDlg::OnCbnDropdownComboCashbox)
	ON_CBN_SELCHANGE(IDC_COMBO_CASHBOX, &CCfgCashboxDlg::OnCbnSelchangeComboCashbox)
	ON_CBN_CLOSEUP(IDC_COMBO_CASHBOX, &CCfgCashboxDlg::OnCbnCloseupComboCashbox)
END_MESSAGE_MAP()


BOOL CCfgCashboxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_vctAllCashbox.resize(1);
	m_vctAllCashbox[0] = g_POSCfg.cashbox_name;
	m_iSelCashboxIdx = 0;
	m_cbCashbox.AddString(m_vctAllCashbox[0]);
	m_cbCashbox.SetCurSel(0);

	return TRUE;
}


ERRCODE CCfgCashboxDlg::ApplyCfg(POSConfig &config)
{
	ERRCODE errRet = err_OK;

	if (m_iSelCashboxIdx < 0 || m_iSelCashboxIdx >= (int)m_vctAllCashbox.size())
	{
		config.cashbox_name = _T("");
	}
	else
	{
		config.cashbox_name = m_vctAllCashbox[m_iSelCashboxIdx];
	}

	return errRet;
}

// CCfgCashboxDlg message handlers


void CCfgCashboxDlg::OnCbnDropdownComboCashbox()
{
	// TODO: Add your control notification handler code here
	ERRCODE errRet = err_OK;

	CString csPreSelName = _T("");
	if (m_iSelCashboxIdx != -1)
	{
		csPreSelName = m_vctAllCashbox[m_iSelCashboxIdx];
	}
	m_vctAllCashbox.clear();

	m_cbCashbox.ResetContent();

	vector<PORT_INFO*>* pVctAllLPTPorts = g_deviceMgr.GetAllLPTPorts();
	if (pVctAllLPTPorts == NULL || pVctAllLPTPorts->size() == 0)
	{
		return;
	}

	for (unsigned int i = 0; i < pVctAllLPTPorts->size(); i++)
	{
		m_vctAllCashbox.push_back(pVctAllLPTPorts->at(i)->csPortName);
		m_cbCashbox.AddString(pVctAllLPTPorts->at(i)->csPortName);
		if (csPreSelName != _T("") && csPreSelName == pVctAllLPTPorts->at(i)->csPortName)
		{
			m_iSelCashboxIdx = i;
		}
	}
}


void CCfgCashboxDlg::OnCbnSelchangeComboCashbox()
{
	// TODO: Add your control notification handler code here
	int iSel = m_cbCashbox.GetCurSel();
	if (iSel != -1)
	{
		m_iSelCashboxIdx = iSel;
	}
}


void CCfgCashboxDlg::OnCbnCloseupComboCashbox()
{
	// TODO: Add your control notification handler code here
	int iSel = m_cbCashbox.GetCurSel();
	if (iSel == -1)
	{
		if (m_iSelCashboxIdx != -1)
		{
			m_cbCashbox.SetCurSel(m_iSelCashboxIdx);
		}
	}
}

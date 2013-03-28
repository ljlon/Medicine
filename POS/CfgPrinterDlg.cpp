// CfgPrinterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "POS.h"
#include "CfgPrinterDlg.h"
#include "afxdialogex.h"
#include "DeviceManager.h"
#include "CfgPrintFormatDlg.h"

// CCfgPrinterDlg dialog

IMPLEMENT_DYNAMIC(CCfgPrinterDlg, CDialogEx)

CCfgPrinterDlg::CCfgPrinterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCfgPrinterDlg::IDD, pParent)
{
	m_iSelPrinterIdx = -1;
}

CCfgPrinterDlg::~CCfgPrinterDlg()
{
	m_vctAllPrinters.clear();
}

void CCfgPrinterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_Printer, m_cmbPrinters);
}


BEGIN_MESSAGE_MAP(CCfgPrinterDlg, CDialogEx)
	ON_CBN_DROPDOWN(IDC_COMBO_Printer, &CCfgPrinterDlg::OnCbnDropdownComboPrinter)
	ON_CBN_SELCHANGE(IDC_COMBO_Printer, &CCfgPrinterDlg::OnCbnSelchangeComboPrinter)
	ON_CBN_CLOSEUP(IDC_COMBO_Printer, &CCfgPrinterDlg::OnCbnCloseupComboPrinter)
	ON_BN_CLICKED(IDC_BUTTON_PRINT_FORMAT, &CCfgPrinterDlg::OnBnClickedButtonPrintFormat)
END_MESSAGE_MAP()

BOOL CCfgPrinterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_vctAllPrinters.resize(1);
	m_vctAllPrinters[0].csPrinterName = g_config.printer_name;
	m_iSelPrinterIdx = 0;
	m_cmbPrinters.AddString(m_vctAllPrinters[0].csPrinterName);
	m_cmbPrinters.SetCurSel(0);

	return TRUE;
}

ERRCODE CCfgPrinterDlg::ApplyCfg(Config &config)
{
	ERRCODE errRet = err_OK;

	if (m_iSelPrinterIdx < 0 || m_iSelPrinterIdx >= (int)m_vctAllPrinters.size())
	{
		config.printer_name = _T("");
	}
	else
	{
		config.printer_name = m_vctAllPrinters[m_iSelPrinterIdx].csPrinterName;
	}
	
	return errRet;
}

// CCfgPrinterDlg message handlers


void CCfgPrinterDlg::OnCbnDropdownComboPrinter()
{
	// TODO: Add your control notification handler code here
	ERRCODE errRet = err_OK;
	CString csPreSelPrinterName = _T("");
	if (m_iSelPrinterIdx != -1)
	{
		csPreSelPrinterName = m_vctAllPrinters[m_iSelPrinterIdx].csPrinterName;
	}

	m_iSelPrinterIdx = -1;
	m_vctAllPrinters.clear();
	m_cmbPrinters.ResetContent();
	vector<PORT_INFO*>* pVctAllLPTPorts = g_deviceMgr.GetAllLPTPorts();
	if (pVctAllLPTPorts == NULL || pVctAllLPTPorts->size() == 0)
	{
		return;
	}

	m_vctAllPrinters.resize(pVctAllLPTPorts->size());
	for (unsigned int i = 0; i < pVctAllLPTPorts->size(); i++)
	{
		m_vctAllPrinters[i].csPrinterName = pVctAllLPTPorts->at(i)->csPortName;
		m_cmbPrinters.AddString(pVctAllLPTPorts->at(i)->csPortName);
		if (csPreSelPrinterName != _T("") && csPreSelPrinterName == pVctAllLPTPorts->at(i)->csPortName)
		{
			m_iSelPrinterIdx = i;
		}
	}
}


void CCfgPrinterDlg::OnCbnSelchangeComboPrinter()
{
	// TODO: Add your control notification handler code here
	int iSel = m_cmbPrinters.GetCurSel();
	if (iSel != -1)
	{
		m_iSelPrinterIdx = iSel;
	}
}

void CCfgPrinterDlg::OnCbnCloseupComboPrinter()
{
	// TODO: Add your control notification handler code here
	int iSel = m_cmbPrinters.GetCurSel();
	if (iSel == -1)
	{
		if (m_iSelPrinterIdx != -1)
		{
			m_cmbPrinters.SetCurSel(m_iSelPrinterIdx);
		}
	}
}


void CCfgPrinterDlg::OnBnClickedButtonPrintFormat()
{
	// TODO: Add your control notification handler code here

	CCfgPrintFormatDlg printFormatDlg;
	printFormatDlg.DoModal();
}

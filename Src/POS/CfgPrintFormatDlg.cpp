// CfgPrinterFormatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "POS.h"
#include "CfgPrintFormatDlg.h"
#include "afxdialogex.h"
#include "PrintFormat.h"
#include "POSConfig.h"

// CCfgPrinterFormatDlg dialog

IMPLEMENT_DYNAMIC(CCfgPrintFormatDlg, CDialogEx)

CCfgPrintFormatDlg::CCfgPrintFormatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCfgPrintFormatDlg::IDD, pParent)
{
	m_bDataChange = FALSE;
}

CCfgPrintFormatDlg::~CCfgPrintFormatDlg()
{
}

void CCfgPrintFormatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FORMAT, m_editText);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_staticText);
	DDX_Control(pDX, IDC_BUTTON_PRESEE, m_btnPresee);
}


BEGIN_MESSAGE_MAP(CCfgPrintFormatDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_EDIT_FORMAT, &CCfgPrintFormatDlg::OnEnChangeEditFormat)
	ON_EN_KILLFOCUS(IDC_EDIT_FORMAT, &CCfgPrintFormatDlg::OnEnKillfocusEditFormat)
	ON_BN_CLICKED(IDC_BUTTON_PRESEE, &CCfgPrintFormatDlg::OnBnClickedButtonPresee)
END_MESSAGE_MAP()


// CCfgPrinterFormatDlg message handlers
BOOL CCfgPrintFormatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(_T("�Զ����ӡ��ʽ"));

	ResizeDlg();

	if (g_printFormat.GetFormatStr() != NULL)
	{
		m_editText.SetWindowText(LPTSTR(g_printFormat.GetFormatStr()));
		m_staticText.SetWindowText(LPTSTR(g_printFormat.GetFormatStr()));
	}
	else
	{
		m_editText.SetWindowText(_T(""));
		m_staticText.SetWindowText(_T(""));
	}
	
	OnBnClickedButtonPresee();
	
	m_bDataChange = FALSE;

	return TRUE;
}

void CCfgPrintFormatDlg::OnClose()
{
	CString csMsg;
	m_editText.GetWindowText(csMsg);
	csMsg.TrimRight();
	
	if (m_bDataChange == TRUE)
	{
		if (IDOK == MessageBox(_T("�Ƿ񱣴�ô�ӡ��ʽ��"), _T(""), MB_OKCANCEL|MB_ICONQUESTION))
		{
			g_printFormat.SetFormatStr((BYTE*)csMsg.GetBuffer(), strlen(csMsg.GetBuffer()));
			g_printFormat.Save();
		}
	}

	CDialogEx::OnClose();
}

void CCfgPrintFormatDlg::ResizeDlg()
{
	int iWidthSpan = 10;

	int iPrintCharNum = (g_POSCfg.printer_width + 1) / g_POSCfg.printer_font_width;
	if (iPrintCharNum <= 0)
	{
		return;
	}
	iPrintCharNum += 2;

	BYTE *pTestBuf = new BYTE[iPrintCharNum + 1];
	memset(pTestBuf, 'T', iPrintCharNum + 1);
	pTestBuf[iPrintCharNum] = 0;

	CSize editSize(0,0), staticSize(0,0); 

	CDC *pdc = m_editText.GetDC();
	CFont *pOldFont=pdc->SelectObject(m_editText.GetFont()); 
	::GetTextExtentPoint32((HDC)pdc->m_hDC, (CHAR*)pTestBuf, iPrintCharNum, &editSize); 
	ReleaseDC(pdc);
	pdc = NULL;

	pdc = m_staticText.GetDC();
	pOldFont=pdc->SelectObject(m_staticText.GetFont()); 
	::GetTextExtentPoint32((HDC)pdc->m_hDC, (CHAR*)pTestBuf, iPrintCharNum, &staticSize); 
	ReleaseDC(pdc);
	pdc = NULL;

	delete pTestBuf;
	pTestBuf = NULL;

	//
	CRect rect, editRect, staticRect, btnRect; 

	this->GetWindowRect(rect); 
	m_staticText.GetWindowRect(staticRect);
	m_editText.GetWindowRect(editRect); 
	m_btnPresee.GetWindowRect(btnRect);

	rect.right=rect.left+editSize.cx + staticSize.cx + iWidthSpan * 3; 
	this->MoveWindow(rect);

	staticRect.left = rect.left + iWidthSpan;
	staticRect.right=staticRect.left+staticSize.cx; 

	editRect.left = staticRect.right + iWidthSpan;
	editRect.right=editRect.left+editSize.cx; 

	btnRect.left = editRect.left;
	btnRect.right = editRect.right;

	ScreenToClient(&staticRect); 
	m_staticText. MoveWindow(staticRect);

	ScreenToClient(&editRect); 
	m_editText. MoveWindow(editRect);

	ScreenToClient(&btnRect); 
	m_btnPresee. MoveWindow(btnRect);
}

void CCfgPrintFormatDlg::OnEnChangeEditFormat()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	m_bDataChange = TRUE;
}


void CCfgPrintFormatDlg::OnEnKillfocusEditFormat()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCfgPrintFormatDlg::OnBnClickedButtonPresee()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString csMsg;
	m_editText.GetWindowText(csMsg);
	csMsg.TrimRight();

	g_printFormat.SetFormatStr((BYTE*)csMsg.GetBuffer(), strlen(csMsg.GetBuffer()));

	BYTE pbyBuf[MAX_PATH];
	memset(pbyBuf, 0, MAX_PATH);
	DWORD dwBufSize = 0;
	
	PrintItem *pPrintItem = g_printFormat.GetPrintItemPtr();
	if (pPrintItem != NULL)
	{
		pPrintItem->csPOSNO = _T("1");
		pPrintItem->csNO = _T("0000000000");
		pPrintItem->csUID = _T("0001");
		CTime time = CTime::GetCurrentTime();
		pPrintItem->csDataTime = time.Format(_T("%Y/%m/%d %H:%M:%S"));
		pPrintItem->vctRetailItem.resize(3);
		pPrintItem->vctRetailItem[0].csName = _T("ʾ��ҩƷ1");
		pPrintItem->vctRetailItem[0].csSN = _T("YP88888888");
		pPrintItem->vctRetailItem[0].csBatchNum = _T("000000");
		pPrintItem->vctRetailItem[0].csSpec = _T("10g");
		pPrintItem->vctRetailItem[0].csNum = _T("10");
		pPrintItem->vctRetailItem[0].csPrice = _T("10");
		pPrintItem->vctRetailItem[0].csTotalPrice = _T("100");
		pPrintItem->vctRetailItem[1].csName = _T("ʾ��ҩƷ2");
		pPrintItem->vctRetailItem[1].csSpec = _T("10g");
		pPrintItem->vctRetailItem[1].csSN = _T("YP88888888");
		pPrintItem->vctRetailItem[1].csBatchNum = _T("000000");
		pPrintItem->vctRetailItem[1].csNum = _T("20");
		pPrintItem->vctRetailItem[1].csPrice = _T("20");
		pPrintItem->vctRetailItem[1].csTotalPrice = _T("400");
		pPrintItem->vctRetailItem[2].csName = _T("ʾ��ҩƷ3");
		pPrintItem->vctRetailItem[2].csSpec = _T("10g");
		pPrintItem->vctRetailItem[2].csSN = _T("YP88888888");
		pPrintItem->vctRetailItem[2].csBatchNum = _T("000000");
		pPrintItem->vctRetailItem[2].csNum = _T("30");
		pPrintItem->vctRetailItem[2].csPrice = _T("30");
		pPrintItem->vctRetailItem[2].csTotalPrice = _T("900");
		pPrintItem->csTotalPrice = _T("1200");
		pPrintItem->csTotalIn = _T("1200");
		pPrintItem->csTotalOut = _T("0");
	}

	DWORD dwRet = g_printFormat.GetPrintStrFirstLine(pbyBuf, &dwBufSize, MAX_PATH);
	pbyBuf[dwBufSize] = 0;
	csMsg = LPTSTR(pbyBuf);

	while(dwRet == err_OK && dwBufSize)
	{
		memset(pbyBuf, 0, MAX_PATH);
		dwRet = g_printFormat.GetPrintStrNextLine(pbyBuf, &dwBufSize, MAX_PATH);
		pbyBuf[dwBufSize] = 0;
		csMsg += LPTSTR(pbyBuf);
	}

	m_staticText.SetWindowText(csMsg);
}

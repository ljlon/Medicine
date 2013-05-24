// RetailItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "POSConfig.h"
#include "POS.h"
#include "RetailItemDlg.h"
#include "afxdialogex.h"
#include "PrintFormat.h"

// CRetailItemDlg dialog

IMPLEMENT_DYNAMIC(CRetailItemDlg, CDialogEx)

CRetailItemDlg::CRetailItemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRetailItemDlg::IDD, pParent)
{

}

CRetailItemDlg::~CRetailItemDlg()
{
}

void CRetailItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_staticRetaiItem);
}


BEGIN_MESSAGE_MAP(CRetailItemDlg, CDialogEx)
END_MESSAGE_MAP()


BOOL CRetailItemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ResizeDlg();

	CString csMsg;
	CRetailDB retailDB;
	vector<RetailItem*> vctRetailItem;
	ERRCODE errRet = retailDB.GetRetail(m_retail.csID.GetBuffer(), &m_retail);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取销售信息失败！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("销售管理"), MB_ICONERROR);
		return TRUE;
	}

	errRet = retailDB.GetRetailItems(m_retail.csID.GetBuffer(), vctRetailItem);
	if (errRet != err_OK)
	{
		for (unsigned int i = 0; i < vctRetailItem.size(); i++)
		{
			delete vctRetailItem[i];
			vctRetailItem[i] = NULL;
		}
		vctRetailItem.clear();

		csMsg.Format(_T("获取销售信息失败！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("销售管理"), MB_ICONERROR);
		return TRUE;
	}

	BYTE pbyBuf[MAX_PATH];
	memset(pbyBuf, 0, MAX_PATH);
	DWORD dwBufSize = 0;

	PrintItem *pPrintItem = g_printFormat.GetPrintItemPtr();
	if (pPrintItem != NULL)
	{
		pPrintItem->csPOSNO = m_retail.csPOSID;
		pPrintItem->csUID = theApp.m_curUser.csUID;
		pPrintItem->csNO = m_retail.csSN;
		CTime time = CTime::GetCurrentTime();
		pPrintItem->csDataTime = time.Format(_T("%Y/%m/%d %H:%M:%S"));
		if (vctRetailItem.size())
		{
			pPrintItem->vctRetailItem.resize(vctRetailItem.size());
			for (unsigned int i = 0; i < vctRetailItem.size(); i++)
			{
				pPrintItem->vctRetailItem[i].csName = vctRetailItem[i]->csMedicineName;
				pPrintItem->vctRetailItem[i].csVendor = vctRetailItem[i]->csMedicineVendorName;
				pPrintItem->vctRetailItem[i].csSpec = vctRetailItem[i]->csMedicineSpec;
				pPrintItem->vctRetailItem[i].csBatchNum = vctRetailItem[i]->csMedicineBatchNum;
				pPrintItem->vctRetailItem[i].csSN = vctRetailItem[i]->csMedicineSN;
				pPrintItem->vctRetailItem[i].csNum = vctRetailItem[i]->csMedicineNumber;
				pPrintItem->vctRetailItem[i].csPrice = vctRetailItem[i]->csMedicinePrice;
				pPrintItem->vctRetailItem[i].csTotalPrice = vctRetailItem[i]->csRetailPrice;
			}
			pPrintItem->csTotalPrice = m_retail.csTotalPrcie;
			pPrintItem->csTotalIn = m_retail.csInPrice;
			pPrintItem->csTotalOut = m_retail.csOutPrice;
		}
	}

	for (unsigned int i = 0; i < vctRetailItem.size(); i++)
	{
		delete vctRetailItem[i];
		vctRetailItem[i] = NULL;
	}
	vctRetailItem.clear();

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

	m_staticRetaiItem.SetWindowText(csMsg);

	return TRUE;
}

void CRetailItemDlg::ResizeDlg()
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

	CSize editSize(0,0); 

	CDC *pdc = m_staticRetaiItem.GetDC();
	CFont *pOldFont=pdc->SelectObject(m_staticRetaiItem.GetFont()); 
	::GetTextExtentPoint32((HDC)pdc->m_hDC, (CHAR*)pTestBuf, iPrintCharNum, &editSize); 
	ReleaseDC(pdc);
	pdc = NULL;

	delete pTestBuf;
	pTestBuf = NULL;

	//
	CRect rect, editRect; 

	this->GetWindowRect(rect); 
	m_staticRetaiItem.GetWindowRect(editRect); 

	rect.right=rect.left+editSize.cx + iWidthSpan * 2; 
	this->MoveWindow(rect);

	editRect.left = rect.left + iWidthSpan;
	editRect.right=editRect.left+editSize.cx; 

	ScreenToClient(&editRect); 
	m_staticRetaiItem. MoveWindow(editRect);
}

// CRetailItemDlg message handlers

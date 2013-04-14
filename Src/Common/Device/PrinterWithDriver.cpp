#include "stdafx.h"
#include "Winspool.h"
#include "PrinterWithDriver.h"

CPrinterWithDriver::CPrinterWithDriver()
{
	m_printDC = NULL;
}

CPrinterWithDriver::~CPrinterWithDriver()
{
	ClosePrinter();
}

ERRCODE CPrinterWithDriver::CreatePrinter(LPTSTR lpPrinterName)
{
	if (lpPrinterName == NULL)
	{
		return err_InvalidParameter;
	}

	if (m_printDC != NULL)
	{
		err_Printer_Not_Close;
	}

	m_printDC = CreateDC(_T(""), lpPrinterName, NULL, NULL);
	if (m_printDC == NULL)
	{
		err_Printer_Create_Fail;
	}

	m_xPage = ::GetDeviceCaps(m_printDC, HORZRES); // 得到可打印纸张的高度
	m_yPage = ::GetDeviceCaps(m_printDC, VERTRES); // 得到可打印纸张的宽度

	return err_OK;
}

ERRCODE CPrinterWithDriver::ClosePrinter()
{
	if (m_printDC != NULL)
	{
		DeleteDC(m_printDC);
		m_printDC = NULL;
	}

	return err_OK;
}

ERRCODE CPrinterWithDriver::StartDoc(LPTSTR lpDocName)
{
	if (m_printDC == NULL)
	{
		return err_InvalidParameter;
	}

	DOCINFO di;
	memset( &di, 0, sizeof(DOCINFO) );
	di.lpszDocName = lpDocName; // 设定打印文档名称
	di.lpszOutput = NULL; 
	di.cbSize = sizeof(DOCINFO);
	di.fwType = 0; 

	if(::StartDoc(m_printDC, &di) <= 0)
	{
		return err_Printer_Start_Doc;
	}

	return err_OK;
}

ERRCODE CPrinterWithDriver::EndDoc()
{
	if (m_printDC == NULL)
	{
		return err_InvalidParameter;
	}

	if(::EndDoc(m_printDC) <= 0)
	{
		return err_Printer_End_Page;
	}

	return err_OK;
}

ERRCODE CPrinterWithDriver::StartPage()
{
	if (m_printDC == NULL)
	{
		return err_InvalidParameter;
	}

	if(::StartPage(m_printDC) <= 0)
	{
		return err_Printer_Start_Page;
	}

	return err_OK;
}

ERRCODE CPrinterWithDriver::EndPage()
{
	if (m_printDC == NULL)
	{
		return err_InvalidParameter;
	}

	if(::EndPage(m_printDC) <= 0)
	{
		return err_Printer_End_Page;
	}

	return err_OK;
}

ERRCODE CPrinterWithDriver::TextOut(int x, int y, LPTSTR lpBuf, int iBufSize)
{
	if (m_printDC == NULL)
	{
		return err_InvalidParameter;
	}

	if (x < 0 || x > m_xPage || y < 0 || y > m_yPage)
	{
		return err_InvalidParameter;
	}

	if (::TextOut(m_printDC, x, y, lpBuf, iBufSize) == 0)
	{
		return err_Printer_TextOut;
	}

	return err_OK;
}
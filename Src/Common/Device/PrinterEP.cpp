#include "stdafx.h"
#include "PrinterEP.h"

CPrinterEP::CPrinterEP()
{
	m_hPrinter = INVALID_HANDLE_VALUE;

	m_iInRowsNum = 8;
}

CPrinterEP::~CPrinterEP()
{
	Close();
}

ERRCODE CPrinterEP::Create(LPTSTR lpName)
{
	if (lpName == NULL)
	{
		return err_InvalidParameter;
	}

	if (m_hPrinter != INVALID_HANDLE_VALUE)
	{
		err_Printer_Not_Close;
	}

	m_hPrinter = CreateFile(lpName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
	if(m_hPrinter == INVALID_HANDLE_VALUE)
	{
		return err_Printer_Create_Fail;
	}

	return err_OK;
}

ERRCODE CPrinterEP::Close()
{
	if (m_hPrinter != NULL)
	{
		CloseHandle(m_hPrinter);
		m_hPrinter = NULL;
	}

	return err_OK;
}

ERRCODE CPrinterEP::InitPrint()
{
	if (m_hPrinter == NULL)
	{
		return err_InvalidParameter;
	}

	const BYTE Cmd[] = {0x1B, 0x40};
	DWORD dwWritten=0;
	if (WriteFile(m_hPrinter, &Cmd, sizeof(Cmd), &dwWritten, NULL) != TRUE)
	{
		return err_Printer_Write;
	}

	return err_OK;
}

ERRCODE CPrinterEP::AddTextOut(LPTSTR lpBuf, int iBufSize)
{
	if (m_hPrinter == NULL)
	{
		return err_InvalidParameter;
	}

	DWORD dwWritten=0;
	if (WriteFile(m_hPrinter, lpBuf, iBufSize, &dwWritten, NULL) != TRUE)
	{
		return err_Printer_Write;
	}

	if (dwWritten != iBufSize)
	{
		return err_Printer_Write;
	}

	return err_OK;
}

ERRCODE CPrinterEP::DoPrint()
{
	if (m_hPrinter == NULL)
	{
		return err_InvalidParameter;
	}

	const BYTE Cmd[] = {0x1B, 'd', m_iInRowsNum};
	DWORD dwWritten=0;
	if (WriteFile(m_hPrinter, &Cmd, sizeof(Cmd), &dwWritten, NULL) != TRUE)
	{
		return err_Printer_Write;
	}

	return err_OK;
}

ERRCODE CPrinterEP::OpenCashBox()
{
	if (m_hPrinter == NULL)
	{
		return err_InvalidParameter;
	}

	const BYTE Cmd[] = {0x1B, 0x70, 0x00, 0xFF, 0xFF};
	DWORD dwWritten=0;
	if (WriteFile(m_hPrinter, &Cmd, sizeof(Cmd), &dwWritten, NULL) != TRUE)
	{
		return err_Cashbox_Open;
	}

	return err_OK;
}
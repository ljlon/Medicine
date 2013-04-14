#include "stdafx.h"
#include "CustomerDisplay.h"

CCustomerDisplay::CCustomerDisplay()
{
	m_hDisplay = INVALID_HANDLE_VALUE;
}

CCustomerDisplay::~CCustomerDisplay()
{
	Close();
}

ERRCODE CCustomerDisplay::Create(LPTSTR lpName)
{
	if (lpName == NULL)
	{
		return err_InvalidParameter;
	}

	if (m_hDisplay != INVALID_HANDLE_VALUE)
	{
		err_CustomerDisplay_Not_Close;
	}

	m_hDisplay = CreateFile(lpName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
	if(m_hDisplay == INVALID_HANDLE_VALUE)
	{
		return err_CustomerDisplay_Create_Fail;
	}

	return err_OK;
}

ERRCODE CCustomerDisplay::Close()
{
	if (m_hDisplay != NULL)
	{
		CloseHandle(m_hDisplay);
		m_hDisplay = NULL;
	}

	return err_OK;
}

ERRCODE CCustomerDisplay::InitDisplay()
{
	if (m_hDisplay == NULL)
	{
		return err_InvalidParameter;
	}

	const BYTE Cmd[] = {0x1B, 0x40};
	DWORD dwWritten=0;
	if (WriteFile(m_hDisplay, &Cmd, sizeof(Cmd), &dwWritten, NULL) != TRUE)
	{
		return err_CustomerDisplay_Write;
	}

	return err_OK;
}

ERRCODE CCustomerDisplay::Display(EnumCustomerDisplayType type, double dbData)
{
	if (m_hDisplay == NULL)
	{
		return err_InvalidParameter;
	}

	CString csData;
	csData.Format(_T("%8.2f"), dbData);
	
	const BYTE CmdData[] = {0x1B, 0x51, 0x41, 
		csData.GetBuffer()[0],
		csData.GetBuffer()[1],
		csData.GetBuffer()[2],
		csData.GetBuffer()[3],
		csData.GetBuffer()[4],
		csData.GetBuffer()[5],
		csData.GetBuffer()[6],
		csData.GetBuffer()[7],
		0xD};
	DWORD dwWritten=0;
	if (WriteFile(m_hDisplay, &CmdData, sizeof(CmdData), &dwWritten, NULL) != TRUE)
	{
		return err_CustomerDisplay_Write;
	}

	const BYTE CmdType[] = {0x1B, 0x73, type};
	dwWritten=0;
	if (WriteFile(m_hDisplay, &CmdType, sizeof(CmdType), &dwWritten, NULL) != TRUE)
	{
		return err_CustomerDisplay_Write;
	}

	return err_OK;
}

ERRCODE CCustomerDisplay::Clear()
{
	if (m_hDisplay == NULL)
	{
		return err_InvalidParameter;
	}

	const BYTE Cmd[] = {0xC};
	DWORD dwWritten=0;
	if (WriteFile(m_hDisplay, &Cmd, sizeof(Cmd), &dwWritten, NULL) != TRUE)
	{
		return err_CustomerDisplay_Write;
	}

	return err_OK;
}
#include "stdafx.h"
#include "CashBox.h"

CCashBox::CCashBox()
{
	m_hCashBox = INVALID_HANDLE_VALUE;
}

CCashBox::~CCashBox()
{
	Close();
}

ERRCODE CCashBox::Create(LPTSTR lpName)
{
	if (lpName == NULL)
	{
		return err_InvalidParameter;
	}

	if (m_hCashBox != INVALID_HANDLE_VALUE)
	{
		err_Cashbox_Not_Close;
	}

	m_hCashBox = CreateFile(lpName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
	if(m_hCashBox == INVALID_HANDLE_VALUE)
	{
		return err_Cashbox_Create_Fail;
	}

	return err_OK;
}

ERRCODE CCashBox::Close()
{
	if (m_hCashBox != NULL)
	{
		CloseHandle(m_hCashBox);
		m_hCashBox = NULL;
	}

	return err_OK;
}

ERRCODE CCashBox::Open()
{
	if (m_hCashBox == NULL)
	{
		return err_InvalidParameter;
	}

	const BYTE Cmd[] = {0x1B, 0x70, 0x00, 0xFF, 0xFF};
	DWORD dwWritten=0;
	if (WriteFile(m_hCashBox, &Cmd, sizeof(Cmd), &dwWritten, NULL) != TRUE)
	{
		return err_Cashbox_Open;
	}

	return err_OK;
}
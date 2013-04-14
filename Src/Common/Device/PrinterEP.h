#pragma once
#include "StdHead.h"

class CPrinterEP
{
public:
	CPrinterEP();
	~CPrinterEP();

	ERRCODE Create(LPTSTR lpName);
	ERRCODE Close();

	ERRCODE OpenCashBox();

	ERRCODE InitPrint();
	ERRCODE AddTextOut(LPTSTR lpBuf, int iBufSize);
	ERRCODE DoPrint();

protected:

private:
	HANDLE  m_hPrinter;

	int m_iInRowsNum;
};
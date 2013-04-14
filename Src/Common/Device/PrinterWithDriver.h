#pragma once
#include "StdHead.h"

class CPrinterWithDriver
{
public:
	CPrinterWithDriver();
	~CPrinterWithDriver();

	ERRCODE CreatePrinter(LPTSTR lpPrinterName);
	ERRCODE ClosePrinter();

	ERRCODE StartDoc(LPTSTR lpDocName);
	ERRCODE StartPage();
	ERRCODE EndDoc();
	ERRCODE EndPage();
	ERRCODE TextOut(int x, int y, LPTSTR lpBuf, int iBufSize);
protected:

private:
	HDC m_printDC;
	int m_xPage;
	int m_yPage;
};
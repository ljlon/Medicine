#pragma once
#include "StdHead.h"

typedef struct _PrinterInfo
{
	CString  csPrinterName;
}PrinterInfo;

class CPrinterManager
{
public:
	CPrinterManager();
	~CPrinterManager();

	ERRCODE  EnumAllPrinters(vector<PrinterInfo> &vctAllPrinters);

protected:

private:

};

extern CPrinterManager g_printerMgr;
#include "stdafx.h"
#include "Winspool.h"
#include "PrinterManager.h"

CPrinterManager g_printerMgr;

CPrinterManager::CPrinterManager()
{
	
}

CPrinterManager::~CPrinterManager()
{

}

ERRCODE  CPrinterManager::EnumAllPrinters(vector<PrinterInfo> &vctAllPrinters) 
{ 
	vctAllPrinters.clear();

	CString csMsg;
	DWORD	 Flags   =   PRINTER_ENUM_FAVORITE | PRINTER_ENUM_LOCAL;  
	DWORD	 dwBufSize; 
	DWORD	 dwRetNum; 

	DWORD	 Level   =   2; 
	TCHAR	 Name[500]   ; 
	LPPRINTER_INFO_2   pPrinterEnum   =   NULL   ; 

	memset(Name,   0,   sizeof(TCHAR)   *   500)   ; 
	::EnumPrinters(Flags,   Name,   Level,   NULL,   0,   &dwBufSize,   &dwRetNum);

	pPrinterEnum   =   (LPPRINTER_INFO_2)LocalAlloc(LPTR,   dwBufSize + 4)   ; 
	if   (!pPrinterEnum) 
	{ 
		return err_MemoryNotEnough;
	} 

	if   (!::EnumPrinters( 
			Flags,	 
			Name,	 
			Level,	 
			(LPBYTE)pPrinterEnum,	
			dwBufSize,	 
			&dwBufSize,	 
			&dwRetNum)	) 
	{ 
		csMsg.Format( "Enum printers failed with error %d\n ",  GetLastError()); 
		g_log.Write(csMsg);

		if (pPrinterEnum != NULL)
		{
			LocalFree(pPrinterEnum);
			pPrinterEnum = NULL;
		}
		return   err_Printer_Not_Found; 
	} 

	if(dwRetNum <= 0) 
	{
		if (pPrinterEnum != NULL)
		{
			LocalFree(pPrinterEnum);
			pPrinterEnum = NULL;

		}

		return  err_Printer_Not_Found;
	}

	vctAllPrinters.resize(dwRetNum);
	for (unsigned int i = 0; i < dwRetNum; i++)
	{
		vctAllPrinters[i].csPrinterName = pPrinterEnum[i].pPrinterName;
	}

	if (pPrinterEnum != NULL)
	{
		LocalFree(pPrinterEnum);
		pPrinterEnum = NULL;
	}

	return err_OK;
} 
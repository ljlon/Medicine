#pragma once
#include "StdHead.h"

#define FILE_PRINTFORMAT_TXT  _T("Configuration\\PrintFormat.dat")

#define MARCO_NO _T("NO")							//单号
#define MARCO_POSNO _T("POS")					//POS机号
#define MARCO_UID _T("UID")						//收银员
#define MARCO_DATETIME   _T("DATETIME")	//时间
#define MARCO_ITEM		 _T("ITEM")			//零售药品项
#define MARCO_NAME		 _T("NAME")			//药品名称
#define MARCO_SN         _T("SN")					//药品编码
#define MARCO_SPEC       _T("SPEC")         //药品规格
#define MARCO_NUM		 _T("NUM")			//药品数量
#define MARCO_PRICE      _T("PRICE")				//药品价格
#define MARCO_SUMPRICE   _T("SUM")			//药品金额小计
#define MARCO_TOTALPRICE _T("TOTAL")		//所有零售药品项金额总计
#define MARCO_TOTALIN    _T("IN")				//实收金额
#define MARCO_TOTALOUT   _T("OUT")			//找零金额

typedef struct _PrintRetailItem
{
	CString csName;
	CString csSN;
	CString csSpec;
	CString csPrice;
	CString csNum;
	CString csTotalPrice;
}PrintRetailItem;

typedef struct _PrintItem
{
	CString csUID;
	CString csPOSNO;
	CString csNO;
	CString csDataTime;
	vector<PrintRetailItem> vctRetailItem;
	CString csTotalPrice;
	CString csTotalIn;
	CString csTotalOut;
}PrintItem;

class CPrintFormat
{
public:
	CPrintFormat();
	~CPrintFormat();

	ERRCODE Load();
	ERRCODE Save();

	BYTE *GetFormatStr();
	ERRCODE SetFormatStr(BYTE *pbStr, DWORD dwStrLen);

	PrintItem* GetPrintItemPtr();

	ERRCODE GetPrintStrFirstLine(BYTE *pbyBuf, DWORD *pdwGetNum, DWORD dwBufSize);
	ERRCODE GetPrintStrNextLine(BYTE *pbyBuf, DWORD *pdwGetNum, DWORD dwBufSize);

protected:
	ERRCODE DecodePrintStr(BYTE *pbyFormatStr, 
							DWORD *pdwRetFormatStrSize, 
							DWORD dwFormatStrSize, 
							BYTE *pbyPrintStr, 
							DWORD *pdwRetPrintStrSize, 
							DWORD dwPrintBufSize);
	ERRCODE DecodeItemPrintStr(BYTE *pbyFormatStr, 
								DWORD dwFormatStrSize, 
								DWORD *pdwRetFormatStrSize, 
								PrintRetailItem *pRetailItem,
								BYTE *pbyPrintStr, 
								DWORD dwPrintBufSize,
								DWORD *pdwRetPrintStrSize);
	ERRCODE DecodeCmdPrintLen(BYTE *pbyFormatStr, DWORD dwFormatStrSize, DWORD *pdwRetFormatStrSize, LONG *plPrintStrLen);

	BYTE *m_pbyFormatStr;
	DWORD m_dwFormatStrSize;
	BYTE* m_pbFormatStrPos;
	PrintItem m_printItem;
	int   m_iNextRetailItem;

private:

};

extern CPrintFormat g_printFormat;
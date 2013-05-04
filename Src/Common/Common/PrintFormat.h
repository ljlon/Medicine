#pragma once
#include "StdHead.h"

#define FILE_PRINTFORMAT_TXT  _T("Configuration\\PrintFormat.dat")

#define MARCO_NO _T("NO")							//����
#define MARCO_POSNO _T("POS")					//POS����
#define MARCO_UID _T("UID")						//����Ա
#define MARCO_DATETIME   _T("DATETIME")	//ʱ��
#define MARCO_ITEM		 _T("ITEM")			//����ҩƷ��
#define MARCO_NAME		 _T("NAME")			//ҩƷ����
#define MARCO_SN         _T("SN")					//ҩƷ����
#define MARCO_SPEC       _T("SPEC")         //ҩƷ���
#define MARCO_NUM		 _T("NUM")			//ҩƷ����
#define MARCO_PRICE      _T("PRICE")				//ҩƷ�۸�
#define MARCO_SUMPRICE   _T("SUM")			//ҩƷ���С��
#define MARCO_TOTALPRICE _T("TOTAL")		//��������ҩƷ�����ܼ�
#define MARCO_TOTALIN    _T("IN")				//ʵ�ս��
#define MARCO_TOTALOUT   _T("OUT")			//������

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
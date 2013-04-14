#pragma once
#include "StdHead.h"

class CAdapter
{
public:
	CAdapter();
	~CAdapter();

	ERRCODE GetAdaptersInfo();
	ERRCODE GetMacAddress(BYTE* pbyBuffer, DWORD& dwLength);
	ERRCODE GetMacAddressByChar(CHAR* pchBuffer, DWORD& dwLength);
protected:

private:
	PBYTE m_pbyAdaptersInfo;
	DWORD m_dwAdapatersInfoLength;
};
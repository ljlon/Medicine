#pragma once
#include "ErrorCode.h"
#include "windows.h"

class CVersion
{
public:
	CVersion();
	~CVersion();

	VS_FIXEDFILEINFO *GetVersionInfo(LPTSTR lpFileName);

private:
	ERRCODE InitVersionInfo(LPTSTR lpFileName);

	BYTE *m_pData;
	VS_FIXEDFILEINFO *m_pVersionInfo;
};

extern CVersion g_version;


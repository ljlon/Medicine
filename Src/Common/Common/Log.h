#pragma once

#include <afxmt.h >
#include "StdHead.h"

using namespace std;

class CLog
{
public:
	CLog();
	~CLog();

	ERRCODE Init(LPCTSTR pszLogFilePath);
	ERRCODE Write(LPCTSTR pszMessage, ERRCODE errCode = err_OK);
	ERRCODE WriteNoChangeLine(LPCTSTR pszMessage);
	ERRCODE WriteNoChangeLineNoTime(LPCTSTR pszMessage);   
	ERRCODE ChangeLine();   

protected:
private:
	ERRCODE BasicWrite(LPCTSTR pszMessage);
	BOOL m_bInitialized;
	CString m_csFilePath;
	HANDLE m_hFile;
	CCriticalSection m_CritAccess;;
};

bool FileExist(const TCHAR* pszFileName);
bool FileNew(const TCHAR* pszFileName);

extern CLog g_log;
#pragma once

BOOL ChangeCharToByte(const char* pszString, 
										PBYTE pbyBuffer,
										int& iLength);

BOOL ChangeByteToChar(PBYTE pbyBuffer, 
										int iByteNum, 
										char* pszString, 
										int iMaxLength);

BOOL CreateRandom(TCHAR *pRandomKey, int iBitNum);

BOOL ChangeDate(LPTSTR lpDateStr, SYSTEMTIME &sysTime);

int CmpDate(LPTSTR lpDateStr1, LPTSTR lpDateStr2);
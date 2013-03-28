#include "stdafx.h"
#include "CommUtil.h"

BOOL ChangeCharToByte(const char* pszString, PBYTE pbyBuffer, int& iLength)
{
	const char* pszTemp = pszString;
	BYTE* pbyTemp = pbyBuffer;
	if (strlen(pszString) % 2 != 0 ||
		strlen(pszString) == 0)
	{
		return FALSE;
	}
	BOOL bIsHigh = TRUE;
	while(*pszTemp != 0)
	{
		if (pbyTemp - pbyBuffer >= iLength)
		{
			return FALSE;
		}

		BYTE byTemp = 0;
		if (*pszTemp >= '0' && *pszTemp <= '9')
		{
			byTemp = *pszTemp - 0x30;
		}
		else if (*pszTemp >= 'A' && *pszTemp <= 'F')
		{
			byTemp = *pszTemp - 'A' + 10;
		}
		else if (*pszTemp >= 'a' && *pszTemp <= 'f')
		{
			byTemp = *pszTemp - 'a' + 10;
		}
		else
		{
			return FALSE;
		}
		if (bIsHigh)
		{
			*pbyTemp = (byTemp << 4);
			bIsHigh = FALSE;

		}
		else
		{
			*pbyTemp |= byTemp;
			bIsHigh = TRUE;
			*pbyTemp++;
		}
		pszTemp++;
	}
	iLength = pbyTemp - pbyBuffer;
	return TRUE;
}

BOOL ChangeByteToChar(PBYTE pbyBuffer, int iByteNum, 
	char* pszString, int iMaxLength)
{
	memset(pszString, 0, iMaxLength);
	unsigned int i = 0;
	char szTemp[3];
	for (; i < (unsigned int)iByteNum; i++)
	{
		if (strlen(pszString) + 3 > (unsigned int)iMaxLength)
		{
			return FALSE;
		}
		memset(szTemp, 0, 3);
		sprintf_s(szTemp, "%x", (int)(pbyBuffer[i]));
		if (strlen(szTemp) == 1)
		{
			szTemp[1] = szTemp[0];
			szTemp[0] = '0';
			szTemp[2] = 0;
		}
		strcat_s(pszString, iMaxLength, szTemp); 
	}

	return TRUE;
}

BOOL CreateRandom(TCHAR *pRandomKey, int iBitNum)
{
	if (pRandomKey == NULL)
	{
		return FALSE;
	}
	int iBit = 16;

	srand((unsigned)time(NULL)); 
	for (int i = 0; i < iBitNum; i++)
	{
		TCHAR *pTemp = pRandomKey+i;
		sprintf_s(pTemp, 2, "%X", int(rand() % iBit)); 
	}

	return TRUE;
}

BOOL ChangeDate(LPTSTR lpDateStr, SYSTEMTIME &sysTime)
{
	memset(&sysTime, 0, sizeof(SYSTEMTIME));
	if (sscanf_s(lpDateStr,"%d/%d/%d",&(sysTime.wYear),&(sysTime.wMonth),&(sysTime.wDay)) != 3 && 
		sscanf_s(lpDateStr,"%d-%d-%d",&(sysTime.wYear),&(sysTime.wMonth),&(sysTime.wDay)) != 3)
	{
		return FALSE;
	}

	return TRUE;
}

int CmpDate(LPTSTR lpDateStr1, LPTSTR lpDateStr2)
{
	if (lpDateStr1 == NULL || lpDateStr2 == NULL)
	{
		return 1;
	}

	SYSTEMTIME time1, time2;

	if (ChangeDate(lpDateStr1, time1) != TRUE)
	{
		return 1;
	}

	if (ChangeDate(lpDateStr2, time2) != TRUE)
	{
		return 1;
	}

	if  (time1.wYear != time2.wYear || time1.wMonth != time2.wMonth || time1.wDay != time2.wDay)
	{
		return 1;
	}

	return 0;
}
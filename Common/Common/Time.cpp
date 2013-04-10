#include "stdafx.h"
#include "Time.h"

int ChangeSysTime(SYSTEMTIME &sysTime, int nIncDay, int nIncHour, int nIncMin, int nIncSec)
{
	if (nIncDay == 0 && nIncHour == 0 && nIncMin == 0 && nIncSec == 0)
	{
		return 1;
	}

	FILETIME ft={0};   
	SystemTimeToFileTime(&sysTime, &ft);   

	ULONGLONG qwResult;  
	// Copy the time into a quadword.  
	qwResult = (((ULONGLONG) ft.dwHighDateTime) << 32) + ft.dwLowDateTime;  

	qwResult += nIncDay * _DAY; 
	qwResult += nIncHour * _HOUR;  
	qwResult += nIncMin * _MINUTE; 
	qwResult += nIncSec * _SECOND; 

	// Copy the result back into the FILETIME structure.  
	ft.dwLowDateTime  = (DWORD) (qwResult & 0xFFFFFFFF );  
	ft.dwHighDateTime = (DWORD) (qwResult >> 32 );  

	FileTimeToSystemTime(&ft, &sysTime);  

	return 0;
}

DWORD CmpTimeBySec(SYSTEMTIME &sysTime0, SYSTEMTIME &sysTime1)
{
	FILETIME fileTime0, fileTime1;
	SystemTimeToFileTime(&sysTime0, &fileTime0);   
	SystemTimeToFileTime(&sysTime1, &fileTime1);   

	ULONGLONG qwResult0;  
	qwResult0 = (((ULONGLONG) fileTime0.dwHighDateTime) << 32) + fileTime0.dwLowDateTime;  
	ULONGLONG qwResult1;  
	qwResult1 = (((ULONGLONG) fileTime1.dwHighDateTime) << 32) + fileTime1.dwLowDateTime;  

	ULONGLONG resQwResult = qwResult1 - qwResult0;

	return (DWORD)(resQwResult / _SECOND);
}
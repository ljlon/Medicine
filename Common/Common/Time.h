#pragma once

#define _SECOND ((ULONGLONG) 10000000)  
#define _MINUTE (60 * _SECOND)  
#define _HOUR   (60 * _MINUTE)  
#define _DAY    (24 * _HOUR)  

//�޸�SystemTime
int ChangeSysTime(SYSTEMTIME &sysTime, int nIncDay, int nIncHour, int nIncMin, int nIncSec);

//�Ƚ�����SystemTime�Ĳ�࣬����ֵΪtime0��time1��������
DWORD CmpTimeBySec(SYSTEMTIME &sysTime0, SYSTEMTIME &sysTime1);
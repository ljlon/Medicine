#pragma once

#define _SECOND ((ULONGLONG) 10000000)  
#define _MINUTE (60 * _SECOND)  
#define _HOUR   (60 * _MINUTE)  
#define _DAY    (24 * _HOUR)  

//修改SystemTime
int ChangeSysTime(SYSTEMTIME &sysTime, int nIncDay, int nIncHour, int nIncMin, int nIncSec);

//比较两个SystemTime的差距，返回值为time0比time1相差多少秒
DWORD CmpTimeBySec(SYSTEMTIME &sysTime0, SYSTEMTIME &sysTime1);
#pragma once
#include "StdHead.h"
#include "Winspool.h"

typedef struct _PORT_INFO
{
	CString     csPortName;
	CString     csMonitorName;
	CString     csDescription;
	DWORD    dwPortType;
}PORT_INFO;

class CDeviceManager
{
public:
	CDeviceManager();
	~CDeviceManager();

	ERRCODE  EnumAllPorts();
	vector<PORT_INFO*>*  GetAllPorts();
	vector<PORT_INFO*>*  GetAllCOMPorts();
	vector<PORT_INFO*>*  GetAllLPTPorts();

protected:
	vector<PORT_INFO*> m_vctAllPorts;
	vector<PORT_INFO*> m_vctAllCOMPorts;
	vector<PORT_INFO*> m_vctAllLPTPorts;

private:
	BOOL m_bInit;
};

extern CDeviceManager g_deviceMgr;
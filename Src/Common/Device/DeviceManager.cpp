#include "stdafx.h"
#include "DeviceManager.h"

CDeviceManager g_deviceMgr;

void ReleasePortVector(vector<PORT_INFO*> &vctPorts)
{
	for (int i = 0; i < (int)vctPorts.size(); i++)
	{
		if (vctPorts[i] != NULL)
		{
			delete vctPorts[i];
			vctPorts[i] = NULL;
		}
	}
	vctPorts.clear();
}

CDeviceManager::CDeviceManager()
{
	m_bInit = FALSE;
}

CDeviceManager::~CDeviceManager()
{
	ReleasePortVector(m_vctAllPorts);
	m_vctAllCOMPorts.clear();
	m_vctAllLPTPorts.clear();
}

ERRCODE  CDeviceManager::EnumAllPorts()
{
	ReleasePortVector(m_vctAllPorts);
	m_vctAllCOMPorts.clear();
	m_vctAllLPTPorts.clear();

	CString csMsg;
	DWORD	 dwBufSize; 
	DWORD	 dwRetNum; 

	DWORD	 Level   =   2; 
	BYTE	 tszPortsBuf[500]   ; 
	memset(tszPortsBuf,   0,   sizeof(TCHAR)   *   500)   ; 
	::EnumPorts(NULL,   Level,   tszPortsBuf,   0,   &dwBufSize,   &dwRetNum);
	LPPORT_INFO_2 pPortsEnum   =   (LPPORT_INFO_2)LocalAlloc(LPTR,   dwBufSize + 4)   ; 
	if   (!pPortsEnum) 
	{ 
		return err_MemoryNotEnough;
	} 

	if   (!::EnumPorts( 
		NULL,	 
		Level,	 
		(LPBYTE)pPortsEnum,	
		dwBufSize,	 
		&dwBufSize,	 
		&dwRetNum)	) 
	{ 
		csMsg.Format( "Enum ports failed with error %d\n ",  GetLastError()); 
		g_log.Write(csMsg);

		if (pPortsEnum != NULL)
		{
			LocalFree(pPortsEnum);
			pPortsEnum = NULL;
		}
		return   err_Printer_Not_Found; 
	} 

	if(dwRetNum <= 0) 
	{
		if (pPortsEnum != NULL)
		{
			LocalFree(pPortsEnum);
			pPortsEnum = NULL;
		}

		return  err_Printer_Not_Found;
	}

	for (unsigned int i = 0; i < dwRetNum; i++)
	{
		PORT_INFO *pPartInfo = new PORT_INFO;
		pPartInfo->csPortName = LPTSTR(pPortsEnum[i].pPortName);
		pPartInfo->csMonitorName = LPTSTR(pPortsEnum[i].pMonitorName);
		pPartInfo->csDescription = LPTSTR(pPortsEnum[i].pDescription);
		pPartInfo->dwPortType = pPortsEnum[i].fPortType;
		m_vctAllPorts.push_back(pPartInfo);

		if (_tcsncmp(pPortsEnum[i].pPortName, _T("COM"), 3) == 0)
		{
			m_vctAllCOMPorts.push_back(pPartInfo);
		}
		else 	if (_tcsncmp(pPortsEnum[i].pPortName, _T("LPT"), 3) == 0)
		{
			m_vctAllLPTPorts.push_back(pPartInfo);
		}
	}

	if (pPortsEnum != NULL)
	{
		LocalFree(pPortsEnum);
		pPortsEnum = NULL;
	}

	m_bInit = TRUE;

	return err_OK;
}

vector<PORT_INFO*>*  CDeviceManager::GetAllPorts()
{
	if (m_bInit != TRUE)
	{
		EnumAllPorts();
	}

	return &m_vctAllPorts;
}

vector<PORT_INFO*>*  CDeviceManager::GetAllCOMPorts()
{
	if (m_bInit != TRUE)
	{
		EnumAllPorts();
	}

	return &m_vctAllCOMPorts;
}

vector<PORT_INFO*>*  CDeviceManager::GetAllLPTPorts()
{
	if (m_bInit != TRUE)
	{
		EnumAllPorts();
	}

	return &m_vctAllLPTPorts;
}
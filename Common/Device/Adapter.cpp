#include "stdafx.h"
#include "Adapter.h"
#include <Iphlpapi.h>

CAdapter::CAdapter()
{
	m_pbyAdaptersInfo = NULL;
	m_dwAdapatersInfoLength = 0;
}

CAdapter::~CAdapter()
{
	if (m_pbyAdaptersInfo != NULL)
	{
		delete m_pbyAdaptersInfo;
		m_pbyAdaptersInfo = NULL;
	}
	m_dwAdapatersInfoLength = 0;
}

ERRCODE CAdapter::GetAdaptersInfo()
{
	if (m_pbyAdaptersInfo != NULL)
	{
		delete m_pbyAdaptersInfo;
		m_pbyAdaptersInfo = NULL;
		m_dwAdapatersInfoLength = 0;
	}
	PIP_ADAPTER_INFO pAdapterInfo = NULL;
	ULONG uSize = 0;
	DWORD dwRet = ::GetAdaptersInfo(NULL, &uSize);
	if (dwRet == ERROR_BUFFER_OVERFLOW)
	{
		m_pbyAdaptersInfo = new BYTE[uSize];
		if (m_pbyAdaptersInfo == NULL)
		{
			return err_MemoryNotEnough;
		}
		m_dwAdapatersInfoLength = uSize;
		memset(m_pbyAdaptersInfo, 0, uSize);
		pAdapterInfo = (PIP_ADAPTER_INFO)m_pbyAdaptersInfo;
		dwRet = ::GetAdaptersInfo(pAdapterInfo, &uSize);
	}
	if (dwRet != ERROR_SUCCESS)
	{
		if (m_pbyAdaptersInfo != NULL)
		{
			delete m_pbyAdaptersInfo;
			m_pbyAdaptersInfo = NULL;
		}
		m_dwAdapatersInfoLength = 0;
		return (ERRCODE)(dwRet | 0x20000000);
	}
	else
	{
		return err_OK;
	}
}

ERRCODE CAdapter::GetMacAddress(BYTE* pbyBuffer, DWORD& dwLength)
{
	ERRCODE errRet = err_OK;

	if (m_pbyAdaptersInfo == NULL || m_dwAdapatersInfoLength == 0)
	{
		errRet = GetAdaptersInfo();
		if (errRet != err_OK)
		{
			return errRet;
		}
	}

	IP_ADAPTER_INFO* pAdapterInfoTemp = (IP_ADAPTER_INFO*)m_pbyAdaptersInfo;
	BYTE byMacAddress[MAX_ADAPTER_ADDRESS_LENGTH];
	memset(byMacAddress, 0xFF, MAX_ADAPTER_ADDRESS_LENGTH);
	DWORD dwMacLength = 0;
	while(pAdapterInfoTemp != NULL && 
		((PBYTE)pAdapterInfoTemp) < m_pbyAdaptersInfo + m_dwAdapatersInfoLength)
	{
		//if (strstr(pAdapterInfoTemp->Description,"PCI") > 0 && 
		if (pAdapterInfoTemp->Type == MIB_IF_TYPE_ETHERNET &&
			memcmp(byMacAddress, pAdapterInfoTemp->Address, pAdapterInfoTemp->AddressLength) >0)
		{
			memset(byMacAddress, 0, MAX_ADAPTER_ADDRESS_LENGTH);
			memcpy(byMacAddress, pAdapterInfoTemp->Address, pAdapterInfoTemp->AddressLength);
			dwMacLength = pAdapterInfoTemp->AddressLength;
		}
		pAdapterInfoTemp = pAdapterInfoTemp->Next;
	}

	if (dwLength >= dwMacLength)
	{
		memcpy(pbyBuffer, byMacAddress, dwMacLength);
		dwLength = dwMacLength;
	}
	else
	{
		memcpy(pbyBuffer, byMacAddress + dwMacLength - dwLength, dwLength);
		dwLength = dwLength;
	}

	return err_OK;
}

ERRCODE CAdapter::GetMacAddressByChar(CHAR* pchBuffer, DWORD& dwLength)
{
	ERRCODE errRet = err_OK;
	BYTE byMacAddress[MAX_ADAPTER_ADDRESS_LENGTH];
	memset(byMacAddress, 0xFF, MAX_ADAPTER_ADDRESS_LENGTH);

	DWORD dwMacAddressLen = MAX_ADAPTER_ADDRESS_LENGTH;
	errRet = GetMacAddress(byMacAddress, dwMacAddressLen);
	if (errRet != err_OK)
	{
		return errRet;
	}
	
	if (ChangeByteToChar(byMacAddress, (int)dwMacAddressLen, pchBuffer, (int)dwLength) != TRUE)
	{
		return err_InvalidParameter;
	}

	return err_OK;
}
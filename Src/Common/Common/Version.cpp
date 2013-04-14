#include "stdafx.h"
#include "Version.h"

CVersion g_version;

CVersion::CVersion()
{
	m_pData = NULL;
	m_pVersionInfo = NULL;
}

CVersion::~CVersion()
{
	m_pVersionInfo = NULL;

	if (m_pData != NULL)
	{
		delete m_pData;
		m_pData = NULL;
	}
}

ERRCODE CVersion::InitVersionInfo(LPTSTR lpFileName)
{
	DWORD dwVersionHandler;
	UINT nVersionInfoSize = GetFileVersionInfoSize(lpFileName, &dwVersionHandler);
	if (nVersionInfoSize == 0)
	{
		return err_InvalidParameter;
	}

	m_pVersionInfo = NULL;
	if (m_pData != NULL)
	{
		delete m_pData;
		m_pData = NULL;
	}
	m_pData = new BYTE[nVersionInfoSize];

	if (GetFileVersionInfo(lpFileName, dwVersionHandler, nVersionInfoSize, m_pData) != TRUE)
	{
		delete m_pData;
		m_pData = NULL;
		return err_InvalidParameter;
	}

	if (::VerQueryValue(m_pData, (LPTSTR)_T( "\\"), (void**)&m_pVersionInfo, &nVersionInfoSize) != TRUE)
	{
		delete m_pData;
		m_pData = NULL;
		return err_InvalidParameter;
	}

	return err_OK;
}

VS_FIXEDFILEINFO* CVersion::GetVersionInfo(LPTSTR lpFileName)
{
	if (m_pData == NULL)
	{
		InitVersionInfo(lpFileName);
	}

	return m_pVersionInfo;
}
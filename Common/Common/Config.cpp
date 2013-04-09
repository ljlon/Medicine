#include "stdafx.h"
#include "Config.h"
#include "Crypto.h"

Config g_config;

Config::Config()
{
	
}

Config::~Config()
{

}

ERRCODE Config::Load()
{
	BYTE pbyBuf[MAX_PATH];
	int iByteLen;
	DWORD dwByteLen;

	//database
	GetPrivateProfileString(SECTION_DATABASE, _T("Host"), _T(""), database_host.GetBuffer(MAX_PATH), MAX_PATH, FILE_CONFIG_INI);
	database_port = GetPrivateProfileInt(SECTION_DATABASE, _T("Port"), 3306, FILE_CONFIG_INI);
	GetPrivateProfileString(SECTION_DATABASE, _T("DBName"), _T(""), database_dbname.GetBuffer(MAX_PATH), MAX_PATH, FILE_CONFIG_INI);
	GetPrivateProfileString(SECTION_DATABASE, _T("UID"), _T(""), database_uid.GetBuffer(MAX_PATH), MAX_PATH, FILE_CONFIG_INI);
	
	memset(pbyBuf, 0, MAX_PATH);
	GetPrivateProfileString(SECTION_DATABASE, _T("PWD"), _T(""), database_pwd.GetBuffer(MAX_PATH), MAX_PATH, FILE_CONFIG_INI);
	iByteLen = MAX_PATH;
	ChangeCharToByte(database_pwd.GetBuffer(), pbyBuf, iByteLen);
	dwByteLen = strlen(database_pwd.GetBuffer()) / 2;
	Decrypt(pbyBuf, dwByteLen);
	database_pwd = LPTSTR(pbyBuf);

	return err_OK;
}

ERRCODE Config::Save()
{ 
	BOOL bRet = TRUE;
	TCHAR tszBuf[MAX_PATH];
	BYTE pbyBuf[MAX_PATH];
	DWORD dwBufLen;

	//Database
	bRet = WritePrivateProfileString(SECTION_DATABASE, _T("Host"), database_host, FILE_CONFIG_INI);
	memset(tszBuf, 0, sizeof(TCHAR) * MAX_PATH);
	_ltoa_s(database_port, tszBuf, 10);
	bRet = WritePrivateProfileString(SECTION_DATABASE, _T("Port"), tszBuf, FILE_CONFIG_INI);
	bRet = WritePrivateProfileString(SECTION_DATABASE, _T("DBName"), database_dbname, FILE_CONFIG_INI);
	bRet = WritePrivateProfileString(SECTION_DATABASE, _T("UID"), database_uid, FILE_CONFIG_INI);

	memset(pbyBuf, 0, sizeof(TCHAR) * MAX_PATH);
	memcpy(pbyBuf, database_pwd.GetBuffer(), database_pwd.GetLength());
	dwBufLen = database_pwd.GetLength();
	Encrypt(pbyBuf, dwBufLen, MAX_PATH);
	ChangeByteToChar(pbyBuf, dwBufLen, tszBuf, MAX_PATH);
	bRet = WritePrivateProfileString(SECTION_DATABASE, _T("PWD"), tszBuf, FILE_CONFIG_INI);

	return err_OK;
}
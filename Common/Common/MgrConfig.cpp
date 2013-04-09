#include "stdafx.h"
#include "MgrConfig.h"
#include "Crypto.h"

MgrConfig g_MgrCfg;

MgrConfig::MgrConfig()
{

}

MgrConfig::~MgrConfig()
{

}

ERRCODE MgrConfig::Load()
{
	//database
	GetPrivateProfileString(SECTION_MYSQL, _T("InstallFolder"), _T(""), mysql_install_folder.GetBuffer(MAX_PATH), MAX_PATH, FILE_MGRCFG_INI);

	return err_OK;
}

ERRCODE MgrConfig::Save()
{ 
	BOOL bRet;

	bRet = WritePrivateProfileString(SECTION_MYSQL, _T("InstallFolder"), mysql_install_folder, FILE_MGRCFG_INI);

	return err_OK;
}
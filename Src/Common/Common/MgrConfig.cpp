#include "stdafx.h"
#include "MgrConfig.h"
#include "Crypto.h"

MgrConfig g_MgrCfg;

MgrConfig::MgrConfig()
{
	theme_font_name = _T("MS Shell Dlg");
	theme_font_height = 14;

	backup_auto = 1;
	backup_auto_date = 1;
	backup_auto_date_unit = 0;
	backup_auto_time = 12;
}

MgrConfig::~MgrConfig()
{

}

ERRCODE MgrConfig::Load()
{
	//database
	GetPrivateProfileString(SECTION_MYSQL, _T("InstallFolder"), _T(""), mysql_install_folder.GetBuffer(MAX_PATH), MAX_PATH, FILE_MGRCFG_INI);
	
	//Theme
	GetPrivateProfileString(SECTION_THEME, _T("FontName"), _T(""), theme_font_name.GetBuffer(MAX_PATH), MAX_PATH, FILE_MGRCFG_INI);
	theme_font_height = GetPrivateProfileInt(SECTION_THEME, _T("FontHeight"), 14, FILE_MGRCFG_INI);

	//Backup
	backup_auto = GetPrivateProfileInt(SECTION_BACKUP, _T("AutoBackup"), 1, FILE_MGRCFG_INI);
	backup_auto_date = GetPrivateProfileInt(SECTION_BACKUP, _T("AutoBackupDate"), 1, FILE_MGRCFG_INI);
	backup_auto_date_unit = GetPrivateProfileInt(SECTION_BACKUP, _T("AutoBackupDateUnit"), 0, FILE_MGRCFG_INI);
	backup_auto_time = GetPrivateProfileInt(SECTION_BACKUP, _T("AutoBackupTime"), 12, FILE_MGRCFG_INI);

	return err_OK;
}

ERRCODE MgrConfig::Save()
{ 
	BOOL bRet = TRUE;
	TCHAR tszBuf[MAX_PATH];

	//MySQL
	bRet = WritePrivateProfileString(SECTION_MYSQL, _T("InstallFolder"), mysql_install_folder, FILE_MGRCFG_INI);

	//Theme
	bRet = WritePrivateProfileString(SECTION_THEME, _T("FontName"), theme_font_name, FILE_MGRCFG_INI);
	memset(tszBuf, 0, sizeof(TCHAR) * MAX_PATH);
	_ltoa_s(theme_font_height, tszBuf, 10);
	bRet = WritePrivateProfileString(SECTION_THEME, _T("FontHeight"), tszBuf, FILE_MGRCFG_INI);

	//Backup
	memset(tszBuf, 0, sizeof(TCHAR) * MAX_PATH);
	_ltoa_s(backup_auto, tszBuf, 10);
	bRet = WritePrivateProfileString(SECTION_BACKUP, _T("AutoBackup"), tszBuf, FILE_MGRCFG_INI);
	memset(tszBuf, 0, sizeof(TCHAR) * MAX_PATH);
	_ltoa_s(backup_auto_date, tszBuf, 10);
	bRet = WritePrivateProfileString(SECTION_BACKUP, _T("AutoBackupDate"), tszBuf, FILE_MGRCFG_INI);	memset(tszBuf, 0, sizeof(TCHAR) * MAX_PATH);
	_ltoa_s(backup_auto_date_unit, tszBuf, 10);
	bRet = WritePrivateProfileString(SECTION_BACKUP, _T("AutoBackupDateUnit"), tszBuf, FILE_MGRCFG_INI);	memset(tszBuf, 0, sizeof(TCHAR) * MAX_PATH);
	_ltoa_s(backup_auto_time, tszBuf, 10);
	bRet = WritePrivateProfileString(SECTION_BACKUP, _T("AutoBackupTime"), tszBuf, FILE_MGRCFG_INI);

	return err_OK;
}
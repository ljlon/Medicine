#pragma once
#include "StdHead.h"

#define FILE_MGRCFG_INI _T("Configuration\\MgrConfig.ini")

#define SECTION_MYSQL	_T("MySQL")
#define SECTION_THEME   _T("Theme")
#define SECTION_BACKUP  _T("Backup")

class MgrConfig
{
public:
	MgrConfig();
	~MgrConfig();

	ERRCODE Load();
	ERRCODE Save();

	//mysql
	CString mysql_install_folder;

	//Theme
	CString theme_font_name;
	int theme_font_height;
	
	//Backup
	int backup_auto;
	int backup_auto_date;
	int backup_auto_date_unit;
	int backup_auto_time;

protected:

private:

};

extern MgrConfig g_MgrCfg;
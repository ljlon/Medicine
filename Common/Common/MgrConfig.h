#pragma once
#include "StdHead.h"

#define FILE_MGRCFG_INI _T("Configuration\\MgrConfig.ini")

#define SECTION_MYSQL	_T("MySQL")

class MgrConfig
{
public:
	MgrConfig();
	~MgrConfig();

	ERRCODE Load();
	ERRCODE Save();

	//mysql
	CString mysql_install_folder;

protected:

private:

};

extern MgrConfig g_MgrCfg;
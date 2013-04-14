#pragma once
#include "StdHead.h"

#define FILE_CONFIG_INI _T("Configuration\\Config.ini")

#define SECTION_DATABASE	_T("Database")

class Config
{
public:
	Config();
	~Config();

	ERRCODE Load();
	ERRCODE Save();

	//database
	CString database_host;
	int database_port;
	CString database_dbname;
	CString database_uid;
	CString database_pwd;

protected:

private:

};

extern Config g_config;
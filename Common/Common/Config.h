#pragma once
#include "StdHead.h"

#define FILE_CONFIG_INI _T("Configuration\\Config.ini")

#define SECTION_GENERAL	_T("General")
#define SECTION_DATABASE	_T("Database")
#define SECTION_PRINTER      _T("Printer")
#define SECTION_CASHBOX      _T("CashBox")
#define SECTION_DISPALY      _T("Display")

class Config
{
public:
	Config();
	~Config();

	ERRCODE Load();
	ERRCODE Save();

	//factory or debug mode
	int			factory_mode;

	//general
	CString general_company_name;

	//database
	CString database_host;
	int database_port;
	CString database_dbname;
	CString database_uid;
	CString database_pwd;

	//keyboard
	int key_checkout[2];
	int key_num[2];
	int key_del_one[2];
	int key_new_retail[2];

	//printer
	CString printer_name;
	int printer_width;
	int printer_font_width;

	//cashbox
	CString cashbox_name;

	//customer display
	CString customerdispay_name;

protected:

private:

};

extern Config g_config;
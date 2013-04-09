#pragma once
#include "StdHead.h"
#include "Config.h"

#define FILE_POSCFG_INI _T("Configuration\\POSConfig.ini")

#define SECTION_GENERAL	_T("General")
#define SECTION_DATABASE	_T("Database")
#define SECTION_PRINTER      _T("Printer")
#define SECTION_CASHBOX      _T("CashBox")
#define SECTION_DISPALY      _T("Display")

class POSConfig
{
public:
	POSConfig();
	~POSConfig();

	ERRCODE Load();
	ERRCODE Save();

	//factory or debug mode
	int			factory_mode;

	//general
	CString general_company_name;

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

extern POSConfig g_POSCfg;
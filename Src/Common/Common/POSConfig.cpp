#include "stdafx.h"
#include "POSConfig.h"
#include "Crypto.h"

POSConfig g_POSCfg;

POSConfig::POSConfig()
{
	factory_mode = 0;
	printer_width = 384;
	printer_font_width = 12;

	key_checkout[0] = -1;
	key_checkout[1] = -1;
	key_num[0] = -1;
	key_num[1] = -1;
	key_del_one[0] = -1;
	key_del_one[1] = -1;
	key_new_retail[0] = -1;
	key_new_retail[1] = -1;
}

POSConfig::~POSConfig()
{

}

ERRCODE POSConfig::Load()
{
	//general
	GetPrivateProfileString(SECTION_GENERAL, _T("CompanyName"), _T(""), general_company_name.GetBuffer(MAX_PATH), MAX_PATH, FILE_POSCFG_INI);

	//keyboard
	key_checkout[0] = VK_ADD;
	key_checkout[1] = VK_F2;
	key_num[0] = VK_MULTIPLY;
	key_num[1] = VK_F3;
	key_del_one[0] = VK_DECIMAL;
	key_del_one[1] = VK_F4;
	key_new_retail[0] = VK_F12;

	//printer
	GetPrivateProfileString(SECTION_PRINTER, _T("Name"), _T(""), printer_name.GetBuffer(MAX_PATH), MAX_PATH, FILE_POSCFG_INI);

	//cashbox
	GetPrivateProfileString(SECTION_CASHBOX, _T("Name"), _T(""), cashbox_name.GetBuffer(MAX_PATH), MAX_PATH, FILE_POSCFG_INI);

	//display
	GetPrivateProfileString(SECTION_DISPALY, _T("Name"), _T(""), customerdispay_name.GetBuffer(MAX_PATH), MAX_PATH, FILE_POSCFG_INI);

	return err_OK;
}

ERRCODE POSConfig::Save()
{ 
	BOOL bRet = TRUE;

	//General
	bRet = WritePrivateProfileString(SECTION_GENERAL, _T("CompanyName"), general_company_name, FILE_POSCFG_INI);

	//Device
	bRet = WritePrivateProfileString(SECTION_PRINTER, _T("Name"), printer_name, FILE_POSCFG_INI);
	bRet = WritePrivateProfileString(SECTION_CASHBOX, _T("Name"), cashbox_name, FILE_POSCFG_INI);
	bRet = WritePrivateProfileString(SECTION_DISPALY, _T("Name"), customerdispay_name, FILE_POSCFG_INI);

	return err_OK;
}
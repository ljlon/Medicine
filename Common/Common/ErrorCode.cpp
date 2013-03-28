#include "stdafx.h"
#include "ErrorCode.h"

TCHAR * pszPublicErrMsg[] =						// 0x00
{
	_T("�ɹ�"),												//err_OK				 = 0,
	_T("������Ч"),										//err_InvalidParameter	 = 1,
	NULL
};

//file error message:
TCHAR * pszFileErrMsg[] =					    // 0x01
{
	NULL,												//Begin
	_T("���ļ�ʧ��"),								//err_FILE_Open				= ERR_FILE_BEGIN + 1,
	_T("�ļ��ر�ʧ��"),								//err_FILE_Close			= ERR_FILE_BEGIN + 2,
	_T("�ļ���ȡʧ��"),								//err_FILE_Read				= ERR_FILE_BEGIN + 3,
	_T("�ļ�д��ʧ��"),								//err_FILE_Write			= ERR_FILE_BEGIN + 4,
	_T("�ļ�ɾ��ʧ��"),								//err_FILE_Delete			= ERR_FILE_BEGIN + 5,		
	NULL													//End
};

//database error message:
TCHAR * pszDBErrMsg[] =						// 0x2 * 0x100
{
	NULL,											//Begin
	_T("���ݿ�����ʧ��"),							//err_FILE_Open				= ERR_FILE_BEGIN + 1,
	_T("ִ�����ݿ��ѯ����ʧ��"),					//err_DB_Proc_Execute	    = ERR_FILE_BEGIN + 2,
	_T("���ݿⷵ�ؽ�����Ͳ�ƥ��"),					//err_DB_NumFieldNotMatch	= ERR_DB_BEGIN + 3,	//
	NULL											//End
};

//database error message:
TCHAR * pszAccountErrMsg[] =				// 0x3 * 0x100
{
	NULL,												//Begin
	_T("�˻��������������������"),			//err_Account_InvalidPwd = ERR_ACCOUNT_BEGIN + 1,
	_T("�û���Ϣ��Ч"),								//err_Account_InvalidRandomKey	= ERR_ACCOUNT_BEGIN + 2
	NULL													//End
};

//supplier error message:
TCHAR * pszSupplierErrMsg[] =				// 0x4 * 0x100
{
	NULL,												//Begin
	_T("��ӹ�Ӧ��ʧ��"),							//err_Supplier_AddFail = ERR_SUPPLIER_BEGIN + 1,
	_T("�ù�Ӧ���Ѵ���"),							//err_Supplier_AlreadyExist = ERR_SUPPLIER_BEGIN + 2,
	_T("ɾ����Ӧ��ʧ��"),							//err_Supplier_DeleteFail = ERR_SUPPLIER_BEGIN + 3,
	_T("�޸Ĺ�Ӧ��ʧ��"),							//err_Supplier_UpdateFail = ERR_SUPPLIER_BEGIN + 4,
	NULL													//End
};

//supplier error message:
TCHAR * pszVendorErrMsg[] =				// 0x5 * 0x100
{
	NULL,										//Begin
	_T("�����������ʧ��"),						//err_Vendor_AddFail = ERR_VENDOR_BEGIN + 1,
	_T("�����������Ѵ���"),						//err_Vendor_AlreadyExist = ERR_VENDOR_BEGIN + 2,
	_T("ɾ����������ʧ��"),						//err_Vendor_DeleteFail = ERR_VENDOR_BEGIN + 3,
	_T("�޸���������ʧ��"),						//err_Vendor_UpdateFail = ERR_VENDOR_BEGIN + 4,
	NULL										//End
};

//medicine error message:
TCHAR * pszMedicineErrMsg[] =						// 0x6 * 0x100
{
	NULL,											   //Begin
	_T("���ҩƷʧ��"),								//err_Medicine_AddFail = ERR_MEDICINE_BEGIN + 1,
	_T("��ҩƷ�Ѵ���"),								//err_Medicine_AlreadyExist = ERR_MEDICINE_BEGIN + 2,
	_T("ɾ��ҩƷʧ��"),								//err_Medicine_DeleteFail = ERR_MEDICINE_BEGIN + 3,
	_T("�޸�ҩƷʧ��"),								//err_Medicine_UpdateFail = ERR_MEDICINE_BEGIN + 4,
	_T("ҩƷ������"),								    //err_Medicine_NotExist = ERR_MEDICINE_BEGIN + 5,
	_T("����ҩƷ����ʧ��"),						//err_Medicine_Batch_UpdateFail       = ERR_MEDICINE_BEGIN + 6,
	_T("ɾ��ҩƷ����ʧ��"),						//err_Medicine_Batch_Delete       = ERR_MEDICINE_BEGIN + 7,
	NULL											        //End
};

//user error message:
TCHAR * pszUserErrMsg[] =							// 0x7 * 0x100
{
	NULL,											//Begin
	_T("����û�ʧ��"),								//err_User_AddFail = ERR_USER_BEGIN + 1,
	_T("���û��Ѵ���"),								//err_User_AlreadyExist = ERR_USER_BEGIN + 2,
	_T("�û�������"),								//err_User_NotExist = ERR_USER_BEGIN + 3,
	_T("ɾ���û�ʧ��"),								//err_User_DeleteFail = ERR_USER_BEGIN + 4,
	_T("�޸��û�ʧ��"),								//err_User_UpdateFail = ERR_USER_BEGIN + 5,
	NULL											//End
};

//purchase history error message:
TCHAR * pszPurchaseHistoryErrMsg[] =				// 0x8 * 0x100
{
	NULL,											//Begin
	_T("��Ӳɹ���ʷ������Ϣʧ��"),					//err_PurchaseHistory_AddFail = ERR_PURCHASEHISTORY_BEGIN + 1,
	_T("ɾ���ɹ���ʷ������Ϣʧ��"),					//err_PurchaseHistory_DeleteFail = ERR_PURCHASEHISTORY_BEGIN + 2,	
	NULL											//End
};

//purchase error message:
TCHAR * pszStoreErrMsg[] =				// 0x9 * 0x100
{
	NULL,											//Begin
	_T("��治����"),								//err_Medicine_Store_NotExist = ERR_MEDICINE_STORE_BEGIN + 1,
	_T("ɾ�����ʧ��"),								//err_Medicine_Store_Delete           = ERR_MEDICINE_STORE_BEGIN + 2,
	NULL											   //End
};

//pos error code
TCHAR * pszPOSErrMsg[] =				// 0xA * 0x100
{
	NULL,											//Begin
	_T("POS������"),								//err_POS_NotExist				= ERR_POS_BEGIN + 1,
	_T("���POSʧ��"),							//err_POS_AddFail					= ERR_MEDICINE_BEGIN + 2,
	_T("��POS�Ѵ���"),							//err_POS_AlreadyExist			= ERR_MEDICINE_BEGIN + 3,
	_T("����POS��Ϣʧ��"),					//err_POS_UpdateFail			= ERR_MEDICINE_BEGIN + 4,	
	NULL											    //End
};

//printer error message:
TCHAR * pszPrinterErrMsg[] =				// 0x0B * 0x100
{
	NULL,											//Begin
	_T("��ӡ��δ�ҵ�"),							//err_Printer_Not_Found    	= ERR_PINTER_BEGIN + 1,	
	_T("�򿪴�ӡ��ʧ��"),						//err_Printer_Create_Fail			= ERR_PINTER_BEGIN + 2,		
	_T("��ӡ��δ�ر�"),							//err_Printer_Not_Close		    = ERR_PINTER_BEGIN + 3,		
	_T(""),//err_Printer_Start_Doc		    = ERR_PINTER_BEGIN + 4,		
	_T(""),//err_Printer_End_Doc		    = ERR_PINTER_BEGIN + 5,		
	_T(""),//err_Printer_Start_Page		    = ERR_PINTER_BEGIN + 6,		
	_T(""),//err_Printer_End_Page		    = ERR_PINTER_BEGIN + 7,		
	_T(""),//err_Printer_TextOut		        = ERR_PINTER_BEGIN + 8,		
	_T(""),//err_Printer_Write	        = ERR_PINTER_BEGIN + 9,		
	NULL											//End
};

//cashbox error message:
TCHAR * pszCashboxErrMsg[] =				// 0x0C * 0x100
{
	NULL,											//Begin
	_T(""),//err_Cashbox_Create_Fail			= ERR_CASHBOX_BEGIN + 1,	
	_T(""),//err_Cashbox_Not_Close		    = ERR_CASHBOX_BEGIN + 2,		
	_T(""),//err_Cashbox_Open		            = ERR_CASHBOX_BEGIN + 3,		
	NULL											//End
};

//customer display error message:
TCHAR * pszCustomerDisplayrrMsg[] =				// 0x0D* 0x100
{
	NULL,											//Begin
	_T(""),//err_CustomerDisplay_Create_Fail			= ERR_CUSTOMERDISPLAY_BEGIN + 1,	
	_T(""),//err_CustomerDisplay_Not_Close		    = ERR_CUSTOMERDISPLAY_BEGIN + 2,		
	_T(""),//err_CustomerDisplay_Open		            = ERR_CUSTOMERDISPLAY_BEGIN + 3,		
	_T(""),//err_CustomerDisplay_Write		            = ERR_CUSTOMERDISPLAY_BEGIN + 4,
	NULL											//End
};

TCHAR ** g_ppszErrMsg[] =
{
	pszPublicErrMsg,			//0x00, public common
	pszFileErrMsg,				//0x01, file
	pszDBErrMsg,				//0x02, database
	pszAccountErrMsg,		//0x03, account
	pszSupplierErrMsg,		//0x04, supplier
	pszVendorErrMsg,			//0x05, vendor
	pszMedicineErrMsg,		//0x06, medicine
	pszUserErrMsg,				//0x07 user
	pszPurchaseHistoryErrMsg, //0x08 purchase history
	pszStoreErrMsg,		    //0x09 store
	pszPOSErrMsg,             //0x0A pos
	pszPrinterErrMsg,			//0x0B purchase
	pszCashboxErrMsg,		//0x0C printer
	pszCustomerDisplayrrMsg,		//0xD customer display 
	NULL										//id for last one;
};

CString GetErrMsg(ERRCODE errCode)
{
	CString csErrorMsg;
	if (errCode == -1)
	{

	}
	else if (errCode >= ERR_LAST_ID)
	{

	}
	else if (g_ppszErrMsg[(errCode&0XFF00)>>8] != NULL && g_ppszErrMsg[(errCode&0XFF00)>>8][errCode&0XFF])
	{
		csErrorMsg = LPTSTR(g_ppszErrMsg[(errCode&0XFF00)>>8][errCode&0XFF]);
	}	
	else 
	{

	}

	return csErrorMsg;
}
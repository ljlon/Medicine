#pragma once

#ifndef ERRCODE
#define ERRCODE unsigned short
#endif

const ERRCODE
//----------------------------------------------------------------
//public error code:
//----------------------------------------------------------------
//
err_OK					= 0,
err_InvalidParameter    = 1,
err_MemoryNotEnough = 2,
err_Not_Find_Adapter    = 3,

//----------------------------------------------------------------
//file error code:
//----------------------------------------------------------------
ERR_FILE_BEGIN			= 0x1 * 0x100,
err_FILE_Open			= ERR_FILE_BEGIN + 1,	    //�ļ��򿪴���
err_FILE_Close			= ERR_FILE_BEGIN + 2,		//�ļ��رմ���
err_FILE_Read			= ERR_FILE_BEGIN + 3,		//�ļ���ȡ����
err_FILE_Write			= ERR_FILE_BEGIN + 4,		//�ļ�д�����
err_FILE_Delete			= ERR_FILE_BEGIN + 5,		//�ļ�ɾ������

//----------------------------------------------------------------
//database error code
//----------------------------------------------------------------
ERR_DB_BEGIN					= 0x2 * 0x100,
err_DB_Open						= ERR_DB_BEGIN + 1,	//���ݿ�����ʧ��
err_DB_Proc_Execute				= ERR_DB_BEGIN + 2,	//ִ�в�ѯ���ʧ��
err_DB_NumFieldNotMatch		    = ERR_DB_BEGIN + 3,	//���ݿⷵ�ؽ�����Ͳ�ƥ��

//----------------------------------------------------------------
//account error code
//----------------------------------------------------------------
ERR_ACCOUNT_BEGIN				= 0x3 * 0x100,
err_Account_InvalidPwd			= ERR_ACCOUNT_BEGIN + 1,			//�˻����������
err_Account_InvalidRandomKey	= ERR_ACCOUNT_BEGIN + 2,		//��Ч�����Key

//supplier error code
ERR_SUPPLIER_BEGIN				= 0x4 * 0x100,
err_Supplier_AddFail				= ERR_SUPPLIER_BEGIN + 1,		//��ӹ�Ӧ��ʧ��
err_Supplier_AlreadyExist		= ERR_SUPPLIER_BEGIN + 2,		//��Ӧ���Ѵ���
err_Supplier_DeleteFail			= ERR_SUPPLIER_BEGIN + 3,		//ɾ����Ӧ��ʧ��
err_Supplier_UpdateFail			= ERR_SUPPLIER_BEGIN + 4,		//�޸Ĺ�Ӧ��ʧ��

//vendor error code
ERR_VENDOR_BEGIN				= 0x5 * 0x100,
err_Vendor_AddFail				= ERR_VENDOR_BEGIN + 1,		//�����������ʧ��
err_Vendor_AlreadyExist			= ERR_VENDOR_BEGIN + 2,		//���������Ѵ���
err_Vendor_DeleteFail			= ERR_VENDOR_BEGIN + 3,		//ɾ����������ʧ��
err_Vendor_UpdateFail			= ERR_VENDOR_BEGIN + 4,		//�޸���������ʧ��

//medicine error code
ERR_MEDICINE_BEGIN				= 0x6 * 0x100,
err_Medicine_AddFail					= ERR_MEDICINE_BEGIN + 1,	//���ҩƷʧ��
err_Medicine_AlreadyExist			= ERR_MEDICINE_BEGIN + 2,		//��ҩƷ�Ѵ���
err_Medicine_DeleteFail				= ERR_MEDICINE_BEGIN + 3,		//ɾ��ҩƷʧ��
err_Medicine_UpdateFail				= ERR_MEDICINE_BEGIN + 4,		//�޸�ҩƷʧ��
err_Medicine_NotExist				= ERR_MEDICINE_BEGIN + 5,		//ҩƷ������
err_Medicine_Batch_UpdateFail	= ERR_MEDICINE_BEGIN + 6,		
err_Medicine_Batch_Delete			= ERR_MEDICINE_BEGIN + 7,	

//user error code
ERR_USER_BEGIN					= 0x7 * 0x100,
err_User_AddFail				= ERR_USER_BEGIN + 1,		//����û�ʧ��
err_User_AlreadyExist			= ERR_USER_BEGIN + 2,		//���û��Ѵ���
err_User_NotExist				= ERR_USER_BEGIN + 3,		//�û�������
err_User_DeleteFail				= ERR_USER_BEGIN + 4,		//ɾ���û�ʧ��
err_User_UpdateFail				= ERR_USER_BEGIN + 5,		//�޸��û�ʧ��

//purchase error code
ERR_PURCHASE_BEGIN				= 0x8 * 0x100,
err_Purchase_AddFail			= ERR_PURCHASE_BEGIN + 1,		//��Ӳɹ�ʧ��
err_Purchase_DeleteFail			= ERR_PURCHASE_BEGIN + 2,		//ɾ������ʧ��

//sotre error code
ERR_MEDICINE_STORE_BEGIN			= 0x9 * 0x100,
err_Medicine_Store_NotExist			= ERR_MEDICINE_STORE_BEGIN + 1,
err_Medicine_Store_Delete           = ERR_MEDICINE_STORE_BEGIN + 2,

//pos error code
ERR_POS_BEGIN			= 0xA * 0x100,
err_POS_NotExist				= ERR_POS_BEGIN + 1,				//POS������
err_POS_AddFail					= ERR_MEDICINE_BEGIN + 2,		//���POSʧ��
err_POS_AlreadyExist			= ERR_MEDICINE_BEGIN + 3,		//��POS�Ѵ���
err_POS_UpdateFail			= ERR_MEDICINE_BEGIN + 4,		//����POS��Ϣʧ��

//printer code
ERR_PINTER_BEGIN			= 0x0B * 0x100,
err_Printer_Not_Found    	= ERR_PINTER_BEGIN + 1,		//��ӡ��δ�ҵ�
err_Printer_Create_Fail			= ERR_PINTER_BEGIN + 2,		//�򿪴�ӡ��ʧ��
err_Printer_Not_Close		    = ERR_PINTER_BEGIN + 3,		//��ӡ��δ�ر�
err_Printer_Start_Doc		    = ERR_PINTER_BEGIN + 4,		//
err_Printer_End_Doc		    = ERR_PINTER_BEGIN + 5,		//
err_Printer_Start_Page		    = ERR_PINTER_BEGIN + 6,		//
err_Printer_End_Page		    = ERR_PINTER_BEGIN + 7,		//
err_Printer_TextOut		        = ERR_PINTER_BEGIN + 8,		//
err_Printer_Write	        = ERR_PINTER_BEGIN + 9,		//

//cashbox code
ERR_CASHBOX_BEGIN			= 0x0C * 0x100,
err_Cashbox_Create_Fail			= ERR_CASHBOX_BEGIN + 1,	//
err_Cashbox_Not_Close		    = ERR_CASHBOX_BEGIN + 2,		//
err_Cashbox_Open		            = ERR_CASHBOX_BEGIN + 3,		//

//display code
ERR_CUSTOMERDISPLAY_BEGIN			= 0x0E * 0x100,
err_CustomerDisplay_Create_Fail			= ERR_CUSTOMERDISPLAY_BEGIN + 1,	//
err_CustomerDisplay_Not_Close		    = ERR_CUSTOMERDISPLAY_BEGIN + 2,		//
err_CustomerDisplay_Open		            = ERR_CUSTOMERDISPLAY_BEGIN + 3,		//
err_CustomerDisplay_Write		            = ERR_CUSTOMERDISPLAY_BEGIN + 4,//

//----------------------------------------------------------------
//last error code:
//----------------------------------------------------------------
ERR_LAST_ID				= 0x2700;

CString GetErrMsg(ERRCODE errCode);
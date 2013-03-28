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
err_FILE_Open			= ERR_FILE_BEGIN + 1,	    //文件打开错误
err_FILE_Close			= ERR_FILE_BEGIN + 2,		//文件关闭错误
err_FILE_Read			= ERR_FILE_BEGIN + 3,		//文件读取错误
err_FILE_Write			= ERR_FILE_BEGIN + 4,		//文件写入错误
err_FILE_Delete			= ERR_FILE_BEGIN + 5,		//文件删除错误

//----------------------------------------------------------------
//database error code
//----------------------------------------------------------------
ERR_DB_BEGIN					= 0x2 * 0x100,
err_DB_Open						= ERR_DB_BEGIN + 1,	//数据库连接失败
err_DB_Proc_Execute				= ERR_DB_BEGIN + 2,	//执行查询语句失败
err_DB_NumFieldNotMatch		    = ERR_DB_BEGIN + 3,	//数据库返回结果类型不匹配

//----------------------------------------------------------------
//account error code
//----------------------------------------------------------------
ERR_ACCOUNT_BEGIN				= 0x3 * 0x100,
err_Account_InvalidPwd			= ERR_ACCOUNT_BEGIN + 1,			//账户或密码错误
err_Account_InvalidRandomKey	= ERR_ACCOUNT_BEGIN + 2,		//无效的随机Key

//supplier error code
ERR_SUPPLIER_BEGIN				= 0x4 * 0x100,
err_Supplier_AddFail				= ERR_SUPPLIER_BEGIN + 1,		//添加供应商失败
err_Supplier_AlreadyExist		= ERR_SUPPLIER_BEGIN + 2,		//供应商已存在
err_Supplier_DeleteFail			= ERR_SUPPLIER_BEGIN + 3,		//删除供应商失败
err_Supplier_UpdateFail			= ERR_SUPPLIER_BEGIN + 4,		//修改供应商失败

//vendor error code
ERR_VENDOR_BEGIN				= 0x5 * 0x100,
err_Vendor_AddFail				= ERR_VENDOR_BEGIN + 1,		//添加生产厂家失败
err_Vendor_AlreadyExist			= ERR_VENDOR_BEGIN + 2,		//生产厂家已存在
err_Vendor_DeleteFail			= ERR_VENDOR_BEGIN + 3,		//删除生产厂家失败
err_Vendor_UpdateFail			= ERR_VENDOR_BEGIN + 4,		//修改生产厂家失败

//medicine error code
ERR_MEDICINE_BEGIN				= 0x6 * 0x100,
err_Medicine_AddFail					= ERR_MEDICINE_BEGIN + 1,	//添加药品失败
err_Medicine_AlreadyExist			= ERR_MEDICINE_BEGIN + 2,		//该药品已存在
err_Medicine_DeleteFail				= ERR_MEDICINE_BEGIN + 3,		//删除药品失败
err_Medicine_UpdateFail				= ERR_MEDICINE_BEGIN + 4,		//修改药品失败
err_Medicine_NotExist				= ERR_MEDICINE_BEGIN + 5,		//药品不存在
err_Medicine_Batch_UpdateFail	= ERR_MEDICINE_BEGIN + 6,		
err_Medicine_Batch_Delete			= ERR_MEDICINE_BEGIN + 7,	

//user error code
ERR_USER_BEGIN					= 0x7 * 0x100,
err_User_AddFail				= ERR_USER_BEGIN + 1,		//添加用户失败
err_User_AlreadyExist			= ERR_USER_BEGIN + 2,		//该用户已存在
err_User_NotExist				= ERR_USER_BEGIN + 3,		//用户不存在
err_User_DeleteFail				= ERR_USER_BEGIN + 4,		//删除用户失败
err_User_UpdateFail				= ERR_USER_BEGIN + 5,		//修改用户失败

//purchase error code
ERR_PURCHASE_BEGIN				= 0x8 * 0x100,
err_Purchase_AddFail			= ERR_PURCHASE_BEGIN + 1,		//添加采购失败
err_Purchase_DeleteFail			= ERR_PURCHASE_BEGIN + 2,		//删除订单失败

//sotre error code
ERR_MEDICINE_STORE_BEGIN			= 0x9 * 0x100,
err_Medicine_Store_NotExist			= ERR_MEDICINE_STORE_BEGIN + 1,
err_Medicine_Store_Delete           = ERR_MEDICINE_STORE_BEGIN + 2,

//pos error code
ERR_POS_BEGIN			= 0xA * 0x100,
err_POS_NotExist				= ERR_POS_BEGIN + 1,				//POS不存在
err_POS_AddFail					= ERR_MEDICINE_BEGIN + 2,		//添加POS失败
err_POS_AlreadyExist			= ERR_MEDICINE_BEGIN + 3,		//该POS已存在
err_POS_UpdateFail			= ERR_MEDICINE_BEGIN + 4,		//更新POS信息失败

//printer code
ERR_PINTER_BEGIN			= 0x0B * 0x100,
err_Printer_Not_Found    	= ERR_PINTER_BEGIN + 1,		//打印机未找到
err_Printer_Create_Fail			= ERR_PINTER_BEGIN + 2,		//打开打印机失败
err_Printer_Not_Close		    = ERR_PINTER_BEGIN + 3,		//打印机未关闭
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
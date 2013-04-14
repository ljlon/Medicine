#pragma once
#include <vector>
#include "mysql.h"

using namespace std;

//Database type
enum DBType{
	DB_MYSQL = 0,
	DB_SQLSERVER = 1,
	DB_ORACLE = 2,
};

//ADO
enum DataTypeEnum{
	adEmpty = 0,			//没有值 (DBTYPE_EMPTY)。
	adSmallInt	= 2,		//一个双字节的有符号整数 (DBTYPE_I2)。
	adInteger = 3,		//一个四字节的有符号整数 (DBTYPE_I4)。
	adSingle = 4,			//一个单精度浮点值 (DBTYPE_R4)。
	adDouble	= 5,		//一个双精度浮点值 (DBTYPE_R8)。
	adCurrency = 6,		//一个货币值 (DBTYPE_CY)。货币是一个定点数字，小数点右侧有四位数字。该值存储为八字节、范围为 10,000 的有符号整数。
	adDate	= 7,			//日期值 (DBTYPE_DATE)。日期保存为双精度数，数字的整数部分是从 1899 年 12 月 30 日算起的天数，小数部分是一天当中的片段时间。
	adBSTR	= 8,			//以 Null 终止的字符串 (Unicode) (DBTYPE_BSTR)。
	adIDispatch = 9,	//指向 COM 对象上 IDispatch 接口的指针 (DBTYPE_IDISPATCH)。注意:ADO 目前不支持这种数据类型。使用它可能导致不可预料的结果。
   adError = 10,			 //一个 32 位的错误代码 (DBTYPE_ERROR)。
   adBoolean	= 11,		//一个布尔值 (DBTYPE_BOOL)。
   adVariant = 12,		//一个 Automation Variant (DBTYPE_VARIANT)。注意:ADO 目前不支持这种数据类型。使用它可能导致不可预料的结果。
   adIUnknown = 13,	 //   指向 COM 对象上 IUnknown 接口的指针 (DBTYPE_IUNKNOWN)。注意:ADO 目前不支持这种数据类型。使用它可能导致不可预料的结果。
   adDecimal = 14, 		//具有固定精度和范围的确切数字值 (DBTYPE_DECIMAL)。adTinyInt	16	一个单字节的有符号整数 (DBTYPE_I1)。
   adUnsignedTinyInt = 17,		//一个单字节的无符号整数 (DBTYPE_UI1)。
   adUnsignedSmallInt = 18,	 //一个双字节的无符号整数 (DBTYPE_UI2)。
   adUnsignedInt = 19,			//一个四字节的无符号整数 (DBTYPE_UI4)。
   adBigInt	 = 20,					//一个八字节的有符号整数 (DBTYPE_I8)。
   adUnsignedBigInt = 21,		//	一个八字节的无符号整数 (DBTYPE_UI8)。
   adFileTime = 	64,				//一个 64 位的值，表示从 1601 年 1 月 1 日开始的 100 个十亿分之一秒间隔的数量 (DBTYPE_FILETIME)。
   adGUID	= 	72	,					//全局唯一标识符 (GUID) (DBTYPE_GUID)。
   adBinary	 = 128,					//一个二进制值 (DBTYPE_BYTES)。
   adChar = 	129,					//一个字符串值 (DBTYPE_STR)。.
   adWChar = 130,					//一个以 Null 终止的 Unicode 字符串 (DBTYPE_WSTR)。
   adNumeric	= 131,				//具有固定精度和范围的确切数字值 (DBTYPE_NUMERIC)。
   adUserDefined = 132,			//一个用户定义的变量 (DBTYPE_UDT)。
   adDBDate	= 	133,				//日期值 (yyyymmdd) (DBTYPE_DBDATE)。
   adDBTime = 134	,				//时间值 (hhmmss) (DBTYPE_DBTIME)。
   adDBTimeStamp	= 	135,		//日期/时间戳（yyyymmddhhmmss 加十亿分之一的小数）(DBTYPE_DBTIMESTAMP)。
   adChapter	= 	136,				//一个四字节的子集值，标识子行集合中的行 (DBTYPE_HCHAPTER)。
   adPropVariant = 138,			//一个 Automation PROPVARIANT (DBTYPE_PROP_VARIANT)。
   adVarNumeric = 139,			//一个数字值（仅限于 Parameter 对象）。
   adVarChar	= 	200,				//一个字符串值（仅限于 Parameter 对象）。
   adLongVarChar	= 	201,		//一个长字符串值（仅限于 Parameter 对象）。
   adVarWChar	= 	202,			//一个以 Null 终止的 Unicode 字符串（仅限于 Parameter 对象）。
   adLongVarWChar = 203,		//一个以 Null 终止的长 Unicode 字符串值（仅限于 Parameter 对象）。
   adVarBinary = 204,				//一个二进制值（仅限于 Parameter 对象）。
   adLongVarBinary = 205,		//一个长二进制值（仅限于 Parameter 对象）。
   AdArray	= 	0x2000,				//一个标志值，通常与另一个数据类型常量组合，指示该数据类型的数组。
};

enum ParameterDirectionEnum{
	adParamUnknown = 	0,		//指示该参数的方向未知。
	adParamInput = 1,				//默认值。指示该参数是输入参数
	adParamOutput	= 2,			//指示该参数是输出参数。
	adParamInputOutput = 3,	//指示该参数既是输入参数，又是输出参数。
	adParamReturnValue = 4,   //指示该参数是返回值。
};

class CDatabase
{
public:
	CDatabase();
	~CDatabase();

	//打开，关闭
	BOOL Connect();
	BOOL Disconnect();
	BOOL BeConnected();

	//获取错误信息
	CString GetLastErrorMsg();

	//存储过程
	BOOL ProcedureInit(LPCSTR pProcedureName);
	BOOL ProcedureAddParam(LPCSTR pName, DataTypeEnum dataType, ParameterDirectionEnum direction, const LPVOID pValue = NULL);
	BOOL ProcedureExecute();
	BOOL ProcedureGetOutParam(LPCSTR pName, DataTypeEnum dataType, const LPVOID pValue);
	MYSQL_RES *ProcedureGetResult(); //需要手动释放MYSQL_ERS, mysql_free_result(results);

	//释放
	BOOL FreeOtherResults();

private:
	MYSQL m_mysql;
	BOOL m_bConnected;
	DBType m_dbType;
	CString m_csLastErrorMsg;
	CString m_csProcedureName;
	vector<CString> m_vctProcedureParam;
	
};
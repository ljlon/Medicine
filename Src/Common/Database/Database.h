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
	adEmpty = 0,			//û��ֵ (DBTYPE_EMPTY)��
	adSmallInt	= 2,		//һ��˫�ֽڵ��з������� (DBTYPE_I2)��
	adInteger = 3,		//һ�����ֽڵ��з������� (DBTYPE_I4)��
	adSingle = 4,			//һ�������ȸ���ֵ (DBTYPE_R4)��
	adDouble	= 5,		//һ��˫���ȸ���ֵ (DBTYPE_R8)��
	adCurrency = 6,		//һ������ֵ (DBTYPE_CY)��������һ���������֣�С�����Ҳ�����λ���֡���ֵ�洢Ϊ���ֽڡ���ΧΪ 10,000 ���з���������
	adDate	= 7,			//����ֵ (DBTYPE_DATE)�����ڱ���Ϊ˫�����������ֵ����������Ǵ� 1899 �� 12 �� 30 �������������С��������һ�쵱�е�Ƭ��ʱ�䡣
	adBSTR	= 8,			//�� Null ��ֹ���ַ��� (Unicode) (DBTYPE_BSTR)��
	adIDispatch = 9,	//ָ�� COM ������ IDispatch �ӿڵ�ָ�� (DBTYPE_IDISPATCH)��ע��:ADO Ŀǰ��֧�������������͡�ʹ�������ܵ��²���Ԥ�ϵĽ����
   adError = 10,			 //һ�� 32 λ�Ĵ������ (DBTYPE_ERROR)��
   adBoolean	= 11,		//һ������ֵ (DBTYPE_BOOL)��
   adVariant = 12,		//һ�� Automation Variant (DBTYPE_VARIANT)��ע��:ADO Ŀǰ��֧�������������͡�ʹ�������ܵ��²���Ԥ�ϵĽ����
   adIUnknown = 13,	 //   ָ�� COM ������ IUnknown �ӿڵ�ָ�� (DBTYPE_IUNKNOWN)��ע��:ADO Ŀǰ��֧�������������͡�ʹ�������ܵ��²���Ԥ�ϵĽ����
   adDecimal = 14, 		//���й̶����Ⱥͷ�Χ��ȷ������ֵ (DBTYPE_DECIMAL)��adTinyInt	16	һ�����ֽڵ��з������� (DBTYPE_I1)��
   adUnsignedTinyInt = 17,		//һ�����ֽڵ��޷������� (DBTYPE_UI1)��
   adUnsignedSmallInt = 18,	 //һ��˫�ֽڵ��޷������� (DBTYPE_UI2)��
   adUnsignedInt = 19,			//һ�����ֽڵ��޷������� (DBTYPE_UI4)��
   adBigInt	 = 20,					//һ�����ֽڵ��з������� (DBTYPE_I8)��
   adUnsignedBigInt = 21,		//	һ�����ֽڵ��޷������� (DBTYPE_UI8)��
   adFileTime = 	64,				//һ�� 64 λ��ֵ����ʾ�� 1601 �� 1 �� 1 �տ�ʼ�� 100 ��ʮ�ڷ�֮һ���������� (DBTYPE_FILETIME)��
   adGUID	= 	72	,					//ȫ��Ψһ��ʶ�� (GUID) (DBTYPE_GUID)��
   adBinary	 = 128,					//һ��������ֵ (DBTYPE_BYTES)��
   adChar = 	129,					//һ���ַ���ֵ (DBTYPE_STR)��.
   adWChar = 130,					//һ���� Null ��ֹ�� Unicode �ַ��� (DBTYPE_WSTR)��
   adNumeric	= 131,				//���й̶����Ⱥͷ�Χ��ȷ������ֵ (DBTYPE_NUMERIC)��
   adUserDefined = 132,			//һ���û�����ı��� (DBTYPE_UDT)��
   adDBDate	= 	133,				//����ֵ (yyyymmdd) (DBTYPE_DBDATE)��
   adDBTime = 134	,				//ʱ��ֵ (hhmmss) (DBTYPE_DBTIME)��
   adDBTimeStamp	= 	135,		//����/ʱ�����yyyymmddhhmmss ��ʮ�ڷ�֮һ��С����(DBTYPE_DBTIMESTAMP)��
   adChapter	= 	136,				//һ�����ֽڵ��Ӽ�ֵ����ʶ���м����е��� (DBTYPE_HCHAPTER)��
   adPropVariant = 138,			//һ�� Automation PROPVARIANT (DBTYPE_PROP_VARIANT)��
   adVarNumeric = 139,			//һ������ֵ�������� Parameter ���󣩡�
   adVarChar	= 	200,				//һ���ַ���ֵ�������� Parameter ���󣩡�
   adLongVarChar	= 	201,		//һ�����ַ���ֵ�������� Parameter ���󣩡�
   adVarWChar	= 	202,			//һ���� Null ��ֹ�� Unicode �ַ����������� Parameter ���󣩡�
   adLongVarWChar = 203,		//һ���� Null ��ֹ�ĳ� Unicode �ַ���ֵ�������� Parameter ���󣩡�
   adVarBinary = 204,				//һ��������ֵ�������� Parameter ���󣩡�
   adLongVarBinary = 205,		//һ����������ֵ�������� Parameter ���󣩡�
   AdArray	= 	0x2000,				//һ����־ֵ��ͨ������һ���������ͳ�����ϣ�ָʾ���������͵����顣
};

enum ParameterDirectionEnum{
	adParamUnknown = 	0,		//ָʾ�ò����ķ���δ֪��
	adParamInput = 1,				//Ĭ��ֵ��ָʾ�ò������������
	adParamOutput	= 2,			//ָʾ�ò��������������
	adParamInputOutput = 3,	//ָʾ�ò�����������������������������
	adParamReturnValue = 4,   //ָʾ�ò����Ƿ���ֵ��
};

class CDatabase
{
public:
	CDatabase();
	~CDatabase();

	//�򿪣��ر�
	BOOL Connect();
	BOOL Disconnect();
	BOOL BeConnected();

	//��ȡ������Ϣ
	CString GetLastErrorMsg();

	//�洢����
	BOOL ProcedureInit(LPCSTR pProcedureName);
	BOOL ProcedureAddParam(LPCSTR pName, DataTypeEnum dataType, ParameterDirectionEnum direction, const LPVOID pValue = NULL);
	BOOL ProcedureExecute();
	BOOL ProcedureGetOutParam(LPCSTR pName, DataTypeEnum dataType, const LPVOID pValue);
	MYSQL_RES *ProcedureGetResult(); //��Ҫ�ֶ��ͷ�MYSQL_ERS, mysql_free_result(results);

	//�ͷ�
	BOOL FreeOtherResults();

private:
	MYSQL m_mysql;
	BOOL m_bConnected;
	DBType m_dbType;
	CString m_csLastErrorMsg;
	CString m_csProcedureName;
	vector<CString> m_vctProcedureParam;
	
};
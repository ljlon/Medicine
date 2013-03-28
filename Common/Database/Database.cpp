#include "stdafx.h"
#include "Database.h"
#include "Config.h"

CDatabase::CDatabase()
{
	m_dbType = DB_MYSQL;
	m_bConnected = FALSE;
	m_csLastErrorMsg = _T("");
}

CDatabase::~CDatabase()
{
	Disconnect();
}

CString CDatabase::GetLastErrorMsg()
{
	return m_csLastErrorMsg;
}

BOOL CDatabase::Connect()
{
	if (m_bConnected == TRUE)
	{
		Disconnect();
	}

	if (m_dbType == DB_MYSQL)
	{
		mysql_init(&m_mysql);

		if(!mysql_real_connect(&m_mysql, 
			g_config.database_host.GetBuffer(), 
			g_config.database_uid.GetBuffer(), 
			g_config.database_pwd.GetBuffer(),
			g_config.database_dbname.GetBuffer(),
			g_config.database_port,
			NULL,
			CLIENT_MULTI_RESULTS))
		{
			m_csLastErrorMsg.Format(_T("连接数据库：连接数据库时发生错误!%d,%s!"), mysql_errno(&m_mysql), mysql_error(&m_mysql));
			m_bConnected = FALSE;
			return FALSE;
		}
	}
	else
	{
		m_bConnected = FALSE;
		return FALSE;
	}

	m_bConnected = TRUE;

	return TRUE;
}

//关闭链接
BOOL CDatabase::Disconnect()
{
	if (m_bConnected)
	{
		if (m_dbType == DB_MYSQL)
		{
			mysql_close(&m_mysql);
			m_bConnected = FALSE;
		}
	}

	return TRUE;
}

BOOL CDatabase::BeConnected()
{
	return m_bConnected;
}

BOOL CDatabase::ProcedureInit(LPCSTR pProcedureName)
{
	if (!m_bConnected)
	{
		m_csLastErrorMsg.Format(_T("初始化存储过程：数据库未连接!"));

		if (Connect()!= TRUE)
		{
			return FALSE;
		}
	}

	m_csProcedureName = pProcedureName;
	m_vctProcedureParam.clear();

	return TRUE;
}

BOOL CDatabase::ProcedureAddParam(LPCSTR pName, DataTypeEnum dataType, ParameterDirectionEnum direction, const LPVOID pValue)
{
	if (!m_bConnected)
	{
		m_csLastErrorMsg.Format(_T("添加存储过程参数：数据库未连接!"));
		if (Connect()!= TRUE)
		{
			return FALSE;
		}
	}

	CString csParam;
	if (direction == adParamInput)
	{
		if (pValue == NULL)
		{
			csParam.Format("null");
		}
		else if (dataType == adInteger)
		{
			csParam.Format("%d", *(LONG*)pValue);
		}
		else if (dataType == adVarChar)
		{
			if (strlen((TCHAR*)pValue) == 0)
			{
				csParam.Format("null");
			}
			else
			{
				csParam.Format("'%s'", pValue);
			}
		}
		else if (dataType == adDouble)
		{
			csParam.Format("%f", *(double*)pValue);
		}
		else
		{
			m_csLastErrorMsg.Format(_T("添加存储过程参数：参数无效!"));
			return FALSE;
		}
	}
	else if (direction == adParamOutput)
	{
		if (pName == NULL)
		{
			m_csLastErrorMsg.Format(_T("添加存储过程参数：参数无效!"));
			return FALSE;
		}
		csParam.Format("@%s", pName);
	}
	else
	{
		m_csLastErrorMsg.Format(_T("添加存储过程参数：参数无效!"));
		return FALSE;
	}

	m_vctProcedureParam.push_back(csParam);
	return TRUE;
}

BOOL CDatabase::ProcedureExecute()
{
	if (!m_bConnected)
	{
		m_csLastErrorMsg.Format(_T("执行存储过程：数据库未连接!"));
		if (Connect()!= TRUE)
		{
			return FALSE;
		}
	}

	mysql_query(&m_mysql,"SET NAMES GBK");

	CString csQueryProcedure;
	csQueryProcedure.Format("CALL %s(", m_csProcedureName);
	if (m_vctProcedureParam.size())
	{
		csQueryProcedure.AppendFormat("%s", m_vctProcedureParam[0]);
	}
	for (unsigned int i = 1; i < m_vctProcedureParam.size(); i++)
	{
		csQueryProcedure.AppendFormat(",%s", m_vctProcedureParam[i]); 
	}
	csQueryProcedure.Append(");");
	int iRet = mysql_query(&m_mysql,(const char*)(LPCSTR)csQueryProcedure);
	if (iRet != 0)
	{
		m_csLastErrorMsg.Format(_T("执行存储过程：数据库查询，执行存储过程失败!%d,%s!"), mysql_errno(&m_mysql), mysql_error(&m_mysql));
		return FALSE;
	}

	return TRUE;
}

MYSQL_RES *CDatabase::ProcedureGetResult()
{
	if (!m_bConnected)
	{
		m_csLastErrorMsg.Format(_T("获取存储过程输出结果：数据库未连接!"));
		if (Connect()!= TRUE)
		{
			return FALSE;
		}
	}
	MYSQL_RES* pResults = NULL;
	pResults = mysql_store_result(&m_mysql);

	return pResults;
}

BOOL CDatabase::ProcedureGetOutParam(LPCSTR pName, DataTypeEnum dataType, const LPVOID pValue)
{
	if (!m_bConnected)
	{
		m_csLastErrorMsg.Format(_T("获取存储过程输出参数：数据库未连接!"));
		if (Connect()!= TRUE)
		{
			return FALSE;
		}
	}

	BOOL bRet = TRUE;
	CString csQuery;
	csQuery.Format("SELECT @%s;", pName);
	int iRet = mysql_query(&m_mysql, (const char*)(LPCSTR)csQuery);
	if (iRet != 0)
	{
		m_csLastErrorMsg.Format(_T("获取存储过程输出参数：数据库查询，选择输出参数失败!%d,%s!"), mysql_errno(&m_mysql), mysql_error(&m_mysql));
		return FALSE;
	}

	MYSQL_RES* pResults = NULL;	//结果集
	MYSQL_ROW record;	//行记录
	
	pResults=mysql_store_result(&m_mysql);
	if((record=mysql_fetch_row(pResults)))
	{
		//mysql_num_fields(pResults);

		if (record[0] == NULL)
		{
			m_csLastErrorMsg.Format(_T("获取存储过程输出参数：获取输出参数失败!"));
			bRet = FALSE;
		}
		else
		{
			if (pValue == NULL)
			{

			}
			else if (dataType == adInteger)
			{
				*(LONG*)pValue = atol(record[0]);
			}
			else if (dataType == adVarChar)
			{
				*(char**)pValue = new char[strlen(record[0]) + 1];
				memset(*(char**)pValue, 0, strlen(record[0]) + 1);
				memcpy(*(char**)pValue, record[0], strlen(record[0]));
			}
			else if (dataType == adDouble)
			{
				*(double*)pValue = atof(record[0]);
			}
			else
			{
				m_csLastErrorMsg.Format(_T("获取存储过程输出参数：参数无效!"));
				bRet = FALSE;
			}
		}
	}
	mysql_free_result(pResults);

	FreeOtherResults();

	return bRet;
}

BOOL CDatabase::FreeOtherResults()
{
	BOOL bRet = TRUE;
	MYSQL_RES *pResults = NULL;

	while (TRUE)
	{
		int iRet = mysql_next_result(&m_mysql);
		if (iRet == 0)
		{
			//成功，还有结果
			pResults=mysql_store_result(&m_mysql);

			mysql_free_result(pResults);
		}
		else if (iRet == -1)
		{
			//成功，没有下一个结果
			break;;
		}
		else if (iRet > 0)
		{
			//失败
			m_csLastErrorMsg.Format(_T("获取存储过程输出参数：获取结果集失败!errCode=%d"), iRet);
			bRet = FALSE;
		}
	}
	
	return bRet;
}
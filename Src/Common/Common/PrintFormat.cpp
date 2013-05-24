#include "stdafx.h"
#include "PrintFormat.h"

CPrintFormat g_printFormat;

CPrintFormat::CPrintFormat()
{
	m_pbyFormatStr = NULL;
	m_dwFormatStrSize = 0;
}

CPrintFormat::~CPrintFormat()
{
	m_dwFormatStrSize = 0;
	if (m_pbyFormatStr != NULL)
	{
		delete m_pbyFormatStr;
		m_pbyFormatStr = NULL;
	}
}

ERRCODE CPrintFormat::Load()
{
	m_dwFormatStrSize = 0;
	if (m_pbyFormatStr != NULL)
	{
		delete m_pbyFormatStr;
		m_pbyFormatStr = NULL;
	}
	
	HANDLE hFile = CreateFile(FILE_PRINTFORMAT_TXT, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return err_FILE_Open;
	}

	DWORD dwFileSize = GetFileSize(hFile, &dwFileSize);
	if (dwFileSize == INVALID_FILE_SIZE)
	{
		CloseHandle(hFile);
		return err_FILE_Read;
	}

	if (dwFileSize == 0)
	{
		CloseHandle(hFile);
		return err_OK;
	}

	m_dwFormatStrSize = dwFileSize;
	m_pbyFormatStr = new BYTE[m_dwFormatStrSize + 1];
	memset(m_pbyFormatStr, 0, m_dwFormatStrSize + 1);
	DWORD dwReadSize = 0;
	if (ReadFile(hFile, m_pbyFormatStr, dwFileSize, &dwReadSize, NULL) == FALSE)
	{
		delete m_pbyFormatStr;
		m_pbyFormatStr = NULL;
		CloseHandle(hFile);
		return err_FILE_Read;
	}
	CloseHandle(hFile);

	return err_OK;
}

ERRCODE CPrintFormat::Save()
{ 
	HANDLE hFile = CreateFile(FILE_PRINTFORMAT_TXT, GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return err_FILE_Open;
	}

	if (m_pbyFormatStr == NULL)
	{
		CloseHandle(hFile);
		return err_OK;
	}

	DWORD dwWriteSize = 0;
	if (WriteFile(hFile, m_pbyFormatStr, m_dwFormatStrSize, &dwWriteSize, NULL) == FALSE)
	{
		CloseHandle(hFile);
		return err_FILE_Write;
	}

	CloseHandle(hFile);

	return err_OK;
}

BYTE* CPrintFormat::GetFormatStr()
{
	return m_pbyFormatStr;
}

ERRCODE CPrintFormat::SetFormatStr(BYTE *pbStr, DWORD dwStrLen)
{
	m_dwFormatStrSize = 0;
	if (m_pbyFormatStr != NULL)
	{
		delete m_pbyFormatStr;
		m_pbyFormatStr = NULL;
	}

	if (pbStr == NULL || dwStrLen == 0)
	{
		return err_OK;
	}

	m_dwFormatStrSize = dwStrLen;
	m_pbyFormatStr = new BYTE[m_dwFormatStrSize + 1];
	memset(m_pbyFormatStr, 0, m_dwFormatStrSize + 1);
	memcpy(m_pbyFormatStr, pbStr, m_dwFormatStrSize);

	return err_OK;
}

PrintItem* CPrintFormat::GetPrintItemPtr()
{
	return &m_printItem;
}

ERRCODE CPrintFormat::DecodePrintStr(BYTE *pbyFormatStr, 
	DWORD *pdwRetFormatStrSize, 
	DWORD dwFormatStrSize, 
	BYTE *pbyPrintStr, 
	DWORD *pdwRetPrintStrSize, 
	DWORD dwPrintBufSize)
{
	if (pbyFormatStr == NULL || 
		pdwRetFormatStrSize == NULL ||
		dwFormatStrSize == 0 || 
		pbyPrintStr == NULL || 
		pdwRetPrintStrSize == NULL ||
		dwPrintBufSize == 0)
	{
		return err_InvalidParameter;
	}

	*pdwRetPrintStrSize = 0;
	DWORD dwIdx = 0;
	for (dwIdx; dwIdx < dwFormatStrSize; dwIdx++)
	{
		BYTE *pby = (BYTE*)(pbyFormatStr + dwIdx);
		if (*pby == 0xD && *(pby + 1) == 0xA)
		{
			memcpy(pbyPrintStr + (*pdwRetPrintStrSize), _T("\r"), 2);
			(*pdwRetPrintStrSize) += 2;

			dwIdx += 2;
			break;
		}
		else if (*pby != '%')
		{
			pbyPrintStr[*pdwRetPrintStrSize] = *pby;
			(*pdwRetPrintStrSize)++;
		}
		else
		{
			pby++;
			dwIdx++;

			CHAR *pszEnd = strchr((CHAR*)pby, '%');
			if (pszEnd != NULL)
			{
				DWORD dwCmdLen = (DWORD)pszEnd -  (DWORD)pby;
				dwIdx = dwIdx + dwCmdLen;

				DWORD dwCmdNumLen = 0;
				LONG lCmdPrintLen = 0;
				DecodeCmdPrintLen(pby, dwCmdLen, &dwCmdNumLen, &lCmdPrintLen);

				dwCmdLen -= dwCmdNumLen;
				pby += dwCmdNumLen;

				DWORD dwPrintStrRetSize = 0;
				if (dwCmdLen == strlen(MARCO_NO) && !_strnicmp((CHAR*)pby, MARCO_NO, dwCmdLen))
				{
					dwPrintStrRetSize = strlen(m_printItem.csNO.GetBuffer());
					memcpy(pbyPrintStr + *pdwRetPrintStrSize, m_printItem.csNO.GetBuffer(), dwPrintStrRetSize);
					(*pdwRetPrintStrSize) += dwPrintStrRetSize;
				}
				else if (dwCmdLen == strlen(MARCO_POSNO) && !_strnicmp((CHAR*)pby, MARCO_POSNO, dwCmdLen))
				{
					dwPrintStrRetSize = strlen(m_printItem.csPOSNO.GetBuffer());
					memcpy(pbyPrintStr + *pdwRetPrintStrSize, m_printItem.csPOSNO.GetBuffer(), dwPrintStrRetSize);
					(*pdwRetPrintStrSize) += dwPrintStrRetSize;
				}
				else if (dwCmdLen == strlen(MARCO_UID) && !_strnicmp((CHAR*)pby, MARCO_UID, dwCmdLen))
				{
					dwPrintStrRetSize = strlen(m_printItem.csUID.GetBuffer());
					memcpy(pbyPrintStr + *pdwRetPrintStrSize, m_printItem.csUID.GetBuffer(), dwPrintStrRetSize);
					(*pdwRetPrintStrSize) += dwPrintStrRetSize;
				}
				else if (dwCmdLen == strlen(MARCO_DATETIME) && !_strnicmp((CHAR*)pby, MARCO_DATETIME, dwCmdLen))
				{
					dwPrintStrRetSize = strlen(m_printItem.csDataTime.GetBuffer());
					memcpy(pbyPrintStr + *pdwRetPrintStrSize, m_printItem.csDataTime.GetBuffer(), dwPrintStrRetSize);
					(*pdwRetPrintStrSize) += dwPrintStrRetSize;
				}
				else if (dwCmdLen == strlen(MARCO_ITEM) && !_strnicmp((CHAR*)pby, MARCO_ITEM, dwCmdLen))
				{
					dwPrintStrRetSize = 0;
					if (m_iNextRetailItem >= 0 && m_iNextRetailItem < (int)m_printItem.vctRetailItem.size())
					{
						DWORD dwFormatStrRetSize = 0;
						ERRCODE errRet = DecodeItemPrintStr(pby + dwCmdLen + 1, 
							dwFormatStrSize - dwIdx,
							&dwFormatStrRetSize,
							&(m_printItem.vctRetailItem[m_iNextRetailItem]),
							pbyPrintStr + *pdwRetPrintStrSize, 
							dwPrintBufSize - (*pdwRetPrintStrSize),
							&dwPrintStrRetSize);

						m_iNextRetailItem++;
						(*pdwRetPrintStrSize) += dwPrintStrRetSize;	
						if (errRet == err_OK && m_iNextRetailItem < (int)m_printItem.vctRetailItem.size())
						{
							*pdwRetFormatStrSize = dwIdx + 1;
							memcpy(pbyPrintStr + *pdwRetPrintStrSize, _T("\r"), 2);
							(*pdwRetPrintStrSize) += 2;
							return err_OK;
						}
						else
						{
							m_iNextRetailItem = 0;
							dwIdx += dwFormatStrRetSize;			
						}
					}
				}
				else if (dwCmdLen == strlen(MARCO_TOTALPRICE) && !_strnicmp((CHAR*)pby, MARCO_TOTALPRICE, dwCmdLen))
				{
					dwPrintStrRetSize = strlen(m_printItem.csTotalPrice.GetBuffer());
					memcpy(pbyPrintStr + *pdwRetPrintStrSize, m_printItem.csTotalPrice.GetBuffer(), dwPrintStrRetSize);
					(*pdwRetPrintStrSize) += dwPrintStrRetSize; 
				}
				else if (dwCmdLen == strlen(MARCO_TOTALIN) && !_strnicmp((CHAR*)pby, MARCO_TOTALIN, dwCmdLen))
				{
					dwPrintStrRetSize = strlen(m_printItem.csTotalIn.GetBuffer());
					memcpy(pbyPrintStr + *pdwRetPrintStrSize, m_printItem.csTotalIn.GetBuffer(), dwPrintStrRetSize);
					(*pdwRetPrintStrSize) += dwPrintStrRetSize; 
				}
				else if (dwCmdLen == strlen(MARCO_TOTALOUT) && !_strnicmp((CHAR*)pby, MARCO_TOTALOUT, dwCmdLen))
				{
					dwPrintStrRetSize = strlen(m_printItem.csTotalOut.GetBuffer());
					memcpy(pbyPrintStr + *pdwRetPrintStrSize, m_printItem.csTotalOut.GetBuffer(), dwPrintStrRetSize);
					(*pdwRetPrintStrSize) += dwPrintStrRetSize; 
				}
				else
				{
					dwPrintStrRetSize = dwCmdLen;
					memcpy(pbyPrintStr + *pdwRetPrintStrSize, pby, dwPrintStrRetSize);
					(*pdwRetPrintStrSize) += dwPrintStrRetSize;
				}

				if (lCmdPrintLen > (LONG)dwPrintStrRetSize)
				{
					memset(pbyPrintStr + (*pdwRetPrintStrSize), ' ', (lCmdPrintLen - dwPrintStrRetSize));
					((*pdwRetPrintStrSize)) += (lCmdPrintLen - dwPrintStrRetSize);
				}
			}
			else
			{
				DWORD dwPrintStrRetSize = dwFormatStrSize - (pby - pbyFormatStr);
				dwIdx = dwIdx + dwPrintStrRetSize;

				memcpy(pbyPrintStr + *pdwRetPrintStrSize, pby, dwPrintStrRetSize);
				(*pdwRetPrintStrSize) += dwPrintStrRetSize;
			}
		}
	}

	*pdwRetFormatStrSize = dwIdx;

	return err_OK;
}

ERRCODE CPrintFormat::DecodeCmdPrintLen(BYTE *pbyFormatStr, DWORD dwFormatStrSize, DWORD *pdwRetFormatStrSize, LONG *plPrintStrLen)
{
	if (pbyFormatStr == NULL || 
		dwFormatStrSize == 0 || 
		pdwRetFormatStrSize == NULL || 
		plPrintStrLen == NULL)
	{
		return err_InvalidParameter;
	}

	*plPrintStrLen = 0;
	*pdwRetFormatStrSize = 0;

	CHAR *pszChar = new CHAR[dwFormatStrSize + 1];
	memset(pszChar, 0, dwFormatStrSize + 1);

	unsigned int iIdx = 0;
	for(iIdx = 0; iIdx < dwFormatStrSize; iIdx++)
	{
		BYTE *pby = pbyFormatStr + iIdx;
		if((*pby) > '9' || (*pby) < '0')
		{
			break;
		}
		memcpy(pszChar + iIdx, pby, 1);
	}

	*pdwRetFormatStrSize = iIdx;
	if (iIdx > 0)
	{
		*plPrintStrLen = atol(pszChar);
	}

	if (pszChar != NULL)
	{
		delete pszChar;
		pszChar = NULL;
	}

	return err_OK;
};

ERRCODE CPrintFormat::DecodeItemPrintStr(BYTE *pbyFormatStr, 
										 DWORD dwFormatStrSize, 
										 DWORD (*pdwRetFormatStrSize), 
										 PrintRetailItem *pRetailItem,
										 BYTE *pbyPrintStr, 
										 DWORD dwPrintBufSize,
										 DWORD (*pdwRetPrintStrSize))
{
	if (pbyFormatStr == NULL || dwFormatStrSize == 0 || pdwRetFormatStrSize == NULL || 
		pbyPrintStr == NULL || dwPrintBufSize == 0 || pdwRetPrintStrSize == NULL)
	{
		return err_InvalidParameter;
	}	

	(*pdwRetFormatStrSize) = 0;
	(*pdwRetPrintStrSize) = 0;
	
	if (*pbyFormatStr != '(')
	{
		return err_InvalidParameter;
	}
	(*pdwRetFormatStrSize)++;
	
	for ((*pdwRetFormatStrSize); ((*pdwRetFormatStrSize)) < dwFormatStrSize; (*pdwRetFormatStrSize)++)
	{
		BYTE *pby = (BYTE*)(pbyFormatStr + (*pdwRetFormatStrSize));
		if (*pby == ')')
		{
			(*pdwRetFormatStrSize)++;
			return err_OK;
		}
		else if (*pby != '%')
		{
			pbyPrintStr[(*pdwRetPrintStrSize)] = *pby;
			((*pdwRetPrintStrSize))++;
		}
		else
		{
			pby++;
			(*pdwRetFormatStrSize)++;

			CHAR *pszEnd = strchr((CHAR*)pby, '%');
			if (pszEnd != NULL)
			{
				DWORD dwCmdLen = (DWORD)pszEnd -  (DWORD)pby;
				(*pdwRetFormatStrSize) = (*pdwRetFormatStrSize) + dwCmdLen;
				
				DWORD dwCmdNumLen = 0;
				LONG lCmdPrintLen = 0;
				DecodeCmdPrintLen(pby, dwCmdLen, &dwCmdNumLen, &lCmdPrintLen);

				dwCmdLen -= dwCmdNumLen;
				pby += dwCmdNumLen;

				if (dwCmdLen == strlen(MARCO_NAME) && !_strnicmp((CHAR*)pby, MARCO_NAME, dwCmdLen))
				{
					if (pRetailItem != NULL)
					{
						dwCmdLen = strlen(pRetailItem->csName.GetBuffer());
						memcpy(pbyPrintStr + (*pdwRetPrintStrSize), pRetailItem->csName.GetBuffer(), dwCmdLen);
						((*pdwRetPrintStrSize)) += dwCmdLen;
					}
				}
				else if (dwCmdLen == strlen(MARCO_SN) && !_strnicmp((CHAR*)pby, MARCO_SN, dwCmdLen))
				{
					if (pRetailItem != NULL)
					{
						dwCmdLen = strlen(pRetailItem->csSN.GetBuffer());
						memcpy(pbyPrintStr + (*pdwRetPrintStrSize), pRetailItem->csSN.GetBuffer(), dwCmdLen);
						((*pdwRetPrintStrSize)) += dwCmdLen;
					}
				}
				else if (dwCmdLen == strlen(MARCO_BATCHNUM) && !_strnicmp((CHAR*)pby, MARCO_BATCHNUM, dwCmdLen))
				{
					if (pRetailItem != NULL)
					{
						dwCmdLen = strlen(pRetailItem->csBatchNum.GetBuffer());
						memcpy(pbyPrintStr + (*pdwRetPrintStrSize), pRetailItem->csBatchNum.GetBuffer(), dwCmdLen);
						((*pdwRetPrintStrSize)) += dwCmdLen;
					}
				}
				else if (dwCmdLen == strlen(MARCO_SPEC) && !_strnicmp((CHAR*)pby, MARCO_SPEC, dwCmdLen))
				{
					if (pRetailItem != NULL)
					{
						dwCmdLen = strlen(pRetailItem->csSpec.GetBuffer());
						memcpy(pbyPrintStr + (*pdwRetPrintStrSize), pRetailItem->csSpec.GetBuffer(), dwCmdLen);
						((*pdwRetPrintStrSize)) += dwCmdLen;
					}
				}
				else if (dwCmdLen == strlen(MARCO_NUM) && !_strnicmp((CHAR*)pby, MARCO_NUM, dwCmdLen))
				{
					if (pRetailItem != NULL)
					{
						dwCmdLen = strlen(pRetailItem->csNum.GetBuffer());
						memcpy(pbyPrintStr + (*pdwRetPrintStrSize), pRetailItem->csNum.GetBuffer(), dwCmdLen);
						((*pdwRetPrintStrSize)) += dwCmdLen;
					}
				}
				else if (dwCmdLen == strlen(MARCO_PRICE) && !_strnicmp((CHAR*)pby, MARCO_PRICE, dwCmdLen))
				{
					if (pRetailItem != NULL)
					{
						dwCmdLen = strlen(pRetailItem->csPrice.GetBuffer());
						memcpy(pbyPrintStr + (*pdwRetPrintStrSize), pRetailItem->csPrice.GetBuffer(), dwCmdLen);
						((*pdwRetPrintStrSize)) += dwCmdLen;
					}
				}
				else if (dwCmdLen == strlen(MARCO_SUMPRICE) && !_strnicmp((CHAR*)pby, MARCO_SUMPRICE, dwCmdLen))
				{
					if (pRetailItem != NULL)
					{
						dwCmdLen = strlen(pRetailItem->csTotalPrice.GetBuffer());
						memcpy(pbyPrintStr + (*pdwRetPrintStrSize), pRetailItem->csTotalPrice.GetBuffer(), dwCmdLen);
						((*pdwRetPrintStrSize)) += dwCmdLen;
					}
				}
				else
				{
					memcpy(pbyPrintStr + (*pdwRetPrintStrSize), pby, dwCmdLen);
					((*pdwRetPrintStrSize)) += dwCmdLen;
				}

				if (lCmdPrintLen > (LONG)dwCmdLen)
				{
					memset(pbyPrintStr + (*pdwRetPrintStrSize), ' ', (lCmdPrintLen - dwCmdLen));
					((*pdwRetPrintStrSize)) += (lCmdPrintLen - dwCmdLen);
				}
			}
			else
			{
				DWORD dwCmdLen = dwFormatStrSize - (pby - pbyFormatStr);
				(*pdwRetFormatStrSize) += dwCmdLen;

				memcpy(pbyPrintStr + (*pdwRetPrintStrSize), pby, dwCmdLen);
				((*pdwRetPrintStrSize)) += dwCmdLen;
			}
		}
	}

	return err_OK;
}


ERRCODE CPrintFormat::GetPrintStrFirstLine(BYTE *pbyBuf, DWORD *pdwGetNum, DWORD dwBufSize)
{
	if (pdwGetNum != NULL)
	{
		*pdwGetNum = 0;
	}
	
	if (pbyBuf == NULL || pdwGetNum == NULL || dwBufSize == NULL)
	{
		return err_InvalidParameter;
	}

	if (m_pbyFormatStr == NULL || m_dwFormatStrSize == 0)
	{
		*pdwGetNum = 0;
		return err_OK;
	}

	m_pbFormatStrPos = m_pbyFormatStr;
	m_iNextRetailItem = 0;
	DWORD dwFormatStrLen = m_dwFormatStrSize;
	DWORD dwRetFormatStrLen = 0;	

	ERRCODE errRet = DecodePrintStr(m_pbFormatStrPos, &dwRetFormatStrLen, dwFormatStrLen, pbyBuf, pdwGetNum, dwBufSize);
	if (errRet)
	{
		m_pbFormatStrPos += dwRetFormatStrLen;
		return errRet;
	}
	
	if (m_iNextRetailItem == 0 || m_iNextRetailItem >= (int)m_printItem.vctRetailItem.size())
	{
		m_pbFormatStrPos += dwRetFormatStrLen;
	}

	return err_OK;
}

ERRCODE CPrintFormat::GetPrintStrNextLine(BYTE *pbyBuf, DWORD *pdwGetNum, DWORD dwBufSize)
{
	if (pdwGetNum != NULL)
	{
		*pdwGetNum = 0;
	}

	if (pbyBuf == NULL || pdwGetNum == NULL || dwBufSize == NULL)
	{
		return err_InvalidParameter;
	}

	if (m_pbFormatStrPos == NULL)
	{
		*pdwGetNum = 0;
		return err_OK;
	}

	if (m_pbyFormatStr == NULL || m_dwFormatStrSize == 0)
	{
		*pdwGetNum = 0;
		return err_OK;
	}

	DWORD dwFormatStrLen = m_dwFormatStrSize - (m_pbFormatStrPos - m_pbyFormatStr);
	DWORD dwRetFormatStrLen = 0;
	
	ERRCODE errRet = DecodePrintStr(m_pbFormatStrPos, &dwRetFormatStrLen, dwFormatStrLen, pbyBuf, pdwGetNum, dwBufSize);
	if (errRet)
	{
		m_pbFormatStrPos += dwRetFormatStrLen;
		return errRet;
	}

	if (m_iNextRetailItem == 0 || m_iNextRetailItem >= (int)m_printItem.vctRetailItem.size())
	{
		m_pbFormatStrPos += dwRetFormatStrLen;
	}

	return err_OK;
}
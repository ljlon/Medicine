#include "stdafx.h"
#include "Crypto.h"

struct 
{
	BLOBHEADER hdr;
	DWORD cbKeySize;
	BYTE rgbKeyData[8];
} keyBlob;

BOOL Encrypt(BYTE *pBuf, DWORD &dwByteLen, DWORD dwMaxBufLen)
{
	keyBlob.hdr.bType = PLAINTEXTKEYBLOB;
	keyBlob.hdr.bVersion = CUR_BLOB_VERSION;
	keyBlob.hdr.reserved = 0;
	keyBlob.hdr.aiKeyAlg = CALG_DES;
	keyBlob.cbKeySize = 8;
	memset(keyBlob.rgbKeyData, 0, 8);
	memcpy(keyBlob.rgbKeyData, _T("С����Ī"), 8);

	HCRYPTPROV hCryptProv = NULL;
	if (CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0) == FALSE)
	{
		return FALSE;
	}

	HCRYPTKEY hKey = NULL;
	if (CryptImportKey(hCryptProv, (BYTE*)&keyBlob, sizeof(keyBlob), 0,0, &hKey) == FALSE)
	{
		CryptReleaseContext(hCryptProv, 0);
		return FALSE;
	}

	if (CryptEncrypt(
						hKey,					//��Կ
						0,						//�������ͬʱ����ɢ�кͼ��ܣ����ﴫ��һ��ɢ�ж���
						TRUE,
						0,						//����
						pBuf,					//���뱻�������ݣ�������ܺ������
						&dwByteLen,   //���뱻��������ʵ�ʳ��ȣ�������ܺ����ݳ���
						dwMaxBufLen)
						== FALSE)
	{
		CryptDestroyKey(hKey);
		CryptReleaseContext(hCryptProv, 0);
		return FALSE;
	}

	CryptDestroyKey(hKey);
	CryptReleaseContext(hCryptProv, 0);

	return TRUE;

	//���������Կ
	/*
	HCRYPTHASH hHash = NULL;
	if (CryptCreateHash(hCryptProv,CALG_MD5, 0, 0, &hHash) == FALSE)
	{
	CryptReleaseContext(hCryptProv, 0);
	return FALSE;
	}
	
	if (CryptHashData(hHash, (BYTE *)pBuf, dwByteNum, 0) == FALSE)
	{
	CryptDestroyHash(hHash);
	CryptReleaseContext(hCryptProv, 0);
	return FALSE;
	}

	if (CryptDeriveKey(hCryptProv, CALG_DES, hHash, CRYPT_EXPORTABLE, &hKey) == FALSE)
	{
		CryptDestroyHash(hHash);
		CryptReleaseContext(hCryptProv, 0);
		return FALSE;
	}

	BYTE *pbyKeyBlob = NULL;
	DWORD dwKeyBlobLen = 0;
	if (GetExportedKey(hKey, PLAINTEXTKEYBLOB, &pbyKeyBlob,&dwKeyBlobLen) == FALSE)
	{
		CryptDestroyKey(hKey);
		CryptDestroyHash(hHash);
		CryptReleaseContext(hCryptProv, 0);
		return FALSE;
	}

	if (pbyKeyBlob != NULL)
	{
	free(pbyKeyBlob);
	pbyKeyBlob = NULL;
	}

	CryptDestroyKey(hKey);
	hKey = NULL;*/
}

BOOL Decrypt(BYTE *pBuf, DWORD &dwByteLen)
{
	keyBlob.hdr.bType = PLAINTEXTKEYBLOB;
	keyBlob.hdr.bVersion = CUR_BLOB_VERSION;
	keyBlob.hdr.reserved = 0;
	keyBlob.hdr.aiKeyAlg = CALG_DES;
	keyBlob.cbKeySize = 8;
	memset(keyBlob.rgbKeyData, 0, 8);
	memcpy(keyBlob.rgbKeyData, _T("С����Ī"), 8);

	DWORD dwMaxLen = dwByteLen;

	HCRYPTPROV hCryptProv = NULL;
	if (CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0) == FALSE)
	{
		return FALSE;
	}

	HCRYPTKEY hKey = NULL;
	if (CryptImportKey(hCryptProv, (BYTE*)&keyBlob, sizeof(keyBlob), 0,0, &hKey) == FALSE)
	{
		CryptReleaseContext(hCryptProv, 0);
		return FALSE;
	}

	if (CryptDecrypt(
		hKey,							//��Կ
		0,								//�������ͬʱ����ɢ�кͼ��ܣ����ﴫ��һ��ɢ�ж���
		TRUE, 
		0,								//����
		pBuf,							//���뱻�������ݣ�������ܺ������
		&dwByteLen)           //���뱻��������ʵ�ʳ��ȣ�������ܺ����ݳ���
		== FALSE)
	{
		CryptDestroyKey(hKey);
		CryptReleaseContext(hCryptProv, 0);
		return FALSE;
	}
	if (dwByteLen < dwMaxLen)
	{
		pBuf[dwByteLen] = 0;
	}

	CryptDestroyKey(hKey);
	CryptReleaseContext(hCryptProv, 0);

	return TRUE;
}

BOOL GetExportedKey(
	HCRYPTKEY hKey, 
	DWORD dwBlobType,
	LPBYTE *ppbKeyBlob, 
	LPDWORD pdwBlobLen)
{
	DWORD dwBlobLength;
	*ppbKeyBlob = NULL;
	*pdwBlobLen = 0;

	// Export the public key. Here the public key is exported to a 
	// PUBLICKEYBLOB. This BLOB can be written to a file and
	// sent to another user.

	if(CryptExportKey(   
		hKey,    
		NULL,    
		dwBlobType,
		0,    
		NULL, 
		&dwBlobLength)) 
	{
		printf("Size of the BLOB for the public key determined. \n");
	}
	else
	{
		int iRet = GetLastError();
		printf("Error computing BLOB length.\n");
		return FALSE;
	}

	// Allocate memory for the pbKeyBlob.
	if(*ppbKeyBlob = (LPBYTE)malloc(dwBlobLength)) 
	{
		printf("Memory has been allocated for the BLOB. \n");
	}
	else
	{
		printf("Out of memory. \n");
		return FALSE;
	}

	// Do the actual exporting into the key BLOB.
	if(CryptExportKey(   
		hKey, 
		NULL,    
		dwBlobType,    
		0,    
		*ppbKeyBlob,    
		&dwBlobLength))
	{
		printf("Contents have been written to the BLOB. \n");
		*pdwBlobLen = dwBlobLength;
	}
	else
	{
		printf("Error exporting key.\n");
		free(*ppbKeyBlob);
		*ppbKeyBlob = NULL;

		return FALSE;
	}

	return TRUE;
}
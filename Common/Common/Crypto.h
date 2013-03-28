#pragma once
#include "WinCrypt.h"

BOOL Encrypt(BYTE *pBuf, DWORD &dwByteLen, DWORD dwMaxBufLen);

BOOL Decrypt(BYTE *pBuf, DWORD &dwByteLen);
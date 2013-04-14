#pragma once
#include "StdHead.h"

enum EnumCustomerDisplayType
{
	CDisplayType_None = 48,
	CDisplayType_Price = 49,
	CDisplayType_Total = 50,
	CDisplayType_In = 51,
	CDisplayType_Out = 52
};

class CCustomerDisplay
{
public:
	CCustomerDisplay();
	~CCustomerDisplay();

	ERRCODE Create(LPTSTR lpName);
	ERRCODE Close();

	ERRCODE InitDisplay();
	ERRCODE Clear();
	
	ERRCODE Display(EnumCustomerDisplayType type, double dbData);

protected:

private:
	HANDLE  m_hDisplay;
};
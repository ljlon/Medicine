#pragma once
#include "StdHead.h"

class CCashBox
{
public:
	CCashBox();
	~CCashBox();

	ERRCODE Create(LPTSTR lpName);
	ERRCODE Close();

	ERRCODE Open();

protected:

private:
	HANDLE  m_hCashBox;
};
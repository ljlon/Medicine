#pragma once
#include "StdHead.h"

class CTheme
{
public:
	CTheme();
	~CTheme();

	ERRCODE Init(LPTSTR lpFontName, int nFontHeight);
	CFont *GetFont();
protected:
	
private:
	BOOL  m_bInit;
	CFont m_font;
};

extern CTheme g_theme;
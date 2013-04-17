#include "stdafx.h"
#include "Theme.h"

CTheme g_theme;

CTheme::CTheme()
{
	m_bInit = FALSE;
}

CTheme::~CTheme()
{
	m_font.Detach();
}

ERRCODE CTheme::Init(LPTSTR lpFontName, int nFontHeight)
{
	m_font.Detach();

	m_font.CreateFont(nFontHeight,   // nHeight  
						0,                         // nWidth  
						0,                         // nEscapement  
						0,                         // nOrientation  
						FW_NORMAL,                 // nWeight  
						FALSE,                     // bItalic  
						FALSE,                     // bUnderline  
						0,                         // cStrikeOut  
						DEFAULT_CHARSET,           // nCharSet  
						OUT_DEFAULT_PRECIS,        // nOutPrecision  
						CLIP_DEFAULT_PRECIS,       // nClipPrecision  
						DEFAULT_QUALITY,           // nQuality  
						DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily  
						lpFontName);  

	m_bInit = TRUE;

	return err_OK;
}

CFont *CTheme::GetFont()
{
	if (m_bInit != TRUE)
	{
		return NULL;
	}

	return &m_font;
}
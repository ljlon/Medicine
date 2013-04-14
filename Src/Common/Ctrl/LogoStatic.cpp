// LogoStatic.cpp : implementation file
//

#include "stdafx.h"
#include "LogoStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogoStatic

CLogoStatic::CLogoStatic()
{
	memset(m_szText, 0, MAX_PATH);
	strncpy_s(m_szFont, _T("Arial Bold"), 10);
	m_nWeight = FW_NORMAL;
	m_Type = 0;
	m_nFormat = DT_LEFT;
	m_nPreHeight = 50;
	m_nHeight = 50;
	m_color = RGB(0x00, 0x00, 0xff);
}

CLogoStatic::~CLogoStatic()
{

}

void CLogoStatic::SetStyle(int nHeight, int nWeight, COLORREF color, const TCHAR *pszFont, UINT nFormat)
{
	if (pszFont != NULL)
	{
		strncpy_s(m_szFont, pszFont, strlen(pszFont) + 1);
		return;
	}

	m_nPreHeight = m_nHeight;
	m_nHeight = nHeight;
	m_nWeight = nWeight;
	m_color = color;
	m_nFormat = nFormat;
}

BEGIN_MESSAGE_MAP(CLogoStatic, CStatic)
	//{{AFX_MSG_MAP(CLogoStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogoStatic message handlers

void CLogoStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect(&rc);	
	
	if (m_Type == 1)
	{
		DrawBitmap(&dc, rc);
		return;
	}
	// TODO: Add your message handler code here

	//²Á³ý
	CFont BlankFont;
	BlankFont.CreateFont(
									m_nPreHeight,              // nHeight
									0,                         // nWidth
									0,                         // nEscapement
									0,                         // nOrientation
									m_nWeight,                 // nWeight
									FALSE,                     // bItalic
									FALSE,                     // bUnderline
									0,                         // cStrikeOut
									ANSI_CHARSET,              // nCharSet
									OUT_DEFAULT_PRECIS,        // nOutPrecision
									CLIP_DEFAULT_PRECIS,       // nClipPrecision
									DEFAULT_QUALITY,           // nQuality
									DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
									m_szFont);                 // lpszFacename
	CFont* poldFont = dc.SelectObject(&BlankFont);
	COLORREF bkcolor = ::GetSysColor(COLOR_BTNFACE);
									dc.SetBkColor(bkcolor);
									dc.SetTextColor(m_color);
									dc.DrawText(_T("                                                                                    "), 
									&rc, 
									m_nFormat /*| DT_BOTTOM */ | DT_VCENTER | DT_SINGLELINE );

	//Draw text
	CFont textFont;
	textFont.CreateFont(
								m_nHeight,                 // nHeight
								0,                         // nWidth
								0,                         // nEscapement
								0,                         // nOrientation
								m_nWeight,                 // nWeight
								FALSE,                     // bItalic
								FALSE,                     // bUnderline
								0,                         // cStrikeOut
								ANSI_CHARSET,              // nCharSet
								OUT_DEFAULT_PRECIS,        // nOutPrecision
								CLIP_DEFAULT_PRECIS,       // nClipPrecision
								DEFAULT_QUALITY,           // nQuality
								DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
								m_szFont);                 // lpszFacename

	dc.SelectObject(&textFont);
	bkcolor = ::GetSysColor(COLOR_BTNFACE);
	dc.SetBkColor(bkcolor);
	dc.SetTextColor(m_color);
	dc.DrawText(m_szText, &rc, m_nFormat /*| DT_BOTTOM */ | DT_VCENTER | DT_SINGLELINE );
	dc.SelectObject(poldFont);

	// Do not call CStatic::OnPaint() for painting messages
}

void CLogoStatic::SetText(LPCTSTR lpstr, COLORREF color/* = RGB(0, 0, 0)*/)
{
	if (lpstr == NULL)
	{
		return;
	}
	m_color = color;

	memset(m_szText, 0, sizeof(m_szText));
	strncpy_s(m_szText, lpstr, MAX_PATH - 1);
//	if (nOldLen > _tcslen(m_szText))
//	{
//		for (unsigned int i = _tcslen(m_szText); i < nOldLen; i++)
//		{
//			m_szText[i] = 0x20;
//		}
//	}
	Invalidate(TRUE);
}

void CLogoStatic::DrawBitmap(CDC* pdc, CRect& rt)
{	
 // device context for painting
	CRect rc(rt.left, rt.top, rt.left + rt.Width(), rt.bottom);
	CBrush br(RGB(0x00, 0x00, 0xff));
	//pdc->FrameRect(rc, &br);

	CBitmap bmp;
	bmp.LoadBitmap(m_nSource);
	BITMAP bmpInfo;
	bmp.GetBitmap(&bmpInfo);
	
	CDC memdc;
	memdc.CreateCompatibleDC(pdc);
	CBitmap* pOldBmp = memdc.SelectObject(&bmp);
	pdc->StretchBlt(rc.left + 1, rc.top + 1, rc.Width() - 2, rt.Height() - 2, 
		&memdc, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

	memdc.SelectObject(pOldBmp);
	rt.DeflateRect(0, 0, 0, 0);
}

void CLogoStatic::SetBMP(UINT IDRBMP)
{
	m_nSource = IDRBMP;
	m_Type = 1;
	Invalidate(TRUE);
}

void CLogoStatic::SetIcon(UINT IDRICON)
{
	m_nSource = IDRICON;
	m_Type = 2;
	Invalidate(TRUE);
}

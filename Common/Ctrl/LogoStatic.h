#if !defined(AFX_LOGOSTATIC_H__EC578347_268F_4FF8_B1D3_967149E75BE8__INCLUDED_)
#define AFX_LOGOSTATIC_H__EC578347_268F_4FF8_B1D3_967149E75BE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogoStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogoStatic window

class CLogoStatic : public CStatic
{
// Construction
public:
	CLogoStatic();
	virtual ~CLogoStatic();

	void SetStyle(int nHight,  int nWeight,	COLORREF color, const TCHAR *pszFont, UINT nFormat = DT_LEFT);
	
	void SetText(LPCTSTR lpstr, COLORREF color = RGB(0, 0, 0));

	void SetIcon(UINT IDRICON);

	void SetBMP(UINT IDRBMP);
	void DrawBitmap(CDC* pdc, CRect& rt);

// Attributes
public:

// Operations
public:
	int m_nHeight, m_nPreHeight;
	COLORREF m_color;
	TCHAR m_szFont[20];
	TCHAR m_szText[MAX_PATH];
	UINT m_nFormat;
	UINT m_nWeight;
	UINT m_nSource;
	UINT m_Type; 	// 0: Text, 1: Bitmap, 2: ICON, 3: Control

	// Generated message map functions
protected:
	//{{AFX_MSG(CLogoStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGOSTATIC_H__EC578347_268F_4FF8_B1D3_967149E75BE8__INCLUDED_)

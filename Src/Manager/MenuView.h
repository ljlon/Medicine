
#pragma once

#include "ViewTree.h"

const UINT WM_MENUVIEW = RegisterWindowMessage(TEXT("WM_MENUVIEW"));

const WPARAM WM_MENUVIEW_SETITEM = 1;
const WPARAM WM_MENUVIEW_SETPREITEM = 2;

class CMenuView : public CView
{
public: // create from serialization only
	CMenuView();
	DECLARE_DYNCREATE(CMenuView)

	void AdjustLayout();
	void OnChangeVisualStyle();

protected:
	void FillMenuView();

	// Attributes
protected:
	CViewTree m_wndMenuView;
	CImageList m_MenuViewImages;
	TreeMenuID m_curMenuID;
	TreeMenuID m_preMenuID;

	CManagerDoc* GetDocument() const;

	// Operations
public:

	// Implementation
public:
	virtual ~CMenuView();
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view

	void SetMenuItem(TreeMenuID menuID);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTextView)
	afx_msg LRESULT OnMenuView(WPARAM wParam, LPARAM lParam);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnNMClickMenuTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*
class CMenuView : public CView
{
// 构造
public:
	CMenuView();

	void AdjustLayout();
	void OnChangeVisualStyle();

// 特性
protected:

	CViewTree m_wndMenuView;
	CImageList m_MenuViewImages;

protected:
	void FillMenuView();

// 实现
public:
	virtual ~CMenuView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};*/
#include "stdafx.h"
#include "ExSplitterWnd.h"


CExSplitterWnd::CExSplitterWnd() 
{ 
} 
CExSplitterWnd::~CExSplitterWnd() 
{ 
} 

BEGIN_MESSAGE_MAP(CExSplitterWnd, CSplitterWnd)
END_MESSAGE_MAP()

BOOL   CExSplitterWnd::AttachView(CWnd*   pView,   int   row,   int   col) 
{ 
	//Make   sure   the   splitter   window   was   created 
	if   (!IsWindow(m_hWnd)) 
	{ 
		ASSERT(0); 
		TRACE(_T( "Create   the   splitter   window   before   attaching   windows   to   panes ")); 
		return   (FALSE); 
	} 
	//Make   sure   the   row   and   col   indices   are   within   bounds 
	if   (row   >=   GetRowCount()   ||   col   >=   GetColumnCount()) 
	{ 
		ASSERT(0); 
		return   FALSE; 
	} 
	//Is   the   window   to   be   attached   a   valid   one 
	if   (pView   ==   NULL   ||   (!IsWindow(pView->m_hWnd))) 
	{ 
		ASSERT(0); 
		return   FALSE; 
	} 
	pView-> SetDlgCtrlID(IdFromRowCol(row,   col)); 
	pView-> SetParent(this); 
	pView-> ShowWindow(SW_SHOW); 
	pView-> UpdateWindow(); 
	return   (TRUE); 
} 
BOOL  CExSplitterWnd::DetachView(int   row,   int   col) 
{ 
	//Make   sure   the   splitter   window   was   created 
	if   (!IsWindow(m_hWnd)) 
	{ 
		ASSERT(0); 
		TRACE(_T( "Create   the   splitter   window   before   attaching   windows   to   panes ")); 
		return   (FALSE); 
	} 
	//Make   sure   the   row   and   col   indices   are 
	//within   bounds 
	if   (row   >=   GetRowCount()   ||   col   >=   GetColumnCount()) 
	{ 
		ASSERT(0); 
		return   FALSE; 
	} 
	CWnd*   pWnd   =   GetPane(row,   col); 
	if   (pWnd   ==   NULL   ||   (!IsWindow(pWnd->m_hWnd))) 
	{ 
		ASSERT(0); 
		return   FALSE; 
	} 
	pWnd->ShowWindow(SW_HIDE); 
	pWnd->UpdateWindow(); 
	//Set   the   parent   window   handle   to   NULL   so   that   this   child   window   is   not 
	//destroyed   when   the   parent   (splitter)   is   destroyed 
	pWnd->SetParent(NULL); 
	return   (TRUE); 
}   
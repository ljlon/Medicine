#pragma once

class   CExSplitterWnd : public CSplitterWnd 
{ 
	//   Construction 
public: 
	CExSplitterWnd(); 
	//   Overrides 
	//   ClassWizard   generated   virtual   function   overrides 
	//{{AFX_VIRTUAL(CExSplitterWnd) 
	//}}AFX_VIRTUAL 
	//   Implementation 
	virtual   ~CExSplitterWnd(); 
	BOOL   AttachView(CWnd*   pView,   int   row,   int   col); 
	BOOL   DetachView(int   row,   int   col); 
	//   Generated   message   map   functions 
	//{{AFX_MSG(CExSplitterWnd) 
	//   NOTE   -   the   ClassWizard   will   add   and   remove   member   functions   here. 
	//}}AFX_MSG 
	DECLARE_MESSAGE_MAP() 
}; 
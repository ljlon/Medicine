
// ManagerView.h : CManagerView ��Ľӿ�
//

#pragma once
#include "resource.h"
#include "ManagerDoc.h"

class CManagerView : public CView
{
	DECLARE_DYNCREATE(CManagerView)

public: // �������л�����
	CManagerView();

// ����
public:
	CManagerDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ

// ʵ��
public:
	virtual ~CManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ManagerView.cpp �еĵ��԰汾
inline CManagerDoc* CManagerView::GetDocument() const
   { return reinterpret_cast<CManagerDoc*>(m_pDocument); }
#endif


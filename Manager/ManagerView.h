
// ManagerView.h : CManagerView 类的接口
//

#pragma once
#include "resource.h"
#include "ManagerDoc.h"

class CManagerView : public CView
{
	DECLARE_DYNCREATE(CManagerView)

public: // 仅从序列化创建
	CManagerView();

// 特性
public:
	CManagerDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图

// 实现
public:
	virtual ~CManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ManagerView.cpp 中的调试版本
inline CManagerDoc* CManagerView::GetDocument() const
   { return reinterpret_cast<CManagerDoc*>(m_pDocument); }
#endif


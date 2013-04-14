
// ManagerView.cpp : CManagerView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Manager.h"
#endif

#include "ManagerDoc.h"
#include "ManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CManagerView

IMPLEMENT_DYNCREATE(CManagerView, CView)

BEGIN_MESSAGE_MAP(CManagerView, CView)
	// 标准打印命令
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CManagerView 构造/析构

CManagerView::CManagerView()
{
	// TODO: 在此处添加构造代码

}

CManagerView::~CManagerView()
{
}

void CManagerView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CString csMsg;
	csMsg.Format("%s-%s", APP_NAME, APP_MANAGER);
	AfxGetApp()->GetMainWnd()->SetWindowText(csMsg);
}

// CManagerView 绘制

void CManagerView::OnDraw(CDC* /*pDC*/)
{
	CManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CManagerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CManagerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{

}


// CManagerView 诊断

#ifdef _DEBUG
void CManagerView::AssertValid() const
{
	CView::AssertValid();
}

void CManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CManagerDoc* CManagerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CManagerDoc)));
	return (CManagerDoc*)m_pDocument;
}
#endif //_DEBUG


// CManagerView 消息处理程序

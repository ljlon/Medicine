
// ManagerView.cpp : CManagerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CManagerView ����/����

CManagerView::CManagerView()
{
	// TODO: �ڴ˴���ӹ������

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

// CManagerView ����

void CManagerView::OnDraw(CDC* /*pDC*/)
{
	CManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CManagerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CManagerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{

}


// CManagerView ���

#ifdef _DEBUG
void CManagerView::AssertValid() const
{
	CView::AssertValid();
}

void CManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CManagerDoc* CManagerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CManagerDoc)));
	return (CManagerDoc*)m_pDocument;
}
#endif //_DEBUG


// CManagerView ��Ϣ�������

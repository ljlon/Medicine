#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "RetailSearchDlg.h"

// CRetailMgrView 窗体视图

class CRetailMgrView : public CFormView
{
	DECLARE_DYNCREATE(CRetailMgrView)

protected:
	CRetailMgrView();           // 动态创建所使用的受保护的构造函数
	virtual ~CRetailMgrView();

public:
	enum { IDD = IDD_RETAIL_MANAGE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate();

	void AdjustLayout();
	void DisplayListItem();
	void DisplayDetailListItem(LPTSTR lpRetailID);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnBnClickedBtnPrepage();
	afx_msg void OnBnClickedBtnNextpage();

	CRetailSearchDlg m_retailSearchDlg;
	CListCtrl m_listRetail;
	CStatic m_staticPageInfo;
	CButton m_btnPrePage;
	CButton m_btnNextPage;

	DWORD m_dwCurPage;
	DWORD m_dwTotalPage;
	DWORD m_dwTotalNum;
	double   m_dbTotalPrice;
public:
	CListCtrl m_listRetailDetail;
	afx_msg void OnLvnItemchangedListRetail(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_staticGroupRetailItem;
	CStatic m_staticGroupRetail;
	afx_msg void OnBnClickedButtonSearch();
};



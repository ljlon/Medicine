#pragma once
#include "afxcmn.h"
#include "SupplierAddView.h"
#include "SupplierSearchDlg.h"

// CSupplierMgrView form view

class CSupplierMgrView : public CFormView
{
	DECLARE_DYNCREATE(CSupplierMgrView)

public:
	CSupplierMgrView();           // protected constructor used by dynamic creation
	virtual ~CSupplierMgrView();

public:
	enum { IDD = IDD_SUPPLIER_MANAGE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	void AdjustLayout();
	void DisplayListItem();

	CListCtrl m_listSupplier;
	CStatic m_staticPageInfo;
	CButton m_btnPrePage;
	CButton m_btnNextPage;
	CButton m_btnAdd;
	CButton m_btnEdit;
	CButton m_btnDel;
	CSupplierAddView *m_pActiveView;
	DWORD m_dwCurPage;
	DWORD m_dwTotalPage;
	DWORD m_dwTotalNum;
	CSupplierSearchDlg m_searchDlg;
	CButton m_btnSearch;

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnBnClickedButtonSupplierAdd();
	afx_msg void OnBnClickedButtonSupplierEdit();
	afx_msg void OnBnClickedButtonSupplierDel();
	afx_msg void OnLvnItemchangedListSupplier(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnNMDblclkListSupplier(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnPrepage();
	afx_msg void OnBnClickedBtnNextpage();
	afx_msg void OnBnClickedButtonSearch();
};



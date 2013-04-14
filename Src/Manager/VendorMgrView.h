#pragma once
#include "VendorAddView.h"
#include "afxwin.h"
#include "VendorSearchDlg.h"

// CVendorMgrView form view

class CVendorMgrView : public CFormView
{
	DECLARE_DYNCREATE(CVendorMgrView)

public:
	CVendorMgrView();           // protected constructor used by dynamic creation
	virtual ~CVendorMgrView();

public:
	enum { IDD = IDD_VENDOR_MANAGE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void AdjustLayout();
	void DisplayListItem();

	CListCtrl m_listVendor;
	CStatic m_staticPageInfo;
	CButton m_btnPrePage;
	CButton m_btnNextPage;
	CButton m_btnAdd;
	CButton m_btnEdit;
	CButton m_btnDel;
	CVendorAddView *m_pActiveView;
	DWORD m_dwCurPage;
	DWORD m_dwTotalPage;
	DWORD m_dwTotalNum;
	CVendorSearchDlg m_searchDlg;
	CButton m_btnSearch;

public:
	afx_msg void OnLvnItemchangedListVendor(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonVendorAdd();
	afx_msg void OnBnClickedButtonVendorEdit();
	afx_msg void OnBnClickedButtonVendorDel();
	afx_msg void OnNMDblclkListVendor(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnPrepage();
	afx_msg void OnBnClickedBtnNextpage();
	afx_msg void OnBnClickedButtonSearch();
};



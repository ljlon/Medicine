#pragma once
#include "afxwin.h"
#include "StoreSearchDlg.h"

// CVendorMgrView form view

class CStoreMgrView : public CFormView
{
	DECLARE_DYNCREATE(CStoreMgrView)

public:
	CStoreMgrView();           // protected constructor used by dynamic creation
	virtual ~CStoreMgrView();

public:
	enum { IDD = IDD_STORE_MANAGE };
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
	void DisplayBatchListItem(LPSTR lpMedicineSN);

	CListCtrl m_listStore;
	CListCtrl m_listBatchStore;
	CStatic m_staticPageInfo;
	CButton m_btnPrePage;
	CButton m_btnNextPage;
	CStatic m_staticBatchPageInfo;
	CButton m_btnBatchPrePage;
	CButton m_btnBatchNextPage;

	CStoreSearchDlg m_storeSearchDlg;
	CString m_csSelectedMedicineSN;

	DWORD m_dwCurPage;
	DWORD m_dwTotalPage;
	DWORD m_dwTotalNum;

	DWORD m_dwBatchCurPage;
	DWORD m_dwBatchTotalPage;
	DWORD m_dwBatchTotalNum;

public:
	afx_msg void OnBnClickedBtnPrepage();
	afx_msg void OnBnClickedBtnNextpage();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnLvnItemchangedListStore(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListStore(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListBatchStore(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_btnEdit;
	CButton m_btnDel;
	CButton m_btnSearch;
	CButton m_btnBatchEdit;
	CButton m_btnBatchDel;
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnLvnItemchangedListStoreBatch(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnBatchPrepage();
	afx_msg void OnBnClickedBtnBatchNextpage();
	afx_msg void OnBnClickedButtonStoreBatchEdit();
	afx_msg void OnBnClickedButtonStoreBatchDel();
};



#pragma once
#include "afxwin.h"
#include "PurchaseSearchDlg.h"

// CPurchaseListView FormView

class CPurchaseListView : public CFormView
{
	DECLARE_DYNCREATE(CPurchaseListView)

public:
	CPurchaseListView();   // 标准构造函数
	virtual ~CPurchaseListView();

	// 对话框数据
	enum { IDD = IDD_PURCHASE_LIST };

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void AdjustLayout();
	void DisplayListItem();

	CPurchaseSearchDlg m_purchaseSearchDlg;
	CListCtrl m_listPur;
	CStatic m_staticPageInfo;
	CButton m_btnPrePage;
	CButton m_btnNextPage;
	CButton m_btnAdd;
	CButton m_btnDel;
	DWORD m_dwCurPage;
	DWORD m_dwTotalPage;
	DWORD m_dwTotalNum;
	double m_dbTotalPrice;

public:
	afx_msg void OnLvnItemchangedListPur(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedBtnPrepage();
	afx_msg void OnBnClickedBtnNextpage();
	afx_msg void OnBnClickedButtonDel();
	CStatic m_staticGroupPur;
	afx_msg void OnBnClickedButtonSearch();
	CComboBox m_comboMedicineType;
	afx_msg void OnCbnSelchangeComboMedicineType();
};

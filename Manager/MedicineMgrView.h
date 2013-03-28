#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MedicineAddView.h"
#include "MedicineSearchDlg.h"

// CMedicineView form view

class CMedicineMgrView : public CFormView
{
	DECLARE_DYNCREATE(CMedicineMgrView)

public:
	CMedicineMgrView();           // protected constructor used by dynamic creation
	virtual ~CMedicineMgrView();

public:
	enum { IDD = IDD_MEDICINE_MANAGE };
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

	CMedicineAddView *m_pAddView;
	CMedicineSearchDlg m_medicineSearchDlg;
	CListCtrl m_listMedicine;
	CStatic m_staticPageInfo;
	CButton m_btnPrePage;
	CButton m_btnNextPage;
	CButton m_btnAdd;
	CButton m_btnEdit;
	CButton m_btnDel;

	DWORD m_dwCurPage;
	DWORD m_dwTotalPage;
	DWORD m_dwTotalNum;

public:
	afx_msg void OnLvnItemchangedListMedicine(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonMedicineAdd();
	afx_msg void OnBnClickedButtonMedicineEdit();
	afx_msg void OnBnClickedButtonMedicineDel();
	afx_msg void OnNMDblclkListMedicine(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnPrepage();
	afx_msg void OnBnClickedBtnNextpage();
	afx_msg void OnBnClickedButtonSearch();
};



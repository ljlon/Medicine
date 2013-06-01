#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"



// CStoreEditView form view

class CStoreEditView : public CFormView
{
	DECLARE_DYNCREATE(CStoreEditView)

protected:
	CStoreEditView();           // protected constructor used by dynamic creation
	virtual ~CStoreEditView();

public:
	enum { IDD = IDD_STORE_EDIT };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	BOOL BeCancel();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();

	BOOL LoadDataFromDoc();
	BOOL SaveDataToDoc();
	BOOL SaveMedicineStore();

	void AdjustLayout();

	DECLARE_MESSAGE_MAP()
public:
	CEdit *m_pPopupEditCtrl;
	CDateTimeCtrl *m_pDataTimeCtrl;
	CEdit m_editMedicineSN;
	CEdit m_editMedicineName;
	CEdit m_editMedicineVendor;
	CEdit m_editRetailPrice;
	CEdit m_editMedicineNum;
	CEdit m_editMedicineSpec;
	CStatic m_staticMedicineUnit;
	CButton m_btnOK;
	CButton m_btnCancel;
	CButton m_btnMedicineDetail;
	int m_iBatchListItem;
	int m_iBatchListSubItem;
	CListCtrl m_listBatchStore;
	CButton m_btnBatchDel;
	CStatic m_staticPageInfo;
	CButton m_btnPrePage;
	CButton m_btnNextPage;

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonMedicineEdit();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonOk();
	//afx_msg void OnDtnDatetimechangeDateProduct(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnDtnDatetimechangeDateExpire(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnEnChangeEditMedicineNum();
	afx_msg void OnEnChangeEditMedicineRetailprice();
	afx_msg void OnNMClickListStoreBatch(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnKillfocusPopupEdit();
	afx_msg void OnEnChangeEditPopup();
	afx_msg void OnNMKillfocusDatetime(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnLvnItemchangedListStoreBatch(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonStoreBatchDel();
};



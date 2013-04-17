#pragma once
#include "SupplierDB.h"
#include "RichListCtrl.h"
#include "afxwin.h"
#include "afxdtctl.h"

// CPurchaseAddView 窗体视图

class CPurchaseAddView : public CFormView
{
	DECLARE_DYNCREATE(CPurchaseAddView)
public:

	CPurchaseAddView();           // 动态创建所使用的受保护的构造函数
	virtual ~CPurchaseAddView();

	enum { IDD = IDD_PURCHASE_ADD };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	void AdjustLayout();
	BOOL DisplaySupplierMedicineInfo(LPTSTR lpMedicineSN);
	void DisplayMedicineBatchInfo(LPTSTR lpMedicineID, LPTSTR lpMedicineBatchNum);
	BOOL AddPurchase();
	BOOL SaveDataToDoc();
	BOOL LoadDataFromDoc();
	BOOL BeCancel();

	CRichListCtrl m_purchaseList;
	CString m_csSubSupplierName;
	CString m_csSubPopupStr;
	CEdit *m_pPurListPopupEdit;
	CDateTimeCtrl *m_pDataTimeCtrl;
	CComboBox *m_pCbPopupBox;
	int m_iPurListItem;
	int m_iPurListSubItem;
	Supplier m_curSupplier;

protected:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	void AddOneLine(LPTSTR lpMedicineSN);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();

public:
	afx_msg void OnBnClickedButtonSupplierAdd();
	afx_msg void OnCbnEditupdateComboSupplier();
	afx_msg void OnCbnDropdownComboSupplier();
	afx_msg void OnCbnSelchangeComboSupplier();

	afx_msg void OnNMClickListPurchase(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnKillfocusPopupEdit();
	afx_msg void OnEnChangeEditPopup();
	afx_msg void OnNMRClickListPurchase(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPurlistDelOneLine();

	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();

	CButton m_btnOK;
	CButton m_btnCancel;
	CEdit m_editSN;
	afx_msg void OnNMKillfocusDatetime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnKillfocusCbPopup();
	afx_msg void OnCbnSelchangeCbPopup();
	afx_msg void OnCbnDropdownCbPopup();
	afx_msg void OnCbnEditupdateCbPopup();
};



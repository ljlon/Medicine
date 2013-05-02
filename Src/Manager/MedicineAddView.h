#pragma once
#include "SupplierMedicineDB.h"
#include "SupplierDB.h"
#include "VendorDB.h"
#include "afxwin.h"
#include "ManagerDoc.h"
#include "afxcmn.h"
#include "RichListCtrl.h"

// CMedicineAddView form view

class CMedicineAddView : public CFormView
{
	DECLARE_DYNCREATE(CMedicineAddView)

public:
	CMedicineAddView();           // protected constructor used by dynamic creation
	virtual ~CMedicineAddView();

public:
	enum { IDD = IDD_MEDICINE_ADD };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	void AdjustLayout();
	void DisplayMedicineInfo(LPTSTR lpMedicineID);
	BOOL AddMedicine();
	void OnListBtnClicked(LVHITTESTINFO *pHitInfo);
	BOOL SaveDataToDoc();
	BOOL LoadDataFromDoc();
	BOOL BeCancel();
	BOOL CheckSNExist();

protected:
	EnumViewType m_viewType;			//标识类型：新建或者修改
	BOOL m_bDataChanged;				//数据是否已经被修改，用于退出时保存的判断
	CString m_csSubVendorName;	
	CString m_csSubSupplierName;
	Medicine m_medicine;
	Supplier  m_supplier;
	Vendor   m_vendor;
	vector<MedicineUtil*> m_vctMedicineUtil;
	vector<MedicineType*> m_vctMedicineType;
	vector<MedicineOTC*> m_vctMedicineOTC;
	vector<MedicineForm*> m_vctMedicineForm;
	CComboBox m_cbUtil;
	CComboBox m_cbType;
	CComboBox m_cbOTC;
	CComboBox m_cbForm;
	CComboBox m_cbVendor;
	CRichListCtrl m_listSupplier;
	CButton m_btnDelPur;
	CButton m_btnAddPur;
	CEdit *m_pSupplierListPopupEdit;
	CComboBox *m_pSupplierListPopupCmbox;
	int m_iSupplierListItem;
	int m_iSupplierListSubItem;
	map<LONG, SupplierMedicine*> m_mapVctSupplierMedicine;
	map<LONG, SupplierMedicine*> m_mapVctDelSupplierMedicine;

	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnRichListCtrl(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonMedicineAddOk();
	afx_msg void OnBnClickedButtonMedicineCancel();
	afx_msg void OnEnChangeEditMedicineName();
	afx_msg void OnEnChangeEditMedicineId();
	afx_msg void OnCbnEditupdateComboSupplier();
	afx_msg void OnCbnEditupdateComboVendor();
	afx_msg void OnCbnDropdownComboMedicineSupplierid();
	afx_msg void OnCbnDropdownComboMedicineVendorid();
	afx_msg void OnCbnSelchangeComboMedicineSupplierid();
	afx_msg void OnCbnSelchangeComboMedicineVendorid();
	afx_msg void OnEnChangeEditMedicineSn();
	afx_msg void OnCbnSelchangeComboMedicineUnit();
	afx_msg void OnCbnSelchangeComboMedicineType();
	afx_msg void OnCbnSelchangeComboMedicineOtc();
	afx_msg void OnCbnSelchangeComboMedicineForm();
	afx_msg void OnCbnDropdownComboMedicineUnit();
	afx_msg void OnCbnDropdownComboMedicineType();
	afx_msg void OnCbnDropdownComboMedicineOtc();
	afx_msg void OnCbnDropdownComboMedicineForm();
	afx_msg void OnEnChangeEditMedicineSpec();
	afx_msg void OnEnChangeEditMedicineRetailprice();
	afx_msg void OnLvnItemchangedListSupplier(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnSupplierMedicineDel();
	afx_msg void OnBnClickedBtnSupplierMedicineAdd();
public:
	afx_msg void OnNMClickListSupplier(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnKillfocusPopupEdit();
	afx_msg void OnCbnKillfocusPopupCombox();
	afx_msg void OnLvnEndScrollListSupplier(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnVendorAdd();
	CEdit m_editMedicineSN;
	CEdit m_editMedicineName;
	CEdit m_editMedicineSpec;
	CEdit m_editRetailPrice;
	CEdit m_editMedicineID;
	CButton m_btnAddVendor;
	CButton m_btnAdd;
	CButton m_btnCancel;
	afx_msg void OnEnKillfocusEditMedicineSn();
};



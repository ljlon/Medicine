#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CStoreSearchDlg dialog

class CStoreSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStoreSearchDlg)

public:
	CStoreSearchDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStoreSearchDlg();

// Dialog Data
	enum { IDD = IDD_SEARCH_STORE };

	CString m_csMedicineSN;
	CString m_csMedicineName;
	CString m_csExpireDate;
	CString m_csVendorID;
	CString m_csSupplierID;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	CButton m_cbMedicineName;
	CButton m_cbMedicineSN;
	CButton m_cbExpireDate;
	CEdit m_editMedicineSN;
	CEdit m_editMedicineName;
	CDateTimeCtrl m_datetimeExpire;
	CButton m_cbMedicineVendor;
	CButton m_cbMedicineSupplier;
	CComboBox m_comboVendor;
	CComboBox m_comboSupplier;
	CString  m_csMatchStr;

	afx_msg void OnOK();
	afx_msg void OnBnClickedCheckMedicineSn();
	afx_msg void OnBnClickedCheckMedicineName();
	afx_msg void OnBnClickedCheckExpiredate();
	afx_msg void OnBnClickedCheckMedicineVendor();
	afx_msg void OnBnClickedCheckMedicineSupplier();
	afx_msg void OnCbnDropdownComboVendor();
	afx_msg void OnCbnDropdownComboSupplier();
	afx_msg void OnCbnEditupdateComboVendor();
	afx_msg void OnCbnEditupdateComboSupplier();
};

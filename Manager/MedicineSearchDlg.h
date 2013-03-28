#pragma once
#include "afxwin.h"


// CMedicineSearchDlg dialog

class CMedicineSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMedicineSearchDlg)

public:
	CMedicineSearchDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMedicineSearchDlg();

// Dialog Data
	enum { IDD = IDD_MEDICINE_SEARCH };

	CString m_csMedicineSN;
	CString m_csMedicineName;
	CString m_csVendorID;
	CString m_csSupplierID;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	CButton m_cbMedicineName;
	CButton m_cbMedicineSN;
	CEdit m_editMedicineSN;
	CEdit m_editMedicineName;

	afx_msg void OnOK();
	afx_msg void OnBnClickedCheckMedicineSn();
	afx_msg void OnBnClickedCheckMedicineName();
public:
	CButton m_cbMedicineVendor;
	CButton m_cbMedicineSupplier;
	CComboBox m_comboVendor;
	CComboBox m_comboSupplier;
	CString  m_csMatchStr;
	afx_msg void OnBnClickedCheckMedicineVendor();
	afx_msg void OnBnClickedCheckMedicineSupplier();
	afx_msg void OnCbnDropdownComboVendor();
	afx_msg void OnCbnDropdownComboSupplier();
	afx_msg void OnCbnEditupdateComboVendor();
	afx_msg void OnCbnEditupdateComboSupplier();
};

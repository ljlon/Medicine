#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CPurchaseSearchDlg 对话框

class CPurchaseSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPurchaseSearchDlg)

public:
	CPurchaseSearchDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPurchaseSearchDlg();

// 对话框数据
	enum { IDD = IDD_PURCHASE_SEARCH };

	CString m_csPurBeginDate;
	CString m_csPurEndDate;
	CString m_csMedicineSN;
	CString m_csMedicineName;
	CString m_csMedicineBatchNum;
	CString m_csSupplierID;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	CString m_csSubSupplierName;

	CButton m_btnPurDate;
	CButton m_cbMedicineSN;
	CButton m_cbMedicineName;
	CButton m_cbMedicineBatchNum;
	CButton m_cbSupplier;
	CDateTimeCtrl m_datePurBegin;
	CDateTimeCtrl m_datePurEnd;
	CEdit m_editMedicineSN;
	CEdit m_editMedicineName;
	CEdit m_editMedicineBatchNum;
	CComboBox m_comboSupplier;
	
	afx_msg void OnBnClickedCheckPurchaseDate();
	afx_msg void OnBnClickedCheckMedicineSn();
	afx_msg void OnBnClickedCheckMedicineName();
	afx_msg void OnBnClickedCheckMedicineBatchNum();
	afx_msg void OnBnClickedCheckSupplier();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnEditupdateComboSupplier();
	afx_msg void OnCbnDropdownComboSupplier();
};

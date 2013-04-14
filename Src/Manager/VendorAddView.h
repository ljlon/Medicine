#pragma once
#include "VendorDB.h"
#include "ManagerDoc.h"

// CVendorAddView form view

class CVendorAddView : public CFormView
{
	DECLARE_DYNCREATE(CVendorAddView)

public:
	CVendorAddView();           // protected constructor used by dynamic creation
	virtual ~CVendorAddView();

public:
	enum { IDD = IDD_VENDOR_ADD };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	void AdjustLayout();
	void DisplayVendorInfo(LPTSTR lpVendorID);
	BOOL BeCancel();

protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonVendorAddOk();
	afx_msg void OnBnClickedButtonVendorCancel();
	afx_msg void OnEnChangeEditVendorName();
	afx_msg void OnEnChangeEditVendorTel();
	afx_msg void OnEnChangeEditVendorAddress();

	BOOL AddVendor();

	EnumViewType m_viewType;
	BOOL m_bDataChanged;
	Vendor m_vendor;
};



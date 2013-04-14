#pragma once


 
// CBasicMgrView form view

class CBasicMgrView : public CFormView
{
	DECLARE_DYNCREATE(CBasicMgrView)

public:
	CBasicMgrView();           // protected constructor used by dynamic creation
	virtual ~CBasicMgrView();

public:
	enum { IDD = IDD_BASIC_MANAGE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSupplier();
	afx_msg void OnBnClickedButtonVendor();
	afx_msg void OnBnClickedButtonMedicine();
};



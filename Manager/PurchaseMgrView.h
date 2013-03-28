#pragma once



// CPurchaseMgrView form view

class CPurchaseMgrView : public CFormView
{
	DECLARE_DYNCREATE(CPurchaseMgrView)

public:
	CPurchaseMgrView();           // protected constructor used by dynamic creation
	virtual ~CPurchaseMgrView();

public:
	enum { IDD = IDD_PURCHASE_MANAGE };
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
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonList();
	afx_msg void OnBnClickedButtonHistory();
};



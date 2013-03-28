#pragma once
#include "afxwin.h"
#include "SupplierDB.h"
#include "ManagerDoc.h"

const UINT WM_SUPPLIER_ADD_VIEW = RegisterWindowMessage("WM_SUPPLIER_ADD_VIEW");
//const UINT WM_SUPPLIER_ADD_VIEW_EDIT = 1;

// CSupplierAddView 窗体视图

class CSupplierAddView : public CFormView
{
	DECLARE_DYNCREATE(CSupplierAddView)

public:
	CSupplierAddView();           // 动态创建所使用的受保护的构造函数
	virtual ~CSupplierAddView();

public:
	enum { IDD = IDD_SUPPLIER_ADD };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	virtual void OnInitialUpdate();
	BOOL BeCancel();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


	void AdjustLayout();
	void DisplaySupplierInfo(LPTSTR lpSupplierID);
	BOOL AddSupplier();
	BOOL UpdateSupplier();

	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnSupplierAddView(WPARAM wParam, LPARAM lParam);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonSupplierAddOk();
	afx_msg void OnBnClickedButtonSupplierCancel();

protected:
	EnumViewType m_viewType;
	BOOL m_bDataChanged;
	Supplier m_supplier;

public:
	afx_msg void OnEnChangeEditSupplierName();
	afx_msg void OnEnChangeEditSupplierContact();
	afx_msg void OnEnChangeEditSupplierTel();
	afx_msg void OnEnChangeEditSupplierAddress();
};



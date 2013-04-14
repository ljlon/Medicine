#pragma once
#include "afxwin.h"
#include "RetailDB.h"

// CRetailItemDlg dialog

class CRetailItemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRetailItemDlg)

public:
	CRetailItemDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRetailItemDlg();

// Dialog Data
	enum { IDD = IDD_RETAIL_ITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_staticRetaiItem;
	Retail m_retail;

	void ResizeDlg();
};

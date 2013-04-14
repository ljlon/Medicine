#pragma once
#include "afxwin.h"


// CMedicineSearchDlg dialog

class CMedicineImportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMedicineImportDlg)

public:
	CMedicineImportDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMedicineImportDlg();

// Dialog Data
	enum { IDD = IDD_MEDICINE_IMPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	CButton m_cbExport;
	CButton m_cbImport;
	CEdit m_editExport;
	CEdit m_editImport;

	afx_msg void OnBnClickedExport();
	afx_msg void OnBnClickedImport();
};

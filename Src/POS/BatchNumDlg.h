#pragma once
#include "afxwin.h"


// CBatchNumDlg dialog

class CBatchNumDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBatchNumDlg)

public:
	CBatchNumDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBatchNumDlg();

// Dialog Data
	enum { IDD = IDD_BATCHNUM };

	CString m_csBatchNum;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnOK();

public:
	CEdit m_editBatchNum;

};

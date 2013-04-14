#pragma once
#include "afxwin.h"


// CVendorSearchDlg 对话框

class CVendorSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVendorSearchDlg)

public:
	CVendorSearchDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVendorSearchDlg();

// 对话框数据
	enum { IDD = IDD_VENDOR_SEARCH };

	CString m_csName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CButton m_cbName;
	CEdit m_editName;
	afx_msg void OnBnClickedCheckName();
};

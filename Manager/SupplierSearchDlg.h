#pragma once


// CSupplierSearchDlg 对话框

class CSupplierSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSupplierSearchDlg)

public:
	CSupplierSearchDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSupplierSearchDlg();

// 对话框数据
	enum { IDD = IDD_SUPPLIER_SEARCH };

	CString m_csName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	CButton m_cbName;
	CEdit m_editName;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheckName();
};

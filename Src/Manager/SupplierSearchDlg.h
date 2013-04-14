#pragma once


// CSupplierSearchDlg �Ի���

class CSupplierSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSupplierSearchDlg)

public:
	CSupplierSearchDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSupplierSearchDlg();

// �Ի�������
	enum { IDD = IDD_SUPPLIER_SEARCH };

	CString m_csName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	CButton m_cbName;
	CEdit m_editName;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheckName();
};

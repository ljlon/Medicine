#pragma once
#include "afxwin.h"


// CVendorSearchDlg �Ի���

class CVendorSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVendorSearchDlg)

public:
	CVendorSearchDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVendorSearchDlg();

// �Ի�������
	enum { IDD = IDD_VENDOR_SEARCH };

	CString m_csName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CButton m_cbName;
	CEdit m_editName;
	afx_msg void OnBnClickedCheckName();
};

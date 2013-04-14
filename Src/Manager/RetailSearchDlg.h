#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CRetailSearchDlg �Ի���

class CRetailSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRetailSearchDlg)

public:
	CRetailSearchDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRetailSearchDlg();

// �Ի�������
	enum { IDD = IDD_RETAIL_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckRetailDate();

	CString m_csRetailBeginDate;
	CString m_csRetailEndDate;

	CButton m_btnRetailDate;
	CDateTimeCtrl m_dateRetailBegin;
	CDateTimeCtrl m_dateRetailEnd;
	afx_msg void OnBnClickedOk();
};

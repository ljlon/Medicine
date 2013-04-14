#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CPurchaseSearchDlg 对话框

class CPurchaseSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPurchaseSearchDlg)

public:
	CPurchaseSearchDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPurchaseSearchDlg();

// 对话框数据
	enum { IDD = IDD_PURCHASE_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString m_csPurBeginDate;
	CString m_csPurEndDate;

	CButton m_btnPurDate;
	CDateTimeCtrl m_datePurBegin;
	CDateTimeCtrl m_datePurEnd;
	afx_msg void OnBnClickedCheckPurchaseDate();
	afx_msg void OnBnClickedOk();
};

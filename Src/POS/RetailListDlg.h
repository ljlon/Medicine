#pragma once
#include "afxwin.h"
#include "RetailSearchDlg.h"

// CRetailListDlg dialog

class CRetailListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRetailListDlg)

public:
	CRetailListDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRetailListDlg();

// Dialog Data
	enum { IDD = IDD_RETAIL_LIST };

	virtual void DoDataExchange(CDataExchange* pDX); 
	virtual BOOL OnInitDialog();

	void AdjustLayout();
	void DisplayListItem();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnBnClickedBtnPrepage();
	afx_msg void OnBnClickedBtnNextpage();

	CRetailSearchDlg m_retailSearchDlg;
	CListCtrl m_listRetail;
	CStatic m_staticPageInfo;
	CButton m_btnPrePage;
	CButton m_btnNextPage;
	CListCtrl m_listRetailDetail;
	CStatic m_staticGroupRetailItem;
	CStatic m_staticGroupRetail;

	DWORD m_dwCurPage;
	DWORD m_dwTotalPage;
	DWORD m_dwTotalNum;
	double m_dbTotalPrice;

	afx_msg void OnLvnItemchangedListRetail(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListRetail(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_btnPrint;
	afx_msg void OnBnClickedButtonPrint();
	afx_msg void OnBnClickedButtonSearch();
};

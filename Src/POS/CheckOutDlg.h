#pragma once
#include "CustomerDisplay.h"

// CCheckOutDlg dialog

enum CheckOutStatus
{
	CheckOut_Status_1 = 1,
	CheckOut_Status_2 = 2,
};

class CCheckOutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCheckOutDlg)

public:
	CCheckOutDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCheckOutDlg();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();

	int m_iStatus;
	double m_dbTotalPrice;
	double m_dbIn;
	double m_dbOut;
	CCustomerDisplay *m_pCustomerDisplay;
// Dialog Data
	enum { IDD = IDD_CHECKOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditIn();
};

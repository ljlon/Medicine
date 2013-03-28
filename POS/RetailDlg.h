#pragma once
#include "afxwin.h"
#include "RichListCtrl.h"
#include "CheckOutDlg.h"
#include "PrinterEP.h"
#include "CashBox.h"
#include "CustomerDisplay.h"
#include "LogoStatic.h"

const UINT MESSAGE_RETAILDLG = RegisterWindowMessage(_T("MESSAGE_RETAILDLG"));
const UINT MESSAGE_RETAILDGL_UPDATEINPRICE = 1;

enum RetailStatus
{
	RetailStatus_Input = 0,
	RetailStatus_CheckOut = 1,
	RetailStatus_Finish = 2,
};

// CRetailDlg 对话框

class CRetailDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRetailDlg)

public:
	CRetailDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRetailDlg();

// 对话框数据
	enum { IDD = IDD_RETAIL };

	ERRCODE Init();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT OnRetailDlg(WPARAM wParam, LPARAM lParam);
	virtual void OnOK();
	virtual void OnCancel();

	void OnStatusNewInput();
	void OnStatusInput();
	void OnAddRetailItem(LPTSTR lpMedicineIDORSN);
	void OnDelRetailItem();
	void OnCancelRetail();
	void OnChangeNum();
	void DisplayTotalPrice();
	void GenerateSN();

	BOOL OnStatusCheckOut();
	void OnCancelCheckOut();

	ERRCODE OnPrint();
	ERRCODE OnOpenCashBox();

	void OnStatusFinishCheckOut();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnTimer( UINT nIDEvent ); 

public:
	CRichListCtrl m_listRetail;
	CLogoStatic m_staticTotalTitle;
	CLogoStatic m_staticInTitle;
	CLogoStatic m_staticOutTitle;
	CLogoStatic m_staticTotal;
	CLogoStatic m_staticIn;
	CLogoStatic m_staticOut;
	CStatic m_staticTip;
	CStatic m_staticSN;
	CEdit m_editSN;

	RetailStatus m_retailStatus;
	CString m_csRetailSN;
	double m_dbTotalPrice;
	double m_dbInPrice;
	double m_dbOutPrice;

	CPrinterEP m_printerEP;

	CCashBox *m_pCashBox;

	CCustomerDisplay m_customerDisplay;

	afx_msg void OnEnChangeEditSn();

	CStatic m_staticDateTime;
	CStatic m_staticRetailSN;
	CStatic m_staticInfo;
	CStatic m_staticGroupTotal;
	CStatic m_staticGroupInput;
	CStatic m_staticGroupTip;
};

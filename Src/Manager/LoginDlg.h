#pragma once
#include "afxwin.h"
#include "StdHead.h"

// CLoginDlg dialog

const UINT LOGINDLG_SHOWWINDOW = RegisterWindowMessage(_T("LOGINDLG_SHOWWINDOW"));

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoginDlg();

// Dialog Data
	enum { IDD = IDD_LOGIN };

	void SetShowWindow(int nShowCMD);

	User m_curUser;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit m_editUID;
	CEdit m_editPWD;
	int   m_iShowWindow;
};

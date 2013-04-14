#pragma once



// CPasswordMgrView 窗体视图

class CPasswordMgrDlg : public CDialogEx
{
	DECLARE_DYNCREATE(CPasswordMgrDlg)

public:
	CPasswordMgrDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CPasswordMgrDlg();

public:
	enum { IDD = IDD_ACCOUNT_PASSWORD };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	void AdjustLayout();
	BOOL UpdatePassword();
	BOOL BeCancel();

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	afx_msg void OnEnChangeEditAccountCurrentPassword();
	afx_msg void OnEnChangeEditAccountNewPassword();
	afx_msg void OnEnChangeEditAccountAgainnewPassword();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};



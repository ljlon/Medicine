#pragma once



// CPasswordMgrView ������ͼ

class CPasswordMgrView : public CFormView
{
	DECLARE_DYNCREATE(CPasswordMgrView)

public:
	CPasswordMgrView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPasswordMgrView();

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
	virtual void OnInitialUpdate();
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



#pragma once
#include "afxwin.h"

// CBackupMgrView ������ͼ

class CBackupMgrView : public CFormView
{
	DECLARE_DYNCREATE(CBackupMgrView)

protected:
	CBackupMgrView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CBackupMgrView();

public:
	enum { IDD = IDD_BACKUP_MANAGE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate();

	DECLARE_MESSAGE_MAP()

	void AdjustLayout();

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonBackup();
	afx_msg void OnBnClickedButtonRestore();
	CButton m_cbAutoBackup;
	CEdit m_editAutoDate;
	CComboBox m_comboAutoDateUnit;
	CComboBox m_comboAutoTime;	
	CStatic m_staticBackupInfo;
};



#pragma once
#include "afxwin.h"


// CCfgDatabaseDlg �Ի���

class CCfgDatabaseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCfgDatabaseDlg)

public:
	CCfgDatabaseDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCfgDatabaseDlg();

// �Ի�������
	enum { IDD = IDD_CFG_DATABASE };


	ERRCODE ApplyCfg(Config &config);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cbHost;
	CEdit m_editPort;
	CEdit m_editDBName;
	CEdit m_editUID;
	CEdit m_editPWD;
};

#pragma once
#include "afxwin.h"
#include "POSConfig.h"

// CCfgGeneralDlg �Ի���

class CCfgGeneralDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCfgGeneralDlg)

public:
	CCfgGeneralDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCfgGeneralDlg();

// �Ի�������
	enum { IDD = IDD_CFG_GENERAL };

	ERRCODE ApplyCfg(POSConfig &config);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editCompanyName;
	CEdit m_editPOSID;
};

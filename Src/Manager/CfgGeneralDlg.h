#pragma once
#include "MgrConfig.h"
#include "afxfontcombobox.h"
#include "afxwin.h"

// CCfgGeneralDlg �Ի���

class CCfgGeneralDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCfgGeneralDlg)

public:
	CCfgGeneralDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCfgGeneralDlg();

// �Ի�������
	enum { IDD = IDD_CFG_GENERAL };

	ERRCODE ApplyCfg(MgrConfig &config);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editFontName;
	CEdit m_editFontHeight;
};

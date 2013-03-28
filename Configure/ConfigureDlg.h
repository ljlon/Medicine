
// ConfigureDlg.h : ͷ�ļ�
//
#pragma once

#include "CfgDatabaseDlg.h"
#include "afxwin.h"

// CConfigureDlg �Ի���
class CConfigureDlg : public CDialogEx
{
// ����
public:
	CConfigureDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CConfigureDlg();

// �Ի�������
	enum { IDD = IDD_CONFIGURE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	//HICON m_hIcon;

	CCfgDatabaseDlg *m_pCfgDatabaseDlg;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_staticView;
	afx_msg void OnBnClickedOk();
};


// POSDlg.h : ͷ�ļ�
//

#pragma once
#include "RetailListDlg.h"

// CPOSDlg �Ի���
class CPOSDlg : public CDialogEx
{
// ����
public:
	CPOSDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_POS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;
	CRetailListDlg m_retailListDlg;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCfg();
	afx_msg void OnBnClickedBtnSale();
	afx_msg void OnBnClickedBtnHelp();
	afx_msg void OnBnClickedBtnHistory();
	afx_msg void OnBnClickedBtnAccount();
};

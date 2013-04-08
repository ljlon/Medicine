#pragma once



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

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBackup();
	afx_msg void OnBnClickedButtonRestore();
};



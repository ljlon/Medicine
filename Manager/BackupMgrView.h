#pragma once



// CBackupMgrView 窗体视图

class CBackupMgrView : public CFormView
{
	DECLARE_DYNCREATE(CBackupMgrView)

protected:
	CBackupMgrView();           // 动态创建所使用的受保护的构造函数
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBackup();
	afx_msg void OnBnClickedButtonRestore();
};



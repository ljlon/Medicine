
// Manager.h : Manager Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "StdHead.h"
#include "UserDB.h"

#define APP_MANAGER _T("��̨����")

// CManagerApp:
// �йش����ʵ�֣������ Manager.cpp
//

class CManagerApp : public CWinAppEx
{
public:
	CManagerApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	User  m_curUser;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CManagerApp theApp;

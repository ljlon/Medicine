
// POS.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "UserDB.h"
#include "POSDB.h"

#define APP_POS _T("POS�����ն�")

// CPOSApp:
// �йش����ʵ�֣������ POS.cpp
//

class CPOSApp : public CWinApp
{
public:
	CPOSApp();

// ��д
public:
	virtual BOOL InitInstance();

	User  m_curUser;
	POS   m_curPOS;

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPOSApp theApp;
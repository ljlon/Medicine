
// Configure.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "StdHead.h"

#define APP_CONFIGURE _T("����")

// CConfigureApp:
// �йش����ʵ�֣������ Configure.cpp
//

class CConfigureApp : public CWinApp
{
public:
	CConfigureApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CConfigureApp theApp;
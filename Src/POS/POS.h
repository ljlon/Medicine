
// POS.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "UserDB.h"
#include "POSDB.h"

#define APP_POS _T("POS收银终端")

// CPOSApp:
// 有关此类的实现，请参阅 POS.cpp
//

class CPOSApp : public CWinApp
{
public:
	CPOSApp();

// 重写
public:
	virtual BOOL InitInstance();

	User  m_curUser;
	POS   m_curPOS;

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CPOSApp theApp;
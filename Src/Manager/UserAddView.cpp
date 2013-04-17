// UserAddView.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "UserAddView.h"
#include "MainFrm.h"

// CUserAddView

IMPLEMENT_DYNCREATE(CUserAddView, CFormView)

	CUserAddView::CUserAddView()
	: CFormView(CUserAddView::IDD)
{
	m_bDataChanged = FALSE;
}

CUserAddView::~CUserAddView()
{
	for (unsigned int i = 0; i < m_vctUserRoles.size(); i++)
	{
		delete m_vctUserRoles[i];
		m_vctUserRoles[i] = NULL;
	}
	m_vctUserRoles.clear();
}

void CUserAddView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUserAddView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_USER_ADD_OK, &CUserAddView::OnBnClickedButtonUserAddOk)
	ON_BN_CLICKED(IDC_BUTTON_USER_ADD_CANCEL, &CUserAddView::OnBnClickedButtonUserCancel)
	ON_EN_CHANGE(IDC_EDIT_USER_NAME, &CUserAddView::OnEnChangeEditUserName)
	ON_EN_CHANGE(IDC_EDIT_USER_UID, &CUserAddView::OnEnChangeEditUserID)
	ON_CBN_SELCHANGE(IDC_COMBO_USER_ROLE, &CUserAddView::OnCbnSelchangeComboUserRole)
END_MESSAGE_MAP()


// CUserAddView diagnostics

#ifdef _DEBUG
void CUserAddView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserAddView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserAddView message handlers

void CUserAddView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CString csMsg;
	csMsg.Format("%s-%s", APP_NAME, APP_MANAGER);
	AfxGetApp()->GetMainWnd()->SetWindowText(csMsg);

	CFont *pFont = g_theme.GetFont();
	if (pFont != NULL)
	{
		SetFont(pFont);
		CWnd *pw = GetWindow(GW_CHILD);
		while(pw != NULL)
		{
			pw->SetFont(pFont);
			pw = pw->GetWindow(GW_HWNDNEXT);
		};
	}

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc != NULL)
	{
		CUserDB userDB;
		if (atoi(theApp.m_curUser.csRole) == Role_Supper || atoi(theApp.m_curUser.csRole) == Role_Manager)
		{
			ERRCODE errRet = userDB.GetUserRoles(m_vctUserRoles);
			if (errRet != err_OK)
			{
				csMsg.Format(_T("获取用户信息错误！%s"), GetErrMsg(errRet));
				MessageBox(csMsg, _T("用户管理"), MB_ICONERROR);
				return;
			}

			if (atoi(theApp.m_curUser.csRole) != Role_Supper)
			{
				m_vctUserRoles.erase(m_vctUserRoles.begin());
			}

			for (unsigned int i = 0; i < m_vctUserRoles.size(); i++)
			{
				((CComboBox*)GetDlgItem(IDC_COMBO_USER_ROLE))->AddString(m_vctUserRoles[i]->csName);
			}
		}

		m_viewType = pDoc->m_viewType;
		if (m_viewType == VIEW_EDIT)
		{
			((CEdit*)GetDlgItem(IDC_EDIT_USER_UID))->SetReadOnly(TRUE);
			DisplayUserInfo(pDoc->m_csUserUID.GetBuffer());
		}
		else
		{
			((CEdit*)GetDlgItem(IDC_EDIT_USER_UID))->SetReadOnly(FALSE);
		}
	}
}


void CUserAddView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CUserAddView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	CStatic *pStaticGroup = (CStatic*)GetDlgItem(IDC_STATIC_GROUP_DETAIL);
	if (pStaticGroup->GetSafeHwnd() != NULL)
	{
		pStaticGroup->SetWindowPos(NULL, rectClient.left + 5, rectClient.top + 60, rectClient.Width() - 10, rectClient.Height() - 55, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}


void CUserAddView::OnBnClickedButtonUserAddOk()
{
	// TODO: Add your control notification handler code here

	if (AddUser() != TRUE)
	{
		return;
	}
	m_bDataChanged = FALSE;

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}

	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETPRERIGHTPANE, 0);
}


BOOL CUserAddView::BeCancel()
{
	CString csMsg;
	if (m_bDataChanged == TRUE)
	{
		if (m_viewType != VIEW_EDIT)
		{
			csMsg.Format(_T("是否保存该用户信息？"));
		}
		else
		{
			csMsg.Format(_T("是否保存对该用户信息的修改？"));
		}

		int iRet = MessageBox(csMsg, _T("用户管理"), MB_ICONQUESTION|MB_YESNOCANCEL);
		if (iRet == IDCANCEL)
		{
			return FALSE;
		}
		else if (iRet == IDYES)
		{
			if (AddUser() != TRUE)
			{
				return FALSE;
			}
		}
	}

	m_bDataChanged = FALSE;
	return TRUE;
}


void CUserAddView::OnBnClickedButtonUserCancel()
{
	// TODO: Add your control notification handler code here
	if (BeCancel() != TRUE)
	{
		return;
	}

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}

	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETPRERIGHTPANE, 0);
}


void CUserAddView::OnEnChangeEditUserID()
{
	if (m_bDataChanged != TRUE)
	{
		CString csUID;
		GetDlgItemText(IDC_EDIT_USER_UID, csUID);
		csUID.Trim();
		if (csUID != m_user.csUID)
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_USER_ADD_OK)->EnableWindow(TRUE);
		}
	}
}


void CUserAddView::OnEnChangeEditUserName()
{
	if (m_bDataChanged != TRUE)
	{
		CString csName;
		GetDlgItemText(IDC_EDIT_USER_NAME, csName);
		csName.Trim();
		if (csName != m_user.csName)
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_USER_ADD_OK)->EnableWindow(TRUE);
		}
	}
}

void CUserAddView::OnCbnSelchangeComboUserRole()
{
	if (m_bDataChanged != TRUE)
	{
		int iRole = ((CComboBox*)GetDlgItem(IDC_COMBO_USER_ROLE))->GetCurSel();
		if (m_user.csRole != _T("") && iRole == atoi(m_user.csRole))
		{
			//m_bDataChanged = FALSE;
			//GetDlgItem(IDC_BUTTON_USER_ADD_OK)->EnableWindow(FALSE);
		}
		else
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_USER_ADD_OK)->EnableWindow(TRUE);
		}
	}
}


BOOL CUserAddView::AddUser()
{
	ERRCODE errRet = err_OK;
	CString csMsg;
	if (atoi(theApp.m_curUser.csRole) != Role_Supper && atoi(theApp.m_curUser.csRole) != Role_Manager)
	{
		csMsg.Format("需要管理员权限才能够进行此项操作！");
		MessageBox(csMsg, _T("用户管理"), MB_ICONERROR);
		return FALSE;
	}

	CString csUID, csName;
	GetDlgItemText(IDC_EDIT_USER_UID, csUID);
	GetDlgItemText(IDC_EDIT_USER_NAME, csName);

	CString csRole;
	int iRole = ((CComboBox*)GetDlgItem(IDC_COMBO_USER_ROLE))->GetCurSel();
	if (iRole == -1)
	{
		csMsg.Format("请选择用户角色！");
		MessageBox(csMsg, _T("用户管理"), MB_ICONERROR);
		return FALSE;
	}
	GetDlgItemText(IDC_COMBO_USER_ROLE, csRole);
	for (unsigned int i = 0; i < m_vctUserRoles.size(); i++)
	{
		if (m_vctUserRoles[i]->csName == csRole)
		{
			iRole = atoi(m_vctUserRoles[i]->csID);
			break;
		}
	}

	csUID.Trim();
	csName.Trim();
	if (csName == _T(""))
	{
		csMsg.Format("用户名称不能为空！");
		MessageBox(csMsg, _T("用户管理"), MB_ICONERROR);
		return FALSE;
	}

	CUserDB userDB;
	if (m_viewType != VIEW_EDIT)
	{
		errRet = userDB.AddUser(csUID.GetBuffer(), csUID.GetBuffer(), csName.GetBuffer(), iRole);
		if (errRet != err_OK)
		{
			csMsg.Format(_T("添加用户失败，%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("用户管理"), MB_ICONERROR);
			return FALSE;
		}
	}
	else
	{
		errRet = userDB.UpdateUser(m_user.csID.GetBuffer(), csUID.GetBuffer(), csName.GetBuffer(), iRole);
		if (errRet == err_User_AlreadyExist)
		{
			csMsg.Format(_T("用户名称已经存在，请重新输入"));
			MessageBox(csMsg, _T("用户管理"), MB_ICONINFORMATION);
			return FALSE;
		}
		else if (errRet != err_OK)
		{
			csMsg.Format(_T("修改用户失败，%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("用户管理"), MB_ICONERROR);
			return FALSE;
		}
	}

	return TRUE;
}


void CUserAddView::DisplayUserInfo(LPTSTR lpUserUID)
{
	CUserDB userDB;
	CString csMsg;

	ERRCODE errRet = err_OK;

	errRet = userDB.GetUser(lpUserUID, &m_user);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取用户信息错误！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("用户管理"), MB_ICONERROR);
		return;
	}

	SetDlgItemText(IDC_EDIT_USER_UID, m_user.csUID);
	SetDlgItemText(IDC_EDIT_USER_NAME, m_user.csName);

	int iRole = 0;
	for (unsigned int i = 0; i < m_vctUserRoles.size(); i++)
	{
		if (m_vctUserRoles[i]->csID == m_user.csRole)
		{
			iRole = i;
			break;
		}
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_USER_ROLE))->SetCurSel(iRole);
	SetDlgItemText(IDC_COMBO_USER_ROLE, m_user.csName);
}


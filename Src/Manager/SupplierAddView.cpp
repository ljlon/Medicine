// SupplierAddView.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "SupplierAddView.h"
#include "MainFrm.h"

// CSupplierAddView

IMPLEMENT_DYNCREATE(CSupplierAddView, CFormView)

CSupplierAddView::CSupplierAddView()
	: CFormView(CSupplierAddView::IDD)
{
	m_viewType = VIEW_NONE;
	m_bDataChanged = FALSE;
}

CSupplierAddView::~CSupplierAddView()
{
}

void CSupplierAddView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSupplierAddView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_SUPPLIER_ADD_OK, &CSupplierAddView::OnBnClickedButtonSupplierAddOk)
	ON_BN_CLICKED(IDC_BUTTON_SUPPLIER_CANCEL, &CSupplierAddView::OnBnClickedButtonSupplierCancel)
	ON_REGISTERED_MESSAGE(WM_SUPPLIER_ADD_VIEW, &CSupplierAddView::OnSupplierAddView)
	ON_EN_CHANGE(IDC_EDIT_SUPPLIER_NAME, &CSupplierAddView::OnEnChangeEditSupplierName)
	ON_EN_CHANGE(IDC_EDIT_SUPPLIER_CONTACT, &CSupplierAddView::OnEnChangeEditSupplierContact)
	ON_EN_CHANGE(IDC_EDIT_SUPPLIER_TEL, &CSupplierAddView::OnEnChangeEditSupplierTel)
	ON_EN_CHANGE(IDC_EDIT_SUPPLIER_ADDRESS, &CSupplierAddView::OnEnChangeEditSupplierAddress)
END_MESSAGE_MAP()


void CSupplierAddView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CString csMsg;
	csMsg.Format("%s-%s", APP_NAME, APP_MANAGER);
	AfxGetApp()->GetMainWnd()->SetWindowText(csMsg);

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc != NULL)
	{
		m_viewType = pDoc->m_viewType;
		if (m_viewType == VIEW_EDIT)
		{
			DisplaySupplierInfo(pDoc->m_csSupplierID.GetBuffer());
		}
	}

	GetDlgItem(IDC_EDIT_SUPPLIER_NAME)->SetFocus();
}


LRESULT CSupplierAddView::OnSupplierAddView(WPARAM wParam, LPARAM lParam)
{
	//switch(wParam)
	{
	//default:
		//break;
	}
	return 0;
}


void CSupplierAddView::DisplaySupplierInfo(LPTSTR lpSupplierID)
{
	CSupplierDB supplierDB;
	CString csMsg;
	ERRCODE errRet = supplierDB.GetSupplier(lpSupplierID, &m_supplier);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取供应商信息错误！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("供应商管理"), MB_ICONERROR);
		return;
	}

	SetDlgItemText(IDC_EDIT_SUPPLIER_NAME, m_supplier.csName);
	SetDlgItemText(IDC_EDIT_SUPPLIER_CONTACT, m_supplier.csContact);
	SetDlgItemText(IDC_EDIT_SUPPLIER_TEL, m_supplier.csTelephone);
	SetDlgItemText(IDC_EDIT_SUPPLIER_ADDRESS, m_supplier.csAddress);
}


void CSupplierAddView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CSupplierAddView::AdjustLayout()
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
		pStaticGroup->SetWindowPos(NULL, rectClient.left + 5, rectClient.top + 50, rectClient.Width() - 10, rectClient.Height() - 55, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}


// CSupplierAddView 诊断

#ifdef _DEBUG
void CSupplierAddView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSupplierAddView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSupplierAddView 消息处理程序

void CSupplierAddView::OnBnClickedButtonSupplierAddOk()
{
	// TODO: 在此添加控件通知处理程序代码

	if (AddSupplier() != TRUE)
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


BOOL CSupplierAddView::BeCancel()
{
	CString csMsg;
	if (m_bDataChanged == TRUE)
	{
		if (m_viewType != VIEW_EDIT)
		{
			csMsg.Format(_T("是否保存该供应商信息？"));
		}
		else
		{
			csMsg.Format(_T("是否保存对该供应商信息的修改？"));
		}

		int iRet = MessageBox(csMsg, _T("供应商管理"), MB_ICONQUESTION|MB_YESNOCANCEL);
		if (iRet == IDCANCEL)
		{
			return FALSE;
		}
		else if (iRet == IDYES)
		{
			if (AddSupplier() != TRUE)
			{
				return FALSE;
			}
		}
	}

	m_bDataChanged = FALSE;
	return TRUE;
}


void CSupplierAddView::OnBnClickedButtonSupplierCancel()
{
	// TODO: 在此添加控件通知处理程序代码
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


BOOL CSupplierAddView::AddSupplier()
{
	ERRCODE errRet = err_OK;
	CString csMsg;
	CString csName, csContact, csTelephone, csAddress;
	GetDlgItemText(IDC_EDIT_SUPPLIER_NAME, csName);
	GetDlgItemText(IDC_EDIT_SUPPLIER_CONTACT, csContact);
	GetDlgItemText(IDC_EDIT_SUPPLIER_TEL, csTelephone);
	GetDlgItemText(IDC_EDIT_SUPPLIER_ADDRESS, csAddress);

	csName.Trim();
	csContact.Trim();
	csTelephone.Trim();
	csAddress.Trim();
	if (csName == _T(""))
	{
		csMsg.Format("供应商名称不能为空！");
		MessageBox(csMsg, _T("供应商管理"), MB_ICONERROR);
		return FALSE;
	}
	if (csContact == _T(""))
	{
		csMsg.Format("供应商联系人不能为空！");
		MessageBox(csMsg, _T("供应商管理"), MB_ICONERROR);
		return FALSE;
	}

	CSupplierDB supplierDB;
	if (m_viewType != VIEW_EDIT)
	{
		errRet = supplierDB.AddSupplier(csName.GetBuffer(), csContact.GetBuffer(), csTelephone.GetBuffer(), csAddress.GetBuffer());
		if (errRet != err_OK)
		{
			csMsg.Format(_T("添加供应商失败，%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("供应商管理"), MB_ICONERROR);
			return FALSE;
		}
	}
	else
	{
		errRet = supplierDB.UpdateSupplier(m_supplier.csID.GetBuffer(), csName.GetBuffer(), csContact.GetBuffer(), csTelephone.GetBuffer(), csAddress.GetBuffer());
		if (errRet == err_Supplier_AlreadyExist)
		{
			csMsg.Format(_T("供应商名称已经存在，请重新输入"));
			MessageBox(csMsg, _T("供应商管理"), MB_ICONINFORMATION);
			return FALSE;
		}
		else if (errRet != err_OK)
		{
			csMsg.Format(_T("修改供应商失败，%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("供应商管理"), MB_ICONERROR);
			return FALSE;
		}
	}

	return TRUE;
}


void CSupplierAddView::OnEnChangeEditSupplierName()
{
	if (m_bDataChanged != TRUE)
	{
		CString csName;
		GetDlgItemText(IDC_EDIT_SUPPLIER_NAME, csName);
		csName.Trim();
		if (csName != m_supplier.csName)
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_SUPPLIER_ADD_OK)->EnableWindow(TRUE);
		}
	}
}


void CSupplierAddView::OnEnChangeEditSupplierContact()
{
	if (m_bDataChanged != TRUE)
	{
		CString csContact;
		GetDlgItemText(IDC_EDIT_SUPPLIER_CONTACT, csContact);
		csContact.Trim();
		if (csContact != m_supplier.csContact)
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_SUPPLIER_ADD_OK)->EnableWindow(TRUE);
		}
	}
}


void CSupplierAddView::OnEnChangeEditSupplierTel()
{
	if (m_bDataChanged != TRUE)
	{
		CString csTelephone;
		GetDlgItemText(IDC_EDIT_SUPPLIER_TEL, csTelephone);
		csTelephone.Trim();
		if (csTelephone != m_supplier.csTelephone)
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_SUPPLIER_ADD_OK)->EnableWindow(TRUE);
		}
	}
}


void CSupplierAddView::OnEnChangeEditSupplierAddress()
{
	if (m_bDataChanged != TRUE)
	{
		CString csAddress;
		GetDlgItemText(IDC_EDIT_SUPPLIER_ADDRESS, csAddress);
		csAddress.Trim();
		if (csAddress != m_supplier.csAddress)
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_SUPPLIER_ADD_OK)->EnableWindow(TRUE);
		}
	}
}

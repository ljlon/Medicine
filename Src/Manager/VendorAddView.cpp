// VendorAddView.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "VendorAddView.h"
#include "MainFrm.h"

// CVendorAddView

IMPLEMENT_DYNCREATE(CVendorAddView, CFormView)

CVendorAddView::CVendorAddView()
	: CFormView(CVendorAddView::IDD)
{
	m_bDataChanged = FALSE;
}

CVendorAddView::~CVendorAddView()
{
}

void CVendorAddView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVendorAddView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_VENDOR_ADD_OK, &CVendorAddView::OnBnClickedButtonVendorAddOk)
	ON_BN_CLICKED(IDC_BUTTON_VENDOR_CANCEL, &CVendorAddView::OnBnClickedButtonVendorCancel)
	ON_EN_CHANGE(IDC_EDIT_VENDOR_NAME, &CVendorAddView::OnEnChangeEditVendorName)
	ON_EN_CHANGE(IDC_EDIT_VENDOR_TEL, &CVendorAddView::OnEnChangeEditVendorTel)
	ON_EN_CHANGE(IDC_EDIT_VENDOR_ADDRESS, &CVendorAddView::OnEnChangeEditVendorAddress)
END_MESSAGE_MAP()


// CVendorAddView diagnostics

#ifdef _DEBUG
void CVendorAddView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CVendorAddView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CVendorAddView message handlers

void CVendorAddView::OnInitialUpdate()
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
		m_viewType = pDoc->m_viewType;
		if (m_viewType == VIEW_EDIT)
		{
			DisplayVendorInfo(pDoc->m_csVendorID.GetBuffer());
		}
	}

	GetDlgItem(IDC_EDIT_VENDOR_NAME)->SetFocus();
}


void CVendorAddView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CVendorAddView::AdjustLayout()
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


void CVendorAddView::OnBnClickedButtonVendorAddOk()
{
	// TODO: Add your control notification handler code here

	if (AddVendor() != TRUE)
	{
		return;
	}
	m_bDataChanged = FALSE;

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc != NULL && pDoc->m_pMedicAddViewContext != NULL)
	{
		pDoc->m_pMedicAddViewContext->medicine.csVendorID = m_vendor.csID;
	}

	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETPRERIGHTPANE, 0);
}


BOOL CVendorAddView::BeCancel()
{
	CString csMsg;
	if (m_bDataChanged == TRUE)
	{
		if (m_viewType != VIEW_EDIT)
		{
			csMsg.Format(_T("是否保存该生产厂家信息？"));
		}
		else
		{
			csMsg.Format(_T("是否保存对该生产厂家信息的修改？"));
		}

		int iRet = MessageBox(csMsg, _T("生产厂家管理"), MB_ICONQUESTION|MB_YESNOCANCEL);
		if (iRet == IDCANCEL)
		{
			return FALSE;
		}
		else if (iRet == IDYES)
		{
			if (AddVendor() != TRUE)
			{
				return FALSE;
			}
		}
	}

	m_bDataChanged = FALSE;
	return TRUE;
}

void CVendorAddView::OnBnClickedButtonVendorCancel()
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


void CVendorAddView::OnEnChangeEditVendorName()
{
	if (m_bDataChanged != TRUE)
	{
		CString csName;
		GetDlgItemText(IDC_EDIT_VENDOR_NAME, csName);
		csName.Trim();
		if (csName != m_vendor.csName)
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_VENDOR_ADD_OK)->EnableWindow(TRUE);
		}
	}
}


void CVendorAddView::OnEnChangeEditVendorTel()
{
	if (m_bDataChanged != TRUE)
	{
		CString csTelephone;
		GetDlgItemText(IDC_EDIT_VENDOR_TEL, csTelephone);
		csTelephone.Trim();
		if (csTelephone != m_vendor.csTelephone)
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_VENDOR_ADD_OK)->EnableWindow(TRUE);
		}
	}
}


void CVendorAddView::OnEnChangeEditVendorAddress()
{
	if (m_bDataChanged != TRUE)
	{
		CString csAddress;
		GetDlgItemText(IDC_EDIT_VENDOR_ADDRESS, csAddress);
		csAddress.Trim();
		if (csAddress != m_vendor.csAddress)
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_VENDOR_ADD_OK)->EnableWindow(TRUE);
		}
	}
}


BOOL CVendorAddView::AddVendor()
{
	ERRCODE errRet = err_OK;
	CString csMsg;
	CString csName, csTelephone, csAddress;
	GetDlgItemText(IDC_EDIT_VENDOR_NAME, csName);
	GetDlgItemText(IDC_EDIT_VENDOR_TEL, csTelephone);
	GetDlgItemText(IDC_EDIT_VENDOR_ADDRESS, csAddress);

	csName.Trim();
	csTelephone.Trim();
	csAddress.Trim();
	if (csName == _T(""))
	{
		csMsg.Format("生产厂家名称不能为空！");
		MessageBox(csMsg, _T("生产厂家管理"), MB_ICONERROR);
		return FALSE;
	}

	CVendorDB vendorDB;
	m_vendor.csName = csName;
	m_vendor.csTelephone = csTelephone;
	m_vendor.csAddress = csAddress;
	if (m_viewType != VIEW_EDIT)
	{
		errRet = vendorDB.AddVendor(&m_vendor);
		if (errRet != err_OK)
		{
			csMsg.Format(_T("添加生产厂家失败，%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("生产厂家管理"), MB_ICONERROR);
			return FALSE;
		}
	}
	else
	{
		errRet = vendorDB.UpdateVendor(m_vendor.csID.GetBuffer(), csName.GetBuffer(), csTelephone.GetBuffer(), csAddress.GetBuffer());
		if (errRet == err_Vendor_AlreadyExist)
		{
			csMsg.Format(_T("生产厂家名称已经存在，请重新输入"));
			MessageBox(csMsg, _T("生产厂家管理"), MB_ICONINFORMATION);
			return FALSE;
		}
		else if (errRet != err_OK)
		{
			csMsg.Format(_T("修改生产厂家失败，%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("生产厂家管理"), MB_ICONERROR);
			return FALSE;
		}
	}

	return TRUE;
}


void CVendorAddView::DisplayVendorInfo(LPTSTR lpVendorID)
{
	CVendorDB vendorDB;
	CString csMsg;
	ERRCODE errRet = vendorDB.GetVendor(lpVendorID, &m_vendor);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取生产厂家信息错误！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("生产厂家管理"), MB_ICONERROR);
		return;
	}

	SetDlgItemText(IDC_EDIT_VENDOR_NAME, m_vendor.csName);
	SetDlgItemText(IDC_EDIT_VENDOR_TEL, m_vendor.csTelephone);
	SetDlgItemText(IDC_EDIT_VENDOR_ADDRESS, m_vendor.csAddress);
}
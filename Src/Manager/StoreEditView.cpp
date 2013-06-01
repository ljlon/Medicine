// StoreEditView.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "StoreEditView.h"
#include "mainfrm.h"
#include "MedicineBatchDB.h"

// CStoreEditView

IMPLEMENT_DYNCREATE(CStoreEditView, CFormView)

CStoreEditView::CStoreEditView()
	: CFormView(CStoreEditView::IDD)
{
	m_pPopupEditCtrl = NULL;
	m_pDataTimeCtrl = NULL;
}

CStoreEditView::~CStoreEditView()
{
	if (m_pPopupEditCtrl != NULL)
	{
		delete m_pPopupEditCtrl;
		m_pPopupEditCtrl = NULL;
	}

	if (m_pDataTimeCtrl != NULL)
	{
		delete m_pDataTimeCtrl;
		m_pDataTimeCtrl = NULL;
	}
}

void CStoreEditView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MEDICINE_SN, m_editMedicineSN);
	DDX_Control(pDX, IDC_EDIT_MEDICINE_NAME, m_editMedicineName);
	DDX_Control(pDX, IDC_EDIT_MEDICINE_VENDOR, m_editMedicineVendor);
	DDX_Control(pDX, IDC_EDIT_MEDICINE_RETAILPRICE, m_editRetailPrice);
	DDX_Control(pDX, IDC_EDIT_MEDICINE_SPEC, m_editMedicineSpec);
	DDX_Control(pDX, IDC_EDIT_MEDICINE_STORE_NUM, m_editMedicineNum);
	DDX_Control(pDX, IDC_STATIC_MEDICINE_STORE_UNIT, m_staticMedicineUnit);
	DDX_Control(pDX, IDC_BUTTON_OK, m_btnOK);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_BUTTON_MEDICINE_EDIT, m_btnMedicineDetail);
	DDX_Control(pDX, IDC_LIST_STORE_BATCH, m_listBatchStore);
	DDX_Control(pDX, IDC_BUTTON_STORE_BATCH_DEL, m_btnBatchDel);
	DDX_Control(pDX, IDC_STATIC_BATCH_PAGE, m_staticPageInfo);
	DDX_Control(pDX, IDC_BTN_BATCH_PREPAGE, m_btnPrePage);
	DDX_Control(pDX, IDC_BTN_BATCH_NEXTPAGE, m_btnNextPage);
}

BEGIN_MESSAGE_MAP(CStoreEditView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_MEDICINE_EDIT, &CStoreEditView::OnBnClickedButtonMedicineEdit)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CStoreEditView::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CStoreEditView::OnBnClickedButtonOk)
	//ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE_PRODUCT, &CStoreEditView::OnDtnDatetimechangeDateProduct)
	//ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE_EXPIRE, &CStoreEditView::OnDtnDatetimechangeDateExpire)
	//ON_EN_CHANGE(IDC_EDIT_MEDICINE_NUM, &CStoreEditView::OnEnChangeEditMedicineNum)
	ON_EN_CHANGE(IDC_EDIT_MEDICINE_RETAILPRICE, &CStoreEditView::OnEnChangeEditMedicineRetailprice)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STORE_BATCH, &CStoreEditView::OnNMClickListStoreBatch)
	ON_EN_KILLFOCUS(IDC_EDIT_POPUP, &CStoreEditView::OnCbnKillfocusPopupEdit)
	ON_EN_CHANGE(IDC_EDIT_POPUP, &CStoreEditView::OnEnChangeEditPopup)
	ON_NOTIFY(NM_KILLFOCUS, IDC_DATETIMEPICKER, &CStoreEditView::OnNMKillfocusDatetime)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_STORE_BATCH, &CStoreEditView::OnLvnItemchangedListStoreBatch)
	ON_BN_CLICKED(IDC_BUTTON_STORE_BATCH_DEL, &CStoreEditView::OnBnClickedButtonStoreBatchDel)
END_MESSAGE_MAP()


// CStoreEditView diagnostics

#ifdef _DEBUG
void CStoreEditView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStoreEditView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CStoreEditView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

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

	m_listBatchStore.SetExtendedStyle(LVS_EX_FLATSB    // 扁平风格滚动
		| LVS_EX_FULLROWSELECT    // 允许整行选中
		| LVS_EX_HEADERDRAGDROP    // 允许标题拖拽
		| LVS_EX_GRIDLINES    // 画出网格线
		| LVS_EX_CHECKBOXES
		);
	int iItem = 0;
	m_listBatchStore.InsertColumn(iItem++, "", LVCFMT_LEFT, 20, 0);
	m_listBatchStore.InsertColumn(iItem++, "编号", LVCFMT_LEFT, 0, 0);
	m_listBatchStore.InsertColumn(iItem++, "批号", LVCFMT_LEFT, 80, 0);
	m_listBatchStore.InsertColumn(iItem++, "生产日期", LVCFMT_LEFT, 120, 0);
	m_listBatchStore.InsertColumn(iItem++, "有效期至", LVCFMT_LEFT, 120, 0);
	m_listBatchStore.InsertColumn(iItem++, "库存数量", LVCFMT_LEFT, 60, 0);
	m_listBatchStore.InsertColumn(iItem++, "药品单位", LVCFMT_LEFT, 40, 0);

	m_pPopupEditCtrl = new CEdit;
	m_pPopupEditCtrl->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP , CRect(0,0,0,0), this, IDC_EDIT_POPUP);
	m_pPopupEditCtrl->ShowWindow(SW_HIDE);
	m_pPopupEditCtrl->SetParent(&m_listBatchStore);

	m_pDataTimeCtrl = new CDateTimeCtrl;
	m_pDataTimeCtrl->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP , CRect(0,0,0,0), this, IDC_DATETIMEPICKER);
	m_pDataTimeCtrl->ShowWindow(SW_HIDE);
	m_pDataTimeCtrl->SetParent(&m_listBatchStore);

	m_btnOK.EnableWindow(FALSE);
	m_btnCancel.EnableWindow(TRUE);
	if (LoadDataFromDoc() == TRUE)
	{
		m_btnMedicineDetail.EnableWindow(TRUE);
	}
	else
	{
		m_btnMedicineDetail.EnableWindow(FALSE);
	}
}

void CStoreEditView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CStoreEditView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	int iWidth, iHeight;
	CRect clientRect;
	GetClientRect(clientRect);

	CRect basicGroupRect;
	CStatic *pStaticGroupBasic = (CStatic*)GetDlgItem(IDC_STATIC_GROUP_MEDICINE_BASIC);
	if (pStaticGroupBasic->GetSafeHwnd() != NULL)
	{
		pStaticGroupBasic->GetWindowRect(basicGroupRect);
		ScreenToClient(&basicGroupRect);
		basicGroupRect.right = clientRect.right - (basicGroupRect.left - clientRect.left);
		pStaticGroupBasic->SetWindowPos(NULL, basicGroupRect.left, basicGroupRect.top, basicGroupRect.Width(), basicGroupRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect batchGroupRect;
	CStatic *pStaticGroupBatch = (CStatic*)GetDlgItem(IDC_STATIC_GROUP_MEDICINE_BATCH);
	if (pStaticGroupBatch->GetSafeHwnd() != NULL)
	{
		pStaticGroupBatch->GetWindowRect(batchGroupRect);
		ScreenToClient(&batchGroupRect);
		batchGroupRect.right = clientRect.right - (batchGroupRect.left - clientRect.left);
		pStaticGroupBatch->SetWindowPos(NULL, batchGroupRect.left, batchGroupRect.top, batchGroupRect.Width(), batchGroupRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect batchStoreListRect;
	CListCtrl *pBatchStoreList = (CListCtrl*)GetDlgItem(IDC_LIST_STORE_BATCH);
	if (pBatchStoreList->GetSafeHwnd() != NULL)
	{
		pBatchStoreList->GetWindowRect(batchStoreListRect);
		ScreenToClient(&batchStoreListRect);
		batchStoreListRect.right = clientRect.right - (batchStoreListRect.left - clientRect.left);
		batchStoreListRect.bottom = clientRect.bottom - 5;
		pBatchStoreList->SetWindowPos(NULL, batchStoreListRect.left, batchStoreListRect.top, batchStoreListRect.Width(), batchStoreListRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect nextBtnRect;
	CButton *pBtnNextPage = (CButton*)GetDlgItem(IDC_BTN_BATCH_NEXTPAGE);
	if (pBtnNextPage->GetSafeHwnd() != NULL)
	{
		pBtnNextPage->GetClientRect(nextBtnRect);
		iWidth = nextBtnRect.Width();
		iHeight = nextBtnRect.Height();
		nextBtnRect.right = clientRect.Width() - 7;
		nextBtnRect.left = nextBtnRect.right - iWidth;
		nextBtnRect.top = batchGroupRect.top + 20;
		nextBtnRect.bottom =  nextBtnRect.top + iHeight;
		pBtnNextPage->SetWindowPos(NULL, nextBtnRect.left, nextBtnRect.top, nextBtnRect.Width(),  nextBtnRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect preBtnRect;
	CButton *pBtnPrePage = (CButton*)GetDlgItem(IDC_BTN_BATCH_PREPAGE);
	if (pBtnPrePage->GetSafeHwnd() != NULL)
	{
		pBtnPrePage->GetClientRect(preBtnRect);
		iWidth = preBtnRect.Width();
		iHeight = preBtnRect.Height();
		preBtnRect.right =  nextBtnRect.left;
		preBtnRect.left = preBtnRect.right - iWidth;
		preBtnRect.top = nextBtnRect.top;
		preBtnRect.bottom =  preBtnRect.top + iHeight;
		pBtnPrePage->SetWindowPos(NULL, preBtnRect.left, preBtnRect.top, preBtnRect.Width(),  preBtnRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect pageInfoRect;
	CStatic *pStaticPageInfo = (CStatic*)GetDlgItem(IDC_STATIC_BATCH_PAGE);
	if (pStaticPageInfo->GetSafeHwnd() != NULL)
	{
		pStaticPageInfo->GetClientRect(pageInfoRect);
		iWidth = pageInfoRect.Width();
		iHeight = pageInfoRect.Height();
		pageInfoRect.right =  preBtnRect.left - 3;
		pageInfoRect.left = pageInfoRect.right - iWidth;
		pageInfoRect.top = nextBtnRect.top + 5;
		pageInfoRect.bottom =  pageInfoRect.top + iHeight;
		pStaticPageInfo->SetWindowPos(NULL, pageInfoRect.left, pageInfoRect.top, pageInfoRect.Width(),  pageInfoRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect storeDelRect;
	CButton *pStoreDelBtn = (CButton*)GetDlgItem(IDC_BUTTON_STORE_BATCH_DEL);
	if (pStoreDelBtn->GetSafeHwnd() != NULL)
	{
		pStoreDelBtn->GetClientRect(&storeDelRect);
		iWidth = storeDelRect.Width();
		iHeight = storeDelRect.Height();
		storeDelRect.left = batchGroupRect.left + 5;
		storeDelRect.top = batchGroupRect.top + 25;
		storeDelRect.right = storeDelRect.left + iWidth;
		storeDelRect.bottom = storeDelRect.top + iHeight;
		pStoreDelBtn->SetWindowPos(NULL, storeDelRect.left, storeDelRect.top, storeDelRect.Width(), storeDelRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

}

BOOL CStoreEditView::LoadDataFromDoc()
{
	ERRCODE errRet = err_OK;
	CString csMsg;
	CSupplierDB supplierDB;
	int iListItem = -1;
	DOUBLE dbTotalPrice = 0;
	DWORD dwTotalNum = 0;
	DWORD dwTotalPage = 0;

	STOREEDITVIEW_CONTEXT *pStoreEditViewContext = NULL;
	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return FALSE;
	}

	pStoreEditViewContext = pDoc->m_pStoreEditViewContext;
	if (pStoreEditViewContext == NULL)
	{
		return TRUE;
	}

	CStoreDB storeDB;

	errRet = storeDB.GetMedicineStore(pStoreEditViewContext->medicineStore.csMedicineSN.GetBuffer(), &pStoreEditViewContext->medicineStore);
	if (errRet != err_OK)
	{
		return FALSE;
	}

	m_editMedicineSN.SetWindowText(pStoreEditViewContext->medicineStore.csMedicineSN);
	m_editMedicineName.SetWindowText(pStoreEditViewContext->medicineStore.csMedicineName);
	m_editMedicineVendor.SetWindowText(pStoreEditViewContext->medicineStore.csMedicineVendorName);
	m_editMedicineSpec.SetWindowText(pStoreEditViewContext->medicineStore.csMedicineSpec);
	csMsg.Format(_T("%0.2f"), atof(pStoreEditViewContext->medicineStore.csMedicineRetailPrice));
	m_editRetailPrice.SetWindowText(csMsg);
	m_editMedicineNum.SetWindowText(pStoreEditViewContext->medicineStore.csMedicineNum);
	m_staticMedicineUnit.SetWindowText(pStoreEditViewContext->medicineStore.csMedicineUnitName);

	for (unsigned int i = 0; i < pStoreEditViewContext->vctBatchStore.size(); i++)
	{
		delete pStoreEditViewContext->vctBatchStore[i];
		pStoreEditViewContext->vctBatchStore[i] = NULL;
	}
	pStoreEditViewContext->vctBatchStore.clear();
	errRet = storeDB.GetMedicineBatchStores(0, 
		g_ciNumPerPage, 
		dwTotalPage, 
		dwTotalNum,
		pStoreEditViewContext->vctBatchStore,
		pStoreEditViewContext->medicineStore.csMedicineSN.GetBuffer());
	if (errRet != err_OK)
	{
		return FALSE;
	}
	m_listBatchStore.DeleteAllItems();
	for (unsigned int i = 0; i < pStoreEditViewContext->vctBatchStore.size(); i++)
	{
		m_listBatchStore.InsertItem(i, _T(""));
		int iItem = 1;
		m_listBatchStore.SetItemText(i, iItem++, pStoreEditViewContext->vctBatchStore[i]->csID);
		m_listBatchStore.SetItemText(i, iItem++, pStoreEditViewContext->vctBatchStore[i]->csMedicineBatchNum);
		m_listBatchStore.SetItemText(i, iItem++, pStoreEditViewContext->vctBatchStore[i]->csMedicineProductDate);
		m_listBatchStore.SetItemText(i, iItem++, pStoreEditViewContext->vctBatchStore[i]->csMedicineExpireDate);
		m_listBatchStore.SetItemText(i,iItem++, pStoreEditViewContext->vctBatchStore[i]->csMedicineNum);
		m_listBatchStore.SetItemText(i, iItem++, pStoreEditViewContext->vctBatchStore[i]->csMedicineUnitName);
	}
	return TRUE;
}

BOOL CStoreEditView::SaveDataToDoc()
{
	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return FALSE;
	}

	if (pDoc->m_pStoreEditViewContext == NULL)
	{
		pDoc->m_pStoreEditViewContext = new STOREEDITVIEW_CONTEXT;
		if (pDoc->m_pStoreEditViewContext == NULL)
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CStoreEditView::SaveMedicineStore()
{
	STOREEDITVIEW_CONTEXT *pStoreEditViewContext = NULL;
	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return FALSE;
	}

	pStoreEditViewContext = pDoc->m_pStoreEditViewContext;
	if (pStoreEditViewContext == NULL)
	{
		return FALSE;
	}

	ERRCODE errRet = err_OK;
	CString csMsg, csInfo;

	CStoreDB storeDB;
	CMedicineDB medicineDB;
	CMedicineBatchDB medicineBatchDB;

	m_editRetailPrice.GetWindowText(csMsg);
	csMsg.Trim();
	if (csMsg != pStoreEditViewContext->medicineStore.csMedicineRetailPrice)
	{
		errRet = medicineDB.UpdateMedicineRetailPrice(pStoreEditViewContext->medicineStore.csMedicineID.GetBuffer(), atof(csMsg.GetBuffer()));
		if (errRet != err_OK)
		{
			csMsg.Format(_T("更新药品信息失败，%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("库存管理"), MB_ICONERROR);
			return FALSE;
		}
	}

	MedicineBatch medicineBatch;
	pStoreEditViewContext->medicineStore.csMedicineID.Trim();
	medicineBatch.csMedicineID = pStoreEditViewContext->medicineStore.csMedicineID;

	for (int i = 0; i < m_listBatchStore.GetItemCount(); i++)
	{
		medicineBatch.csBatchNum = m_listBatchStore.GetItemText(i, 2);
		medicineBatch.csBatchNum.Trim();
		medicineBatch.csProductDate = m_listBatchStore.GetItemText(i, 3);
		medicineBatch.csProductDate.Trim();
		medicineBatch.csExpireDate = m_listBatchStore.GetItemText(i, 4);
		medicineBatch.csExpireDate.Trim();

		if (CmpDate(medicineBatch.csProductDate.GetBuffer(), pStoreEditViewContext->vctBatchStore[i]->csMedicineProductDate.GetBuffer()) != 0 ||
			CmpDate(medicineBatch.csExpireDate.GetBuffer(), pStoreEditViewContext->vctBatchStore[i]->csMedicineExpireDate.GetBuffer()) != 0)
		{
			errRet = medicineBatchDB.UpdateMedicineBatch(medicineBatch.csMedicineID.GetBuffer(), medicineBatch.csBatchNum.GetBuffer(), &medicineBatch);
			if (errRet != err_OK)
			{
				csMsg.Format(_T("更新药品批号失败，%s"), GetErrMsg(errRet));
				MessageBox(csMsg, _T("库存管理"), MB_ICONERROR);
				return FALSE;
			}
		}

		csInfo = m_listBatchStore.GetItemText(i, 1);
		csInfo.Trim();
		csMsg = m_listBatchStore.GetItemText(i, 5);
		csMsg.Trim();
		if (csMsg != pStoreEditViewContext->vctBatchStore[i]->csMedicineNum)
		{
			errRet = storeDB.UpdateMedicineBatchStore(csInfo.GetBuffer(), atol(csMsg.GetBuffer()));
			if (errRet != err_OK)
			{
				csMsg.Format(_T("更新药品库存失败，%s"), GetErrMsg(errRet));
				MessageBox(csMsg, _T("库存管理"), MB_ICONERROR);
				return FALSE;
			}
		}
	}

	return TRUE;
}

// CStoreEditView message handlers

void CStoreEditView::OnBnClickedButtonMedicineEdit()
{
	// TODO: Add your control notification handler code here

	STOREEDITVIEW_CONTEXT *pStoreEditViewContext = NULL;
	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}

	pStoreEditViewContext = pDoc->m_pStoreEditViewContext;
	if (pStoreEditViewContext == NULL)
	{
		return;
	}
	pDoc->m_viewType = VIEW_EDIT;
	pDoc->m_csMedicineID = pStoreEditViewContext->medicineStore.csMedicineID;

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}

	m_btnOK.EnableWindow(FALSE);
	TreeMenuID leftPanelID = TREE_MEDICINE_ADD;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}

BOOL CStoreEditView::BeCancel()
{
	if (m_btnOK.IsWindowEnabled() == TRUE)
	{
		CString csMsg;
		csMsg.Format(_T("是否保存对该药品库存信息的修改？"));

		int iRet = MessageBox(csMsg, _T("库存管理"), MB_ICONQUESTION|MB_YESNOCANCEL);
		if (iRet == IDCANCEL)
		{
			return FALSE;
		}
		else if (iRet == IDYES)
		{
			if (SaveMedicineStore() != TRUE)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

void CStoreEditView::OnBnClickedButtonCancel()
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


void CStoreEditView::OnBnClickedButtonOk()
{
	// TODO: Add your control notification handler code here

	if (SaveMedicineStore() != TRUE)
	{
		return;
	}
	m_btnOK.EnableWindow(FALSE);

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETPRERIGHTPANE, 0);
}


/*void CStoreEditView::OnDtnDatetimechangeDateProduct(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	STOREEDITVIEW_CONTEXT *pStoreEditViewContext = NULL;
	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}

	pStoreEditViewContext = pDoc->m_pStoreEditViewContext;
	if (pStoreEditViewContext == NULL)
	{
		return;
	}

	CString csMsg;
	//m_productDate.GetWindowText(csMsg);
	csMsg.Trim();
	if (CmpDate(csMsg.GetBuffer(), pStoreEditViewContext->batchStore.csMedicineProductDate.GetBuffer()) != 0)
	{
		m_btnOK.EnableWindow(TRUE);
	}
}


void CStoreEditView::OnDtnDatetimechangeDateExpire(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	STOREEDITVIEW_CONTEXT *pStoreEditViewContext = NULL;
	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}

	pStoreEditViewContext = pDoc->m_pStoreEditViewContext;
	if (pStoreEditViewContext == NULL)
	{
		return;
	}

	CString csMsg;
	//m_expireDate.GetWindowText(csMsg);
	csMsg.Trim();
	if (CmpDate(csMsg.GetBuffer(), pStoreEditViewContext->batchStore.csMedicineExpireDate.GetBuffer()) != 0)
	{
		m_btnOK.EnableWindow(TRUE);
	}
}


void CStoreEditView::OnEnChangeEditMedicineNum()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	STOREEDITVIEW_CONTEXT *pStoreEditViewContext = NULL;
	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}

	pStoreEditViewContext = pDoc->m_pStoreEditViewContext;
	if (pStoreEditViewContext == NULL)
	{
		return;
	}

	CString csMsg;
	//m_editMedicineBatchNum.GetWindowText(csMsg);
	csMsg.Trim();
	if (csMsg != pStoreEditViewContext->batchStore.csMedicineNum)
	{
		m_btnOK.EnableWindow(TRUE);
	}
}*/


void CStoreEditView::OnEnChangeEditMedicineRetailprice()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	STOREEDITVIEW_CONTEXT *pStoreEditViewContext = NULL;
	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}

	pStoreEditViewContext = pDoc->m_pStoreEditViewContext;
	if (pStoreEditViewContext == NULL)
	{
		return;
	}

	CString csMsg;
	m_editRetailPrice.GetWindowText(csMsg);
	csMsg.Trim();

	int iStart = 0; 
	int iEnd = 0; 
	m_editRetailPrice.GetSel(iStart, iEnd); 
	if (iEnd == 0) 
	{ 
		return; 
	} 

	if (csMsg.GetLength() > 0) 
	{ 
		TCHAR tch = csMsg.GetAt(iEnd-1); 
		if ( ((!(tch>='0' && tch<='9') && tch != '.')) 
			|| csMsg.Find('.') !=  csMsg.ReverseFind('.') ) 
		{ 
			int iSetPos = csMsg.GetLength(); 
			csMsg.Delete(iEnd-1, 1); 
			m_editRetailPrice.SetWindowText(csMsg); 
			m_editRetailPrice.SetSel(iSetPos-1,iSetPos-1); 
		} 
	} 

	if (csMsg != pStoreEditViewContext->medicineStore.csMedicineRetailPrice)
	{
		m_btnOK.EnableWindow(TRUE);
	}
}


void CStoreEditView::OnNMClickListStoreBatch(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CString csMsg;

	POINT pt;
	GetCursorPos(&pt);
	m_listBatchStore.ScreenToClient(&pt);
	LVHITTESTINFO hitInfo;
	hitInfo.pt=pt;
	m_listBatchStore.SubItemHitTest(&hitInfo);

	if((hitInfo.flags & LVHT_ONITEMLABEL) &&      //判断是否单击在文本上
		(hitInfo.iItem != m_listBatchStore.GetItemCount()) &&
		hitInfo.iSubItem != -1)
	{
		CRect rect;
		int iActiveSubItem = -1;

		if (hitInfo.iSubItem == 3 || 
			hitInfo.iSubItem == 4	)
		{
			iActiveSubItem = hitInfo.iSubItem;
			m_iBatchListItem = hitInfo.iItem;
			m_iBatchListSubItem = iActiveSubItem;

			m_listBatchStore.GetSubItemRect(hitInfo.iItem,iActiveSubItem,LVIR_BOUNDS,rect);

			csMsg = m_listBatchStore.GetItemText(hitInfo.iItem,iActiveSubItem);
			m_pDataTimeCtrl->MoveWindow(&rect,TRUE);

			SYSTEMTIME time;  
			if (ChangeDate(csMsg.GetBuffer(), time) == TRUE)
			{
				m_pDataTimeCtrl->SetTime(&time);
			}
			else
			{
				CTime  time = CTime::GetCurrentTime();
				m_pDataTimeCtrl->SetTime(&time);
			}
			m_pDataTimeCtrl->SetWindowText(csMsg);
			m_pDataTimeCtrl->ShowWindow(SW_SHOW);
			m_pDataTimeCtrl->BringWindowToTop();
			m_pDataTimeCtrl->SetFocus();
		}
		else if (hitInfo.iSubItem == 5)
		{
			iActiveSubItem = hitInfo.iSubItem;

			m_iBatchListItem = hitInfo.iItem;
			m_iBatchListSubItem = iActiveSubItem;

			m_listBatchStore.GetSubItemRect(hitInfo.iItem,iActiveSubItem,LVIR_BOUNDS,rect);
			rect.InflateRect(0,0,0,-1);

			csMsg = m_listBatchStore.GetItemText(hitInfo.iItem,iActiveSubItem);
			m_pPopupEditCtrl->MoveWindow(&rect,TRUE);
			m_pPopupEditCtrl->ShowWindow(SW_NORMAL);
			m_pPopupEditCtrl->SetWindowText(csMsg);
			m_pPopupEditCtrl->BringWindowToTop();
			m_pPopupEditCtrl->SetFocus();//使组合框聚焦
			m_pPopupEditCtrl->CreateSolidCaret(1,rect.Height()-3);//创建一个光标
			m_pPopupEditCtrl->ShowCaret();//显示光标
			m_pPopupEditCtrl->SetSel(0);//使光标移到最后面
		}
	}
}

void CStoreEditView::OnEnChangeEditPopup()
{
	if (m_iBatchListSubItem != -1)
	{
		if (m_iBatchListSubItem == 5)
		{
			CString csNum;
			m_pPopupEditCtrl->GetWindowText(csNum);
			csNum.Trim();

			int iStart = 0; 
			int iEnd = 0; 
			m_pPopupEditCtrl->GetSel(iStart, iEnd); 
			if (iEnd == 0) 
			{ 
				return; 
			} 

			if (csNum.GetLength() > 0) 
			{ 
				TCHAR tch = csNum.GetAt(iEnd-1); 
				if (!(tch>='0' && tch<='9')) 
				{ 
					int iSetPos = csNum.GetLength(); 
					csNum.Delete(iEnd-1, 1); 
					m_pPopupEditCtrl->SetWindowText(csNum); 
					m_pPopupEditCtrl->SetSel(iSetPos-1,iSetPos-1); 
				} 
			} 
		}
	}
}


void CStoreEditView::OnCbnKillfocusPopupEdit()
{
	// TODO: 在此添加控件通知处理程序代码

	CString csPopUpMsg, csMsg;
	DWORD dwMedicineNum = 0;
	DWORD dwBatchNum = 0;

	if (m_iBatchListSubItem != -1 && m_iBatchListSubItem != 1)
	{
		m_pPopupEditCtrl->GetWindowText(csPopUpMsg);
		csPopUpMsg.Trim();
		m_pPopupEditCtrl->SetWindowText(_T(""));

		csMsg = m_listBatchStore.GetItemText(m_iBatchListItem, m_iBatchListSubItem);
		csMsg.Trim();

		if (csPopUpMsg != csMsg)
		{
			m_btnOK.EnableWindow(TRUE);

			if (m_iBatchListSubItem == 5)
			{
				dwBatchNum = atol(csMsg);

				m_editMedicineNum.GetWindowText(csMsg);
				dwMedicineNum = atol(csMsg);
				
				dwMedicineNum += atol(csPopUpMsg) - dwBatchNum;
				csMsg.Format(_T("%d"), dwMedicineNum);
				m_editMedicineNum.SetWindowText(csMsg);
			}

			m_listBatchStore.SetItemText(m_iBatchListItem, m_iBatchListSubItem, csPopUpMsg);
		}
	}

	m_btnCancel.EnableWindow(TRUE);

	m_iBatchListItem = -1;
	m_iBatchListSubItem = -1;
	m_pPopupEditCtrl->ShowWindow(SW_HIDE);

	Invalidate();
}

void CStoreEditView::OnNMKillfocusDatetime(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	CString csPopUpMsg, csMsg;

	if (m_iBatchListSubItem != -1 && m_iBatchListSubItem != 1)
	{
		m_pDataTimeCtrl->GetWindowText(csPopUpMsg);
		csPopUpMsg.Trim();
		m_pDataTimeCtrl->SetWindowText(_T(""));

		csMsg = m_listBatchStore.GetItemText(m_iBatchListItem, m_iBatchListSubItem);

		if (CmpDate(csPopUpMsg.GetBuffer(), csMsg.GetBuffer()) != 0)
		{
			m_btnOK.EnableWindow(TRUE);
			m_listBatchStore.SetItemText(m_iBatchListItem, m_iBatchListSubItem, csPopUpMsg);
		}
	}

	m_iBatchListItem = -1;
	m_iBatchListSubItem = -1;
	m_pDataTimeCtrl->ShowWindow(SW_HIDE);

	Invalidate();
}

void CStoreEditView::OnLvnItemchangedListStoreBatch(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int iItem = pNMLV->iItem;
	int iSubItem = pNMLV->iSubItem;

	if (iSubItem == 0)
	{
		m_btnBatchDel.EnableWindow(FALSE);

		for (int i = 0; i < m_listBatchStore.GetItemCount(); i++)
		{
			if (m_listBatchStore.GetCheck(i) == TRUE)
			{
				m_btnBatchDel.EnableWindow(TRUE);
				break;
			}
		}
	}
}


void CStoreEditView::OnBnClickedButtonStoreBatchDel()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csMsg;
	ERRCODE errRet;
	vector<CString> vctCheckBatchSN;
	map<int,CString> mapCheckBatchID;
	for (int i = 0; i < m_listBatchStore.GetItemCount(); i++)
	{
		if (m_listBatchStore.GetCheck(i) == TRUE)
		{
			csMsg = m_listBatchStore.GetItemText(i, 1);
			mapCheckBatchID.insert(map<int,CString>::value_type(i,csMsg));
			csMsg = m_listBatchStore.GetItemText(i, 2);
			vctCheckBatchSN.push_back(csMsg);
		}
	}

	if (vctCheckBatchSN.size() == 0)
	{
		return;
	}
	
	csMsg.Format(_T("您确认要删除以下批次的库存信息吗？"));
	for(int i = 0; i < (int)vctCheckBatchSN.size(); i++)
	{
		csMsg.AppendFormat(_T("\r\n    %s"),vctCheckBatchSN[i]);
	}
	if (IDOK != MessageBox(csMsg, _T("库存管理"), MB_ICONQUESTION|MB_OKCANCEL))
	{
		vctCheckBatchSN.clear();
		mapCheckBatchID.clear();
		return;
	}

	m_editMedicineNum.GetWindowText(csMsg);
	DWORD dwMedicineNum = atol(csMsg);

	CStoreDB storeDB;
	for (map<int, CString>::iterator it = mapCheckBatchID.begin();
		it != mapCheckBatchID.end(); it++)
	{
		errRet = storeDB.DeleteMedicineBatchStore(it->second.GetBuffer());
		if (errRet != err_OK)
		{
			csMsg.Format(_T("删除批次%s的库存信息失败！"), it->second.GetBuffer());
			MessageBox(csMsg, _T("库存管理"), MB_ICONERROR|MB_OKCANCEL);
			return;
		}
		csMsg = m_listBatchStore.GetItemText(it->first, 5);
		dwMedicineNum -= atol(csMsg);
		m_listBatchStore.DeleteItem(it->first);
	}

	csMsg.Format(_T("%d"), dwMedicineNum);
	m_editMedicineNum.SetWindowText(csMsg);

	vctCheckBatchSN.clear();
	mapCheckBatchID.clear();
}

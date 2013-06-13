// StoreMgrView.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "StoreMgrView.h"
#include "mainfrm.h"
#include "StoreDB.h"
#include "MedicineDB.h"

// CVendorMgrView

IMPLEMENT_DYNCREATE(CStoreMgrView, CFormView)

CStoreMgrView::CStoreMgrView()
	: CFormView(CStoreMgrView::IDD)
{
	m_dwCurPage = 0;
	m_dwTotalPage = 0;
	m_dwTotalNum = 0;
	m_dwBatchCurPage = 0;
	m_dwBatchTotalPage = 0;
	m_dwBatchTotalNum = 0;
	m_csSelectedMedicineSN = _T("");
}

CStoreMgrView::~CStoreMgrView()
{
}

void CStoreMgrView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STORE, m_listStore);
	DDX_Control(pDX, IDC_LIST_STORE_BATCH, m_listBatchStore);
	DDX_Control(pDX, IDC_STATIC_PAGE, m_staticPageInfo);
	DDX_Control(pDX, IDC_BTN_PREPAGE, m_btnPrePage);
	DDX_Control(pDX, IDC_BTN_NEXTPAGE, m_btnNextPage);
	DDX_Control(pDX, IDC_STATIC_BATCH_PAGE, m_staticBatchPageInfo);
	DDX_Control(pDX, IDC_BTN_BATCH_PREPAGE, m_btnBatchPrePage);
	DDX_Control(pDX, IDC_BTN_BATCH_NEXTPAGE, m_btnBatchNextPage);
	DDX_Control(pDX, IDC_BUTTON_STORE_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BUTTON_STORE_DEL, m_btnDel);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_btnSearch);
	DDX_Control(pDX, IDC_BUTTON_STORE_BATCH_EDIT, m_btnBatchEdit);
	DDX_Control(pDX, IDC_BUTTON_STORE_BATCH_DEL, m_btnBatchDel);
}

BEGIN_MESSAGE_MAP(CStoreMgrView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_PREPAGE, &CStoreMgrView::OnBnClickedBtnPrepage)
	ON_BN_CLICKED(IDC_BTN_NEXTPAGE, &CStoreMgrView::OnBnClickedBtnNextpage)
	ON_BN_CLICKED(IDC_BUTTON_STORE_EDIT, &CStoreMgrView::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_STORE_DEL, &CStoreMgrView::OnBnClickedButtonDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_STORE, &CStoreMgrView::OnLvnItemchangedListStore)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_STORE, &CStoreMgrView::OnNMDblclkListStore)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CStoreMgrView::OnBnClickedButtonSearch)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_STORE_BATCH, &CStoreMgrView::OnLvnItemchangedListStoreBatch)
	ON_BN_CLICKED(IDC_BUTTON_STORE_BATCH_EDIT, &CStoreMgrView::OnBnClickedButtonStoreBatchEdit)
	ON_BN_CLICKED(IDC_BUTTON_STORE_BATCH_DEL, &CStoreMgrView::OnBnClickedButtonStoreBatchDel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_STORE_BATCH, &CStoreMgrView::OnNMDblclkListBatchStore)
	ON_BN_CLICKED(IDC_BTN_BATCH_PREPAGE, &CStoreMgrView::OnBnClickedBtnBatchPrepage)
	ON_BN_CLICKED(IDC_BTN_BATCH_NEXTPAGE, &CStoreMgrView::OnBnClickedBtnBatchNextpage)
END_MESSAGE_MAP()

void CStoreMgrView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	ERRCODE errRet = err_OK;
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

	CRect rectClient;
	GetClientRect(rectClient);

	m_listStore.SetExtendedStyle(LVS_EX_FLATSB    // 扁平风格滚动
		| LVS_EX_FULLROWSELECT    // 允许整行选中
		| LVS_EX_HEADERDRAGDROP    // 允许标题拖拽
		| LVS_EX_GRIDLINES    // 画出网格线
		);

	int iItem = 0;
	m_listStore.InsertColumn(iItem++, "编号", LVCFMT_LEFT, 0, 0);
	m_listStore.InsertColumn(iItem++, "药品编码", LVCFMT_LEFT, 120, 0);
	m_listStore.InsertColumn(iItem++, "药品名称", LVCFMT_LEFT, 150, 0);
	m_listStore.InsertColumn(iItem++, "药品规格", LVCFMT_LEFT, 80, 0);
	m_listStore.InsertColumn(iItem++, "生产厂家", LVCFMT_LEFT, 80, 0);
	m_listStore.InsertColumn(iItem++, "零售价", LVCFMT_LEFT, 60, 0);
	m_listStore.InsertColumn(iItem++, "库存数量", LVCFMT_LEFT, 60, 0);
	m_listStore.InsertColumn(iItem++, "药品单位", LVCFMT_LEFT, 40, 0);

	m_listBatchStore.SetExtendedStyle(LVS_EX_FLATSB    // 扁平风格滚动
		| LVS_EX_FULLROWSELECT    // 允许整行选中
		| LVS_EX_HEADERDRAGDROP    // 允许标题拖拽
		| LVS_EX_GRIDLINES    // 画出网格线
		);
	m_listBatchStore.InsertColumn(iItem++, "编号", LVCFMT_LEFT, 0, 0);
	m_listBatchStore.InsertColumn(iItem++, "批号", LVCFMT_LEFT, 80, 0);
	m_listBatchStore.InsertColumn(iItem++, "生产日期", LVCFMT_LEFT, 80, 0);
	m_listBatchStore.InsertColumn(iItem++, "有效期至", LVCFMT_LEFT, 80, 0);
	m_listBatchStore.InsertColumn(iItem++, "库存数量", LVCFMT_LEFT, 60, 0);

	DisplayListItem();
}

void CStoreMgrView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CStoreMgrView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	int iWidth = 0, iHeight = 0;
	CRect clientRect;
	GetClientRect(clientRect);

	CRect groupStoreRect;
	CStatic *pGroupStore = (CStatic*)GetDlgItem(IDC_STATIC_GROUP_STORE);
	if (pGroupStore->GetSafeHwnd() != NULL)
	{
		groupStoreRect.left = clientRect.left + 5;
		groupStoreRect.top = clientRect.top + 60;
		groupStoreRect.right = groupStoreRect.left + (clientRect.Width() - 10);
		groupStoreRect.bottom = groupStoreRect.top + (clientRect.Height() - 55) * 3 / 5;
		pGroupStore->SetWindowPos(NULL, groupStoreRect.left, groupStoreRect.top, groupStoreRect.Width(), groupStoreRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect storeRect;
	CListCtrl *pStoreList = (CListCtrl*)GetDlgItem(IDC_LIST_STORE);
	if (pStoreList->GetSafeHwnd() != NULL)
	{
		storeRect.left = clientRect.left + 5;
		storeRect.top = groupStoreRect.top + 65;
		storeRect.right = storeRect.left + (clientRect.Width() - 10);
		storeRect.bottom = groupStoreRect.bottom;
		pStoreList->SetWindowPos(NULL, storeRect.left, storeRect.top, storeRect.Width(), storeRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect nextBtnRect;
	CButton *pBtnNextPage = (CButton*)GetDlgItem(IDC_BTN_NEXTPAGE);
	if (pBtnNextPage->GetSafeHwnd() != NULL)
	{
		pBtnNextPage->GetClientRect(nextBtnRect);
		iWidth = nextBtnRect.Width();
		iHeight = nextBtnRect.Height();
		nextBtnRect.right = clientRect.Width() - 7;
		nextBtnRect.left = nextBtnRect.right - iWidth;
		nextBtnRect.top = groupStoreRect.top + 20;
		nextBtnRect.bottom =  nextBtnRect.top + iHeight;
		pBtnNextPage->SetWindowPos(NULL, nextBtnRect.left, nextBtnRect.top, nextBtnRect.Width(),  nextBtnRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect preBtnRect;
	CButton *pBtnPrePage = (CButton*)GetDlgItem(IDC_BTN_PREPAGE);
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
	CStatic *pStaticPageInfo = (CStatic*)GetDlgItem(IDC_STATIC_PAGE);
	if (pStaticPageInfo->GetSafeHwnd() != NULL)
	{
		pStaticPageInfo->GetClientRect(pageInfoRect);
		iWidth = pageInfoRect.Width();
		iHeight = pageInfoRect.Height();
		pageInfoRect.right =  preBtnRect.left - 3;
		pageInfoRect.left = pageInfoRect.right - iWidth;
		pageInfoRect.top = groupStoreRect.top + 25;
		pageInfoRect.bottom =  pageInfoRect.top + iHeight;
		pStaticPageInfo->SetWindowPos(NULL, pageInfoRect.left, pageInfoRect.top, pageInfoRect.Width(),  pageInfoRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}
	
	CRect storeEditRect;
	CButton *pStoreEditBtn = (CButton*)GetDlgItem(IDC_BUTTON_STORE_EDIT);
	if (pStoreEditBtn->GetSafeHwnd() != NULL)
	{
		pStoreEditBtn->GetWindowRect(&storeEditRect);
		ScreenToClient(&storeEditRect);
		iWidth = storeEditRect.Width();
		iHeight = storeEditRect.Height();
		storeEditRect.top = groupStoreRect.top + 25;
		storeEditRect.right = storeEditRect.left + iWidth;
		storeEditRect.bottom = storeEditRect.top + iHeight;
		pStoreEditBtn->SetWindowPos(NULL, storeEditRect.left, storeEditRect.top, storeEditRect.Width(), storeEditRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect storeDelRect;
	CButton *pStoreDelBtn = (CButton*)GetDlgItem(IDC_BUTTON_STORE_DEL);
	if (pStoreDelBtn->GetSafeHwnd() != NULL)
	{
		pStoreDelBtn->GetWindowRect(&storeDelRect);
		ScreenToClient(&storeDelRect);
		iWidth = storeDelRect.Width();
		iHeight = storeDelRect.Height();
		storeDelRect.top = storeEditRect.top;
		storeDelRect.right = storeDelRect.left + iWidth;
		storeDelRect.bottom = storeDelRect.top + iHeight;
		pStoreDelBtn->SetWindowPos(NULL, storeDelRect.left, storeDelRect.top, storeDelRect.Width(), storeDelRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	//
	CRect groupStoreBatchRect;
	CStatic *pGroupStoreBatch = (CStatic*)GetDlgItem(IDC_STATIC_GROUP_STORE_BATCH);
	if (pGroupStoreBatch->GetSafeHwnd() != NULL)
	{
		groupStoreBatchRect.left = clientRect.left + 5;
		groupStoreBatchRect.top = storeRect.bottom + 10;
		groupStoreBatchRect.right = groupStoreBatchRect.left + (clientRect.Width() - 10);
		groupStoreBatchRect.bottom = clientRect.bottom - 5;
		pGroupStoreBatch->SetWindowPos(NULL, groupStoreBatchRect.left, groupStoreBatchRect.top, groupStoreBatchRect.Width(), groupStoreBatchRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect storeBatchRect;
	CListCtrl *pStoreBatchList = (CListCtrl*)GetDlgItem(IDC_LIST_STORE_BATCH);
	if (pStoreBatchList->GetSafeHwnd() != NULL)
	{
		storeBatchRect.left = clientRect.left + 5;
		storeBatchRect.top = groupStoreBatchRect.top + 60;
		storeBatchRect.right = storeBatchRect.left + (clientRect.Width() - 10);
		storeBatchRect.bottom = groupStoreBatchRect.bottom;
		pStoreBatchList->SetWindowPos(NULL, storeBatchRect.left, storeBatchRect.top, storeBatchRect.Width(), storeBatchRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect batchNextBtnRect;
	CButton *pBtnBatchNextPage = (CButton*)GetDlgItem(IDC_BTN_BATCH_NEXTPAGE);
	if (pBtnBatchNextPage->GetSafeHwnd() != NULL)
	{
		pBtnBatchNextPage->GetClientRect(batchNextBtnRect);
		iWidth = batchNextBtnRect.Width();
		iHeight = batchNextBtnRect.Height();
		batchNextBtnRect.right = clientRect.Width() - 7;
		batchNextBtnRect.left = batchNextBtnRect.right - iWidth;
		batchNextBtnRect.top = groupStoreBatchRect.top + 20;
		batchNextBtnRect.bottom =  batchNextBtnRect.top + iHeight;
		pBtnBatchNextPage->SetWindowPos(NULL, batchNextBtnRect.left, batchNextBtnRect.top, batchNextBtnRect.Width(),  batchNextBtnRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect batchPreBtnRect;
	CButton *pBtnBatchPrePage = (CButton*)GetDlgItem(IDC_BTN_BATCH_PREPAGE);
	if (pBtnBatchPrePage->GetSafeHwnd() != NULL)
	{
		pBtnBatchPrePage->GetClientRect(batchPreBtnRect);
		iWidth = batchPreBtnRect.Width();
		iHeight = batchPreBtnRect.Height();
		batchPreBtnRect.right =  batchNextBtnRect.left;
		batchPreBtnRect.left = batchPreBtnRect.right - iWidth;
		batchPreBtnRect.top = batchNextBtnRect.top;
		batchPreBtnRect.bottom =  batchPreBtnRect.top + iHeight;
		pBtnBatchPrePage->SetWindowPos(NULL, batchPreBtnRect.left, batchPreBtnRect.top, batchPreBtnRect.Width(),  batchPreBtnRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect batchPageInfoRect;
	CStatic *pStaticBatchPageInfo = (CStatic*)GetDlgItem(IDC_STATIC_BATCH_PAGE);
	if (pStaticBatchPageInfo->GetSafeHwnd() != NULL)
	{
		pStaticBatchPageInfo->GetClientRect(batchPageInfoRect);
		iWidth = batchPageInfoRect.Width();
		iHeight = batchPageInfoRect.Height();
		batchPageInfoRect.right =  batchPreBtnRect.left;
		batchPageInfoRect.left = batchPageInfoRect.right - iWidth;
		batchPageInfoRect.top = groupStoreBatchRect.top + 25;
		batchPageInfoRect.bottom =  batchPageInfoRect.top + iHeight;
		pStaticBatchPageInfo->SetWindowPos(NULL, batchPageInfoRect.left, batchPageInfoRect.top, batchPageInfoRect.Width(),  pageInfoRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect storeBatchEditRect;
	CButton *pStoreBatchEditBtn = (CButton*)GetDlgItem(IDC_BUTTON_STORE_BATCH_EDIT);
	if (pStoreBatchEditBtn->GetSafeHwnd() != NULL)
	{
		pStoreBatchEditBtn->GetClientRect(&storeBatchEditRect);
		iWidth = storeBatchEditRect.Width();
		iHeight = storeBatchEditRect.Height();
		storeBatchEditRect.left = clientRect.left + 10;
		storeBatchEditRect.top = groupStoreBatchRect.top + 25;
		storeBatchEditRect.right = storeBatchEditRect.left + iWidth;
		storeBatchEditRect.bottom = storeBatchEditRect.top + iHeight;
		pStoreBatchEditBtn->SetWindowPos(NULL, storeBatchEditRect.left, storeBatchEditRect.top, storeBatchEditRect.Width(), storeBatchEditRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect storeBatchDelRect;
	CButton *pStoreBatchDelBtn = (CButton*)GetDlgItem(IDC_BUTTON_STORE_BATCH_DEL);
	if (pStoreBatchDelBtn->GetSafeHwnd() != NULL)
	{
		pStoreBatchDelBtn->GetClientRect(&storeBatchDelRect);
		iWidth = storeBatchDelRect.Width();
		iHeight = storeBatchDelRect.Height();
		storeBatchDelRect.left = storeBatchEditRect.right + 5;
		storeBatchDelRect.top = storeBatchEditRect.top;
		storeBatchDelRect.right = storeBatchDelRect.left + iWidth;
		storeBatchDelRect.bottom = storeBatchDelRect.top + iHeight;
		pStoreBatchDelBtn->SetWindowPos(NULL, storeBatchDelRect.left, storeBatchDelRect.top, storeBatchDelRect.Width(), storeBatchDelRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

// CVendorMgrView diagnostics

#ifdef _DEBUG
void CStoreMgrView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStoreMgrView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CStoreMgrView::DisplayListItem()
{
	m_listStore.DeleteAllItems();
	m_btnEdit.EnableWindow(FALSE);
	m_btnDel.EnableWindow(FALSE);
	m_dwBatchCurPage = 0;
	m_dwBatchTotalNum = 0;
	m_dwBatchTotalPage = 0;
	DisplayBatchListItem(NULL);

	CString csMsg;
	CMedicineDB medicineDB;
	Medicine medicine;
	CStoreDB storeDB;
	vector<MedicineStore*> vctMedicineStore;
	CString csMedicineName;
	csMedicineName.Format(_T("%s"), m_storeSearchDlg.m_csMedicineName);
	ERRCODE errRet = storeDB.GetMedicineStores(m_dwCurPage, 
												g_ciNumPerPage, 
												m_dwTotalPage, 
												m_dwTotalNum, 
												vctMedicineStore,
												m_storeSearchDlg.m_csMedicineSN.GetBuffer(),
												csMedicineName.GetBuffer(),
												m_storeSearchDlg.m_csExpireDate.GetBuffer(),
												m_storeSearchDlg.m_csVendorID.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取库存信息失败！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("库存管理"), MB_ICONERROR);
		return;
	}

	csMsg.Format(_T("第%d-%d项，共%d项"), m_dwTotalNum>0?m_dwCurPage * g_ciNumPerPage + 1:0, m_dwCurPage * g_ciNumPerPage +  vctMedicineStore.size(), m_dwTotalNum);
	m_staticPageInfo.SetWindowText(csMsg);
	if (m_dwCurPage == 0)
	{
		m_btnPrePage.EnableWindow(FALSE);
	}
	else
	{
		m_btnPrePage.EnableWindow(TRUE);
	}
	if (m_dwCurPage + 1 >= m_dwTotalPage)
	{
		m_btnNextPage.EnableWindow(FALSE);
	}
	else
	{
		m_btnNextPage.EnableWindow(TRUE);
	}

	for (unsigned int i = 0; i < vctMedicineStore.size(); i++)
	{
		m_listStore.InsertItem(i, vctMedicineStore[i]->csID);
		int iItem = 1;
		m_listStore.SetItemText(i, iItem++, vctMedicineStore[i]->csMedicineSN);
		m_listStore.SetItemText(i, iItem++, vctMedicineStore[i]->csMedicineName);
		m_listStore.SetItemText(i, iItem++, vctMedicineStore[i]->csMedicineSpec);
		m_listStore.SetItemText(i, iItem++, vctMedicineStore[i]->csMedicineVendorName);
		//m_listStore.SetItemText(i, iItem++, vctMedicineStore[i]->csMedicineBatchNum);
		//m_listStore.SetItemText(i, iItem++, vctMedicineStore[i]->csMedicineProductDate);
		//m_listStore.SetItemText(i, iItem++, vctMedicineStore[i]->csMedicineExpireDate);
		csMsg.Format(_T("%0.2f"), atof(vctMedicineStore[i]->csMedicineRetailPrice));
		m_listStore.SetItemText(i,iItem++, csMsg);
		m_listStore.SetItemText(i,iItem++, vctMedicineStore[i]->csMedicineNum);
		m_listStore.SetItemText(i, iItem++, vctMedicineStore[i]->csMedicineUnitName);

		delete vctMedicineStore[i];
		vctMedicineStore[i] = NULL;
	}
	vctMedicineStore.clear();
}

void CStoreMgrView::DisplayBatchListItem(LPSTR lpMedicineSN)
{
	if (lpMedicineSN == NULL || strlen(lpMedicineSN) == 0)
	{
		return;
	}

	ERRCODE errRet;
	CString csMsg;
	CMedicineDB medicineDB;
	Medicine medicine;
	CStoreDB storeDB;
	vector<MedicineBatchStore*> vctMedicineBatchStore;
	
	if (lpMedicineSN != NULL)
	{
		errRet = storeDB.GetMedicineBatchStores(m_dwBatchCurPage, 
												g_ciNumPerPage, 
												m_dwBatchTotalPage, 
												m_dwBatchTotalNum, 
												vctMedicineBatchStore,
												lpMedicineSN,
												_T(""),
												m_storeSearchDlg.m_csExpireDate.GetBuffer());
		if (errRet != err_OK)
		{
			csMsg.Format(_T("获取库存信息失败！%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("库存管理"), MB_ICONERROR);
			return;
		}
	}

	csMsg.Format(_T("第%d-%d项，共%d项"), m_dwBatchTotalNum>0?m_dwBatchCurPage * g_ciNumPerPage + 1:0, m_dwBatchCurPage * g_ciNumPerPage +  vctMedicineBatchStore.size(), m_dwBatchTotalNum);
	m_staticBatchPageInfo.SetWindowText(csMsg);
	if (m_dwBatchCurPage == 0)
	{
		m_btnBatchPrePage.EnableWindow(FALSE);
	}
	else
	{
		m_btnBatchPrePage.EnableWindow(TRUE);
	}
	if (m_dwBatchCurPage + 1 >= m_dwBatchTotalPage)
	{
		m_btnBatchNextPage.EnableWindow(FALSE);
	}
	else
	{
		m_btnBatchNextPage.EnableWindow(TRUE);
	}

	m_listBatchStore.DeleteAllItems();
	for (unsigned int i = 0; i < vctMedicineBatchStore.size(); i++)
	{
		m_listBatchStore.InsertItem(i, vctMedicineBatchStore[i]->csID);
		int iItem = 1;
		m_listBatchStore.SetItemText(i, iItem++, vctMedicineBatchStore[i]->csMedicineBatchNum);
		m_listBatchStore.SetItemText(i, iItem++, vctMedicineBatchStore[i]->csMedicineProductDate);
		m_listBatchStore.SetItemText(i, iItem++, vctMedicineBatchStore[i]->csMedicineExpireDate);
		m_listBatchStore.SetItemText(i,iItem++, vctMedicineBatchStore[i]->csMedicineNum);

		delete vctMedicineBatchStore[i];
		vctMedicineBatchStore[i] = NULL;
	}
	vctMedicineBatchStore.clear();
}

// CStoreMgrView message handlers

void CStoreMgrView::OnBnClickedBtnPrepage()
{
	// TODO: Add your control notification handler code here
	if (m_dwCurPage <= 0)
	{
		return;
	}

	m_dwCurPage--;
	DisplayListItem();
}

void CStoreMgrView::OnBnClickedBtnNextpage()
{
	// TODO: Add your control notification handler code here
	if (m_dwCurPage + 1 >= m_dwTotalNum)
	{
		return;
	}

	m_dwCurPage++;
	DisplayListItem();
}

void CStoreMgrView::OnBnClickedBtnBatchPrepage()
{
	// TODO: Add your control notification handler code here
	if (m_dwBatchCurPage <= 0)
	{
		return;
	}

	m_dwBatchCurPage--;
	DisplayBatchListItem(m_csSelectedMedicineSN.GetBuffer());
}

void CStoreMgrView::OnBnClickedBtnBatchNextpage()
{
	// TODO: Add your control notification handler code here
	if (m_dwBatchCurPage + 1 >= m_dwBatchTotalNum)
	{
		return;
	}

	m_dwBatchCurPage++;
	DisplayBatchListItem(m_csSelectedMedicineSN.GetBuffer());
}

void CStoreMgrView::OnBnClickedButtonEdit()
{
	// TODO: Add your control notification handler code here

	POSITION pos = m_listStore.GetFirstSelectedItemPosition();
	int iSelected = m_listStore.GetNextSelectedItem(pos);
	if (iSelected == -1)
	{
		return;
	}
	CString csID = m_listStore.GetItemText(iSelected, 0);
	CString csMedicineSN = m_listStore.GetItemText(iSelected, 1);

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}

	if (pDoc->m_pStoreEditViewContext != NULL)
	{
		delete pDoc->m_pStoreEditViewContext;
		pDoc->m_pStoreEditViewContext = NULL;
	}
	pDoc->m_pStoreEditViewContext = new STOREEDITVIEW_CONTEXT;
	pDoc->m_pStoreEditViewContext->medicineStore.csMedicineSN = csMedicineSN;

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_STORE_EDIT_ID;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}


void CStoreMgrView::OnBnClickedButtonDel()
{
	// TODO: Add your control notification handler code here

	ERRCODE errRet = err_OK;
	CString csMsg;

	POSITION pos = m_listStore.GetFirstSelectedItemPosition();
	int iSelected = m_listStore.GetNextSelectedItem(pos);
	if (iSelected == -1)
	{
		return;
	}

	CString csID = m_listStore.GetItemText(iSelected, 0);
	CString csMedicineSN = m_listStore.GetItemText(iSelected, 1);
	CString csMedicineName = m_listStore.GetItemText(iSelected, 2);

	csMsg.Format(_T("您确认删除药品'%s'的库存信息吗？"), csMedicineName);
	if (IDCANCEL == MessageBox(csMsg, _T("库存管理"), MB_ICONQUESTION|MB_OKCANCEL))
	{
		return;
	}

	CStoreDB storeDB;
	errRet = storeDB.DeleteMedicineStore(csMedicineSN.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("删除库存信息失败，%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("库存管理"), MB_ICONERROR);
		return;
	}

	m_listStore.DeleteItem(iSelected);

	DisplayListItem();
}

void CStoreMgrView::OnLvnItemchangedListStore(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	m_listBatchStore.DeleteAllItems();
	m_csSelectedMedicineSN = _T("");
	m_dwBatchCurPage = 0;
	m_dwBatchTotalNum = 0;
	m_dwBatchTotalPage = 0;

	int iTotalSelected = m_listStore.GetSelectedCount();
	POSITION pos = m_listStore.GetFirstSelectedItemPosition();
	int iSelected = m_listStore.GetNextSelectedItem(pos);
	if (iTotalSelected != 1 || iSelected == -1)
	{
		m_btnEdit.EnableWindow(FALSE);
		m_btnDel.EnableWindow(FALSE);

		m_staticBatchPageInfo.SetWindowText(_T("第0-0项，共0项"));
		m_btnBatchPrePage.EnableWindow(FALSE);
		m_btnBatchNextPage.EnableWindow(FALSE);
		return;
	}

	m_btnEdit.EnableWindow(TRUE);
	m_btnDel.EnableWindow(TRUE);

	m_csSelectedMedicineSN = m_listStore.GetItemText(iSelected, 1);
	DisplayBatchListItem(m_csSelectedMedicineSN.GetBuffer());
}

void CStoreMgrView::OnNMDblclkListStore(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int iSelected = pNMItemActivate->iItem;
	if (iSelected == -1)
	{
		return;
	}
	CString csID = m_listStore.GetItemText(iSelected, 0);
	CString csMedicineSN = m_listStore.GetItemText(iSelected, 1);

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}

	if (pDoc->m_pStoreEditViewContext != NULL)
	{
		delete pDoc->m_pStoreEditViewContext;
		pDoc->m_pStoreEditViewContext = NULL;
	}
	pDoc->m_pStoreEditViewContext = new STOREEDITVIEW_CONTEXT;
	pDoc->m_pStoreEditViewContext->medicineStore.csMedicineSN = csMedicineSN;

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_STORE_EDIT_ID;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}

void CStoreMgrView::OnNMDblclkListBatchStore(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	/*int iSelected = pNMItemActivate->iItem;
	if (iSelected == -1)
	{
		return;
	}
	CString csID = m_listBatchStore.GetItemText(iSelected, 0);
	CString csMedicineSN = m_listBatchStore.GetItemText(iSelected, 1);

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}

	if (pDoc->m_pStoreEditViewContext != NULL)
	{
		delete pDoc->m_pStoreEditViewContext;
		pDoc->m_pStoreEditViewContext = NULL;
	}
	pDoc->m_pStoreEditViewContext = new STOREEDITVIEW_CONTEXT;
	pDoc->m_pStoreEditViewContext->medicineStore.csMedicineSN = csMedicineSN;

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_STORE_EDIT_ID;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);*/
}

void CStoreMgrView::OnBnClickedButtonSearch()
{
	// TODO: Add your control notification handler code here

	if (IDOK != m_storeSearchDlg.DoModal())
	{
		return;
	}

	CString csMsg;
	if (m_storeSearchDlg.m_csMedicineSN == _T("") && m_storeSearchDlg.m_csMedicineName == _T("") && m_storeSearchDlg.m_csExpireDate == _T(""))
	{
		csMsg.Format(_T("库存列表 （全部）"));
	}
	else
	{
		csMsg.Format(_T("库存列表  （ "));
		if (m_storeSearchDlg.m_csMedicineSN != _T(""))
		{
			csMsg.AppendFormat(_T("药品编码：%s "), m_storeSearchDlg.m_csMedicineSN);
		}
		if (m_storeSearchDlg.m_csMedicineName != _T(""))
		{
			csMsg.AppendFormat(_T("药品名称：%s "), m_storeSearchDlg.m_csMedicineName);
		}
		if (m_storeSearchDlg.m_csExpireDate != _T(""))
		{
			csMsg.AppendFormat(_T("过期日期：%s "), m_storeSearchDlg.m_csExpireDate);
		}
		csMsg.AppendFormat(_T("）"));
	}
	SetDlgItemText(IDC_STATIC_GROUP_STORE, csMsg);

	m_dwCurPage = 0;
	DisplayListItem();
}


void CStoreMgrView::OnLvnItemchangedListStoreBatch(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int iTotalSelected = m_listBatchStore.GetSelectedCount();
	POSITION pos = m_listBatchStore.GetFirstSelectedItemPosition();
	int iSelected = m_listBatchStore.GetNextSelectedItem(pos);
	if (iTotalSelected != 1 || iSelected == -1)
	{
		//m_btnBatchEdit.EnableWindow(FALSE);
		//m_btnBatchDel.EnableWindow(FALSE);
		return;
	}

	//m_btnBatchEdit.EnableWindow(TRUE);
	//m_btnBatchDel.EnableWindow(TRUE);
}


void CStoreMgrView::OnBnClickedButtonStoreBatchEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_listBatchStore.GetFirstSelectedItemPosition();
	int iSelected = m_listBatchStore.GetNextSelectedItem(pos);
	if (iSelected == -1)
	{
		return;
	}
	CString csID = m_listBatchStore.GetItemText(iSelected, 0);
	CString csMedicineSN = m_listBatchStore.GetItemText(iSelected, 1);

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}

	if (pDoc->m_pStoreEditViewContext != NULL)
	{
		delete pDoc->m_pStoreEditViewContext;
		pDoc->m_pStoreEditViewContext = NULL;
	}
	pDoc->m_pStoreEditViewContext = new STOREEDITVIEW_CONTEXT;
	pDoc->m_pStoreEditViewContext->medicineStore.csMedicineSN = csMedicineSN;

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_STORE_EDIT_ID;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}


void CStoreMgrView::OnBnClickedButtonStoreBatchDel()
{
	// TODO: 在此添加控件通知处理程序代码
	ERRCODE errRet = err_OK;
	CString csMsg;

	POSITION pos = m_listBatchStore.GetFirstSelectedItemPosition();
	int iSelected = m_listBatchStore.GetNextSelectedItem(pos);
	if (iSelected == -1)
	{
		return;
	}

	CString csID = m_listBatchStore.GetItemText(iSelected, 0);
	CString csMedicineBatch = m_listBatchStore.GetItemText(iSelected, 1);

	csMsg.Format(_T("您确认删除该批次：'%s'的库存信息吗？"), csMedicineBatch);
	if (IDCANCEL == MessageBox(csMsg, _T("库存管理"), MB_ICONQUESTION|MB_OKCANCEL))
	{
		return;
	}

	CStoreDB storeDB;
	errRet = storeDB.DeleteMedicineBatchStore(csID.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("删除库存信息失败，%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("库存管理"), MB_ICONERROR);
		return;
	}

	m_listBatchStore.DeleteItem(iSelected);

	//DisplayListItem();
}

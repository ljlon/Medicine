// VendorMgrView.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "VendorMgrView.h"
#include "mainfrm.h"
#include "VendorDB.h"

// CVendorMgrView

IMPLEMENT_DYNCREATE(CVendorMgrView, CFormView)

CVendorMgrView::CVendorMgrView()
	: CFormView(CVendorMgrView::IDD)
{
	m_dwCurPage = 0;
	m_dwTotalPage = 0;
	m_dwTotalNum = 0;
}

CVendorMgrView::~CVendorMgrView()
{
}

void CVendorMgrView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VENDOR, m_listVendor);
	DDX_Control(pDX, IDC_STATIC_PAGE, m_staticPageInfo);
	DDX_Control(pDX, IDC_BTN_PREPAGE, m_btnPrePage);
	DDX_Control(pDX, IDC_BTN_NEXTPAGE, m_btnNextPage);
	DDX_Control(pDX, IDC_BUTTON_VENDOR_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_BUTTON_VENDOR_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BUTTON_VENDOR_DEL, m_btnDel);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_btnSearch);
}

BEGIN_MESSAGE_MAP(CVendorMgrView, CFormView)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_VENDOR, &CVendorMgrView::OnLvnItemchangedListVendor)
	ON_BN_CLICKED(IDC_BUTTON_VENDOR_ADD, &CVendorMgrView::OnBnClickedButtonVendorAdd)
	ON_BN_CLICKED(IDC_BUTTON_VENDOR_EDIT, &CVendorMgrView::OnBnClickedButtonVendorEdit)
	ON_BN_CLICKED(IDC_BUTTON_VENDOR_DEL, &CVendorMgrView::OnBnClickedButtonVendorDel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_VENDOR, &CVendorMgrView::OnNMDblclkListVendor)
	ON_BN_CLICKED(IDC_BTN_PREPAGE, &CVendorMgrView::OnBnClickedBtnPrepage)
	ON_BN_CLICKED(IDC_BTN_NEXTPAGE, &CVendorMgrView::OnBnClickedBtnNextpage)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CVendorMgrView::OnBnClickedButtonSearch)
END_MESSAGE_MAP()

void CVendorMgrView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CString csMsg;
	csMsg.Format("%s-%s", APP_NAME, APP_MANAGER);
	AfxGetApp()->GetMainWnd()->SetWindowText(csMsg);

	CRect rectClient;
	GetClientRect(rectClient);

	m_listVendor.SetExtendedStyle(LVS_EX_FLATSB    // 扁平风格滚动
		| LVS_EX_FULLROWSELECT    // 允许整行选中
		| LVS_EX_HEADERDRAGDROP    // 允许标题拖拽
		| LVS_EX_GRIDLINES    // 画出网格线
		);
	m_listVendor.InsertColumn(0, "编号", LVCFMT_LEFT, 0, 0);
	m_listVendor.InsertColumn(1, "名称", LVCFMT_LEFT, 150, 0);
	m_listVendor.InsertColumn(3, "电话", LVCFMT_LEFT, 150, 0);
	m_listVendor.InsertColumn(4, "地址", LVCFMT_LEFT, 150, 0);
	m_listVendor.InsertColumn(5, "药品数量", LVCFMT_LEFT, 150, 0);
	m_listVendor.InsertColumn(6, "创建时间", LVCFMT_LEFT, 150, 0);
	m_listVendor.InsertColumn(7, "修改时间", LVCFMT_LEFT, 150, 0);

	DisplayListItem();

	m_btnAdd.SetFocus();
}

void CVendorMgrView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CVendorMgrView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	int iWidth = 0, iHeight = 0;
	CRect clientRect;
	GetClientRect(clientRect);

	CRect nextBtnRect;
	CButton *pBtnNextPage = (CButton*)GetDlgItem(IDC_BTN_NEXTPAGE);
	if (pBtnNextPage->GetSafeHwnd() != NULL)
	{
		pBtnNextPage->GetClientRect(nextBtnRect);
		iWidth = nextBtnRect.Width();
		iHeight = nextBtnRect.Height();
		nextBtnRect.right = clientRect.Width() - 7;
		nextBtnRect.left = nextBtnRect.right - iWidth;
		nextBtnRect.top = clientRect.top + 15;
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
		preBtnRect.top = clientRect.top + 15;
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
		pageInfoRect.top = clientRect.top + 20;
		pageInfoRect.bottom =  pageInfoRect.top + iHeight;
		pStaticPageInfo->SetWindowPos(NULL, pageInfoRect.left, pageInfoRect.top, pageInfoRect.Width(),  pageInfoRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CListCtrl *pVendorList = (CListCtrl*)GetDlgItem(IDC_LIST_VENDOR);
	if (pVendorList->GetSafeHwnd() != NULL)
	{
		pVendorList->SetWindowPos(NULL, clientRect.left + 5, clientRect.top + 50, clientRect.Width() - 10, clientRect.Height() - 55, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void CVendorMgrView::DisplayListItem()
{
	CString csMsg, csName;
	CVendorDB vendorDB;
	vector<Vendor*> vctVendors;
	csName.Format(_T("%s"), m_searchDlg.m_csName);

	ERRCODE errRet = vendorDB.GetVendors(m_dwCurPage, g_ciNumPerPage, m_dwTotalPage, m_dwTotalNum, vctVendors, csName.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取生产厂家信息失败！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("生产厂家管理"), MB_ICONERROR);
		return;
	}

	csMsg.Format(_T("第%d-%d项，共%d项"), m_dwTotalNum>0?m_dwCurPage * g_ciNumPerPage + 1:0, m_dwCurPage * g_ciNumPerPage +  vctVendors.size(), m_dwTotalNum);
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

	m_listVendor.DeleteAllItems();
	for (unsigned int i = 0; i < vctVendors.size(); i++)
	{
		m_listVendor.InsertItem(i, vctVendors[i]->csID);
		m_listVendor.SetItemText(i, 1, vctVendors[i]->csName);
		m_listVendor.SetItemText(i, 2, vctVendors[i]->csTelephone);
		m_listVendor.SetItemText(i,3, vctVendors[i]->csAddress);
		m_listVendor.SetItemText(i,4, vctVendors[i]->csMedicineCount);
		m_listVendor.SetItemText(i,5, vctVendors[i]->csCreateTime);
		m_listVendor.SetItemText(i,6, vctVendors[i]->csModifyTime);

		delete vctVendors[i];
		vctVendors[i] = NULL;
	}
	vctVendors.clear();
}

// CVendorMgrView diagnostics

#ifdef _DEBUG
void CVendorMgrView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CVendorMgrView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CVendorMgrView message handlers


void CVendorMgrView::OnLvnItemchangedListVendor(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int iTotalSelected = m_listVendor.GetSelectedCount();
	POSITION pos = m_listVendor.GetFirstSelectedItemPosition();
	int iSelected = m_listVendor.GetNextSelectedItem(pos);
	if (iTotalSelected != 1 || iSelected == -1)
	{
		m_btnEdit.EnableWindow(FALSE);
		m_btnDel.EnableWindow(FALSE);
		return;
	}

	m_btnEdit.EnableWindow(TRUE);
	m_btnDel.EnableWindow(TRUE);
}


void CVendorMgrView::OnBnClickedButtonVendorAdd()
{
	// TODO: Add your control notification handler code here

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}
	pDoc->m_viewType = VIEW_NEW;
	pDoc->m_csVendorID = _T("");

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_VENDOR_ADD;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}


void CVendorMgrView::OnBnClickedButtonVendorEdit()
{
	// TODO: Add your control notification handler code here
	
	CString csMsg;

	POSITION pos = m_listVendor.GetFirstSelectedItemPosition();
	int iSelected = m_listVendor.GetNextSelectedItem(pos);
	if (iSelected == -1)
	{
		return;
	}
	CString csID = m_listVendor.GetItemText(iSelected, 0);

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}
	pDoc->m_viewType = VIEW_EDIT;
	pDoc->m_csVendorID = csID;

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_VENDOR_ADD;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}


void CVendorMgrView::OnBnClickedButtonVendorDel()
{
	// TODO: Add your control notification handler code here

	ERRCODE errRet = err_OK;
	CString csMsg;

	POSITION pos = m_listVendor.GetFirstSelectedItemPosition();
	int iSelected = m_listVendor.GetNextSelectedItem(pos);
	if (iSelected == -1)
	{
		return;
	}

	CString csID = m_listVendor.GetItemText(iSelected, 0);
	CString csName = m_listVendor.GetItemText(iSelected, 1);

	CMedicineDB medicineDB;
	vector<Medicine*> vctMedicines;
	errRet = medicineDB.GetMedicines(0, 1000, m_dwTotalPage, m_dwTotalNum, vctMedicines, NULL, NULL, csID.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("删除供应商失败，%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("供应商管理"), MB_ICONERROR);
		return;
	}
	if (vctMedicines.size())
	{
		for (unsigned int i = 0; i < vctMedicines.size(); i++)
		{
			if (vctMedicines[i]  != NULL)
			{
				delete vctMedicines[i];
				vctMedicines[i] = NULL;
			}
		}
		vctMedicines.clear();

		csMsg.Format(_T("需要先删除该生产厂家的所有药品信息，才能删除该生产厂家！"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("供应商管理"), MB_ICONINFORMATION);
		return;
	}

	csMsg.Format(_T("您确认删除生产厂家'%s'吗？"), csName);
	if (IDCANCEL == MessageBox(csMsg, _T("生产厂家管理"), MB_ICONQUESTION|MB_OKCANCEL))
	{
		return;
	}

	CVendorDB vendorDB;
	errRet = vendorDB.DeleteVendor(csID.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("删除生产厂家失败，%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("生产厂家管理"), MB_ICONERROR);
		return;
	}

	m_listVendor.DeleteItem(iSelected);
}


void CVendorMgrView::OnNMDblclkListVendor(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	OnBnClickedButtonVendorEdit();

	*pResult = 0;
}

void CVendorMgrView::OnBnClickedBtnPrepage()
{
	// TODO: Add your control notification handler code here
	if (m_dwCurPage <= 0)
	{
		return;
	}

	m_dwCurPage--;
	DisplayListItem();
}

void CVendorMgrView::OnBnClickedBtnNextpage()
{
	// TODO: Add your control notification handler code here
	if (m_dwCurPage + 1 >= m_dwTotalNum)
	{
		return;
	}

	m_dwCurPage++;
	DisplayListItem();
}

void CVendorMgrView::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IDOK != m_searchDlg.DoModal())
	{
		return;
	}

	m_dwCurPage = 0;
	DisplayListItem();
}

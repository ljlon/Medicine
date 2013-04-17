// SupplierMgrView.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "SupplierMgrView.h"
#include "mainfrm.h"
#include "SupplierDB.h"

// CSupplierMgrView

IMPLEMENT_DYNCREATE(CSupplierMgrView, CFormView)

CSupplierMgrView::CSupplierMgrView()
	: CFormView(CSupplierMgrView::IDD)
{
	m_dwCurPage = 0;
	m_dwTotalPage = 0;
	m_dwTotalNum = 0;
}

CSupplierMgrView::~CSupplierMgrView()
{
}

void CSupplierMgrView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SUPPLIER, m_listSupplier);
	DDX_Control(pDX, IDC_STATIC_PAGE, m_staticPageInfo);
	DDX_Control(pDX, IDC_BTN_PREPAGE, m_btnPrePage);
	DDX_Control(pDX, IDC_BTN_NEXTPAGE, m_btnNextPage);
	DDX_Control(pDX, IDC_BUTTON_SUPPLIER_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_BUTTON_SUPPLIER_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BUTTON_SUPPLIER_DEL, m_btnDel);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_btnSearch);
}

BEGIN_MESSAGE_MAP(CSupplierMgrView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_SUPPLIER_ADD, &CSupplierMgrView::OnBnClickedButtonSupplierAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUPPLIER_EDIT, &CSupplierMgrView::OnBnClickedButtonSupplierEdit)
	ON_BN_CLICKED(IDC_BUTTON_SUPPLIER_DEL, &CSupplierMgrView::OnBnClickedButtonSupplierDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SUPPLIER, &CSupplierMgrView::OnLvnItemchangedListSupplier)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SUPPLIER, &CSupplierMgrView::OnNMDblclkListSupplier)
	ON_BN_CLICKED(IDC_BTN_PREPAGE, &CSupplierMgrView::OnBnClickedBtnPrepage)
	ON_BN_CLICKED(IDC_BTN_NEXTPAGE, &CSupplierMgrView::OnBnClickedBtnNextpage)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CSupplierMgrView::OnBnClickedButtonSearch)
END_MESSAGE_MAP()

void CSupplierMgrView::OnInitialUpdate()
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

	CRect rectClient;
	GetClientRect(rectClient);

	m_listSupplier.SetExtendedStyle(LVS_EX_FLATSB    // 扁平风格滚动
		| LVS_EX_FULLROWSELECT    // 允许整行选中
		| LVS_EX_HEADERDRAGDROP    // 允许标题拖拽
		| LVS_EX_GRIDLINES    // 画出网格线
		);
	m_listSupplier.InsertColumn(0, "编号", LVCFMT_LEFT, 0, 0);
	m_listSupplier.InsertColumn(1, "名称", LVCFMT_LEFT, 150, 0);
	m_listSupplier.InsertColumn(2, "联系人", LVCFMT_LEFT, 150, 0);
	m_listSupplier.InsertColumn(3, "电话", LVCFMT_LEFT, 150, 0);
	m_listSupplier.InsertColumn(4, "地址", LVCFMT_LEFT, 150, 0);
	m_listSupplier.InsertColumn(5, "药品数量", LVCFMT_LEFT, 150, 0);
	m_listSupplier.InsertColumn(6, "创建时间", LVCFMT_LEFT, 150, 0);
	m_listSupplier.InsertColumn(7, "修改时间", LVCFMT_LEFT, 150, 0);

	DisplayListItem();

	m_btnAdd.SetFocus();
}

void CSupplierMgrView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CSupplierMgrView::AdjustLayout()
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

	CListCtrl *pSupplierList = (CListCtrl*)GetDlgItem(IDC_LIST_SUPPLIER);
	if (pSupplierList->GetSafeHwnd() != NULL)
	{
		pSupplierList->SetWindowPos(NULL, clientRect.left + 5, clientRect.top + 60, clientRect.Width() - 10, clientRect.Height() - 55, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void CSupplierMgrView::DisplayListItem()
{
	CString csMsg, csName;
	CSupplierDB supplierDB;
	vector<Supplier*> vctSuppliers;
	csName.Format(_T("%s"), m_searchDlg.m_csName);

	ERRCODE errRet = supplierDB.GetSuppliers(m_dwCurPage, g_ciNumPerPage, m_dwTotalPage, m_dwTotalNum, vctSuppliers, csName.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取供应商信息失败！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("供应商管理"), MB_ICONERROR);
		return;
	}

	csMsg.Format(_T("第%d-%d项，共%d项"), m_dwTotalNum>0?m_dwCurPage * g_ciNumPerPage + 1:0, m_dwCurPage * g_ciNumPerPage +  vctSuppliers.size(), m_dwTotalNum);
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

	m_listSupplier.DeleteAllItems();
	for (unsigned int i = 0; i < vctSuppliers.size(); i++)
	{
		m_listSupplier.InsertItem(i, vctSuppliers[i]->csID);
		m_listSupplier.SetItemText(i, 1, vctSuppliers[i]->csName);
		m_listSupplier.SetItemText(i, 2, vctSuppliers[i]->csContact);
		m_listSupplier.SetItemText(i, 3, vctSuppliers[i]->csTelephone);
		m_listSupplier.SetItemText(i, 4, vctSuppliers[i]->csAddress);
		m_listSupplier.SetItemText(i, 5, vctSuppliers[i]->csMedicineCount);
		m_listSupplier.SetItemText(i, 6, vctSuppliers[i]->csCreateTime);
		m_listSupplier.SetItemText(i, 7, vctSuppliers[i]->csModifyTime);

		delete vctSuppliers[i];
		vctSuppliers[i] = NULL;
	}
	vctSuppliers.clear();
}

// CSupplierMgrView diagnostics

#ifdef _DEBUG
void CSupplierMgrView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSupplierMgrView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSupplierMgrView message handlers


void CSupplierMgrView::OnBnClickedButtonSupplierAdd()
{
	// TODO: 在此添加控件通知处理程序代码

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}
	pDoc->m_viewType = VIEW_NEW;
	pDoc->m_csSupplierID = _T("");

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_SUPPLIER_ADD;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}


void CSupplierMgrView::OnBnClickedButtonSupplierEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csMsg;

	POSITION pos = m_listSupplier.GetFirstSelectedItemPosition();
	int iSelected = m_listSupplier.GetNextSelectedItem(pos);
	if (iSelected == -1)
	{
		return;
	}
	CString csID = m_listSupplier.GetItemText(iSelected, 0);

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}
	pDoc->m_viewType = VIEW_EDIT;
	pDoc->m_csSupplierID = csID;

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_SUPPLIER_ADD;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}


void CSupplierMgrView::OnBnClickedButtonSupplierDel()
{
	// TODO: 在此添加控件通知处理程序代码
	ERRCODE errRet = err_OK;
	CString csMsg;

	POSITION pos = m_listSupplier.GetFirstSelectedItemPosition();
	int iSelected = m_listSupplier.GetNextSelectedItem(pos);
	if (iSelected == -1)
	{
		return;
	}

	CString csID = m_listSupplier.GetItemText(iSelected, 0);
	CString csName = m_listSupplier.GetItemText(iSelected, 1);
	csMsg.Format(_T("您确认删除供应商'%s'吗？"), csName);
	if (IDCANCEL == MessageBox(csMsg, _T("供应商管理"), MB_ICONQUESTION|MB_OKCANCEL))
	{
		return;
	}

	CSupplierMedicineDB supplierMedicineDB;
	vector<SupplierMedicine*> vctSupplierMedicines;
	errRet = supplierMedicineDB.GetSupplierMedicines(0, 1000, m_dwTotalPage, m_dwTotalNum, vctSupplierMedicines, csID.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("删除供应商失败，%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("供应商管理"), MB_ICONERROR);
		return;
	}
	/*if (vctSupplierMedicines.size())
	{
		for (unsigned int i = 0; i < vctSupplierMedicines.size(); i++)
		{
			if (vctSupplierMedicines[i]  != NULL)
			{
				delete vctSupplierMedicines[i];
				vctSupplierMedicines[i] = NULL;
			}
		}
		vctSupplierMedicines.clear();

		csMsg.Format(_T("需要先删除该供应商的所有药品信息，才能删除该供应商！"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("供应商管理"), MB_ICONINFORMATION);
		return;
	}*/
	for (unsigned int j = 0; j < vctSupplierMedicines.size(); j++)
	{
		if (vctSupplierMedicines[j]  != NULL)
		{
			delete vctSupplierMedicines[j];
			vctSupplierMedicines[j] = NULL;
		}
	}
	vctSupplierMedicines.clear();

	errRet = supplierMedicineDB.DeleteSupplierMedicinesBySID(csID.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("删除药品失败，%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return;
	}

	CSupplierDB supplierDB;
	errRet = supplierDB.DeleteSupplier(csID.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("删除供应商失败，%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("供应商管理"), MB_ICONERROR);
		return;
	}

	m_listSupplier.DeleteItem(iSelected);
}


void CSupplierMgrView::OnLvnItemchangedListSupplier(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int iTotalSelected = m_listSupplier.GetSelectedCount();
	POSITION pos = m_listSupplier.GetFirstSelectedItemPosition();
	int iSelected = m_listSupplier.GetNextSelectedItem(pos);
	if (iTotalSelected != 1 || iSelected == -1)
	{
		m_btnEdit.EnableWindow(FALSE);
		m_btnDel.EnableWindow(FALSE);
		return;
	}

	m_btnEdit.EnableWindow(TRUE);
	m_btnDel.EnableWindow(TRUE);
}


void CSupplierMgrView::OnNMDblclkListSupplier(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	OnBnClickedButtonSupplierEdit();

	*pResult = 0;
}

void CSupplierMgrView::OnBnClickedBtnPrepage()
{
	// TODO: Add your control notification handler code here
	if (m_dwCurPage <= 0)
	{
		return;
	}

	m_dwCurPage--;
	DisplayListItem();
}

void CSupplierMgrView::OnBnClickedBtnNextpage()
{
	// TODO: Add your control notification handler code here
	if (m_dwCurPage + 1 >= m_dwTotalNum)
	{
		return;
	}

	m_dwCurPage++;
	DisplayListItem();
}

void CSupplierMgrView::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IDOK != m_searchDlg.DoModal())
	{
		return;
	}

	m_dwCurPage = 0;
	DisplayListItem();
}
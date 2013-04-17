// PurchaseListView.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "PurchaseListView.h"
#include "Mainfrm.h"
#include "PurchaseDB.h"

// CPurchaseListView

IMPLEMENT_DYNCREATE(CPurchaseListView, CFormView)

CPurchaseListView::CPurchaseListView()
	: CFormView(CPurchaseListView::IDD)
{
	m_dwCurPage = 0;
	m_dwTotalPage = 0;
	m_dwTotalNum = 0;
	m_dbTotalPrice = 0;
}

CPurchaseListView::~CPurchaseListView()
{
}

void CPurchaseListView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PUR, m_listPur);
	DDX_Control(pDX, IDC_STATIC_PAGE, m_staticPageInfo);
	DDX_Control(pDX, IDC_BTN_PREPAGE, m_btnPrePage);
	DDX_Control(pDX, IDC_BTN_NEXTPAGE, m_btnNextPage);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btnAdd);
	//DDX_Control(pDX, IDC_BUTTON_DEL, m_btnDel);
	DDX_Control(pDX, IDC_STATIC_GROUP_PUR, m_staticGroupPur);
}

BEGIN_MESSAGE_MAP(CPurchaseListView, CFormView)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PUR, &CPurchaseListView::OnLvnItemchangedListPur)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CPurchaseListView::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CPurchaseListView::OnBnClickedButtonEdit)
	//ON_BN_CLICKED(IDC_BUTTON_DEL, &CPurchaseListView::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BTN_PREPAGE, &CPurchaseListView::OnBnClickedBtnPrepage)
	ON_BN_CLICKED(IDC_BTN_NEXTPAGE, &CPurchaseListView::OnBnClickedBtnNextpage)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CPurchaseListView::OnBnClickedButtonSearch)
END_MESSAGE_MAP()

void CPurchaseListView::OnInitialUpdate()
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

	m_listPur.SetExtendedStyle(LVS_EX_FLATSB    // 扁平风格滚动
		| LVS_EX_FULLROWSELECT    // 允许整行选中
		| LVS_EX_HEADERDRAGDROP    // 允许标题拖拽
		| LVS_EX_GRIDLINES    // 画出网格线
		);
	m_listPur.InsertColumn(0, "编号", LVCFMT_LEFT, 0, 0);
	m_listPur.InsertColumn(1, "进货人员", LVCFMT_LEFT, 80, 0);
	m_listPur.InsertColumn(2, "药品编码", LVCFMT_LEFT, 120, 0);
	m_listPur.InsertColumn(3, "药品名称", LVCFMT_LEFT, 150, 0);
	m_listPur.InsertColumn(4, "药品规格", LVCFMT_LEFT, 80, 0);
	m_listPur.InsertColumn(5, "生产厂家", LVCFMT_LEFT, 80, 0);
	m_listPur.InsertColumn(6, "批号", LVCFMT_LEFT, 80, 0);
	m_listPur.InsertColumn(7, "生产日期", LVCFMT_LEFT, 80, 0);
	m_listPur.InsertColumn(8, "有效期至", LVCFMT_LEFT, 80, 0);
	m_listPur.InsertColumn(9, "进价", LVCFMT_LEFT, 60, 0);
	m_listPur.InsertColumn(10, "数量", LVCFMT_LEFT, 60, 0);
	m_listPur.InsertColumn(11, "单位", LVCFMT_LEFT, 40, 0);
	m_listPur.InsertColumn(12, "金额", LVCFMT_LEFT, 80, 0);
	m_listPur.InsertColumn(13, "进货时间", LVCFMT_LEFT, 80, 0);
	//m_listPur.InsertColumn(12, "修改时间", LVCFMT_LEFT, 120, 0);

	DisplayListItem();
}

void CPurchaseListView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPurchaseListView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	int iWidth = 0, iHeight = 0;
	CRect clientRect;
	GetClientRect(clientRect);

	CRect groupPurRect;
	CStatic *pGroupPur = (CStatic*)GetDlgItem(IDC_STATIC_GROUP_PUR);
	if (pGroupPur->GetSafeHwnd() != NULL)
	{
		groupPurRect.left = clientRect.left + 5;
		groupPurRect.top = clientRect.top + 50;
		groupPurRect.right = groupPurRect.left + (clientRect.Width() - 10);
		groupPurRect.bottom = clientRect.bottom - 5;
		pGroupPur->SetWindowPos(NULL, groupPurRect.left, groupPurRect.top, groupPurRect.Width(), groupPurRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect purListRect;
	CListCtrl *pPurList = (CListCtrl*)GetDlgItem(IDC_LIST_PUR);
	if (pPurList->GetSafeHwnd() != NULL)
	{
		purListRect.left = groupPurRect.left;
		purListRect.top = groupPurRect.top + 60;
		purListRect.right = purListRect.left + (clientRect.Width() - 10);
		purListRect.bottom = clientRect.bottom - 5;
		pPurList->SetWindowPos(NULL, purListRect.left, purListRect.top, purListRect.Width(), purListRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
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
		nextBtnRect.top = groupPurRect.top + 20;
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
		pageInfoRect.top = groupPurRect.top + 25;
		pageInfoRect.bottom =  pageInfoRect.top + iHeight;
		pStaticPageInfo->SetWindowPos(NULL, pageInfoRect.left, pageInfoRect.top, pageInfoRect.Width(),  pageInfoRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void CPurchaseListView::DisplayListItem()
{
	CString csMsg;
	CPurchaseDB purchaseDB;
	CMedicineDB medicineDB;
	vector<Purchase*> vctPurchases;
	vector<MedicineUtil*> vctMedicineUnit;

	ERRCODE errRet = purchaseDB.GetPurchases(m_dwCurPage, 
																		g_ciNumPerPage, 
																		m_dwTotalPage, 
																		m_dwTotalNum, 
																		m_dbTotalPrice, 
																		vctPurchases,
																		m_purchaseSearchDlg.m_csPurBeginDate.GetBuffer(),
																		m_purchaseSearchDlg.m_csPurEndDate.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取进货信息失败！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("进货清单"), MB_ICONERROR);
		return;
	}

	csMsg.Format(_T("第%d-%d项，共%d项"), m_dwTotalNum>0?m_dwCurPage * g_ciNumPerPage + 1:0, m_dwCurPage * g_ciNumPerPage +  vctPurchases.size(), m_dwTotalNum);
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

	csMsg.Format(_T("进货列表 （合计：%0.2f元）"), m_dbTotalPrice);
	if (m_purchaseSearchDlg.m_csPurBeginDate != _T("") && m_purchaseSearchDlg.m_csPurEndDate != _T(""))
	{
		csMsg.AppendFormat(_T(" （ 进货日期：%s至%s ）"), m_purchaseSearchDlg.m_csPurBeginDate, m_purchaseSearchDlg.m_csPurEndDate);
	}

	m_staticGroupPur.SetWindowText(csMsg);

	errRet = medicineDB.GetMedicineUnits(vctMedicineUnit);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取药品信息错误！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("进货清单"), MB_ICONERROR);
		return;
	}
	m_listPur.DeleteAllItems();
	for (unsigned int i = 0; i < vctPurchases.size(); i++)
	{
		m_listPur.InsertItem(i, vctPurchases[i]->csID);
		csMsg.Format(_T("%s-%s"), vctPurchases[i]->csUserUID, vctPurchases[i]->csUserName);
		m_listPur.SetItemText(i, 1, csMsg);
		m_listPur.SetItemText(i, 2, vctPurchases[i]->csMedicineSN);
		m_listPur.SetItemText(i,3, vctPurchases[i]->csMedicineName);
		m_listPur.SetItemText(i,4, vctPurchases[i]->csMedicineSpec);
		m_listPur.SetItemText(i,5, vctPurchases[i]->csMedicineVendorName);
		m_listPur.SetItemText(i,6, vctPurchases[i]->csBatchNum);
		m_listPur.SetItemText(i,7, vctPurchases[i]->csProductDate);
		m_listPur.SetItemText(i,8, vctPurchases[i]->csExpireDate);
		csMsg.Format(_T("%0.2f"), atof(vctPurchases[i]->csPurPrice));
		m_listPur.SetItemText(i,9, csMsg);
		m_listPur.SetItemText(i,10, vctPurchases[i]->csNumber);
		m_listPur.SetItemText(i,11, vctPurchases[i]->csMedicineUnit);
		csMsg.Format(_T("%0.2f"), atof(vctPurchases[i]->csPurPrice.GetBuffer()) * atol(vctPurchases[i]->csNumber.GetBuffer()));
		m_listPur.SetItemText(i,12, csMsg);
		m_listPur.SetItemText(i,13, vctPurchases[i]->csCreateTime);
		//m_listPur.SetItemText(i,12, vctPurchases[i]->csModifyTime);

		delete vctPurchases[i];
		vctPurchases[i] = NULL;
	}
	vctPurchases.clear();

	for (unsigned int i = 0; i < vctMedicineUnit.size(); i++)
	{
		delete vctMedicineUnit[i];
		vctMedicineUnit[i] = NULL;
	}
	vctMedicineUnit.clear();
}

// CVendorMgrView diagnostics

#ifdef _DEBUG
void CPurchaseListView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPurchaseListView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CPurchaseListView 消息处理程序

void CPurchaseListView::OnLvnItemchangedListPur(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int iTotalSelected = m_listPur.GetSelectedCount();
	POSITION pos = m_listPur.GetFirstSelectedItemPosition();
	int iSelected = m_listPur.GetNextSelectedItem(pos);
	if (iTotalSelected != 1 || iSelected == -1)
	{
		//m_btnDel.EnableWindow(FALSE);
		return;
	}

	//m_btnDel.EnableWindow(TRUE);
}

void CPurchaseListView::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_PURCHASE_ADD;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}

void CPurchaseListView::OnBnClickedBtnPrepage()
{
	// TODO: Add your control notification handler code here
	if (m_dwCurPage <= 0)
	{
		return;
	}

	m_dwCurPage--;
	DisplayListItem();
}

void CPurchaseListView::OnBnClickedBtnNextpage()
{
	// TODO: Add your control notification handler code here
	if (m_dwCurPage + 1 >= m_dwTotalNum)
	{
		return;
	}

	m_dwCurPage++;
	DisplayListItem();
}

void CPurchaseListView::OnBnClickedButtonEdit()
{
	// TODO: Add your control notification handler code here
}

void CPurchaseListView::OnBnClickedButtonDel()
{
	// TODO: Add your control notification handler code here

	ERRCODE errRet = err_OK;
	CString csMsg, csTotalPrice;

	POSITION pos = m_listPur.GetFirstSelectedItemPosition();
	int iSelected = m_listPur.GetNextSelectedItem(pos);
	if (iSelected == -1)
	{
		return;
	}

	CString csID = m_listPur.GetItemText(iSelected, 0);

	csMsg.Format(_T("您确认删除订单'%s'吗？"), csID);
	if (IDCANCEL == MessageBox(csMsg, _T("进货管理"), MB_ICONQUESTION|MB_OKCANCEL))
	{
		return;
	}

	CPurchaseDB purchaseDB;
	Purchase purchase;
	errRet = purchaseDB.GetPurchase(csID.GetBuffer(), &purchase);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("删除订单失败，%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("进货管理"), MB_ICONERROR);
		return;
	}

	errRet = purchaseDB.DeletePurchase(csID.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("删除订单失败，%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("进货管理"), MB_ICONERROR);
		return;
	}
	m_listPur.DeleteItem(iSelected);
}

void CPurchaseListView::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码

	if (IDOK != m_purchaseSearchDlg.DoModal())
	{
		return;
	}

	m_dwCurPage = 0;
	DisplayListItem();
}

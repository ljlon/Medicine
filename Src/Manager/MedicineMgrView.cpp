// MedicineView.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "MedicineMgrView.h"
#include "Mainfrm.h"
#include "SupplierMedicineDB.h"
#include "MedicineBatchDB.h"
#include "StoreDB.h"
#include "MedicineImport.h"

// CMedicineView

IMPLEMENT_DYNCREATE(CMedicineMgrView, CFormView)

CMedicineMgrView::CMedicineMgrView()
	: CFormView(CMedicineMgrView::IDD)
{
	m_dwCurPage = 0;
	m_dwTotalPage = 0;
	m_dwTotalNum = 0;
}

CMedicineMgrView::~CMedicineMgrView()
{

}

void CMedicineMgrView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PAGE, m_staticPageInfo);
	DDX_Control(pDX, IDC_BTN_PREPAGE, m_btnPrePage);
	DDX_Control(pDX, IDC_BTN_NEXTPAGE, m_btnNextPage);
	DDX_Control(pDX, IDC_LIST_MEDICINE, m_listMedicine);
	DDX_Control(pDX, IDC_BUTTON_MEDICINE_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_BUTTON_MEDICINE_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BUTTON_MEDICINE_DEL, m_btnDel);
	DDX_Control(pDX, IDC_BUTTON_IMPORT, m_btnImport);
}

BEGIN_MESSAGE_MAP(CMedicineMgrView, CFormView)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MEDICINE, &CMedicineMgrView::OnLvnItemchangedListMedicine)
	ON_BN_CLICKED(IDC_BUTTON_MEDICINE_ADD, &CMedicineMgrView::OnBnClickedButtonMedicineAdd)
	ON_BN_CLICKED(IDC_BUTTON_MEDICINE_EDIT, &CMedicineMgrView::OnBnClickedButtonMedicineEdit)
	ON_BN_CLICKED(IDC_BUTTON_MEDICINE_DEL, &CMedicineMgrView::OnBnClickedButtonMedicineDel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MEDICINE, &CMedicineMgrView::OnNMDblclkListMedicine)
	ON_BN_CLICKED(IDC_BTN_PREPAGE, &CMedicineMgrView::OnBnClickedBtnPrepage)
	ON_BN_CLICKED(IDC_BTN_NEXTPAGE, &CMedicineMgrView::OnBnClickedBtnNextpage)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CMedicineMgrView::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CMedicineMgrView::OnBnClickedButtonImport)
END_MESSAGE_MAP()

void CMedicineMgrView::OnInitialUpdate()
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

	if(atol(theApp.m_curUser.csRole.GetBuffer()) == Role_Supper)
	{
		m_btnImport.ShowWindow(SW_SHOW);
	}
	else
	{
		m_btnImport.ShowWindow(SW_HIDE);
	}

	m_listMedicine.SetExtendedStyle(LVS_EX_FLATSB    // 扁平风格滚动
		| LVS_EX_FULLROWSELECT    // 允许整行选中
		| LVS_EX_HEADERDRAGDROP    // 允许标题拖拽
		| LVS_EX_GRIDLINES    // 画出网格线
		);
	m_listMedicine.InsertColumn(0, "编号", LVCFMT_LEFT, 0, 0);
	m_listMedicine.InsertColumn(1, "编码", LVCFMT_LEFT, 120, 0);
	m_listMedicine.InsertColumn(2, "名称", LVCFMT_LEFT, 150, 0);
	m_listMedicine.InsertColumn(3, "规格", LVCFMT_LEFT, 90, 0);
	m_listMedicine.InsertColumn(4, "生产厂家", LVCFMT_LEFT, 90, 0);
	m_listMedicine.InsertColumn(5, "零售价", LVCFMT_LEFT, 60, 0);
	m_listMedicine.InsertColumn(6, "单位", LVCFMT_LEFT, 40, 0);
	m_listMedicine.InsertColumn(7, "供应商数量", LVCFMT_LEFT, 60, 0);
	m_listMedicine.InsertColumn(8, "创建时间", LVCFMT_LEFT, 90, 0);
	m_listMedicine.InsertColumn(9, "修改时间", LVCFMT_LEFT, 90, 0);
	
	DisplayListItem();

	m_btnAdd.SetFocus();
}

void CMedicineMgrView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CMedicineMgrView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	int iWidth = 0, iHeight = 0;
	CRect clientRect, tempRect;
	GetClientRect(clientRect);

	CRect groupListRect;
	CStatic *pGroupList = (CStatic*)GetDlgItem(IDC_STATIC_GROUP_LIST);
	if (pGroupList->GetSafeHwnd() != NULL)
	{
		groupListRect.left = clientRect.left + 5;
		groupListRect.top = clientRect.top + 60;
		groupListRect.right = groupListRect.left + (clientRect.Width() - 10);
		groupListRect.bottom = clientRect.bottom - 5;
		pGroupList->SetWindowPos(NULL, groupListRect.left, groupListRect.top, groupListRect.Width(), groupListRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect listRect;
	CListCtrl *pMedicineList = (CListCtrl*)GetDlgItem(IDC_LIST_MEDICINE);
	if (pMedicineList->GetSafeHwnd() != NULL)
	{
		listRect.left = clientRect.left + 5;
		listRect.top = groupListRect.top + 65;
		listRect.right = listRect.left + (clientRect.Width() - 10);
		listRect.bottom = clientRect.bottom - 5;
		pMedicineList->SetWindowPos(NULL, listRect.left, listRect.top, listRect.Width(), listRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
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
		nextBtnRect.top = groupListRect.top + 20;
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
		pageInfoRect.top = groupListRect.top + 25;
		pageInfoRect.bottom =  pageInfoRect.top + iHeight;
		pStaticPageInfo->SetWindowPos(NULL, pageInfoRect.left, pageInfoRect.top, pageInfoRect.Width(),  pageInfoRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect editRect;
	CButton *pEditBtn = (CButton*)GetDlgItem(IDC_BUTTON_MEDICINE_EDIT);
	if (pEditBtn->GetSafeHwnd() != NULL)
	{
		pEditBtn->GetWindowRect(&editRect);
		ScreenToClient(&editRect);
		iWidth = editRect.Width();
		iHeight = editRect.Height();
		editRect.top = groupListRect.top + 25;
		editRect.right = editRect.left + iWidth;
		editRect.bottom = editRect.top + iHeight;
		pEditBtn->SetWindowPos(NULL, editRect.left, editRect.top, editRect.Width(), editRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect delRect;
	CButton *pDelBtn = (CButton*)GetDlgItem(IDC_BUTTON_MEDICINE_DEL);
	if (pDelBtn->GetSafeHwnd() != NULL)
	{
		pDelBtn->GetWindowRect(&delRect);
		ScreenToClient(&delRect);
		iWidth = delRect.Width();
		iHeight = delRect.Height();
		delRect.top = editRect.top;
		delRect.right = delRect.left + iWidth;
		delRect.bottom = delRect.top + iHeight;
		pDelBtn->SetWindowPos(NULL, delRect.left, delRect.top, delRect.Width(), delRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect btnImportRect, btnSearchRect;
	CButton *pBtnImport = (CButton*)GetDlgItem(IDC_BUTTON_IMPORT);
	CButton *pBtnSearch = (CButton*)GetDlgItem(IDC_BUTTON_SEARCH);
	if( pBtnImport->GetSafeHwnd() != NULL && 
	    pBtnImport->IsWindowVisible() == TRUE &&
		pBtnSearch->GetSafeHwnd() != NULL)
	{
		pBtnImport->GetWindowRect(&btnImportRect);
		pBtnSearch->GetWindowRect(&btnSearchRect);
		ScreenToClient(&btnImportRect);
		ScreenToClient(&btnSearchRect);

		if (btnImportRect.left > btnSearchRect.left)
		{
			tempRect = btnImportRect;
			btnImportRect = btnSearchRect;
			btnSearchRect =tempRect;
		}
		pBtnImport->SetWindowPos(NULL, 
								btnImportRect.left,  
								btnImportRect.top, 
								btnImportRect.Width(), 
								btnImportRect.Height(), 
								SWP_NOACTIVATE | SWP_NOZORDER);
		pBtnSearch->SetWindowPos(NULL, 
								btnSearchRect.left,  
								btnSearchRect.top, 
								btnSearchRect.Width(), 
								btnSearchRect.Height(), 
								SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void CMedicineMgrView::DisplayListItem()
{
	ERRCODE errRet = err_OK;
	CString csMsg;
	CMedicineDB medicineDB;
	vector<Medicine*> vctMedicines;
	CSupplierMedicineDB supplierMedicineDB;
	vector<SupplierMedicine*> vctSupplierMedicine;
	CString csMedicineSN, csMedicineName, csVendor;
	csMedicineSN.Format(_T("%s"), m_medicineSearchDlg.m_csMedicineSN);
	csMedicineName.Format(_T("%%%s%%"), m_medicineSearchDlg.m_csMedicineName);

	if (m_medicineSearchDlg.m_csSupplierID == _T(""))
	{
		errRet = medicineDB.GetMedicines(m_dwCurPage, 
			g_ciNumPerPage, 
			m_dwTotalPage, 
			m_dwTotalNum, 
			vctMedicines, 
			csMedicineSN.GetBuffer(), 
			csMedicineName.GetBuffer(),
			m_medicineSearchDlg.m_csVendorID.GetBuffer());
		if (errRet != err_OK)
		{
			csMsg.Format(_T("获取药品信息失败！%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			return;
		}

		csMsg.Format(_T("第%d-%d项，共%d项"), m_dwTotalNum>0?m_dwCurPage * g_ciNumPerPage + 1:0, m_dwCurPage * g_ciNumPerPage +  vctMedicines.size(), m_dwTotalNum);
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

		m_btnEdit.EnableWindow(FALSE);
		m_btnDel.EnableWindow(FALSE);
		m_listMedicine.DeleteAllItems();
		for (unsigned int i = 0; i < vctMedicines.size(); i++)
		{
			m_listMedicine.InsertItem(i, vctMedicines[i]->csID);
			m_listMedicine.SetItemText(i, 1, vctMedicines[i]->csSN);
			m_listMedicine.SetItemText(i, 2, vctMedicines[i]->csName);
			m_listMedicine.SetItemText(i, 3, vctMedicines[i]->csSpec);
			m_listMedicine.SetItemText(i,4, vctMedicines[i]->csVendorName);
			csMsg.Format(_T("%0.2f"), atof(vctMedicines[i]->csRetailPrice));
			m_listMedicine.SetItemText(i, 5, csMsg);
			m_listMedicine.SetItemText(i, 6, vctMedicines[i]->unit.csName);
			m_listMedicine.SetItemText(i, 7, vctMedicines[i]->csSupplierCount);
			m_listMedicine.SetItemText(i,8, vctMedicines[i]->csCreateTime);
			m_listMedicine.SetItemText(i,9, vctMedicines[i]->csModifyTime);

			delete vctMedicines[i];
			vctMedicines[i] = NULL;
		}
		vctMedicines.clear();
	}
	else
	{
		errRet = supplierMedicineDB.GetSupplierMedicines(m_dwCurPage, 
			g_ciNumPerPage, 
			m_dwTotalPage, 
			m_dwTotalNum, 
			vctSupplierMedicine, 
			m_medicineSearchDlg.m_csSupplierID.GetBuffer(),
			csMedicineSN.GetBuffer(), 
			csMedicineName.GetBuffer(),
			m_medicineSearchDlg.m_csVendorID.GetBuffer());
		if (errRet != err_OK)
		{
			csMsg.Format(_T("获取药品信息失败！%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			return;
		}

		csMsg.Format(_T("第%d-%d项，共%d项"), m_dwTotalNum>0?m_dwCurPage * g_ciNumPerPage + 1:0, m_dwCurPage * g_ciNumPerPage +  vctSupplierMedicine.size(), m_dwTotalNum);
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

		m_btnEdit.EnableWindow(FALSE);
		m_btnDel.EnableWindow(FALSE);
		m_listMedicine.DeleteAllItems();
		for (unsigned int i = 0; i < vctSupplierMedicine.size(); i++)
		{
			m_listMedicine.InsertItem(i, vctSupplierMedicine[i]->medicine.csID);
			m_listMedicine.SetItemText(i, 1, vctSupplierMedicine[i]->medicine.csSN);
			m_listMedicine.SetItemText(i, 2, vctSupplierMedicine[i]->medicine.csName);
			m_listMedicine.SetItemText(i, 3, vctSupplierMedicine[i]->medicine.csSpec);
			m_listMedicine.SetItemText(i,4, vctSupplierMedicine[i]->medicine.csVendorName);
			csMsg.Format(_T("%0.2f"), atof(vctSupplierMedicine[i]->medicine.csRetailPrice));
			m_listMedicine.SetItemText(i, 5, csMsg);
			m_listMedicine.SetItemText(i, 6, vctSupplierMedicine[i]->medicine.unit.csName);
			m_listMedicine.SetItemText(i, 7, vctSupplierMedicine[i]->medicine.csSupplierCount);
			m_listMedicine.SetItemText(i,8, vctSupplierMedicine[i]->medicine.csCreateTime);
			m_listMedicine.SetItemText(i,9, vctSupplierMedicine[i]->medicine.csModifyTime);

			delete vctSupplierMedicine[i];
			vctSupplierMedicine[i] = NULL;
		}
		vctSupplierMedicine.clear();
	}
}

// CMedicineView diagnostics

#ifdef _DEBUG
void CMedicineMgrView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMedicineMgrView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMedicineView message handlers

void CMedicineMgrView::OnLvnItemchangedListMedicine(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int iTotalSelected = m_listMedicine.GetSelectedCount();
	POSITION pos = m_listMedicine.GetFirstSelectedItemPosition();
	int iSelected = m_listMedicine.GetNextSelectedItem(pos);
	if (iTotalSelected != 1 || iSelected == -1)
	{
		m_btnEdit.EnableWindow(FALSE);
		m_btnDel.EnableWindow(FALSE);
		return;
	}

	m_btnEdit.EnableWindow(TRUE);
	m_btnDel.EnableWindow(TRUE);
}

void CMedicineMgrView::OnBnClickedButtonMedicineAdd()
{
	// TODO: Add your control notification handler code here

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}
	pDoc->m_viewType = VIEW_NEW;
	pDoc->m_csMedicineID = _T("");

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_MEDICINE_ADD;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}


void CMedicineMgrView::OnBnClickedButtonMedicineEdit()
{
	// TODO: Add your control notification handler code here

	CString csMsg;

	POSITION pos = m_listMedicine.GetFirstSelectedItemPosition();
	int iSelected = m_listMedicine.GetNextSelectedItem(pos);
	if (iSelected == -1)
	{
		return;
	}
	CString csID = m_listMedicine.GetItemText(iSelected, 0);

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}
	pDoc->m_viewType = VIEW_EDIT;
	pDoc->m_csMedicineID = csID;

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}
	TreeMenuID leftPanelID = TREE_MEDICINE_ADD;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}


void CMedicineMgrView::OnBnClickedButtonMedicineDel()
{
	// TODO: Add your control notification handler code here

	ERRCODE errRet = err_OK;
	CString csMsg;

	POSITION pos = m_listMedicine.GetFirstSelectedItemPosition();
	int iSelected = m_listMedicine.GetNextSelectedItem(pos);
	if (iSelected == -1)
	{
		return;
	}

	CString csID = m_listMedicine.GetItemText(iSelected, 0);
	CString csSN = m_listMedicine.GetItemText(iSelected, 1);
	CString csName = m_listMedicine.GetItemText(iSelected, 2);
	csID.Trim();
	csSN.Trim();
	csName.Trim();

	CStoreDB storeDB;
	vector<MedicineBatchStore*> vctMedicineStore;

	errRet = storeDB.GetMedicineBatchStores(m_dwCurPage, 
																	g_ciNumPerPage, 
																	m_dwTotalPage, 
																	m_dwTotalNum, 
																	vctMedicineStore,
																	csSN.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("删除药品失败，%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return;
	}
	if (vctMedicineStore.size())
	{
		csMsg.Format(_T("由于库存中存在该药品，不允许删除该药品信息！"));
		MessageBox(csMsg, _T("药品管理"), MB_ICONINFORMATION);
		return;
	}

	csMsg.Format(_T("您确认删除药品'%s'吗？"), csName);
	if (IDCANCEL == MessageBox(csMsg, _T("药品管理"), MB_ICONQUESTION|MB_OKCANCEL))
	{
		return;
	}

	CMedicineDB medicineDB;
	CSupplierMedicineDB supplierMedicineDB;
	CMedicineBatchDB medicineBatchDB;

	vector<SupplierMedicine*> vctSupplierMedicines;
	errRet = supplierMedicineDB.GetSupplierMedicines(0, 1000, m_dwTotalPage, m_dwTotalNum, vctSupplierMedicines, NULL, csSN.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("删除药品失败，%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return;
	}
	for (unsigned int j = 0; j < vctSupplierMedicines.size(); j++)
	{
		if (vctSupplierMedicines[j]  != NULL)
		{
			delete vctSupplierMedicines[j];
			vctSupplierMedicines[j] = NULL;
		}
	}
	vctSupplierMedicines.clear();

	errRet = supplierMedicineDB.DeleteSupplierMedicinesByMID(csID.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("删除药品失败，%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return;
	}
	
	errRet = medicineBatchDB.DeleteMedicineBatchs(csID.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("删除药品失败，%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return;
	}

	errRet = medicineDB.DeleteMedicine(csID.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("删除药品失败，%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return;
	}

	m_listMedicine.DeleteItem(iSelected);
}

void CMedicineMgrView::OnNMDblclkListMedicine(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	OnBnClickedButtonMedicineEdit();
	*pResult = 0;
}

void CMedicineMgrView::OnBnClickedBtnPrepage()
{
	// TODO: Add your control notification handler code here
	if (m_dwCurPage <= 0)
	{
		return;
	}

	m_dwCurPage--;
	DisplayListItem();
}


void CMedicineMgrView::OnBnClickedBtnNextpage()
{
	// TODO: Add your control notification handler code here
	if (m_dwCurPage + 1 >= m_dwTotalNum)
	{
		return;
	}

	m_dwCurPage++;
	DisplayListItem();
}


void CMedicineMgrView::OnBnClickedButtonImport()
{
	CMedicineImportDlg medicineImportDlg;
	medicineImportDlg.DoModal();
}


void CMedicineMgrView::OnBnClickedButtonSearch()
{
	// TODO: Add your control notification handler code here

	if (IDOK != m_medicineSearchDlg.DoModal())
	{
		m_btnAdd.SetFocus();
		return;
	}
	m_listMedicine.SetFocus();

	CString csMsg;
	if (m_medicineSearchDlg.m_csMedicineSN == _T("") && m_medicineSearchDlg.m_csMedicineName == _T(""))
	{
		csMsg.Format(_T("库存列表 （全部）"));
	}
	else
	{
		csMsg.Format(_T("库存列表  （ "));
		if (m_medicineSearchDlg.m_csMedicineSN != _T(""))
		{
			csMsg.AppendFormat(_T("药品编码：%s "), m_medicineSearchDlg.m_csMedicineSN);
		}
		if (m_medicineSearchDlg.m_csMedicineName != _T(""))
		{
			csMsg.AppendFormat(_T("药品名称：%s "), m_medicineSearchDlg.m_csMedicineName);
		}
		csMsg.AppendFormat(_T("）"));
	}
	SetDlgItemText(IDC_STATIC_GROUP_LIST, csMsg);

	m_dwCurPage = 0;
	DisplayListItem();
}

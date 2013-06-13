// PurchaseListView.cpp : ʵ���ļ�
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
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_btnDel);
	DDX_Control(pDX, IDC_STATIC_GROUP_PUR, m_staticGroupPur);
	DDX_Control(pDX, IDC_COMBO_MEDICINE_TYPE, m_comboMedicineType);
}

BEGIN_MESSAGE_MAP(CPurchaseListView, CFormView)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PUR, &CPurchaseListView::OnLvnItemchangedListPur)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CPurchaseListView::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CPurchaseListView::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CPurchaseListView::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BTN_PREPAGE, &CPurchaseListView::OnBnClickedBtnPrepage)
	ON_BN_CLICKED(IDC_BTN_NEXTPAGE, &CPurchaseListView::OnBnClickedBtnNextpage)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CPurchaseListView::OnBnClickedButtonSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_MEDICINE_TYPE, &CPurchaseListView::OnCbnSelchangeComboMedicineType)
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

	m_listPur.SetExtendedStyle(LVS_EX_FLATSB    // ��ƽ������
		| LVS_EX_FULLROWSELECT    // ��������ѡ��
		| LVS_EX_HEADERDRAGDROP    // ���������ק
		| LVS_EX_GRIDLINES    // ����������
		);
	int iSubItem = 0;
	m_listPur.InsertColumn(iSubItem++, "���", LVCFMT_LEFT, 0, 0);
	m_listPur.InsertColumn(iSubItem++, "��������", LVCFMT_LEFT, 80, 0);
	m_listPur.InsertColumn(iSubItem++, "������Ա", LVCFMT_LEFT, 80, 0);
	m_listPur.InsertColumn(iSubItem++, "ҩƷ����", LVCFMT_LEFT, 120, 0);
	m_listPur.InsertColumn(iSubItem++, "ҩƷ����", LVCFMT_LEFT, 150, 0);
	m_listPur.InsertColumn(iSubItem++, "����", LVCFMT_LEFT, 60, 0);
	m_listPur.InsertColumn(iSubItem++, "���", LVCFMT_LEFT, 80, 0);
	m_listPur.InsertColumn(iSubItem++, "��Ӧ��", LVCFMT_LEFT, 80, 0);
	m_listPur.InsertColumn(iSubItem++, "��������", LVCFMT_LEFT, 80, 0);
	m_listPur.InsertColumn(iSubItem++, "��������", LVCFMT_LEFT, 80, 0);
	m_listPur.InsertColumn(iSubItem++, "��׼�ĺ�", LVCFMT_LEFT, 80, 0);
	m_listPur.InsertColumn(iSubItem++, "��������", LVCFMT_LEFT, 80, 0);
	m_listPur.InsertColumn(iSubItem++, "��Ч����", LVCFMT_LEFT, 80, 0);
	m_listPur.InsertColumn(iSubItem++, "����", LVCFMT_LEFT, 60, 0);
	m_listPur.InsertColumn(iSubItem++, "����", LVCFMT_LEFT, 60, 0);
	m_listPur.InsertColumn(iSubItem++, "��λ", LVCFMT_LEFT, 60, 0);
	m_listPur.InsertColumn(iSubItem++, "���", LVCFMT_LEFT, 80, 0);

	m_comboMedicineType.AddString("ȫ��");
	m_comboMedicineType.AddString("ҩƷ");
	m_comboMedicineType.AddString("����Ʒ");
	m_comboMedicineType.AddString("ҽ����е");
	m_comboMedicineType.SetCurSel(1);

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

	CRect comboMedicTypeRect;
	CComboBox *pComboMedicType = (CComboBox*)GetDlgItem(IDC_COMBO_MEDICINE_TYPE);
	if (pComboMedicType->GetSafeHwnd() != NULL)
	{
		pComboMedicType->GetWindowRect(comboMedicTypeRect);
		ScreenToClient(&comboMedicTypeRect);
		iWidth = comboMedicTypeRect.Width();
		iHeight = comboMedicTypeRect.Height();
		comboMedicTypeRect.right = clientRect.Width() - 7;
		comboMedicTypeRect.left = comboMedicTypeRect.right - iWidth;
		pComboMedicType->SetWindowPos(NULL, comboMedicTypeRect.left, comboMedicTypeRect.top, comboMedicTypeRect.Width(),  comboMedicTypeRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect groupPurRect;
	CStatic *pGroupPur = (CStatic*)GetDlgItem(IDC_STATIC_GROUP_PUR);
	if (pGroupPur->GetSafeHwnd() != NULL)
	{
		groupPurRect.left = clientRect.left + 5;
		groupPurRect.top = clientRect.top + 60;
		groupPurRect.right = groupPurRect.left + (clientRect.Width() - 10);
		groupPurRect.bottom = clientRect.bottom - 5;
		pGroupPur->SetWindowPos(NULL, groupPurRect.left, groupPurRect.top, groupPurRect.Width(), groupPurRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect purListRect;
	CListCtrl *pPurList = (CListCtrl*)GetDlgItem(IDC_LIST_PUR);
	if (pPurList->GetSafeHwnd() != NULL)
	{
		purListRect.left = groupPurRect.left;
		purListRect.top = groupPurRect.top + 65;
		purListRect.right = purListRect.left + (clientRect.Width() - 10);
		purListRect.bottom = clientRect.bottom - 5;
		pPurList->SetWindowPos(NULL, purListRect.left, purListRect.top, purListRect.Width(), purListRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect delBtnRect;
	CButton *pBtnDel = (CButton*)GetDlgItem(IDC_BUTTON_DELETE);
	if (pBtnDel->GetSafeHwnd() != NULL)
	{
		pBtnDel->GetWindowRect(delBtnRect);
		ScreenToClient(&delBtnRect);
		iWidth = delBtnRect.Width();
		iHeight = delBtnRect.Height();
		delBtnRect.top = groupPurRect.top + 25;
		delBtnRect.bottom =  delBtnRect.top + iHeight;
		pBtnDel->SetWindowPos(NULL, delBtnRect.left, delBtnRect.top, delBtnRect.Width(),  delBtnRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
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
	CString csMedicineName;
	if (m_purchaseSearchDlg.m_csMedicineName != "")
	{
		csMedicineName.Format(_T("%%%s%%"), m_purchaseSearchDlg.m_csMedicineName);
	}

	CString csMedicTypeID;
	int iComboMedicType = m_comboMedicineType.GetCurSel();
	if (iComboMedicType == 0)
	{

	}
	else if (iComboMedicType == 1)
	{
		csMedicTypeID.Format("%d,%d,%d", TYPE_ZHONGCHENGYAO, TYPE_ZHONGCAOYAO, TYPE_XIYAO);
	}
	else if (iComboMedicType == 2)
	{
		csMedicTypeID.Format("%d", TYPE_BAOJIANPIN);
	}
	else if (iComboMedicType == 3)
	{
		csMedicTypeID.Format("%d", TYPE_YILIAOQIXIE);
	}

	ERRCODE errRet = purchaseDB.GetPurchases(m_dwCurPage, 
																		g_ciNumPerPage, 
																		m_dwTotalPage, 
																		m_dwTotalNum, 
																		m_dbTotalPrice, 
																		vctPurchases,
																		m_purchaseSearchDlg.m_csPurBeginDate.GetBuffer(),
																		m_purchaseSearchDlg.m_csPurEndDate.GetBuffer(),
																		m_purchaseSearchDlg.m_csMedicineSN.GetBuffer(),
																		csMedicineName.GetBuffer(),
																		csMedicTypeID.GetBuffer(),
																		m_purchaseSearchDlg.m_csMedicineBatchNum.GetBuffer(),
																		m_purchaseSearchDlg.m_csSupplierID.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("��ȡ������Ϣʧ�ܣ�%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("�����嵥"), MB_ICONERROR);
		return;
	}

	csMsg.Format(_T("��%d-%d���%d��"), m_dwTotalNum>0?m_dwCurPage * g_ciNumPerPage + 1:0, m_dwCurPage * g_ciNumPerPage +  vctPurchases.size(), m_dwTotalNum);
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

	csMsg.Format(_T("�����б� ���ϼƣ�%0.2fԪ��"), m_dbTotalPrice);
	if (m_purchaseSearchDlg.m_csPurBeginDate != _T("") && m_purchaseSearchDlg.m_csPurEndDate != _T(""))
	{
		csMsg.AppendFormat(_T(" �� �������ڣ�%s��%s ��"), m_purchaseSearchDlg.m_csPurBeginDate, m_purchaseSearchDlg.m_csPurEndDate);
	}

	m_staticGroupPur.SetWindowText(csMsg);

	errRet = medicineDB.GetMedicineUnits(vctMedicineUnit);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("��ȡҩƷ��Ϣ����%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("�����嵥"), MB_ICONERROR);
		return;
	}

	int iSubItem = 0;
	m_listPur.DeleteAllItems();
	for (unsigned int i = 0; i < vctPurchases.size(); i++)
	{
		m_listPur.InsertItem(i, vctPurchases[i]->csID);
		iSubItem = 1;
		m_listPur.SetItemText(i,iSubItem++, vctPurchases[i]->csPurchaseTime);
		csMsg.Format(_T("%s-%s"), vctPurchases[i]->csUserUID, vctPurchases[i]->csUserName);
		m_listPur.SetItemText(i, iSubItem++, csMsg);
		m_listPur.SetItemText(i, iSubItem++, vctPurchases[i]->medicine.csSN);
		m_listPur.SetItemText(i,iSubItem++, vctPurchases[i]->medicine.csName);
		m_listPur.SetItemText(i,iSubItem++, vctPurchases[i]->medicine.form.csName);
		m_listPur.SetItemText(i,iSubItem++, vctPurchases[i]->medicine.csSpec);
		m_listPur.SetItemText(i, iSubItem++, vctPurchases[i]->csSupplierName);
		m_listPur.SetItemText(i,iSubItem++, vctPurchases[i]->medicine.csVendorName);
		m_listPur.SetItemText(i,iSubItem++, vctPurchases[i]->medicineBatch.csBatchNum);
		m_listPur.SetItemText(i,iSubItem++, vctPurchases[i]->medicine.csRegNum);
		m_listPur.SetItemText(i,iSubItem++, vctPurchases[i]->medicineBatch.csProductDate);
		m_listPur.SetItemText(i,iSubItem++, vctPurchases[i]->medicineBatch.csExpireDate);
		csMsg.Format(_T("%0.2f"), atof(vctPurchases[i]->csPurPrice));
		m_listPur.SetItemText(i,iSubItem++, csMsg);
		m_listPur.SetItemText(i,iSubItem++, vctPurchases[i]->csNumber);
		m_listPur.SetItemText(i,iSubItem++, vctPurchases[i]->medicine.unit.csName);
		csMsg.Format(_T("%0.2f"), atof(vctPurchases[i]->csPurPrice.GetBuffer()) * atol(vctPurchases[i]->csNumber.GetBuffer()));
		m_listPur.SetItemText(i,iSubItem++, csMsg);
		

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

// CPurchaseListView ��Ϣ�������

void CPurchaseListView::OnLvnItemchangedListPur(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	csMsg.Format(_T("��ȷ��ִ�����²�����\r\n  1. ���¿�棬ȡ���ö�����������\r\n  2. ɾ���ý���������¼��Ϣ��"), csID);
	if (IDCANCEL == MessageBox(csMsg, _T("��������"), MB_ICONQUESTION|MB_OKCANCEL))
	{
		return;
	}

	CPurchaseDB purchaseDB;

	errRet = purchaseDB.DeletePurchase(csID.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("ɾ������ʧ�ܣ�%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("��������"), MB_ICONERROR);
		return;
	}
	m_listPur.DeleteItem(iSelected);
}

void CPurchaseListView::OnBnClickedButtonSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (IDOK != m_purchaseSearchDlg.DoModal())
	{
		return;
	}

	m_dwCurPage = 0;
	DisplayListItem();
}


void CPurchaseListView::OnCbnSelchangeComboMedicineType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_dwCurPage = 0;
	m_dwTotalNum = 0;
	m_dwTotalPage = 0;
	DisplayListItem();
}

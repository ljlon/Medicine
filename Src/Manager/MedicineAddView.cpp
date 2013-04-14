// MedicineAddView.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "MedicineAddView.h"
#include "MainFrm.h"

// CMedicineAddView

IMPLEMENT_DYNCREATE(CMedicineAddView, CFormView)

CMedicineAddView::CMedicineAddView()
	: CFormView(CMedicineAddView::IDD)
{
	m_bDataChanged = FALSE;
	m_iSupplierListItem = -1;
	m_iSupplierListSubItem = -1;
}

CMedicineAddView::~CMedicineAddView()
{
	if (m_pSupplierListPopupEdit != NULL)
	{
		delete m_pSupplierListPopupEdit;
		m_pSupplierListPopupEdit = NULL;
	}

	if (m_pSupplierListPopupCmbox != NULL)
	{
		delete m_pSupplierListPopupCmbox;
		m_pSupplierListPopupCmbox = NULL;
	}

	for (unsigned int i = 0; i < m_vctMedicineUtil.size(); i++)
	{

		delete m_vctMedicineUtil[i];
		m_vctMedicineUtil[i] = NULL;
	}
	m_vctMedicineUtil.clear();

	for (unsigned int i = 0; i < m_vctMedicineType.size(); i++)
	{

		delete m_vctMedicineType[i];
		m_vctMedicineType[i] = NULL;
	}
	m_vctMedicineType.clear();

	for (unsigned int i = 0; i < m_vctMedicineOTC.size(); i++)
	{

		delete m_vctMedicineOTC[i];
		m_vctMedicineOTC[i] = NULL;
	}
	m_vctMedicineOTC.clear();

	for (unsigned int i = 0; i < m_vctMedicineForm.size(); i++)
	{
		delete m_vctMedicineForm[i];
		m_vctMedicineForm[i] = NULL;
	}
	m_vctMedicineForm.clear();

	for (map<LONG, SupplierMedicine*>::iterator it = m_mapVctSupplierMedicine.begin(); it != m_mapVctSupplierMedicine.end(); it++)
	{
		if (it->second != NULL)
		{
			delete it->second;
			it->second = NULL;
		}
	}
	m_mapVctSupplierMedicine.clear();
}

void CMedicineAddView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MEDICINE_UNIT, m_cbUtil);
	DDX_Control(pDX, IDC_COMBO_MEDICINE_TYPE, m_cbType);
	DDX_Control(pDX, IDC_COMBO_MEDICINE_OTC, m_cbOTC);
	DDX_Control(pDX, IDC_COMBO_MEDICINE_FORM, m_cbForm);
	DDX_Control(pDX, IDC_COMBO_MEDICINE_VENDORID, m_cbVendor);
	DDX_Control(pDX, IDC_LIST_SUPPLIER, m_listSupplier);
	DDX_Control(pDX, IDC_BTN_SUPPLIER_DEL, m_btnDelPur);
	DDX_Control(pDX, IDC_BTN_SUPPLIER_ADD, m_btnAddPur);
	DDX_Control(pDX, IDC_EDIT_MEDICINE_SN, m_editMedicineSN);
}

BEGIN_MESSAGE_MAP(CMedicineAddView, CFormView)
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(WM_RICHLISTCTRL_MESSGAE, &CMedicineAddView::OnRichListCtrl)
	ON_BN_CLICKED(IDC_BUTTON_MEDICINE_ADD_OK, &CMedicineAddView::OnBnClickedButtonMedicineAddOk)
	ON_BN_CLICKED(IDC_BUTTON_MEDICINE_CANCEL, &CMedicineAddView::OnBnClickedButtonMedicineCancel)
	ON_EN_CHANGE(IDC_EDIT_MEDICINE_NAME, &CMedicineAddView::OnEnChangeEditMedicineName)
	ON_EN_CHANGE(IDC_EDIT_MEDICINE_ID, &CMedicineAddView::OnEnChangeEditMedicineId)
	ON_CBN_EDITUPDATE(IDC_COMBO_MEDICINE_VENDORID, &CMedicineAddView::OnCbnEditupdateComboVendor)
	ON_CBN_DROPDOWN(IDC_COMBO_MEDICINE_VENDORID, &CMedicineAddView::OnCbnDropdownComboMedicineVendorid)
	ON_CBN_SELCHANGE(IDC_COMBO_MEDICINE_VENDORID, &CMedicineAddView::OnCbnSelchangeComboMedicineVendorid)
	ON_CBN_EDITUPDATE(IDC_COMBO_POPUP, &CMedicineAddView::OnCbnEditupdateComboSupplier)
	ON_CBN_DROPDOWN(IDC_COMBO_POPUP, &CMedicineAddView::OnCbnDropdownComboMedicineSupplierid)
	ON_CBN_SELCHANGE(IDC_COMBO_POPUP, &CMedicineAddView::OnCbnSelchangeComboMedicineSupplierid)
	ON_EN_CHANGE(IDC_EDIT_MEDICINE_SN, &CMedicineAddView::OnEnChangeEditMedicineSn)
	ON_CBN_SELCHANGE(IDC_COMBO_MEDICINE_UNIT, &CMedicineAddView::OnCbnSelchangeComboMedicineUnit)
	ON_CBN_SELCHANGE(IDC_COMBO_MEDICINE_TYPE, &CMedicineAddView::OnCbnSelchangeComboMedicineType)
	ON_CBN_SELCHANGE(IDC_COMBO_MEDICINE_OTC, &CMedicineAddView::OnCbnSelchangeComboMedicineOtc)
	ON_CBN_SELCHANGE(IDC_COMBO_MEDICINE_FORM, &CMedicineAddView::OnCbnSelchangeComboMedicineForm)
	ON_CBN_DROPDOWN(IDC_COMBO_MEDICINE_UNIT, &CMedicineAddView::OnCbnDropdownComboMedicineUnit)
	ON_CBN_DROPDOWN(IDC_COMBO_MEDICINE_TYPE, &CMedicineAddView::OnCbnDropdownComboMedicineType)
	ON_CBN_DROPDOWN(IDC_COMBO_MEDICINE_OTC, &CMedicineAddView::OnCbnDropdownComboMedicineOtc)
	ON_CBN_DROPDOWN(IDC_COMBO_MEDICINE_FORM, &CMedicineAddView::OnCbnDropdownComboMedicineForm)
	ON_EN_CHANGE(IDC_EDIT_MEDICINE_SPEC, &CMedicineAddView::OnEnChangeEditMedicineSpec)
	ON_EN_CHANGE(IDC_EDIT_MEDICINE_RETAILPRICE, &CMedicineAddView::OnEnChangeEditMedicineRetailprice)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SUPPLIER, &CMedicineAddView::OnLvnItemchangedListSupplier)
	ON_BN_CLICKED(IDC_BTN_SUPPLIER_DEL, &CMedicineAddView::OnBnClickedBtnSupplierMedicineDel)
	ON_BN_CLICKED(IDC_BTN_SUPPLIER_ADD, &CMedicineAddView::OnBnClickedBtnSupplierMedicineAdd)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SUPPLIER, &CMedicineAddView::OnNMClickListSupplier)
	ON_EN_KILLFOCUS(IDC_EDIT_POPUP, &CMedicineAddView::OnCbnKillfocusPopupEdit)
	ON_CBN_KILLFOCUS(IDC_COMBO_POPUP, &CMedicineAddView::OnCbnKillfocusPopupCombox)
	ON_NOTIFY(LVN_ENDSCROLL, IDC_LIST_SUPPLIER, &CMedicineAddView::OnLvnEndScrollListSupplier)
	ON_BN_CLICKED(IDC_BTN_VENDOR_ADD, &CMedicineAddView::OnBnClickedBtnVendorAdd)
END_MESSAGE_MAP()


// CMedicineAddView diagnostics

#ifdef _DEBUG
void CMedicineAddView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMedicineAddView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMedicineAddView message handlers

void CMedicineAddView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CString csMsg;
	csMsg.Format("%s-%s", APP_NAME, APP_MANAGER);
	AfxGetApp()->GetMainWnd()->SetWindowText(csMsg);

	m_listSupplier.SetExtendedStyle(LVS_EX_FLATSB    // 扁平风格滚动
		| LVS_EX_FULLROWSELECT    // 允许整行选中
		| LVS_EX_HEADERDRAGDROP    // 允许标题拖拽
		| LVS_EX_CHECKBOXES
		//| LVS_EX_GRIDLINES    // 画出网格线
		);
	m_listSupplier.InsertColumn(0, "", LVCFMT_LEFT, 20, 0);
	m_listSupplier.InsertColumn(1, "编号", LVCFMT_LEFT, 0, 0);
	m_listSupplier.InsertColumn(2, "供应商", LVCFMT_LEFT, 200, 0);
	m_listSupplier.InsertColumn(3, "进价", LVCFMT_LEFT, 80, 0);
	m_listSupplier.InsertColumn(4, "", LVCFMT_LEFT, 80, 0);
	m_listSupplier.InsertColumn(5, "", LVCFMT_LEFT, 80, 0);

	m_pSupplierListPopupEdit = new CEdit;
	m_pSupplierListPopupEdit->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP , CRect(0,0,0,0), this, IDC_EDIT_POPUP);
	m_pSupplierListPopupEdit->ShowWindow(SW_HIDE);
	m_pSupplierListPopupEdit->SetParent(&m_listSupplier);

	m_pSupplierListPopupCmbox = new CComboBox;
	m_pSupplierListPopupCmbox->Create(CBS_AUTOHSCROLL|CBS_DROPDOWN|WS_VSCROLL|WS_CHILD|WS_VISIBLE|WS_TABSTOP , CRect(0,0,0,0), this, IDC_COMBO_POPUP);
	m_pSupplierListPopupCmbox->ShowWindow(SW_HIDE);
	m_pSupplierListPopupCmbox->SetParent(&m_listSupplier);

	CMedicineDB medicineDB;
	//Medicine Units
	ERRCODE errRet = medicineDB.GetMedicineUnits(m_vctMedicineUtil);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取药品信息错误！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return;
	}
	for (unsigned int i = 0; i < m_vctMedicineUtil.size(); i++)
	{
		csMsg.Format(_T("%s"), m_vctMedicineUtil[i]->csName);
		m_cbUtil.AddString(csMsg);
	}

	//Medicine Type
	errRet = medicineDB.GetMedicineTypes(m_vctMedicineType);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取药品信息错误！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return;
	}
	for (unsigned int i = 0; i < m_vctMedicineType.size(); i++)
	{
		csMsg.Format(_T("%s"), m_vctMedicineType[i]->csName);
		m_cbType.AddString(csMsg);
	}

	//Medicine OTC
	errRet = medicineDB.GetMedicineOTCs(m_vctMedicineOTC);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取药品信息错误！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return;
	}
	for (unsigned int i = 0; i < m_vctMedicineOTC.size(); i++)
	{
		csMsg.Format(_T("%s"), m_vctMedicineOTC[i]->csName);
		m_cbOTC.AddString(csMsg);
	}

	//Medicine Form
	errRet = medicineDB.GetMedicineForms(m_vctMedicineForm);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取药品信息错误！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return;
	}
	for (unsigned int i = 0; i < m_vctMedicineForm.size(); i++)
	{
		csMsg.Format(_T("%s"), m_vctMedicineForm[i]->csName);
		m_cbForm.AddString(csMsg);
	}

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc != NULL)
	{
		m_viewType = pDoc->m_viewType;
		pDoc->m_csMedicineID.Trim();
		pDoc->m_csMedicineSN.Trim();
		if (m_viewType == VIEW_EDIT)
		{
			m_editMedicineSN.SetReadOnly(TRUE);
			m_btnAddPur.EnableWindow(TRUE);
			m_btnDelPur.EnableWindow(FALSE);
			m_medicine.csID = pDoc->m_csMedicineID;
			DisplayMedicineInfo(m_medicine.csID.GetBuffer());
		}
		else if (m_viewType == VIEW_SUBNEW)
		{
			if (pDoc->m_csMedicineSN != _T(""))
			{
				SetDlgItemText(IDC_EDIT_MEDICINE_SN, pDoc->m_csMedicineSN);
				m_editMedicineSN.SetReadOnly(TRUE);
			}
			if (pDoc->m_csSupplierID != _T(""))
			{
				CSupplierDB supplierDB;
				supplierDB.GetSupplier(pDoc->m_csSupplierID.GetBuffer(), &m_supplier);
				csMsg.Format(_T("%s-%s"), m_supplier.csID, m_supplier.csName);
				
				m_listSupplier.InsertItem(0, _T(""), CTRL_DEFAULT);
				m_listSupplier.SetItemText(0, 1, m_supplier.csID);
				m_listSupplier.SetItemText(0, 2, csMsg);
				
				SupplierMedicine *pSupplierMedicine = new SupplierMedicine;
				pSupplierMedicine->csSupplierID = m_supplier.csID;
				m_mapVctSupplierMedicine.insert(map<LONG, SupplierMedicine*>::value_type(atol(m_supplier.csID), pSupplierMedicine));

				m_btnAddPur.EnableWindow(FALSE);
				m_btnDelPur.EnableWindow(FALSE);
			}
		}

		LoadDataFromDoc();
	}

	m_editMedicineSN.SetFocus();
}

BOOL CMedicineAddView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			CString csSN;
			CWnd *pWnd = GetFocus();
			if (pWnd == GetDlgItem(IDC_EDIT_MEDICINE_SN))
			{
				GetDlgItemText(IDC_EDIT_MEDICINE_SN, csSN);
				csSN.Trim();

				Medicine medicine;
				if (GetMedicineInfoBySN(csSN.GetBuffer(), &medicine) == err_OK)
				{
					SetDlgItemText(IDC_EDIT_MEDICINE_SN, _T(""));
					MessageBox(_T("该药品编码已经存在！"), _T(""), MB_ICONINFORMATION);
					GetDlgItem(IDC_EDIT_MEDICINE_SN)->SetFocus();
					return CFormView::PreTranslateMessage(pMsg);
				}
			}
			pMsg->wParam = VK_TAB;
		}
	}  

	return CFormView::PreTranslateMessage(pMsg);
}

LRESULT CMedicineAddView::OnRichListCtrl(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case WM_RICHLS_CLICK_BUTTON:
		OnListBtnClicked((LVHITTESTINFO*)lParam);
		break;

	default:
		break;
	}
	return TRUE;
}

void CMedicineAddView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CMedicineAddView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	CStatic *pStaticGroupBasic = (CStatic*)GetDlgItem(IDC_STATIC_GROUP_BASIC);
	CStatic *pStaticGroupPSG = (CStatic*)GetDlgItem(IDC_STATIC_GROUP_PSG);
	CStatic *pStaticGroupPur = (CStatic*)GetDlgItem(IDC_STATIC_GROUP_PUR);
	CListCtrl *pListSupplier = (CListCtrl*)GetDlgItem(IDC_LIST_SUPPLIER);

	if (pStaticGroupBasic->GetSafeHwnd() == NULL || 
		pStaticGroupPSG->GetSafeHwnd() == NULL || 
		pStaticGroupPur->GetSafeHwnd() == NULL || 
		pListSupplier->GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect basicRect;
	pStaticGroupBasic->GetWindowRect(basicRect);
	ScreenToClient(&basicRect);
	pStaticGroupBasic->SetWindowPos(NULL, basicRect.left, basicRect.top, rectClient.Width() - 2 * (basicRect.left - rectClient.left), basicRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);

	CRect PSGRect;
	pStaticGroupPSG->GetWindowRect(PSGRect);
	ScreenToClient(&PSGRect);
	pStaticGroupPSG->SetWindowPos(NULL, PSGRect.left, PSGRect.top, rectClient.Width() - 2 * (PSGRect.left - rectClient.left), PSGRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);

	CRect PSGPur;
	pStaticGroupPur->GetWindowRect(PSGPur);
	ScreenToClient(&PSGPur);
	pStaticGroupPur->SetWindowPos(NULL, PSGPur.left, PSGPur.top, rectClient.Width() - 2 * (PSGPur.left - rectClient.left), PSGPur.Height(), SWP_NOACTIVATE | SWP_NOZORDER);

	CRect supplierListRect;
	pListSupplier->GetWindowRect(supplierListRect);
	ScreenToClient(&supplierListRect);
	pListSupplier->SetWindowPos(NULL, supplierListRect.left, supplierListRect.top, supplierListRect.Width(), supplierListRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
}


void CMedicineAddView::OnBnClickedButtonMedicineAddOk()
{
	// TODO: Add your control notification handler code here

	if (AddMedicine() != TRUE)
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


BOOL CMedicineAddView::BeCancel()
{
	CString csMsg;
	if (m_bDataChanged == TRUE)
	{
		if (m_viewType != VIEW_EDIT)
		{
			csMsg.Format(_T("是否保存该药品信息？"));
		}
		else
		{
			csMsg.Format(_T("是否保存对该药品信息的修改？"));
		}

		int iRet = MessageBox(csMsg, _T("药品管理"), MB_ICONQUESTION|MB_YESNOCANCEL);
		if (iRet == IDCANCEL)
		{
			return FALSE;
		}
		else if (iRet == IDYES)
		{
			if (AddMedicine() != TRUE)
			{
				return FALSE;
			}
		}
	}

	for (map<LONG, SupplierMedicine*>::iterator it = m_mapVctSupplierMedicine.begin(); it != m_mapVctSupplierMedicine.end(); it++)
	{
		if (it->second != NULL)
		{
			delete it->second;
			it->second = NULL;
		}
	}
	m_mapVctSupplierMedicine.clear();

	for (map<LONG, SupplierMedicine*>::iterator it = m_mapVctDelSupplierMedicine.begin(); it != m_mapVctDelSupplierMedicine.end(); it++)
	{
		if (it->second != NULL)
		{
			delete it->second;
			it->second = NULL;
		}
	}
	m_mapVctDelSupplierMedicine.clear();

	m_bDataChanged = FALSE;
	return TRUE;
}

void CMedicineAddView::OnBnClickedButtonMedicineCancel()
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


BOOL CMedicineAddView::AddMedicine()
{
	ERRCODE errRet = err_OK;
	CString csMsg;
	CString csSN, csName, csSpec,csVendor, csRetailPrice, csUnit, csType, csOTC, csForm;
	GetDlgItemText(IDC_EDIT_MEDICINE_SN, csSN);
	GetDlgItemText(IDC_EDIT_MEDICINE_NAME, csName);
	GetDlgItemText(IDC_EDIT_MEDICINE_SPEC, csSpec);
	GetDlgItemText(IDC_COMBO_MEDICINE_VENDORID, csVendor);
	GetDlgItemText(IDC_EDIT_MEDICINE_RETAILPRICE, csRetailPrice);

	unsigned int iCurSel = m_cbUtil.GetCurSel();
	if (iCurSel < m_vctMedicineUtil.size())
	{
		csUnit = m_vctMedicineUtil[iCurSel]->csID;
	}
	iCurSel = m_cbType.GetCurSel();
	if (iCurSel < m_vctMedicineType.size())
	{
		csType = m_vctMedicineType[iCurSel]->csID;
	}
	iCurSel = m_cbOTC.GetCurSel();
	if (iCurSel < m_vctMedicineOTC.size())
	{
		csOTC = m_vctMedicineOTC[iCurSel]->csID;
	}
	iCurSel = m_cbForm.GetCurSel();
	if (iCurSel < m_vctMedicineForm.size())
	{
		csForm = m_vctMedicineForm[iCurSel]->csID;
	}

	csSN.Trim();
	csName.Trim();
	csSpec.Trim();
	csVendor.Trim();
	csRetailPrice.Trim();
	csUnit.Trim();
	csType.Trim();
	csOTC.Trim();
	csForm.Trim();

	//检查未填写
	if (csSN == _T(""))
	{
		csMsg.Format("药品编码不能为空！");
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return FALSE;
	}

	if (csName == _T(""))
	{
		csMsg.Format("药品名称不能为空！");
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return FALSE;
	}

	if (csSpec == _T(""))
	{
		csMsg.Format("药品规格不能为空！");
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return FALSE;
	}

	if (csRetailPrice == _T(""))
	{
		csMsg.Format("药品零售价格不能为空！");
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return FALSE;
	}

	if (csUnit == _T(""))
	{
		csMsg.Format("请选择药品单位！");
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return FALSE;
	}

	if (csType == _T(""))
	{
		csMsg.Format("请选择药品类型！");
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return FALSE;
	}

	if (csOTC == _T(""))
	{
		csMsg.Format("请选择药品是否处方！");
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return FALSE;
	}

	if (csForm == _T(""))
	{
		csMsg.Format("请选择药品剂型！");
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return FALSE;
	}

	int iFind = -1;
	BOOL bExist = FALSE;
	//检查生产厂家是否存在
	if (csVendor != _T(""))
	{
		iFind = csVendor.Find(_T("-"));
		if (iFind <= 0)
		{
			csMsg.Format("请选择正确的生产厂家！");
			MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			return FALSE;
		}
		csVendor = csVendor.GetBufferSetLength(iFind);

		CVendorDB vendorDB;
		bExist = FALSE;
		if (csVendor != _T(""))
		{
			errRet = vendorDB.CheckVendorExit(csVendor.GetBuffer(), _T(""), bExist);
			if (errRet != err_OK)
			{
				csMsg.Format(_T("添加药品失败，%s"), GetErrMsg(errRet));
				MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
				return FALSE;
			}
		}
		if (bExist ==  FALSE)
		{
			csMsg.Format(_T("添加药品失败, 生产厂家不存在，请重新选择！"));
			MessageBox(csMsg, _T("药品管理"), MB_ICONINFORMATION);
			return FALSE;
		}
	}

	//检查供应商信息
	double dbMaxSupplierPrice = 0;
	CSupplierDB supplierDB;
	for (map<LONG, SupplierMedicine*>::iterator it = m_mapVctSupplierMedicine.begin(); it != m_mapVctSupplierMedicine.end(); it++)
	{
		if (it->second == NULL)
		{
			continue;
		}

		bExist = FALSE;
		it->second->csSupplierID.Trim();
		if (it->second->csSupplierID == _T(""))
		{
			csMsg.Format(_T("供应商不能为空！"));
			MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			return FALSE;
		}

		errRet = supplierDB.CheckSupplierExist(it->second->csSupplierID.GetBuffer(), NULL, bExist);
		if (errRet != err_OK)
		{
			csMsg.Format(_T("修改药品采购信息失败，%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			return FALSE;
		}

		if (bExist !=  TRUE)
		{
			csMsg.Format(_T("供应商%s不存在"), it->second->csSupplierID.GetBuffer());
			MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			return FALSE;
		}

		if (atof(it->second->csPurPrice.GetBuffer()) > dbMaxSupplierPrice)
		{
			dbMaxSupplierPrice = atof(it->second->csPurPrice.GetBuffer());
		}
	}

	if (atof(csRetailPrice.GetBuffer()) < dbMaxSupplierPrice)
	{
		csMsg.Format(_T("零售价不能低于进价！"));
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return FALSE;
	}

	//添加或者更新药品信息
	CMedicineDB medicineDB;
	Medicine medicine;
	medicine.csID = m_medicine.csID;
	medicine.csSN = csSN;
	medicine.csName = csName;
	medicine.csSpec = csSpec;
	medicine.csVendorID = csVendor;
	medicine.csRetailPrice = csRetailPrice;
	medicine.util.csID = csUnit;
	medicine.OTC.csID = csOTC;
	medicine.type.csID = csType;
	medicine.form.csID = csForm;

	if (m_viewType != VIEW_EDIT)
	{
		errRet = medicineDB.AddMedicine(&medicine);
		if (errRet == err_Medicine_AlreadyExist)
		{
			csMsg.Format(_T("已经存在该药品，请重新输入一个新的药品编号"));
			MessageBox(csMsg, _T("药品管理"), MB_ICONINFORMATION);
			return FALSE;
		}
		if (errRet != err_OK)
		{
			csMsg.Format(_T("添加药品失败，%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			return FALSE;
		}

		errRet = medicineDB.GetMedicineBySN(medicine.csSN.GetBuffer(), &medicine);
		if (errRet != err_OK)
		{
			csMsg.Format(_T("添加药品失败，%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			return FALSE;
		}
	}
	else
	{
		errRet = medicineDB.UpdateMedicine(medicine.csID.GetBuffer(), &medicine);
		if (errRet == err_Medicine_AlreadyExist)
		{
			csMsg.Format(_T("该供应商下已经存在该药品，请重新输入一个新的药品编号或者选择其他供应商"));
			MessageBox(csMsg, _T("药品管理"), MB_ICONINFORMATION);
			return FALSE;
		}
		else if (errRet != err_OK)
		{
			csMsg.Format(_T("修改药品失败，%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			return FALSE;
		}
	}

	CSupplierMedicineDB supplierMedicineDB;
	for (map<LONG, SupplierMedicine*>::iterator it = m_mapVctDelSupplierMedicine.begin(); it != m_mapVctDelSupplierMedicine.end(); it++)
	{
		if (it->second == NULL)
		{
			continue;
		}

		bExist = FALSE;
		it->second->csID.Trim();
		if (it->second->csID != _T(""))
		{
			errRet = supplierMedicineDB.CheckSupplierMedicineExist(it->second->csID.GetBuffer(), bExist);
			if (errRet != err_OK)
			{
				csMsg.Format(_T("修改药品采购信息失败，%s"), GetErrMsg(errRet));
				MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			}
		}

		if (bExist !=  FALSE)
		{
			errRet = supplierMedicineDB.DeleteSupplierMedicine(it->second->csID.GetBuffer());
			if (errRet != err_OK)
			{
				csMsg.Format(_T("修改药品采购信息失败，%s"), GetErrMsg(errRet));
				MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			}
		}

		delete it->second;
		it->second = NULL;
	}
	m_mapVctDelSupplierMedicine.clear();

	for (map<LONG, SupplierMedicine*>::iterator it = m_mapVctSupplierMedicine.begin(); it != m_mapVctSupplierMedicine.end(); it++)
	{
		if (it->second == NULL)
		{
			continue;
		}

		it->second->medicine.csID = medicine.csID;
		bExist = FALSE;
		it->second->csID.Trim();
		if (it->second->csID != _T(""))
		{
			errRet = supplierMedicineDB.CheckSupplierMedicineExist(it->second->csID.GetBuffer(), bExist);
			if (errRet != err_OK)
			{
				csMsg.Format(_T("修改药品采购信息失败，%s"), GetErrMsg(errRet));
				MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			}
		}

		if (bExist ==  FALSE)
		{
			errRet = supplierMedicineDB.AddSupplierMedicine(it->second);
			if (errRet != err_OK)
			{
				csMsg.Format(_T("修改药品采购信息失败，%s"), GetErrMsg(errRet));
				MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			}
		}
		else
		{
			errRet = supplierMedicineDB.UpdateSupplierMedicine(it->second);
			if (errRet != err_OK)
			{
				csMsg.Format(_T("修改药品采购信息失败，%s"), GetErrMsg(errRet));
				MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			}
		}

		delete it->second;
		it->second = NULL;
	}
	m_mapVctSupplierMedicine.clear();

	return TRUE;
}


ERRCODE CMedicineAddView::GetMedicineInfoBySN(LPTSTR lpMedicineSN, Medicine *pMedicine)
{
	if (lpMedicineSN == NULL || strlen(lpMedicineSN) == 0 || pMedicine == NULL)
	{
		return err_InvalidParameter;
	}

	CMedicineDB medicineDB;
	CString csMsg;
	ERRCODE errRet = medicineDB.GetMedicineBySN(lpMedicineSN, pMedicine);
	if (errRet != err_OK)
	{
		return errRet;
	}

	return err_OK;
}


void CMedicineAddView::DisplayMedicineInfo(LPTSTR lpMedicineID)
{
	if (lpMedicineID == NULL || strlen(lpMedicineID) == 0)
	{
		return;
	}

	CMedicineDB medicineDB;
	CString csMsg;
	ERRCODE errRet = medicineDB.GetMedicine(lpMedicineID, &m_medicine);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取药品信息错误！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return;
	}

	SetDlgItemText(IDC_EDIT_MEDICINE_ID, m_medicine.csID);
	SetDlgItemText(IDC_EDIT_MEDICINE_SN, m_medicine.csSN);
	SetDlgItemText(IDC_EDIT_MEDICINE_NAME, m_medicine.csName);
	SetDlgItemText(IDC_EDIT_MEDICINE_SPEC, m_medicine.csSpec);
	csMsg.Format(_T("%0.2f"), atof(m_medicine.csRetailPrice));
	SetDlgItemText(IDC_EDIT_MEDICINE_RETAILPRICE, csMsg);

	for (unsigned int i = 0; i < m_vctMedicineUtil.size(); i++)
	{
		if (m_vctMedicineUtil[i]->csID == m_medicine.util.csID)
		{
			m_medicine.util.csName = m_vctMedicineUtil[i]->csName;
			m_cbUtil.SetCurSel(i);
			break;
		}
	}

	for (unsigned int i = 0; i < m_vctMedicineType.size(); i++)
	{
		if (m_vctMedicineType[i]->csID == m_medicine.type.csID)
		{
			m_medicine.type.csName = m_vctMedicineType[i]->csName;
			m_cbType.SetCurSel(i);
			break;
		}
	}

	for (unsigned int i = 0; i < m_vctMedicineOTC.size(); i++)
	{
		if (m_vctMedicineOTC[i]->csID == m_medicine.OTC.csID)
		{
			m_medicine.OTC.csName = m_vctMedicineOTC[i]->csName;
			m_cbOTC.SetCurSel(i);
			break;
		}
	}

	for (unsigned int i = 0; i < m_vctMedicineForm.size(); i++)
	{
		if (m_vctMedicineForm[i]->csID == m_medicine.form.csID)
		{
			m_medicine.form.csName = m_vctMedicineForm[i]->csName;
			m_cbForm.SetCurSel(i);
			break;
		}
	}

	if (m_medicine.csVendorID != _T(""))
	{
		csMsg.Format(_T("%s-%s"), m_medicine.csVendorID, m_medicine.csVendorName);
		SetDlgItemText(IDC_COMBO_MEDICINE_VENDORID, csMsg);
	}

	CSupplierDB supplierDB;
	CSupplierMedicineDB supplierMedicineDB;
	vector<SupplierMedicine*> vctSupplierMedicine;
	DWORD dwCurPage = 0;
	DWORD dwTotalPage = 0;
	DWORD dwTotalNum = 0;
	errRet = supplierMedicineDB.GetSupplierMedicines(dwCurPage, 
													g_ciNumPerPage, 
													dwTotalPage, 
													dwTotalNum, 
													vctSupplierMedicine, 
													NULL, 
													m_medicine.csSN.GetBuffer());
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取该药品的供应商信息失败！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
		return;
	}

	for (map<LONG, SupplierMedicine*>::iterator it = m_mapVctSupplierMedicine.begin(); it != m_mapVctSupplierMedicine.end(); it++)
	{
		if (it->second != NULL)
		{
			delete it->second;
			it->second = NULL;
		}
	}
	m_mapVctSupplierMedicine.clear();

	for (map<LONG, SupplierMedicine*>::iterator it = m_mapVctDelSupplierMedicine.begin(); it != m_mapVctDelSupplierMedicine.end(); it++)
	{
		if (it->second != NULL)
		{
			delete it->second;
			it->second = NULL;
		}
	}
	m_mapVctDelSupplierMedicine.clear();

	m_listSupplier.DeleteAllItems();
	for (unsigned int i = 0; i < vctSupplierMedicine.size(); i++)
	{
		m_listSupplier.InsertItem(i, _T(""), CTRL_DEFAULT);
		m_listSupplier.SetItemText(i, 1, vctSupplierMedicine[i]->csID);

		errRet = supplierDB.GetSupplier(vctSupplierMedicine[i]->csSupplierID.GetBuffer(), &m_supplier);
		if (errRet != err_OK)
		{
			csMsg.Format(_T("获取该药品的供应商信息失败！%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			csMsg.Format(_T("%s- "), m_supplier.csID);
			m_listSupplier.SetItemText(i, 2, csMsg);
		}
		else
		{
			csMsg.Format(_T("%s-%s"), m_supplier.csID, m_supplier.csName);
			m_listSupplier.SetItemText(i, 2, csMsg);
		}

		csMsg.Format(_T("%0.2f"), atof(vctSupplierMedicine[i]->csPurPrice));
		m_listSupplier.SetItemText(i, 3, csMsg);
		//m_listSupplier.SetItemText(i, 4, _T("编辑"), CTRL_BUTTON);

		if (m_mapVctSupplierMedicine.find(atol(vctSupplierMedicine[i]->csID)) == m_mapVctSupplierMedicine.end())
		{
			m_mapVctSupplierMedicine.insert(map<LONG, SupplierMedicine*>::value_type(atol(vctSupplierMedicine[i]->csSupplierID), vctSupplierMedicine[i]));
		}
		else
		{
			delete vctSupplierMedicine[i];
			vctSupplierMedicine[i] = NULL;
		}
	}
	vctSupplierMedicine.clear();

}

void CMedicineAddView::OnEnChangeEditMedicineName()
{
	if (m_bDataChanged != TRUE)
	{
		CString csName;
		GetDlgItemText(IDC_EDIT_MEDICINE_NAME, csName);
		csName.Trim();
		if (csName == m_medicine.csName)
		{
			//m_bDataChanged = FALSE;
			//GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(FALSE);
		}
		else
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(TRUE);
		}
	}
}

void CMedicineAddView::OnEnChangeEditMedicineId()
{
	if (m_bDataChanged != TRUE)
	{
			CString csID;
		GetDlgItemText(IDC_EDIT_MEDICINE_ID, csID);
		csID.Trim();
		if (csID != m_medicine.csID)
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(TRUE);
		}
	}

	// TODO:  Add your control notification handler code here
}


void CMedicineAddView::OnEnChangeEditMedicineSpec()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	if (m_bDataChanged != TRUE)
	{
		CString csSpec;
		GetDlgItemText(IDC_EDIT_MEDICINE_SPEC, csSpec);
		csSpec.Trim();
		if (csSpec != m_medicine.csSpec)
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(TRUE);
		}
	}
}


void CMedicineAddView::OnEnChangeEditMedicineRetailprice()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CEdit *pEditRetailPrice = (CEdit*)GetDlgItem(IDC_EDIT_MEDICINE_RETAILPRICE);
	CString csRetailPrice;
	pEditRetailPrice->GetWindowText(csRetailPrice);
	csRetailPrice.Trim();

	int iStart = 0; 
	int iEnd = 0; 
	pEditRetailPrice->GetSel(iStart, iEnd); 
	if (iEnd == 0) 
	{ 
		return; 
	} 

	if (csRetailPrice.GetLength() > 0) 
	{ 
		TCHAR tch = csRetailPrice.GetAt(iEnd-1); 
		if ( ((!(tch>='0' && tch<='9') && tch != '.')) 
			|| csRetailPrice.Find('.') !=  csRetailPrice.ReverseFind('.') ) 
		{ 
			int iSetPos = csRetailPrice.GetLength(); 
			csRetailPrice.Delete(iEnd-1, 1); 
			pEditRetailPrice->SetWindowText(csRetailPrice); 
			pEditRetailPrice->SetSel(iSetPos-1,iSetPos-1); 
		} 
	} 

	if (m_bDataChanged != TRUE)
	{
		if (csRetailPrice != m_medicine.csRetailPrice)
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(TRUE);
		}
	}
}


void CMedicineAddView::OnCbnEditupdateComboSupplier()
{
	CString csMsg;
	m_pSupplierListPopupCmbox->GetWindowText(m_csSubSupplierName);
	m_csSubSupplierName.Trim();

	csMsg.Format(_T("%s-%s"), m_supplier.csID, m_supplier.csName);
	if (csMsg == m_csSubSupplierName)
	{
		//m_bDataChanged = FALSE;
		//GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(FALSE);
	}
	else
	{
		m_bDataChanged = TRUE;
		GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(TRUE);
	}

	m_pSupplierListPopupCmbox->ShowDropDown(FALSE);
	m_pSupplierListPopupCmbox->ShowDropDown(TRUE);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
}


void CMedicineAddView::OnCbnEditupdateComboVendor()
{
	// TODO: Add your control notification handler code here

	CString csMsg;
	m_cbVendor.GetWindowText(m_csSubVendorName);
	m_csSubVendorName.Trim();

	csMsg.Format(_T("%s-%s"), m_vendor.csID, m_vendor.csName);
	if (csMsg == m_csSubVendorName)
	{
		//m_bDataChanged = FALSE;
		//GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(FALSE);
	}
	else
	{
		m_bDataChanged = TRUE;
		GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(TRUE);
	}

	m_cbVendor.ShowDropDown(FALSE);
	m_cbVendor.ShowDropDown(TRUE);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
}


void CMedicineAddView::OnCbnDropdownComboMedicineSupplierid()
{
	// TODO: Add your control notification handler code here

	CString csMsg;
	CSize   sz;
	int     dx = 0;
	TEXTMETRIC   tm;
	CDC*    pDC = m_pSupplierListPopupCmbox->GetDC();
	CFont*  pFont = m_pSupplierListPopupCmbox->GetFont();
	CFont* pOldFont = pDC->SelectObject(pFont);
	pDC->GetTextMetrics(&tm);

	DWORD dwCurPage = 0;
	DWORD dwTotalPage = 0;
	DWORD dwTotalNum = 0;
	CSupplierDB supplierDB;
	vector<Supplier*> vctSuppliers;
	supplierDB.GetSuppliers(dwCurPage, g_ciNumPerPage, dwTotalPage, dwTotalNum, vctSuppliers, m_csSubSupplierName.GetBuffer());

	for(int  i = m_pSupplierListPopupCmbox->GetCount() - 1;  i >= 0;  i--) 
	{ 
		m_pSupplierListPopupCmbox->DeleteString(i); 
	} 

	int iIdx = 0;
	for (unsigned int i = 0; i < vctSuppliers.size(); i++)
	{
		if (m_mapVctSupplierMedicine.find(atol(vctSuppliers[i]->csID)) == m_mapVctSupplierMedicine.end())
		{
			csMsg.Format(_T("%s-%s"), vctSuppliers[i]->csID, vctSuppliers[i]->csName);
			m_pSupplierListPopupCmbox->InsertString(iIdx++, csMsg);

			sz = pDC->GetTextExtent(csMsg);
			sz.cx += tm.tmAveCharWidth;

			if (sz.cx > dx)
				dx = sz.cx;
		}

		delete vctSuppliers[i];
		vctSuppliers[i] = NULL;
	}
	vctSuppliers.clear();

	pDC->SelectObject(pOldFont);
	m_pSupplierListPopupCmbox->ReleaseDC(pDC);
	dx += ::GetSystemMetrics(SM_CXVSCROLL) + 2*::GetSystemMetrics(SM_CXEDGE);
	m_pSupplierListPopupCmbox->SetDroppedWidth(dx);

	m_csSubSupplierName = _T("");
}


void CMedicineAddView::OnCbnDropdownComboMedicineVendorid()
{
	// TODO: Add your control notification handler code here
	CString csMsg;
	CSize   sz;
	int     dx = 0;
	TEXTMETRIC   tm;
	CDC*    pDC = m_cbVendor.GetDC();
	CFont*  pFont = m_cbVendor.GetFont();
	CFont* pOldFont = pDC->SelectObject(pFont);
	pDC->GetTextMetrics(&tm);

	DWORD dwCurPage = 0;
	DWORD dwTotalPage = 0;
	DWORD dwTotalNum = 0;
	CVendorDB vendorDB;
	vector<Vendor*> vctVendors;
	vendorDB.GetVendors(dwCurPage, g_ciNumPerPage, dwTotalPage, dwTotalNum, vctVendors, m_csSubVendorName.GetBuffer());

	for(int  i = m_cbVendor.GetCount() - 1;  i >= 0;  i--) 
	{ 
		m_cbVendor.DeleteString(i); 
	} 

	for (unsigned int i = 0; i < vctVendors.size(); i++)
	{
		csMsg.Format(_T("%s-%s"), vctVendors[i]->csID, vctVendors[i]->csName);
		m_cbVendor.InsertString(i, csMsg);

		sz = pDC->GetTextExtent(csMsg);
		sz.cx += tm.tmAveCharWidth;

		if (sz.cx > dx)
			dx = sz.cx;

		delete vctVendors[i];
		vctVendors[i] = NULL;
	}
	vctVendors.clear();
	
	pDC->SelectObject(pOldFont);
	m_cbVendor.ReleaseDC(pDC);
	dx += ::GetSystemMetrics(SM_CXVSCROLL) + 2*::GetSystemMetrics(SM_CXEDGE);
	m_cbVendor.SetDroppedWidth(dx);

	m_csSubVendorName = _T("");
}

void CMedicineAddView::OnCbnSelchangeComboMedicineSupplierid()
{
	// TODO: Add your control notification handler code here
	if (m_bDataChanged != TRUE)
	{
		CString csMsg;
		CString csSupplier;
		int iSel =  m_pSupplierListPopupCmbox->GetCurSel();
		m_pSupplierListPopupCmbox->GetLBText(iSel,csSupplier);
		csSupplier.Trim();

		csMsg.Format(_T("%s-%s"), m_supplier.csID, m_supplier.csName);
		if (csMsg == csSupplier)
		{
			//m_bDataChanged = FALSE;
			//GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(FALSE);
		}
		else
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(TRUE);
		}
	}
}

void CMedicineAddView::OnCbnSelchangeComboMedicineVendorid()
{
	// TODO: Add your control notification handler code here
	if (m_bDataChanged != TRUE)
	{
		CComboBox *pcbVendor = (CComboBox*)GetDlgItem(IDC_COMBO_MEDICINE_VENDORID);
		if (pcbVendor->GetSafeHwnd() == NULL)
		{
			return;
		}
		CString csMsg;
		CString csVendor;
		int iSel =  pcbVendor-> GetCurSel();
		pcbVendor-> GetLBText(iSel,csVendor);
		csVendor.Trim();

		csMsg.Format(_T("%s-%s"), m_vendor.csID, m_vendor.csName);
		if (csMsg == csVendor)
		{
			//m_bDataChanged = FALSE;
			//GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(FALSE);
		}
		else
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(TRUE);
		}
	}
}


void CMedicineAddView::OnEnChangeEditMedicineSn()
{
	if (m_bDataChanged != TRUE)
	{
		CString csSN;
		GetDlgItemText(IDC_EDIT_MEDICINE_SN, csSN);
		csSN.Trim();
		if (csSN != m_medicine.csSN)
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(TRUE);
		}
	}
}


void CMedicineAddView::OnCbnSelchangeComboMedicineUnit()
{
	// TODO: Add your control notification handler code here
	if (m_bDataChanged != TRUE)
	{
		CString csMsg;
		CString csUnit;
		int iSel =  m_cbUtil. GetCurSel();
		m_cbUtil.GetLBText(iSel, csUnit);
		csUnit.Trim();

		if (m_medicine.util.csName != csUnit)
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(TRUE);
		}
	}
}


void CMedicineAddView::OnCbnSelchangeComboMedicineType()
{
	// TODO: Add your control notification handler code here
	if (m_bDataChanged != TRUE)
	{
		CString csMsg;
		CString csType;
		int iSel =  m_cbType. GetCurSel();
		m_cbType.GetLBText(iSel, csType);
		csType.Trim();

		if (m_medicine.type.csName != csType)
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(TRUE);
		}
	}
}


void CMedicineAddView::OnCbnSelchangeComboMedicineOtc()
{
	// TODO: Add your control notification handler code here
	if (m_bDataChanged != TRUE)
	{
		CString csMsg;
		CString csOTC;
		int iSel =  m_cbOTC. GetCurSel();
		m_cbOTC.GetLBText(iSel, csOTC);
		csOTC.Trim();

		if (m_medicine.OTC.csName != csOTC)
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(TRUE);
		}
	}
}


void CMedicineAddView::OnCbnSelchangeComboMedicineForm()
{
	// TODO: Add your control notification handler code here
	if (m_bDataChanged != TRUE)
	{
		CString csMsg;
		CString csForm;
		int iSel =  m_cbForm. GetCurSel();
		m_cbForm.GetLBText(iSel, csForm);
		csForm.Trim();

		if (m_medicine.form.csName != csForm)
		{
			m_bDataChanged = TRUE;
			GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(TRUE);
		}
	}
}


void CMedicineAddView::OnCbnDropdownComboMedicineUnit()
{
	// TODO: Add your control notification handler code here
}


void CMedicineAddView::OnCbnDropdownComboMedicineType()
{
	// TODO: Add your control notification handler code here
}


void CMedicineAddView::OnCbnDropdownComboMedicineOtc()
{
	// TODO: Add your control notification handler code here
}


void CMedicineAddView::OnCbnDropdownComboMedicineForm()
{
	// TODO: Add your control notification handler code here
}


void CMedicineAddView::OnLvnItemchangedListSupplier(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	if (pNMLV->uOldState == 0 && pNMLV->uNewState == 0) 
	{
		// No change 
		return;	
	}
	 
	BOOL bPrevState = (BOOL)(((pNMLV->uOldState &  LVIS_STATEIMAGEMASK)>> 12)-1);  //Old check box state 
	if (bPrevState < 0)	//On startup there's no previous state   
	{
		bPrevState = 0; //so assign as false (unchecked) 
	}

	//New check box state 
	BOOL bChecked=(BOOL)(((pNMLV-> uNewState & LVIS_STATEIMAGEMASK)>>12)-1);       
	if (bChecked   <   0)   //On non-checkbox notifications assume false 
	{
		bChecked = 0;   
	}
	if (bPrevState == bChecked)//No change in check box 
	{
		return; 
	}

	m_btnDelPur.EnableWindow(bChecked);

}


void CMedicineAddView::OnBnClickedBtnSupplierMedicineDel()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csMsg;
	vector<int> vctCheckedID;
	for (int i = 0; i < m_listSupplier.GetItemCount(); i++)
	{
		if (m_listSupplier.GetCheck(i) == TRUE)
		{
			vctCheckedID.push_back(i);
		}
	}
	
	if (vctCheckedID.size() == 0)
	{
		return;
	}

	csMsg.Format(_T("确认删除选择的这%d项？"), vctCheckedID.size());
	if (IDOK != MessageBox(csMsg, _T("药品管理"), MB_OKCANCEL))
	{
		return;
	}

	ERRCODE errRet = err_OK;
	CSupplierMedicineDB supplierMedicineDB;
	map<LONG, SupplierMedicine*>::iterator it, deleteIt;
	SupplierMedicine *pSupplierMedicine = NULL;
	int iFind = -1;

	for (int i = (int)vctCheckedID.size() - 1; i >= 0; i--)
	{
/*
		csMsg = m_listSupplier.GetItemText(vctCheckedID[i], 1);
		errRet = supplierMedicineDB.DeleteSupplierMedicine(atol(csMsg));
		if (errRet != err_OK)
		{
			continue;
		}*/

		csMsg = m_listSupplier.GetItemText(vctCheckedID[i], 2);

		iFind = csMsg.Find(_T("-"));
		if (iFind > 0)
		{
			csMsg = csMsg.GetBufferSetLength(iFind);
			it = m_mapVctSupplierMedicine.find(atol(csMsg));
			if (it != m_mapVctSupplierMedicine.end())
			{
				pSupplierMedicine = it->second;
				m_mapVctSupplierMedicine.erase(it);

				deleteIt = m_mapVctDelSupplierMedicine.find(atol(csMsg));
				if (deleteIt != m_mapVctDelSupplierMedicine.end())
				{
					if (deleteIt->second != NULL)
					{
						delete deleteIt->second;
						deleteIt->second = NULL;
					}
					deleteIt->second = pSupplierMedicine;
				}
				else
				{
					m_mapVctDelSupplierMedicine.insert(map<LONG, SupplierMedicine*>::value_type(atol(csMsg), pSupplierMedicine));
				}
			}
		}

		m_listSupplier.DeleteItem(vctCheckedID[i]);
	}
	vctCheckedID.clear();

	m_bDataChanged = TRUE;
	GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(TRUE);
}


void CMedicineAddView::OnBnClickedBtnSupplierMedicineAdd()
{
	// TODO: 在此添加控件通知处理程序代码

	int iItem = m_listSupplier.GetItemCount();
	CString csMsg;
	
	m_listSupplier.InsertItem(iItem, _T(""), CTRL_STATIC);

	csMsg.Format(_T("确认"));
	m_listSupplier.SetItemText(iItem, 4, csMsg, CTRL_BUTTON);
	csMsg.Format(_T("取消"));
	m_listSupplier.SetItemText(iItem, 5, csMsg, CTRL_BUTTON);

	m_btnAddPur.EnableWindow(FALSE);
}


void CMedicineAddView::OnNMClickListSupplier(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CString csMsg;
	POINT pt;
	GetCursorPos(&pt);
	m_listSupplier.ScreenToClient(&pt);
	LVHITTESTINFO hitInfo;
	hitInfo.pt=pt;
	m_listSupplier.SubItemHitTest(&hitInfo);

	if(hitInfo.flags & LVHT_ONITEMLABEL)//判断是否单击在文本上
	{
		CRect rect;
		m_iSupplierListItem = hitInfo.iItem;
		m_iSupplierListSubItem = hitInfo.iSubItem;

		m_listSupplier.GetSubItemRect(m_iSupplierListItem, m_iSupplierListSubItem, LVIR_BOUNDS, rect);
		rect.InflateRect(0,0,0,-1);

		if (m_iSupplierListSubItem == 2)
		{
			csMsg = m_listSupplier.GetItemText(m_iSupplierListItem, 4);
			csMsg.Trim();
			if (csMsg == _T("确认"))
			{
				csMsg = m_listSupplier.GetItemText(m_iSupplierListItem, m_iSupplierListSubItem);

				m_pSupplierListPopupCmbox->MoveWindow(&rect,TRUE);
				m_pSupplierListPopupCmbox->ShowWindow(SW_SHOW);
				m_pSupplierListPopupCmbox->SetWindowText(csMsg);
				m_pSupplierListPopupCmbox->BringWindowToTop();
				m_pSupplierListPopupCmbox->SetFocus();//使组合框聚焦
				//m_pSupplierListPopupCmbox->CreateSolidCaret(1,rect.Height()-3);//创建一个光标
				//m_pSupplierListPopupCmbox->ShowCaret();//显示光标
				//m_pSupplierListPopupCmbox->SetSel(0);//使光标移到最后面
			}
		}
		else if (m_iSupplierListSubItem == 3)
		{
			csMsg = m_listSupplier.GetItemText(m_iSupplierListItem, m_iSupplierListSubItem);

			m_pSupplierListPopupEdit->MoveWindow(&rect,TRUE);
			m_pSupplierListPopupEdit->ShowWindow(SW_SHOW);
			m_pSupplierListPopupEdit->SetWindowText(csMsg);
			m_pSupplierListPopupEdit->BringWindowToTop();
			m_pSupplierListPopupEdit->SetFocus();//使组合框聚焦
			//m_pSupplierListPopupEdit->CreateSolidCaret(1,rect.Height()-3);//创建一个光标
			//m_pSupplierListPopupEdit->ShowCaret();//显示光标
			//m_pSupplierListPopupEdit->SetSel(0);//使光标移到最后面
		}
	}
}

void CMedicineAddView::OnLvnEndScrollListSupplier(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 此功能要求 Internet Explorer 5.5 或更高版本。
	// 符号 _WIN32_IE 必须是 >= 0x0560。
	LPNMLVSCROLL pStateChanged = reinterpret_cast<LPNMLVSCROLL>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CString csMsg;
	if (m_iSupplierListItem != -1)
	{
		CRect rect;
		m_listSupplier.GetSubItemRect(m_iSupplierListItem, m_iSupplierListSubItem, LVIR_BOUNDS, rect);
		rect.InflateRect(0,0,0,-1);

		if (m_iSupplierListSubItem == 2)
		{
			csMsg = m_listSupplier.GetItemText(m_iSupplierListItem, m_iSupplierListSubItem);

			m_pSupplierListPopupCmbox->MoveWindow(&rect,TRUE);
			m_pSupplierListPopupCmbox->ShowWindow(SW_SHOW);
			m_pSupplierListPopupCmbox->SetWindowText(csMsg);
			m_pSupplierListPopupCmbox->BringWindowToTop();
			m_pSupplierListPopupCmbox->SetFocus();//使组合框聚焦
			//m_pSupplierListPopupCmbox->CreateSolidCaret(1,rect.Height()-3);//创建一个光标
			//m_pSupplierListPopupCmbox->ShowCaret();//显示光标
			//m_pSupplierListPopupCmbox->SetSel(0);//使光标移到最后面
		}
		if (m_iSupplierListSubItem == 3)
		{
			csMsg = m_listSupplier.GetItemText(m_iSupplierListItem, m_iSupplierListSubItem);

			m_pSupplierListPopupEdit->MoveWindow(&rect,TRUE);
			m_pSupplierListPopupEdit->ShowWindow(SW_SHOW);
			m_pSupplierListPopupEdit->SetWindowText(csMsg);
			m_pSupplierListPopupEdit->BringWindowToTop();
			m_pSupplierListPopupEdit->SetFocus();//使组合框聚焦
			//m_pSupplierListPopupEdit->CreateSolidCaret(1,rect.Height()-3);//创建一个光标
			//m_pSupplierListPopupEdit->ShowCaret();//显示光标
			//m_pSupplierListPopupEdit->SetSel(0);//使光标移到最后面
		}
	}
}

void CMedicineAddView::OnCbnKillfocusPopupEdit()
{
	// TODO: 在此添加控件通知处理程序代码

	CString csMsg, csPurPrice;
	int iListItem = -1;
	double dbTotalPrice = 0;
	CRect rect;
	m_pSupplierListPopupEdit->GetWindowRect(&rect);

	if (m_iSupplierListItem != -1 && m_iSupplierListSubItem != 1)
	{
		m_pSupplierListPopupEdit->GetWindowText(csMsg);
		csMsg.Trim();

		if (m_iSupplierListSubItem == 3)
		{
			if (csMsg != _T(""))
			{
				csPurPrice.Format(_T("%0.2f"), atof(csMsg));
			}
			m_listSupplier.SetItemText(m_iSupplierListItem, m_iSupplierListSubItem, csPurPrice);

			csMsg = m_listSupplier.GetItemText(m_iSupplierListItem, 2);
			map<LONG, SupplierMedicine*>::iterator it;
			int iFind = csMsg.Find(_T("-"));
			if (iFind > 0)
			{
				csMsg = csMsg.GetBufferSetLength(iFind);
				it = m_mapVctSupplierMedicine.find(atol(csMsg));
				if (it != m_mapVctSupplierMedicine.end())
				{
					if (it->second->csPurPrice != csPurPrice)
					{
						it->second->csPurPrice = csPurPrice;
						m_bDataChanged = TRUE;
						GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(TRUE);
					}
				}
			}
		}
	}

	m_iSupplierListItem = -1;
	m_iSupplierListSubItem = -1;
	m_pSupplierListPopupEdit->ShowWindow(SW_HIDE);

	//InvalidateRect(&rect);
}

void CMedicineAddView::OnCbnKillfocusPopupCombox()
{
	// TODO: 在此添加控件通知处理程序代码

	CString csMsg, csSupplierID;
	int iListItem = -1;
	double dbTotalPrice = 0;
	CRect rect;
	m_pSupplierListPopupCmbox->GetWindowRect(&rect);

	if (m_iSupplierListItem != -1 && m_iSupplierListSubItem != 1)
	{
		m_pSupplierListPopupCmbox->GetWindowText(csMsg);
		
		switch (m_iSupplierListSubItem)
		{
		case 2:
			int iFind = csMsg.Find(_T("-"));
			if (iFind <= 0)
			{
				break;
			}
			csSupplierID = csMsg.GetBufferSetLength(iFind);

			BOOL bExist = FALSE;
			CSupplierDB supplierDB;
			Supplier supplier;
			if (supplierDB.GetSupplier(csSupplierID.GetBuffer(), &supplier) != err_OK)
			{
				break;
			}

			csMsg.Format(_T("%s-%s"), supplier.csID, supplier.csName);
			m_listSupplier.SetItemText(m_iSupplierListItem, m_iSupplierListSubItem, csMsg);
			break;
		}
	}

	m_iSupplierListItem = -1;
	m_iSupplierListSubItem = -1;
	m_pSupplierListPopupCmbox->ShowWindow(SW_HIDE);

	InvalidateRect(&rect);
}

void CMedicineAddView::OnListBtnClicked(LVHITTESTINFO *pHitInfo)
{
	if (pHitInfo == NULL ||
		pHitInfo->iItem < 0 || 
		pHitInfo->iItem >= m_listSupplier.GetItemCount())
	{
		return;
	}
	
	ERRCODE errRet = err_OK;
	map<LONG, SupplierMedicine*>::iterator it;

	CString csMsg = m_listSupplier.GetItemText(pHitInfo->iItem, pHitInfo->iSubItem);
	csMsg.Trim();

	if (pHitInfo->iSubItem == 4 && csMsg == _T("确认"))
	{
		CString csSupplier, csPurPrice;
		csSupplier = m_listSupplier.GetItemText(pHitInfo->iItem, 2);
		csPurPrice = m_listSupplier.GetItemText(pHitInfo->iItem, 3);

		csSupplier.Trim();
		csPurPrice.Trim();

		//检查供应商是否存在
		if (csSupplier == _T(""))
		{
			csMsg.Format("供应商不能为空！");
			MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			return;
		}
		int iFind = csSupplier.Find(_T("-"));
		if (iFind <= 0)
		{
			csMsg.Format("请选择正确的供应商！");
			MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			return;
		}
		csSupplier = csSupplier.GetBufferSetLength(iFind);

		BOOL bExist;
		CSupplierDB supplierDB;
		errRet = supplierDB.CheckSupplierExist(csSupplier.GetBuffer(), "", bExist);
		if (errRet != err_OK)
		{
			csMsg.Format(_T("添加药品信息失败，%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			return;
		}
		if (bExist ==  FALSE)
		{
			csMsg.Format(_T("添加药品失败, 供应商不存在，请重新选择！"));
			MessageBox(csMsg, _T("药品管理"), MB_ICONINFORMATION);
			return;
		}

		//进价是否为空
		if (csPurPrice == _T(""))
		{
			csMsg.Format("请填写进货价格！");
			MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			return;
		}

		//
		CSupplierMedicineDB supplierMedicineDB;
		errRet = supplierMedicineDB.CheckSupplierMedicineExist(m_medicine.csID.GetBuffer(), csSupplier.GetBuffer(), bExist);
		if (errRet != err_OK)
		{
			csMsg.Format(_T("添加药品信息失败，%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			return;
		}
		if (bExist ==  TRUE)
		{
			csMsg.Format(_T("添加药品失败, 该供应商已经存在该药品，请重新选择！"));
			MessageBox(csMsg, _T("药品管理"), MB_ICONINFORMATION);
			return;
		}

		SupplierMedicine *pSupplierMedicine = new SupplierMedicine;
		pSupplierMedicine->csSupplierID = csSupplier;
		pSupplierMedicine->csPurPrice = csPurPrice;
		pSupplierMedicine->medicine.csID = m_medicine.csID;

		//
		m_listSupplier.SetItemText(pHitInfo->iItem, 0, _T(""), CTRL_DEFAULT);
		m_listSupplier.SetItemText(pHitInfo->iItem, 4, _T(""));
		m_listSupplier.SetItemText(pHitInfo->iItem, 5, _T(""));

		it = m_mapVctSupplierMedicine.find(atol(csSupplier));
		if (it == m_mapVctSupplierMedicine.end())
		{
			m_mapVctSupplierMedicine.insert(map<LONG, SupplierMedicine*>::value_type(atol(csSupplier), pSupplierMedicine));
		}
		else
		{
			delete pSupplierMedicine;
			pSupplierMedicine = NULL;
		}

		it = m_mapVctDelSupplierMedicine.find(atol(csSupplier));
		if (it != m_mapVctDelSupplierMedicine.end())
		{
			if (it->second != NULL)
			{
				delete it->second;
				it->second = NULL;
			}
			m_mapVctDelSupplierMedicine.erase(it);
		}

		m_btnAddPur.EnableWindow(TRUE);
	}
	else if (pHitInfo->iSubItem == 4 && csMsg == _T("编辑"))
	{
		m_listSupplier.SetItemText(pHitInfo->iItem, 4, _T("确定"), CTRL_BUTTON);
		m_listSupplier.SetItemText(pHitInfo->iItem, 5, _T("取消"), CTRL_BUTTON);
	}
	else if (pHitInfo->iSubItem == 5)
	{
		m_listSupplier.DeleteItem(pHitInfo->iItem);
		m_btnAddPur.EnableWindow(TRUE);
	}
}

void CMedicineAddView::OnBnClickedBtnVendorAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return;
	}
	pDoc->m_viewType = VIEW_NEW;

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMain == NULL)
	{
		return;
	}

	if (!SaveDataToDoc())
	{
		return;
	}

	m_bDataChanged = FALSE;
	TreeMenuID leftPanelID = TREE_VENDOR_ADD;
	pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
}

BOOL CMedicineAddView::SaveDataToDoc()
{
	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return FALSE;
	}

	if (pDoc->m_pMedicAddViewContext == NULL)
	{
		pDoc->m_pMedicAddViewContext = new MEDICINEADDVIEW_CONTEXT;
		if (pDoc->m_pMedicAddViewContext == NULL)
		{
			return FALSE;
		}
	}
	pDoc->m_pMedicAddViewContext->viewType = m_viewType;
	MEDICINEADDVIEW_CONTEXT *pMedicAddViewContext = pDoc->m_pMedicAddViewContext;
	Medicine &medicine = pMedicAddViewContext->medicine;

	ERRCODE errRet = err_OK;
	CString csMsg;
	CString csSN, csName, csSpec,csVendor, csRetailPrice, csUnit, csType, csOTC, csForm;
	GetDlgItemText(IDC_EDIT_MEDICINE_SN, csSN);
	GetDlgItemText(IDC_EDIT_MEDICINE_NAME, csName);
	GetDlgItemText(IDC_EDIT_MEDICINE_SPEC, csSpec);
	GetDlgItemText(IDC_COMBO_MEDICINE_VENDORID, csVendor);
	GetDlgItemText(IDC_EDIT_MEDICINE_RETAILPRICE, csRetailPrice);

	unsigned int iCurSel = m_cbUtil.GetCurSel();
	if (iCurSel < m_vctMedicineUtil.size())
	{
		csUnit = m_vctMedicineUtil[iCurSel]->csID;
	}
	iCurSel = m_cbType.GetCurSel();
	if (iCurSel < m_vctMedicineType.size())
	{
		csType = m_vctMedicineType[iCurSel]->csID;
	}
	iCurSel = m_cbOTC.GetCurSel();
	if (iCurSel < m_vctMedicineOTC.size())
	{
		csOTC = m_vctMedicineOTC[iCurSel]->csID;
	}
	iCurSel = m_cbForm.GetCurSel();
	if (iCurSel < m_vctMedicineForm.size())
	{
		csForm = m_vctMedicineForm[iCurSel]->csID;
	}

	csSN.Trim();
	csName.Trim();
	csSpec.Trim();
	csVendor.Trim();
	csRetailPrice.Trim();
	csUnit.Trim();
	csType.Trim();
	csOTC.Trim();
	csForm.Trim();

	int iFind = -1;
	BOOL bExist = FALSE;
	//检查生产厂家是否存在
	if (csVendor != _T(""))
	{
		iFind = csVendor.Find(_T("-"));
		if (iFind > 0)
		{
			csVendor = csVendor.GetBufferSetLength(iFind);

			CVendorDB vendorDB;
			bExist = FALSE;
			if (csVendor != _T(""))
			{
				errRet = vendorDB.CheckVendorExit(csVendor.GetBuffer(), _T(""), bExist);
				if (errRet == err_OK && bExist == TRUE)
				{
					medicine.csVendorID = csVendor;
				}
			}
		}
	}

	medicine.csID = m_medicine.csID;
	medicine.csSN = csSN;
	medicine.csName = csName;
	medicine.csSpec = csSpec;
	medicine.csRetailPrice = csRetailPrice;
	medicine.util.csID = csUnit;
	medicine.OTC.csID = csOTC;
	medicine.type.csID = csType;
	medicine.form.csID = csForm;

	pMedicAddViewContext->mapVctSupplierMedicine = m_mapVctSupplierMedicine;
	m_mapVctSupplierMedicine.clear();
	pMedicAddViewContext->mapVctDelSupplierMedicine = m_mapVctDelSupplierMedicine;
	m_mapVctDelSupplierMedicine.clear();

	return TRUE;
}


BOOL CMedicineAddView::LoadDataFromDoc()
{
	ERRCODE errRet = err_OK;
	CString csMsg;
	CSupplierDB supplierDB;
	int iListItem = -1;
	DOUBLE dbTotalPrice = 0;

	MEDICINEADDVIEW_CONTEXT *pMedicAddViewContext = NULL;
	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return FALSE;
	}

	pMedicAddViewContext = pDoc->m_pMedicAddViewContext;
	if (pMedicAddViewContext == NULL)
	{
		return TRUE;
	}

	m_viewType = pDoc->m_pMedicAddViewContext->viewType;

	m_medicine = pMedicAddViewContext->medicine;

	SetDlgItemText(IDC_EDIT_MEDICINE_ID, m_medicine.csID);
	SetDlgItemText(IDC_EDIT_MEDICINE_SN, m_medicine.csSN);
	SetDlgItemText(IDC_EDIT_MEDICINE_NAME, m_medicine.csName);
	SetDlgItemText(IDC_EDIT_MEDICINE_SPEC, m_medicine.csSpec);
	SetDlgItemText(IDC_EDIT_MEDICINE_RETAILPRICE, m_medicine.csRetailPrice);

	for (unsigned int i = 0; i < m_vctMedicineUtil.size(); i++)
	{
		if (m_vctMedicineUtil[i]->csID == m_medicine.util.csID)
		{
			m_medicine.util.csName = m_vctMedicineUtil[i]->csName;
			m_cbUtil.SetCurSel(i);
			break;
		}
	}

	for (unsigned int i = 0; i < m_vctMedicineType.size(); i++)
	{
		if (m_vctMedicineType[i]->csID == m_medicine.type.csID)
		{
			m_medicine.type.csName = m_vctMedicineType[i]->csName;
			m_cbType.SetCurSel(i);
			break;
		}
	}

	for (unsigned int i = 0; i < m_vctMedicineOTC.size(); i++)
	{
		if (m_vctMedicineOTC[i]->csID == m_medicine.OTC.csID)
		{
			m_medicine.OTC.csName = m_vctMedicineOTC[i]->csName;
			m_cbOTC.SetCurSel(i);
			break;
		}
	}

	for (unsigned int i = 0; i < m_vctMedicineForm.size(); i++)
	{
		if (m_vctMedicineForm[i]->csID == m_medicine.form.csID)
		{
			m_medicine.form.csName = m_vctMedicineForm[i]->csName;
			m_cbForm.SetCurSel(i);
			break;
		}
	}

	CVendorDB vendorDB;
	errRet = vendorDB.GetVendor(m_medicine.csVendorID.GetBuffer(), &m_vendor);
	if (errRet == err_OK)
	{
		csMsg.Format(_T("%s-%s"), m_vendor.csID, m_vendor.csName);
		SetDlgItemText(IDC_COMBO_MEDICINE_VENDORID, csMsg);
	}
	
	m_mapVctSupplierMedicine = pMedicAddViewContext->mapVctSupplierMedicine;
	pMedicAddViewContext->mapVctSupplierMedicine.clear();
	m_mapVctDelSupplierMedicine = pMedicAddViewContext->mapVctDelSupplierMedicine;
	pMedicAddViewContext->mapVctDelSupplierMedicine.clear();
	m_listSupplier.DeleteAllItems();
	int nItem = 0;
	for (map<LONG, SupplierMedicine*>::iterator it = m_mapVctSupplierMedicine.begin(); it != m_mapVctSupplierMedicine.end(); it++, nItem++)
	{
		if (it->second == NULL)
		{
			continue;
		}

		m_listSupplier.InsertItem(nItem, _T(""), CTRL_DEFAULT);
		m_listSupplier.SetItemText(nItem, 1, it->second->csID);

		errRet = supplierDB.GetSupplier(it->second->csSupplierID.GetBuffer(), &m_supplier);
		if (errRet != err_OK)
		{
			csMsg.Format(_T("获取该药品的供应商信息失败！%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("药品管理"), MB_ICONERROR);
			csMsg.Format(_T("%s- "), m_supplier.csID);
			m_listSupplier.SetItemText(nItem, 2, csMsg);
		}
		else
		{
			csMsg.Format(_T("%s-%s"), m_supplier.csID, m_supplier.csName);
			m_listSupplier.SetItemText(nItem, 2, csMsg);
		}

		csMsg.Format(_T("%0.2f"), atof(it->second->csPurPrice));
		m_listSupplier.SetItemText(nItem, 3, csMsg);
		//m_listSupplier.SetItemText(i, 4, _T("编辑"), CTRL_BUTTON);
	}

	delete pDoc->m_pMedicAddViewContext;
	pDoc->m_pMedicAddViewContext = NULL;

	m_bDataChanged = TRUE;
	GetDlgItem(IDC_BUTTON_MEDICINE_ADD_OK)->EnableWindow(TRUE);

	return TRUE;
}
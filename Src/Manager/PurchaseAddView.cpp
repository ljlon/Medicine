// PurchaseAddView.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "PurchaseAddView.h"
#include "MainFrm.h"
#include "PurchaseDB.h"
#include "MedicineBatchDB.h"

// CPurchaseAddView

IMPLEMENT_DYNCREATE(CPurchaseAddView, CFormView)

CPurchaseAddView::CPurchaseAddView()
	: CFormView(CPurchaseAddView::IDD)
{
	m_pPurListPopupEdit = NULL;
	m_pDataTimeCtrl = NULL;
	m_pCbPopupBox = NULL;
	m_iPurListItem = -1;
	m_iPurListSubItem = -1;
}

CPurchaseAddView::~CPurchaseAddView()
{
	if (m_pPurListPopupEdit != NULL)
	{
		delete m_pPurListPopupEdit;
		m_pPurListPopupEdit = NULL;
	}

	if (m_pDataTimeCtrl != NULL)
	{
		delete m_pDataTimeCtrl;
		m_pDataTimeCtrl = NULL;
	}

	if (m_pCbPopupBox != NULL)
	{
		delete m_pCbPopupBox;
		m_pCbPopupBox = NULL;
	}
}

void CPurchaseAddView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PURCHASE, m_purchaseList);
	DDX_Control(pDX, IDC_BUTTON_OK, m_btnOK);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_EDIT_SN, m_editSN);
}

BEGIN_MESSAGE_MAP(CPurchaseAddView, CFormView)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SUPPLIER_ADD, &CPurchaseAddView::OnBnClickedButtonSupplierAdd)
	ON_CBN_EDITUPDATE(IDC_COMBO_SUPPLIER, &CPurchaseAddView::OnCbnEditupdateComboSupplier)
	ON_CBN_DROPDOWN(IDC_COMBO_SUPPLIER, &CPurchaseAddView::OnCbnDropdownComboSupplier)
	ON_CBN_SELCHANGE(IDC_COMBO_SUPPLIER, &CPurchaseAddView::OnCbnSelchangeComboSupplier)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PURCHASE, &CPurchaseAddView::OnNMClickListPurchase)
	ON_EN_KILLFOCUS(IDC_EDIT_POPUP, &CPurchaseAddView::OnCbnKillfocusPopupEdit)
	ON_EN_CHANGE(IDC_EDIT_POPUP, &CPurchaseAddView::OnEnChangeEditPopup)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PURCHASE, &CPurchaseAddView::OnNMRClickListPurchase)
	ON_COMMAND(ID_PURLIST_DELONEROW, &CPurchaseAddView::OnPurlistDelOneLine)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CPurchaseAddView::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CPurchaseAddView::OnBnClickedButtonCancel)
	ON_NOTIFY(NM_KILLFOCUS, IDC_DATETIMEPICKER, &CPurchaseAddView::OnNMKillfocusDatetime)
	ON_CBN_KILLFOCUS(IDC_CB_POPUP, &CPurchaseAddView::OnCbnKillfocusCbPopup)
	ON_CBN_SELCHANGE(IDC_CB_POPUP, &CPurchaseAddView::OnCbnSelchangeCbPopup)
	ON_CBN_DROPDOWN(IDC_CB_POPUP, &CPurchaseAddView::OnCbnDropdownCbPopup)
	ON_CBN_EDITUPDATE(IDC_CB_POPUP, &CPurchaseAddView::OnCbnEditupdateCbPopup)
END_MESSAGE_MAP()


// CPurchaseMgrView 诊断

#ifdef _DEBUG
void CPurchaseAddView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPurchaseAddView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPurchaseMgrView 消息处理程序
void CPurchaseAddView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	ERRCODE errRet = err_OK;
	CString csMsg;
	csMsg.Format("%s-%s", APP_NAME, APP_MANAGER);
	AfxGetApp()->GetMainWnd()->SetWindowText(csMsg);

	m_purchaseList.SetExtendedStyle(LVS_EX_FLATSB    // 扁平风格滚动
									| LVS_EX_HEADERDRAGDROP    // 允许标题拖拽
									| LVS_EX_FULLROWSELECT    // 允许整行选中
									//| LVS_EX_GRIDLINES    // 画出网格线
									);

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
		m_purchaseList.SetFont(pFont);
	}

	int iIdx = 0;
	m_purchaseList.InsertColumn(iIdx++, "行号", LVCFMT_LEFT, 60, 0);
	m_purchaseList.InsertColumn(iIdx++, "药品编号", LVCFMT_LEFT, 0, 0);
	m_purchaseList.InsertColumn(iIdx++, "药品编码", LVCFMT_LEFT, 150, 0);
	m_purchaseList.InsertColumn(iIdx++, "药品名称", LVCFMT_LEFT, 150, 0);
	m_purchaseList.InsertColumn(iIdx++, "批号", LVCFMT_LEFT, 120, 0);
	m_purchaseList.InsertColumn(iIdx++, "生产日期", LVCFMT_LEFT, 80, 0);
	m_purchaseList.InsertColumn(iIdx++, "有效期至", LVCFMT_LEFT, 80, 0);
	m_purchaseList.InsertColumn(iIdx++, "进价", LVCFMT_LEFT, 80, 0);
	m_purchaseList.InsertColumn(iIdx++, "数量", LVCFMT_LEFT, 80, 0);
	m_purchaseList.InsertColumn(iIdx++, "单位", LVCFMT_LEFT, 80, 0);
	m_purchaseList.InsertColumn(iIdx++, "金额", LVCFMT_LEFT, 80, 0);

	m_pPurListPopupEdit = new CEdit;
	m_pPurListPopupEdit->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP , CRect(0,0,0,0), this, IDC_EDIT_POPUP);
	m_pPurListPopupEdit->ShowWindow(SW_HIDE);
	m_pPurListPopupEdit->SetParent(&m_purchaseList);

	m_pDataTimeCtrl = new CDateTimeCtrl;
	m_pDataTimeCtrl->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP , CRect(0,0,0,0), this, IDC_DATETIMEPICKER);
	m_pDataTimeCtrl->ShowWindow(SW_HIDE);
	m_pDataTimeCtrl->SetParent(&m_purchaseList);

	m_pCbPopupBox = new CComboBox;
	m_pCbPopupBox->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|CBS_DROPDOWN|WS_VSCROLL, CRect(0,0,0,0), this, IDC_CB_POPUP);
	m_pCbPopupBox->ShowWindow(SW_HIDE);
	m_pCbPopupBox->SetParent(&m_purchaseList);

	m_purchaseList.EnableWindow(FALSE);
	m_editSN.EnableWindow(FALSE);
	m_btnOK.EnableWindow(FALSE);
	m_btnCancel.EnableWindow(FALSE);

	LoadDataFromDoc();
}


BOOL CPurchaseAddView::PreTranslateMessage(MSG* pMsg)
{
	BOOL bRet = CFormView::PreTranslateMessage(pMsg);

	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			CString csSN;
			CWnd *pWnd = GetFocus();
			if (pWnd == m_pPurListPopupEdit)
			{
				m_pPurListPopupEdit->ShowWindow(FALSE);
			}
			else if (pWnd == m_pDataTimeCtrl)
			{
				
			}
			else if (m_pCbPopupBox->IsWindowVisible())
			{
				OnCbnKillfocusCbPopup();
			}
			else
			{
				m_editSN.GetWindowText(csSN);
				csSN.Trim();
				if (csSN != _T(""))
				{
					AddOneLine(csSN.GetBuffer());
				}
			}
		}
		else if ((pMsg->wParam <= '9' && pMsg->wParam >= '0') ||
			(pMsg->wParam <= 'Z' && pMsg->wParam >= 'A') ||
			(pMsg->wParam <= 'z' && pMsg->wParam >= 'a'))
		{
			CString csSN;
			CWnd *pWnd = GetFocus();
			if (pWnd != m_pPurListPopupEdit && 
				pWnd != m_pDataTimeCtrl && 
				!m_pCbPopupBox->IsWindowVisible() &&
				pWnd != GetDlgItem(IDC_COMBO_SUPPLIER) && 
				pWnd != &m_editSN)
			{
				m_editSN.GetWindowText(csSN);
				csSN.Trim();
				csSN.AppendChar(pMsg->wParam);
				m_editSN.SetWindowText(csSN);
				m_editSN.SetFocus();
				m_editSN.SetSel(csSN.GetLength(), csSN.GetLength());
			}
		}
	}  

	return bRet;
}


void CPurchaseAddView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CPurchaseAddView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	CRichListCtrl *pPurchaseList = (CRichListCtrl*)GetDlgItem(IDC_LIST_PURCHASE);
	if (pPurchaseList->GetSafeHwnd() != NULL)
	{
		pPurchaseList->SetWindowPos(NULL, rectClient.left + 5, rectClient.top + 57, rectClient.Width() - 10, rectClient.Height() - (57 + 100), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CStatic *pStaticGroup = (CStatic*)GetDlgItem(IDC_STATIC_GROUP);
	if (pStaticGroup->GetSafeHwnd() != NULL)
	{
		pStaticGroup->SetWindowPos(NULL, rectClient.left + 5, rectClient.top + 50, rectClient.Width() - 10, rectClient.Height() - (5 + 50 + 50), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CStatic *pStaticSN = (CStatic*)GetDlgItem(IDC_STATIC_SN);
	if (pStaticSN->GetSafeHwnd() != NULL)
	{
		pStaticSN->SetWindowPos(NULL, rectClient.left + 10, rectClient.bottom - 85, 70, 24, SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CEdit *pEditSn = (CEdit*)GetDlgItem(IDC_EDIT_SN);
	if (pEditSn->GetSafeHwnd() != NULL)
	{
		pEditSn->SetWindowPos(NULL, rectClient.left + 10 + 70, rectClient.bottom - 90, 200, 24, SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CButton *pBtnOK = (CButton*)GetDlgItem(IDC_BUTTON_OK);
	if (pBtnOK->GetSafeHwnd() != NULL)
	{
		pBtnOK->SetWindowPos(NULL, rectClient.left + 10, rectClient.bottom - 40, 100, 24, SWP_NOACTIVATE | SWP_NOZORDER);
	}
	CButton *pBtnCancel = (CButton*)GetDlgItem(IDC_BUTTON_CANCEL);
	if (pBtnCancel->GetSafeHwnd() != NULL)
	{
		pBtnCancel->SetWindowPos(NULL, rectClient.left + 10 + 100 + 10, rectClient.bottom - 40, 100, 24, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}


void CPurchaseAddView::OnDestroy()
{
	SaveDataToDoc();

	CFormView::OnDestroy();
}


void CPurchaseAddView::OnBnClickedButtonSupplierAdd()
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


void CPurchaseAddView::OnCbnEditupdateComboSupplier()
{
	CComboBox *pcbSupplier = (CComboBox*)GetDlgItem(IDC_COMBO_SUPPLIER);
	if (pcbSupplier->GetSafeHwnd() == NULL)
	{
		return;
	}

	CString csMsg;
	pcbSupplier->GetWindowText(m_csSubSupplierName);
	m_csSubSupplierName.Trim();

	pcbSupplier->ShowDropDown(FALSE);
	pcbSupplier->ShowDropDown(TRUE);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
}


void CPurchaseAddView::OnCbnDropdownComboSupplier()
{
	// TODO: Add your control notification handler code here
	CComboBox *pcbSupplier = (CComboBox*)GetDlgItem(IDC_COMBO_SUPPLIER);
	if (pcbSupplier->GetSafeHwnd() == NULL)
	{
		return;
	}

	CString csMsg;
	CSize   sz;
	int     dx = 0;
	TEXTMETRIC   tm;
	CDC*    pDC = pcbSupplier->GetDC();
	CFont*  pFont = pcbSupplier->GetFont();
	CFont* pOldFont = pDC->SelectObject(pFont);
	pDC->GetTextMetrics(&tm);

	DWORD dwCurPage = 0;
	DWORD dwTotalPage = 0;
	DWORD dwTotalNum = 0;
	CSupplierDB supplierDB;
	vector<Supplier*> vctSuppliers;
	supplierDB.GetSuppliers(dwCurPage, 
							g_ciNumPerPage, 
							dwTotalPage, 
							dwTotalNum, 
							vctSuppliers, 
							m_csSubSupplierName.GetBuffer());

	for(int  i = pcbSupplier->GetCount() - 1;  i >= 0;  i--) 
	{ 
		pcbSupplier->DeleteString(i); 
	} 

	for (unsigned int i = 0; i < vctSuppliers.size(); i++)
	{
		csMsg.Format(_T("%s-%s"), vctSuppliers[i]->csID, vctSuppliers[i]->csName);
		pcbSupplier->InsertString(i, csMsg);

		sz = pDC->GetTextExtent(csMsg);
		sz.cx += tm.tmAveCharWidth;
		if (sz.cx > dx)
			dx = sz.cx;

		delete vctSuppliers[i];
		vctSuppliers[i] = NULL;
	}
	vctSuppliers.clear();

	pDC->SelectObject(pOldFont);
	pcbSupplier->ReleaseDC(pDC);
	dx += ::GetSystemMetrics(SM_CXVSCROLL) + 2*::GetSystemMetrics(SM_CXEDGE);
	pcbSupplier->SetDroppedWidth(dx);

	m_csSubSupplierName = _T("");
}


void CPurchaseAddView::OnCbnSelchangeComboSupplier()
{
	// TODO: Add your control notification handler code here

	CComboBox *pcbSupplier = (CComboBox*)GetDlgItem(IDC_COMBO_SUPPLIER);
	if (pcbSupplier->GetSafeHwnd() == NULL)
	{
		return;
	}

	CString csMsg;
	CString csSupplier, csSupplierID;
	int iSel =  pcbSupplier-> GetCurSel();
	if (iSel == -1)
	{
		return;
	}
	pcbSupplier-> GetLBText(iSel,csSupplier);
	csSupplier.Trim();
	int iFind = csSupplier.Find(_T("-"));
	if (iFind <= 0)
	{
		csMsg.Format("请选择正确的供应商！");
		MessageBox(csMsg, _T("进货管理"), MB_ICONERROR);
		return;
	}
	csSupplierID = csSupplier.GetBufferSetLength(iFind);

	m_curSupplier.csID = csSupplierID;
	m_curSupplier.csName = csSupplier;

	m_purchaseList.EnableWindow(TRUE);
	m_editSN.EnableWindow(TRUE);
	m_editSN.SetFocus();
}


void CPurchaseAddView::OnNMClickListPurchase(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	// TODO: 在此添加控件通知处理程序代码
	CString csMsg;

	POINT pt;
	GetCursorPos(&pt);
	m_purchaseList.ScreenToClient(&pt);
	LVHITTESTINFO hitInfo;
	hitInfo.pt=pt;
	m_purchaseList.SubItemHitTest(&hitInfo);

	if((hitInfo.flags & LVHT_ONITEMLABEL) &&      //判断是否单击在文本上
		(hitInfo.iItem != m_purchaseList.GetItemCount() - 1) &&
		hitInfo.iSubItem != -1)
	{
		CRect rect;
		int iActiveSubItem = -1;

		if (hitInfo.iSubItem == 5 || 
			hitInfo.iSubItem == 6	)
		{
			iActiveSubItem = hitInfo.iSubItem;
			m_iPurListItem = hitInfo.iItem;
			m_iPurListSubItem = iActiveSubItem;

			m_purchaseList.GetSubItemRect(hitInfo.iItem,iActiveSubItem,LVIR_BOUNDS,rect);

			csMsg = m_purchaseList.GetItemText(hitInfo.iItem,iActiveSubItem);
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
		else if (hitInfo.iSubItem == 4)
		{
			iActiveSubItem = hitInfo.iSubItem;
			m_iPurListItem = hitInfo.iItem;
			m_iPurListSubItem = iActiveSubItem;

			m_purchaseList.GetSubItemRect(hitInfo.iItem,iActiveSubItem,LVIR_BOUNDS,rect);
			m_pCbPopupBox->MoveWindow(&rect,TRUE);
			m_pCbPopupBox->ShowWindow(SW_SHOW);
			m_pCbPopupBox->SetFocus();

			csMsg = _T(" ") + m_purchaseList.GetItemText(hitInfo.iItem,iActiveSubItem);
			m_pCbPopupBox->SetWindowText(csMsg);
		}
		else	
		{
			if (hitInfo.iSubItem == 0 || 
				hitInfo.iSubItem == 1 || 
				hitInfo.iSubItem == 2 || 
				hitInfo.iSubItem == 3 ||
				hitInfo.iSubItem == 9 ||
				hitInfo.iSubItem == 10)
			{
				iActiveSubItem = 2;
			}
			else
			{
				iActiveSubItem = hitInfo.iSubItem;
			}

			m_iPurListItem = hitInfo.iItem;
			m_iPurListSubItem = iActiveSubItem;

			m_purchaseList.GetSubItemRect(hitInfo.iItem,iActiveSubItem,LVIR_BOUNDS,rect);
			rect.InflateRect(0,0,0,-1);

			csMsg = m_purchaseList.GetItemText(hitInfo.iItem,iActiveSubItem);
			m_pPurListPopupEdit->MoveWindow(&rect,TRUE);
			m_pPurListPopupEdit->ShowWindow(SW_NORMAL);
			m_pPurListPopupEdit->SetWindowText(csMsg);
			m_pPurListPopupEdit->BringWindowToTop();
			m_pPurListPopupEdit->SetFocus();//使组合框聚焦
			m_pPurListPopupEdit->CreateSolidCaret(1,rect.Height()-3);//创建一个光标
			m_pPurListPopupEdit->ShowCaret();//显示光标
			m_pPurListPopupEdit->SetSel(0);//使光标移到最后面
		}
	}
}
 

void CPurchaseAddView::OnEnChangeEditPopup()
{
	if (m_iPurListSubItem != -1)
	{
		if (m_iPurListSubItem == 7)
		{
			CString csRetailPrice;
			m_pPurListPopupEdit->GetWindowText(csRetailPrice);
			csRetailPrice.Trim();

			int iStart = 0; 
			int iEnd = 0; 
			m_pPurListPopupEdit->GetSel(iStart, iEnd); 
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
					m_pPurListPopupEdit->SetWindowText(csRetailPrice); 
					m_pPurListPopupEdit->SetSel(iSetPos-1,iSetPos-1); 
				} 
			} 
		}
		else if (m_iPurListSubItem == 8)
		{
			CString csNum;
			m_pPurListPopupEdit->GetWindowText(csNum);
			csNum.Trim();

			int iStart = 0; 
			int iEnd = 0; 
			m_pPurListPopupEdit->GetSel(iStart, iEnd); 
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
					m_pPurListPopupEdit->SetWindowText(csNum); 
					m_pPurListPopupEdit->SetSel(iSetPos-1,iSetPos-1); 
				} 
			} 
		}
	}
}


void CPurchaseAddView::OnCbnKillfocusPopupEdit()
{
	// TODO: 在此添加控件通知处理程序代码

	CString csInfo, csMsg, csMedicineID;
	int iListItem = -1;
	double dbTotalPrice = 0;

	if (m_iPurListSubItem != -1 && m_iPurListSubItem != 1)
	{
		m_pPurListPopupEdit->GetWindowText(csMsg);
		csMsg.Trim();
		m_pPurListPopupEdit->SetWindowText(_T(""));
		
		m_purchaseList.SetItemText(m_iPurListItem, m_iPurListSubItem, csMsg);
		switch (m_iPurListSubItem)
		{
			case 2:
				if (csMsg != _T(""))
				{
					if (DisplaySupplierMedicineInfo(csMsg.GetBuffer()) == TRUE)
					{
						GetDlgItem(IDC_COMBO_SUPPLIER)->EnableWindow(FALSE);
						GetDlgItem(IDC_BUTTON_SUPPLIER_ADD)->EnableWindow(FALSE);
					}
					else
					{
						m_pPurListPopupEdit->ShowWindow(SW_HIDE);
						m_purchaseList.SetFocus();
						csInfo.Format(_T("药品'%s'不存在，是否新建该药品信息?"), csMsg);
						if (IDYES == m_purchaseList.MessageBox(csInfo, _T("进货管理"), MB_ICONQUESTION|MB_YESNO))
						{
							CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
							if (pDoc == NULL)
							{
								m_purchaseList.SetItemText(m_iPurListItem, m_iPurListSubItem, _T(""));
								break;
							}
							pDoc->m_viewType = VIEW_SUBNEW;
							pDoc->m_csMedicineSN = csMsg;
							pDoc->m_csSupplierID = m_curSupplier.csID;
							CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
							if (pMain == NULL)
							{
								m_purchaseList.SetItemText(m_iPurListItem, m_iPurListSubItem, _T(""));
								break;
							}

							m_pPurListPopupEdit->SetWindowText(_T(""));
							m_pPurListPopupEdit->ShowWindow(SW_HIDE);
							TreeMenuID leftPanelID = TREE_MEDICINE_ADD;
							pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
							return;
						}
						else
						{
							m_purchaseList.SetItemText(m_iPurListItem, m_iPurListSubItem, _T(""));
							break;
						}
					}
				}
				break;
			case 8:
				{
					int iNum = atol(csMsg);
					csMsg = m_purchaseList.GetItemText(m_iPurListItem, 7);
					double dbTotal = atof(csMsg);
					dbTotal = dbTotal * iNum;
					csMsg.Format(_T("%0.2f"), dbTotal);
					m_purchaseList.SetItemText(m_iPurListItem, 10, csMsg);

					dbTotalPrice = 0;
					for (int i = 0; i < m_purchaseList.GetItemCount() - 1; i++)
					{
						csMsg = m_purchaseList.GetItemText(i, 10);
						dbTotalPrice += atof(csMsg);
					}
					iListItem = m_purchaseList.GetItemCount() - 1;
					csMsg.Format(_T("%0.2f"), dbTotalPrice);
					m_purchaseList.SetItemText(iListItem, 10, csMsg);

					if (dbTotalPrice > 0)
					{
						m_btnOK.EnableWindow(TRUE);
					}
					else
					{
						m_btnOK.EnableWindow(FALSE);
					}
				}
				break;
			case 7:
				{
					double dbTotal = atof(csMsg);
					csMsg = m_purchaseList.GetItemText(m_iPurListItem, 8);
					int iNum = atol(csMsg);
					dbTotal = dbTotal * iNum;
					csMsg.Format(_T("%0.2f"), dbTotal);
					m_purchaseList.SetItemText(m_iPurListItem, 10, csMsg);
				
					dbTotalPrice = 0;
					for (int i = 0; i < m_purchaseList.GetItemCount() - 1; i++)
					{
						csMsg = m_purchaseList.GetItemText(i, 10);
						dbTotalPrice += atof(csMsg);
					}
					iListItem = m_purchaseList.GetItemCount() - 1;
					csMsg.Format(_T("%0.2f"), dbTotalPrice);
					m_purchaseList.SetItemText(iListItem, 10, csMsg);

					if (dbTotalPrice > 0)
					{
						m_btnOK.EnableWindow(TRUE);
					}
					else
					{
						m_btnOK.EnableWindow(FALSE);
					}	
				}
				break;

			default:
				break;
		}
	}

	m_btnCancel.EnableWindow(TRUE);

	m_iPurListItem = -1;
	m_iPurListSubItem = -1;
	m_pPurListPopupEdit->ShowWindow(SW_HIDE);

	Invalidate();
}


void CPurchaseAddView::OnNMRClickListPurchase(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	if (pNMItemActivate->iItem == -1 || pNMItemActivate->iItem == m_purchaseList.GetItemCount() - 1)
	{
		return;
	}

	POINT pt;
	GetCursorPos(&pt);
	//m_purchaseList.ScreenToClient(&pt);

	CMenu menu;
	menu.LoadMenu(IDR_POPUP_PURLIST);
	CMenu *pMenu = menu.GetSubMenu(0);
	pMenu->TrackPopupMenu(0, pt.x, pt.y, this);

	*pResult = 0;
}


void CPurchaseAddView::AddOneLine(LPTSTR lpMedicineSN)
{
	// TODO: 在此添加命令处理程序代码
	if (lpMedicineSN == _T(""))
	{
		return;
	}

	CString csMsg, csInfo;
	m_iPurListItem = m_purchaseList.GetItemCount() - 1;
	m_iPurListSubItem = 2;
	csMsg.Format(_T("%d"), m_iPurListItem + 1);
	m_purchaseList.InsertItem(m_iPurListItem, csMsg);
	m_purchaseList.SetItemText(m_iPurListItem, m_iPurListSubItem, lpMedicineSN);
	
	m_editSN.SetWindowText(_T(""));

	if (DisplaySupplierMedicineInfo(lpMedicineSN) == TRUE)
	{
		GetDlgItem(IDC_COMBO_SUPPLIER)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SUPPLIER_ADD)->EnableWindow(FALSE);

		m_btnCancel.EnableWindow(TRUE);
		m_iPurListItem = -1;
		m_iPurListSubItem = -1;
	}
	else
	{
		m_purchaseList.SetFocus();
		csInfo.Format(_T("药品'%s'不存在，是否新建该药品信息?"), lpMedicineSN);
		if (IDYES == m_purchaseList.MessageBox(csInfo, _T("进货管理"), MB_ICONQUESTION|MB_YESNO))
		{
			CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
			if (pDoc == NULL)
			{
				m_purchaseList.SetItemText(m_iPurListItem, m_iPurListSubItem, _T(""));
				return;
			}
			pDoc->m_viewType = VIEW_SUBNEW;
			pDoc->m_csMedicineSN = lpMedicineSN;
			pDoc->m_csSupplierID = m_curSupplier.csID;
			CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
			if (pMain == NULL)
			{
				m_purchaseList.SetItemText(m_iPurListItem, m_iPurListSubItem, _T(""));
				return;
			}

			m_pPurListPopupEdit->SetWindowText(_T(""));
			m_pPurListPopupEdit->ShowWindow(SW_HIDE);

			m_btnOK.EnableWindow(FALSE);
			TreeMenuID leftPanelID = TREE_MEDICINE_ADD;
			pMain->SendMessage(WM_MAINFRM, WM_MAINFRM_SETRIGHTPANE, (LPARAM)leftPanelID);
			return;
		}
		else
		{
			m_purchaseList.DeleteItem(m_iPurListItem);

			for (int i = m_iPurListItem; i < m_purchaseList.GetItemCount() - 1; i++)
			{
				csMsg.Format(_T("%d"), i+1);
				m_purchaseList.SetItemText(i, 0, csMsg);
			}
			return;
		}
	}
}


void CPurchaseAddView::OnPurlistDelOneLine()
{
	// TODO: 在此添加命令处理程序代码
	POSITION pos = m_purchaseList.GetFirstSelectedItemPosition();
	int iSelected = m_purchaseList.GetNextSelectedItem(pos);
	if (iSelected == -1 || iSelected == m_purchaseList.GetItemCount() - 1)
	{
		return;
	}

	m_purchaseList.DeleteItem(iSelected);

	CString csMsg;
	for (int i = iSelected; i < m_purchaseList.GetItemCount() - 1; i++)
	{
		csMsg.Format(_T("%d"), i+1);
		m_purchaseList.SetItemText(i, 0, csMsg);
	}
}


BOOL CPurchaseAddView::DisplaySupplierMedicineInfo(LPTSTR lpMedicineSN)
{
	CSupplierMedicineDB supplierMedicineDB;
	CMedicineDB medicineDB;
	SupplierMedicine supplierMedicine; 
	Medicine medicine;
	CString csMsg;
	int iPurListItem = m_iPurListItem;
	ERRCODE errRet = medicineDB.GetMedicineBySN(lpMedicineSN, &medicine);
	if (errRet != err_OK)
	{
		return FALSE;
	}

	errRet = supplierMedicineDB.GetSupplierMedicine(medicine.csID.GetBuffer(), m_curSupplier.csID.GetBuffer(), &supplierMedicine);
	if (errRet == err_Medicine_NotExist)
	{
		
	}
	else if (errRet != err_OK)
	{
		csMsg.Format(_T("获取药品信息错误！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("进货管理"), MB_ICONERROR);
		return TRUE;
	}

	m_purchaseList.SetItemText(m_iPurListItem, 1, medicine.csID);
	m_purchaseList.SetItemText(m_iPurListItem, 2, medicine.csSN);
	m_purchaseList.SetItemText(m_iPurListItem, 3, medicine.csName);
	csMsg.Format(_T("%0.2f"), atof(supplierMedicine.csPurPrice));
	m_purchaseList.SetItemText(m_iPurListItem, 7, csMsg);

	MedicineUtil medicineUtil;
	if (medicine.util.csID != _T(""))
	{
		errRet = medicineDB.GetMedicineUnit(atoi(medicine.util.csID), &medicineUtil);
		if (errRet != err_OK)
		{
			csMsg.Format(_T("获取药品信息错误！%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("进货管理"), MB_ICONERROR);
			return TRUE;
		}

		m_purchaseList.SetItemText(m_iPurListItem, 9, medicineUtil.csName);
	}

	GetDlgItem(IDC_COMBO_SUPPLIER)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SUPPLIER_ADD)->EnableWindow(FALSE);
	return TRUE;
}


void CPurchaseAddView::DisplayMedicineBatchInfo(LPTSTR lpMedicineID, LPTSTR lpMedicineBatchNum)
{
	CMedicineBatchDB medicineBatchDB;
	MedicineBatch medicineBatch;
	CString csMsg;
	ERRCODE errRet = medicineBatchDB.GetMedicineBatch(lpMedicineID, lpMedicineBatchNum, &medicineBatch);
	if (errRet != err_OK)
	{
		return;
	}

	SYSTEMTIME time; 
	csMsg = _T("");
	if (ChangeDate(medicineBatch.csProductDate.GetBuffer(), time) == TRUE)
	{
		csMsg.Format(_T("%d/%d/%d"), time.wYear, time.wMonth, time.wDay);
	}
	m_purchaseList.SetItemText(m_iPurListItem, 5, csMsg);
	
	csMsg = _T("");
	if (ChangeDate(medicineBatch.csExpireDate.GetBuffer(), time) == TRUE)
	{
		csMsg.Format(_T("%d/%d/%d"), time.wYear, time.wMonth, time.wDay);
	}
	m_purchaseList.SetItemText(m_iPurListItem, 6, csMsg);
}


void CPurchaseAddView::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码

	if (AddPurchase() != TRUE)
	{
		return;
	}
	m_btnOK.EnableWindow(FALSE);

	PURMGRVIEW_CONTEXT *pPurMgrViewContext = NULL;
	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc != NULL && pDoc->m_pPurMgrViewContext != NULL)
	{
		delete pDoc->m_pPurMgrViewContext;
		pDoc->m_pPurMgrViewContext = NULL;
	}
	GetDlgItem(IDC_COMBO_SUPPLIER)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SUPPLIER_ADD)->EnableWindow(TRUE);

	MessageBox(_T("进货成功！"), _T("进货管理"), MB_ICONINFORMATION);
}


BOOL CPurchaseAddView::BeCancel()
{
	CString csMsg;

	if (m_btnOK.IsWindowEnabled() == TRUE)
	{
		csMsg.Format(_T("存在未完成的进货，是否确定放弃本次进货？"));
		int iRet = MessageBox(csMsg, _T("进货管理"), MB_ICONQUESTION|MB_OKCANCEL);
		if (iRet == IDCANCEL)
		{
			return FALSE;
		}
	}

	return TRUE;
}

void CPurchaseAddView::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码

	m_purchaseList.DeleteAllItems();

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc != NULL && pDoc->m_pPurMgrViewContext != NULL)
	{
		delete pDoc->m_pPurMgrViewContext;
		pDoc->m_pPurMgrViewContext = NULL;
	}

	GetDlgItem(IDC_COMBO_SUPPLIER)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SUPPLIER_ADD)->EnableWindow(TRUE);

	LoadDataFromDoc();
}


BOOL CPurchaseAddView::AddPurchase()
{
	ERRCODE errRet = err_OK;
	CString csMsg;
	CString csTotalPrice;
	CPurchaseDB purchaseDB;
	CSupplierMedicineDB supplierMedicineDB;
	CMedicineDB medicineDB;
	SupplierMedicine supplierMedicine;
	Medicine medicine;
	Purchase purchase;

	for (int i = 0; i < m_purchaseList.GetItemCount() - 1; i++)
	{
		purchase.csMedicineID = m_purchaseList.GetItemText(i, 1);
		purchase.csMedicineSN = m_purchaseList.GetItemText(i, 2);
		purchase.csBatchNum = m_purchaseList.GetItemText(i, 4);
		purchase.csProductDate = m_purchaseList.GetItemText(i, 5);
		purchase.csExpireDate = m_purchaseList.GetItemText(i, 6);
		purchase.csPurPrice = m_purchaseList.GetItemText(i, 7);
		purchase.csNumber = m_purchaseList.GetItemText(i, 8);

		purchase.csMedicineID.Trim();
		purchase.csMedicineSN.Trim();
		purchase.csBatchNum.Trim();
		purchase.csProductDate.Trim();
		purchase.csExpireDate.Trim();
		purchase.csPurPrice.Trim();
		purchase.csNumber.Trim();
		if (purchase.csMedicineID == _T(""))
		{
			csMsg.Format(_T("请填写第%d行的药品编码！"), i+1);
			MessageBox(csMsg, _T(""), MB_ICONWARNING);
			return FALSE;
		}
		if (purchase.csMedicineSN == _T(""))
		{
			csMsg.Format(_T("请填写第%d行的药品编码！"), i+1);
			MessageBox(csMsg, _T(""), MB_ICONWARNING);
			return FALSE;
		}
		if (purchase.csBatchNum == _T(""))
		{
			csMsg.Format(_T("请填写第%d行的药品批号！"), i+1);
			MessageBox(csMsg, _T(""), MB_ICONWARNING);
			return FALSE;
		}
		if (purchase.csProductDate == _T(""))
		{
			csMsg.Format(_T("请正确填写第%d行的药品生产日期！"), i+1);
			MessageBox(csMsg, _T(""), MB_ICONWARNING);
			return FALSE;
		}
		if (purchase.csExpireDate == _T(""))
		{
			csMsg.Format(_T("请正确填写第%d行的有效期至！"), i+1);
			MessageBox(csMsg, _T(""), MB_ICONWARNING);
			return FALSE;
		}
		if (purchase.csPurPrice == _T("")  || atof(purchase.csPurPrice) <= 0)
		{
			csMsg.Format(_T("请正确填写第%d行的药品进价！"), i+1);
			MessageBox(csMsg, _T(""), MB_ICONWARNING);
			return FALSE;
		}
		if (purchase.csNumber == _T("") || atol(purchase.csNumber) <= 0)
		{
			csMsg.Format(_T("请正确填写第%d行的药品数量！"), i+1);
			MessageBox(csMsg, _T(""), MB_ICONWARNING);
			return FALSE;
		}
	}

	for (int i = m_purchaseList.GetItemCount() - 2; i >= 0; i--)
	{
		purchase.csUserID = theApp.m_curUser.csID;
		purchase.csMedicineID = m_purchaseList.GetItemText(i, 1);
		purchase.csMedicineSN = m_purchaseList.GetItemText(i, 2);
		purchase.csMedicineName = m_purchaseList.GetItemText(i, 3);
		purchase.csBatchNum = m_purchaseList.GetItemText(i, 4);
		purchase.csProductDate = m_purchaseList.GetItemText(i, 5);
		purchase.csExpireDate = m_purchaseList.GetItemText(i, 6);
		purchase.csPurPrice = m_purchaseList.GetItemText(i, 7);
		purchase.csNumber = m_purchaseList.GetItemText(i, 8);
		purchase.csMedicineUnit = m_purchaseList.GetItemText(i, 9);
		csTotalPrice = m_purchaseList.GetItemText(i, 10);

		purchase.csMedicineID.Trim();
		if (purchase.csMedicineID == _T(""))
		{
			continue;
		}

		//添加进货
		errRet = purchaseDB.AddPurchase(&purchase);
		if (errRet != err_OK)
		{
			csMsg.Format(_T("添加进货信息错误！%s"), GetErrMsg(errRet));
			MessageBox(csMsg, _T("进货管理"), MB_ICONERROR);
			return FALSE;
		}

		m_purchaseList.DeleteItem(i);

		//如果SupplierMedicine不存在，将medicine信息保存为SupplierMedicine
		errRet = supplierMedicineDB.GetSupplierMedicine(purchase.csMedicineID.GetBuffer(), m_curSupplier.csID.GetBuffer(), &supplierMedicine);
		if (errRet == err_Medicine_NotExist)
		{
			errRet = medicineDB.GetMedicineBySN(purchase.csMedicineSN.GetBuffer(), &medicine);
			if (errRet == err_OK)
			{
				supplierMedicine.csSupplierID = m_curSupplier.csID;
				supplierMedicine.csPurPrice = purchase.csPurPrice;
				supplierMedicine.medicine.csID = purchase.csMedicineID;
				supplierMedicineDB.AddSupplierMedicine(&supplierMedicine);
			}
		}
		else
		{
			supplierMedicine.csPurPrice = purchase.csPurPrice;
			supplierMedicineDB.UpdateSupplierMedicine(&supplierMedicine);
		}
	}

	int iLastItem = m_purchaseList.GetItemCount() - 1;
	csMsg.Format(_T("0.00"));
	m_purchaseList.SetItemText(iLastItem, 10, csMsg);

	return TRUE;
}


BOOL CPurchaseAddView::SaveDataToDoc()
{
	CString csMsg;

	if (m_curSupplier.csID == _T("") && m_purchaseList.GetItemCount() <= 1)
	{
		return TRUE;
	}

	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		return FALSE;
	}

	if (pDoc->m_pPurMgrViewContext == NULL)
	{
		pDoc->m_pPurMgrViewContext = new PURMGRVIEW_CONTEXT;
		if (pDoc->m_pPurMgrViewContext == NULL)
		{
			return FALSE;
		}
	}
	PURMGRVIEW_CONTEXT *pPurMgrViewContext = pDoc->m_pPurMgrViewContext;

	pPurMgrViewContext->csSupplierID = m_curSupplier.csID.GetBuffer();
	for (unsigned int i = 0; i < pPurMgrViewContext->m_vctPurchaseList.size(); i++)
	{
		pPurMgrViewContext->m_vctPurchaseList[i].clear();
	}
	pPurMgrViewContext->m_vctPurchaseList.clear();
	
	int iCols = m_purchaseList.GetHeaderCtrl()-> GetItemCount();
	for (int i = 0; i < m_purchaseList.GetItemCount(); i++)
	{
		csMsg = m_purchaseList.GetItemText(i, 2);
		csMsg.Trim();
		if (csMsg == _T(""))
		{
			continue;
		}

		vector<CString> vctMsg;
		for (int j = 0; j < iCols; j++)
		{
			csMsg = m_purchaseList.GetItemText(i, j);
			csMsg.Trim();
			vctMsg.push_back(csMsg);
		}
		pPurMgrViewContext->m_vctPurchaseList.push_back(vctMsg);
		vctMsg.clear();
	}

	return TRUE;
}


BOOL CPurchaseAddView::LoadDataFromDoc()
{
	ERRCODE errRet = err_OK;
	CString csMsg;
	CSupplierDB supplierDB;
	int iListItem = -1;
	DOUBLE dbTotalPrice = 0;
	
	PURMGRVIEW_CONTEXT *pPurMgrViewContext = NULL;
	CManagerDoc *pDoc = (CManagerDoc*)GetDocument();
	if (pDoc == NULL)
	{
		goto end;
	}

	pPurMgrViewContext = pDoc->m_pPurMgrViewContext;
	if (pPurMgrViewContext == NULL)
	{
		goto end;
	}

	errRet = supplierDB.GetSupplier(pPurMgrViewContext->csSupplierID.GetBuffer(), &m_curSupplier);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("获取供应商信息错误, %s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("进货管理"), MB_ICONERROR);

		goto end;
	}

	csMsg.Format(_T("%s-%s"), pPurMgrViewContext->csSupplierID, m_curSupplier.csName);
	((CComboBox*)GetDlgItem(IDC_COMBO_SUPPLIER))->SetWindowText(csMsg);
	m_curSupplier.csID.Format(_T("%s"), pPurMgrViewContext->csSupplierID);
	m_curSupplier.csName = m_curSupplier.csName;
	m_purchaseList.EnableWindow(TRUE);
	m_editSN.EnableWindow(TRUE);

	m_iPurListItem = 0;
	for (unsigned int i = 0; i < pPurMgrViewContext->m_vctPurchaseList.size(); i++)
	{
		csMsg.Format(_T("%d"), m_iPurListItem + 1);
		m_purchaseList.InsertItem(m_iPurListItem, csMsg);
		for (unsigned int j = 0; j < pPurMgrViewContext->m_vctPurchaseList[i].size(); j++)
		{
			m_purchaseList.SetItemText(m_iPurListItem, j, pPurMgrViewContext->m_vctPurchaseList[i][j]);
		}

		if (DisplaySupplierMedicineInfo((pPurMgrViewContext->m_vctPurchaseList[i][2]).GetBuffer()) != TRUE)
		{
			m_purchaseList.DeleteItem(m_iPurListItem);
			pPurMgrViewContext->m_vctPurchaseList[i].clear();
			continue;
		}

		csMsg = m_purchaseList.GetItemText(m_iPurListItem, 10);
		dbTotalPrice += atof(csMsg);

		m_iPurListItem++;
		pPurMgrViewContext->m_vctPurchaseList[i].clear();
	}
	pPurMgrViewContext->m_vctPurchaseList.clear();

end:
	iListItem = m_purchaseList.GetItemCount();
	if (iListItem <= 0)
	{
		iListItem = 0;
	}
	else
	{
		GetDlgItem(IDC_COMBO_SUPPLIER)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SUPPLIER_ADD)->EnableWindow(FALSE);
		m_btnCancel.EnableWindow(TRUE);
	}

	m_purchaseList.InsertItem(iListItem, _T(""));
	m_purchaseList.SetItemText(iListItem, 9, _T("总计："));
	csMsg.Format(_T("%0.2f"), dbTotalPrice);
	m_purchaseList.SetItemText(iListItem, 10, csMsg);

	if (dbTotalPrice > 0)
	{
		m_btnOK.EnableWindow(TRUE);
	}
	else
	{
		m_btnOK.EnableWindow(FALSE);
	}

	return TRUE;
}

void CPurchaseAddView::OnNMKillfocusDatetime(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	CString csInfo, csMsg, csMedicineID;
	int iListItem = -1;
	double dbTotalPrice = 0;

	if (m_iPurListSubItem != -1 && m_iPurListSubItem != 1)
	{
		m_pDataTimeCtrl->GetWindowText(csMsg);
		csMsg.Trim();
		m_pDataTimeCtrl->SetWindowText(_T(""));

		m_purchaseList.SetItemText(m_iPurListItem, m_iPurListSubItem, csMsg);
		switch (m_iPurListSubItem)
		{
		case 5:
			break;
		case 6:
			break;
		default:
			break;
		}
	}

	m_iPurListItem = -1;
	m_iPurListSubItem = -1;
	m_pDataTimeCtrl->ShowWindow(SW_HIDE);

	Invalidate();
}


void CPurchaseAddView::OnCbnKillfocusCbPopup()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csInfo, csMsg, csMedicineID;
	int iListItem = -1;
	double dbTotalPrice = 0;

	if (m_iPurListSubItem != -1 && m_iPurListSubItem != 1)
	{
		m_pCbPopupBox->GetWindowText(csMsg);
		csMsg.Trim();
		m_pCbPopupBox->SetWindowText(_T(""));

		m_purchaseList.SetItemText(m_iPurListItem, m_iPurListSubItem, csMsg);

		csMedicineID = m_purchaseList.GetItemText(m_iPurListItem, 1);
		csMedicineID.Trim();
		if (csMsg != _T("") && csMedicineID != _T(""))
		{
			DisplayMedicineBatchInfo(csMedicineID.GetBuffer(), csMsg.GetBuffer());
			GetDlgItem(IDC_COMBO_SUPPLIER)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_SUPPLIER_ADD)->EnableWindow(FALSE);
		}
	}

	m_iPurListItem = -1;
	m_iPurListSubItem = -1;
	m_pCbPopupBox->ShowWindow(SW_HIDE);

	Invalidate();
}


void CPurchaseAddView::OnCbnSelchangeCbPopup()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csInfo, csMsg, csMedicineID;
	int iListItem = -1;
	double dbTotalPrice = 0;

	if (m_iPurListSubItem == -1 || m_iPurListSubItem == 1)
	{
		return;
	}

	int iCurSel = m_pCbPopupBox->GetCurSel();
	if (iCurSel == -1)
	{
		return;
	}

	m_pCbPopupBox->GetLBText(iCurSel, csMsg);
	csMsg.Trim();

	csMedicineID = m_purchaseList.GetItemText(m_iPurListItem, 1);
	csMedicineID.Trim();

	if (csMsg != _T("") && csMedicineID != _T(""))
	{
		DisplayMedicineBatchInfo(csMedicineID.GetBuffer(), csMsg.GetBuffer());
		GetDlgItem(IDC_COMBO_SUPPLIER)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SUPPLIER_ADD)->EnableWindow(FALSE);
	}
}


void CPurchaseAddView::OnCbnDropdownCbPopup()
{
	// TODO: 在此添加控件通知处理程序代码
	CSize   sz;
	int     dx = 0;
	TEXTMETRIC   tm;
	CDC*    pDC = m_pCbPopupBox->GetDC();
	CFont*  pFont = m_pCbPopupBox->GetFont();
	CFont* pOldFont = pDC->SelectObject(pFont);
	pDC->GetTextMetrics(&tm);

	CMedicineBatchDB medicineBatchDB;
	vector<MedicineBatch*> vctMedicineBatch;
	CString csMsg = m_purchaseList.GetItemText(m_iPurListItem, 1);
	csMsg.Trim();
	DWORD dwTotalNum, dwTotalPage;
	ERRCODE errRet = medicineBatchDB.GetMedicineBatchs(0, 
														50, 
														dwTotalPage, 
														dwTotalNum,
														vctMedicineBatch, 
														csMsg.GetBuffer(), 
														m_csSubPopupStr.GetBuffer());
	if (errRet != err_OK)
	{
		return;
	}

	while(m_pCbPopupBox->GetCount())
	{
		m_pCbPopupBox->DeleteString(0);
	}

	for (int i = 0; i < (int)vctMedicineBatch.size(); i++)
	{
		m_pCbPopupBox->InsertString(i, vctMedicineBatch[i]->csBatchNum);

		sz = pDC->GetTextExtent(vctMedicineBatch[i]->csBatchNum);
		sz.cx += tm.tmAveCharWidth;
		if (sz.cx > dx)
			dx = sz.cx;

		delete vctMedicineBatch[i];
		vctMedicineBatch[i] = NULL;
	}
	vctMedicineBatch.clear();

	pDC->SelectObject(pOldFont);
	m_pCbPopupBox->ReleaseDC(pDC);
	dx += ::GetSystemMetrics(SM_CXVSCROLL) + 2*::GetSystemMetrics(SM_CXEDGE);
	m_pCbPopupBox->SetDroppedWidth(dx);

	m_csSubPopupStr = _T("");
}


void CPurchaseAddView::OnCbnEditupdateCbPopup()
{
	// TODO: 在此添加控件通知处理程序代码
	CMedicineBatchDB medicineBatchDB;
	vector<MedicineBatch*> vctMedicineBatch;

	m_pCbPopupBox->GetWindowText(m_csSubPopupStr);
	m_csSubPopupStr.Trim();
	m_csSubPopupStr.AppendFormat(_T("%%"));

	m_pCbPopupBox->ShowDropDown(FALSE);
	m_pCbPopupBox->ShowDropDown(TRUE);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

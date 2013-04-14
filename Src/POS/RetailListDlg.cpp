// RetailListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "POS.h"
#include "RetailListDlg.h"
#include "afxdialogex.h"
#include "RetailDB.h"
#include "RetailItemDlg.h"

// CRetailListDlg dialog

IMPLEMENT_DYNAMIC(CRetailListDlg, CDialogEx)

CRetailListDlg::CRetailListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRetailListDlg::IDD, pParent)
{
	m_dwCurPage = 0;
	m_dwTotalPage = 0;
	m_dwTotalNum = 0;
	m_dbTotalPrice = 0;
}

CRetailListDlg::~CRetailListDlg()
{
}

void CRetailListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RETAIL, m_listRetail);
	DDX_Control(pDX, IDC_STATIC_PAGE, m_staticPageInfo);
	DDX_Control(pDX, IDC_BTN_PREPAGE, m_btnPrePage);
	DDX_Control(pDX, IDC_BTN_NEXTPAGE, m_btnNextPage);
	DDX_Control(pDX, IDC_LIST_RETAIL_DETAIL, m_listRetailDetail);
	DDX_Control(pDX, IDC_STATIC_GROUP_RETAIL_ITEM, m_staticGroupRetailItem);
	DDX_Control(pDX, IDC_STATIC_GROUP_RETAIL, m_staticGroupRetail);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_btnPrint);
}


BEGIN_MESSAGE_MAP(CRetailListDlg, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_PREPAGE, &CRetailListDlg::OnBnClickedBtnPrepage)
	ON_BN_CLICKED(IDC_BTN_NEXTPAGE, &CRetailListDlg::OnBnClickedBtnNextpage)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_RETAIL, &CRetailListDlg::OnLvnItemchangedListRetail)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RETAIL, &CRetailListDlg::OnNMDblclkListRetail)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, &CRetailListDlg::OnBnClickedButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CRetailListDlg::OnBnClickedButtonSearch)
END_MESSAGE_MAP()


BOOL CRetailListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ERRCODE errRet = err_OK;
	
	CString csMsg;
	csMsg.Format(_T("%s-%s"), APP_NAME, APP_POS);
	SetWindowText(csMsg);

	CRect rectClient;
	GetClientRect(rectClient);

	m_listRetail.SetExtendedStyle(LVS_EX_FLATSB    // 扁平风格滚动
		| LVS_EX_FULLROWSELECT    // 允许整行选中
		| LVS_EX_HEADERDRAGDROP    // 允许标题拖拽
		| LVS_EX_GRIDLINES    // 画出网格线
		);
	m_listRetail.InsertColumn(0, "编号", LVCFMT_LEFT, 0, 0);
	m_listRetail.InsertColumn(1, "POS机号", LVCFMT_LEFT, 60, 0);
	m_listRetail.InsertColumn(2, "收银员", LVCFMT_LEFT, 150, 0);
	m_listRetail.InsertColumn(3, "日期", LVCFMT_LEFT, 150, 0);
	m_listRetail.InsertColumn(4, "金额", LVCFMT_LEFT, 150, 0);
	m_listRetail.InsertColumn(5, "实收", LVCFMT_LEFT, 150, 0);
	m_listRetail.InsertColumn(6, "找零", LVCFMT_LEFT, 150, 0);

	m_listRetailDetail.SetExtendedStyle(LVS_EX_FLATSB    // 扁平风格滚动
		| LVS_EX_FULLROWSELECT    // 允许整行选中
		| LVS_EX_HEADERDRAGDROP    // 允许标题拖拽
		| LVS_EX_GRIDLINES    // 画出网格线
		);
	m_listRetailDetail.InsertColumn(0, "编号", LVCFMT_LEFT, 0, 0);
	m_listRetailDetail.InsertColumn(1, "药品编码", LVCFMT_LEFT, 150, 0);
	m_listRetailDetail.InsertColumn(2, "药品名称", LVCFMT_LEFT, 150, 0);
	m_listRetailDetail.InsertColumn(3, "药品价格", LVCFMT_LEFT, 150, 0);
	m_listRetailDetail.InsertColumn(4, "药品数量", LVCFMT_LEFT, 150, 0);
	m_listRetailDetail.InsertColumn(5, "药品单位", LVCFMT_LEFT, 150, 0);
	m_listRetailDetail.InsertColumn(6, "金额", LVCFMT_LEFT, 150, 0);

	DisplayListItem();

	ShowWindow(SW_SHOWMAXIMIZED);
	return TRUE;
}


// CRetailListDlg message handlers


void CRetailListDlg::DisplayListItem()
{
	CString csMsg;
	CRetailDB retailDB;
	vector<Retail*> vctRetail;

	ERRCODE errRet = retailDB.GetRetails(m_dwCurPage, 
		g_ciNumPerPage, 
		m_dwTotalPage, 
		m_dwTotalNum, 
		m_dbTotalPrice, 
		vctRetail, 
		theApp.m_curPOS.csID.GetBuffer(),
		NULL,
		m_retailSearchDlg.m_csRetailBeginDate.GetBuffer(),
		m_retailSearchDlg.m_csRetailEndDate.GetBuffer()); 
	if (errRet != err_OK)
	{
		for (unsigned int i = 0; i < vctRetail.size(); i++)
		{
			delete vctRetail[i];
			vctRetail[i] = NULL;
		}
		vctRetail.clear();

		csMsg.Format(_T("获取销售信息失败！%s"), GetErrMsg(errRet));
		MessageBox(csMsg, _T("销售管理"), MB_ICONERROR);
		return;
	}

	csMsg.Format(_T("第%d-%d项，共%d项"), m_dwTotalNum>0?m_dwCurPage * g_ciNumPerPage + 1:0, m_dwCurPage * g_ciNumPerPage +  vctRetail.size(), m_dwTotalNum);
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

	csMsg.Format(_T("销售列表 （合计：%0.2f元）"), m_dbTotalPrice);
	if (m_retailSearchDlg.m_csRetailBeginDate != _T("") && m_retailSearchDlg.m_csRetailEndDate != _T(""))
	{
		csMsg.AppendFormat(_T(" （ 销售日期：%s至%s ）"), m_retailSearchDlg.m_csRetailBeginDate, m_retailSearchDlg.m_csRetailEndDate);
	}
	m_staticGroupRetail.SetWindowText(csMsg);

	m_btnPrint.EnableWindow(FALSE);
	m_listRetail.DeleteAllItems();
	for (unsigned int i = 0; i < vctRetail.size(); i++)
	{
		m_listRetail.InsertItem(i, vctRetail[i]->csID);
		m_listRetail.SetItemText(i, 1, vctRetail[i]->csPOSID);
		csMsg.Format(_T("%s-%s"), vctRetail[i]->csUserUID, vctRetail[i]->csUserName);
		m_listRetail.SetItemText(i, 2, csMsg);
		m_listRetail.SetItemText(i, 3, vctRetail[i]->csCreateTime);
		csMsg.Format(_T("%0.2f"), atof(vctRetail[i]->csTotalPrcie));
		m_listRetail.SetItemText(i, 4, csMsg);
		csMsg.Format(_T("%0.2f"), atof(vctRetail[i]->csInPrice));
		m_listRetail.SetItemText(i, 5, csMsg);
		csMsg.Format(_T("%0.2f"), atof(vctRetail[i]->csOutPrice));
		m_listRetail.SetItemText(i, 6, csMsg);

		delete vctRetail[i];
		vctRetail[i] = NULL;
	}
	vctRetail.clear();
} 

// CRetailMgrView 消息处理程序

void CRetailListDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CRetailListDlg::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	int iWidth = 0, iHeight = 0;
	CRect clientRect;
	GetClientRect(clientRect);

	CRect printBtnRect;
	CButton *pPrintBtn = (CButton *)GetDlgItem(IDC_BUTTON_PRINT);
	if (pPrintBtn->GetSafeHwnd() != NULL)
	{
		pPrintBtn->GetClientRect(printBtnRect);
		iWidth = printBtnRect.Width();
		iHeight = printBtnRect.Height();
		printBtnRect.left = clientRect.left + 7;
		printBtnRect.right = printBtnRect.left + iWidth;
		printBtnRect.top = clientRect.top + 15;
		printBtnRect.bottom =  printBtnRect.top + iHeight;
		pPrintBtn->SetWindowPos(NULL, printBtnRect.left, printBtnRect.top, printBtnRect.Width(),  printBtnRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect searchBtnRect;
	CButton *pSearchBtn = (CButton *)GetDlgItem(IDC_BUTTON_SEARCH);
	if (pSearchBtn->GetSafeHwnd() != NULL)
	{
		pSearchBtn->GetClientRect(searchBtnRect);
		iWidth = searchBtnRect.Width();
		iHeight = searchBtnRect.Height();
		searchBtnRect.left = printBtnRect.right + 10;
		searchBtnRect.right = searchBtnRect.left + iWidth;
		searchBtnRect.top = clientRect.top + 15;
		searchBtnRect.bottom =  searchBtnRect.top + iHeight;
		pSearchBtn->SetWindowPos(NULL, searchBtnRect.left, searchBtnRect.top, searchBtnRect.Width(),  searchBtnRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect groupRetailRect;
	CStatic *pGroupRetail = (CStatic*)GetDlgItem(IDC_STATIC_GROUP_RETAIL);
	if (pGroupRetail->GetSafeHwnd() != NULL)
	{
		groupRetailRect.left = clientRect.left + 5;
		groupRetailRect.top = clientRect.top + 50;
		groupRetailRect.right = clientRect.Width() - 10 + groupRetailRect.left;
		groupRetailRect.bottom = clientRect.bottom - (clientRect.Height() - 75 - 5) / 3;
		pGroupRetail->SetWindowPos(NULL, groupRetailRect.left, groupRetailRect.top, groupRetailRect.Width(), groupRetailRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect retailListRect;
	CListCtrl *pRetailList = (CListCtrl*)GetDlgItem(IDC_LIST_RETAIL);
	if (pRetailList->GetSafeHwnd() != NULL)
	{
		retailListRect.left = clientRect.left + 5;
		retailListRect.top = groupRetailRect.top + 60;
		retailListRect.right = clientRect.Width() - 10 + retailListRect.left;
		retailListRect.bottom = groupRetailRect.bottom;
		pRetailList->SetWindowPos(NULL, retailListRect.left, retailListRect.top, retailListRect.Width(), retailListRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
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
		nextBtnRect.top = groupRetailRect.top + 20;
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
		pageInfoRect.right =  preBtnRect.left;
		pageInfoRect.left = pageInfoRect.right - iWidth;
		pageInfoRect.top = nextBtnRect.top + 5;
		pageInfoRect.bottom =  pageInfoRect.top + iHeight;
		pStaticPageInfo->SetWindowPos(NULL, pageInfoRect.left, pageInfoRect.top, pageInfoRect.Width(),  pageInfoRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect retailDetailListRect;
	CListCtrl *pRetaiDetaillList = (CListCtrl*)GetDlgItem(IDC_LIST_RETAIL_DETAIL);
	if (pRetaiDetaillList->GetSafeHwnd() != NULL)
	{
		retailDetailListRect.left = retailListRect.left;
		retailDetailListRect.top = retailListRect.bottom + 35;
		retailDetailListRect.right = retailListRect.right;
		retailDetailListRect.bottom = clientRect.bottom - 5;
		pRetaiDetaillList->SetWindowPos(NULL, retailDetailListRect.left, retailDetailListRect.top, retailDetailListRect.Width(), retailDetailListRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CRect groupRetailDetailRect;
	CStatic *pGroupRetailDetail = (CStatic*)GetDlgItem(IDC_STATIC_GROUP_RETAIL_ITEM);
	if (pGroupRetailDetail->GetSafeHwnd() != NULL)
	{
		groupRetailDetailRect.left = groupRetailRect.left;
		groupRetailDetailRect.top = groupRetailRect.bottom + 10;
		groupRetailDetailRect.right = clientRect.Width() - 10 + groupRetailDetailRect.left;
		groupRetailDetailRect.bottom = retailDetailListRect.bottom;
		pGroupRetailDetail->SetWindowPos(NULL, groupRetailDetailRect.left, groupRetailDetailRect.top, groupRetailDetailRect.Width(), groupRetailDetailRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void CRetailListDlg::OnBnClickedBtnPrepage()
{
	// TODO: Add your control notification handler code here
	if (m_dwCurPage <= 0)
	{
		return;
	}

	m_dwCurPage--;
	DisplayListItem();
}

void CRetailListDlg::OnBnClickedBtnNextpage()
{
	// TODO: Add your control notification handler code here
	if (m_dwCurPage + 1 >= m_dwTotalNum)
	{
		return;
	}

	m_dwCurPage++;
	DisplayListItem();
}

void CRetailListDlg::OnLvnItemchangedListRetail(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	m_btnPrint.EnableWindow(FALSE);

	if (pNMLV->iItem < 0)
	{
		return;
	}

	if(pNMLV-> uChanged==LVIF_STATE) 
	{ 
		m_listRetailDetail.DeleteAllItems();

		if(pNMLV-> uNewState) 
		{	
			m_btnPrint.EnableWindow(TRUE);

			CString csMsg;
			CRetailDB retailDB;
			vector<RetailItem*> vctRetailItem;
			csMsg = m_listRetail.GetItemText(pNMLV->iItem, 0);
			ERRCODE errRet = retailDB.GetRetailItems(csMsg.GetBuffer(), vctRetailItem);
			if (errRet != err_OK)
			{
				for (unsigned int i = 0; i < vctRetailItem.size(); i++)
				{
					delete vctRetailItem[i];
					vctRetailItem[i] = NULL;
				}
				vctRetailItem.clear();

				csMsg.Format(_T("获取销售信息失败！%s"), GetErrMsg(errRet));
				MessageBox(csMsg, _T("销售管理"), MB_ICONERROR);
				return;
			}

			for (unsigned int i = 0; i < vctRetailItem.size(); i++)
			{
				m_listRetailDetail.InsertItem(i, vctRetailItem[i]->csID);
				m_listRetailDetail.SetItemText(i, 1, vctRetailItem[i]->csMedicineSN);
				m_listRetailDetail.SetItemText(i, 2, vctRetailItem[i]->csMedicineName);
				csMsg.Format(_T("%0.2f"), atof(vctRetailItem[i]->csMedicinePrice));
				m_listRetailDetail.SetItemText(i, 3, csMsg);
				m_listRetailDetail.SetItemText(i, 4, vctRetailItem[i]->csMedicineNumber);
				m_listRetailDetail.SetItemText(i, 5, vctRetailItem[i]->csMedicineUnitName);
				csMsg.Format(_T("%0.2f"), atof(vctRetailItem[i]->csRetailPrice));
				m_listRetailDetail.SetItemText(i, 6, csMsg);

				delete vctRetailItem[i];
				vctRetailItem[i] = NULL;
			}
			vctRetailItem.clear();
		}
	}
}

void CRetailListDlg::OnNMDblclkListRetail(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	CString csMsg;

	POSITION pos = m_listRetail.GetFirstSelectedItemPosition();
	int iSelected = m_listRetail.GetNextSelectedItem(pos);
	if (iSelected == -1)
	{
		return;
	}
	
	CRetailItemDlg retailItemDlg;
	retailItemDlg.m_retail.csID = m_listRetail.GetItemText(iSelected, 0);
	retailItemDlg.m_retail.csID.Trim();

	retailItemDlg.DoModal();
}


void CRetailListDlg::OnBnClickedButtonPrint()
{
	// TODO: Add your control notification handler code here

	CString csMsg;

	POSITION pos = m_listRetail.GetFirstSelectedItemPosition();
	int iSelected = m_listRetail.GetNextSelectedItem(pos);
	if (iSelected == -1)
	{
		return;
	}

	CRetailItemDlg retailItemDlg;
	retailItemDlg.m_retail.csID = m_listRetail.GetItemText(iSelected, 0);
	retailItemDlg.m_retail.csID.Trim();

	retailItemDlg.DoModal();
}


void CRetailListDlg::OnBnClickedButtonSearch()
{
	// TODO: Add your control notification handler code here

	if (IDOK != m_retailSearchDlg.DoModal())
	{
		return;
	}

	DisplayListItem();
}

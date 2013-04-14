// RetailDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POS.h"
#include "RetailDlg.h"
#include "afxdialogex.h"
#include "StoreDB.h"
#include "RetailDB.h"
#include "POSConfig.h"
#include "PrintFormat.h"
#include "ChangeNumDlg.h"
#include "DeleteOneRowDlg.h"

#define INPUT_HELP _T("当前状态：录入   |    帮助：+/F2-付款，*/F3-数量，-/F4-删除一行, F12-重新上单，ESC-退出")
#define CHECKOUT_HELP _T("当前状态：付款   |    帮助：+/F2/回车-付款,  ESC-取消付款")
#define FINISH_HELP _T("当前状态：完成交易")

// CRetailDlg 对话框

IMPLEMENT_DYNAMIC(CRetailDlg, CDialogEx)

CRetailDlg::CRetailDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRetailDlg::IDD, pParent)
{
	m_retailStatus = RetailStatus_Input;
	m_dbTotalPrice = 0;
	m_dbInPrice = 0;
	m_dbOutPrice = 0;
	m_pCashBox = NULL;
}

CRetailDlg::~CRetailDlg()
{
	if (m_pCashBox != NULL)
	{
		delete m_pCashBox;
		m_pCashBox = NULL;
	}
}

void CRetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RETAIL, m_listRetail);
	DDX_Control(pDX, IDC_STATIC_TOTAL, m_staticTotal);
	DDX_Control(pDX, IDC_STATIC_TIP, m_staticTip);
	DDX_Control(pDX, IDC_STATIC_SN, m_staticSN);
	DDX_Control(pDX, IDC_EDIT_SN, m_editSN);
	DDX_Control(pDX, IDC_STATIC_IN, m_staticIn);
	DDX_Control(pDX, IDC_STATIC_OUT, m_staticOut);
	DDX_Control(pDX, IDC_STATIC_TOTAL_TITLE, m_staticTotalTitle);
	DDX_Control(pDX, IDC_STATIC_IN_TITLE, m_staticInTitle);
	DDX_Control(pDX, IDC_STATIC_OUT_TITLE, m_staticOutTitle);
	DDX_Control(pDX, IDC_STATIC_DATETIME, m_staticDateTime);
	DDX_Control(pDX, IDC_STATIC_NO, m_staticRetailSN);
	DDX_Control(pDX, IDC_STATIC_INFO, m_staticInfo);
	DDX_Control(pDX, IDC_STATIC_GROUP_TOTAL, m_staticGroupTotal);
	DDX_Control(pDX, IDC_STATIC_GROUP_INPUT, m_staticGroupInput);
	DDX_Control(pDX, IDC_STATIC_GROUP_TIP, m_staticGroupTip);
}


BEGIN_MESSAGE_MAP(CRetailDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_REGISTERED_MESSAGE(MESSAGE_RETAILDLG, OnRetailDlg)
	ON_EN_CHANGE(IDC_EDIT_SN, &CRetailDlg::OnEnChangeEditSn)
END_MESSAGE_MAP()


BOOL CRetailDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString csMsg;

	csMsg.Format(_T("POS机号：%d  |  收银员：%s-%s"), atol(theApp.m_curPOS.csID.GetBuffer()), theApp.m_curUser.csUID, theApp.m_curUser.csName);
	m_staticInfo.SetWindowText(csMsg);

	SetTimer(1, 1000, NULL);
	CTime time = CTime::GetCurrentTime();
	csMsg = time.Format(_T("%Y年%m月%d日 %H:%M:%S"));
	m_staticDateTime.SetWindowText(csMsg);

	m_listRetail.SetExtendedStyle(LVS_EX_FLATSB			   // 扁平风格滚动
								| LVS_EX_HEADERDRAGDROP    // 允许标题拖拽
								| LVS_EX_FULLROWSELECT     // 允许整行选中
								| LVS_EX_GRIDLINES
								);
	//m_listRetail.SetRichStyle(LVS_RICH_DRAWREMAIN);

	int iIdx = 0;
	m_listRetail.InsertColumn(iIdx++, "行号", LVCFMT_LEFT, 60, 0);
	m_listRetail.InsertColumn(iIdx++, "药品编号", LVCFMT_LEFT, 0, 0);
	m_listRetail.InsertColumn(iIdx++, "药品编码", LVCFMT_LEFT, 150, 0);
	m_listRetail.InsertColumn(iIdx++, "药品名称", LVCFMT_LEFT, 200, 0);
	//m_listRetail.InsertColumn(iIdx++, "批号", LVCFMT_LEFT, 150, 0);
	m_listRetail.InsertColumn(iIdx++, "单价", LVCFMT_LEFT, 80, 0);
	m_listRetail.InsertColumn(iIdx++, "单位", LVCFMT_LEFT, 80, 0);
	m_listRetail.InsertColumn(iIdx++, "数量", LVCFMT_LEFT, 80, 0);
	m_listRetail.InsertColumn(iIdx++, "金额", LVCFMT_LEFT, 80, 0);

	m_staticTip.SetWindowText(INPUT_HELP);

	m_staticTotalTitle.SetStyle(30, FW_HEAVY,RGB(0, 0, 0), NULL, DT_CENTER);
	m_staticTotalTitle.SetText(_T("合计："), RGB(0, 0,0) );
	m_staticTotal.SetStyle(35, FW_HEAVY,RGB(0, 255, 0), NULL, DT_LEFT);

	m_staticInTitle.SetStyle(30, FW_HEAVY,RGB(0, 0, 0), NULL, DT_CENTER);
	m_staticInTitle.SetText(_T("实收："), RGB(0, 0,0) );
	m_staticIn.SetStyle(35, FW_HEAVY,RGB(0, 255, 0), NULL, DT_LEFT);

	m_staticOutTitle.SetStyle(30, FW_HEAVY,RGB(0, 0, 0), NULL, DT_CENTER);
	m_staticOutTitle.SetText(_T("找零："), RGB(0, 0,0) );
	m_staticOut.SetStyle(35, FW_HEAVY,RGB(0, 255, 0), NULL, DT_LEFT);
	
	OnStatusNewInput();

	return FALSE;
}

ERRCODE CRetailDlg::Init()
{
	ERRCODE errRet = m_printerEP.Create(g_POSCfg.printer_name.GetBuffer());
	if (errRet != err_OK)
	{
		if (IDOK != MessageBox(_T("初始化打印机设备失败！"), _T(""), MB_ICONERROR))
		{
			return errRet;
		}
	}

	if (g_POSCfg.printer_name != g_POSCfg.cashbox_name)
	{
		if (m_pCashBox == NULL)
		{
			m_pCashBox = new CCashBox();
		}
		errRet = m_pCashBox->Create(g_POSCfg.cashbox_name.GetBuffer());
		if (errRet != err_OK)
		{
			if (IDOK != MessageBox(_T("初始化钱箱设备失败！"), _T(""), MB_ICONERROR))
			{
				return errRet;
			}
		}
	}

	errRet = m_customerDisplay.Create(g_POSCfg.customerdispay_name.GetBuffer());
	if (errRet != err_OK)
	{
		if (IDOK != MessageBox(_T("初始化顾客显示屏设备失败！"), _T(""), MB_ICONERROR))
		{
			return errRet;
		}
	}

	return err_OK;
}

BOOL CRetailDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (m_retailStatus == RetailStatus_Input)
		{
			//删除
			if (pMsg->wParam == g_POSCfg.key_del_one[0] || pMsg->wParam == g_POSCfg.key_del_one[1])
			{
				OnDelRetailItem();
				return TRUE;
			}
			//结帐
			else if (pMsg->wParam == g_POSCfg.key_checkout[0] || pMsg->wParam == g_POSCfg.key_checkout[1])
			{
				OnStatusCheckOut();
				return TRUE;
			}
			//修改数量
			else if (pMsg->wParam == g_POSCfg.key_num[0] || pMsg->wParam == g_POSCfg.key_num[1])
			{
				OnChangeNum();
				return TRUE;
			}
			//重新上单
			else if (pMsg->wParam == g_POSCfg.key_new_retail[0] || pMsg->wParam == g_POSCfg.key_new_retail[1])
			{
				OnStatusNewInput();
				return TRUE;
			}
			//Enter
			else if (pMsg->wParam == VK_RETURN)
			{
				CString csMsg;
				m_editSN.GetWindowText(csMsg);
				csMsg.Trim();
				OnAddRetailItem(csMsg.GetBuffer());
				m_editSN.SetWindowText(_T(""));
				m_editSN.SetFocus();
				return TRUE;
			}
			//字母与数字
			else if ((pMsg->wParam >= '0' && pMsg->wParam <= '9') || 
				(pMsg->wParam >= 'a' && pMsg->wParam <= 'z') ||
				(pMsg->wParam >= 'A' && pMsg->wParam <= 'Z'))
			{	
				CWnd *pFocus = GetFocus();
				if (pFocus != GetDlgItem(IDC_EDIT_SN))
				{
					CString csMsg;
					m_editSN.GetWindowText(csMsg);
					csMsg.AppendChar(pMsg->wParam);
					m_editSN.SetWindowText(csMsg);
					m_editSN.SetFocus();
					m_editSN.SetSel(csMsg.GetLength(), csMsg.GetLength());
				}
			}
			//退出
			else if (pMsg->wParam == VK_ESCAPE)
			{
				
			}
			//其他
			else
			{
				
			}
		}
		else if (m_retailStatus == RetailStatus_CheckOut)
		{
			if (pMsg->wParam == VK_ESCAPE)
			{
				OnCancelCheckOut();
				return TRUE;
			}
		}
		else if (m_retailStatus == RetailStatus_Finish)
		{
			//字母与数字
			if ((pMsg->wParam >= '0' && pMsg->wParam <= '9') || 
				(pMsg->wParam >= 'a' && pMsg->wParam <= 'z') ||
				(pMsg->wParam >= 'A' && pMsg->wParam <= 'Z'))
			{
				OnStatusNewInput();
				
				CWnd *pFocus = GetFocus();
				if (pFocus != GetDlgItem(IDC_EDIT_SN))
				{
					CString csMsg;
					m_editSN.GetWindowText(csMsg);
					csMsg.AppendChar(pMsg->wParam);
					m_editSN.SetWindowText(csMsg);
					m_editSN.SetFocus();
					m_editSN.SetSel(csMsg.GetLength(), csMsg.GetLength());
				}
			}
			//退出
			else if (pMsg->wParam == VK_ESCAPE)
			{

			}
			//其他
			else
			{
				OnStatusNewInput();
			}
		}
	} 

	return CDialogEx::PreTranslateMessage(pMsg);
}

LRESULT CRetailDlg::OnRetailDlg(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case MESSAGE_RETAILDGL_UPDATEINPRICE:
		m_dbInPrice = *(double*)lParam;
		m_dbOutPrice = m_dbInPrice - m_dbTotalPrice;

		DisplayTotalPrice();
		break;
		
	default:
		break;
	}

	return TRUE;
}

// CRetailDlg 消息处理程序

void CRetailDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	LONG style = ::GetWindowLong(this->m_hWnd,GWL_STYLE);
	style &= ~(WS_DLGFRAME | WS_THICKFRAME);
	SetWindowLong(this->m_hWnd,GWL_STYLE, style);
	ShowWindow(SW_SHOWMAXIMIZED);

	CRect rect;
	GetWindowRect(&rect);
	::SetWindowPos(this->m_hWnd,HWND_NOTOPMOST,rect.left, rect.top, rect.Width(), rect.Height(), SWP_FRAMECHANGED);
}

void CRetailDlg::OnPaint()
{
	CDialogEx::OnPaint();

	CRect rect;
	this->GetClientRect(&rect);

	int iLeftSpan = 24;
	int iMinLeftSpan = 4;
	int iWidthSpan = 24;
	int iHeightSpan = 24;
	int iMinHeightSpan = 12;
	int iWidth = 0, iHeight = 0;

	//Information and Retail NO
	CRect staticInfo;
	m_staticInfo.GetWindowRect(&staticInfo);
	ScreenToClient(&staticInfo);
	iWidth = staticInfo.Width();
	iHeight = staticInfo.Height();
	staticInfo.left = rect.left + iLeftSpan;
	staticInfo.right = staticInfo.left + iWidth;
	staticInfo.top = rect.top + iHeightSpan;
	staticInfo.bottom = staticInfo.top + iHeight;
	m_staticInfo.SetWindowPos(NULL,
											staticInfo.left, 
											staticInfo.top,
											staticInfo.Width(),							
											staticInfo.Height(),
											SWP_NOACTIVATE | SWP_NOZORDER);

	CRect staticNO;
	m_staticRetailSN.GetWindowRect(&staticNO);
	ScreenToClient(&staticNO);
	iWidth = staticNO.Width();
	iHeight = staticNO.Height();
	staticNO.right = rect.right - iLeftSpan;
	staticNO.left = staticNO.right - iWidth;
	staticNO.top = rect.top + iHeightSpan;
	staticNO.bottom = staticNO.top + iHeight;
	m_staticRetailSN.SetWindowPos(NULL,
											staticNO.left, 
											staticNO.top,
											staticNO.Width(),							
											staticNO.Height(),
											SWP_NOACTIVATE | SWP_NOZORDER);

	//Tips rect
	CRect staticTipRect;
	m_staticTip.GetWindowRect(&staticTipRect);
	ScreenToClient(&staticTipRect);
	iWidth = staticTipRect.Width();
	iHeight = staticTipRect.Height();
	staticTipRect.left = rect.left + iMinLeftSpan;
	staticTipRect.right = staticTipRect.left + rect.Width() * 3 / 4;
	staticTipRect.bottom = rect.bottom;
	staticTipRect.top = rect.bottom - iHeight;

	m_staticTip.SetWindowPos(NULL,
							staticTipRect.left, 
							staticTipRect.top,
							staticTipRect.Width(),							
							staticTipRect.Height(),
							SWP_NOACTIVATE | SWP_NOZORDER);

	CRect staticDateTime;
	m_staticDateTime.GetWindowRect(&staticDateTime);
	ScreenToClient(&staticDateTime);
	iWidth = staticDateTime.Width();
	iHeight = staticDateTime.Height();
	staticDateTime.right = rect.right - iMinLeftSpan;
	staticDateTime.left = staticDateTime.right - iWidth;
	staticDateTime.top = staticTipRect.top;
	staticDateTime.bottom = staticTipRect.bottom;
	m_staticDateTime.SetWindowPos(NULL,
							staticDateTime.left, 
							staticDateTime.top,
							staticDateTime.Width(),							
							staticDateTime.Height(),
							SWP_NOACTIVATE | SWP_NOZORDER);

	CRect staticGroupTip;
	m_staticGroupTip.GetWindowRect(&staticGroupTip);
	ScreenToClient(&staticGroupTip);
	staticGroupTip.left =rect.left;
	staticGroupTip.right = rect.right;
	staticGroupTip.top = staticTipRect.top - 14;
	staticGroupTip.bottom = staticTipRect.bottom;
	m_staticGroupTip.SetWindowPos(NULL,
		staticGroupTip.left, 
		staticGroupTip.top,
		staticGroupTip.Width(),		
		staticGroupTip.Height(),
		SWP_NOACTIVATE | SWP_NOZORDER);

	//Input SN
	CRect staticSNRect;
	m_staticSN.GetWindowRect(&staticSNRect);
	ScreenToClient(&staticSNRect);
	iWidth = staticSNRect.Width();
	iHeight = staticSNRect.Height();
	staticSNRect.top = staticTipRect.top - iHeight - iHeightSpan - iMinHeightSpan + 6;
	staticSNRect.bottom = staticSNRect.top + iHeight;
	staticSNRect.left = rect.left + iLeftSpan;
	staticSNRect.right = staticSNRect.left + iWidth;
	m_staticSN.SetWindowPos(NULL,
											staticSNRect.left, 
											staticSNRect.top,
											staticSNRect.Width(),		
											staticSNRect.Height(),
											SWP_NOACTIVATE | SWP_NOZORDER);

	CRect editSNRect;
	m_editSN.GetWindowRect(&editSNRect);
	ScreenToClient(&editSNRect);
	iWidth = editSNRect.Width();
	iHeight = editSNRect.Height();
	editSNRect.left = staticSNRect.right;
	editSNRect.right = editSNRect.left + iWidth;
	editSNRect.top = staticTipRect.top - iHeight - iHeightSpan - iMinHeightSpan;
	editSNRect.bottom = editSNRect.top + iHeight;
	m_editSN.SetWindowPos(NULL,
										editSNRect.left, 
										editSNRect.top,
										editSNRect.Width(),		
										editSNRect.Height(),
										SWP_NOACTIVATE | SWP_NOZORDER);

	CRect staticGroupInput;
	m_staticGroupInput.GetWindowRect(&staticGroupInput);
	ScreenToClient(&staticGroupInput);
	staticGroupInput.left = rect.left;
	staticGroupInput.right = rect.right;
	staticGroupInput.top = editSNRect.top - iMinHeightSpan - 8;
	staticGroupInput.bottom = editSNRect.bottom + iMinHeightSpan;
	m_staticGroupInput.SetWindowPos(NULL,
														staticGroupInput.left, 
														staticGroupInput.top,
														staticGroupInput.Width(),		
														staticGroupInput.Height(),
														SWP_NOACTIVATE | SWP_NOZORDER);
	m_staticGroupInput.ShowWindow(SW_HIDE);

	//Total Price
	CRect totalPriceTitleRect;
	m_staticTotalTitle.GetWindowRect(&totalPriceTitleRect);
	ScreenToClient(&totalPriceTitleRect);
	iWidth = totalPriceTitleRect.Width();
	iHeight = totalPriceTitleRect.Height();
	totalPriceTitleRect.left = rect.left + iLeftSpan;
	totalPriceTitleRect.right = totalPriceTitleRect.left + iWidth;
	totalPriceTitleRect.bottom = editSNRect.top - iHeightSpan - iMinHeightSpan;
	totalPriceTitleRect.top = totalPriceTitleRect.bottom - iHeight;
	m_staticTotalTitle.SetWindowPos(NULL,
							totalPriceTitleRect.left, 
							totalPriceTitleRect.top,
							totalPriceTitleRect.Width(),		
							totalPriceTitleRect.Height(),
							SWP_NOACTIVATE | SWP_NOZORDER);

	CRect totalPriceRect;
	m_staticTotal.GetWindowRect(&totalPriceRect);
	ScreenToClient(&totalPriceRect);
	iWidth = totalPriceRect.Width();
	totalPriceRect.left = totalPriceTitleRect.right;
	totalPriceRect.right = totalPriceRect.left + iWidth;
	totalPriceRect.top = totalPriceTitleRect.top;
	totalPriceRect.bottom = totalPriceTitleRect.bottom;
	m_staticTotal.SetWindowPos(NULL,
												totalPriceRect.left, 
												totalPriceRect.top,
												totalPriceRect.Width(),		
												totalPriceRect.Height(),
												SWP_NOACTIVATE | SWP_NOZORDER);

	CRect inPriceTitleRect;
	m_staticInTitle.GetWindowRect(&inPriceTitleRect);
	ScreenToClient(&inPriceTitleRect);
	iWidth = inPriceTitleRect.Width();
	inPriceTitleRect.left = totalPriceRect.right + iWidthSpan;
	inPriceTitleRect.right = inPriceTitleRect.left + iWidth;
	inPriceTitleRect.top = totalPriceTitleRect.top;
	inPriceTitleRect.bottom = totalPriceTitleRect.bottom;
	m_staticInTitle.SetWindowPos(NULL,
										inPriceTitleRect.left, 
										inPriceTitleRect.top,
										inPriceTitleRect.Width(),		
										inPriceTitleRect.Height(),
										SWP_NOACTIVATE | SWP_NOZORDER);

	CRect inPriceRect;
	m_staticIn.GetWindowRect(&inPriceRect);
	ScreenToClient(&inPriceRect);
	iWidth = inPriceRect.Width();
	inPriceRect.left = inPriceTitleRect.right;
	inPriceRect.right = inPriceRect.left + iWidth;
	inPriceRect.top = totalPriceTitleRect.top;
	inPriceRect.bottom = totalPriceTitleRect.bottom;
	m_staticIn.SetWindowPos(NULL,
		inPriceRect.left, 
		inPriceRect.top,
		inPriceRect.Width(),		
		inPriceRect.Height(),
		SWP_NOACTIVATE | SWP_NOZORDER);

	CRect outPriceTitleRect;
	m_staticOutTitle.GetWindowRect(&outPriceTitleRect);
	ScreenToClient(&outPriceTitleRect);
	iWidth = outPriceTitleRect.Width();
	outPriceTitleRect.left = inPriceRect.right + iWidthSpan;
	outPriceTitleRect.right = outPriceTitleRect.left + iWidth;
	outPriceTitleRect.top = totalPriceTitleRect.top;
	outPriceTitleRect.bottom = totalPriceTitleRect.bottom;
	m_staticOutTitle.SetWindowPos(NULL,
											outPriceTitleRect.left, 
											outPriceTitleRect.top,
											outPriceTitleRect.Width(),		
											outPriceTitleRect.Height(),
											SWP_NOACTIVATE | SWP_NOZORDER);

	CRect outPriceRect;
	m_staticOut.GetWindowRect(&outPriceRect);
	ScreenToClient(&outPriceRect);
	iWidth = inPriceRect.Width();
	outPriceRect.left = outPriceTitleRect.right;
	outPriceRect.right = outPriceRect.left + iWidth;
	outPriceRect.top = totalPriceTitleRect.top;
	outPriceRect.bottom = totalPriceTitleRect.bottom;
	m_staticOut.SetWindowPos(NULL,
		outPriceRect.left, 
		outPriceRect.top,
		outPriceRect.Width(),		
		outPriceRect.Height(),
		SWP_NOACTIVATE | SWP_NOZORDER);

	//List rect 
	CRect listRect;
	m_listRetail.GetWindowRect(&listRect);
	ScreenToClient(&listRect);
	listRect.left = rect.left;
	listRect.right = rect.right;
	listRect.top = staticNO.bottom + iHeightSpan;
	listRect.bottom = totalPriceTitleRect.top - 2;
	m_listRetail.SetWindowPos(NULL,
											listRect.left, 
											listRect.top,
											listRect.Width(),		
											listRect.Height(),
											SWP_NOACTIVATE | SWP_NOZORDER);


	CRect staticGroupTotal;
	m_staticGroupTotal.GetWindowRect(&staticGroupTotal);
	ScreenToClient(&staticGroupTotal);
	staticGroupTotal.left = rect.left;
	staticGroupTotal.right = rect.right;
	staticGroupTotal.top = totalPriceTitleRect.top - 10;
	staticGroupTotal.bottom = totalPriceTitleRect.bottom + 2;
	m_staticGroupTotal.SetWindowPos(NULL,
															staticGroupTotal.left, 
															staticGroupTotal.top,
															staticGroupTotal.Width(),		
															staticGroupTotal.Height(),
															SWP_NOACTIVATE | SWP_NOZORDER);
}


void CRetailDlg::OnTimer( UINT nIDEvent )
{
	CTime time = CTime::GetCurrentTime();
	CString csDateTime = time.Format(_T("%Y年%m月%d日 %H:%M:%S"));
	m_staticDateTime.SetWindowText(csDateTime);

	CDialogEx::OnTimer(nIDEvent);
}

void CRetailDlg::DisplayTotalPrice()
{
	CString csMsg;
	m_dbOutPrice = m_dbInPrice - m_dbTotalPrice;
	if (m_dbOutPrice < 0)
	{
		m_dbOutPrice = 0;
	}

	csMsg.Format(_T("￥%0.2f"), m_dbTotalPrice);
	m_staticTotal.SetText(csMsg, RGB(0, 255,0) );
	csMsg.Format(_T("￥%0.2f"), m_dbInPrice);
	m_staticIn.SetText(csMsg, RGB(0, 255,0) );
	csMsg.Format(_T("￥%0.2f"), m_dbOutPrice);
	m_staticOut.SetText(csMsg, RGB(0, 255,0) );
}

void CRetailDlg::GenerateSN()
{
	CString csMsg;

	CTime time = CTime::GetCurrentTime();
	m_csRetailSN.Format(_T("%02x%s"), atol(theApp.m_curPOS.csID.GetBuffer()), time.Format(_T("%Y%m%d%H%M%S")));
	csMsg.Format(_T("单号：%s"), m_csRetailSN);

	m_staticRetailSN.SetWindowText(csMsg);
}

void CRetailDlg::OnAddRetailItem(LPTSTR lpMedicineIDORSN)
{
	ERRCODE errRet = err_OK;
	CString csMsg;
	CStoreDB storeDB;
	MedicineStore medicineStore;

	if (lpMedicineIDORSN == NULL ||  strlen(lpMedicineIDORSN) == 0)
	{
		return;
	}

	errRet = storeDB.GetMedicineStore(lpMedicineIDORSN, &medicineStore);
	if (errRet != err_OK)
	{
		csMsg.Format(_T("库存中不存在编码为‘%s’的药品！"), lpMedicineIDORSN);
		MessageBox(csMsg, _T(""), MB_OK|MB_ICONERROR);
		return;
	}

	double dbPrice = 0;
	int iSubItem = 0;
	int iItem = m_listRetail.GetItemCount();
	csMsg.Format(_T("%d"), iItem + 1);
	m_listRetail.InsertItem(iItem, csMsg);
	m_listRetail.SetItemText(iItem, ++iSubItem, medicineStore.csMedicineID);
	m_listRetail.SetItemText(iItem, ++iSubItem, medicineStore.csMedicineSN);
	m_listRetail.SetItemText(iItem, ++iSubItem, medicineStore.csMedicineName);
	
	dbPrice = atof(medicineStore.csMedicineRetailPrice.GetBuffer());
	csMsg.Format(_T("%0.2f"), dbPrice);
	m_listRetail.SetItemText(iItem, ++iSubItem, csMsg);
	m_listRetail.SetItemText(iItem, ++iSubItem, medicineStore.csMedicineUnitName);
	m_listRetail.SetItemText(iItem, ++iSubItem, _T("1"));
	csMsg.Format(_T("%0.2f"), dbPrice);
	m_listRetail.SetItemText(iItem, ++iSubItem, csMsg);

	m_customerDisplay.InitDisplay();
	m_customerDisplay.Display(CDisplayType_Price, dbPrice);

	m_dbTotalPrice += dbPrice;
	DisplayTotalPrice();

	m_editSN.SetWindowText(_T(""));
}

void CRetailDlg::OnCancelRetail()
{
	CString csMsg;

	m_listRetail.DeleteAllItems();

	m_dbTotalPrice = 0;
	m_dbInPrice = 0;
	m_dbOutPrice = 0;
	DisplayTotalPrice();

	m_editSN.SetWindowText(_T(""));
}

void CRetailDlg::OnDelRetailItem()
{
	CString csMsg;
	int iSelectItem = m_listRetail.GetItemCount();
	if (iSelectItem <= 0)
	{
		return;
	}
	iSelectItem--;

	CDeleteOneRowDlg deleteOneRowDlg;
	deleteOneRowDlg.m_iRow = iSelectItem + 1;
	if (deleteOneRowDlg.DoModal() != IDOK)
	{
		return;
	}

	iSelectItem = deleteOneRowDlg.m_iRow - 1;

	csMsg = m_listRetail.GetItemText(iSelectItem, 7);
	double dbPrice = atof(csMsg.GetBuffer());
	m_dbTotalPrice -= dbPrice;

	m_listRetail.DeleteItem(iSelectItem);

	DisplayTotalPrice();

	for (int i = iSelectItem; i < m_listRetail.GetItemCount(); i++)
	{
		csMsg.Format(_T("%d"), i + 1);
		m_listRetail.SetItemText(i, 0, csMsg);
	}
	return;
}

void CRetailDlg::OnStatusNewInput()
{
	CString csMsg;

	m_retailStatus = RetailStatus_Input;

	GenerateSN();

	m_customerDisplay.Clear();

	m_staticTip.SetWindowText(INPUT_HELP);

	m_listRetail.DeleteAllItems();

	m_dbTotalPrice = 0;
	m_dbInPrice = 0;
	m_dbOutPrice = 0;
	DisplayTotalPrice();

	m_editSN.EnableWindow(TRUE);

	m_editSN.SetWindowText(_T(""));
}

void CRetailDlg::OnStatusInput()
{
	CString csMsg;

	m_retailStatus = RetailStatus_Input;

	m_staticTip.SetWindowText(INPUT_HELP);

	DisplayTotalPrice();

	m_editSN.EnableWindow(TRUE);

	m_editSN.SetWindowText(_T(""));
}

BOOL CRetailDlg::OnStatusCheckOut()
{
	if (m_dbTotalPrice <= 0)
	{
		return FALSE;
	}
	CString csMsg;

	m_retailStatus = RetailStatus_CheckOut;

	m_staticTip.SetWindowText(CHECKOUT_HELP);

	m_editSN.EnableWindow(FALSE);

	m_customerDisplay.Display(CDisplayType_Total, m_dbTotalPrice);

	CCheckOutDlg checkOutDlg;
	checkOutDlg.m_pCustomerDisplay = &m_customerDisplay;
	checkOutDlg.m_dbTotalPrice = m_dbTotalPrice;
	if (checkOutDlg.DoModal() != IDOK)
	{
		OnStatusInput();
		return FALSE;
	}
	m_dbInPrice = checkOutDlg.m_dbIn;
	m_dbOutPrice = checkOutDlg.m_dbOut;

	m_customerDisplay.Display(CDisplayType_Out, m_dbOutPrice);

	DisplayTotalPrice();

	//打开钱箱
	OnOpenCashBox();

	//打印收据
	OnPrint();

	//添加到数据库

	//完成

	OnStatusFinishCheckOut();

	return TRUE;
}

void CRetailDlg::OnCancelCheckOut()
{
	CString csMsg;

	if (IDOK != MessageBox(_T("确认取消该次结算？"), _T(""), MB_OKCANCEL | MB_ICONQUESTION))
	{
		return;
	}

	OnStatusNewInput();
}

void CRetailDlg::OnStatusFinishCheckOut()
{
	CRetailDB retailDB;
	Retail retail;
	
	retail.csPCID.Format(_T("%d"), atol(theApp.m_curPOS.csPCID.GetBuffer()));
	retail.csSN = m_csRetailSN;
	retail.csUserID = theApp.m_curUser.csID;
	retail.csTotalPrcie.Format(_T("%0.2f"), m_dbTotalPrice);
	retail.csInPrice.Format(_T("%0.2f"), m_dbInPrice);
	retail.csOutPrice.Format(_T("%0.2f"), m_dbOutPrice);

	ERRCODE errRet = retailDB.AddRetail(&retail);
	if (errRet != err_OK)
	{
		MessageBox(_T("添加销售记录到数据库失败！"), _T(""), MB_OK | MB_ICONWARNING);
		g_log.Write(_T("添加销售记录到数据库失败！"), errRet);
	}
	else
	{
		for (int i = 0; i < m_listRetail.GetItemCount(); i++)
		{
			RetailItem retailItem;
			retailItem.csRetailID = retail.csID;
			retailItem.csMedicineID = m_listRetail.GetItemText(i, 1);
			retailItem.csMedicineSN = m_listRetail.GetItemText(i, 2);
			retailItem.csMedicineName = m_listRetail.GetItemText(i, 3);
			retailItem.csMedicinePrice = m_listRetail.GetItemText(i, 4);
			retailItem.csMedicineUnitName = m_listRetail.GetItemText(i, 5);
			retailItem.csMedicineNumber = m_listRetail.GetItemText(i, 6);
			retailItem.csRetailPrice = m_listRetail.GetItemText(i, 7);

			errRet = retailDB.AddRetailItem(&retailItem);
			if (errRet != err_OK)
			{
				MessageBox(_T("添加销售记录到数据库失败！"), _T(""), MB_OK | MB_ICONWARNING);
				g_log.Write(_T("添加销售记录到数据库失败！"), errRet);
			}
		}
	}

	m_retailStatus = RetailStatus_Finish;

	m_staticTip.SetWindowText(FINISH_HELP);

	m_editSN.EnableWindow(TRUE);

	m_editSN.SetWindowText(_T(""));
}

ERRCODE CRetailDlg::OnOpenCashBox()
{
	ERRCODE errRet = err_OK;

	if (m_pCashBox != NULL)
	{
		errRet = m_pCashBox->Open();
	}
	else
	{
		errRet = m_printerEP.OpenCashBox();
	}
	if (errRet != err_OK)
	{
		MessageBox(_T("打开钱箱失败！"), _T(""), MB_OK | MB_ICONWARNING);
		g_log.Write(_T("打开钱箱失败！"), errRet);
	}

	return errRet;
}

ERRCODE CRetailDlg::OnPrint()
{
	ERRCODE errRet = err_OK;
	CString csMsg;

	errRet = m_printerEP.InitPrint();
	if (errRet != err_OK)
	{
		goto quit;
	}

	PrintItem *pPrintItem = g_printFormat.GetPrintItemPtr();
	if (pPrintItem != NULL)
	{
		pPrintItem->csPOSNO.Format(_T("%d"), atol(theApp.m_curPOS.csID.GetBuffer()));
		pPrintItem->csNO = m_csRetailSN;
		pPrintItem->csUID = theApp.m_curUser.csUID;
		CTime time = CTime::GetCurrentTime();
		pPrintItem->csDataTime = time.Format(_T("%Y/%m/%d %H:%M:%S"));
		int iItemCount = m_listRetail.GetItemCount();
		if (iItemCount)
		{
			pPrintItem->vctRetailItem.resize(iItemCount);
			for (int i = 0; i < iItemCount; i++)
			{
				csMsg.Format(_T("%s\r%-18s %-6s %-6s\r"), 
					m_listRetail.GetItemText(i, 3),
					m_listRetail.GetItemText(i, 2),
					csMsg = m_listRetail.GetItemText(i, 6),
					csMsg = m_listRetail.GetItemText(i, 7));

				pPrintItem->vctRetailItem[i].csName = m_listRetail.GetItemText(i, 3);
				pPrintItem->vctRetailItem[i].csSN = m_listRetail.GetItemText(i, 2);
				pPrintItem->vctRetailItem[i].csNum = m_listRetail.GetItemText(i, 6);
				pPrintItem->vctRetailItem[i].csPrice = m_listRetail.GetItemText(i, 4);
				pPrintItem->vctRetailItem[i].csTotalPrice = m_listRetail.GetItemText(i, 7);
			}
			pPrintItem->csTotalPrice.Format(_T("%0.2f"), m_dbTotalPrice);
			pPrintItem->csTotalIn.Format(_T("%0.2f"), m_dbInPrice);
			pPrintItem->csTotalOut.Format(_T("%0.2f"), m_dbOutPrice);
		}
	}

    #define PRINT_BUFFER_SIZE 500
	BYTE pbyBuf[PRINT_BUFFER_SIZE];
	memset(pbyBuf, 0, PRINT_BUFFER_SIZE);
	DWORD dwRetBufSize = 0;
	errRet = g_printFormat.GetPrintStrFirstLine(pbyBuf, &dwRetBufSize, PRINT_BUFFER_SIZE);
	pbyBuf[dwRetBufSize] = 0;

	while(errRet == err_OK && dwRetBufSize)
	{
		errRet = m_printerEP.AddTextOut(LPTSTR(pbyBuf), dwRetBufSize);
		
		errRet = g_printFormat.GetPrintStrNextLine(pbyBuf, &dwRetBufSize, PRINT_BUFFER_SIZE);
		pbyBuf[dwRetBufSize] = 0;
	}

	errRet = m_printerEP.DoPrint();
	if (errRet != err_OK)
	{
		MessageBox(_T("do print fail!"), _T(""), MB_ICONWARNING);
		goto quit;
	}

quit:
	if (errRet != err_OK)
	{
		MessageBox(_T("打印机服务不可用，打印票据失败！"), _T(""), MB_OK | MB_ICONWARNING);
		g_log.Write(_T("打印机服务不可用，打印票据失败！"), errRet);
		return errRet;
	}

	return errRet;
}

void CRetailDlg::OnOK()
{

}

void CRetailDlg::OnCancel()
{
	if (m_retailStatus == RetailStatus_CheckOut)
	{
		MessageBox(_T("结算未完成， 无法退出"), _T(""), MB_OK | MB_ICONWARNING);
		return;
	}

	if ((m_retailStatus == RetailStatus_Input && m_listRetail.GetItemCount()) &&
		IDOK != MessageBox(_T("存在未结算条目，是否放弃结算并退出？"), _T(""), MB_OKCANCEL | MB_ICONQUESTION))
	{
		return;
	}
	
	CDialogEx::OnCancel();
}

void CRetailDlg::OnClose()
{
	OnCancel();
}

void CRetailDlg::OnEnChangeEditSn()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

}

void CRetailDlg::OnChangeNum()
{
	CString csMsg;
	int iSelectItem = m_listRetail.GetItemCount();
	if (iSelectItem <= 0)
	{
		return;
	}
	iSelectItem--;
	
	CChangeNumDlg changeNumDlg;
	changeNumDlg.m_iRow = iSelectItem + 1;
	csMsg = m_listRetail.GetItemText(iSelectItem, 6);
	changeNumDlg.m_iNum = atol(csMsg.GetBuffer());	
	if (changeNumDlg.DoModal() != IDOK)
	{
		return;
	}
	
	iSelectItem = changeNumDlg.m_iRow - 1;

	csMsg = m_listRetail.GetItemText(iSelectItem, 6);
	int iNum = atol(csMsg.GetBuffer());	
	csMsg = m_listRetail.GetItemText(iSelectItem, 7);
	double dbPrice = atof(csMsg.GetBuffer());
	m_dbTotalPrice -= dbPrice;

	iNum = changeNumDlg.m_iNum;

	csMsg = m_listRetail.GetItemText(iSelectItem, 4);
	dbPrice = atof(csMsg.GetBuffer());
	dbPrice *= iNum;
	m_dbTotalPrice += dbPrice;

	csMsg.Format(_T("%d"), iNum);
	m_listRetail.SetItemText(iSelectItem, 6, csMsg);

	csMsg.Format(_T("%0.2f"), dbPrice);
	m_listRetail.SetItemText(iSelectItem, 7, csMsg);

	DisplayTotalPrice();

	return;
}
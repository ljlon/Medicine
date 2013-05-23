// PurchaseSearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "PurchaseSearchDlg.h"
#include "afxdialogex.h"
#include "PurchaseDB.h"

// CPurchaseSearchDlg 对话框

IMPLEMENT_DYNAMIC(CPurchaseSearchDlg, CDialogEx)

CPurchaseSearchDlg::CPurchaseSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPurchaseSearchDlg::IDD, pParent)
{

}

CPurchaseSearchDlg::~CPurchaseSearchDlg()
{
}

void CPurchaseSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_PURCHASE_DATE, m_btnPurDate);
	DDX_Control(pDX, IDC_CHECK_MEDICINE_NAME, m_cbMedicineName);
	DDX_Control(pDX, IDC_CHECK_MEDICINE_SN, m_cbMedicineSN);
	DDX_Control(pDX, IDC_CHECK_MEDICINE_BATCHNUM, m_cbMedicineBatchNum);
	DDX_Control(pDX, IDC_CHECK_MEDICINE_SUPPLIER, m_cbSupplier);
	DDX_Control(pDX, IDC_DATE_PUR_BEGIN, m_datePurBegin);
	DDX_Control(pDX, IDC_DATE_PUR_END, m_datePurEnd);
	DDX_Control(pDX, IDC_EDIT_MEDICINE_SN, m_editMedicineSN);
	DDX_Control(pDX, IDC_EDIT_MEDICINE_NAME, m_editMedicineName);
	DDX_Control(pDX, IDC_EDIT_MEDICINE_BATCHNUM, m_editMedicineBatchNum);
	DDX_Control(pDX, IDC_COMBO_SUPPLIER, m_comboSupplier);
}


BEGIN_MESSAGE_MAP(CPurchaseSearchDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPurchaseSearchDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_PURCHASE_DATE, &CPurchaseSearchDlg::OnBnClickedCheckPurchaseDate)
	ON_BN_CLICKED(IDC_CHECK_MEDICINE_SN, &CPurchaseSearchDlg::OnBnClickedCheckMedicineSn)
	ON_BN_CLICKED(IDC_CHECK_MEDICINE_NAME, &CPurchaseSearchDlg::OnBnClickedCheckMedicineName)
	ON_BN_CLICKED(IDC_CHECK_MEDICINE_BATCHNUM, &CPurchaseSearchDlg::OnBnClickedCheckMedicineBatchNum)
	ON_BN_CLICKED(IDC_CHECK_MEDICINE_SUPPLIER, &CPurchaseSearchDlg::OnBnClickedCheckSupplier)
	ON_CBN_DROPDOWN(IDC_COMBO_SUPPLIER, &CPurchaseSearchDlg::OnCbnDropdownComboSupplier)
	ON_CBN_EDITUPDATE(IDC_COMBO_SUPPLIER, &CPurchaseSearchDlg::OnCbnEditupdateComboSupplier)
END_MESSAGE_MAP()


BOOL CPurchaseSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	ERRCODE errRet = err_OK;
	CString csMsg;

	m_cbMedicineSN.SetCheck(TRUE);
	m_cbMedicineName.SetCheck(TRUE);
	m_cbMedicineBatchNum.SetCheck(TRUE);
	m_cbSupplier.SetCheck(TRUE);
	m_editMedicineSN.SetFocus();

	if (m_csPurBeginDate != _T("") && m_csPurEndDate != _T(""))
	{
		m_btnPurDate.SetCheck(TRUE);
		m_datePurBegin.EnableWindow(TRUE);
		m_datePurEnd.EnableWindow(TRUE);

		SYSTEMTIME time;
		if (ChangeDate(m_csPurBeginDate.GetBuffer(), time) == TRUE)
		{
			m_datePurBegin.SetTime(&time);
		}
		if (ChangeDate(m_csPurEndDate.GetBuffer(), time) == TRUE)
		{
			m_datePurEnd.SetTime(&time);
		}
	}

	if (m_csMedicineName != _T(""))
	{
		m_cbMedicineName.SetCheck(TRUE);
		m_editMedicineName.EnableWindow(TRUE);
		m_editMedicineName.SetWindowText(m_csMedicineName);
	}

	if (m_csMedicineSN != _T(""))
	{
		m_cbMedicineSN.SetCheck(TRUE);
		m_editMedicineSN.EnableWindow(TRUE);
		//m_editMedicineSN.SetWindowText(m_csMedicineSN);
	}

	CSupplierDB supplierDB;
	Supplier supplier;
	if (m_csSupplierID != _T(""))
	{
		errRet = supplierDB.GetSupplier(m_csSupplierID.GetBuffer(), &supplier);
		if (errRet == err_OK)
		{
			csMsg.Format(_T("%s-%s"), supplier.csID, supplier.csName);
			m_comboSupplier.SetWindowText(csMsg);
			m_comboSupplier.SetFocus();
		}
	}

	return FALSE;
}

// CPurchaseSearchDlg 消息处理程序


void CPurchaseSearchDlg::OnBnClickedCheckPurchaseDate()
{
	// TODO: Add your control notification handler code here
	if (m_btnPurDate.GetCheck() == TRUE)
	{
		m_datePurBegin.EnableWindow(TRUE);
		m_datePurEnd.EnableWindow(TRUE);
		m_datePurBegin.SetFocus();
	}
	else
	{
		m_datePurBegin.EnableWindow(FALSE);
		m_datePurEnd.EnableWindow(FALSE);
	}
}


void CPurchaseSearchDlg::OnBnClickedCheckMedicineSn()
{
	// TODO: Add your control notification handler code here
	if (m_cbMedicineSN.GetCheck() == TRUE)
	{
		m_editMedicineSN.EnableWindow(TRUE);
		m_editMedicineSN.SetFocus();
	}
	else
	{
		m_editMedicineSN.EnableWindow(FALSE);
	}
}


void CPurchaseSearchDlg::OnBnClickedCheckMedicineName()
{
	// TODO: Add your control notification handler code here
	if (m_cbMedicineName.GetCheck() == TRUE)
	{
		m_editMedicineName.EnableWindow(TRUE);
		m_editMedicineName.SetFocus();
	}
	else
	{
		m_editMedicineName.EnableWindow(FALSE);
	}
}


void CPurchaseSearchDlg::OnBnClickedCheckMedicineBatchNum()
{
	if (m_cbMedicineBatchNum.GetCheck() == TRUE)
	{
		m_editMedicineBatchNum.EnableWindow(TRUE);
		m_editMedicineBatchNum.SetFocus();
	}
	else
	{
		m_editMedicineBatchNum.EnableWindow(FALSE);
	}
}


void CPurchaseSearchDlg::OnBnClickedCheckSupplier()
{
	if (m_cbSupplier.GetCheck() == TRUE)
	{
		m_comboSupplier.EnableWindow(TRUE);
		m_comboSupplier.SetFocus();
	}
	else
	{
		m_comboSupplier.EnableWindow(FALSE);
	}
}


void CPurchaseSearchDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	m_csPurBeginDate = _T("");
	m_csPurEndDate = _T("");
	if (m_btnPurDate.GetCheck() == TRUE)
	{
		m_datePurBegin.GetWindowText(m_csPurBeginDate);
		m_datePurEnd.GetWindowText(m_csPurEndDate);
		m_csPurBeginDate.Trim();
		m_csPurEndDate.Trim();

		if (m_csPurBeginDate > m_csPurEndDate)
		{
			m_csPurEndDate = m_csPurBeginDate;
		}
	}

	m_csMedicineSN = _T("");
	if (m_cbMedicineSN.GetCheck() == TRUE)
	{
		m_editMedicineSN.GetWindowText(m_csMedicineSN);
		m_csMedicineSN.Trim();
	}

	m_csMedicineName = _T("");
	if (m_cbMedicineName.GetCheck() == TRUE)
	{
		m_editMedicineName.GetWindowText(m_csMedicineName);
		m_csMedicineName.Trim();
	}

	m_csMedicineBatchNum = _T("");
	if (m_cbMedicineBatchNum.GetCheck() == TRUE)
	{
		m_editMedicineBatchNum.GetWindowText(m_csMedicineBatchNum);
		m_csMedicineBatchNum.Trim();
	}

	m_csSupplierID = _T("");
	if (m_cbSupplier.GetCheck() == TRUE)
	{
		m_comboSupplier.GetWindowText(m_csSupplierID);
		m_csSupplierID.Trim();
		if (m_csSupplierID != _T(""))
		{
			int iFind = m_csSupplierID.Find(_T("-"));
			if (iFind > 0)
			{
				m_csSupplierID = m_csSupplierID.GetBufferSetLength(iFind);
			}
			else
			{
				m_csSupplierID = _T("");
			}
		}
	}

	CDialogEx::OnOK();
}


void CPurchaseSearchDlg::OnCbnEditupdateComboSupplier()
{
	CString csMsg;
	m_comboSupplier.GetWindowText(m_csSubSupplierName);
	m_csSubSupplierName.Trim();

	m_comboSupplier.ShowDropDown(FALSE);
	m_comboSupplier.ShowDropDown(TRUE);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
}


void CPurchaseSearchDlg::OnCbnDropdownComboSupplier()
{
	// TODO: Add your control notification handler code here

	CString csMsg;
	CSize   sz;
	int     dx = 0;
	TEXTMETRIC   tm;
	CDC*    pDC = m_comboSupplier.GetDC();
	CFont*  pFont = m_comboSupplier.GetFont();
	CFont* pOldFont = pDC->SelectObject(pFont);
	pDC->GetTextMetrics(&tm);

	DWORD dwCurPage = 0;
	DWORD dwTotalPage = 0;
	DWORD dwTotalNum = 0;
	CSupplierDB supplierDB;
	vector<Supplier*> vctSuppliers;
	supplierDB.GetSuppliers(dwCurPage, g_ciNumPerPage, dwTotalPage, dwTotalNum, vctSuppliers, m_csSubSupplierName.GetBuffer());

	for(int  i = m_comboSupplier.GetCount() - 1;  i >= 0;  i--) 
	{ 
		m_comboSupplier.DeleteString(i); 
	} 

	int iIdx = 0;
	for (unsigned int i = 0; i < vctSuppliers.size(); i++)
	{
		csMsg.Format(_T("%s-%s"), vctSuppliers[i]->csID, vctSuppliers[i]->csName);
		m_comboSupplier.InsertString(iIdx++, csMsg);

		sz = pDC->GetTextExtent(csMsg);
		sz.cx += tm.tmAveCharWidth;

		if (sz.cx > dx)
			dx = sz.cx;

		delete vctSuppliers[i];
		vctSuppliers[i] = NULL;
	}
	vctSuppliers.clear();

	pDC->SelectObject(pOldFont);
	m_comboSupplier.ReleaseDC(pDC);
	dx += ::GetSystemMetrics(SM_CXVSCROLL) + 2*::GetSystemMetrics(SM_CXEDGE);
	m_comboSupplier.SetDroppedWidth(dx);

	m_csSubSupplierName = _T("");
}
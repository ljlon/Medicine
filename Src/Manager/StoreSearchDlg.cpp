// StoreSearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "StoreSearchDlg.h"
#include "afxdialogex.h"
#include "VendorDB.h"
#include "SupplierDB.h"

// CStoreSearchDlg dialog

IMPLEMENT_DYNAMIC(CStoreSearchDlg, CDialogEx)

CStoreSearchDlg::CStoreSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStoreSearchDlg::IDD, pParent)
{

}

CStoreSearchDlg::~CStoreSearchDlg()
{
}

void CStoreSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_MEDICINE_NAME, m_cbMedicineName);
	DDX_Control(pDX, IDC_CHECK_MEDICINE_SN, m_cbMedicineSN);
	DDX_Control(pDX, IDC_CHECK_EXPIREDATE, m_cbExpireDate);
	DDX_Control(pDX, IDC_EDIT_MEDICINE_SN, m_editMedicineSN);
	DDX_Control(pDX, IDC_EDIT_MEDICINE_NAME, m_editMedicineName);
	DDX_Control(pDX, IDC_DATETIMEPICKER_EXPIREDATE, m_datetimeExpire);
	DDX_Control(pDX, IDC_CHECK_MEDICINE_VENDOR, m_cbMedicineVendor);
	DDX_Control(pDX, IDC_CHECK_MEDICINE_SUPPLIER, m_cbMedicineSupplier);
	DDX_Control(pDX, IDC_COMBO_VENDOR, m_comboVendor);
	DDX_Control(pDX, IDC_COMBO_SUPPLIER, m_comboSupplier);
}


BEGIN_MESSAGE_MAP(CStoreSearchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_MEDICINE_SN, &CStoreSearchDlg::OnBnClickedCheckMedicineSn)
	ON_BN_CLICKED(IDC_CHECK_MEDICINE_NAME, &CStoreSearchDlg::OnBnClickedCheckMedicineName)
	ON_BN_CLICKED(IDC_CHECK_EXPIREDATE, &CStoreSearchDlg::OnBnClickedCheckExpiredate)
	ON_BN_CLICKED(IDC_CHECK_MEDICINE_VENDOR, &CStoreSearchDlg::OnBnClickedCheckMedicineVendor)
	ON_BN_CLICKED(IDC_CHECK_MEDICINE_SUPPLIER, &CStoreSearchDlg::OnBnClickedCheckMedicineSupplier)
	ON_CBN_DROPDOWN(IDC_COMBO_VENDOR, &CStoreSearchDlg::OnCbnDropdownComboVendor)
	ON_CBN_DROPDOWN(IDC_COMBO_SUPPLIER, &CStoreSearchDlg::OnCbnDropdownComboSupplier)
	ON_CBN_EDITUPDATE(IDC_COMBO_VENDOR, &CStoreSearchDlg::OnCbnEditupdateComboVendor)
	ON_CBN_EDITUPDATE(IDC_COMBO_SUPPLIER, &CStoreSearchDlg::OnCbnEditupdateComboSupplier)
END_MESSAGE_MAP()

BOOL CStoreSearchDlg::OnInitDialog()
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

	ERRCODE errRet;
	CString csMsg;
	CVendorDB vendorDB;
	Vendor vendor;
	CSupplierDB supplierDB;
	Supplier supplier;

	m_cbMedicineSN.SetCheck(TRUE);
	m_cbMedicineName.SetCheck(TRUE);
	m_cbExpireDate.SetCheck(FALSE);
	m_datetimeExpire.EnableWindow(FALSE);
	m_cbMedicineVendor.SetCheck(TRUE);
	m_cbMedicineSupplier.SetCheck(TRUE);
	m_editMedicineSN.SetFocus();

	if (m_csExpireDate != _T(""))
	{
		m_cbExpireDate.SetCheck(TRUE);
		m_datetimeExpire.EnableWindow(TRUE);

		SYSTEMTIME time;
		if (ChangeDate(m_csExpireDate.GetBuffer(), time) == TRUE)
		{
			m_datetimeExpire.SetTime(&time);
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

	if (m_csVendorID != _T(""))
	{
		errRet = vendorDB.GetVendor(m_csVendorID.GetBuffer(), &vendor);
		if (errRet == err_OK)
		{
			csMsg.Format(_T("%s-%s"), vendor.csID, vendor.csName);
			m_comboVendor.SetWindowText(csMsg);
			m_comboVendor.SetFocus();
		}
	}

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

// CStoreSearchDlg message handlers


void CStoreSearchDlg::OnBnClickedCheckMedicineSn()
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


void CStoreSearchDlg::OnBnClickedCheckMedicineName()
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


void CStoreSearchDlg::OnBnClickedCheckExpiredate()
{
	// TODO: Add your control notification handler code here
	if (m_cbExpireDate.GetCheck() == TRUE)
	{
		m_datetimeExpire.EnableWindow(TRUE);
		m_datetimeExpire.SetFocus();
	}
	else
	{
		m_datetimeExpire.EnableWindow(FALSE);
	}
}


void CStoreSearchDlg::OnOK()
{
	CDialogEx::OnOK();

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

	m_csExpireDate = _T("");
	if (m_cbExpireDate.GetCheck() == TRUE)
	{
		m_datetimeExpire.GetWindowText(m_csExpireDate);
		m_csExpireDate.Trim();
	}

	m_csVendorID = _T("");
	if (m_cbMedicineVendor.GetCheck() == TRUE)
	{
		m_comboVendor.GetWindowText(m_csVendorID);
		m_csVendorID.Trim();
		if (m_csVendorID != _T(""))
		{
			int iFind = m_csVendorID.Find(_T("-"));
			if (iFind > 0)
			{
				m_csVendorID = m_csVendorID.GetBufferSetLength(iFind);
			}
			else
			{
				m_csVendorID = _T("");
			}
		}
	}

	m_csSupplierID = _T("");
	if (m_cbMedicineSupplier.GetCheck() == TRUE)
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
}

void CStoreSearchDlg::OnBnClickedCheckMedicineVendor()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: Add your control notification handler code here
	if (m_cbMedicineVendor.GetCheck() == TRUE)
	{
		m_comboVendor.EnableWindow(TRUE);
		m_comboVendor.SetFocus();
	}
	else
	{
		m_comboVendor.EnableWindow(FALSE);
	}
}


void CStoreSearchDlg::OnBnClickedCheckMedicineSupplier()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_cbMedicineSupplier.GetCheck() == TRUE)
	{
		m_comboSupplier.EnableWindow(TRUE);
		m_comboSupplier.SetFocus();
	}
	else
	{
		m_comboSupplier.EnableWindow(FALSE);
	}
}


void CStoreSearchDlg::OnCbnDropdownComboVendor()
{
	// TODO: 在此添加控件通知处理程序代码
	CVendorDB vendorDB;
	vector<Vendor*> vctVendor;
	DWORD dwTotalPage, dwTotalNum;
	CString csMsg;

	for (int i = m_comboVendor.GetCount() - 1; i >= 0; i--)
	{
		m_comboVendor.DeleteString(i);
	}

	ERRCODE errRet = vendorDB.GetVendors(0, 50, dwTotalPage, dwTotalNum, vctVendor, m_csMatchStr.GetBuffer());
	if (errRet != err_OK)
	{
		return;
	}

	for (int i = 0; i < (int)vctVendor.size(); i++)
	{
		csMsg.Format(_T("%s-%s"), vctVendor[i]->csID.GetBuffer(), vctVendor[i]->csName.GetBuffer());
		m_comboVendor.AddString(csMsg);

		delete vctVendor[i];
		vctVendor[i] = NULL;
	}
	vctVendor.clear();

	m_csMatchStr = _T("");
}


void CStoreSearchDlg::OnCbnDropdownComboSupplier()
{
	// TODO: 在此添加控件通知处理程序代码
	CSupplierDB supplierDB;
	vector<Supplier*> vctSupplier;
	DWORD dwTotalPage, dwTotalNum;
	CString csMsg;

	for (int i = m_comboSupplier.GetCount() - 1; i >= 0; i--)
	{
		m_comboSupplier.DeleteString(i);
	}

	ERRCODE errRet = supplierDB.GetSuppliers(0, 50, dwTotalPage, dwTotalNum, vctSupplier, m_csMatchStr.GetBuffer());
	if (errRet != err_OK)
	{
		return;
	}

	for (int i = 0; i < (int)vctSupplier.size(); i++)
	{
		csMsg.Format(_T("%s-%s"), vctSupplier[i]->csID.GetBuffer(), vctSupplier[i]->csName.GetBuffer());
		m_comboSupplier.AddString(csMsg);

		delete vctSupplier[i];
		vctSupplier[i] = NULL;
	}
	vctSupplier.clear();

	m_csMatchStr = _T("");
}


void CStoreSearchDlg::OnCbnEditupdateComboVendor()
{
	// TODO: 在此添加控件通知处理程序代码
	m_comboVendor.GetWindowText(m_csMatchStr);
	m_csMatchStr.Trim();

	m_comboVendor.ShowDropDown(FALSE);
	m_comboVendor.ShowDropDown(TRUE);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
}


void CStoreSearchDlg::OnCbnEditupdateComboSupplier()
{
	// TODO: 在此添加控件通知处理程序代码
	m_comboSupplier.GetWindowText(m_csMatchStr);
	m_csMatchStr.Trim();

	m_comboSupplier.ShowDropDown(FALSE);
	m_comboSupplier.ShowDropDown(TRUE);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
}
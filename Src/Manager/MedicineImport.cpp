// MedicineSearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Manager.h"
#include "MedicineImport.h"
#include "afxdialogex.h"
#include "MedicineDB.h"
#include "VendorDB.h"

// CMedicineSearchDlg dialog

IMPLEMENT_DYNAMIC(CMedicineImportDlg, CDialogEx)

CMedicineImportDlg::CMedicineImportDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMedicineImportDlg::IDD, pParent)
{
	
}

CMedicineImportDlg::~CMedicineImportDlg()
{
}

void CMedicineImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_EXPORT, m_cbExport);
	DDX_Control(pDX, IDC_BTN_IMPORT, m_cbImport);
	DDX_Control(pDX, IDC_EDIT_EXPORT, m_editExport);
	DDX_Control(pDX, IDC_EDIT_IMPORT, m_editImport);
}


BEGIN_MESSAGE_MAP(CMedicineImportDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_EXPORT, &CMedicineImportDlg::OnBnClickedExport)
	ON_BN_CLICKED(IDC_BTN_IMPORT, &CMedicineImportDlg::OnBnClickedImport)
END_MESSAGE_MAP()

BOOL CMedicineImportDlg::OnInitDialog()
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

	TCHAR tszPath[MAX_PATH];
	memset(tszPath, 0, MAX_PATH * sizeof(TCHAR));
	GetCurrentDirectory(MAX_PATH, tszPath);

	_tcscat_s(tszPath, _T("\\Backup\\Medicine.dat"));
	m_editExport.SetWindowText(tszPath);
	m_editImport.SetWindowText(tszPath);

	return FALSE;
}

// CMedicineImportDlg message handlers

void CMedicineImportDlg::OnBnClickedExport()
{
	// TODO: Add your control notification handler code here
	CString csPath, csMsg;
	m_editExport.GetWindowText(csPath);

	CMedicineDB medicineDB;
	vector<Medicine*> vctMedicine;

	DWORD dwPageNum = 0, dwNumPerPage = 0, dwTotalPage = 0, dwTotalNum = 0;
	ERRCODE errRet = err_OK;
	
	FILE *pFile = NULL;
	fopen_s(&pFile, csPath.GetBuffer(), "w+");
	if (pFile == NULL)
	{
		MessageBox(_T("导出文件打开失败！"), _T(""), MB_ICONERROR);
		return;
	}

	while(TRUE)
	{
		errRet = medicineDB.GetMedicines(dwPageNum++, g_ciNumPerPage, dwTotalPage, dwTotalNum, vctMedicine);
		if (errRet != err_OK)
		{
			MessageBox(_T("导出失败！"), _T(""), MB_ICONERROR);
			break;
		}

		if (vctMedicine.size() == 0)
		{
			break;
		}

		for (int i = 0; i < (int)vctMedicine.size(); i++)
		{
			Medicine *pMedicine = vctMedicine[i];
			if (pMedicine == NULL)
			{
				continue;
			}

			fprintf_s(pFile,_T("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\r\n"), 
					pMedicine->csID,
					pMedicine->csSN,
					pMedicine->csName,
					pMedicine->csSpec,
					pMedicine->csVendorName,
					pMedicine->csCreateTime,
					pMedicine->csModifyTime,
					pMedicine->util.csID,
					pMedicine->csRetailPrice,
					pMedicine->type.csID,
					pMedicine->medicineClass.csID,
					pMedicine->OTC.csID,
					pMedicine->form.csID,
					pMedicine->csSupplierCount);

			delete pMedicine;
			pMedicine = NULL;
		}
		vctMedicine.clear();

		fflush(pFile);
	} 

	if (pFile != NULL)
	{
		fclose(pFile);
		pFile = NULL;
	}

	MessageBox(_T("导出成功！"), _T(""), MB_ICONINFORMATION);
}


void CMedicineImportDlg::OnBnClickedImport()
{
	// TODO: Add your control notification handler code here

	CString csPath;
	m_editImport.GetWindowText(csPath);

	FILE *pFile = NULL;
	fopen_s(&pFile, csPath.GetBuffer(), "r");
	if (pFile == NULL)
	{
		MessageBox(_T("导入文件打开失败！"), _T(""), MB_ICONERROR);
		return;
	}

	ERRCODE errRet = err_OK;
	CMedicineDB medicineDB;
	CVendorDB vendorDB;
	DWORD dwTotalNum = 0, dwSuccussNum = 0;
	TCHAR tszBuf[1024];
	memset(tszBuf, 0, 1024);
	 
	fseek(pFile, 0L, SEEK_SET);
	while (fgets(tszBuf, 1024, pFile) != NULL)
	{
		dwTotalNum++;

		Medicine medicine;
		Vendor vendor;

		TCHAR *pBuf = tszBuf;
		TCHAR *pPos = strstr(pBuf, _T(","));
		if (pPos == NULL)
		{
			continue;
		}
		pPos[0] = 0;
		medicine.csID = pBuf;
		pBuf = pPos + 1;

		pPos = strstr(pBuf, _T(","));
		if (pPos == NULL)
		{
			continue;
		}
		pPos[0] = 0;
		medicine.csSN = pBuf;
		pBuf = pPos + 1;

		pPos = strstr(pBuf, _T(","));
		if (pPos == NULL)
		{
			continue;
		}
		pPos[0] = 0;
		medicine.csName = pBuf;
		pBuf = pPos + 1;

		pPos = strstr(pBuf, _T(","));
		if (pPos == NULL)
		{
			continue;
		}
		pPos[0] = 0;
		medicine.csSpec = pBuf;
		pBuf = pPos + 1;

		pPos = strstr(pBuf, _T(","));
		if (pPos == NULL)
		{
			continue;
		}
		pPos[0] = 0;
		medicine.csVendorName = pBuf;
		pBuf = pPos + 1;

		pPos = strstr(pBuf, _T(","));
		if (pPos == NULL)
		{
			continue;
		}
		pPos[0] = 0;
		medicine.csCreateTime = pBuf;
		pBuf = pPos + 1;

		pPos = strstr(pBuf, _T(","));
		if (pPos == NULL)
		{
			continue;
		}
		pPos[0] = 0;
		medicine.csModifyTime = pBuf;
		pBuf = pPos + 1;

		pPos = strstr(pBuf, _T(","));
		if (pPos == NULL)
		{
			continue;
		}
		pPos[0] = 0;
		medicine.util.csID = pBuf;
		pBuf = pPos + 1;

		pPos = strstr(pBuf, _T(","));
		if (pPos == NULL)
		{
			continue;
		}
		pPos[0] = 0;
		medicine.csRetailPrice = pBuf;
		pBuf = pPos + 1;

		pPos = strstr(pBuf, _T(","));
		if (pPos == NULL)
		{
			continue;
		}
		pPos[0] = 0;
		medicine.type.csID = pBuf;
		pBuf = pPos + 1;

		pPos = strstr(pBuf, _T(","));
		if (pPos == NULL)
		{
			continue;
		}
		pPos[0] = 0;
		medicine.medicineClass.csID = pBuf;
		pBuf = pPos + 1;

		pPos = strstr(pBuf, _T(","));
		if (pPos == NULL)
		{
			continue;
		}
		pPos[0] = 0;
		medicine.OTC.csID = pBuf;
		pBuf = pPos + 1;

		pPos = strstr(pBuf, _T(","));
		if (pPos == NULL)
		{
			continue;
		}
		pPos[0] = 0;
		medicine.form.csID = pBuf;
		pBuf = pPos + 1;

		medicine.csSupplierCount = pBuf;

		vendor.csName = medicine.csVendorName;
		errRet = vendorDB.AddVendor(&vendor);

		errRet = vendorDB.GetVendorByName(vendor.csName.GetBuffer(), &vendor);
		if (errRet == err_OK)
		{
			medicine.csVendorID = vendor.csID;
		}

		BOOL bExist = FALSE;
		medicineDB.CheckMedicineExistBySN(medicine.csSN.GetBuffer(), bExist);
		if (bExist == FALSE)
		{
			errRet = medicineDB.AddMedicine(&medicine);
			if (errRet == err_OK)
			{
				dwSuccussNum++;
			}
		}
	}
	
	if (pFile != NULL)
	{
		fclose(pFile);
		pFile = NULL;
	}

	CString csMsg;
	csMsg.Format(_T("导入完成：共%d项，成功%d项目。"), dwTotalNum, dwSuccussNum);
	MessageBox(csMsg, _T(""), MB_ICONINFORMATION);
}
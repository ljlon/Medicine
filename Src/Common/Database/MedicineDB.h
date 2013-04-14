#pragma once
#include "StdHead.h"
#include "Database.h"

//Medicne
#define PROCEDURE_MEDICINE_GET _T("medicine_get")
#define PROCEDURE_MEDICINE_SELECT _T("medicine_select")
#define PROCEDURE_MEDICINE_SELECT_BYSN _T("medicine_select_by_sn")
#define PROCEDURE_MEDICINE_ADD _T("medicine_add")
#define PROCEDURE_MEDICINE_UPDATE _T("medicine_update")
#define PROCEDURE_MEDICINE_UPDATE_RETAILPRICE  _T("medicine_update_retail_price")
#define PROCEDURE_MEDICINE_CHECKEXIST _T("medicine_check_exist")
#define PROCEDURE_MEDICINE_CHECKEXIST_BYSN _T("medicine_check_exist_by_sn")
#define PROCEDURE_MEDICINE_DELETE _T("medicine_delete")

//Medicne Unit
#define PROCEDURE_MEDICINEUNIT_GET _T("medicineunit_get")
#define PROCEDURE_MEDICINEUNIT_SELECT _T("medicineunit_select")

//Medicne Type
#define PROCEDURE_MEDICINETYPE_GET _T("medicinetype_get")
#define PROCEDURE_MEDICINETYPE_SELECT _T("medicinetype_select")

//Medicne OTC
#define PROCEDURE_MEDICINEOTC_GET _T("medicineOTC_get")
#define PROCEDURE_MEDICINEOTC_SELECT _T("medicineOTC_select")

//Medicne Form
#define PROCEDURE_MEDICINEFORM_GET _T("medicineform_get")
#define PROCEDURE_MEDICINEFORM_SELECT _T("medicineform_select")

typedef struct _MedicineType
{
	CString csID;
	CString csName;
}MedicineType;

typedef struct _MedicineOTC
{
	CString csID;
	CString csName;
}MedicineOTC;

typedef struct _MedicineForm
{
	CString csID;
	CString csName;
}MedicineForm;

typedef struct _MedicineUtil
{
	CString csID;
	CString csName;
}MedicineUtil;

typedef struct _MedicineClass
{
	CString csID;
	CString csName;
}MedicineClass;

typedef struct _Medicine
{
	CString csID;
	CString csSN;
	CString csName;
	CString csSpec;
	CString csVendorID;
	CString csVendorName;
	CString csCreateTime;
	CString csModifyTime;
	CString csRetailPrice;
	MedicineUtil util;
	MedicineClass medicineClass;
	MedicineType type;
	MedicineOTC OTC;
	MedicineForm form;
	CString csSupplierCount;
}Medicine;

class CMedicineDB
{
public:
	CMedicineDB();
	~CMedicineDB();

	//Medicine
	ERRCODE GetMedicine(LPTSTR lpID, Medicine* pMedicine);
	ERRCODE GetMedicineBySN(LPTSTR lpSN, Medicine* pMedicine);
	ERRCODE GetMedicines(DWORD dwPageNum, 
						DWORD dwNumPerPage, 
						DWORD &dwTotalPage, 
						DWORD &dwTotalNum, 
						vector<Medicine*> &vctMedicines, 
						LPTSTR lpMedicineSN = NULL, 
						LPTSTR lpMedicineName = NULL,
						LPTSTR lpVendorID = NULL);
	ERRCODE AddMedicine(Medicine *pMedicine);
	ERRCODE UpdateMedicine(LPTSTR lpID, Medicine *pMedicine);
	ERRCODE UpdateMedicineRetailPrice(LPTSTR lpID, double dbRetailPrice);
	ERRCODE DeleteMedicine(LPTSTR lpID);
	ERRCODE CheckMedicineExist(LPTSTR lpMedicineID, BOOL& bExist);
	ERRCODE CheckMedicineExistBySN(LPTSTR lpMedicineSN, BOOL& bExist);

	//Medicine Unit
	ERRCODE GetMedicineUnit(int iUnitID, MedicineUtil *pMedicineUtil);
	ERRCODE GetMedicineUnits(vector<MedicineUtil*> &vctMedicineUtils);

	//Medicine Type
	ERRCODE GetMedicineType(int iTypeID, MedicineType *pMedicineType);
	ERRCODE GetMedicineTypes(vector<MedicineType*> &vctMedicineTypes);

	//Medicine OTC
	ERRCODE GetMedicineOTC(int iOTCID, MedicineOTC *pMedicineOTC);
	ERRCODE GetMedicineOTCs(vector<MedicineOTC*> &vctMedicineOTCs);

	//Medicine Form
	ERRCODE GetMedicineForm(int iFormID, MedicineForm *pMedicineForm);
	ERRCODE GetMedicineForms(vector<MedicineForm*> &vctMedicineForms);

private:
	CDatabase m_database;
};
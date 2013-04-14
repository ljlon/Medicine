
// ManagerDoc.h : CManagerDoc 类的接口
//


#pragma once
#include "StdHead.h"
#include "MedicineDB.h"
#include "SupplierMedicineDB.h"
#include "StoreDB.h"
#include <map>

using namespace std;

enum TreeMenuID{
	TREE_ROOT_ID =  0,
	TREE_BASIC_ID,
	TREE_SUPPLIER_ID,
	TREE_SUPPLIER_ADD,
	TREE_VENDOR_ID,
	TREE_VENDOR_ADD,
	TREE_MEDICINE_ID,
	TREE_MEDICINE_ADD,
	TREE_PURCHASE_ID,
	TREE_PURCHASE_ADD,
	TREE_PURCHASE_LIST,
	TREE_RETAIL_ID,
	TREE_STORE_ID,
	TREE_STORE_EDIT_ID,
	//TREE_STORE_BATCH_EDIT_ID,
	TREE_USER_ID,
	TREE_USER_ADD,
	TREE_ACCOUNT_ID,
	TREE_ACCOUNT_NEWPWS,
	TREE_BACKUP_ID,
	TREE_END_ID,
};

enum EnumViewType{
	VIEW_NONE = -1,
	VIEW_NEW = 0,
	VIEW_EDIT,
	VIEW_SUBNEW
};

CString GetMenuName(TreeMenuID id);
TreeMenuID GetMenuID(LPSTR lpMenuName);

typedef struct _PURMGRVIEW_CONTEXT
{
	CString csSupplierID;
	vector<vector<CString>> m_vctPurchaseList;
}PURMGRVIEW_CONTEXT;

typedef struct _MEDICINEADDVIEW_CONTEXT
{
	EnumViewType viewType;
	Medicine medicine;
	map<LONG, SupplierMedicine*> mapVctSupplierMedicine;
	map<LONG, SupplierMedicine*> mapVctDelSupplierMedicine;
}MEDICINEADDVIEW_CONTEXT;

typedef struct _STOREEDITVIEW_CONTEXT
{
	EnumViewType viewType;
	MedicineStore      medicineStore;
	vector<MedicineBatchStore*> vctBatchStore;

	~_STOREEDITVIEW_CONTEXT()
	{
		for (unsigned int i = 0; i < vctBatchStore.size(); i++)
		{
			delete vctBatchStore[i];
			vctBatchStore[i] = NULL;
		}
		vctBatchStore.clear();
	}
}STOREEDITVIEW_CONTEXT;

class CManagerDoc : public CDocument
{
protected: // 仅从序列化创建
	CManagerDoc();
	DECLARE_DYNCREATE(CManagerDoc)

// 特性
public:
	EnumViewType m_viewType;

	//MenuView
	TreeStruct m_menuTree;

	//SupplierMgrView
	CString m_csSupplierID;

	//VendorMgrView
	CString m_csVendorID;

	//MedicineMgrView
	CString m_csMedicineID;
	CString m_csMedicineSN;

	//MedicineAddView
	MEDICINEADDVIEW_CONTEXT *m_pMedicAddViewContext;

	//PurchaseMgrView
	PURMGRVIEW_CONTEXT *m_pPurMgrViewContext;

	//UserMgrView
	CString m_csUserUID;

	//StoreMgrView
	CString m_csStoreID;

	//StoreEditView
	STOREEDITVIEW_CONTEXT *m_pStoreEditViewContext;

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CManagerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

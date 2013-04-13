
// ManagerDoc.cpp : CManagerDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Manager.h"
#endif

#include "ManagerDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


TCHAR * pszMenuName[] =							// 0x01
{
	_T("首页"),
	_T("基本档案"),
	_T("供应商管理"),
	_T("添加供应商"),
	_T("生产厂家管理"),
	_T("添加生产厂家"),
	_T("药品管理"),
	_T("添加药品"),
	_T("进货管理"),
	_T("进货"),
	_T("进货清单"),
	_T("销售管理"),
	_T("库存管理"),
	_T("修改库存"),
	_T("用户管理"),
	_T("添加用户"),
	_T("个人信息"),
	_T("修改密码"),
	_T("数据安全"),
	NULL
};

CString GetMenuName(TreeMenuID id)
{
	CString csMenuName;
	if (id < 0 || id > TREE_END_ID)
	{

	}
	else if (pszMenuName[id] != NULL)
	{
		csMenuName = LPTSTR(pszMenuName[id]);
	}	

	return csMenuName;
}

TreeMenuID GetMenuID(LPSTR lpMenuName)
{
	TreeMenuID treeMenuID = TREE_ROOT_ID;
	CString csMenuName = lpMenuName;
	for (unsigned int i = 0; i < TREE_END_ID; i++)
	{
		if (!strcmp(lpMenuName, pszMenuName[i]))
		{
			treeMenuID = (TreeMenuID)i;
			break;;
		}
	}

	return treeMenuID;
}

// CManagerDoc

IMPLEMENT_DYNCREATE(CManagerDoc, CDocument)

BEGIN_MESSAGE_MAP(CManagerDoc, CDocument)
END_MESSAGE_MAP()


// CManagerDoc 构造/析构

CManagerDoc::CManagerDoc()
{
	// TODO: 在此添加一次性构造代码
	m_viewType = VIEW_NONE;
	m_csSupplierID = _T("");
	m_csVendorID = _T("");

	m_pPurMgrViewContext = NULL;
	m_pMedicAddViewContext = NULL;
	m_pStoreEditViewContext = NULL;
}

CManagerDoc::~CManagerDoc()
{
	if (m_pPurMgrViewContext != NULL)
	{
		delete m_pPurMgrViewContext;
		m_pPurMgrViewContext = NULL;
	}

	if (m_pMedicAddViewContext != NULL)
	{
		delete m_pMedicAddViewContext;
		m_pMedicAddViewContext = NULL;
	}

	if (m_pStoreEditViewContext != NULL)
	{
		delete m_pStoreEditViewContext;
		m_pStoreEditViewContext = NULL;
	}
}

BOOL CManagerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	int iUserRole = atoi(theApp.m_curUser.csRole);

	m_menuTree.csNodeName = GetMenuName(TREE_ROOT_ID);
	
	//基本信息
	TreeStruct *pBasicInfoTree = new TreeStruct;
	pBasicInfoTree->csNodeName = GetMenuName(TREE_BASIC_ID);
	m_menuTree.vctChildTree.push_back(pBasicInfoTree);

	TreeStruct *pSupplierTree = new TreeStruct; 
	pSupplierTree->csNodeName = GetMenuName(TREE_SUPPLIER_ID);
	pBasicInfoTree->vctChildTree.push_back(pSupplierTree);
	TreeStruct *pVendorTree = new TreeStruct; 
	pVendorTree->csNodeName = GetMenuName(TREE_VENDOR_ID);
	pBasicInfoTree->vctChildTree.push_back(pVendorTree);
	TreeStruct *pMedicineTree = new TreeStruct; 
	pMedicineTree->csNodeName = GetMenuName(TREE_MEDICINE_ID);
	pBasicInfoTree->vctChildTree.push_back(pMedicineTree);

	//采购管理
	TreeStruct *pPurMgrTree = new TreeStruct;
	pPurMgrTree->csNodeName = GetMenuName(TREE_PURCHASE_ID);
	m_menuTree.vctChildTree.push_back(pPurMgrTree);
	TreeStruct *pPurAddTree = new TreeStruct; 
	pPurAddTree->csNodeName = GetMenuName(TREE_PURCHASE_ADD);
	pPurMgrTree->vctChildTree.push_back(pPurAddTree);
	TreeStruct *pPurListTree = new TreeStruct; 
	pPurListTree->csNodeName = GetMenuName(TREE_PURCHASE_LIST);
	pPurMgrTree->vctChildTree.push_back(pPurListTree);
	/*TreeStruct *pPurHistoryTree = new TreeStruct; 
	pPurHistoryTree->csNodeName = GetMenuName(TREE_PURCHASE_HISTORY);
	pPurMgrTree->vctChildTree.push_back(pPurHistoryTree);*/
	
	//零售管理
	TreeStruct *pRetailMgrTree = new TreeStruct;
	pRetailMgrTree->csNodeName = GetMenuName(TREE_RETAIL_ID);
	m_menuTree.vctChildTree.push_back(pRetailMgrTree);

	//库存管理
	if (iUserRole == Role_Supper || iUserRole == Role_Manager || iUserRole == Role_DataEntryClerk)
	{
		TreeStruct *pStoreMgrTree = new TreeStruct;
		pStoreMgrTree->csNodeName = GetMenuName(TREE_STORE_ID);
		m_menuTree.vctChildTree.push_back(pStoreMgrTree);
	}

	//用户管理
	if (iUserRole == Role_Supper || iUserRole == Role_Manager)
	{
		TreeStruct *pUserMgrTree = new TreeStruct;
		pUserMgrTree->csNodeName = GetMenuName(TREE_USER_ID);
		m_menuTree.vctChildTree.push_back(pUserMgrTree);
	}	

	//个人信息
	TreeStruct *pAccountTree = new TreeStruct;
	pAccountTree->csNodeName = GetMenuName(TREE_ACCOUNT_ID);
	m_menuTree.vctChildTree.push_back(pAccountTree);

	//数据安全
	if (iUserRole == Role_Supper || iUserRole == Role_Manager)
	{
		TreeStruct *pBackup = new TreeStruct;
		pBackup->csNodeName = GetMenuName(TREE_BACKUP_ID);
		m_menuTree.vctChildTree.push_back(pBackup);
	}

	return TRUE;
}


// CManagerDoc 序列化

void CManagerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CManagerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CManagerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CManagerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CManagerDoc 诊断

#ifdef _DEBUG
void CManagerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CManagerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CManagerDoc 命令

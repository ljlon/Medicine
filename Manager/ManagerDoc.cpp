
// ManagerDoc.cpp : CManagerDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	_T("��ҳ"),
	_T("��������"),
	_T("��Ӧ�̹���"),
	_T("��ӹ�Ӧ��"),
	_T("�������ҹ���"),
	_T("�����������"),
	_T("ҩƷ����"),
	_T("���ҩƷ"),
	_T("��������"),
	_T("����"),
	_T("�����嵥"),
	_T("���۹���"),
	_T("������"),
	_T("�޸Ŀ��"),
	_T("�û�����"),
	_T("����û�"),
	_T("������Ϣ"),
	_T("�޸�����"),
	_T("���ݰ�ȫ"),
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


// CManagerDoc ����/����

CManagerDoc::CManagerDoc()
{
	// TODO: �ڴ����һ���Թ������
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

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	int iUserRole = atoi(theApp.m_curUser.csRole);

	m_menuTree.csNodeName = GetMenuName(TREE_ROOT_ID);
	
	//������Ϣ
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

	//�ɹ�����
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
	
	//���۹���
	TreeStruct *pRetailMgrTree = new TreeStruct;
	pRetailMgrTree->csNodeName = GetMenuName(TREE_RETAIL_ID);
	m_menuTree.vctChildTree.push_back(pRetailMgrTree);

	//������
	if (iUserRole == Role_Supper || iUserRole == Role_Manager || iUserRole == Role_DataEntryClerk)
	{
		TreeStruct *pStoreMgrTree = new TreeStruct;
		pStoreMgrTree->csNodeName = GetMenuName(TREE_STORE_ID);
		m_menuTree.vctChildTree.push_back(pStoreMgrTree);
	}

	//�û�����
	if (iUserRole == Role_Supper || iUserRole == Role_Manager)
	{
		TreeStruct *pUserMgrTree = new TreeStruct;
		pUserMgrTree->csNodeName = GetMenuName(TREE_USER_ID);
		m_menuTree.vctChildTree.push_back(pUserMgrTree);
	}	

	//������Ϣ
	TreeStruct *pAccountTree = new TreeStruct;
	pAccountTree->csNodeName = GetMenuName(TREE_ACCOUNT_ID);
	m_menuTree.vctChildTree.push_back(pAccountTree);

	//���ݰ�ȫ
	if (iUserRole == Role_Supper || iUserRole == Role_Manager)
	{
		TreeStruct *pBackup = new TreeStruct;
		pBackup->csNodeName = GetMenuName(TREE_BACKUP_ID);
		m_menuTree.vctChildTree.push_back(pBackup);
	}

	return TRUE;
}


// CManagerDoc ���л�

void CManagerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CManagerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CManagerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CManagerDoc ���

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


// CManagerDoc ����

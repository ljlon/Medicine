#pragma once
#include <vector>
#include <map>

using namespace std;

//Message
const UINT WM_RICHLISTCTRL_MESSGAE = ::RegisterWindowMessage(_T("WM_RICHLISTCTRL_MESSGAE"));
const UINT WM_RICHLS_CLICK_BUTTON = 1;

//Rich Stype
#define LVS_RICH_DRAWREMAIN 0x1

//List Item nID
#define LIST_ITEM_ID_BENGIN  10000

//Ctrl Style
enum EnumCtrlType{
	CTRL_DEFAULT = 0,
	CTRL_STATIC,
	CTRL_EDIT,
	CTRL_COMBOBOX,
	CTRL_BUTTON,
};

//
typedef struct _ListSubItem{
	EnumCtrlType itemType;
	CString csText;
	UINT nID; 
	CWnd *pItem;

	_ListSubItem()
	{
		itemType = CTRL_DEFAULT;
		csText = _T("");
		nID = NULL;
		pItem = NULL;
	}
	~_ListSubItem()
	{
		if (pItem != NULL)
		{
			delete pItem;
			pItem = NULL;
		}
	}
}ListSubItem;

class CRichListCtrl : public CListCtrl
{
public:
	CRichListCtrl();
	~CRichListCtrl();
	
	void SetExtendedStyle(DWORD dwExStyle);
	void SetRichStyle(DWORD dwRichStype);
	void SetItemHeight(int iHeight);
	int InsertItem(int nItem, LPCTSTR lpszItem, EnumCtrlType ctrlType = CTRL_STATIC); 
	BOOL SetItemText(int nItem, int nSubItem, LPCTSTR lpszText, EnumCtrlType ctrlType = CTRL_STATIC);
	EnumCtrlType GetItemType( int nItem, int nSubItem);
	BOOL DeleteItem(int nItem);
	BOOL DeleteAllItems();

protected:
	unsigned int m_iListItemHeight;
	DWORD m_dwExStyle;
	DWORD m_dwRichStype;
	vector<map<int, ListSubItem*>> m_vctItem;
	UINT m_nListItemID;

protected:
	DECLARE_MESSAGE_MAP()  
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);  
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	void DrawItem(CDC* pDC, int nItem, CRect &rcItem);
	void DrawSubItem(CDC *pDC, int nItem, int nSubItem, CRect &rcSubItem, bool bSelected, bool bFocus);  
	void DrawRowBK(CDC *pDC, RECT rc, bool bSelected, bool bFocus,int nRow);  
	void DrawRemainItems(CDC* pDC, CRect &rect);
};
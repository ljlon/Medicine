#include "StdAfx.h"
#include "RichListCtrl.h"

CRichListCtrl::CRichListCtrl()
{
	m_iListItemHeight = 24;
	m_dwExStyle = 0;
	m_dwRichStype = 0;
	m_nListItemID = LIST_ITEM_ID_BENGIN;
}

CRichListCtrl::~CRichListCtrl()
{
	DeleteAllItems();
}

BEGIN_MESSAGE_MAP(CRichListCtrl, CListCtrl)  
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CRichListCtrl::OnNMCustomdraw)
END_MESSAGE_MAP()  
  
BOOL CRichListCtrl::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_LBUTTONUP)
	{
		int nBtnID = GetWindowLong(pMsg->hwnd,GWL_ID); 
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(&pt);
		LVHITTESTINFO hitInfo;
		hitInfo.pt=pt;
		SubItemHitTest(&hitInfo);
		if (GetItemType(hitInfo.iItem, hitInfo.iSubItem) == CTRL_BUTTON)
		{
			this->GetParent()->SendMessage(WM_RICHLISTCTRL_MESSGAE, WM_RICHLS_CLICK_BUTTON, (LPARAM)&hitInfo); 
			return TRUE;
		}
		
	}
	return CListCtrl::PreTranslateMessage(pMsg);
}

void CRichListCtrl::SetExtendedStyle(DWORD dwExStyle)
{
	m_dwExStyle = dwExStyle;
	CListCtrl::SetExtendedStyle(dwExStyle);
}

void CRichListCtrl::SetRichStyle(DWORD dwRichStype)
{
	m_dwRichStype = dwRichStype;
}

int CRichListCtrl::InsertItem(int nItem, LPCTSTR lpszItem, EnumCtrlType ctrlType)
{
	CListCtrl::InsertItem(nItem, lpszItem);

	map<int, ListSubItem*> mapSubItem;
	ListSubItem *pListSubItem = new ListSubItem;

	pListSubItem->itemType = ctrlType;
	pListSubItem->csText = lpszItem;
	pListSubItem->nID = m_nListItemID++;
	switch(ctrlType)
	{
	case CTRL_BUTTON:
		pListSubItem->pItem = new CButton();
		((CButton*)(pListSubItem->pItem))->Create(pListSubItem->csText, WS_CHILD|WS_VISIBLE|WS_TABSTOP, CRect(0,0,0,0), this, pListSubItem->nID);

		break;

	default:
		break;
	}
	mapSubItem.insert(map<int, ListSubItem*>::value_type(0, pListSubItem));

	if (nItem < (int)m_vctItem.size())
	{
		m_vctItem.push_back(m_vctItem[m_vctItem.size() - 1]);

		for (int i = (int)m_vctItem.size() - 1; i > nItem; i--)
		{
			m_vctItem[i] = m_vctItem[i - 1];
		}
		m_vctItem[nItem] = mapSubItem;
	}
	else if (nItem == m_vctItem.size())
	{
		m_vctItem.push_back(mapSubItem);
	}

	return 0;
}


BOOL CRichListCtrl::SetItemText(_In_ int nItem, _In_ int nSubItem, _In_z_ LPCTSTR lpszText, EnumCtrlType ctrlType)
{
	if (nItem < 0 || nItem >= (int)m_vctItem.size())
	{
		return FALSE;
	}

	ListSubItem *pListSubItem = NULL;
	map<int, ListSubItem*>::iterator it = m_vctItem[nItem].find(nSubItem);
	if (it != m_vctItem[nItem].end())
	{
		pListSubItem = it->second;
		pListSubItem->itemType = ctrlType;
		pListSubItem->csText = lpszText;
		pListSubItem->nID = m_nListItemID++;
	}
	else
	{
		pListSubItem = new ListSubItem;

		pListSubItem->itemType = ctrlType;
		pListSubItem->csText = lpszText;
		pListSubItem->nID = m_nListItemID++;
		m_vctItem[nItem].insert(map<int, ListSubItem*>::value_type(nSubItem, pListSubItem));
	}

	if (pListSubItem->pItem != NULL)
	{
		delete pListSubItem->pItem;
		pListSubItem->pItem = NULL;
	}
	switch(ctrlType)
	{
	case CTRL_BUTTON:
		pListSubItem->pItem = new CButton();
		((CButton*)(pListSubItem->pItem))->Create(pListSubItem->csText, WS_CHILD|WS_VISIBLE|WS_TABSTOP, CRect(0,0,0,0), this, pListSubItem->nID);

		break;

	default:
		break;
	}

	return CListCtrl::SetItemText(nItem, nSubItem, lpszText);
}

BOOL CRichListCtrl::DeleteItem(int nItem)
{	
	if (nItem < 0 || nItem >= (int)m_vctItem.size())
	{
		return FALSE;
	}

	for (int i = 0; i < (int)m_vctItem[nItem].size(); i++)
	{
		if (m_vctItem[nItem][i] != NULL)
		{
			delete m_vctItem[nItem][i];
			m_vctItem[nItem][i] = NULL;
		}
	}
	m_vctItem[nItem].clear();

	for (int i = nItem; i < (int)m_vctItem.size() - 1; i++)
	{
		m_vctItem[i] = m_vctItem[i + 1];
	}

	m_vctItem.pop_back();

	BOOL bRet = TRUE;
	if (GetSafeHwnd() != NULL)
	{
		CListCtrl::DeleteItem(nItem);
	}
	return bRet;
}

BOOL CRichListCtrl::DeleteAllItems()
{
	for (int i = 0; i < (int)m_vctItem.size(); i++)
	{
		for (int j = 0; j < (int)m_vctItem[i].size(); j++)
		{
			if (m_vctItem[i][j] != NULL)
			{
				delete m_vctItem[i][j];
				m_vctItem[i][j] = NULL;
			}
		}
		m_vctItem[i].clear();
	}
	m_vctItem.clear();

	BOOL bRet = TRUE;

	if (GetSafeHwnd() != NULL)
	{
		CListCtrl::DeleteAllItems();
	}

	return bRet;
}

EnumCtrlType CRichListCtrl::GetItemType( int nItem, int nSubItem)
{
	if (nItem < 0 || nItem >= (int)m_vctItem.size())
	{
		return CTRL_DEFAULT;
	}

	map<int, ListSubItem*>::iterator it = m_vctItem[nItem].find(nSubItem);
	if (it != m_vctItem[nItem].end())
	{
		return it->second->itemType;
	}

	return CTRL_DEFAULT;
}

// CRichListCtrl message handlers  
void CRichListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)  
{  
    *pResult = 0;  
	LPNMLVCUSTOMDRAW lpnmcd = (LPNMLVCUSTOMDRAW) pNMHDR;  

	CString csMsg;

    if (lpnmcd ->nmcd.dwDrawStage == CDDS_PREPAINT)  
    {  
        *pResult = CDRF_NOTIFYITEMDRAW | CDRF_NOTIFYPOSTPAINT;  
        return;  
    }  
    else if (lpnmcd->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)  
    {  
        int iItem = lpnmcd->nmcd.dwItemSpec;  
        if (iItem >= 0 && iItem < (int)m_vctItem.size())  
        {  
			CRect rSubItem;  
			for (map<int, ListSubItem*>::iterator it = m_vctItem[iItem].begin(); it != m_vctItem[iItem].end(); it++)
			{
				if (it->second->itemType == CTRL_BUTTON)
				{
					GetSubItemRect(iItem, it->first, LVIR_LABEL,rSubItem);  
					if (it->first == 0)
					{
						rSubItem.left = 0;  
					}

					CButton *pButton = (CButton*)(it->second->pItem);
					if (pButton != NULL)
					{		
						pButton->ShowWindow(SW_SHOW);
						pButton->MoveWindow(rSubItem);		
					}
				}
			}
        }  

		*pResult = CDRF_NOTIFYSUBITEMDRAW;  
		return;  
    }  
	else if (lpnmcd ->nmcd.dwDrawStage == (CDDS_ITEMPREPAINT|CDDS_SUBITEM))
	{  
		int iItem = lpnmcd->nmcd.dwItemSpec;   
		int iSubItem = lpnmcd->iSubItem;  
		if (iItem >= 0 && iItem < (int)m_vctItem.size() && iSubItem >= 0)  
		{  
			CRect rSubItem;  
			HDC hDC = lpnmcd->nmcd.hdc;  
			GetSubItemRect(iItem, iSubItem, LVIR_LABEL,rSubItem);  
			if (iSubItem == 0)  
			{  
				rSubItem.left = 0;  
			}  

			bool bSelected = false;  
			if (GetItemState(iItem, LVIS_SELECTED))  
			{  
				bSelected = true;  
			}  

			bool bFocus = false;  
			CWnd *pWndFocus = GetFocus();  
			if (IsChild(pWndFocus) || pWndFocus == this)  
			{  
				bFocus = true;  
			}  

			map<int, ListSubItem*>::iterator it = m_vctItem[iItem].find(iSubItem);

			if (it == m_vctItem[iItem].end() || it->second->itemType == CTRL_STATIC)
			{
				CDC dc;  
				dc.Attach(lpnmcd->nmcd.hdc); 

				rSubItem.NormalizeRect();  
				DrawSubItem(&dc,iItem,iSubItem,rSubItem,bSelected,bFocus);  
				*pResult = CDRF_SKIPDEFAULT;

				dc.Detach();  
				return;  
			}
			else if (it->second->itemType == CTRL_BUTTON)
			{
				CButton *pButton = (CButton*)(it->second->pItem);
				if (pButton != NULL)
				{		
					pButton->ShowWindow(SW_SHOW);
					pButton->MoveWindow(rSubItem);

					*pResult = CDRF_SKIPDEFAULT;
					return;  
				}
			}
		}  
	}
    else if (lpnmcd ->nmcd.dwDrawStage == CDDS_POSTPAINT)  
    {  
		if (m_dwRichStype&LVS_RICH_DRAWREMAIN)
		{
			DrawRemainSpace(lpnmcd); 
		}
        *pResult = CDRF_SKIPDEFAULT;  
        return;  
    }  
       
    *pResult = 0;  
}  


// overwrite:  
void CRichListCtrl::DrawSubItem(CDC *pDC, int nItem, int nSubItem, CRect &rSubItem, bool bSelected, bool bFocus)  
{  
  
    pDC->SetBkMode(TRANSPARENT);  
    pDC->SetTextColor(RGB(0, 0, 0));  
    CFont font;  
    font.CreateFont(12,   // nHeight  
        0,                         // nWidth  
        0,                         // nEscapement  
        0,                         // nOrientation  
        FW_NORMAL,                 // nWeight  
        FALSE,                     // bItalic  
        FALSE,                     // bUnderline  
        0,                         // cStrikeOut  
        ANSI_CHARSET,              // nCharSet  
        OUT_DEFAULT_PRECIS,        // nOutPrecision  
        CLIP_DEFAULT_PRECIS,       // nClipPrecision  
        DEFAULT_QUALITY,           // nQuality  
        DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily  
        _T("宋体"));  
    pDC->SelectObject(&font);  
    CString strText;  
    strText = GetItemText(nItem, nSubItem);  
    DrawRowBK(pDC, rSubItem, bSelected, bFocus, nItem);  

	CRect drawRect;
	drawRect.left = rSubItem.left + 8;
	drawRect.right = rSubItem.right;
	drawRect.top = rSubItem.top;
	drawRect.bottom = rSubItem.bottom;
    pDC->DrawText(strText, strText.GetLength(), &drawRect, DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_END_ELLIPSIS);  
    
}  


// 画剩余部分  
void CRichListCtrl::DrawRemainSpace(LPNMLVCUSTOMDRAW lpnmcd)  
{  
    int nTop = lpnmcd->nmcd.rc.top;  
    int nCount = GetItemCount();  
    if (nCount > 0)  
    {  
        CRect rcItem;  
        GetItemRect(nCount - 1, &rcItem, LVIR_LABEL);  
        nTop = rcItem.bottom;  
    }  
    CRect rectClient;  
    GetClientRect(&rectClient);  
    if (nTop < lpnmcd->nmcd.rc.bottom) // 有剩余  
    {  
        CRect rcRemain = lpnmcd->nmcd.rc;  
        rcRemain.top = nTop;  
        rcRemain.right = rectClient.right;  
        int nRemainItem = rcRemain.Height(); // m_iListItemHeight;  
        if (rcRemain.Height() % m_iListItemHeight)  
        {  
            nRemainItem++;  
        }  
        int pos = GetScrollPos(SB_HORZ);  
        CDC dc;  
        dc.Attach(lpnmcd->nmcd.hdc);  
        for (int i = 0; i < nRemainItem; ++i)  
        {  
            CRect rcItem;  
            rcItem.top = rcRemain.top + i * m_iListItemHeight;  
            rcItem.left = rcRemain.left;  
            rcItem.right = rcRemain.right;  
            rcItem.bottom = rcItem.top + m_iListItemHeight;  
            int nColumnCount = GetHeaderCtrl()->GetItemCount();  
            CRect  rcSubItem;  
            for (int j = 0; j < nColumnCount; ++j)  
            {  
                GetHeaderCtrl()->GetItemRect(j, &rcSubItem);  
                rcSubItem.top = rcItem.top;  
                rcSubItem.bottom = rcItem.bottom;  
                rcSubItem.OffsetRect(-pos, 0);  
                if(rcSubItem.right < rcRemain.left || rcSubItem.left > rcRemain.right)  
                    continue;  
                DrawRowBK(&dc, rcSubItem, false, false, i + nCount);            
            }   
        }  
        dc.Detach();  
    }  
}  


void CRichListCtrl::DrawRowBK(CDC *pDC, RECT rc, bool bSelected, bool bFocus,int nRow)  
{   
    bool bOdd = (nRow % 2 == 0 ? true : false);  
    CRect rect = rc;  
    if (rect.Width() == 0)  
    {  
        return;  
    }  
       
    int nSave = pDC->SaveDC();  
    if (bSelected)  
    {  
        if (bFocus)  
        {  
            CBrush selectBrush;  
            selectBrush.CreateSolidBrush(RGB(203, 223, 239));  
            pDC->FillRect(&rc, &selectBrush);  
        }  
        else  
        {  
            CBrush selectNoFocusBrush;  
            selectNoFocusBrush.CreateSolidBrush(RGB(206, 206, 206));  
            pDC->FillRect(&rc, &selectNoFocusBrush);  
        }  
    }  
    else if (bOdd)  
    {  
        CBrush oddBrush;  
        oddBrush.CreateSolidBrush(RGB(255, 255, 255));  
        pDC->FillRect(&rc, &oddBrush);  
    }  
    else  
    {  
        CBrush normalBrush;  
        normalBrush.CreateSolidBrush(RGB(243, 243, 243));  
        pDC->FillRect(&rc, &normalBrush);  
    }  
  
    // 画竖线  
    CPen pen;  
    pen.CreatePen(PS_SOLID, 1, RGB(218, 218, 218));  
    pDC->SelectObject(&pen);  
    pDC->MoveTo(rc.right - 1, rc.top);  
    pDC->LineTo(rc.right - 1, rc.bottom);  
	pDC->MoveTo(rc.left, rc.bottom - 1);  
	pDC->LineTo(rc.right, rc.bottom - 1);  

    // 画选中的底部分割线  
    if (bSelected)  
    {  
        CPen bottomPen;  
        bottomPen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));  
        pDC->SelectObject(&bottomPen);  
        pDC->MoveTo(rc.left, rc.bottom - 1);  
        pDC->LineTo(rc.right, rc.bottom - 1);  
    }  
    pDC->RestoreDC(nSave);  
}  
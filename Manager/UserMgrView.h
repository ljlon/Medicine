#pragma once
#include "UserAddView.h"

// CUserMgrView form view

class CUserMgrView : public CFormView
{
	DECLARE_DYNCREATE(CUserMgrView)

public:
	CUserMgrView();           // protected constructor used by dynamic creation
	virtual ~CUserMgrView();

public:
	enum { IDD = IDD_USER_MANAGE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void AdjustLayout();
	void DisplayUsers();
	void DisplayUserList(vector<User*> vctUsers);
	void DisplayUserListItem(int iItem, User *pUser);

	CListCtrl m_listUser;
	CStatic m_staticPageInfo;
	CButton m_btnPrePage;
	CButton m_btnNextPage;
	CButton m_btnAdd;
	CButton m_btnEdit;
	CButton m_btnDel;
	CUserAddView *m_pActiveView;
	DWORD m_dwCurPage;
	DWORD m_dwTotalPage;
	DWORD m_dwTotalNum;
	vector<UserRole*> m_vctUserRoles;

public:
	afx_msg void OnLvnItemchangedListUser(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonUserAdd();
	afx_msg void OnBnClickedButtonUserEdit();
	afx_msg void OnBnClickedButtonUserDel();
	afx_msg void OnNMDblclkListUser(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnPrepage();
	afx_msg void OnBnClickedBtnNextpage();
};



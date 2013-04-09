// CfgGeneralDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POS.h"
#include "CfgGeneralDlg.h"
#include "afxdialogex.h"
#include "POSConfig.h"

// CCfgGeneralDlg 对话框

IMPLEMENT_DYNAMIC(CCfgGeneralDlg, CDialogEx)

CCfgGeneralDlg::CCfgGeneralDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCfgGeneralDlg::IDD, pParent)
{

}

CCfgGeneralDlg::~CCfgGeneralDlg()
{
}

void CCfgGeneralDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_COMPANY, m_editCompanyName);
	DDX_Control(pDX, IDC_EDIT_POSID, m_editPOSID);
}


BEGIN_MESSAGE_MAP(CCfgGeneralDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CCfgGeneralDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString csMsg;

	m_editCompanyName.SetWindowText(g_POSCfg.general_company_name);
	csMsg.Format(_T("%s"), theApp.m_curPOS.csID);
	m_editPOSID.SetWindowText(csMsg);

	return TRUE;
}

// CCfgGeneralDlg 消息处理程序
ERRCODE CCfgGeneralDlg::ApplyCfg(POSConfig &config)
{
	ERRCODE errRet = err_OK;

	CString csMsg, csCompanyName, csPOSID;
	m_editCompanyName.GetWindowText(csCompanyName);
	csCompanyName.Trim();
	if (csCompanyName == _T(""))
	{
		MessageBox(_T("公司名称不能为空！"), _T(""), MB_ICONERROR);
		return err_InvalidParameter;
	}

	config.general_company_name = csCompanyName.GetBuffer();

	CPOSDB POSDB;
	POS tempPOS;
	BOOL bExist = TRUE;
	m_editPOSID.GetWindowText(csPOSID);
	csPOSID.Trim();
	if (csPOSID != theApp.m_curPOS.csID)
	{
		errRet = POSDB.CheckPOSExist(atol(csPOSID.GetBuffer()), bExist);
		if (errRet != err_OK)
		{
			csMsg.Format(_T("配置POS机号失败，%s！"), GetErrMsg(errRet));
			MessageBox(csMsg, _T(""), MB_ICONERROR);
			return err_InvalidParameter;
		}
		if (bExist == TRUE)
		{
			csMsg.Format(_T("POS机号：%s已经存在，请重新输入！"), csPOSID);
			MessageBox(csMsg, _T(""), MB_ICONERROR);
			return err_InvalidParameter;
		}

		LONG lOldID = atol(theApp.m_curPOS.csID);
		tempPOS.csID = csPOSID.GetBuffer();
		tempPOS.csPCID = theApp.m_curPOS.csPCID;
		tempPOS.csPCMAC = theApp.m_curPOS.csPCMAC;
		errRet = POSDB.UpdatePOS(lOldID, &tempPOS);
		if (errRet != err_OK)
		{
			csMsg.Format(_T("配置POS机号失败，%s！"), GetErrMsg(errRet));
			MessageBox(csMsg, _T(""), MB_ICONERROR);
			return err_InvalidParameter;
		}

		theApp.m_curPOS.csID = tempPOS.csID;
	}

	return errRet;
}
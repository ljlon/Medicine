// CfgGeneralDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "POS.h"
#include "CfgGeneralDlg.h"
#include "afxdialogex.h"
#include "POSConfig.h"

// CCfgGeneralDlg �Ի���

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

// CCfgGeneralDlg ��Ϣ�������
ERRCODE CCfgGeneralDlg::ApplyCfg(POSConfig &config)
{
	ERRCODE errRet = err_OK;

	CString csMsg, csCompanyName, csPOSID;
	m_editCompanyName.GetWindowText(csCompanyName);
	csCompanyName.Trim();
	if (csCompanyName == _T(""))
	{
		MessageBox(_T("��˾���Ʋ���Ϊ�գ�"), _T(""), MB_ICONERROR);
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
			csMsg.Format(_T("����POS����ʧ�ܣ�%s��"), GetErrMsg(errRet));
			MessageBox(csMsg, _T(""), MB_ICONERROR);
			return err_InvalidParameter;
		}
		if (bExist == TRUE)
		{
			csMsg.Format(_T("POS���ţ�%s�Ѿ����ڣ����������룡"), csPOSID);
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
			csMsg.Format(_T("����POS����ʧ�ܣ�%s��"), GetErrMsg(errRet));
			MessageBox(csMsg, _T(""), MB_ICONERROR);
			return err_InvalidParameter;
		}

		theApp.m_curPOS.csID = tempPOS.csID;
	}

	return errRet;
}
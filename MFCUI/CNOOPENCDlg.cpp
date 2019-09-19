// CNOOPENCDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCUI.h"
#include "CNOOPENCDlg.h"
#include "afxdialogex.h"


// CNOOPENCDlg 对话框

IMPLEMENT_DYNAMIC(CNOOPENCDlg, CDialogEx)

CNOOPENCDlg::CNOOPENCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOOPENC, pParent)
{

}

CNOOPENCDlg::~CNOOPENCDlg()
{
}

void CNOOPENCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNOOPENCDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CNOOPENCDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CNOOPENCDlg 消息处理程序
BOOL CNOOPENCDlg::OnInitDialog()
{
	extern  CString strMessageBox5;
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC)->m_hWnd);
	mmmm_font.CreatePointFont(120, _T("微软雅黑"));
	GetDlgItem(IDC_STATIC)->SetFont(&mmmm_font);
	SetDlgItemText(IDC_STATIC, strMessageBox5);
	return TRUE;
}



void CNOOPENCDlg::OnBnClickedButton1()
{
	CDialog::OnOK();
}


HBRUSH CNOOPENCDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC:
	{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&mmmm_font);
	break; }
	}
	return hbr;
}

// CNOUniqueCDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCUI.h"
#include "CNOUniqueCDlg.h"
#include "afxdialogex.h"


// CNOUniqueCDlg 对话框

IMPLEMENT_DYNAMIC(CNOUniqueCDlg, CDialogEx)

CNOUniqueCDlg::CNOUniqueCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOUNIQUEC, pParent)
{

}

CNOUniqueCDlg::~CNOUniqueCDlg()
{
}

void CNOUniqueCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNOUniqueCDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CNOUniqueCDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CNOUniqueCDlg 消息处理程序
BOOL CNOUniqueCDlg::OnInitDialog()
{
	extern CString strMessageBox6;
    skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC)->m_hWnd);
	mmm_font.CreatePointFont(120, _T("微软雅黑"));
	GetDlgItem(IDC_STATIC)->SetFont(&mmm_font);
	SetDlgItemText(IDC_STATIC, strMessageBox6);
	return TRUE;
}


void CNOUniqueCDlg::OnBnClickedButton1()
{
	CDialog::OnOK();
}


HBRUSH CNOUniqueCDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC:
	{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&mmm_font);
	break; }
	}
	return hbr;
}

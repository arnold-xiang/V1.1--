// CNOCameraDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCUI.h"
#include "CNOCameraDlg.h"
#include "afxdialogex.h"


// CNOCameraDlg 对话框

IMPLEMENT_DYNAMIC(CNOCameraDlg, CDialogEx)

CNOCameraDlg::CNOCameraDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOCAMERA, pParent)
{

}

CNOCameraDlg::~CNOCameraDlg()
{
}

void CNOCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNOCameraDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CNOCameraDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CNOCameraDlg 消息处理程序
BOOL CNOCameraDlg::OnInitDialog()
{
	extern CString strMessageBox1;
    skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC)->m_hWnd);
	mm_font.CreatePointFont(120, _T("微软雅黑"));
	GetDlgItem(IDC_STATIC)->SetFont(&mm_font);
	SetDlgItemText(IDC_STATIC, strMessageBox1);
	return TRUE;
}


void CNOCameraDlg::OnBnClickedButton1()
{
	CDialog::OnOK();
}





HBRUSH CNOCameraDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC:
	{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&mm_font);
	break; }
	}
	return hbr;
}

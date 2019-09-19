// CNGDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCUI.h"
#include "CNGDlg.h"
#include "afxdialogex.h"


// CNGDlg 对话框

IMPLEMENT_DYNAMIC(CNGDlg, CDialogEx)

CNGDlg::CNGDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NG, pParent)
{

}

CNGDlg::~CNGDlg()
{
}

void CNGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNGDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CNGDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CNGDlg::OnBnClickedButton2)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CNGDlg 消息处理程序
BOOL CNGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATICR)->m_hWnd);
	mw_font.CreatePointFont(120, _T("微软雅黑"));
	GetDlgItem(IDC_STATICR)->SetFont(&mw_font);
	extern CString s1;
	extern CString s2;
	extern CString s3;
	extern CString strStaticDeal;
	extern CString strStaticFailed;
	extern CString strStaticTotal;


	SetDlgItemText(IDC_STATICR, _T(strStaticDeal+":"+s2+"个\n\n"+strStaticFailed+":"+s3+"个\n\n"+strStaticFailed+":"+s1+"个"));
	return TRUE;
}


void CNGDlg::OnBnClickedButton1()
{
	CDialog::OnOK();
}


void CNGDlg::OnBnClickedButton2()
{
	CDialog::OnOK();
}
HBRUSH CNGDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATICR:
	{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&mw_font);
	break; }
	
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	}
	return hbr;
}
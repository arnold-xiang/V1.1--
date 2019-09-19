// CWelcomeDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCUI.h"
#include "CWelcomeDlg.h"
#include "afxdialogex.h"


// CWelcomeDlg 对话框

IMPLEMENT_DYNAMIC(CWelcomeDlg, CDialogEx)

CWelcomeDlg::CWelcomeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WELCOME, pParent)
{

}

CWelcomeDlg::~CWelcomeDlg()
{
}

void CWelcomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWelcomeDlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CWelcomeDlg 消息处理程序
BOOL CWelcomeDlg::OnInitDialog()
{
	SetTimer(1, 3000, NULL);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC_Introduction)->m_hWnd);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC_SN)->m_hWnd);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC_Loading)->m_hWnd);
	//skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC_Adress)->m_hWnd);
	//skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC_Tel)->m_hWnd);
	//skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC_SN)->m_hWnd);
	/*skinppSetNoSkinHwnd(GetDlgItem(IDC_EDIT_Name)->m_hWnd);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_EDIT_Adress)->m_hWnd);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_EDIT_Tel)->m_hWnd);*/
	mw_font.CreatePointFont(150, _T("微软雅黑"));
	msw_font.CreatePointFont(80, _T("微软雅黑"));
	GetDlgItem(IDC_STATIC_Loading)->SetFont(&mw_font);
	GetDlgItem(IDC_STATIC_Introduction)->SetFont(&mw_font);
	GetDlgItem(IDC_STATIC_SN)->SetFont(&msw_font);
	/*GetDlgItem(IDC_STATIC_Name)->SetFont(&mw_font);
	GetDlgItem(IDC_STATIC_Adress)->SetFont(&mw_font);
	GetDlgItem(IDC_STATIC_Tel)->SetFont(&mw_font);
	GetDlgItem(IDC_STATIC_SN)->SetFont(&mw_font);
	GetDlgItem(IDC_STATIC_Introduction)->SetFont(&mw_font);
	GetDlgItem(IDC_EDIT_Name)->SetFont(&mw_font);
	GetDlgItem(IDC_EDIT_Adress)->SetFont(&mw_font);
	GetDlgItem(IDC_EDIT_Tel)->SetFont(&mw_font);
	SetDlgItemText(IDC_EDIT_Name, "上海****有限公司");
	SetDlgItemText(IDC_EDIT_Adress, "上海市徐汇区****");
	SetDlgItemText(IDC_EDIT_Tel, "166-2367-9035");*/

	/*if (-1 != GetFileAttributes("D:\\系统文件\\Welcome.txt"))
	{
		char *Buf;
		CFile myFile("D:\\系统文件\\Welcome.txt", CFile::typeText | CFile::modeRead);
		DWORD dwFileLen;
		dwFileLen = myFile.GetLength();
		Buf = new char[dwFileLen + 1];
		Buf[dwFileLen] = 0;
		myFile.Read(Buf, dwFileLen);
		myFile.Close();
		SetDlgItemText(IDC_STATIC_Introduction, Buf);
	}
	else
	{
		SetDlgItemText(IDC_STATIC_Introduction, "欢迎使用冻存管二维码自动识别采集系统");
	}*/
	extern CString strWelcome;
	GetPrivateProfileString("Text Info", "Welcome", "欢迎使用冻存管二维码自动采集识别系统", strWelcome.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\IniConfig.ini");
	SetDlgItemText(IDC_STATIC_Introduction, strWelcome);
	
	return TRUE;
}


void CWelcomeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		////SetDlgItemText(IDC_STATIC_Top, "nihao");
		//CWnd* hWnd = FindWindow(NULL, _T("欢迎bala"));
		//if (hWnd)
		//{
		//	hWnd->PostMessage(WM_CLOSE, NULL, NULL);
		//}
		KillTimer(1);   //关闭定时器
		OnOK();
		CDialogEx::OnTimer(nIDEvent);
	}
}

HBRUSH CWelcomeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_Loading:
	{pDC->SetTextColor(RGB(255, 255, 255)); pDC->SetBkColor(RGB(30, 76, 146)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(30, 76, 146)); pDC->SelectObject(&mw_font);
	break; }
	case IDC_STATIC_Introduction:
	{pDC->SetTextColor(RGB(255, 255, 255)); pDC->SetBkColor(RGB(30, 76, 146)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(30, 76, 146)); pDC->SelectObject(&mw_font);
	break; }
	/*case IDC_STATIC_Name:
	{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&mw_font);
	break; }
	case IDC_STATIC_Adress:
	{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&mw_font);
	break; }
	case IDC_STATIC_Tel:
	{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&mw_font);
	break; }*/
	case IDC_STATIC_SN:
	{pDC->SetTextColor(RGB(255, 255, 255)); pDC->SetBkColor(RGB(30, 76, 146)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(30, 76, 146)); pDC->SelectObject(&msw_font);
	break; }
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	}
	return hbr;
}


void CWelcomeDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(30, 76, 146));
}

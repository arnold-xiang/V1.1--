
// MFCUIDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCUI.h"
#include "MFCUIDlg.h"
#include "HalconCpp.h"
#include "Mysql.h"
#include "afxdialogex.h"
#include "mySplash.h"
//#include "CRemindDlg.h"
#include "CNGDlg.h"
#include "CNOCameraDlg.h"
#include "CNOUniqueCDlg.h"
#include "CNOOPENCDlg.h"
#include "MD5.h"
#include <iostream>
using namespace std;
using namespace HalconCpp;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//全局变量
int MoRow;
int MoCol;
CString s1;
CString s2;
CString s3;
CTime t1;
CRect rtWindow;
HObject  ho_Image, ho_ImageMirror;
HTuple m_htWindow,hv_Length;
HTuple  width, height;
HTuple DirectShow, hv_AcqHandle;
//缩放功能变量
float m_nDlgWidth;
float m_nDlgHeight;
float m_nWidth;
float m_nHeight;
float m_Multiple_width;
float m_Mutiple_heigth;
bool change_flag;
//控件变量定义
CString strTitle;
CString strWelcome;
CString strButtonOpen;
CString strButtonClose;
CString strButtonDeal;
CString strButtonImage;
CString strButtonSql;
CString strButtonTxt;
CString strButtonExcel;
CString strButtonOut;
CString strButtonChange;
CString strStaticTotal ;
CString strStaticDeal ;
CString strStaticFailed;
CString strStaticSize;
CString strStaticOutZone;
CString strStaticOutContent;
CString strStaticBoxInfoZone;
CString strStaticBoxNumber;
CString strStaticSampleType;
CString strStaticBoxDesc;
CString strStaticBoxLocation;
CString strStaticModifyZone;
CString strlistcontrolOrder;
CString strlistcontroIndex;
CString VarGrabWelcome;
CString strMessageBox1;
CString strMessageBox2;
CString strMessageBox3;
CString strMessageBox4;
CString strMessageBox5;
CString strMessageBox6;
CString strMessageBox7;
CString txtBoxInfo;
CString strSaveTime;
CString txtCryotubeInfo;




class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	HACCEL hAccel;
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCUIDlg 对话框




CMFCUIDlg::CMFCUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCUI_DIALOG, pParent)
	/*, Row(_T(""))
	, Column(_T(""))*/
	, Bar_Total(_T(""))
	, Bar_Dealed(_T(""))
	, BoxNumber(_T(""))
	, SampleType(_T(""))
	, BoxDescription(_T(""))
	, BoxLocation(_T(""))
	, m_ChangeContext(_T(""))
	, Outsql(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CMFCUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	/*DDX_Text(pDX, IDC_EDIT1_Row, Row);
	DDX_Text(pDX, IDC_EDIT2_Column, Column);*/
	DDX_Text(pDX, IDC_EDIT3_BoxNumber, BoxNumber);
	DDX_Text(pDX, IDC_EDIT4_SampleType, SampleType);
	DDX_Text(pDX, IDC_EDIT5_BoxDescription, BoxDescription);
	DDX_Text(pDX, IDC_EDIT6_BoxLocation, BoxLocation);
	DDX_Control(pDX, IDC_LIST, m_ListCtrl);
	DDX_Text(pDX, IDC_EDIT_ChangeContext, m_ChangeContext);
	DDX_Text(pDX, IDC_EDIT1_Total, Bar_Total);
	DDX_Text(pDX, IDC_EDIT1_Dealed, Bar_Dealed);
	//	DDX_Control(pDX, IDC_COMBO1, m_Device);
	DDX_Control(pDX, IDC_BUTTON2_Deal, B_Deal);
	DDX_Control(pDX, IDC_BUTTON3_Image, B_Image);
	DDX_Control(pDX, IDC_BUTTON4_Sql, B_Sql);
	DDX_Control(pDX, IDC_BUTTON5_Txt, B_Txt);
	DDX_Control(pDX, IDC_BUTTON5_Excel, B_Excel);
	DDX_Control(pDX, IDC_BUTTON_Exit, B_Exit);
	DDX_Control(pDX, IDC_BUTTON_ChangeContext, B_Change);
	DDX_Control(pDX, IDC_BUTTON_Grab, B_Grab);
	DDX_Control(pDX, IDC_COMBO1, m_Version);
	DDX_Control(pDX, IDC_BUTTON_OutSql, B_OutSql);
	DDX_Text(pDX, IDC_EDIT_OutSql, Outsql);
	DDX_Control(pDX, IDC_BUTTON_English, B_English);
	DDX_Control(pDX, IDC_BUTTON_Chinese, B_Chinese);
	DDX_Control(pDX, IDC_COMBO_Camera, m_Camera);
}

BEGIN_MESSAGE_MAP(CMFCUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON5_Txt, &CMFCUIDlg::OnBnClickedButton5Txt)
	ON_BN_CLICKED(IDC_BUTTON3_Image, &CMFCUIDlg::OnBnClickedButton3Image)
	ON_BN_CLICKED(IDC_BUTTON4_Sql, &CMFCUIDlg::OnBnClickedButton4Sql)
	ON_BN_CLICKED(IDC_BUTTON_ChangeContext, &CMFCUIDlg::OnBnClickedButtonChangecontext)
	ON_NOTIFY(NM_CLICK, IDC_LIST, &CMFCUIDlg::OnNMClickList)
	ON_BN_CLICKED(IDC_BUTTON_Exit, &CMFCUIDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON2_Deal, &CMFCUIDlg::OnBnClickedButton2Deal)
	ON_BN_CLICKED(IDC_BUTTON5_Excel, &CMFCUIDlg::OnBnClickedButton5Excel)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_Grab, &CMFCUIDlg::OnBnClickedButtonGrab)
	ON_BN_CLICKED(IDC_BUTTON_OutSql, &CMFCUIDlg::OnBnClickedButtonOutsql)
	ON_BN_CLICKED(IDC_BUTTON_English, &CMFCUIDlg::OnBnClickedButtonEnglish)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_Chinese, &CMFCUIDlg::OnBnClickedButtonChinese)
END_MESSAGE_MAP()


// CMFCUIDlg 消息处理程序

BOOL CMFCUIDlg::OnInitDialog()
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

	
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	
	GetClientRect(&m_rect);
	//启动动画
	//mySplash wndSplash;                 //创建启动窗口类的实例
	//wndSplash.Create(IDB_Logo);     //BMP图片的ID
	//wndSplash.CenterWindow();
	//wndSplash.UpdateWindow();          //send WM_PAINT
	//Sleep(3000);
	//wndSplash.DestroyWindow();//销毁初始画面窗口


	//标题
	//if (-1 != GetFileAttributes("D:\\系统文件\\Title.txt"))
	//{
	//	char *Buf;
	//	CFile myFile("D:\\系统文件\\Title.txt", CFile::typeText | CFile::modeRead);
	//	DWORD dwFileLen;
	//	dwFileLen = myFile.GetLength();
	//	Buf = new char[dwFileLen + 1];
	//	Buf[dwFileLen] = 0;
	//	myFile.Read(Buf, dwFileLen);
	//	myFile.Close();
	//	SetWindowText(Buf);
	//}
	//else
	//{
	//	SetWindowText("冻存管二维码自动采集识别系统");
	//}
	GetPrivateProfileString("Text Info", "Title", "冻存管二维码自动采集识别系统", strTitle.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\IniConfig.ini");
	SetWindowText(strTitle);
	
	//背景色
	m_brush.CreateSolidBrush(RGB(226,234,226));

	m_Menu.LoadMenu(IDR_MENU1);
	this->SetMenu(&m_Menu);
	
	//取消某些控件皮肤
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC0)->m_hWnd);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC)->m_hWnd);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC_Total)->m_hWnd);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC_Dealed)->m_hWnd);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC7)->m_hWnd);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC8)->m_hWnd);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC9)->m_hWnd);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC10)->m_hWnd);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC11)->m_hWnd);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC14)->m_hWnd);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC18)->m_hWnd);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATICOutsql)->m_hWnd);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC_Language)->m_hWnd);
	skinppSetNoSkinHwnd(GetDlgItem(IDC_STATIC_Camera)->m_hWnd);
	//重绘按钮
	//B_Excel.SubclassDlgItem(IDC_BUTTON5_Excel, this);
	B_Excel.SetIcon(IDI_Excel);
	B_Excel.SetAlign(CButtonST::ST_ALIGN_VERT);
	B_Excel.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(236,233,216));//普通状态下背景色
	B_Excel.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(214, 217, 188));
	

	B_Grab.SetIcon(IDI_Grab);
	B_Grab.SetAlign(CButtonST::ST_ALIGN_VERT);
	B_Grab.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(236, 233, 216));
	B_Grab.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(214, 217, 188));

	B_Deal.SetIcon(IDI_ICON1);
	B_Deal.SetAlign(CButtonST::ST_ALIGN_VERT);
	B_Deal.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(236, 233, 216));
	B_Deal.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(214, 217, 188));

	B_Sql.SetIcon(IDI_Sql);
	B_Sql.SetAlign(CButtonST::ST_ALIGN_VERT);
	B_Sql.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(236, 233, 216));
	B_Sql.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(214, 217, 188));

	B_Txt.SetIcon(IDI_Txt);
	B_Txt.SetAlign(CButtonST::ST_ALIGN_VERT);
	B_Txt.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(236, 233, 216));
	B_Txt.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(214, 217, 188));

	B_Image.SetIcon(IDI_Image);
	B_Image.SetAlign(CButtonST::ST_ALIGN_VERT);
	B_Image.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(236, 233, 216));
	B_Image.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(214, 217, 188));
	
	B_Exit.SetIcon(IDI_Close);
	B_Exit.SetAlign(CButtonST::ST_ALIGN_VERT);
	B_Exit.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(236, 233, 216));
	B_Exit.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(214, 217, 188));

	B_Change.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(236, 233, 216));
	B_Change.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(214, 217, 188));

	B_OutSql.SetIcon(IDI_Delete);
	B_OutSql.SetAlign(CButtonST::ST_ALIGN_VERT);
	B_OutSql.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(214, 217, 188));
	B_OutSql.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(236, 233, 216));

	B_Chinese.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(236, 233, 216));
	B_Chinese.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(214, 217, 188));

	B_English.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(236, 233, 216));
	B_English.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(214, 217, 188));
	//获取当前时间
	t1 = CTime::GetCurrentTime();
	
	//给变量初始值
	VarGrabWelcome = "欢迎使用, 请先选择条码规格, 然后开始识别";
	txtBoxInfo = "盒子信息";
	strSaveTime = "导出时间";
	txtCryotubeInfo = "冻存管信息";
	strMessageBox1 = "没有在此设备上检测到任何可用的相机\n请确认是否已经连接相机";
	strMessageBox2 = "打开相机失败,请重试";
	strMessageBox3 = "操作失败,请重试";
	strMessageBox4 = "没有数据要存储!";
	strMessageBox5 = "无效的操作\n请先点击连接相机";
	strMessageBox6 = "无法打开指定的相机\n请确认相机的型号";
	strMessageBox7 = "数据库连接失败!";
	strStaticTotal = "总数";
	strStaticDeal = "识别";
	strStaticFailed = "未识别";
	strStaticBoxNumber = "盒子编号";
	strStaticSampleType = "标本类型";
	strStaticBoxDesc = "盒子描述";
	strStaticBoxLocation = "盒子位置";



	m_Version.AddString(str1);
	m_Version.AddString(str2);
	//m_Language.AddString(str3);
	//m_Language.AddString(str4);
	//m_Language.AddString(str5);
	//m_Language.AddString(str6);

	//设置字体
	m_font.CreatePointFont(100,_T("微软雅黑"));
	GetDlgItem(IDC_STATIC)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC7)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC8)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC9)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC10)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC11)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC14)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC18)->SetFont(&m_font);
	GetDlgItem(IDC_STATICOutsql)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC0)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_Total)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_Language)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON_Grab)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_Dealed)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON2_Deal)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON3_Image)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON4_Sql)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON5_Txt)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON5_Excel)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON_ChangeContext)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON_Exit)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON_OutSql)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON_Chinese)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON_English)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_Camera)->SetFont(&m_font);
	
	//加载快捷键
//	HACCEL m_hAccel = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR2));

	//初始化
	flag1 = false;
	init_list_control();
	//init_StatusBarr();
	BoxNumber = "0000";
	UpdateData(FALSE);
	SampleType = "NULL";
	UpdateData(FALSE);
	BoxDescription = "NULL";
	UpdateData(FALSE);
	BoxLocation = "NULL";
	UpdateData(FALSE);
	//m_ChangeContext = "00000";

	//获取相机参数
//获取相机参数
	HTuple hv_Information, hv_ValueList, hv_Length1;
	InfoFramegrabber("DirectShow", "device", &hv_Information, &hv_ValueList);
	TupleLength(hv_ValueList, &hv_Length1);
	if (0 == hv_Length1)
	{
		MessageBox("无法获取相机参数");
	}
	else
	{
		for (int i = 0; i < hv_Length1; i++)
		{
			m_Camera.AddString(hv_ValueList[i].S());
		}
	}
	
	//显示图片到picture控件
	
	HWND hImgWnd = GetDlgItem(IDC_STATIC_Image)->m_hWnd;
	GetDlgItem(IDC_STATIC_Image)->GetClientRect(&rtWindow);
	SetWindowAttr("background_color", "white");
	OpenWindow(rtWindow.left, rtWindow.top, rtWindow.Width(), rtWindow.Height(), (Hlong)hImgWnd, "visible", "", &m_htWindow);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	/*	Invalidate(FALSE);
		UpdateWindow();*/
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//缩放
void CMFCUIDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (nType != SIZE_MINIMIZED)
	{

		int a[38] = { IDC_STATIC,IDC_STATIC7,IDC_STATIC8,IDC_STATIC10,IDC_STATIC9,IDC_STATIC11,IDC_STATIC14,IDC_STATIC18,
			IDC_STATICOutsql,IDC_STATIC0,IDC_STATIC_Total,IDC_STATIC_Dealed, IDC_STATIC_Language ,IDC_BUTTON_Grab ,IDC_BUTTON2_Deal ,
		IDC_BUTTON3_Image ,IDC_BUTTON4_Sql ,IDC_BUTTON5_Txt ,IDC_BUTTON5_Excel ,IDC_BUTTON_ChangeContext ,IDC_BUTTON_Exit ,
		IDC_BUTTON_OutSql  ,IDC_BUTTON_English  ,IDC_BUTTON_Chinese,IDC_LIST ,IDC_EDIT1_Total ,IDC_EDIT1_Dealed ,
		IDC_STATIC5 ,IDC_STATIC1 ,IDC_STATIC4 ,IDC_EDIT_OutSql ,IDC_EDIT3_BoxNumber ,IDC_EDIT4_SampleType ,IDC_EDIT5_BoxDescription ,
		IDC_EDIT6_BoxLocation ,IDC_EDIT_ChangeContext, IDC_STATIC_Image,IDC_STATIC_Camera };
		int i;
		for (i = 0; i < 38; i++)
			Modifys(a[i], m_rect, cx, cy);
		Modify(IDC_COMBO1, m_rect, cx, cy);
		Modify(IDC_COMBO_Camera, m_rect, cx, cy);
		GetClientRect(&m_rect);//将变化后的对话框大小设为旧大小
	}

}
void CMFCUIDlg::Modifys(int idc, CRect client, int x, int y)
{
	CWnd *pWin;
	pWin = GetDlgItem(idc);//获取控件句柄
	if (pWin)//判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建
	{
		CRect Editrect;//获取控件变化前大小
		pWin->GetWindowRect(&Editrect);
		ScreenToClient(&Editrect);//将控件大小转换为在对话框中的区域坐标
		//x/client.Width()为对话框在横向的变化比例

		Editrect.left = Editrect.left*x / client.Width();//调整控件大小
		Editrect.right = Editrect.right*x / client.Width();
		Editrect.top = Editrect.top*y / client.Height();
		Editrect.bottom = Editrect.bottom*y / client.Height();
		pWin->MoveWindow(Editrect);//调整控件大小

	}

}
void CMFCUIDlg::Modify(int idc, CRect client, int x, int y)
{
	CWnd *pWin;
	pWin = GetDlgItem(idc);//获取控件句柄
	if (pWin)//判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建
	{
		CRect Editrect;//获取控件变化前大小
		pWin->GetWindowRect(&Editrect);
		ScreenToClient(&Editrect);//将控件大小转换为在对话框中的区域坐标
		//x/client.Width()为对话框在横向的变化比例

		Editrect.left = Editrect.left*x / client.Width();//调整控件大小
		Editrect.right = Editrect.right*x / client.Width();
		Editrect.top = Editrect.top*y / client.Height();
		Editrect.bottom = Editrect.bottom*y / client.Height() + 90;
		pWin->MoveWindow(Editrect);//调整控件大小

	}

}


//打开相机
void CMFCUIDlg::OnBnClickedButtonGrab()
{
		//获取相机参数
		/*HTuple  hv_Information, hv_ValueList, hv_i, hv_Index;
		HTuple  hv_Num;
		InfoFramegrabber("DirectShow", "device", &hv_Information, &hv_ValueList);*/
		//hv_i = hv_ValueList.TupleLength();
		//if (hv_i == 0)
		//{
		//	CNOCameraDlg dlg;
		//	dlg.DoModal();
		//}
		//{
		//	HTuple end_val3 = hv_i;
		//	HTuple step_val3 = 1;
		//	for (hv_Index = 0; hv_Index.Continue(end_val3, step_val3); hv_Index += step_val3)
		//	{
		//		if (0 != (hv_Index < hv_i))
		//		{
		//			TupleFind(hv_ValueList, ("[" + hv_Index) + "] Ecust", &hv_Num);
		//			if (0 != (hv_Num == -1))
		//			{
		//				hv_Num = hv_Num;
		//			}
		//			else
		//			{
		//				int index = hv_Num.I();
		//				CString Index;
		//				Index.Format("%d", index);
		//				CameraName = "[" + Index + "] Ecust";
		//				hv_Index = hv_i;

		//			}
		//		}
		//		else
		//		{
		//			CNOUniqueCDlg dlg;
		//			dlg.DoModal();
		//		}

		//	}
		//}
		//
		////打开相机
		//HTuple name = CameraName.GetBuffer();
		//HTuple pixel = CameraName.GetAt(1);
		//try
		//{
		//	OpenFramegrabber("DirectShow", 1, 1, 0, 0, 0, 0, "default", 8, "gray", -1, "false",
		//		"[" + pixel + "] yuv (3264x2448)", name, 0, -1, &hv_AcqHandle);
		//}
		//catch (const std::exception&)
		//{
		//	MessageBox(strMessageBox2);
		//}
		//调参数		
	//判断复选框内容

	//打开相机
	int indexD = m_Camera.GetCurSel();
	CString strDevice;
	m_Camera.GetLBText(indexD, strDevice);
	try
	{
		OpenFramegrabber("DirectShow", 1, 1, 0, 0, 0, 0, "default", 8, "gray", -1, "false",
			"[" + (HTuple)strDevice[1] + " yuv (3264x2448)", (HTuple)strDevice, 0, -1, &hv_AcqHandle);
		SetFramegrabberParam(hv_AcqHandle, "brightness", 20);
		SetFramegrabberParam(hv_AcqHandle, "gamma", 82);
		//SetFramegrabberParam(hv_AcqHandle, "white_balance", 5500);
		SetFramegrabberParam(hv_AcqHandle, "exposure", -1);
		GrabImageStart(hv_AcqHandle, -1);
		GrabImage(&ho_Image, hv_AcqHandle);
		GetImageSize(ho_Image, &height, &width);
		//SetWindowAttr("background_color", "black");
		SetPart(m_htWindow, 0, 0, width, height);
		if (HDevWindowStack::IsOpen())
			HalconCpp::CloseWindow(m_htWindow);
		DispObj(ho_Image, m_htWindow);
		SetTposition(m_htWindow, 12, 12);
		GetDlgItem(IDC_BUTTON_Grab)->SetWindowText(strButtonOpen);
		WriteString(m_htWindow, VarGrabWelcome.GetBuffer());
		Sleep(300);
	}
	catch (const std::exception&)
	{
		MessageBox("相机打开失败");
	}

	
	
	flag1 = true;
	B_Grab.EnableWindow(FALSE);
}

//抓图处理
void CMFCUIDlg::OnBnClickedButton2Deal()
{
	if (flag1 == true)
	{
		MessageBeep(MB_ICONHAND);
		m_ListCtrl.SetRedraw(FALSE);
		//判断复选框内容
		int nIndex = m_Version.GetCurSel();
		CString strCBText;
		m_Version.GetLBText(nIndex, strCBText);
		m_ListCtrl.DeleteAllItems();
		CString Esavetime = t1.Format("%Y-%m-%d %X");
		HObject  ho_Circle, ho_ImageScaled,ho_ImageReduced, ho_ImageReduced1;
		HObject  ho_SymbolXLDs1;
		HTuple  hv_CircleD, hv_Blank, hv_row, hv_column, hv_index, hv_DataCodeHandle;
		HTuple   hv_ResultHandles, hv_DecodedDataStrings1;
		HTuple hv_tag, hv_Length1, hv_Data;
		hv_index = HTuple();
		hv_tag = HTuple();
		//定位变量
		HObject  ho_GrayImage1, ho_ImageScaled1;
		HObject  ho_Rectangle1, ho_Regions, ho_ConnectedRegions1;
		HObject  ho_SelectedRegions, ho_RegionUnion1, ho_Rectangle, ho_Rectangle2;
		HObject  ho_Regions1, ho_Regions2, ho_SelectedRegions1;
		HTuple  hv_WindowHandle;
		HTuple  hv_IndexY, hv_IndexX, hv_Min, hv_Max, hv_Range, hv_Row11, hv_Column11;
		HTuple  hv_Row2, hv_Column2, hv_Row3, hv_Column3, hv_Row4, hv_Column4,hv_Radius2, hv_Radius3;
		HTuple  hv_Length, hv_rowper, hv_Columnper, hv_rowy, hv_columnx;
		GrabImage(&ho_ImageMirror, hv_AcqHandle);
		//ReadImage(&ho_ImageMirror, "E:/Images/100/1.jpg");
		//WriteImage(ho_Image, "jpg", 0, "E:/Images/100/1.1.jpg");
		MirrorImage(ho_ImageMirror, &ho_Image, "column");
		ScaleImage(ho_Image, &ho_ImageScaled, 1.8, 0);
		GetImageSize(ho_Image, &height, &width);
		//SetWindowAttr("background_color", "black");
		SetPart(m_htWindow, 0, 0, width, height);
		if (HDevWindowStack::IsOpen())
			HalconCpp::CloseWindow(m_htWindow);
		DispObj(ho_ImageScaled, m_htWindow);
		CreateDataCode2dModel("Data Matrix ECC 200", "default_parameters", "maximum_recognition",
			&hv_DataCodeHandle);

		if (strCBText == str1)
		{
			//8*12处理
			Rgb1ToGray(ho_Image, &ho_GrayImage1);
			ScaleImage(ho_GrayImage1, &ho_ImageScaled1, 3, 0);
			GenRectangle1(&ho_Rectangle1, 0, 0, height, width);
			MinMaxGray(ho_Rectangle1, ho_ImageScaled1, 0, &hv_Min, &hv_Max, &hv_Range);
			Threshold(ho_ImageScaled1, &ho_Regions, hv_Min + (0.7*hv_Range), hv_Max);
			Connection(ho_Regions, &ho_ConnectedRegions1);
			SelectShape(ho_ConnectedRegions1, &ho_SelectedRegions, "area", "and", 500, 500000);
			SelectShape(ho_SelectedRegions, &ho_SelectedRegions1, "circularity", "and", 0.06835,
				0.5);
			Union1(ho_SelectedRegions1, &ho_RegionUnion1);
			SmallestRectangle1(ho_RegionUnion1, &hv_Row11, &hv_Column11, &hv_Row2, &hv_Column2);
			hv_rowper = (hv_Row2 - hv_Row11) / 10.0;
			hv_Columnper = (hv_Column2 - hv_Column11) / 13.0;
			GenRectangle1(&ho_Rectangle, hv_Row11, hv_Column11, hv_Row11 + hv_rowper, hv_Column11 + hv_Columnper);
			GenRectangle1(&ho_Rectangle2, hv_Row2 - hv_rowper, hv_Column2 - hv_Columnper, hv_Row2,
				hv_Column2);
			ReduceDomain(ho_ImageScaled1, ho_Rectangle, &ho_ImageReduced);
			ReduceDomain(ho_ImageScaled1, ho_Rectangle2, &ho_ImageReduced1);
			Threshold(ho_ImageReduced, &ho_Regions1, hv_Min + (0.7*hv_Range), hv_Max);
			SmallestCircle(ho_Regions1, &hv_Row3, &hv_Column3, &hv_Radius2);
			Threshold(ho_ImageReduced1, &ho_Regions2, hv_Min + (0.7*hv_Range), hv_Max);
			SmallestCircle(ho_Regions2, &hv_Row4, &hv_Column4, &hv_Radius3);
			HTuple  hv_letter;
			TupleGenConst(96, "null", &hv_Data);
			hv_letter.Clear();
			hv_letter[0] = "A";
			hv_letter[1] = "B";
			hv_letter[2] = "C";
			hv_letter[3] = "D";
			hv_letter[4] = "E";
			hv_letter[5] = "F";
			hv_letter[6] = "G";
			hv_letter[7] = "H";
			hv_row = hv_Row3;
			hv_column = hv_Column3;
			hv_rowy = (hv_Column4 - hv_Column3) / 11;
			hv_columnx = (hv_Column4 - hv_Column3) / 11;
			for (hv_IndexY = 0; hv_IndexY <= 7; hv_IndexY += 1)
			{
				for (hv_IndexX = 0; hv_IndexX <= 11; hv_IndexX += 1)
				{
					GenCircle(&ho_Circle, hv_row + (hv_rowy * hv_IndexY), hv_column + (hv_columnx * hv_IndexX), 90);
					ReduceDomain(ho_ImageScaled, ho_Circle, &ho_ImageReduced);
					FindDataCode2d(ho_ImageReduced, &ho_SymbolXLDs1, hv_DataCodeHandle, HTuple(),
						HTuple(), &hv_ResultHandles, &hv_DecodedDataStrings1);
					DispObj(ho_SymbolXLDs1, m_htWindow);
					TupleLength(hv_DecodedDataStrings1, &hv_Length1);
					if (0 != (hv_Length1 == 1))
					{
						hv_Data[(12 * hv_IndexY) + hv_IndexX] = hv_DecodedDataStrings1;
					}
					TupleConcat(hv_index, hv_DecodedDataStrings1, &hv_index);
					TupleLength(hv_index, &hv_Length);
					SetTposition(m_htWindow, (hv_row - 100) + (hv_rowy * hv_IndexY), (hv_column + 7) + (hv_columnx * hv_IndexX));
					WriteString(m_htWindow, HTuple(hv_letter[hv_IndexY]) + (hv_IndexX + 1));
					TupleConcat(hv_tag, HTuple(hv_letter[hv_IndexY]) + (hv_IndexX + 1), &hv_tag);
				}
			}
			//给表添加数据
			for (int i = 1; i < 96 + 1; i++)
			{
				CString str;
				str.Format(_T("%d"), i);
				CString temp = (CString)hv_Data[i - 1].S();
				int nRow = m_ListCtrl.InsertItem(i, str);
				m_ListCtrl.SetItemText(nRow, 1, hv_tag[i - 1].S());
				m_ListCtrl.SetItemText(nRow, 2, temp);
				m_ListCtrl.SetItemText(nRow, 3, _T(""));
				UpdateData(true);
				m_ListCtrl.SetItemText(nRow, 4, BoxNumber);
				UpdateData(true);
				m_ListCtrl.SetItemText(nRow, 5, SampleType);
				UpdateData(true);
				m_ListCtrl.SetItemText(nRow, 6, BoxDescription);
				UpdateData(true);
				m_ListCtrl.SetItemText(nRow, 7, BoxLocation);
				m_ListCtrl.SetItemText(nRow, 8, Esavetime);
			}
		}
		else if (strCBText == str2)
		{
			Rgb1ToGray(ho_Image, &ho_GrayImage1);
			ScaleImage(ho_GrayImage1, &ho_ImageScaled1, 3, 0);
			GenRectangle1(&ho_Rectangle1, 0, 0, height, width);
			MinMaxGray(ho_Rectangle1, ho_ImageScaled1, 0, &hv_Min, &hv_Max, &hv_Range);
			Threshold(ho_ImageScaled1, &ho_Regions, hv_Min + (0.7*hv_Range), hv_Max);
			Connection(ho_Regions, &ho_ConnectedRegions1);
			SelectShape(ho_ConnectedRegions1, &ho_SelectedRegions, "area", "and", 500, 500000);
			SelectShape(ho_SelectedRegions, &ho_SelectedRegions1, "circularity", "and", 0.06835, 0.5);
			Union1(ho_SelectedRegions1, &ho_RegionUnion1);
			SmallestRectangle1(ho_RegionUnion1, &hv_Row11, &hv_Column11, &hv_Row2, &hv_Column2);
			hv_rowper = (hv_Row2 - hv_Row11) / 11.0;
			hv_Columnper = (hv_Row2 - hv_Row11) / 11.0;
			GenRectangle1(&ho_Rectangle, hv_Row11, hv_Column11, hv_Row11 + hv_rowper, hv_Column11 + hv_Columnper);
			GenRectangle1(&ho_Rectangle2, hv_Row11, hv_Column11 + (10 * hv_rowper), hv_Row11 + hv_rowper,
				hv_Column2);
			ReduceDomain(ho_ImageScaled1, ho_Rectangle, &ho_ImageReduced);
			ReduceDomain(ho_ImageScaled1, ho_Rectangle2, &ho_ImageReduced1);
			Threshold(ho_ImageReduced, &ho_Regions1, hv_Min + (0.7*hv_Range), hv_Max);
			SmallestCircle(ho_Regions1, &hv_Row3, &hv_Column3, &hv_Radius2);
			Threshold(ho_ImageReduced1, &ho_Regions2, hv_Min + (0.7*hv_Range), hv_Max);
			SmallestCircle(ho_Regions2, &hv_Row4, &hv_Column4, &hv_Radius3);
			TupleGenConst(100, "null", &hv_Data);
			hv_row = hv_Row3;
			hv_column = hv_Column3;
			hv_rowy = (hv_Column4 - hv_Column3) / 9;
			hv_columnx = (hv_Column4 - hv_Column3) / 9;
			for (hv_IndexY = 0; hv_IndexY <= 9; hv_IndexY += 1)
			{
				for (hv_IndexX = 0; hv_IndexX <= 9; hv_IndexX += 1)
				{
					GenCircle(&ho_Circle, hv_row + (hv_rowy * hv_IndexY), hv_column + (hv_columnx * hv_IndexX), 110);
					ReduceDomain(ho_ImageScaled, ho_Circle, &ho_ImageReduced);
					FindDataCode2d(ho_ImageReduced, &ho_SymbolXLDs1, hv_DataCodeHandle, HTuple(),
						HTuple(), &hv_ResultHandles, &hv_DecodedDataStrings1);
					DispObj(ho_SymbolXLDs1, m_htWindow);
					TupleLength(hv_DecodedDataStrings1, &hv_Length1);
					if (0 != (hv_Length1 == 1))
					{
						hv_Data[(10 * hv_IndexY) + hv_IndexX] = hv_DecodedDataStrings1;
					}
					TupleConcat(hv_index, hv_DecodedDataStrings1, &hv_index);
					TupleLength(hv_index, &hv_Length);
					SetTposition(m_htWindow, (hv_row - 100) + (hv_rowy * hv_IndexY), (hv_column + 10) + (hv_columnx * hv_IndexX));
					WriteString(m_htWindow, (hv_IndexX + (hv_IndexY * 10)) + 1);
				}
			}
			for (int i = 1; i < 100 + 1; i++)
			{
				CString str;
				str.Format(_T("%d"), i);
				CString temp = (CString)hv_Data[i - 1].S();
				int nRow = m_ListCtrl.InsertItem(i, str);
				m_ListCtrl.SetItemText(nRow, 1, str);
				m_ListCtrl.SetItemText(nRow, 2, temp);
				m_ListCtrl.SetItemText(nRow, 3, _T(""));
				UpdateData(true);
				m_ListCtrl.SetItemText(nRow, 4, BoxNumber);
				UpdateData(true);
				m_ListCtrl.SetItemText(nRow, 5, SampleType);
				UpdateData(true);
				m_ListCtrl.SetItemText(nRow, 6, BoxDescription);
				UpdateData(true);
				m_ListCtrl.SetItemText(nRow, 7, BoxLocation);

				m_ListCtrl.SetItemText(nRow, 8, Esavetime);
			}
		}
		m_ListCtrl.SetRedraw(true);
		//显示识别数目
		int t = hv_IndexY * hv_IndexX;
		int d = hv_Length;
		//CString s1;
		s1.Format("%d", t);
		//s1.Format("%d",100);
		Bar_Total = s1;
		UpdateData(false);
		//CString s2;
		s2.Format("%d", d);
		//s2.Format("%d", 100);
		Bar_Dealed = s2;
		UpdateData(false);
		int f = t - d;
		//CString s3;
		s3.Format("%d", f);
		SetDlgItemText(IDC_STATIC, strStaticFailed + s3 );
		if (f !=0)
		{
			CNGDlg dlg;
			dlg.DoModal();
		}
	}
	else
	{
	CNOOPENCDlg dlg;
	dlg.DoModal();
	//MessageBox("无效的操作，没有连接相机！","警告");
	return;
	}
}

//注册码
//void CMFCUIDlg::init_Register()
//{
//	unsigned long s1, s2;
//	CString sCpuID, CPUID1, CPUID2;
//	__asm {
//		mov eax, 01h
//		xor edx, edx
//		cpuid
//		mov s1, edx
//		mov s2, eax
//	}
//	CPUID1.Format("%08X%08X", s1, s2);
//	__asm {
//		mov eax, 03h
//		xor ecx, ecx
//		xor edx, edx
//		cpuid
//		mov s1, edx
//		mov s2, ecx
//	}
//	CPUID2.Format("%08X%08X", s1, s2);
//	sCpuID = CPUID1 + CPUID2;
//	SetDlgItemText(IDC_EDIT1, sCpuID);
//	DWORD ser;
//	char namebuf[128];
//	char filebuf[128];
//	::GetVolumeInformation("c:\\", namebuf, 128, &ser, 0, 0, filebuf, 128);
//	CString strdisk, strmachine;
//	strdisk.Format("%d", ser);
//	SetDlgItemText(IDC_EDIT2, strdisk);
//	strmachine = sCpuID.Mid(13, 5); 
//	strmachine += strdisk.Mid(3, 5);
//	MD5 md5;
//	md5.update(strmachine.GetBuffer());
//	regcode = md5.toString().c_str();
//	LONG lValue;
//	RegQueryValue(HKEY_CURRENT_USER, "Software\\AliiPay\\USER", NULL, &lValue);
//	char *pBuf = new char[lValue];
//	RegQueryValue(HKEY_CURRENT_USER, "Software\\AliiPay\\USER", pBuf, &lValue);
//	if (pBuf == regcode)
//	{
//		flag2 = true;
//	}
//	else
//	{
//		flag2 = false;
//		//MessageBox("weizhuce");
//	}
//}

//保存图像
void CMFCUIDlg::OnBnClickedButton3Image()
{
	/*HTuple hv_Rand;
	TupleRand(1, &hv_Rand);
	WriteImage(ho_Image, "jpg", 0, "C:\\Users\\Arnold\\Desktop\\ImageSave\\"+ hv_Rand +".jpg");*/
	try
	{
		/*CWnd* bmpShow = GetDlgItem(IDC_STATIC_Image);
		CDC *pdc = bmpShow->GetDC();
		CImage  imag;
		CRect rect;

		GetClientRect(&rect);
		bmpShow->GetWindowRect(&rect);
		imag.Create(rect.Width(), rect.Height(), 32);
		::BitBlt(imag.GetDC(), 0, 0, rect.Width(), rect.Height(), pdc->m_hDC, 0, 0, SRCCOPY);*/

		TCHAR szFilter[] = _T("jpg file(.jpg)|.jpg|bmp file(.bmp)|.bmp|所有文件(*.*)|*.*||");
		CFileDialog fileDlg(FALSE, _T("jpg"), _T(".jpg"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
		fileDlg.m_ofn.lpstrTitle = _T("JPG");
		CString picturePath;
		if (IDOK == fileDlg.DoModal())
		{
			picturePath = fileDlg.GetPathName();
		}
		const char* fpath = CStringA(picturePath);
		WriteImage(ho_Image, "jpg", 0, fpath);
		if (FAILED(fpath))
		{
			MessageBox(strMessageBox3);
		}
	}
	catch (const std::exception&)
	{
		MessageBox(strMessageBox3);
	}
	
}

//保存为Txt
void CMFCUIDlg::OnBnClickedButton5Txt()
{
	txtBoxInfo.ReleaseBuffer();
	strSaveTime.ReleaseBuffer();
	strStaticBoxNumber.ReleaseBuffer();
	strStaticSampleType.ReleaseBuffer();
	strStaticBoxDesc.ReleaseBuffer();
	strStaticBoxLocation.ReleaseBuffer();
	txtCryotubeInfo.ReleaseBuffer();
	if (m_ListCtrl.GetItemCount() == 0)
	{
		MessageBox(_T(strMessageBox4,"Warning"));
		return;
	}
	int nRow = m_ListCtrl.GetItemCount();
	itemCount = nRow;
	try
	{
		CString strFilePath;
		CString strFilter = _T("txt文件(*.txt)|*.txt");
		CFileDialog dlg(FALSE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter, this);
		dlg.m_ofn.lpstrTitle = _T("TXT");
		if (dlg.DoModal() != IDC_BUTTON5_Txt)
		{
			strFilePath = dlg.GetPathName();
			FILE *fp;
			const char* fpath = CStringA(strFilePath);
			fopen_s(&fp, fpath, "w");
			char str[2048];
			if (fp == NULL)
			{
				printf("save error\n");
				return;
			}
			int nHeadNum = m_ListCtrl.GetHeaderCtrl()->GetItemCount();
			LVCOLUMN lvcol;
			char str_out[1024];
			int nColNUm;
			nColNUm = 0;
			lvcol.mask = LVCF_TEXT;
			lvcol.pszText = str_out;
			lvcol.cchTextMax = 1024;
			fwrite("["+txtBoxInfo+"]", 1, strlen("[" + txtBoxInfo + "]"), fp);
			fprintf_s(fp, "\n");
			CString savetime = t1.Format("%Y-%m-%d %X");
		
			fwrite(strSaveTime + "=" +  savetime, 1, strlen(strSaveTime + s1 + savetime), fp);
			//fprintf_s(fp,  strSaveTime+"=" + savetime);
			fprintf_s(fp, "\n");
			UpdateData(true);
			fprintf_s(fp, "%s\t", strStaticBoxNumber +"=" + BoxNumber);
			fprintf_s(fp, "\n");
			UpdateData(true);
			fprintf_s(fp, "%s\t", strStaticSampleType +"=" + SampleType);
			fprintf_s(fp, "\n");
			UpdateData(true);
			fprintf_s(fp, "%s\t", strStaticBoxDesc +"=" + BoxDescription);
			fprintf_s(fp, "\n");
			UpdateData(true);
			fprintf_s(fp, "%s\t", strStaticBoxLocation +"=" + BoxLocation);
			fprintf_s(fp, "\n");
			fprintf_s(fp, "%s\t", "[" + txtCryotubeInfo + "]");
		//	fwrite("["+ txtCryotubeInfo+"]", 1, strlen("[" + txtCryotubeInfo + "]"), fp);
			fprintf_s(fp, "\n");
			while (m_ListCtrl.GetColumn(nColNUm, &lvcol))
			{

				nColNUm++;
				//fprintf_s(fp, "%s\t", lvcol.pszText);

			}
			for (nColNUm = 0; nColNUm < 4; nColNUm++)
			{
				m_ListCtrl.GetColumn(nColNUm, &lvcol);
				fprintf_s(fp, "%s\t", lvcol.pszText);
			}
			fprintf_s(fp, "\n", lvcol.pszText);
			/*CString sa;
			sa.Format("%d", itemCount);
			MessageBox(sa);*/
			for (int i = 0; i < 50; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					CString str_data = m_ListCtrl.GetItemText(i, j);
					fprintf_s(fp, "%s\t", str_data);
				}
				fprintf_s(fp, "\n");
			}
			fclose(fp);
		}
		
	}
	catch (const std::exception&)
	{
		MessageBox(strMessageBox3);;
	}
	
}

//保存为Excel
void CMFCUIDlg::OnBnClickedButton5Excel()
{
	if (m_ListCtrl.GetItemCount() == 0)
	{
		MessageBox(_T(strMessageBox4, "Warning"));
		return;
	}
	int nRow = m_ListCtrl.GetItemCount();
	int num;
	//if (flag2 == true)
	//{
	//	itemCount = nRow;
	//	/*CString Esavetime = t1.Format("%Y-%m-%d %X");
	//	for (int i = 1; i < hv_Length + 1; i++)
	//	{
	//		UpdateData(true);
	//		m_ListCtrl.SetItemText(i - 1, 4, BoxNumber);
	//		UpdateData(true);
	//		m_ListCtrl.SetItemText(i - 1, 5, SampleType);
	//		UpdateData(true);
	//		m_ListCtrl.SetItemText(i - 1, 6, BoxDescription);
	//		UpdateData(true);
	//		m_ListCtrl.SetItemText(i - 1, 7, BoxLocation);
	//		m_ListCtrl.SetItemText(i - 1, 8, Esavetime);
	//	}*/
	//}
	//else
	//{
	//	itemCount = 20;
	//}
	//判断复选框内容
	int nIndex = m_Version.GetCurSel();
	CString strCBText;
	m_Version.GetLBText(nIndex, strCBText);
	if (strCBText == str1) 
	{
		num = 96;
	}
	else
	{
		num = 100;
	}
	//更新list control
	for (int i = 1; i < num + 1; i++)
			{
				UpdateData(true);
				m_ListCtrl.SetItemText(i - 1, 4, BoxNumber);
				UpdateData(true);
				m_ListCtrl.SetItemText(i - 1, 5, SampleType);
				UpdateData(true);
				m_ListCtrl.SetItemText(i - 1, 6, BoxDescription);
				UpdateData(true);
				m_ListCtrl.SetItemText(i - 1, 7, BoxLocation);
			}
	itemCount = nRow;
	try
	{
		
		CString strFilePath;
		CString strFilter = _T("xls文件(*.xls)|*.xls");
		CFileDialog dlg(FALSE, _T(".xls"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter, this);
		dlg.m_ofn.lpstrTitle = _T("Excel");
		if (dlg.DoModal() != IDC_BUTTON5_Txt)
		{
			strFilePath = dlg.GetPathName();
			FILE *fp;
			const char* fpath = CStringA(strFilePath);
			fopen_s(&fp, fpath, "w");
			char str[1024];
			if (fp == NULL)
			{
				printf("save error\n");
				return;
			}
			int nHeadNum = m_ListCtrl.GetHeaderCtrl()->GetItemCount();
			LVCOLUMN lvcol;
			char str_out[256];
			int nColNUm;
			nColNUm = 0;
			lvcol.mask = LVCF_TEXT;
			lvcol.pszText = str_out;
			lvcol.cchTextMax = 256;
			while (m_ListCtrl.GetColumn(nColNUm, &lvcol))
			{
				nColNUm++;
				fprintf_s(fp, "%s\t", lvcol.pszText);
			}
			fprintf_s(fp, "\n", lvcol.pszText);
			
			for (int i = 0; i < 50; i++)
			{
				for (int j = 0; j < nColNUm; j++)
				{
					CString str_data = m_ListCtrl.GetItemText(i, j);
					fprintf_s(fp, "%s\t", str_data);
				}
				fprintf_s(fp, "\n");
			}

			fclose(fp);
		}
	}
	catch (const std::exception&)
	{
		MessageBox("strMessageBox3");
	}
}

//保存到数据库
void CMFCUIDlg::OnBnClickedButton4Sql()
{
	//判断复选框内容
	int num = 0;
	int nIndex = m_Version.GetCurSel();
	CString strCBText;
	m_Version.GetLBText(nIndex, strCBText);
	if (strCBText == str2)
	{
		num = 100;
	}
	if (strCBText == str1)
	{
		num = 96;
	}
	//更新list control
	for (int i = 1; i < num + 1; i++)
	{
		UpdateData(true);
		m_ListCtrl.SetItemText(i - 1, 4, BoxNumber);
		UpdateData(true);
		m_ListCtrl.SetItemText(i - 1, 5, SampleType);
		UpdateData(true);
		m_ListCtrl.SetItemText(i - 1, 6, BoxDescription);
		UpdateData(true);
		m_ListCtrl.SetItemText(i - 1, 7, BoxLocation);
	}
	CString Ssavetime = t1.Format("%Y-%m-%d %X");
	if (m_ListCtrl.GetItemCount() == 0)
	{
		MessageBox(_T(strMessageBox4));
		return;
	}
	const char user[] = "root";
	const char pswd[] = "123456";
	const char host[] = "localhost";
	const char db[] = "product_data";
	unsigned int port = 3306;
	MYSQL mycont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	//int res;
	char select_user[1024];
	CString sqls;
	mysql_init(&mycont);
	if (!mysql_real_connect(&mycont, host, user, pswd, db, port, NULL, 0))
	{
		MessageBox(_T(strMessageBox7));
	}
	else
	{
		//MessageBox(_T("数据库连接chengg!"));
		mysql_query(&mycont, "SET NAMES GBK");
		//mysql_real_query(&mycont, create, strlen(create));
		for (int i = 0; i < num; i++)
		{
			//char*   (LPTSTR)(LPCTSTR)

			CString ID = m_ListCtrl.GetItemText(i, 0);
			CString location = m_ListCtrl.GetItemText(i, 1);
			CString BarCont = m_ListCtrl.GetItemText(i, 2);
			CString SampleCont = m_ListCtrl.GetItemText(i, 3);
			CString str1 = m_ListCtrl.GetItemText(i, 4);
			CString str2 = m_ListCtrl.GetItemText(i, 5);
			CString str3 = m_ListCtrl.GetItemText(i, 6);
			CString str4 = m_ListCtrl.GetItemText(i, 7);
			CString str5 = m_ListCtrl.GetItemText(i, 8);
			sprintf_s(select_user, "INSERT INTO tb_data(order,index,content_of_barcode,conent_of_sample,tube_box_code,sample_type,desc_of_tube_box,location_of_tube_box,save_time) VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s')",
				ID, location, BarCont, SampleCont, str1, str2, str3, str4, str5);
			//MessageBox(select_user);
			if (mysql_real_query(&mycont, select_user, strlen(select_user)))
			{
				MessageBox(strMessageBox3);
			}
		
			UpdateData(false);
		}
		mysql_close(&mycont);
	}
}

//初始化list control
void CMFCUIDlg::init_list_control()
{
	
	//表头
	m_ListCtrl.SetItemState(30, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrl.InsertColumn(0, _T("序号"));
	m_ListCtrl.InsertColumn(1, _T("位置"));
	m_ListCtrl.InsertColumn(2, _T("条码内容"));
	m_ListCtrl.InsertColumn(3, _T("标本内容"));
	m_ListCtrl.InsertColumn(4, _T("盒子序号"));
	m_ListCtrl.InsertColumn(5, _T("标本类型"));
	m_ListCtrl.InsertColumn(6, _T("盒子描述"));
	m_ListCtrl.InsertColumn(7, _T("盒子位置"));
	m_ListCtrl.InsertColumn(8, _T("入库时间"));
	CRect rect;
	m_ListCtrl.GetClientRect(rect);
	m_ListCtrl.SetColumnWidth(0, 0.2*rect.Width());
	m_ListCtrl.SetColumnWidth(1, 0.2*rect.Width());
	m_ListCtrl.SetColumnWidth(2, 0.3*rect.Width());
	m_ListCtrl.SetColumnWidth(3, 0.3*rect.Width());
}

//初始化状态栏
//void CMFCUIDlg::init_StatusBarr()
//{
//	m_bar.Create(this);
//	m_bar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
//	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
//	m_bar.SetFont(&m_font);
//	CRect rect;
//	m_bar.GetClientRect(rect);
//	m_bar.SetPaneInfo(0, IDS_T1, SBPS_STRETCH, 0.2*rect.Width());
//	m_bar.SetPaneInfo(1, IDS_T1, SBPS_STRETCH, 0.59*rect.Width());
//	m_bar.SetPaneInfo(2, IDS_T1, SBPS_STRETCH, 0.21*rect.Width());
//	CString date = t1.Format("%Y-%m-%d ");
//	m_bar.SetPaneText(0, date+ _T(""));
//	m_bar.SetPaneText(1, "");
//	m_bar.SetPaneText(2, " ");
//}

//快捷键虚函数重载
BOOL CMFCUIDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
	{
	case 113: {OnBnClickedButtonGrab(); break; }
	case 114: {OnBnClickedButton2Deal(); break; }
	case 115: {OnBnClickedButton3Image(); break; }
	case 116: {OnBnClickedButton4Sql(); break; }
	case 117: {OnBnClickedButton5Txt(); break; }
	case 118: {OnBnClickedButton5Excel(); break; }
	case 119: {OnBnClickedButtonExit(); break; }
	}
	}
	return CDialog::PreTranslateMessage(pMsg);
	/*int iResult;
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		//翻译加速键表。该函数处理菜单命令中的加速键。
		iResult = TranslateAccelerator(m_hWnd, m_hAccel, pMsg);
		if (iResult == IDC_BUTTON_Grab)
		{
			OnBnClickedButtonGrab();
			return true;
		}
		break;
	}
	return CDialogEx::PreTranslateMessage(pMsg);*/
}

//添加listctrl控件的NM_CLICK消息相应函数,得到单击的CListCtrl的行列号
void CMFCUIDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1)
	{


		MoRow = pNMListView->iItem;
		MoCol = pNMListView->iSubItem;

	}

	*pResult = 0;
}

//修改条码内容
void CMFCUIDlg::OnBnClickedButtonChangecontext()
{
	UpdateData();
	CString Mostr = m_ChangeContext;
	UpdateData(TRUE);
	m_ListCtrl.SetItemText(MoRow, MoCol + 1, _T(Mostr));
}

//item选中高亮
void CMFCUIDlg::OnCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

	*pResult = CDRF_DODEFAULT;
	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ((CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage)
	{

		COLORREF clrNewTextColor, clrNewBkColor;

		int nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec);

		POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
		int index = m_ListCtrl.GetNextSelectedItem(pos);

		if (index == nItem)//如果要刷新的项为当前选择的项，则将文字设为白色，背景色设为蓝色
		{
			clrNewTextColor = RGB(255, 255, 255);        //Set the text to white
			clrNewBkColor = RGB(49, 106, 197);        //Set the background color to blue
		}
		else
		{
			clrNewTextColor = RGB(0, 0, 0);        //set the text black
			clrNewBkColor = RGB(255, 255, 255);    //leave the background color white
		}

		pLVCD->clrText = clrNewTextColor;
		pLVCD->clrTextBk = clrNewBkColor;

		*pResult = CDRF_DODEFAULT;
	}

}

//关闭相机
void CMFCUIDlg::OnBnClickedButtonExit()
{
	if (flag1==true)
	{
		CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC_Image);
		pStatic->GetClientRect(&rtWindow);
		pStatic->GetDC()->FillSolidRect(rtWindow.left, rtWindow.top, rtWindow.Width(), rtWindow.Height(), RGB(236, 233, 216));
		pStatic->GetClientRect(&rtWindow); pStatic->GetDC()->FillSolidRect(rtWindow.left, rtWindow.top, rtWindow.Width(), rtWindow.Height(), RGB(0, 0, 0));
		m_ListCtrl.DeleteAllItems();
		CloseFramegrabber(hv_AcqHandle);
		B_Grab.EnableWindow(TRUE);
	}
	else
	{
		CNOOPENCDlg dlg;
		dlg.DoModal();;
		return;
	}

}

//改变字体颜色，背景
HBRUSH CMFCUIDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	switch (pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC2:
		{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
		case IDC_STATIC3:
		{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
		case IDC_STATIC4:
		{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
		case IDC_STATIC5:
		{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
		case IDC_STATIC7:
		{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
		case IDC_STATIC8:
		{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
		case IDC_STATIC9:
		{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
		case IDC_STATIC10:
		{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
		case IDC_STATIC11:
		{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
		case IDC_STATIC14:
		{pDC->SetTextColor(RGB(243, 58, 21)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
		case IDC_STATIC18:
		{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
		case IDC_STATICOutsql:
		{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
		case IDC_STATIC0:
		{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
		case IDC_STATIC:
		{pDC->SetTextColor(RGB(243, 58, 21)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
		case IDC_STATIC_Total:
		{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
		case IDC_STATIC_Dealed:
		{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
		case IDC_STATIC_Language:
		{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
		case IDC_STATIC_Camera:
		{pDC->SetTextColor(RGB(0, 51, 51)); pDC->SetBkColor(RGB(236, 233, 216)); pDC->SetBkMode(OPAQUE); hbr = CreateSolidBrush(RGB(236, 233, 216)); pDC->SelectObject(&m_font);
		break; }
	}
	//return m_brush;
	return hbr;
}

//出库
void CMFCUIDlg::OnBnClickedButtonOutsql()
{
	CString Outime = t1.Format("%Y-%m-%d %X");
	const char user[] = "root";
	const char pswd[] = "123456";
	const char host[] = "localhost";
	const char db[] = "product_data";
	unsigned int port = 3306;
	MYSQL mycont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	char select_user[1024];
	CString sqls;
	mysql_init(&mycont);
	if (!mysql_real_connect(&mycont, host, user, pswd, db, port, NULL, 0))
	{
		MessageBox(_T(strMessageBox7));
	}
	else
	{
		mysql_query(&mycont, "SET NAMES GBK");
		UpdateData(true);
		sprintf(select_user, "INSERT INTO out_data (order,index,content_of_barcode,conent_of_sample,tube_box_code,sample_type,desc_of_tube_box,location_of_tube_box,save_time) SELECT order,index,content_of_barcode,conent_of_sample,tube_box_code,sample_type,desc_of_tube_box,location_of_tube_box,save_time FROM tb_data WHERE content_of_barcode=('%s')", Outsql);
		if (mysql_real_query(&mycont, select_user, strlen(select_user)))
		{
			MessageBox(strMessageBox3);
		}
		UpdateData(true);
		CString buf;
		buf.Format("update out_data set save_time= '"+Outime+"'  WHERE content_of_barcode =  '" + Outsql + "'");
		/*sprintf(select_user, "update out_data set 出库时间="+ "WHERE 条码内容 = ('%s')", BoxNumber);*/
		//MessageBox(buf);
		if (mysql_real_query(&mycont, buf, strlen(buf)))
		{
			MessageBox(strMessageBox3);
		}
		sprintf(select_user, "DELETE FROM tb_data WHERE content_of_barcode = ('%s')", Outsql);
		if (mysql_real_query(&mycont, select_user, strlen(select_user)))
		{
			MessageBox("strMessageBox3");
		}
	}
}

void CMFCUIDlg::OnBnClickedButtonEnglish()
{
	//判断复选框内容
	//int nIndex = m_Language.GetCurSel();
	//CString strCBText;
	//m_Language.GetLBText(nIndex, strCBText);
	const char* HeadEnglish[] = { "Order" ,"Index","BarcodeContent","SampleContent","BoxNumber","SampleType","BoxDesc","BoxLocation","SaveTime" };
		GetPrivateProfileString("Language Info", "ButtonOpen", "Connect Camera(F2)", strButtonOpen.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON_Grab)->SetWindowText(strButtonOpen);
		GetPrivateProfileString("Language Info", "ButtonClose", "Close Camera(F3)", strButtonClose.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON_Exit)->SetWindowText(strButtonClose);
		GetPrivateProfileString("Language Info", "ButtonDeal", "Deal(F3)", strButtonDeal.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON2_Deal)->SetWindowText(strButtonDeal);
		GetPrivateProfileString("Language Info", "ButtonImage", "Save as Photo(F4)", strButtonImage.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON3_Image)->SetWindowText(strButtonImage);
		GetPrivateProfileString("Language Info", "ButtonSql", "Save to DataBase(F5)", strButtonSql.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON4_Sql)->SetWindowText(strButtonSql);
		GetPrivateProfileString("Language Info", "ButtonTxt", "Save as TXT(F6)", strButtonTxt.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON5_Txt)->SetWindowText(strButtonTxt);
		GetPrivateProfileString("Language Info", "ButtonExcel", "Save as Excel(F7)", strButtonExcel.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON5_Excel)->SetWindowText(strButtonExcel);
		GetPrivateProfileString("Language Info", "ButtonOut", "Outbound", strButtonOut.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON_OutSql)->SetWindowText(strButtonOut);
		GetPrivateProfileString("Language Info", "ButtonChange", "modification content  ", strButtonChange.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON_ChangeContext)->SetWindowText(strButtonChange);
		GetPrivateProfileString("Language Info", "StaticTotal", "Total", strStaticTotal.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC_Total)->SetWindowText(strStaticTotal);
		GetPrivateProfileString("Language Info", "StaticDeal", "Dealed", strStaticDeal.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC_Dealed)->SetWindowText(strStaticDeal);
		GetPrivateProfileString("Language Info", "StaticFailed", "Failed", strStaticFailed.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC)->SetWindowText(strStaticFailed);
		GetPrivateProfileString("Language Info", "StaticSize", "Size Choose", strStaticSize.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC0)->SetWindowText(strStaticSize);
		GetPrivateProfileString("Language Info", "StaticOutZone", "Outbound operation", strStaticOutZone.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC14)->SetWindowText(strStaticOutZone);
		GetPrivateProfileString("Language Info", "StaticOutContent", "Info of  barcode ", strStaticOutContent.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_STATICOutsql)->SetWindowText(strStaticOutContent);
		GetPrivateProfileString("Language Info", "StaticBoxInfoZone", "Info of tube box", strStaticBoxInfoZone.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC18)->SetWindowText(strStaticBoxInfoZone);
		GetPrivateProfileString("Language Info", "StaticBoxNumber", "tube box code", strStaticBoxNumber.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC8)->SetWindowText(strStaticBoxNumber);
		GetPrivateProfileString("Language Info", "StaticSampleType", "Sample Type", strStaticSampleType.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC9)->SetWindowText(strStaticSampleType);
		GetPrivateProfileString("Language Info", "StaticBoxDesc", "description of tube box", strStaticBoxDesc.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC10)->SetWindowText(strStaticBoxDesc);
		GetPrivateProfileString("Language Info", "StaticBoxLocation", "Location of tube box", strStaticBoxLocation.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC11)->SetWindowText(strStaticBoxLocation);
		GetPrivateProfileString("Language Info", "StaticModifyZone", "modification of sample type ", strStaticModifyZone.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC7)->SetWindowText(strStaticModifyZone);
		GetPrivateProfileString("Language Info", "GrabWelcome", "welcome to use， choose barcode specifications，then start recognition", VarGrabWelcome.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetPrivateProfileString("Language Info", "MessageBox2 ", "failed to open camera，please try again", strMessageBox2.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
		GetPrivateProfileString("Language Info", "MessageBox1 ", "no camera found，please check the camera", strMessageBox1.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetPrivateProfileString("Language Info", "MessageBox3 ", "failed ，please try again", strMessageBox3.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetPrivateProfileString("Language Info", "MessageBox4 ", "There have no data to save", strMessageBox4.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetPrivateProfileString("Language Info", "MessageBox5 ", "Invalid operation, please click the button to connect camera first", strMessageBox5.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetPrivateProfileString("Language Info", "MessageBox6 ", "can not open the camera，please check the camera type", strMessageBox6.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetPrivateProfileString("Language Info", "MessageBox7 ", "unable to connect to database!!", strMessageBox7.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
		GetPrivateProfileString("Language Info", "BoxInfo ", "Tube Box Information", txtBoxInfo.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetPrivateProfileString("Language Info", "SaveTime ", "Save Time", strSaveTime.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		GetPrivateProfileString("Language Info", "CryotubeInfo ", "Cryogenic Vial Information", txtCryotubeInfo.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\EnglishConfig.ini");
		for (int i = 0; i < 9; i++)
		{
			CHeaderCtrl* pListHeader = m_ListCtrl.GetHeaderCtrl();
			HDITEM hditem;
			//enum { sizeOfBuffer = 256 };
			TCHAR  lpBuffer[256];
			hditem.mask = HDI_TEXT;//取字符掩码  
			hditem.pszText = lpBuffer;//字符缓冲区 
			hditem.cchTextMax = 256;//缓冲区大小 
			pListHeader->GetItem(i, &hditem);
			CString s = HeadEnglish[i];
			hditem.pszText = (LPSTR)(LPCSTR)s;
			pListHeader->SetItem(i, &hditem);
		}
}

void CMFCUIDlg::OnBnClickedButtonChinese()
{
	const char* HeadChinese[] = { "序号" ,"位置","条码内容","标本内容","盒子序号","标本类型","盒子描述","盒子位置","入库时间" };
	GetPrivateProfileString("Language Info", "ButtonOpen", "连接相机(F2)", strButtonOpen.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON_Grab)->SetWindowText(strButtonOpen);
	GetPrivateProfileString("Language Info", "ButtonClose", "关闭相机(F3)", strButtonClose.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON_Exit)->SetWindowText(strButtonClose);
	GetPrivateProfileString("Language Info", "ButtonDeal", "点我识别(F3)", strButtonDeal.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON2_Deal)->SetWindowText(strButtonDeal);
	GetPrivateProfileString("Language Info", "ButtonImage", "保存为图片(F4)", strButtonImage.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON3_Image)->SetWindowText(strButtonImage);
	GetPrivateProfileString("Language Info", "ButtonSql", "保存到数据库(F5)", strButtonSql.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON4_Sql)->SetWindowText(strButtonSql);
	GetPrivateProfileString("Language Info", "ButtonTxt", "保存为TXT(F6)", strButtonTxt.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON5_Txt)->SetWindowText(strButtonTxt);
	GetPrivateProfileString("Language Info", "ButtonExcel", "保存为Excel(F7)", strButtonExcel.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON5_Excel)->SetWindowText(strButtonExcel);
	GetPrivateProfileString("Language Info", "ButtonOut", "出库", strButtonOut.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON_OutSql)->SetWindowText(strButtonOut);
	GetPrivateProfileString("Language Info", "ButtonChange", "修改内容", strButtonChange.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON_ChangeContext)->SetWindowText(strButtonChange);
	GetPrivateProfileString("Language Info", "StaticTotal", "总数", strStaticTotal.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC_Total)->SetWindowText(strStaticTotal);
	GetPrivateProfileString("Language Info", "StaticDeal", "识别", strStaticDeal.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC_Dealed)->SetWindowText(strStaticDeal);
	GetPrivateProfileString("Language Info", "StaticFailed", "未识别", strStaticFailed.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC)->SetWindowText(strStaticFailed);
	GetPrivateProfileString("Language Info", "StaticSize", "条码规格选择", strStaticSize.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC0)->SetWindowText(strStaticSize);
	GetPrivateProfileString("Language Info", "StaticOutZone", "出库操作区", strStaticOutZone.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC14)->SetWindowText(strStaticOutZone);
	GetPrivateProfileString("Language Info", "StaticOutContent", "出库条码内容", strStaticOutContent.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_STATICOutsql)->SetWindowText(strStaticOutContent);
	GetPrivateProfileString("Language Info", "StaticBoxInfoZone", "盒子信息填写区", strStaticBoxInfoZone.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC18)->SetWindowText(strStaticBoxInfoZone);
	GetPrivateProfileString("Language Info", "StaticBoxNumber", "盒子编号", strStaticBoxNumber.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC8)->SetWindowText(strStaticBoxNumber);
	GetPrivateProfileString("Language Info", "StaticSampleType", "标本类型", strStaticSampleType.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC9)->SetWindowText(strStaticSampleType);
	GetPrivateProfileString("Language Info", "StaticBoxDesc", "盒子描述", strStaticBoxDesc.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC10)->SetWindowText(strStaticBoxDesc);
	GetPrivateProfileString("Language Info", "StaticBoxLocation", "盒子位置", strStaticBoxLocation.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC11)->SetWindowText(strStaticBoxLocation);
	GetPrivateProfileString("Language Info", "StaticModifyZone", "标本内容修改区", strStaticModifyZone.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC7)->SetWindowText(strStaticModifyZone);
	GetPrivateProfileString("Language Info", "GrabWelcome", "欢迎使用,请先选择条码规格,然后开始识别", VarGrabWelcome.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "MessageBox2 ", "打开相机失败,请重试", strMessageBox2.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "MessageBox1 ", "没有在此设备上检测到任何可用的相机\n请确认是否已经连接相机", strMessageBox1.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "MessageBox3 ", "保存失败,请重试", strMessageBox3.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "MessageBox4 ", "没有数据要储存", strMessageBox4.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "MessageBox5 ", "没有连接相机,无效的操作", strMessageBox5.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "MessageBox6 ", "无法打开指定的相机\n请确认相机的型号", strMessageBox6.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "MessageBox7 ", "数据库连接失败!", strMessageBox7.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "BoxInfo ", "盒子信息", txtBoxInfo.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "SaveTime ", "导出时间", strSaveTime.GetBuffer(MAX_PATH), MAX_PATH, "D:\\系统文件\\ChineseConfig.ini");
	for (int i = 0; i < 9; i++)
	{
		CHeaderCtrl* pListHeaderr = m_ListCtrl.GetHeaderCtrl();
		HDITEM hditemm;
		//enum { sizeOfBuffer = 256 };
		TCHAR  lpBuffer[256];
		hditemm.mask = HDI_TEXT;//取字符掩码  
		hditemm.pszText = lpBuffer;//字符缓冲区 
		hditemm.cchTextMax = 256;//缓冲区大小 
		pListHeaderr->GetItem(i, &hditemm);
		CString ss = HeadChinese[i];
		hditemm.pszText = (LPSTR)(LPCSTR)ss;
		pListHeaderr->SetItem(i, &hditemm);
	}
}

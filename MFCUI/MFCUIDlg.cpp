
// MFCUIDlg.cpp : ʵ���ļ�
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

//ȫ�ֱ���
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
//���Ź��ܱ���
float m_nDlgWidth;
float m_nDlgHeight;
float m_nWidth;
float m_nHeight;
float m_Multiple_width;
float m_Mutiple_heigth;
bool change_flag;
//�ؼ���������
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

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCUIDlg �Ի���




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


// CMFCUIDlg ��Ϣ�������

BOOL CMFCUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	
	GetClientRect(&m_rect);
	//��������
	//mySplash wndSplash;                 //���������������ʵ��
	//wndSplash.Create(IDB_Logo);     //BMPͼƬ��ID
	//wndSplash.CenterWindow();
	//wndSplash.UpdateWindow();          //send WM_PAINT
	//Sleep(3000);
	//wndSplash.DestroyWindow();//���ٳ�ʼ���洰��


	//����
	//if (-1 != GetFileAttributes("D:\\ϵͳ�ļ�\\Title.txt"))
	//{
	//	char *Buf;
	//	CFile myFile("D:\\ϵͳ�ļ�\\Title.txt", CFile::typeText | CFile::modeRead);
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
	//	SetWindowText("����ܶ�ά���Զ��ɼ�ʶ��ϵͳ");
	//}
	GetPrivateProfileString("Text Info", "Title", "����ܶ�ά���Զ��ɼ�ʶ��ϵͳ", strTitle.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\IniConfig.ini");
	SetWindowText(strTitle);
	
	//����ɫ
	m_brush.CreateSolidBrush(RGB(226,234,226));

	m_Menu.LoadMenu(IDR_MENU1);
	this->SetMenu(&m_Menu);
	
	//ȡ��ĳЩ�ؼ�Ƥ��
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
	//�ػ水ť
	//B_Excel.SubclassDlgItem(IDC_BUTTON5_Excel, this);
	B_Excel.SetIcon(IDI_Excel);
	B_Excel.SetAlign(CButtonST::ST_ALIGN_VERT);
	B_Excel.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(236,233,216));//��ͨ״̬�±���ɫ
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
	//��ȡ��ǰʱ��
	t1 = CTime::GetCurrentTime();
	
	//��������ʼֵ
	VarGrabWelcome = "��ӭʹ��, ����ѡ��������, Ȼ��ʼʶ��";
	txtBoxInfo = "������Ϣ";
	strSaveTime = "����ʱ��";
	txtCryotubeInfo = "�������Ϣ";
	strMessageBox1 = "û���ڴ��豸�ϼ�⵽�κο��õ����\n��ȷ���Ƿ��Ѿ��������";
	strMessageBox2 = "�����ʧ��,������";
	strMessageBox3 = "����ʧ��,������";
	strMessageBox4 = "û������Ҫ�洢!";
	strMessageBox5 = "��Ч�Ĳ���\n���ȵ���������";
	strMessageBox6 = "�޷���ָ�������\n��ȷ��������ͺ�";
	strMessageBox7 = "���ݿ�����ʧ��!";
	strStaticTotal = "����";
	strStaticDeal = "ʶ��";
	strStaticFailed = "δʶ��";
	strStaticBoxNumber = "���ӱ��";
	strStaticSampleType = "�걾����";
	strStaticBoxDesc = "��������";
	strStaticBoxLocation = "����λ��";



	m_Version.AddString(str1);
	m_Version.AddString(str2);
	//m_Language.AddString(str3);
	//m_Language.AddString(str4);
	//m_Language.AddString(str5);
	//m_Language.AddString(str6);

	//��������
	m_font.CreatePointFont(100,_T("΢���ź�"));
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
	
	//���ؿ�ݼ�
//	HACCEL m_hAccel = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR2));

	//��ʼ��
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

	//��ȡ�������
//��ȡ�������
	HTuple hv_Information, hv_ValueList, hv_Length1;
	InfoFramegrabber("DirectShow", "device", &hv_Information, &hv_ValueList);
	TupleLength(hv_ValueList, &hv_Length1);
	if (0 == hv_Length1)
	{
		MessageBox("�޷���ȡ�������");
	}
	else
	{
		for (int i = 0; i < hv_Length1; i++)
		{
			m_Camera.AddString(hv_ValueList[i].S());
		}
	}
	
	//��ʾͼƬ��picture�ؼ�
	
	HWND hImgWnd = GetDlgItem(IDC_STATIC_Image)->m_hWnd;
	GetDlgItem(IDC_STATIC_Image)->GetClientRect(&rtWindow);
	SetWindowAttr("background_color", "white");
	OpenWindow(rtWindow.left, rtWindow.top, rtWindow.Width(), rtWindow.Height(), (Hlong)hImgWnd, "visible", "", &m_htWindow);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	/*	Invalidate(FALSE);
		UpdateWindow();*/
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//����
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
		GetClientRect(&m_rect);//���仯��ĶԻ����С��Ϊ�ɴ�С
	}

}
void CMFCUIDlg::Modifys(int idc, CRect client, int x, int y)
{
	CWnd *pWin;
	pWin = GetDlgItem(idc);//��ȡ�ؼ����
	if (pWin)//�ж��Ƿ�Ϊ�գ���Ϊ�Ի��򴴽�ʱ����ô˺���������ʱ�ؼ���δ����
	{
		CRect Editrect;//��ȡ�ؼ��仯ǰ��С
		pWin->GetWindowRect(&Editrect);
		ScreenToClient(&Editrect);//���ؼ���Сת��Ϊ�ڶԻ����е���������
		//x/client.Width()Ϊ�Ի����ں���ı仯����

		Editrect.left = Editrect.left*x / client.Width();//�����ؼ���С
		Editrect.right = Editrect.right*x / client.Width();
		Editrect.top = Editrect.top*y / client.Height();
		Editrect.bottom = Editrect.bottom*y / client.Height();
		pWin->MoveWindow(Editrect);//�����ؼ���С

	}

}
void CMFCUIDlg::Modify(int idc, CRect client, int x, int y)
{
	CWnd *pWin;
	pWin = GetDlgItem(idc);//��ȡ�ؼ����
	if (pWin)//�ж��Ƿ�Ϊ�գ���Ϊ�Ի��򴴽�ʱ����ô˺���������ʱ�ؼ���δ����
	{
		CRect Editrect;//��ȡ�ؼ��仯ǰ��С
		pWin->GetWindowRect(&Editrect);
		ScreenToClient(&Editrect);//���ؼ���Сת��Ϊ�ڶԻ����е���������
		//x/client.Width()Ϊ�Ի����ں���ı仯����

		Editrect.left = Editrect.left*x / client.Width();//�����ؼ���С
		Editrect.right = Editrect.right*x / client.Width();
		Editrect.top = Editrect.top*y / client.Height();
		Editrect.bottom = Editrect.bottom*y / client.Height() + 90;
		pWin->MoveWindow(Editrect);//�����ؼ���С

	}

}


//�����
void CMFCUIDlg::OnBnClickedButtonGrab()
{
		//��ȡ�������
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
		////�����
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
		//������		
	//�жϸ�ѡ������

	//�����
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
		MessageBox("�����ʧ��");
	}

	
	
	flag1 = true;
	B_Grab.EnableWindow(FALSE);
}

//ץͼ����
void CMFCUIDlg::OnBnClickedButton2Deal()
{
	if (flag1 == true)
	{
		MessageBeep(MB_ICONHAND);
		m_ListCtrl.SetRedraw(FALSE);
		//�жϸ�ѡ������
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
		//��λ����
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
			//8*12����
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
			//�����������
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
		//��ʾʶ����Ŀ
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
	//MessageBox("��Ч�Ĳ�����û�����������","����");
	return;
	}
}

//ע����
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

//����ͼ��
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

		TCHAR szFilter[] = _T("jpg file(.jpg)|.jpg|bmp file(.bmp)|.bmp|�����ļ�(*.*)|*.*||");
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

//����ΪTxt
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
		CString strFilter = _T("txt�ļ�(*.txt)|*.txt");
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

//����ΪExcel
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
	//�жϸ�ѡ������
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
	//����list control
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
		CString strFilter = _T("xls�ļ�(*.xls)|*.xls");
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

//���浽���ݿ�
void CMFCUIDlg::OnBnClickedButton4Sql()
{
	//�жϸ�ѡ������
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
	//����list control
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
		//MessageBox(_T("���ݿ�����chengg!"));
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

//��ʼ��list control
void CMFCUIDlg::init_list_control()
{
	
	//��ͷ
	m_ListCtrl.SetItemState(30, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrl.InsertColumn(0, _T("���"));
	m_ListCtrl.InsertColumn(1, _T("λ��"));
	m_ListCtrl.InsertColumn(2, _T("��������"));
	m_ListCtrl.InsertColumn(3, _T("�걾����"));
	m_ListCtrl.InsertColumn(4, _T("�������"));
	m_ListCtrl.InsertColumn(5, _T("�걾����"));
	m_ListCtrl.InsertColumn(6, _T("��������"));
	m_ListCtrl.InsertColumn(7, _T("����λ��"));
	m_ListCtrl.InsertColumn(8, _T("���ʱ��"));
	CRect rect;
	m_ListCtrl.GetClientRect(rect);
	m_ListCtrl.SetColumnWidth(0, 0.2*rect.Width());
	m_ListCtrl.SetColumnWidth(1, 0.2*rect.Width());
	m_ListCtrl.SetColumnWidth(2, 0.3*rect.Width());
	m_ListCtrl.SetColumnWidth(3, 0.3*rect.Width());
}

//��ʼ��״̬��
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

//��ݼ��麯������
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
		//������ټ����ú�������˵������еļ��ټ���
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

//���listctrl�ؼ���NM_CLICK��Ϣ��Ӧ����,�õ�������CListCtrl�����к�
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

//�޸���������
void CMFCUIDlg::OnBnClickedButtonChangecontext()
{
	UpdateData();
	CString Mostr = m_ChangeContext;
	UpdateData(TRUE);
	m_ListCtrl.SetItemText(MoRow, MoCol + 1, _T(Mostr));
}

//itemѡ�и���
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

		if (index == nItem)//���Ҫˢ�µ���Ϊ��ǰѡ������������Ϊ��ɫ������ɫ��Ϊ��ɫ
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

//�ر����
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

//�ı�������ɫ������
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

//����
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
		/*sprintf(select_user, "update out_data set ����ʱ��="+ "WHERE �������� = ('%s')", BoxNumber);*/
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
	//�жϸ�ѡ������
	//int nIndex = m_Language.GetCurSel();
	//CString strCBText;
	//m_Language.GetLBText(nIndex, strCBText);
	const char* HeadEnglish[] = { "Order" ,"Index","BarcodeContent","SampleContent","BoxNumber","SampleType","BoxDesc","BoxLocation","SaveTime" };
		GetPrivateProfileString("Language Info", "ButtonOpen", "Connect Camera(F2)", strButtonOpen.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON_Grab)->SetWindowText(strButtonOpen);
		GetPrivateProfileString("Language Info", "ButtonClose", "Close Camera(F3)", strButtonClose.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON_Exit)->SetWindowText(strButtonClose);
		GetPrivateProfileString("Language Info", "ButtonDeal", "Deal(F3)", strButtonDeal.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON2_Deal)->SetWindowText(strButtonDeal);
		GetPrivateProfileString("Language Info", "ButtonImage", "Save as Photo(F4)", strButtonImage.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON3_Image)->SetWindowText(strButtonImage);
		GetPrivateProfileString("Language Info", "ButtonSql", "Save to DataBase(F5)", strButtonSql.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON4_Sql)->SetWindowText(strButtonSql);
		GetPrivateProfileString("Language Info", "ButtonTxt", "Save as TXT(F6)", strButtonTxt.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON5_Txt)->SetWindowText(strButtonTxt);
		GetPrivateProfileString("Language Info", "ButtonExcel", "Save as Excel(F7)", strButtonExcel.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON5_Excel)->SetWindowText(strButtonExcel);
		GetPrivateProfileString("Language Info", "ButtonOut", "Outbound", strButtonOut.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON_OutSql)->SetWindowText(strButtonOut);
		GetPrivateProfileString("Language Info", "ButtonChange", "modification content  ", strButtonChange.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_BUTTON_ChangeContext)->SetWindowText(strButtonChange);
		GetPrivateProfileString("Language Info", "StaticTotal", "Total", strStaticTotal.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC_Total)->SetWindowText(strStaticTotal);
		GetPrivateProfileString("Language Info", "StaticDeal", "Dealed", strStaticDeal.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC_Dealed)->SetWindowText(strStaticDeal);
		GetPrivateProfileString("Language Info", "StaticFailed", "Failed", strStaticFailed.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC)->SetWindowText(strStaticFailed);
		GetPrivateProfileString("Language Info", "StaticSize", "Size Choose", strStaticSize.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC0)->SetWindowText(strStaticSize);
		GetPrivateProfileString("Language Info", "StaticOutZone", "Outbound operation", strStaticOutZone.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC14)->SetWindowText(strStaticOutZone);
		GetPrivateProfileString("Language Info", "StaticOutContent", "Info of  barcode ", strStaticOutContent.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_STATICOutsql)->SetWindowText(strStaticOutContent);
		GetPrivateProfileString("Language Info", "StaticBoxInfoZone", "Info of tube box", strStaticBoxInfoZone.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC18)->SetWindowText(strStaticBoxInfoZone);
		GetPrivateProfileString("Language Info", "StaticBoxNumber", "tube box code", strStaticBoxNumber.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC8)->SetWindowText(strStaticBoxNumber);
		GetPrivateProfileString("Language Info", "StaticSampleType", "Sample Type", strStaticSampleType.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC9)->SetWindowText(strStaticSampleType);
		GetPrivateProfileString("Language Info", "StaticBoxDesc", "description of tube box", strStaticBoxDesc.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC10)->SetWindowText(strStaticBoxDesc);
		GetPrivateProfileString("Language Info", "StaticBoxLocation", "Location of tube box", strStaticBoxLocation.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC11)->SetWindowText(strStaticBoxLocation);
		GetPrivateProfileString("Language Info", "StaticModifyZone", "modification of sample type ", strStaticModifyZone.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetDlgItem(IDC_STATIC7)->SetWindowText(strStaticModifyZone);
		GetPrivateProfileString("Language Info", "GrabWelcome", "welcome to use�� choose barcode specifications��then start recognition", VarGrabWelcome.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetPrivateProfileString("Language Info", "MessageBox2 ", "failed to open camera��please try again", strMessageBox2.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
		GetPrivateProfileString("Language Info", "MessageBox1 ", "no camera found��please check the camera", strMessageBox1.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetPrivateProfileString("Language Info", "MessageBox3 ", "failed ��please try again", strMessageBox3.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetPrivateProfileString("Language Info", "MessageBox4 ", "There have no data to save", strMessageBox4.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetPrivateProfileString("Language Info", "MessageBox5 ", "Invalid operation, please click the button to connect camera first", strMessageBox5.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetPrivateProfileString("Language Info", "MessageBox6 ", "can not open the camera��please check the camera type", strMessageBox6.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetPrivateProfileString("Language Info", "MessageBox7 ", "unable to connect to database!!", strMessageBox7.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
		GetPrivateProfileString("Language Info", "BoxInfo ", "Tube Box Information", txtBoxInfo.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetPrivateProfileString("Language Info", "SaveTime ", "Save Time", strSaveTime.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		GetPrivateProfileString("Language Info", "CryotubeInfo ", "Cryogenic Vial Information", txtCryotubeInfo.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\EnglishConfig.ini");
		for (int i = 0; i < 9; i++)
		{
			CHeaderCtrl* pListHeader = m_ListCtrl.GetHeaderCtrl();
			HDITEM hditem;
			//enum { sizeOfBuffer = 256 };
			TCHAR  lpBuffer[256];
			hditem.mask = HDI_TEXT;//ȡ�ַ�����  
			hditem.pszText = lpBuffer;//�ַ������� 
			hditem.cchTextMax = 256;//��������С 
			pListHeader->GetItem(i, &hditem);
			CString s = HeadEnglish[i];
			hditem.pszText = (LPSTR)(LPCSTR)s;
			pListHeader->SetItem(i, &hditem);
		}
}

void CMFCUIDlg::OnBnClickedButtonChinese()
{
	const char* HeadChinese[] = { "���" ,"λ��","��������","�걾����","�������","�걾����","��������","����λ��","���ʱ��" };
	GetPrivateProfileString("Language Info", "ButtonOpen", "�������(F2)", strButtonOpen.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON_Grab)->SetWindowText(strButtonOpen);
	GetPrivateProfileString("Language Info", "ButtonClose", "�ر����(F3)", strButtonClose.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON_Exit)->SetWindowText(strButtonClose);
	GetPrivateProfileString("Language Info", "ButtonDeal", "����ʶ��(F3)", strButtonDeal.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON2_Deal)->SetWindowText(strButtonDeal);
	GetPrivateProfileString("Language Info", "ButtonImage", "����ΪͼƬ(F4)", strButtonImage.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON3_Image)->SetWindowText(strButtonImage);
	GetPrivateProfileString("Language Info", "ButtonSql", "���浽���ݿ�(F5)", strButtonSql.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON4_Sql)->SetWindowText(strButtonSql);
	GetPrivateProfileString("Language Info", "ButtonTxt", "����ΪTXT(F6)", strButtonTxt.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON5_Txt)->SetWindowText(strButtonTxt);
	GetPrivateProfileString("Language Info", "ButtonExcel", "����ΪExcel(F7)", strButtonExcel.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON5_Excel)->SetWindowText(strButtonExcel);
	GetPrivateProfileString("Language Info", "ButtonOut", "����", strButtonOut.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON_OutSql)->SetWindowText(strButtonOut);
	GetPrivateProfileString("Language Info", "ButtonChange", "�޸�����", strButtonChange.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_BUTTON_ChangeContext)->SetWindowText(strButtonChange);
	GetPrivateProfileString("Language Info", "StaticTotal", "����", strStaticTotal.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC_Total)->SetWindowText(strStaticTotal);
	GetPrivateProfileString("Language Info", "StaticDeal", "ʶ��", strStaticDeal.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC_Dealed)->SetWindowText(strStaticDeal);
	GetPrivateProfileString("Language Info", "StaticFailed", "δʶ��", strStaticFailed.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC)->SetWindowText(strStaticFailed);
	GetPrivateProfileString("Language Info", "StaticSize", "������ѡ��", strStaticSize.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC0)->SetWindowText(strStaticSize);
	GetPrivateProfileString("Language Info", "StaticOutZone", "���������", strStaticOutZone.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC14)->SetWindowText(strStaticOutZone);
	GetPrivateProfileString("Language Info", "StaticOutContent", "������������", strStaticOutContent.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_STATICOutsql)->SetWindowText(strStaticOutContent);
	GetPrivateProfileString("Language Info", "StaticBoxInfoZone", "������Ϣ��д��", strStaticBoxInfoZone.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC18)->SetWindowText(strStaticBoxInfoZone);
	GetPrivateProfileString("Language Info", "StaticBoxNumber", "���ӱ��", strStaticBoxNumber.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC8)->SetWindowText(strStaticBoxNumber);
	GetPrivateProfileString("Language Info", "StaticSampleType", "�걾����", strStaticSampleType.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC9)->SetWindowText(strStaticSampleType);
	GetPrivateProfileString("Language Info", "StaticBoxDesc", "��������", strStaticBoxDesc.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC10)->SetWindowText(strStaticBoxDesc);
	GetPrivateProfileString("Language Info", "StaticBoxLocation", "����λ��", strStaticBoxLocation.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC11)->SetWindowText(strStaticBoxLocation);
	GetPrivateProfileString("Language Info", "StaticModifyZone", "�걾�����޸���", strStaticModifyZone.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetDlgItem(IDC_STATIC7)->SetWindowText(strStaticModifyZone);
	GetPrivateProfileString("Language Info", "GrabWelcome", "��ӭʹ��,����ѡ��������,Ȼ��ʼʶ��", VarGrabWelcome.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "MessageBox2 ", "�����ʧ��,������", strMessageBox2.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "MessageBox1 ", "û���ڴ��豸�ϼ�⵽�κο��õ����\n��ȷ���Ƿ��Ѿ��������", strMessageBox1.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "MessageBox3 ", "����ʧ��,������", strMessageBox3.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "MessageBox4 ", "û������Ҫ����", strMessageBox4.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "MessageBox5 ", "û���������,��Ч�Ĳ���", strMessageBox5.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "MessageBox6 ", "�޷���ָ�������\n��ȷ��������ͺ�", strMessageBox6.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "MessageBox7 ", "���ݿ�����ʧ��!", strMessageBox7.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "BoxInfo ", "������Ϣ", txtBoxInfo.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	GetPrivateProfileString("Language Info", "SaveTime ", "����ʱ��", strSaveTime.GetBuffer(MAX_PATH), MAX_PATH, "D:\\ϵͳ�ļ�\\ChineseConfig.ini");
	for (int i = 0; i < 9; i++)
	{
		CHeaderCtrl* pListHeaderr = m_ListCtrl.GetHeaderCtrl();
		HDITEM hditemm;
		//enum { sizeOfBuffer = 256 };
		TCHAR  lpBuffer[256];
		hditemm.mask = HDI_TEXT;//ȡ�ַ�����  
		hditemm.pszText = lpBuffer;//�ַ������� 
		hditemm.cchTextMax = 256;//��������С 
		pListHeaderr->GetItem(i, &hditemm);
		CString ss = HeadChinese[i];
		hditemm.pszText = (LPSTR)(LPCSTR)ss;
		pListHeaderr->SetItem(i, &hditemm);
	}
}

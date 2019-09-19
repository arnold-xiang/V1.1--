#pragma once


// CWelcomeDlg 对话框

class CWelcomeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWelcomeDlg)

public:
	CWelcomeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CWelcomeDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WELCOME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	//afx_msg void OnTimer(UINT nIDEvent);
	CFont mw_font;
	CFont msw_font;
	CBrush m_brush;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};

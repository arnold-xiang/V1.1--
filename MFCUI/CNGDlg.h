#pragma once


// CNGDlg 对话框

class CNGDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNGDlg)

public:
	CNGDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CNGDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
protected:
	virtual BOOL OnInitDialog();
public:
	CFont mw_font;
	CBrush m_brush;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

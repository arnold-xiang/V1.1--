#pragma once


// CNOOPENCDlg 对话框

class CNOOPENCDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNOOPENCDlg)

public:
	CNOOPENCDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CNOOPENCDlg();
	CFont mmmm_font;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOOPENC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
protected:
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CBrush m_brush;
	afx_msg void OnBnClickedButton1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

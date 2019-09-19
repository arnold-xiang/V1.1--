#pragma once


// CNOCameraDlg 对话框

class CNOCameraDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNOCameraDlg)

public:
	CNOCameraDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CNOCameraDlg();
	CFont mm_font;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOCAMERA };
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

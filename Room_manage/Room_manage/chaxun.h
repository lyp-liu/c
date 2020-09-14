#pragma once


// chaxun 对话框

class chaxun : public CDialogEx
{
	DECLARE_DYNAMIC(chaxun)

public:
	chaxun(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~chaxun();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGchaxun };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CListCtrl shuchu;
	CString m_xingming;
	int m_fanghao;
//	void OnPaint();
	afx_msg void OnPaint();
};

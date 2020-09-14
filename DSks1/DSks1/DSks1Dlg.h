
// DSks1Dlg.h: 头文件
//

#pragma once


// CDSks1Dlg 对话框
class CDSks1Dlg : public CDialogEx
{
// 构造
public:
	CDSks1Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DSKS1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString data1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	int bianliang1;
	int bianliang2;
	CListCtrl shuchu;
	afx_msg void OnBnClickedButton3();
	int n;
	int m;
	afx_msg void OnBnClickedButton4();
	
	afx_msg void OnBnClickedButton5();
	int choice1;
	int zhongzhi;
	afx_msg void OnBnClickedButton6();
	CString xiangjiao;
	int jiaozhi;
	afx_msg void OnEnChangeEdit10();
};

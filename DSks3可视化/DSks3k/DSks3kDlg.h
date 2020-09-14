
// DSks3kDlg.h: 头文件
//

#pragma once

#include<vector>
#include<bits/stdc++.h>
// CDSks3kDlg 对话框
class CDSks3kDlg : public CDialogEx
{
// 构造
public:
	CDSks3kDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DSKS3K_DIALOG };
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
	/*string raokai;
	string qidian;
	string zhongdian;*/
	afx_msg void OnBnClickedButton1();
	CString raokai;
	
	CString zhongdian;
	void add(int,int,int);
	void Init();
	afx_msg void OnBnClickedButton2();
	CListCtrl shuchu;
	int bfs(int,int);
	afx_msg void OnBnClickedButton3();
	
	
	
	CString qidian;
	afx_msg void OnBnClickedButton4();
	void Dijkstra(bool);
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	void Floyd(int);
};



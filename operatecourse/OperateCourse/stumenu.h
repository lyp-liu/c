#pragma once


// stumenu 对话框
#include"xuanke.h"
class stumenu : public CDialogEx
{
	DECLARE_DYNAMIC(stumenu)

public:
	stumenu(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~stumenu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_stumenu };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	xuanke *xkdlg;
	CString tkid;
	CListCtrl shuchu;
	Stuinf stuinf;
	Course course;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	string tempid[1000], tempxm[1000], tempcourse[1000]; int tempscore[1000];
	int jishu = 0,j=0;
	double stupf;
	CString stupy;
	afx_msg void OnBnClickedButton3();
	CString teachnm;
};

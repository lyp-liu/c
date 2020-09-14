#pragma once


// xuanke 对话框

class xuanke : public CDialogEx
{
	DECLARE_DYNAMIC(xuanke)

public:
	xuanke(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~xuanke();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_xuanke };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Stuinf stuinf;
	Course course;
	CListCtrl shuchu;
	CString xkid;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	int j = 0;
	int jishu = 0;
	int i = 1;
	string tempid[1000], tempxm[1000], tempcourse[1000]; int tempscore[1000];
};

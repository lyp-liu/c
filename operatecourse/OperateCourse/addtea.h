#pragma once


// addtea 对话框

class addtea : public CDialogEx
{
	DECLARE_DYNAMIC(addtea)

public:
	addtea(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~addtea();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_addtea };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString addid;
	CString addname;
	CString addsub1;
	CString addsub2;
	CString addsub3;
	CString addsub4;
	CString addsub5;
	afx_msg void OnBnClickedButton2();
	Teacher teacher;
	int t_num = 0;
	virtual BOOL OnInitDialog();
};

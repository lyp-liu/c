#pragma once


// addstu 对话框

class addstu : public CDialogEx
{
	DECLARE_DYNAMIC(addstu)

public:
	addstu(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~addstu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_addstu };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	Student student;
	int s_num = 0;
	CString addid;
	CString addname;
	int addclass;
	CString addzy;
	afx_msg void OnBnClickedButton1();
};

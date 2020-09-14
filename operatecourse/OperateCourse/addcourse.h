#pragma once


// addcourse 对话框

class addcourse : public CDialogEx
{
	DECLARE_DYNAMIC(addcourse)

public:
	addcourse(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~addcourse();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_addcourse };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Course course;
	int c_num = 0;
	virtual BOOL OnInitDialog();
	CString addcourseid;
	double addxf;
	int addtime;
	CString addtype;
	CString addcoursenm;
	afx_msg void OnBnClickedButton3();
};

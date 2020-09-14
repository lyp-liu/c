#pragma once


// admin 对话框
#include"paixushuchu.h"
#include"addcourse.h"
#include"addstu.h"
#include"addtea.h"
class admin : public CDialogEx
{
	DECLARE_DYNAMIC(admin)

public:
	admin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~admin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_admin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int t_num=0,s_num=0,c_num=0;
	addcourse *cdlg;
	addstu *sdlg;
	addtea *tdlg;
	Student student;
	Teacher teacher;
	Course course;
	/*CString addid;
	CString addname;
	int addclass;
	/*CString addzy;
	CString addsub1;
	CString addsub2;
	CString addsub3;
	CString addsub4;
	CString addsub5;*/
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	//CString addcourse;
	afx_msg void OnBnClickedButton3();
	/*CString addcourseid;
	double addxf;
	int addtime;
	CString addtype;*/
	CString delename;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	paixushuchu *pxdlg;
};

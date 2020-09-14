// addcourse.cpp: 实现文件
//

#include "stdafx.h"
#include "OperateCourse.h"
#include "addcourse.h"
#include "afxdialogex.h"
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

// addcourse 对话框

IMPLEMENT_DYNAMIC(addcourse, CDialogEx)

addcourse::addcourse(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_addcourse, pParent)
	, addcourseid(_T(""))
	, addxf(0)
	, addtime(0)
	, addtype(_T(""))
	, addcoursenm(_T(""))
{

}

addcourse::~addcourse()
{
}

void addcourse::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT11, addcourseid);
	DDX_Text(pDX, IDC_EDIT12, addxf);
	DDX_Text(pDX, IDC_EDIT13, addtime);
	DDX_Text(pDX, IDC_EDIT14, addtype);
	DDX_Text(pDX, IDC_EDIT10, addcoursenm);
}


BEGIN_MESSAGE_MAP(addcourse, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &addcourse::OnBnClickedButton3)
END_MESSAGE_MAP()


// addcourse 消息处理程序


BOOL addcourse::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ifstream is;
	is.open("module.txt");
	while (!is.eof()) {
		is >> course[c_num].id >> course[c_num].c_name >> course[c_num].xuefen
			>> course[c_num].xueshi >> course[c_num].type;
		c_num++;
	}
	c_num--;
	is.close();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void addcourse::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string tpid, tpname, tptype;
	tpid = CT2A(addcourseid.GetString());
	tpname = CT2A(addcoursenm.GetString());
	tptype = CT2A(addtype.GetString());
	course[c_num].id = tpid;
	course[c_num].c_name = tpname;
	course[c_num].type = tptype;
	course[c_num].xuefen = addxf;
	course[c_num].xueshi = addtime;
	c_num++;
	ofstream out;
	out.open("course.txt");
	for (int i = 0; i < c_num; i++) {
		out << course[i].id << '\t' << course[i].c_name << '\t'
			<< course[i].xuefen << '\t' << course[i].xueshi << '\t' <<
			course[i].xueshi << '\t' << course[i].type << '\n';
	}
	out.close();
	out.open("module.txt", ios::app);
	int i = c_num - 1;
	out << course[i].id << '\t' << course[i].c_name << '\t'
		<< course[i].xuefen << '\t' << course[i].xueshi << '\t' <<
		course[i].xueshi << '\t' << course[i].type << '\n';

	out.close();
	MessageBox(L"添加成功");
}

// addstu.cpp: 实现文件
//

#include "stdafx.h"
#include "OperateCourse.h"
#include "addstu.h"
#include "afxdialogex.h"
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

// addstu 对话框

IMPLEMENT_DYNAMIC(addstu, CDialogEx)

addstu::addstu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_addstu, pParent)
	, addid(_T(""))
	, addname(_T(""))
	, addclass(0)
	, addzy(_T(""))
{

}

addstu::~addstu()
{
}

void addstu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, addid);
	DDX_Text(pDX, IDC_EDIT2, addname);
	DDX_Text(pDX, IDC_EDIT3, addclass);
	DDX_Text(pDX, IDC_EDIT4, addzy);
}


BEGIN_MESSAGE_MAP(addstu, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &addstu::OnBnClickedButton1)
END_MESSAGE_MAP()


// addstu 消息处理程序


BOOL addstu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ifstream in;
	in.open("student.txt");
	while (!in.eof()) {
		in >> student[s_num].s_id >> student[s_num].s_name >>
			student[s_num].s_banji >> student[s_num].zhuanye;
		s_num++;
	}
	s_num--;
	in.close();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void addstu::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string tpid, tpname, tpzy;
	tpid = CT2A(addid.GetString());
	tpname = CT2A(addname.GetString());
	tpzy = CT2A(addzy.GetString());
	student[s_num].s_id = tpid;
	student[s_num].s_name = tpname;
	student[s_num].s_banji = addclass;
	student[s_num].zhuanye = tpzy;
	s_num++;
	ofstream out;
	out.open("stu.txt");
	for (int i = 0; i < s_num; i++) {
		out << student[i].s_id << '\t' << student[i].s_name << '\t' << student[i].s_banji << '\t' << student[i].zhuanye << '\n';
	}
	out.close();
	ofstream otf;
	otf.open("student.txt", ios::app);
	otf << student[s_num - 1].s_id << '\t' << student[s_num - 1].s_name << '\t' << student[s_num - 1].s_banji << '\t' << student[s_num - 1].zhuanye << '\n';
	otf.close();
	otf.open("account.txt", ios::app);
	string tmp1 = "123", tmp2 = "student";
	otf << student[s_num - 1].s_id << '\t' << student[s_num - 1].s_name << '\t' << tmp1 << '\t' << tmp2 << '\n';
	otf.close();
	MessageBox(L"添加成功");
}

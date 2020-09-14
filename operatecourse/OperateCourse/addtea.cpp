// addtea.cpp: 实现文件
//

#include "stdafx.h"
#include "OperateCourse.h"
#include "addtea.h"
#include "afxdialogex.h"
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

// addtea 对话框

IMPLEMENT_DYNAMIC(addtea, CDialogEx)

addtea::addtea(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_addtea, pParent)
	, addid(_T(""))
	, addname(_T(""))
	, addsub1(_T("none"))
	, addsub2(_T("none"))
	, addsub3(_T("none"))
	, addsub4(_T("none"))
	, addsub5(_T("none"))
{

}

addtea::~addtea()
{
}

void addtea::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, addid);
	DDX_Text(pDX, IDC_EDIT2, addname);
	DDX_Text(pDX, IDC_EDIT5, addsub1);
	DDX_Text(pDX, IDC_EDIT6, addsub2);
	DDX_Text(pDX, IDC_EDIT8, addsub3);
	DDX_Text(pDX, IDC_EDIT7, addsub4);
	DDX_Text(pDX, IDC_EDIT9, addsub5);
}


BEGIN_MESSAGE_MAP(addtea, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &addtea::OnBnClickedButton2)
END_MESSAGE_MAP()


// addtea 消息处理程序


void addtea::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string tpid, tpname, tp1, tp2, tp3, tp4, tp5;
	tpid = CT2A(addid.GetString());
	tpname = CT2A(addname.GetString());
	tp1 = CT2A(addsub1.GetString());
	tp2 = CT2A(addsub2.GetString());
	tp3 = CT2A(addsub3.GetString());
	tp4 = CT2A(addsub4.GetString());
	tp5 = CT2A(addsub5.GetString());
	teacher[t_num].t_id = tpid;
	teacher[t_num].t_name = tpname;
	teacher[t_num].sub1 = tp1;
	teacher[t_num].sub2 = tp2;
	teacher[t_num].sub3 = tp3;
	teacher[t_num].sub4 = tp4;
	teacher[t_num].sub5 = tp5;
	t_num++;
	ofstream out;
	out.open("teacher.txt");
	for (int i = 0; i < t_num; i++) {
		out << teacher[i].t_id << '\t' << teacher[i].t_name << '\t' << teacher[i].sub1 << '\t'
			<< teacher[i].sub2 << '\t' << teacher[i].sub3 << '\t' << teacher[i].sub4 << '\t'
			<< teacher[i].sub5 << '\n';
	}
	out.close();
	out.open("staff.txt", ios::app);
	int i = t_num - 1;
	out << teacher[i].t_id << '\t' << teacher[i].t_name << '\t' << teacher[i].sub1 << '\t'
		<< teacher[i].sub2 << '\t' << teacher[i].sub3 << '\t' << teacher[i].sub4 << '\t'
		<< teacher[i].sub5 << '\n';
	out.close();
	out.open("account.txt", ios::app);
	string tmp1 = "123", tmp2 = "teacher";
	out << teacher[i].t_id << '\t' << teacher[i].t_name << '\t' << tmp1 << '\t' << tmp2 << '\n';
	out.close();
	MessageBox(L"添加成功");
}


BOOL addtea::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ifstream infile;
	infile.open("staff.txt");
	while (!infile.eof()) {
		infile >> teacher[t_num].t_id >> teacher[t_num].t_name >>
			teacher[t_num].sub1 >> teacher[t_num].sub2 >> teacher[t_num].sub3
			>> teacher[t_num].sub4 >> teacher[t_num].sub5;
		t_num++;
	}
	t_num--;
	infile.close();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

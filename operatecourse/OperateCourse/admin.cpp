// admin.cpp: 实现文件
//

#include "stdafx.h"
#include "OperateCourse.h"
#include "admin.h"
#include "afxdialogex.h"
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

// admin 对话框

IMPLEMENT_DYNAMIC(admin, CDialogEx)

admin::admin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_admin, pParent)
	/*, addid(_T(""))
	, addname(_T(""))
	, addclass(0)
	, addzy(_T(""))
	, addsub1(_T("none"))
	, addsub2(_T("none"))
	, addsub3(_T("none"))
	, addsub4(_T("none"))
	, addsub5(_T("none"))
	, addcourse(_T(""))
	, addcourseid(_T(""))
	, addxf(0)
	, addtime(0)
	, addtype(_T(""))*/
	, delename(_T(""))
{
	pxdlg = NULL;
	tdlg = NULL;
	sdlg = NULL;
	cdlg = NULL;
}

admin::~admin()
{
	if (pxdlg != NULL) {
		delete pxdlg;
	}
	if (tdlg != NULL) {
		delete tdlg;
	}
	if (sdlg != NULL) {
		delete sdlg;
	}
	if (cdlg != NULL) {
		delete cdlg;
	}
}

void admin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	/*DDX_Text(pDX, IDC_EDIT1, addid);
	DDX_Text(pDX, IDC_EDIT2, addname);
	DDX_Text(pDX, IDC_EDIT3, addclass);
	DDX_Text(pDX, IDC_EDIT4, addzy);
	DDX_Text(pDX, IDC_EDIT5, addsub1);
	DDX_Text(pDX, IDC_EDIT6, addsub2);
	DDX_Text(pDX, IDC_EDIT8, addsub3);
	DDX_Text(pDX, IDC_EDIT7, addsub4);
	DDX_Text(pDX, IDC_EDIT9, addsub5);
	//DDX_Text(pDX, IDC_EDIT10, addcourse);
	DDX_Text(pDX, IDC_EDIT11, addcourseid);
	DDX_Text(pDX, IDC_EDIT12, addxf);
	DDX_Text(pDX, IDC_EDIT13, addtime);
	DDX_Text(pDX, IDC_EDIT14, addtype);*/
	DDX_Text(pDX, IDC_EDIT15, delename);
}


BEGIN_MESSAGE_MAP(admin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &admin::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &admin::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &admin::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &admin::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &admin::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &admin::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &admin::OnBnClickedButton7)
END_MESSAGE_MAP()


// admin 消息处理程序


void admin::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	/*UpdateData(TRUE);
	string tpid, tpname, tp1,tp2,tp3,tp4,tp5;
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
	out<< teacher[i].t_id << '\t' << teacher[i].t_name << '\t' << teacher[i].sub1 << '\t'
		<< teacher[i].sub2 << '\t' << teacher[i].sub3 << '\t' << teacher[i].sub4 << '\t'
		<< teacher[i].sub5 << '\n';
	out.close();
	out.open("account.txt", ios::app);
	string tmp1 = "123",tmp2="teacher";
	out << teacher[i].t_id << '\t' << teacher[i].t_name << '\t' << tmp1 << '\t' << tmp2 << '\n';
	out.close();
	MessageBox(L"添加成功");*/
	if (tdlg == NULL) {
		tdlg = new addtea();
		tdlg->Create(IDD_addtea, this);

	}
	tdlg->ShowWindow(SW_SHOW);
}


void admin::OnBnClickedButton1()//添加学生
{
	// TODO: 在此添加控件通知处理程序代码
	/*UpdateData(TRUE);
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
		out << student[i].s_id << '\t' << student[i].s_name << '\t' << student[i].s_banji <<'\t'<< student[i].zhuanye << '\n';
	}
	out.close();
	ofstream otf;
	otf.open("student.txt", ios::app);
	otf<<student[s_num-1].s_id<< '\t' << student[s_num-1].s_name << '\t' << student[s_num-1].s_banji << '\t' << student[s_num-1].zhuanye << '\n';
	otf.close();
	otf.open("account.txt", ios::app);
	string tmp1 = "123", tmp2 = "student";
	otf << student[s_num - 1].s_id << '\t' << student[s_num - 1].s_name << '\t' << tmp1 << '\t' << tmp2 << '\n';
	otf.close();
	MessageBox(L"添加成功");*/
	if (sdlg == NULL) {
		sdlg = new addstu();
		sdlg->Create(IDD_addstu, this);
		
	}
	sdlg->ShowWindow(SW_SHOW);
}


BOOL admin::OnInitDialog()
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
	ifstream in;
	in.open("student.txt");
	while (!in.eof()) {
		in >> student[s_num].s_id >> student[s_num].s_name >>
			student[s_num].s_banji >> student[s_num].zhuanye;
		s_num++;
	}
	s_num--;
	in.close();
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


void admin::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	/*UpdateData(TRUE);
	string tpid, tpname,tptype;
	tpid = CT2A(addcourseid.GetString());
	tpname = CT2A(addcourse.GetString());
	tptype= CT2A(addtype.GetString());
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
			<< course[i] .xuefen<< '\t' << course[i].xueshi<<'\t'<<
			course[i] .xueshi<<'\t'<< course[i] .type<< '\n';
	}
	out.close();
	out.open("module.txt",ios::app);
	int i = c_num - 1;
		out << course[i].id << '\t' << course[i].c_name << '\t'
			<< course[i].xuefen << '\t' << course[i].xueshi << '\t' <<
			course[i].xueshi << '\t' << course[i].type << '\n';
	
	out.close();
	MessageBox(L"添加成功");*/
	if (cdlg == NULL) {
		cdlg = new addcourse();
		cdlg->Create(IDD_addcourse, this);

	}
	cdlg->ShowWindow(SW_SHOW);
}


void admin::OnBnClickedButton4()//删除学生
{
	// TODO: 在此添加控件通知处理程序代码
	int a_num = 0;
	ifstream infile;
	infile.open("account.txt");
	string NUM[100], NAME[100], PWD[100], SF[100];
	while (!infile.eof()) {
		infile >> NUM[a_num] >> NAME[a_num] >> PWD[a_num] >> SF[a_num];
		a_num++;
	}
	a_num--;
	infile.close();
	UpdateData(TRUE);
	string tpname;
	tpname = CT2A(delename.GetString());
	for (int i = 0; i < s_num; i++) {
		if (tpname == student[i].s_name) {
			for (int j = i; j < s_num - 1; j++) {
				student[j] = student[j + 1];
			}
			s_num--;
			break;
		}
	}
	
	for (int i = 0; i < a_num; i++) {
		if (NAME[i] == tpname) {
			for (int j = i; j < a_num - 1; j++) {
				NUM[j] = NUM[j + 1];
				NAME[j] = NAME[j + 1];
				PWD[j] = PWD[j + 1];
				SF[j] = SF[j + 1];
			}
			a_num--;
		}
	}
	ofstream out;
	out.open("account.txt");
	for (int i = 0; i < a_num; i++) {
		out << NUM[i] << '\t' << NAME[i] << '\t' << PWD[i] << '\t' << SF[i] << '\n';
	}
	out.close();
	out.open("stu.txt");
	for (int i = 0; i < s_num; i++) {
		out << student[i].s_id << '\t' << student[i].s_name << '\t' << student[i].s_banji << '\t' << student[i].zhuanye << '\n';
	}
	out.close();
	out.open("student.txt");
	for (int i = 0; i < s_num; i++) {
		out << student[i].s_id << '\t' << student[i].s_name << '\t' << student[i].s_banji << '\t' << student[i].zhuanye << '\n';
	}
	out.close();
	MessageBox(L"删除成功");
}
void admin::OnBnClickedButton5()//删除老师
{
	// TODO: 在此添加控件通知处理程序代码
	int a_num = 0;
	ifstream infile;
	infile.open("account.txt");
	string NUM[100], NAME[100], PWD[100], SF[100];
	while (!infile.eof()) {
		infile >> NUM[a_num] >> NAME[a_num] >> PWD[a_num] >> SF[a_num];
		a_num++;
	}
	a_num--;
	infile.close();
	UpdateData(TRUE);
	string tpname;
	tpname = CT2A(delename.GetString());
	for (int i = 0; i < t_num; i++) {
		for (int j = i; j < t_num - 1; j++) {
			teacher[j] = teacher[j + 1];
		}
		t_num--;
		break;
	}
	for (int i = 0; i < a_num; i++) {
		if (NAME[i] == tpname) {
			for (int j = i; j < a_num - 1; j++) {
				NUM[j] = NUM[j + 1];
				NAME[j] = NAME[j + 1];
				PWD[j] = PWD[j + 1];
				SF[j] = SF[j + 1];
			}
			a_num--;
		}
	}
	ofstream out;
	out.open("account.txt");
	for (int i = 0; i < a_num; i++) {
		out << NUM[i] << '\t' << NAME[i] << '\t' << PWD[i] << '\t' << SF[i] << '\n';
	}
	out.close();
	out.open("teacher.txt");
	for (int i = 0; i < t_num; i++) {
		out << teacher[i].t_id << '\t' << teacher[i].t_name << '\t' << teacher[i].sub1 << '\t'
			<< teacher[i].sub2 << '\t' << teacher[i].sub3 << '\t' << teacher[i].sub4 << '\t'
			<< teacher[i].sub5 << '\n';
	}
	out.close();
	out.open("staff.txt");
	for (int i = 0; i < t_num; i++) {
		out << teacher[i].t_id << '\t' << teacher[i].t_name << '\t' << teacher[i].sub1 << '\t'
			<< teacher[i].sub2 << '\t' << teacher[i].sub3 << '\t' << teacher[i].sub4 << '\t'
			<< teacher[i].sub5 << '\n';
	}
	out.close();
	MessageBox(L"删除成功");
}


void admin::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string tpname;
	tpname = CT2A(delename.GetString());
	for (int i = 0; i < c_num; i++) {
		for (int j = i; j < c_num - 1; j++) {
			course[j] = course[j + 1];
		}
		c_num--;
		break;
	}
	ofstream out;
	out.open("course.txt");
	for (int i = 0; i < c_num; i++) {
		out << course[i].id << '\t' << course[i].c_name << '\t'
			<< course[i].xuefen << '\t' << course[i].xueshi << '\t' <<
			course[i].xueshi << '\t' << course[i].type << '\n';
	}
	out.close();
	out.open("module.txt");
	for (int i = 0; i < c_num; i++) {
		out << course[i].id << '\t' << course[i].c_name << '\t'
			<< course[i].xuefen << '\t' << course[i].xueshi << '\t' <<
			course[i].xueshi << '\t' << course[i].type << '\n';
	}
	out.close();
	MessageBox(L"删除成功");
}


void admin::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	if (pxdlg == NULL) {
		pxdlg = new paixushuchu();
		pxdlg->Create(IDD_DIALOG1, this);
		pxdlg->setinfo();
	}
	pxdlg->ShowWindow(SW_SHOW);
}

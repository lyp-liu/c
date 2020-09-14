// stumenu.cpp: 实现文件
//

#include "stdafx.h"
#include "OperateCourse.h"
#include "stumenu.h"
#include "afxdialogex.h"
#include<fstream>
#include<string>
using namespace std;

// stumenu 对话框

IMPLEMENT_DYNAMIC(stumenu, CDialogEx)

stumenu::stumenu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_stumenu, pParent)
	, tkid(_T(""))
	, stupf(0)
	, stupy(_T(""))
	, teachnm(_T(""))
{
	xkdlg = NULL;
}

stumenu::~stumenu()
{
	if (xkdlg != NULL) {
		delete xkdlg;
	}
}

void stumenu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, tkid);
	DDX_Control(pDX, IDC_LIST1, shuchu);
	DDX_Text(pDX, IDC_EDIT2, stupf);
	DDX_Text(pDX, IDC_EDIT3, stupy);
	DDX_Text(pDX, IDC_EDIT4, teachnm);
}


BEGIN_MESSAGE_MAP(stumenu, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &stumenu::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &stumenu::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &stumenu::OnBnClickedButton3)
END_MESSAGE_MAP()


// stumenu 消息处理程序


void stumenu::OnBnClickedButton2()//退课
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string tk;
	tk= CT2A(tkid.GetString());
	for (int i = 0; i < j; i++) {
		if (tk == stuinf[i].id) {
			for (int m = i; m < j-1; m++) {
				stuinf[m].id = stuinf[m + 1].id;
				stuinf[m].name = stuinf[m + 1].name;
				stuinf[m].xuefen = stuinf[m + 1].xuefen;
				stuinf[m].type = stuinf[m + 1].type;
				stuinf[m].xueshi = stuinf[m + 1].xueshi;
				stuinf[m].grade = stuinf[m + 1].grade;
				stuinf[m].zhuren = stuinf[m + 1].zhuren;
			}
			j--;
			break;
		}
	}
	for (int i = 0; i < 100; i++) {//删除表格中元素
		shuchu.DeleteColumn(0);
	}
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	shuchu.InsertColumn(1, _T("课程编号"), LVCFMT_LEFT, 90);
	shuchu.InsertColumn(2, _T("课程名称"), LVCFMT_LEFT, 240);
	shuchu.InsertColumn(3, _T("学分"), LVCFMT_LEFT, 60);
	shuchu.InsertColumn(4, _T("课时"), LVCFMT_LEFT, 60);
	shuchu.InsertColumn(5, _T("课程类型"), LVCFMT_LEFT, 60);
	shuchu.InsertColumn(6, _T("分数"), LVCFMT_LEFT, 90);
	CString ID[50], NAME[50], XUEFEN[50], XUESHI[50], TYPE[50], GRADE[50];
	for (int m = 0; m < j; m++) {
		ID[m] = stuinf[m].id.c_str();

		NAME[m] = stuinf[m].name.c_str();
		XUEFEN[m].Format(L"%0.1f", stuinf[m].xuefen);
		XUESHI[m].Format(L"%d", stuinf[m].xueshi);
		TYPE[m] = stuinf[m].type.c_str();
		if (stuinf[m].grade != 0)
			GRADE[m].Format(L"%d", stuinf[m].grade);
		else GRADE[m].Format(L"%s", _T("暂无成绩"));
		shuchu.InsertItem(m, _T(""), 100);
		shuchu.SetItemText(m, 1, ID[m]);
		shuchu.SetItemText(m, 2, NAME[m]);
		shuchu.SetItemText(m, 3, XUEFEN[m]);
		shuchu.SetItemText(m, 4, XUESHI[m]);
		shuchu.SetItemText(m, 5, TYPE[m]);
		shuchu.SetItemText(m, 6, GRADE[m]);
	}
	ofstream out;
	out.open("score.txt");
	for (int m = 0; m < j; m++) {
		out << stuinf[m].xh <<'\t'<<stuinf[m].zhuren<< '\t' << stuinf[m].name << '\t' << stuinf[m].grade << '\n';
	}
	for (int m = 0; m < jishu; m++) {
		out << tempid[m] << '\t' << tempxm[m] << '\t' << tempcourse[m] << '\t' << tempscore[m] << '\n';
	}
	out.close();
}


void stumenu::OnBnClickedButton1()//打开选课界面
{
	// TODO: 在此添加控件通知处理程序代码
	if (xkdlg == NULL) {
		xkdlg = new xuanke();
		xkdlg->Create(IDD_xuanke, this);
	}
	xkdlg->ShowWindow(SW_SHOW);

}


BOOL stumenu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	DWORD dwStyle = shuchu.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	shuchu.SetExtendedStyle(dwStyle);
	shuchu.InsertItem(0, _T(""), 0);
	for (int i = 1; i < 40; i++) {
		shuchu.InsertItem(i, _T(""), 100);
	}
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	shuchu.InsertColumn(1, _T("课程编号"), LVCFMT_LEFT, 90);
	shuchu.InsertColumn(2, _T("课程名称"), LVCFMT_LEFT, 240);
	shuchu.InsertColumn(3, _T("学分"), LVCFMT_LEFT, 60);
	shuchu.InsertColumn(4, _T("课时"), LVCFMT_LEFT, 60);
	shuchu.InsertColumn(5, _T("课程类型"), LVCFMT_LEFT, 90);
	shuchu.InsertColumn(6, _T("分数"), LVCFMT_LEFT, 60);
	 int i(0); 
	string tpid, tpnm, tpcourse;int  tpgrade;
	ifstream in;
	in.open("module.txt");
	
	while (!in.eof()) {
		in >> course[i].id >> course[i].c_name >> course[i].xuefen >> course[i].xueshi >> course[i].type;
		i++;
	}
	i--;
	ifstream infile;
	infile.open("score.txt");
	while (1) {
		
		infile >> tpid>>tpnm>>tpcourse>>tpgrade;
		if (tpid == dqnum) {
			stuinf[j].xh = tpid;
			stuinf[j].zhuren = tpnm;
			stuinf[j].name = tpcourse;//已知课程信息中的名称和分数
			stuinf[j].grade = tpgrade;
			j++;
		}
		else {
			tempid[jishu] = tpid;
			tempxm[jishu] = tpnm;
			tempcourse[jishu] = tpcourse;
			tempscore[jishu] = tpgrade;
			jishu++;
		}
		
		if (infile.eof())
			break;
	}
	infile.close();
	//把course和stuinf中课程名称相同的找出来，把course中信息赋给stuinf对应的
	for (int m = 0; m< j; m++) {
		for (int n = 0; n < i; n++) {
			if (stuinf[m].name == course[n].c_name) {
				stuinf[m].id = course[n].id;
				stuinf[m].xuefen = course[n].xuefen;
				stuinf[m].xueshi = course[n].xueshi;
				stuinf[m].type = course[n].type;
			}
		}
	}
	CString ID[50],NAME[50],XUEFEN[50],XUESHI[50],TYPE[50],GRADE[50];
	for (int m = 0; m < j; m++) {
		ID[m] = stuinf[m].id.c_str();
		
		NAME[m]=stuinf[m].name.c_str();
			XUEFEN[m].Format(L"%0.1f", stuinf[m].xuefen);
			XUESHI[m].Format(L"%d", stuinf[m].xueshi);
			TYPE[m]=stuinf[m].type.c_str();
			if(stuinf[m].grade!=0)
				GRADE[m].Format(L"%d", stuinf[m].grade);
			else GRADE[m].Format(L"%s", _T("暂无成绩"));
			shuchu.InsertItem(m,_T(""),100);
			shuchu.SetItemText(m, 1, ID[m]);
			shuchu.SetItemText(m, 2, NAME[m]);
			shuchu.SetItemText(m, 3, XUEFEN[m]);
			shuchu.SetItemText(m, 4, XUESHI[m]);
			shuchu.SetItemText(m, 5, TYPE[m]);
			shuchu.SetItemText(m, 6, GRADE[m]);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void stumenu::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string tppy,tpname;//评语
	tppy = CT2A(stupy.GetString());
	tpname = CT2A(teachnm.GetString());
	ofstream out;
	out.open("manyidu.txt", ios::app);
	out << tpname << '\t' << nam << '\t' << stupf << '\t' << tppy << '\n';
	out.close();
	MessageBox(L"提交成功");
}

// xuanke.cpp: 实现文件
//

#include "stdafx.h"
#include "OperateCourse.h"
#include "xuanke.h"
#include "afxdialogex.h"
#include<fstream>
#include<iostream>
using namespace std;

// xuanke 对话框

IMPLEMENT_DYNAMIC(xuanke, CDialogEx)

xuanke::xuanke(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_xuanke, pParent)
	, xkid(_T(""))
{

}

xuanke::~xuanke()
{
}

void xuanke::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, shuchu);
	DDX_Text(pDX, IDC_EDIT1, xkid);
}


BEGIN_MESSAGE_MAP(xuanke, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &xuanke::OnBnClickedButton1)
END_MESSAGE_MAP()


// xuanke 消息处理程序


BOOL xuanke::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	DWORD dwStyle = shuchu.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	shuchu.SetExtendedStyle(dwStyle);
	shuchu.InsertItem(0, _T(""), 0);
	for (; i < 40; i++) {
		shuchu.InsertItem(i, _T(""), 100);
	}
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	shuchu.InsertColumn(1, _T("课程编号"), LVCFMT_LEFT, 90);
	shuchu.InsertColumn(2, _T("课程名称"), LVCFMT_LEFT, 240);
	shuchu.InsertColumn(3, _T("学分"), LVCFMT_LEFT, 60);
	shuchu.InsertColumn(4, _T("课时"), LVCFMT_LEFT, 60);
	shuchu.InsertColumn(5, _T("课程类型"), LVCFMT_LEFT, 90);
	ifstream in;
	in.open("module.txt");
	i = 0;
	while (!in.eof()) {
		in >> course[i].id >> course[i].c_name >> course[i].xuefen >> course[i].xueshi >> course[i].type;
		i++;
	}
	i--;
	CString ID[50], NAME[50], XUEFEN[50], XUESHI[50], TYPE[50];
	for (int m = 0; m < i; m++) {
		ID[m] = course[m].id.c_str();

		NAME[m] =course[m].c_name.c_str();
		XUEFEN[m].Format(L"%0.1f", course[m].xuefen);
		XUESHI[m].Format(L"%d", course[m].xueshi);
		TYPE[m] = course[m].type.c_str();
		
		shuchu.InsertItem(m, _T(""), 100);
		shuchu.SetItemText(m, 1, ID[m]);
		shuchu.SetItemText(m, 2, NAME[m]);
		shuchu.SetItemText(m, 3, XUEFEN[m]);
		shuchu.SetItemText(m, 4, XUESHI[m]);
		shuchu.SetItemText(m, 5, TYPE[m]);
		
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void xuanke::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	string tpid, tpnm, tpcourse; int  tpgrade;
	
	ifstream infile;
	infile.open("score.txt");
	while (!infile.eof()) {
		infile >> tpid >> tpnm >> tpcourse >> tpgrade;
		if (tpid == dqnum) {
			stuinf[j].zhuren = tpnm;
			stuinf[j].name = tpcourse;
			stuinf[j].grade = tpgrade;
			stuinf[j].xh = tpid;
			j++;
		}
		
		else {
			tempid[jishu] = tpid;
			tempxm[jishu] = tpnm;
			tempcourse[jishu] = tpcourse;
			tempscore[jishu] = tpgrade;
			jishu++;
		}
	}
	infile.close();
	string xk;
	xk = CT2A(xkid.GetString());;
	for (int m = 0; m < j; m++) {
		if (stuinf[m].name == xk) {
			MessageBox(L"你已经选过该课程了");
			return;
		}
	}
	
	for (int m = 0; m < i; m++) {
		if (xk == course[m].c_name) {
			stuinf[j].xh = dqnum;
			stuinf[j].zhuren = stuinf[j - 1].zhuren;
			stuinf[j].name = course[m].c_name;
			stuinf[j].grade = 0;
			j++;
		break;
		}
	}
	
	string st = "暂无成绩";
	ofstream out;
	out.open("score.txt");
	for (int m = 0; m < j; m++) {
		out << stuinf[m].xh << '\t' << stuinf[m].zhuren << '\t' << stuinf[m].name << '\t' << stuinf[m].grade << '\n';
	}
	for (int m = 0; m < jishu; m++) {
		out << tempid[m] << '\t' << tempxm[m] << '\t' << tempcourse[m] << '\t' << tempscore[m] << '\n';
	}
	out.close();
	MessageBox(L"选课成功");
}

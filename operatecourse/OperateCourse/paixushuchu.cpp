// paixushuchu.cpp: 实现文件
//

#include "stdafx.h"
#include "OperateCourse.h"
#include "paixushuchu.h"
#include "afxdialogex.h"
#include<string>
#include<iostream>
#include<fstream>
using namespace std;

// paixushuchu 对话框

IMPLEMENT_DYNAMIC(paixushuchu, CDialogEx)

paixushuchu::paixushuchu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

paixushuchu::~paixushuchu()
{
}

void paixushuchu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, shuchu);
}


BEGIN_MESSAGE_MAP(paixushuchu, CDialogEx)
END_MESSAGE_MAP()


// paixushuchu 消息处理程序


void paixushuchu::setinfo()
{
	// TODO: 在此处添加实现代码.
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	shuchu.InsertColumn(1, _T("教师姓名"), LVCFMT_LEFT, 90);
	shuchu.InsertColumn(2, _T("满意度"), LVCFMT_LEFT, 90);
	CString NAME[50], MYD[50];
	for (int i = 0; i < t_num; i++) {
		NAME[i] = teacher[i].t_name.c_str();
		MYD[i].Format(L"%0.1f", teacher[i].avmyd);
		shuchu.InsertItem(i, _T(""), 100);
		shuchu.SetItemText(i, 1, NAME[i]);
		shuchu.SetItemText(i, 2, MYD[i]);
	}
}


BOOL paixushuchu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ifstream in;
	in.open("staff.txt");
	while (!in.eof()) {
		in >> teacher[t_num].t_id >> teacher[t_num].t_name >>
			teacher[t_num].sub1 >> teacher[t_num].sub2 >>
			teacher[t_num].sub3 >> teacher[t_num].sub4 >>
			teacher[t_num].sub5;
		t_num++;
	}
	t_num--;
	in.close();
	ifstream infile;
	infile.open("manyidu.txt");
	while (!infile.eof()) {
		infile >> myd[m_num].teach >> myd[m_num].stu >> myd[m_num].score >> myd[m_num].pingjia;
		m_num++;
	}
	m_num--;
	infile.close();
	for (int j = 0; j < t_num; j++) {

		for (int i = 0; i < m_num; i++) {//求每个老师的平均分teacher[j].avmyd
			if (myd[i].teach == teacher[j].t_name) {
				teacher[j].avmyd += myd[i].score;
			}
		}
		teacher[j].avmyd /= m_num;
	}
	for (int i = 0; i <t_num; i++) {//排序
		for (int j = i; j < t_num - 1; j++) {
			if (teacher[j].avmyd < teacher[j + 1].avmyd) {
				double temp1; string temp2;
				temp1 = teacher[j].avmyd;
				temp2 = teacher[j].t_name;

				teacher[j].avmyd = teacher[1 + j].avmyd;
				teacher[j].t_name = teacher[j + 1].t_name;

				teacher[j+1].avmyd = temp1;
				teacher[j+1].t_id = temp2;
			}
				
		}
	}
	DWORD dwStyle = shuchu.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	shuchu.SetExtendedStyle(dwStyle);
	shuchu.InsertItem(0, _T(""), 0);
	/*for (int i = 1; i < 40; i++) {
		shuchu.InsertItem(i, _T(""), 100);
	}*/

	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

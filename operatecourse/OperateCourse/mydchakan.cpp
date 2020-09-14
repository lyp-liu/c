// mydchakan.cpp: 实现文件
//

#include "stdafx.h"
#include "OperateCourse.h"
#include "mydchakan.h"
#include "afxdialogex.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

// mydchakan 对话框

IMPLEMENT_DYNAMIC(mydchakan, CDialogEx)

mydchakan::mydchakan(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

mydchakan::~mydchakan()
{
}

void mydchakan::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, shuchu);
}


BEGIN_MESSAGE_MAP(mydchakan, CDialogEx)
END_MESSAGE_MAP()


// mydchakan 消息处理程序


BOOL mydchakan::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ifstream infile;
	infile.open("manyidu.txt");
	while (!infile.eof()) {
		infile >> myd[m_num].teach >> myd[m_num].stu >> myd[m_num].score >> myd[m_num].pingjia;
		m_num++;
	}
	m_num--;
	infile.close();
	DWORD dwStyle = shuchu.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	shuchu.SetExtendedStyle(dwStyle);
	shuchu.InsertItem(0, _T(""), 0);
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	shuchu.InsertColumn(1, _T("学生姓名"), LVCFMT_LEFT, 90);
	shuchu.InsertColumn(2, _T("评分"), LVCFMT_LEFT, 80);
	shuchu.InsertColumn(3, _T("评语"), LVCFMT_LEFT, 800);
	CString NAME[100], SCORE[100], PINGYU[100];
	for (int i = 0; i < m_num; i++) {
		NAME[i] = myd[i].stu.c_str();
		SCORE[i].Format(L"%0.1f", myd[i].score);
		PINGYU[i] = myd[i].pingjia.c_str();
		shuchu.InsertItem(i, _T(""), 100);
		shuchu.SetItemText(i, 1, NAME[i]);
		shuchu.SetItemText(i, 2, SCORE[i]);
		shuchu.SetItemText(i, 3, PINGYU[i]);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

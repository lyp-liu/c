// addscore.cpp: 实现文件
//

#include "stdafx.h"
#include "OperateCourse.h"
#include "addscore.h"
#include "afxdialogex.h"
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

// addscore 对话框

IMPLEMENT_DYNAMIC(addscore, CDialogEx)

addscore::addscore(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_addscore, pParent)
{

}

addscore::~addscore()
{
}

void addscore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(addscore, CDialogEx)
END_MESSAGE_MAP()


// addscore 消息处理程序

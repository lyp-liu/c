
// OperateCourseDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "OperateCourse.h"
#include "OperateCourseDlg.h"
#include "afxdialogex.h"
#include<fstream>
#include<iostream>
#include<string>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COperateCourseDlg 对话框



COperateCourseDlg::COperateCourseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPERATECOURSE_DIALOG, pParent)
	, m_yhm(_T(""))
	, m_pwd(_T(""))
{
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COperateCourseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_yhm);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}

BEGIN_MESSAGE_MAP(COperateCourseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &COperateCourseDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// COperateCourseDlg 消息处理程序

BOOL COperateCourseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void COperateCourseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COperateCourseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR COperateCourseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void COperateCourseDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Denglu a;
	ifstream infile;
	infile.open("account.txt");
	int i = 0;
	while (!infile.eof()) {
		infile >> a[i].id >>a[i].name>> a[i].pwd >> a[i].sf;
		i++;
	}
	string t1 = CT2A(m_pwd.GetString());
	string t2 = CT2A(m_yhm.GetString());
	for (int j = 0; j < i; j++) {
		if (t2 == a[j].id)
			break;
		if (t2 != a[j].id&&j!=i-1)
			continue;
		if(t2 != a[j].id&&j == i - 1)
			MessageBox(L"用户名或密码错误请重新输入");
	}
	for (int j = 0; j < i; j++) {
		if (t2== a[j].id) {
			if (t1 == a[j].pwd) {
				CString nm;
				nam = a[j].name;
				nm= a[j].name.c_str();
				dqnum = t2;
				if (a[j].sf == "teacher") {
					CDialog::EndDialog(IDD_OPERATECOURSE_DIALOG);
					MessageBox(nm+"老师您好");
					tcdlg.DoModal();
				}
				else if(a[j].sf == "student"){
					CDialog::EndDialog(IDD_OPERATECOURSE_DIALOG);
					MessageBox(nm + "同学你好");
					stdlg.DoModal();
				}
				else if (a[j].sf == "admin") {
					
						CDialog::EndDialog(IDD_OPERATECOURSE_DIALOG);
						addlg.DoModal();
				}
				
			}
		}
	}
		
}
	



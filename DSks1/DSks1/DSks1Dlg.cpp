
// DSks1Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "DSks1.h"
#include "DSks1Dlg.h"
#include "afxdialogex.h"
#include<cstring>
#include<string>
#include"LinkList.h"
#include<stdio.h>
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


// CDSks1Dlg 对话框



CDSks1Dlg::CDSks1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DSKS1_DIALOG, pParent)
	, data1(_T(""))
	, bianliang1(0)
	, bianliang2(0)
	, n(0)
	, m(0)

	, choice1(0)
	, zhongzhi(0)
	, xiangjiao(_T(""))
	, jiaozhi(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDSks1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, data1);
	DDX_Text(pDX, IDC_EDIT2, bianliang1);
	DDX_Text(pDX, IDC_EDIT3, bianliang2);
	DDX_Control(pDX, IDC_LIST2, shuchu);

	DDX_Text(pDX, IDC_EDIT4, m);
	DDX_Text(pDX, IDC_EDIT6, n);
	DDX_Text(pDX, IDC_EDIT7, choice1);
	DDX_Text(pDX, IDC_EDIT8, zhongzhi);
	DDX_Text(pDX, IDC_EDIT9, xiangjiao);
	DDX_Text(pDX, IDC_EDIT10, jiaozhi);
}

BEGIN_MESSAGE_MAP(CDSks1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDSks1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDSks1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDSks1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDSks1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDSks1Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CDSks1Dlg::OnBnClickedButton6)
	ON_EN_CHANGE(IDC_EDIT10, &CDSks1Dlg::OnEnChangeEdit10)
END_MESSAGE_MAP()


// CDSks1Dlg 消息处理程序

BOOL CDSks1Dlg::OnInitDialog()
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

	ShowWindow(SW_MAXIMIZE);

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	DWORD dwStyle = shuchu.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	shuchu.SetExtendedStyle(dwStyle);
	shuchu.InsertItem(0, _T(""), 0);
	shuchu.InsertItem(1, _T(""), 100);
	shuchu.InsertItem(2, _T(""), 100);
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDSks1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDSks1Dlg::OnPaint()
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
HCURSOR CDSks1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LinkList<int>d;
void CDSks1Dlg::OnBnClickedButton1()//生成链表
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int i = 0, j = 0, k[100];
	CString str = data1, warning("不能识别字符，请重新输入一个小于100的整数！");;

	CString s[100];
	do {
		int n = str.Find(_T(","));
		s[i] = str.Left(n);
		int m = n + 1;
		int length = str.Delete(0, m); //找出","右边的字符串位数
		str = str.Right(length);//将","右边的字符串取出做为新的字符串
		j = n + 1;
		k[i] = _ttoi(s[i]);
		for (int t = 0; t < i; t++) {
			if (!(k[t] <= 100 && k[t] >= 0)) {
				AfxMessageBox(warning);
				exit(1);
			}
		}
		i++;
	} while (str.Left(j) != '@');
	d.length = i;
	for (int l = 0; l < i; l++) {
		d.Insert( k[l]);
		d.DATA[l] = k[l];
	}
	for (int i = 0; i < 100; i++) {//删除表格中元素
		shuchu.DeleteColumn(0);
	}
	for (int i = 0; i < d.length; i++) {
		CString temp;
		temp.Format(_T("%d"), d.DATA[i]);
		int index = shuchu.InsertColumn(i + 1, _T(""), LVCFMT_LEFT, 100);
		shuchu.SetItemText(1, index, temp);
	}
}

LinkNode<int>*Newhead=NULL;
void CDSks1Dlg::OnBnClickedButton2()//搬迁链表
{
	// TODO: 在此添加控件通知处理程序代码
	//先判断变量先后顺序
	UpdateData(TRUE);
	int a = 0, b = 0;//标记位置
	for (; a < d.length; a++) {
		if (d.DATA[a] == bianliang1)
			break;
	}
	for (; b < d.length; b++) {
		if (d.DATA[b] == bianliang2)
			break;
	}
	if (a > b) {
		int c = a;
		a = b;
		b = c;
	}
	LinkNode<int>*p = d.Locate(a);
	/*for (int i = 0; i < a; i++) {
		p = p->link;
	}*/
	LinkNode<int>*q = d.Locate(b)->link;
	
	Newhead= q->link;
	q->link = p->link;
	LinkNode<int> *current1 = Newhead;
	for (; current1->link != NULL;) {
		current1 = current1->link;
	}
	current1->link = p->link;
	for (int i = 0; i < 100; i++) {//删除表格中元素
		shuchu.DeleteColumn(0);
	}
	for (int i = 0; i < 100; i++) {
		shuchu.InsertColumn(i+1, _T(""), LVCFMT_LEFT, 100);
	}
	shuchu.DeleteColumn(0);
	LinkNode<int>*quit1=d.first->link;
	LinkNode<int>*quit2 = Newhead;
	int i = 0,j=0;
	for (; quit1!= q; i++) {
		CString temp;
		temp.AppendFormat(_T("%d"), quit1->data);
		shuchu.SetItemText(1, i+1, temp);
		quit1 = quit1->link;
	}
	CString temp1;
	temp1.AppendFormat(_T("%d"), q->data);
	shuchu.SetItemText(1, i+1, temp1);
	for (; quit2!= q; j++) {
		CString temp;
		temp.AppendFormat(_T("%d"), quit2->data);
		shuchu.SetItemText(2, j+1, temp);
		quit2 = quit2->link;
	}
	CString temp2;
	temp2.AppendFormat(_T("%d"), q->data);
	shuchu.SetItemText(2, j+1, temp2);
}

LinkNode<int>*m1 = NULL;
	LinkNode<int>*n1 = NULL;
void CDSks1Dlg::OnBnClickedButton3()//原表头查环
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	LinkNode<int>*headyuan = d.first->link;
	
	bool f = IsExitsLoop(headyuan);
	if (f == 0) {
		m = 0;
		n = 0;
	}
	else {
		m = m1->data;
		n = n1->data;
	}
	UpdateData(FALSE);
}


void CDSks1Dlg::OnBnClickedButton4()//新表头查环
{
	// TODO: 在此添加控件通知处理程序代码。
	UpdateData(TRUE);

	bool f = IsExitsLoop(Newhead);
	if (f == 0) {
		m = 0;
		n = 0;
	}
	else {
		m = m1->data;
		n = n1->data;
	}
	UpdateData(FALSE);
}


void CDSks1Dlg::OnBnClickedButton5()//恢复单链表(拆环)
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	LinkNode<int>*current = n1;
	n1->link = NULL;
	if (choice1 == 0) {//原表头
		LinkNode<int>*p = d.first;
		LinkNode<int>*q = d.first;
		for (; q->link!= NULL && q->link->link != NULL;) {
			p = p->link;//慢指针
			q = q->link->link;//快指针
		}
		zhongzhi = p->data;
	}
	if (choice1 == 1) {//新表头
		LinkNode<int>*p = Newhead;
		LinkNode<int>*q = Newhead;
		for (; q->link != NULL && q->link->link != NULL;) {
			p = p->link;//慢指针
			q = q->link->link;//快指针
		}
		zhongzhi = p->data;
	}
	UpdateData(FALSE);
}


void CDSks1Dlg::OnBnClickedButton6()//判断相交
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	LinkNode<int>*p = d.first->link;
	LinkNode<int>*q = Newhead; 
	int i = 1; //记录原来链长度
	int j = 1;//记录新链长度
	for (;; )
	{
		if (p->link != NULL) {
			p = p->link;
			i++;
		}
		else break;
	}
	p = d.first->link;
	for (;; )
	{
		if (q->link != NULL) {
			q = q->link;
			j++;
		}
		else break;
	}
	q = Newhead;
	int difference=abs(i-j);
	if (i > j) {
		for (int a = 0; a < difference; a++) {
			p = p->link;
		}
	}
	else {
		for (int a = 0; a < difference; a++) {
			q = q->link;
		}
	}
	while (p != q) {
		p = p->link;
		q = q->link;
	}
	if (q == NULL) {
		xiangjiao = (_T("不相交"));
	}
	else {
		xiangjiao= (_T("相交"));
		jiaozhi = p->data;
	}
	UpdateData(FALSE);
}


void CDSks1Dlg::OnEnChangeEdit10()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

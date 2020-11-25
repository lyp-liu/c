
// Romania_holidayDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Romania_holiday.h"
#include "Romania_holidayDlg.h"
#include "afxdialogex.h"
#include"Graph.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
Graph gr;//实例化一个新图
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


// CRomaniaholidayDlg 对话框



CRomaniaholidayDlg::CRomaniaholidayDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ROMANIA_HOLIDAY_DIALOG, pParent)
	, method_choice(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRomaniaholidayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, method_choice);
	DDX_Control(pDX, IDC_LIST1, shuchu);
}

BEGIN_MESSAGE_MAP(CRomaniaholidayDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CRomaniaholidayDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CRomaniaholidayDlg 消息处理程序

BOOL CRomaniaholidayDlg::OnInitDialog()
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
	DWORD dwStyle = shuchu.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	shuchu.SetExtendedStyle(dwStyle);
	shuchu.InsertItem(0, _T(""), 0);
	
	shuchu.InsertItem(1, _T(""), 100);
	shuchu.InsertItem(2, _T(""), 100);
	shuchu.InsertItem(3, _T(""), 100);
	shuchu.InsertItem(4, _T(""), 100);
	shuchu.InsertItem(5, _T(""), 100);
	shuchu.InsertItem(6, _T(""), 100);
	shuchu.InsertItem(7, _T(""), 100);
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	for (int i = 1; i < 16; i += 2) {
		shuchu.InsertColumn(i, _T(""), LVCFMT_LEFT, 100);
		shuchu.InsertColumn(i+1, _T(""), LVCFMT_LEFT, 50);
	}
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
	//shuchu.InsertColumn(2, _T(""), LVCFMT_LEFT, 50);
	//shuchu.InsertColumn(3, _T(""), LVCFMT_LEFT, 150);
	//shuchu.InsertColumn(4, _T(""), LVCFMT_LEFT, 150);
	//shuchu.InsertColumn(5, _T(""), LVCFMT_LEFT, 150);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRomaniaholidayDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRomaniaholidayDlg::OnPaint()
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
	else {
		CPaintDC dc(this);
		if (!image.IsNull()) image.Destroy();
		image.Load(_T("picture.bmp"));
		if (!image.IsNull()) image.Draw(dc.m_hDC, 0, 0);
		CDialogEx::OnPaint();

		/*CDC *pDc = this->GetDC();
		
			pNewImage.Draw(pDc->GetSafeHdc(), 0, 0);
		}
		if (!image.IsNull())
		{
			image.Draw(pDc->GetSafeHdc(), 0, 0);
		}
		if (pNewImage != NULL) {
			pNewImage->Draw(pDc->GetSafeHdc(), 0, 0);
		}
		this->ReleaseDC(pDc);*/
	}

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRomaniaholidayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRomaniaholidayDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (method_choice == 1) {
		
		BFS();
		
	}
	else if (method_choice == 2) {
		DFS();
	}
	else if (method_choice == 3) {
		Greedy_Best_First();
	}
	else if (method_choice == 4) {
		AStar();
	}
	else {
		MessageBox(_T("输入错误啦！请输入1到4之间的整数"));
		return;
	}
}


void CRomaniaholidayDlg::BFS()
{
	// TODO: 在此处添加实现代码.
	long long int time_end;
	long long int time_start = clock();
	int count = 0;//记录步数
	int father[20] = { 0 };//用来保存下标节点的父节点
	bool flag[20] = { false };//标志当前节点是否已经访问
	queue<int> q;//建立一个先进先出的队列q
	q.push(0);//Arad的位置0入队
	flag[0] = true;//更新0位置被访问
	int n = 0;
	bool seek = false;
	while (!q.empty()) {//队列非空继续访问
		
		int x = q.front();
		q.pop();
		
		for (int i = 0; i < 20; i++) {
			if (gr.graph[x][i] > 0 && gr.graph[x][i] < 1000 && flag[i] == false) {
				q.push(i);//进队
				count++;
				father[i] = x;//将i的父节点更新为x
				if (i == 1)//如果找到了Bucharest
				seek = true;
				flag[i] = true;//标志位更新为已访问
			}
			
		}
		if (seek) {
			break;
		}
	}
	int distance = 0;//存放耗散（即路径长
	int road[20];
	n = 1;
	int i = 0;
	while (1) {
		distance += gr.graph[n][father[n]];
		road[i] = n;//倒序保存路径
		i++;
		n = father[n];
		if (n == 0) {
			road[i] = 0;
			break;
		}
	}
	time_end = clock();
	for (int i = 0; i < 100; i++) {//删除表格中元素
		shuchu.DeleteColumn(0);
	}
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	shuchu.InsertColumn(1, _T(""), LVCFMT_LEFT, 150);
	for (int j = 2; j < 16; j += 2) {
		shuchu.InsertColumn(j, _T(""), LVCFMT_LEFT, 50);
		shuchu.InsertColumn(j + 1, _T(""), LVCFMT_LEFT, 100);
	}
	//第二行显示路径，第三行显示节点数
	//第四行显示耗散路径总长，第五行显示时间
	shuchu.SetItemText(1, 1, _T("宽度优先："));
	CString temp;
	int ii = 1;
	for (; i > 0; i--) {
		temp=CA2W(gr.city[road[i]].name.c_str());
		shuchu.SetItemText(2, ii, temp);
		
		shuchu.SetItemText(2, ++ii, _T("->"));
		ii++;
	}
	temp = CA2W(gr.city[1].name.c_str());
	shuchu.SetItemText(2, ii, temp);
	temp.Format(_T("%d"), count);
	shuchu.SetItemText(3, 1, _T("访问节点数为："));
	shuchu.SetItemText(3, 2, temp);
	temp.Format(_T("%d"), distance);
	shuchu.SetItemText(4, 1, _T("耗散值为："));
	shuchu.SetItemText(4, 2, temp);
	temp.Format(_T("%d"), time_end-time_start);
	shuchu.SetItemText(5, 1, _T("算法运行时间为："));
	shuchu.SetItemText(5, 2, temp+_T("ms"));
}


void CRomaniaholidayDlg::DFS()
{
	// TODO: 在此处添加实现代码
	long long int time_end;
	long long int time_start = clock();
	bool flag[20] = { false };
	int step[20] = { 0 };
	int dist = 0;//耗散值
	step_num = 0;
	dfs(0, 0, flag,step);
	int step_temp[20] = { 0 };
	int num = 0;

	for (int i = 1; i != 0;num++) {//路径
		step_temp[num] = step[i];
		dist += gr.graph[step[i]][i];
		i = step[i];
		
	}
	
	time_end = clock();

	for (int i = 0; i < 100; i++) {//删除表格中元素
		shuchu.DeleteColumn(0);
	}
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	shuchu.InsertColumn(1, _T(""), LVCFMT_LEFT, 150);
	for (int j = 2; j < 16; j += 2) {
		shuchu.InsertColumn(j, _T(""), LVCFMT_LEFT, 50);
		shuchu.InsertColumn(j + 1, _T(""), LVCFMT_LEFT, 100);
	}
	//第二行显示路径，第三行显示节点数
	//第四行显示耗散路径总长，第五行显示时间
	shuchu.SetItemText(1, 1, _T("深度优先："));
	CString temp;
	int ii = 1;
	
	for (int i=num-1; i>=0; i--) {
		temp = CA2W(gr.city[step_temp[i]].name.c_str());
		shuchu.SetItemText(2, ii, temp);

		shuchu.SetItemText(2, ++ii, _T("->"));
		ii++;
	}
	temp = CA2W(gr.city[1].name.c_str());
	shuchu.SetItemText(2, ii, temp);
	temp.Format(_T("%d"), step_num);
	shuchu.SetItemText(3, 1, _T("访问节点数为："));
	shuchu.SetItemText(3, 2, temp);
	temp.Format(_T("%d"), dist);
	shuchu.SetItemText(4, 1, _T("耗散值为："));
	shuchu.SetItemText(4, 2, temp);
	temp.Format(_T("%d"), time_end - time_start);
	shuchu.SetItemText(5, 1, _T("算法运行时间为："));
	shuchu.SetItemText(5, 2, temp + _T("ms"));
}


int CRomaniaholidayDlg::dfs(int start ,int dist,bool flag[20],int step[20])
{
	// TODO: 在此处添加实现代码.
	
	for (int i = 1; i < 20; i++) {
		if (gr.graph[start][i] < 1000 && gr.graph[start][i]>0 && flag[i] == false&&flag[1]==false) {
			flag[i] = true;//修改标志为已走过
			step[i] = start;
			step_num++;
			dfs(i, dist + gr.graph[start][i], flag, step);
			
		}
		
		if (i == 1&&flag[i]==true) {
				if (min > dist) {
					min = dist + gr.graph[start][i];
					
				}
				break;
		}
	}
	return 0;
}


void CRomaniaholidayDlg::AStar()//A*算法0
{
	// TODO: 在此处添加实现代码.
	long long int time_end;
	long long int time_start = clock();
	int count = 0;//访问节点个数
	bool list[20] = { false };//记录节点是否在openlist中
	vector<City>openlist;
	bool closelist[20] = {false};
	int parent[20];//记录父节点
	list[0] = true;
	memset(parent, -1, sizeof(parent));
	//初始点放入openlist
	openlist.push_back(gr.city[0]);
	sort(openlist.begin(), openlist.end());
	//开始遍历openlist
	while (!openlist.empty()) {
		City current = openlist[0];

		if (current.name == gr.city[1].name)
			break;//是目标节点,结束循环
		openlist.erase(openlist.begin());//取出节点
		count++;
		list[current.num] = false;
		sort(openlist.begin(), openlist.end());//对openList重新排序
		closelist[current.num] = true;//节点加入到closelist
		for (int i = 0; i < 20; i++) {
			if (gr.graph[current.num][i] > 0 && gr.graph[current.num][i] < 1000) {//邻接
				if (closelist[i])//如果在closelist中查下一个点
					continue;
				else if (list[i]) {//已经在openlist中
					//找到这个节点
					int num = 0;
					for (vector<City>::iterator it = openlist.begin(); it != openlist.end(); it++)
					{
						if (it->num == i)
							break;
						num++;
					}
					//如果经过current到达i点更好的话，也就是g值更小，则更新这个节点
					if (current.G + gr.graph[current.num][i] < openlist[num].G) {
						openlist[num].G = current.G + gr.graph[current.num][i];
						openlist[num].F = openlist[num].G + openlist[num].H;
						parent[i] = current.num;
						list[i] = true;
					}
				}
				else {
					//如果这个点既不在openList也不在closeList则创建一个新点，将这个点加入openList
					gr.city[i].G = gr.graph[current.num][i]+gr.city[current.num].G;
					gr.city[i].F = gr.city[i].H + gr.city[i].G;
					parent[i] = current.num;
					openlist.push_back(gr.city[i]);
					sort(openlist.begin(), openlist.end());
				}

			}
		}
	}
	time_end = clock();
	for (int i = 0; i < 100; i++) {//删除表格中元素
		shuchu.DeleteColumn(0);
	}
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	shuchu.InsertColumn(1, _T(""), LVCFMT_LEFT, 150);
	for (int j = 2; j < 16; j += 2) {
		shuchu.InsertColumn(j, _T(""), LVCFMT_LEFT, 50);
		shuchu.InsertColumn(j + 1, _T(""), LVCFMT_LEFT, 120);
	}
	//第二行显示路径，第三行显示节点数
	//第四行显示耗散路径总长，第五行显示时间
	shuchu.SetItemText(1, 1, _T("A*算法："));
	CString temp;
	int ii = 1;
	int distance = 0;
	int step[20];
	int step_num = 0;
	for (int i = 1; i != 0; ) {
		step[step_num] = parent[i];
		distance += gr.graph[i][parent[i]];
		i = parent[i];
		step_num++;

	}
	for (int i = step_num-1; i>=0; i--) {
		
		temp = CA2W(gr.city[step[i]].name.c_str());
		shuchu.SetItemText(2, ii, temp);

		shuchu.SetItemText(2, ++ii, _T("->"));
		
		ii++;
	}
	temp = CA2W(gr.city[1].name.c_str());
	shuchu.SetItemText(2, ii, temp);
	temp.Format(_T("%d"), count);
	shuchu.SetItemText(3, 1, _T("访问节点数为："));
	shuchu.SetItemText(3, 2, temp);
	temp.Format(_T("%d"), distance);
	shuchu.SetItemText(4, 1, _T("耗散值为："));
	shuchu.SetItemText(4, 2, temp);
	temp.Format(_T("%d"), time_end - time_start);
	shuchu.SetItemText(5, 1, _T("算法运行时间为："));
	shuchu.SetItemText(5, 2, temp + _T("ms"));

}


void CRomaniaholidayDlg::Greedy_Best_First()
{
	// TODO: 在此处添加实现代码.
	long long int time_end;
	long long int time_start = clock();
	int count = 0;//记录步数
	int h = 0;//启发函数估计值
	int step[20] = { 0 };//用来保存下标节点
	bool flag[20] = { false };//标志当前节点是否已经访问
	queue<int> q;//建立一个先进先出的队列q
	q.push(0);//Arad的位置0入队
	flag[0] = true;//更新0位置被访问
	int n = 0;//保存一共经过几个城市
	while (!q.empty()) {
		step[n] = q.front();
		q.pop();
		h = gr.city[step[n]].H;
		flag[step[n]] = true;
		if (step[n] == 1) {//判断当前城市是否为最终城市
			
			break;
		}
		
		for (int i = 0; i < 20; i++) {
			
			if (gr.graph[step[n]][i] > 0 && gr.graph[step[n]][i] < 1000 && flag[i] == false) {
				count++;
				if (gr.city[i].H < h) {
					h = gr.city[i].H;
					step[n + 1] = i;
				}
			}
		}
		n++;
		flag[step[n]] = true;

		q.push(step[n]);
		
	}
	int distance = 0;
	for (int i = 0; i < n; i++) {
		distance += gr.graph[step[i]][step[i + 1]];
	}



	time_end = clock();


	for (int i = 0; i < 100; i++) {//删除表格中元素
		shuchu.DeleteColumn(0);
	}
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	shuchu.InsertColumn(1, _T(""), LVCFMT_LEFT, 150);
	for (int j = 2; j < 16; j += 2) {
		shuchu.InsertColumn(j, _T(""), LVCFMT_LEFT, 50);
		shuchu.InsertColumn(j + 1, _T(""), LVCFMT_LEFT, 100);
	}
	//第二行显示路径，第三行显示节点数
	//第四行显示耗散路径总长，第五行显示时间
	shuchu.SetItemText(1, 1, _T("贪婪算法："));
	CString temp;
	int ii = 1;
	for (int i = 0; i < n;i++) {
		temp = CA2W(gr.city[step[i]].name.c_str());
		shuchu.SetItemText(2, ii, temp);

		shuchu.SetItemText(2, ++ii, _T("->"));
		ii++;
	}
	temp = CA2W(gr.city[1].name.c_str());
	shuchu.SetItemText(2, ii, temp);
	temp.Format(_T("%d"), count);
	shuchu.SetItemText(3, 1, _T("访问节点数为："));
	shuchu.SetItemText(3, 2, temp);
	temp.Format(_T("%d"), distance);
	shuchu.SetItemText(4, 1, _T("耗散值为："));
	shuchu.SetItemText(4, 2, temp);
	temp.Format(_T("%d"), time_end - time_start);
	shuchu.SetItemText(5, 1, _T("算法运行时间为："));
	shuchu.SetItemText(5, 2, temp + _T("ms"));
	
}

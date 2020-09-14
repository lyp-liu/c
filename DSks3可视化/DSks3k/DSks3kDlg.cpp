
// DSks3kDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "DSks3k.h"
#include "DSks3kDlg.h"
#include "afxdialogex.h"
#include<bits/stdc++.h>
#include <unordered_map>
const int maxn = 50;
const int maxm = 1e3;
using namespace std;
ifstream read_adj("adj.txt");//读取结点关系文件
ifstream read_dis("distance.txt");//读取距离文件
ofstream outfile("output.txt");//输出结果
string city[maxn];//城市名称
int head[maxn];//构建邻接表
bool init_done = 0;//标记图是否已经初始化
unordered_map<string, int>id;//用来记录某个城市的编号
typedef pair<int, int> p;//放入队列中便于计数
bool city_connect[maxn][maxn];//标记两个城市之间是否有联系
int dist[maxn][maxn];//记录两城市之间的距离
int length[maxn][maxn];//floyd算法中用于更新两城市最短路径长的临时数组
int edge_num;//记录边数
bool vis[maxn];//标记bfs算法结点是否被访问
int shortest_dis[maxn];//最短路径的长度
vector<vector<int>>res;//
struct node {
	int juli;
	int v;//边的一个结点
	int next;//用来遍历当前结点在边的另一面结点

}edge[maxm];//存储边

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


// CDSks3kDlg 对话框



CDSks3kDlg::CDSks3kDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DSKS3K_DIALOG, pParent)
	, raokai(_T(""))
	, zhongdian(_T(""))
	//, qidian(_T(""))
	, qidian(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDSks3kDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	/*DDX_Text(pDX, IDC_EDIT3, raokai);
	DDX_Text(pDX, IDC_EDIT1, qidian);
	DDX_Text(pDX, IDC_EDIT2, zhongdian);*/
	DDX_Text(pDX, IDC_EDIT4, raokai);
	//DDX_Control(pDX, IDC_EDIT5, qidian);
	DDX_Text(pDX, IDC_EDIT6, zhongdian);
	DDX_Control(pDX, IDC_LIST1, shuchu);
	//DDX_Text(pDX, IDC_EDIT5, qidian);
	DDX_Text(pDX, IDC_EDIT7, qidian);
}

BEGIN_MESSAGE_MAP(CDSks3kDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDSks3kDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDSks3kDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDSks3kDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDSks3kDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDSks3kDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CDSks3kDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CDSks3kDlg 消息处理程序

BOOL CDSks3kDlg::OnInitDialog()
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
	for (int i = 1; i < 40; i++) {
		shuchu.InsertItem(i, _T(""), 100);
	}
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	shuchu.InsertColumn(1, _T(""), LVCFMT_LEFT, 100);
	shuchu.InsertColumn(2, _T(""), LVCFMT_LEFT, 150);
	shuchu.InsertColumn(3, _T(""), LVCFMT_LEFT, 150);
	shuchu.InsertColumn(4, _T(""), LVCFMT_LEFT, 150);
	shuchu.InsertColumn(5, _T(""), LVCFMT_LEFT, 150);



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDSks3kDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDSks3kDlg::OnPaint()
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
HCURSOR CDSks3kDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDSks3kDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	Init();
	MessageBox(_T("已经初始化成功"), _T("提示"));

}


void CDSks3kDlg::add(int u,int v,int dis)
{
	// TODO: 在此处添加实现代码.
	edge[edge_num].juli = dis;
	edge[edge_num].v = v;
	edge[edge_num].next = head[u];
	head[u] = edge_num++;
}


void CDSks3kDlg::Init()
{
	// TODO: 在此处添加实现代码.
	if (init_done) {
		MessageBox(_T("您已经初始化过了"), _T("注意"));
		
		return;
	}
	memset(dist, 0x3f, sizeof(dist));
	memset(length, 0x3f, sizeof(length));
	for (int i = 0; i < maxn; i++) {
		dist[i][i] = 0;
		length[i][i] = 0;
	}
	memset(head, -1, sizeof(head));
	for (int i = 1; i <= 31; i++) {//读取第一行
		read_adj >> city[i];
		id[city[i]] = i;//对应的城市名作为下标id数组值是城市编号
	}
	for (int i = 1; i <= 31; i++) {//外层循环遍历2~32行的每一行
		string now_city;//记录当前行的城市名
		read_adj >> now_city;
		int now_id = id[now_city];//记录当前行城市的编号
		for (int j = 1; j <= 31; j++) {//内层循环遍历本行的每个值
			read_adj >> city_connect[now_id][j];
			city_connect[j][now_id] = city_connect[now_id][j];//两城市互相之间的联系情况相同
		}
	}
	string fw;
	for (int i = 1; i <= 30; i++) {
		read_dis >> fw;//第一行已经没用了，直接读取后不再使用
		//cout << fw<<'\t';
	}
	for (int i = 1; i <= 31; i++) {
		string now_city;
		read_dis >> now_city;
		int now_id = id[now_city];
		for (int j = 1; j <= i - 1; j++) {//读取的是上三角型数组
			int w;
			read_dis >> w;
			if (!city_connect[now_id][j])continue;
				//如果两城市没联系则进行下一个遍历
				
			dist[now_id][j] = dist[j][now_id] = w;
			length[now_id][j] = length[j][now_id] = w;
			add(now_id, j, w);
			add(j, now_id, w);
		}
	}
}


void CDSks3kDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	bool yon = 1;
	int tmp[maxn] = { -1 };
	{
		for (int i = 0; i < 100; i++) {//删除表格中元素
			shuchu.DeleteColumn(0);
		}

		shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
		shuchu.InsertColumn(1, _T(""), LVCFMT_LEFT, 100);
		shuchu.InsertColumn(2, _T(""), LVCFMT_LEFT, 150);
		shuchu.InsertColumn(3, _T(""), LVCFMT_LEFT, 150);
		shuchu.InsertColumn(4, _T(""), LVCFMT_LEFT, 150);
		shuchu.InsertColumn(5, _T(""), LVCFMT_LEFT, 150); 
	}
	int ii = 1;
	for (int i = 1; i <= 31; i++) {
		
		if (city[i] != "武汉"&&city[i] != "海口") {
			tmp[i] = bfs(i, id["武汉"]);
			CString temp_1,temp_2;
			temp_1=CA2W(city[i].c_str());
			temp_2.Format(_T("%d"), tmp[i]);

			shuchu.SetItemText(ii, 1, temp_1);
			shuchu.SetItemText(ii, 2, _T("到武汉至少中转"));
			shuchu.SetItemText(ii, 3, temp_2);
			shuchu.SetItemText(ii, 4, _T("次"));
			ii++;
			
		}
	}
	for (int i = 1; i < 31; i++) {
		if (tmp[i] > 2) {
			yon = 0;
			break;
		}
	}
	if (!yon)
		MessageBox(_T("各省会城市到武汉的周转次数不超过2个省不成立"), _T("Result"));
		
	else
		MessageBox(_T("各省会城市到武汉的周转次数不超过2个省成立"), _T("Result"));
}


int CDSks3kDlg::bfs(int qidian_city,int zhongdian_city)
{//广度优先求qidian到武汉的中转次数
	// TODO: 在此处添加实现代码.

	memset(vis, false, sizeof(vis));//先全标记为0
	vis[qidian_city] = true;//先把起点标记为已读
	queue<p>q;

	q.push(p(qidian_city, 0));

	while (!q.empty())
	{
		int u = q.front().first, s = q.front().second;
		if (u == zhongdian_city)
			return s - 1;
		q.pop();//先弹出当前的qidian
		for (int i = head[u]; ~i; i = edge[i].next) {//遍历与u有相邻边的结点
			int vv = edge[i].v;
			if (!vis[vv]) {//若当前结点未被标记
				vis[vv] = true;//标记当前结点为已访问

				q.push(p(vv, s + 1));//推入qidian的相邻结点

			}

		}


	}


	return 1e3;
}

bool cmp(const vector<int>&a, const vector<int>&b)
{
	// TODO: 在此处添加实现代码.
	return a[a.size() - 1] < b[b.size() - 1];
}
void dfs(int city_now, int zhongdian_city, int step, int dis_sum, vector<int>jieguo)
{// dis_num记录当前路径总路程
		//vector数组jieguo保存本路径的所有信息
	if (step > 10)return;//step记录当前走过的步数，超过10自动过滤
	vis[city_now] = true;//把起点标为已访问
	jieguo.push_back(city_now);
	if (city_now == zhongdian_city) {
		jieguo.push_back(dis_sum);
		res.push_back(jieguo);//当前city到达终点后将当前路径信息保存到res
		return;//如果city达到终点本次递归结束返回上次递归调用出
	}
	for (int i = head[city_now]; ~i; i = edge[i].next) {
		int vv = edge[i].v;//city_now的后继结点
		if (vis[vv])continue;
		dfs(vv, zhongdian_city, step + 1, dis_sum + edge[i].juli, jieguo);
		vis[vv] = false;//city_now结点重新标记为未访问以便下个路径访问
	}
}
void CDSks3kDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	res.clear();//把res的size设置为0
	memset(vis, false, sizeof(vis));

	string city_qidian;
	string city_zhongdian;
	city_qidian= CW2A(qidian.GetString());
	city_zhongdian = CW2A(zhongdian.GetString());
	
	if (id.find(city_qidian) == id.end()) {
		MessageBox(_T("输入的起点不存在"), _T("错误"));
		return;
	}
	if (id.find(city_qidian) == id.end()) {
		
		MessageBox(_T("输入的终点不存在"), _T("错误"));

		return;
	}
	int id_qidian = id[city_qidian], id_zhongdian = id[city_zhongdian];
	vector<int>temp;
	dfs(id_qidian, id_zhongdian, 0, 0, temp);
	sort(res.begin(), res.end(), cmp);
	int path_jishu = 0;
	for (int i = 0; i < res.size(); i++) {

		int length = res[i].size();
		vector<int>Iter = res[i];


		outfile << "第" << ++path_jishu << "条路径为：" << endl;
		for (int j = 0; j < length - 2; j++) {
			outfile << "从" << city[Iter[j]] << "到" << city[Iter[j + 1]] << endl;
		}
		outfile << "总路程为" << Iter[length - 1] << endl << endl;
	}
	MessageBox(_T("结果已输出到文件"), _T("提示"));
}





void CDSks3kDlg::Dijkstra(bool flag)
{
	// TODO: 在此处添加实现代码.
	bool S[maxn];//最短路径顶点集
	int pre[maxn];//存放路径
	memset(pre, 0, sizeof(pre));
	memset(S, 0, sizeof(S));
	memset(shortest_dis, 999999, sizeof(shortest_dis));

	string city_qidian;
	string city_zhongdian;
	city_qidian = CW2A(qidian.GetString());
	city_zhongdian = CW2A(zhongdian.GetString());

	
	if (id.find(city_qidian) == id.end() || id.find(city_zhongdian) == id.end())
	{
		
		MessageBox(_T("起点或终点不存在"), _T("错误"));
		return;
	}
	int id_raoguo = 0;//要绕过城市名
	if (flag)
	{
		
		string city_site;
		city_site=CW2A(raokai.GetString());
		if (id.find(city_site) == id.end())
		{
		
			MessageBox(_T("绕过的地点不存在"), _T("错误"));
			return;
		}
		id_raoguo = id[city_site];
	}
	priority_queue<p, vector<p>, greater<p>> q;//升序优先级队列
	int id_qidian = id[city_qidian];
	int id_zhongdian = id[city_zhongdian];
	shortest_dis[id_qidian] = 0;
	q.push(p(shortest_dis[id_qidian], id_qidian));
	while (!q.empty()) {//队列为空则所有最短路径已经得出
		//升序队列会把数值小的放在队头
		int qianqu = q.top().second;
		q.pop();//每次弹出距离已经达到最小的元组不再更新
		if (S[qianqu])continue;//队列头元素的前驱已经被访问所以进行下一个元素的访问
		S[qianqu] = true;
		for (int i = head[qianqu]; ~i; i = edge[i].next) {
			int vv = edge[i].v;//qianqu结点的相邻结点
			int juli = edge[i].juli;//vv和qianqu结点的直线距离
			if (vv != id_raoguo && shortest_dis[vv] > shortest_dis[qianqu] + juli) {
				pre[vv] = qianqu;//如果已保存的起点到vv距离大于。。。和
						//qianqu结点到vv距离之和，把vv的前驱结点设置为qianqu
				shortest_dis[vv] = shortest_dis[qianqu] + juli;//更新vv与起点的距离
				q.push(p(shortest_dis[vv], vv));//当前结点vv入队
			}
		}
	}
	{
		for (int i = 0; i < 100; i++) {//删除表格中元素
			shuchu.DeleteColumn(0);
		}
		shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
		shuchu.InsertColumn(1, _T(""), LVCFMT_LEFT, 100);
		shuchu.InsertColumn(2, _T(""), LVCFMT_LEFT, 150);
		shuchu.InsertColumn(3, _T(""), LVCFMT_LEFT, 150);
		shuchu.InsertColumn(4, _T(""), LVCFMT_LEFT, 150);
		shuchu.InsertColumn(5, _T(""), LVCFMT_LEFT, 150); 
	}
	int ii = 1;
	
	shuchu.SetItemText(ii, 1, qidian);
	shuchu.SetItemText(ii, 2, _T("到"));
	shuchu.SetItemText(ii, 3, zhongdian);
	shuchu.SetItemText(ii, 4, _T("的最短路径为："));
	ii++;
	
	int top = 0;
	int path[31];
	for (int i = id_zhongdian; i != id_qidian; ) {
		//通过从终点出发遍历它的前驱来寻找最短路径
		path[top++] = i;//path的最后一个数据是起点的后一个结点
		i = pre[i];
	}
	for (int i = top - 1, j = id_qidian; i >= 0; i--) {
		CString temp_1, temp_2;
		temp_1 = CA2W(city[j].c_str());
		temp_2 = CA2W(city[path[i]].c_str());
		shuchu.SetItemText(ii, 1, _T("从"));
		shuchu.SetItemText(ii, 2, temp_1);
		shuchu.SetItemText(ii, 3, _T("到"));
		shuchu.SetItemText(ii, 4, temp_2);
		ii++;
		
		j = path[i];
	}
	CString temp;
	temp.Format(_T("%d"), shortest_dis[id_zhongdian]);
	shuchu.SetItemText(ii+1, 1, _T("总路程为:"));
	shuchu.SetItemText(ii+1, 2, temp);

}


void CDSks3kDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Dijkstra(false);
}

void CDSks3kDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Dijkstra(true);
}


void CDSks3kDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Floyd(31);
}


void CDSks3kDlg::Floyd(int n)
{
	// TODO: 在此处添加实现代码.
	int path[32][32];
	memset(path, 0, sizeof(path));
	for (int j = 1; j <= 31;j++) {
		for (int i = 1; i <= 31; i++) {
			path[i][j] = j;//i到j最后中转结点为j
		}
	}
	for (int k = 1; k <= n; k++) {//k为中转结点使i->k->j距离小于i->j
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <n; j++) {
				if (length[i][j] > length[i][k] + length[k][j]) {
					
					length[i][j] = length[i][k] + length[k][j];
					path[i][j] = path[i][k];//更新i到j最后中转结点为~
				}
			}
		}
	}
	
	string city_src;
	string city_des;
	city_src = CW2A(qidian.GetString());
	city_des = CW2A(zhongdian.GetString());
	
	if (id.find(city_src) == id.end() || id.find(city_des) == id.end())
	{
		MessageBox(_T("起点或终点不存在"), _T("错误"));
		return;
	}
	int id_src = id[city_src], id_des = id[city_des];
	int temp[31];
	int top = 0;
	for (int i = path[id_src][id_des]; i != id_des; ) {//向后递推路径
		temp[top++] = i;
		i = path[i][id_des];
	}
	temp[top] = id_des;
	{
		for (int i = 0; i < 100; i++) {//删除表格中元素
			shuchu.DeleteColumn(0);
		}
	
		shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
		shuchu.InsertColumn(1, _T(""), LVCFMT_LEFT, 100);
		shuchu.InsertColumn(2, _T(""), LVCFMT_LEFT, 150);
		shuchu.InsertColumn(3, _T(""), LVCFMT_LEFT, 150);
		shuchu.InsertColumn(4, _T(""), LVCFMT_LEFT, 150);
		shuchu.InsertColumn(5, _T(""), LVCFMT_LEFT, 150); 
	}
	int ii = 1;
	CString temp_1=CA2W(city_src.c_str());
	CString temp_2 = CA2W(city_des.c_str());

	shuchu.SetItemText(ii, 1, temp_1);
	shuchu.SetItemText(ii, 2, _T("到"));
	shuchu.SetItemText(ii, 3, temp_2);
	shuchu.SetItemText(ii, 4, _T("的最短路径为："));
	ii++;
	
	for (int i = 0; i < top; i++) {
		temp_2 = CA2W(city[temp[i]].c_str());
		shuchu.SetItemText(ii, 1, _T("从"));
		shuchu.SetItemText(ii, 2, temp_1);
		shuchu.SetItemText(ii, 3, _T("到"));
		shuchu.SetItemText(ii, 4, temp_2);
		temp_1= CA2W(city[temp[i]].c_str());
		ii++;
	}
	CString temp_3;
	temp_3.Format(_T("%d"), length[id_src][id_des]);
	shuchu.SetItemText(ii, 1, _T("总路程为："));
	shuchu.SetItemText(ii, 2, temp_3);
	
}

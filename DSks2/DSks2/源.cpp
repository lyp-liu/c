#include<iostream>
#include<algorithm>
#include<string>
#include<bits/stdc++.h>
#define maxn 50005
using namespace std;
//把树看作无向图
struct node {
	int to;//i边是射向谁的
	int next;//中间量得到与某边相连的结点
	int w;//i边的长度
}edge[maxn * 2];
struct point {

	int v;//extra[],v表示有足够时间到达首都并去支援其他的剩余时间,fail[].v表示还没被占领的剩余时间
//
	int gra;//extra[].gra记录能达到首都的点经过的直辖市点的编号；
}extra[maxn], fail[maxn];
int cnum = 0;//记录城市间边数
int tot = 0;//直辖市个数
int cap[maxn];//记录直辖市编号
int n = 0;//军队个数
int m=0;//城市个数
int depth[maxn];//存储每个结点的深度
int arm[maxn];//存储有军队的城市，没军队的为0
int gran[maxn];//军队所属直辖市号
int fadep[100][21] = { -1};//存储每个结点的祖先结点深度
bool visited[maxn] = { 0 };//标记结点是否被访问
//深度遍历时用int dep = 1;
//用于存储dfs时其父亲节点的深度;int fat = 0;
int head[maxn * 2];//head[x]表示x相连的边号，再由edge[head[x]].next得出与x相连的结点
int dis[maxn];//存储某城市到首都的距离
int fath[maxn];//标记此结点到首都距离是否已经被设置
int neng;//能到首都的有几个
int weizhanling = 0;//记录能到未占领的个数
int buneng;//暂时不能占领的有几个
int tim[maxn];//标记能不能到
int b[maxn];//标记该直辖市被什么状态占领:0当前无法被占领，1被只能到直辖市的占领，-1被能到首都的军队经过且未占领
//int wu_city[maxn];//存放没有军队的城市 下标从1到m-n为有效
void dfs_math(int);//遍历每个点
void update_extra(int);//更新extra数据
void update_fail(int);//更新fail数据
bool ok(int);//判断当前time能否控制疫情
void enough(int);//判断军队规定时间能不能到首都
bool comp(int);//判断能不能补齐
int ddx(int, int);//从大到小排序
int ddx(int i, int j) {
	return i > j;
}
bool compare(const point &a, const point &b)//比较函数
{
	return a.v > b.v;
}
void add(int u, int v, int w) {//添加边
	cnum++;
	edge[cnum].to = v;
	edge[cnum].next = head[u];
	edge[cnum].w = w;
	head[u] = cnum;
}
void dfs_math(int x)//深度优先遍历各城市并找出其是否已经被覆盖
{
	int maxx = -1;
	int now1 = 0;
	int now2 = 0;
	for (int i = head[x]; i; i = edge[i].next) {
		int vv = edge[i].to;
		if (fath[x] != vv) {
			dfs_math(vv);

		}
	}
}
void update_extra(int time)
{

	for (int i = 1; i <= n; i++) {
		if (dis[arm[i]]<time) {//说明arm[i]能到首都
			extra[++neng].v = time - dis[arm[i]];//到达根节点后的剩余时间
			extra[neng].gra = gran[arm[i]];
			if(b[gran[arm[i]]!=1]){
			b[gran[arm[i]]] = -1;//能到但先不占领
			}
		}
	}
	

	sort(extra + 1, extra + neng+1,compare);
}
void update_fail(int time)//直辖市没军队占领的或所属直辖市子树上没有军队的
{
	//所属直辖市子树没军队：arm[i]为0
	for (int i = 1; i <= tot; i++) {
		if(b[cap[i]]==0||b[cap[i]]==-1){//b[cap[i]]==0表示暂时不能被占领的所有直辖市
			fail[++buneng].v = dis[cap[i]];
		}
	}
	sort(fail + 1, fail + buneng + 1, compare);
}
bool ok(int time) {
	neng = buneng=weizhanling = 0;
	memset(b, 0, sizeof(b));
	memset(tim, -1, sizeof(tim));//tim初值为-1,若能到则仍然为-1
	enough(time);
	update_extra(time);
	update_fail(time);
	return comp(time);
}

void enough(int time)//判断军队规定时间能不能到首都
{
	for (int i = 1; i <= n; i++) {
		if (dis[arm[i]] >= time && (dis[arm[i]] - dis[gran[arm[i]]]) <= time) {
			//军队能到直辖市不能到首都的tim标为0，能到首都的默认标-1
			
			tim[arm[i]] = 0;
		}
		else if ((dis[arm[i]] - dis[gran[arm[i]]]) > time)//军队不能到直辖市的标time
			tim[arm[i]] = time;
	}
	for (int i = 1; i <= n; i++) {
		if (tim[arm[i]] == 0) {//只能到直辖市的先分配占领
			b[gran[arm[i]]] = 1;//标记为已占领
		}
	}
}

bool comp(int time)
{
	if (buneng > neng)
		return false;
	for (int i = 1; i <= buneng; i++) {
		if (extra[i].v < fail[i].v) {
			return false;
		}
	
	}
	return true;
}



int erfen() {
	int l = -1, r = 999999;
	while (l + 1 < r) {
		int mid = (l + r) / 2;
		if (ok(mid))r = mid;
		else l = mid;
	}
	return r;
}
void dfs_record(int root,int dep,int fat) {//深度优先遍历记录祖先结点关系
	if (visited[root])return;
	visited[root] = true;
	depth[root] = dep;
	fadep[root][0] = fat;//由于初始fat为0，所以根节点的祖先深度为0，其他结点某个祖先如果不存在深度则为-1；
	
	for (int i = head[root]; i; i = edge[i].next) {
		int vv = edge[i].to;//root的下一个子女结点
		if (fath[root]!=vv) {
			if (root == 1) {
				dis[root] = 0;
				dis[vv] = edge[i].w;
				gran[vv] = vv;
			}
			else {
				dis[vv] = edge[i].w + dis[root];
				gran[vv] = root;
			}
			fath[vv] = root;
		}
		dfs_record(vv,dep+1,dep);
	}
}
int main() {
	
	cout << "请输入城市个数" << endl;
	cin >> m;
	cout << "请输入两城市编号和距离（中间空格隔开）" << endl;
	for (int i = 1; i < m; i++) {//一共m-1组数据
		int u, v, w;
		cin >> u >> v >> w;
		add(u, v, w);
		add(v, u, w);
		if (u == 1 ) {//记录直辖市编号
			cap[++tot] = v;
		}
		if (v == 1) {
			cap[++tot] = u;
		}
	}
	/*for (int i = 1; i <= m; i++) {
		wu_city[i] = i;
	}*/
	cout << "请输入军队个数" << endl;
	
	cin >> n;
	if (tot > n) {
		cout << "-1" << endl;
		system("pause");
		return 0;
	}
	cout << "请输入军队所在城市编号" << endl;
	for (int i = 1; i <= n; i++) {
		cin >> arm[i];
		/*for (int j = 1; j <= m; j++) {
			if (arm[i] == wu_city[j]) {
				wu_city[j] = 0;
			}
		}*/
	}
	/*sort(wu_city + 1, wu_city + m + 1, ddx);*/
	sort(arm + 1, arm + 1 + n);//有军队的城市编号越小越靠前

	memset(depth, 0, sizeof(depth));
	dfs_record(1,1,0);
	for (int j = 1; j <= 20; j++) {
		for (int i = 1; i <= m; i++) {
			fadep[i][j] = fadep[fadep[i][j - 1]][j - 1];
			
		}
	}
	/*for (int i = 1; i <=m; i++) {
		cout << gran[i] << endl;
	}*/
	cout << erfen();


	system("pause");
	return 0;
}
#pragma once
#include<iostream>
#include<algorithm>
#include<string>
#define maxn 50005
using namespace std;
//把树看作有向图
struct node{
	int to;//i边是射向谁的
	int next;//i边是从谁发出的
	int w;//i边的长度
}edge[maxn*2];
struct point {

	int v;//extra[],v表示有足够时间到达首都并去支援其他的剩余时间,fail[].v表示还没被占领的剩余时间
//
	int gra;//extra[].gra表示
}extra[maxn],fail[maxn];
int cnum = 0;//记录城市间边数
int tot=0;//直辖市个数
int depth[maxn];//存储每个结点的深度
int fadep[100][21] = {0};//存储每个结点的祖先结点深度
bool visited[maxn] = { 0 };//标记结点是否被访问
int dep = 1;//深度遍历时用
int fat = 0;//用于存储dfs时其父亲节点的深度;
void add(int u, int v, int w) {//添加边
	cnum++;
	edge[cnum].to = u;
	edge[cnum].next = v;
	edge[cnum].w = w;
}
void dfs_record(int root) {//深度优先遍历记录祖先结点关系
	if (visited[root])return;
	visited[root] = true;
	depth[root] = dep;
	fadep[root][0] = fat;
	for()
}
int main() {
	int m;
	cout << "请输入城市个数"<<endl;
	cin >> m;
	cout << "请输入两城市编号和距离（中间空格隔开）" << endl;
	for (int i = 1; i < m; i++) {//一共m-1组数据
		int u, v, w;
		cin >> u >> v >> w;
		add(u, v, w);
		add(v, u, w);
		if (u == 1 || v == 1) {//记录直辖市个数
			tot++;
		}
	}
	cout << "请输入军队个数" << endl;
	int n;
	cin >> n;
	if (tot > n) {
		cout << "-1"<<endl;
		system("pause");
		return 0;
	}
	memset(depth, 0, sizeof(depth));
	dfs_record(1);




	return 0;
}
#pragma once
#include<iostream>
#include<algorithm>
#include<string>
#define maxn 50005
using namespace std;
//������������ͼ
struct node{
	int to;//i��������˭��
	int next;//i���Ǵ�˭������
	int w;//i�ߵĳ���
}edge[maxn*2];
struct point {

	int v;//extra[],v��ʾ���㹻ʱ�䵽���׶���ȥ֧Ԯ������ʣ��ʱ��,fail[].v��ʾ��û��ռ���ʣ��ʱ��
//
	int gra;//extra[].gra��ʾ
}extra[maxn],fail[maxn];
int cnum = 0;//��¼���м����
int tot=0;//ֱϽ�и���
int depth[maxn];//�洢ÿ���������
int fadep[100][21] = {0};//�洢ÿ���������Ƚ�����
bool visited[maxn] = { 0 };//��ǽ���Ƿ񱻷���
int dep = 1;//��ȱ���ʱ��
int fat = 0;//���ڴ洢dfsʱ�丸�׽ڵ�����;
void add(int u, int v, int w) {//��ӱ�
	cnum++;
	edge[cnum].to = u;
	edge[cnum].next = v;
	edge[cnum].w = w;
}
void dfs_record(int root) {//������ȱ�����¼���Ƚ���ϵ
	if (visited[root])return;
	visited[root] = true;
	depth[root] = dep;
	fadep[root][0] = fat;
	for()
}
int main() {
	int m;
	cout << "��������и���"<<endl;
	cin >> m;
	cout << "�����������б�ź;��루�м�ո������" << endl;
	for (int i = 1; i < m; i++) {//һ��m-1������
		int u, v, w;
		cin >> u >> v >> w;
		add(u, v, w);
		add(v, u, w);
		if (u == 1 || v == 1) {//��¼ֱϽ�и���
			tot++;
		}
	}
	cout << "��������Ӹ���" << endl;
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
#include<iostream>
#include<algorithm>
#include<string>
#include<bits/stdc++.h>
#define maxn 50005
using namespace std;
//������������ͼ
struct node {
	int to;//i��������˭��
	int next;//�м����õ���ĳ�������Ľ��
	int w;//i�ߵĳ���
}edge[maxn * 2];
struct point {

	int v;//extra[],v��ʾ���㹻ʱ�䵽���׶���ȥ֧Ԯ������ʣ��ʱ��,fail[].v��ʾ��û��ռ���ʣ��ʱ��
//
	int gra;//extra[].gra��¼�ܴﵽ�׶��ĵ㾭����ֱϽ�е�ı�ţ�
}extra[maxn], fail[maxn];
int cnum = 0;//��¼���м����
int tot = 0;//ֱϽ�и���
int cap[maxn];//��¼ֱϽ�б��
int n = 0;//���Ӹ���
int m=0;//���и���
int depth[maxn];//�洢ÿ���������
int arm[maxn];//�洢�о��ӵĳ��У�û���ӵ�Ϊ0
int gran[maxn];//��������ֱϽ�к�
int fadep[100][21] = { -1};//�洢ÿ���������Ƚ�����
bool visited[maxn] = { 0 };//��ǽ���Ƿ񱻷���
//��ȱ���ʱ��int dep = 1;
//���ڴ洢dfsʱ�丸�׽ڵ�����;int fat = 0;
int head[maxn * 2];//head[x]��ʾx�����ıߺţ�����edge[head[x]].next�ó���x�����Ľ��
int dis[maxn];//�洢ĳ���е��׶��ľ���
int fath[maxn];//��Ǵ˽�㵽�׶������Ƿ��Ѿ�������
int neng;//�ܵ��׶����м���
int weizhanling = 0;//��¼�ܵ�δռ��ĸ���
int buneng;//��ʱ����ռ����м���
int tim[maxn];//����ܲ��ܵ�
int b[maxn];//��Ǹ�ֱϽ�б�ʲô״̬ռ��:0��ǰ�޷���ռ�죬1��ֻ�ܵ�ֱϽ�е�ռ�죬-1���ܵ��׶��ľ��Ӿ�����δռ��
//int wu_city[maxn];//���û�о��ӵĳ��� �±��1��m-nΪ��Ч
void dfs_math(int);//����ÿ����
void update_extra(int);//����extra����
void update_fail(int);//����fail����
bool ok(int);//�жϵ�ǰtime�ܷ��������
void enough(int);//�жϾ��ӹ涨ʱ���ܲ��ܵ��׶�
bool comp(int);//�ж��ܲ��ܲ���
int ddx(int, int);//�Ӵ�С����
int ddx(int i, int j) {
	return i > j;
}
bool compare(const point &a, const point &b)//�ȽϺ���
{
	return a.v > b.v;
}
void add(int u, int v, int w) {//��ӱ�
	cnum++;
	edge[cnum].to = v;
	edge[cnum].next = head[u];
	edge[cnum].w = w;
	head[u] = cnum;
}
void dfs_math(int x)//������ȱ��������в��ҳ����Ƿ��Ѿ�������
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
		if (dis[arm[i]]<time) {//˵��arm[i]�ܵ��׶�
			extra[++neng].v = time - dis[arm[i]];//������ڵ���ʣ��ʱ��
			extra[neng].gra = gran[arm[i]];
			if(b[gran[arm[i]]!=1]){
			b[gran[arm[i]]] = -1;//�ܵ����Ȳ�ռ��
			}
		}
	}
	

	sort(extra + 1, extra + neng+1,compare);
}
void update_fail(int time)//ֱϽ��û����ռ��Ļ�����ֱϽ��������û�о��ӵ�
{
	//����ֱϽ������û���ӣ�arm[i]Ϊ0
	for (int i = 1; i <= tot; i++) {
		if(b[cap[i]]==0||b[cap[i]]==-1){//b[cap[i]]==0��ʾ��ʱ���ܱ�ռ�������ֱϽ��
			fail[++buneng].v = dis[cap[i]];
		}
	}
	sort(fail + 1, fail + buneng + 1, compare);
}
bool ok(int time) {
	neng = buneng=weizhanling = 0;
	memset(b, 0, sizeof(b));
	memset(tim, -1, sizeof(tim));//tim��ֵΪ-1,���ܵ�����ȻΪ-1
	enough(time);
	update_extra(time);
	update_fail(time);
	return comp(time);
}

void enough(int time)//�жϾ��ӹ涨ʱ���ܲ��ܵ��׶�
{
	for (int i = 1; i <= n; i++) {
		if (dis[arm[i]] >= time && (dis[arm[i]] - dis[gran[arm[i]]]) <= time) {
			//�����ܵ�ֱϽ�в��ܵ��׶���tim��Ϊ0���ܵ��׶���Ĭ�ϱ�-1
			
			tim[arm[i]] = 0;
		}
		else if ((dis[arm[i]] - dis[gran[arm[i]]]) > time)//���Ӳ��ܵ�ֱϽ�еı�time
			tim[arm[i]] = time;
	}
	for (int i = 1; i <= n; i++) {
		if (tim[arm[i]] == 0) {//ֻ�ܵ�ֱϽ�е��ȷ���ռ��
			b[gran[arm[i]]] = 1;//���Ϊ��ռ��
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
void dfs_record(int root,int dep,int fat) {//������ȱ�����¼���Ƚ���ϵ
	if (visited[root])return;
	visited[root] = true;
	depth[root] = dep;
	fadep[root][0] = fat;//���ڳ�ʼfatΪ0�����Ը��ڵ���������Ϊ0���������ĳ��������������������Ϊ-1��
	
	for (int i = head[root]; i; i = edge[i].next) {
		int vv = edge[i].to;//root����һ����Ů���
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
	
	cout << "��������и���" << endl;
	cin >> m;
	cout << "�����������б�ź;��루�м�ո������" << endl;
	for (int i = 1; i < m; i++) {//һ��m-1������
		int u, v, w;
		cin >> u >> v >> w;
		add(u, v, w);
		add(v, u, w);
		if (u == 1 ) {//��¼ֱϽ�б��
			cap[++tot] = v;
		}
		if (v == 1) {
			cap[++tot] = u;
		}
	}
	/*for (int i = 1; i <= m; i++) {
		wu_city[i] = i;
	}*/
	cout << "��������Ӹ���" << endl;
	
	cin >> n;
	if (tot > n) {
		cout << "-1" << endl;
		system("pause");
		return 0;
	}
	cout << "������������ڳ��б��" << endl;
	for (int i = 1; i <= n; i++) {
		cin >> arm[i];
		/*for (int j = 1; j <= m; j++) {
			if (arm[i] == wu_city[j]) {
				wu_city[j] = 0;
			}
		}*/
	}
	/*sort(wu_city + 1, wu_city + m + 1, ddx);*/
	sort(arm + 1, arm + 1 + n);//�о��ӵĳ��б��ԽСԽ��ǰ

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
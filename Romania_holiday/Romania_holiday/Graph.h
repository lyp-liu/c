#pragma once
#include<bits/stdc++.h>
using namespace std;

struct City {
	int num;//���б��
	string name;
	int H;//������������
	int G=0;//�Ѿ�����·����
	int F=G+H;//��hΪ����ֵ������·��ֵ֮��
	bool operator<(const City&a)const {
		return F < a.F;
	}
};
class Graph
{
public:
	Graph();
	~Graph();
	City city[20];
	int graph[20][20];
};


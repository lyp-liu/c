#pragma once
#include<bits/stdc++.h>
using namespace std;

struct City {
	int num;//城市编号
	string name;
	int H;//保存启发函数
	int G=0;//已经过的路径长
	int F=G+H;//设h为启发值与已有路径值之和
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


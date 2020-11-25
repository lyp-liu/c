#include "stdafx.h"
#include "Graph.h"
#include<fstream>
#include<iostream>
#include<bits/stdc++.h>

using namespace std;
//int gra[20][20];//存放图的邻接矩阵
const int Func[20] = {366,0,160,242,161,176,77,151,226,244,241,234,380,100,193,253,329,80,199,374};//存放启发信息
string cities[20];//对城市编号分别对应0~19
Graph::Graph()//初始化图
{
	ifstream read_info("maps.txt");
	for (int i = 0; i < 20; i++) {//读取txt中第一行城市名
		read_info >> cities[i];
		city[i].name = cities[i];
		city[i].H = Func[i];
		city[i].num = i;
		//city[i].F = city[i].H + city[i].G;
	}
	string fw_str;
	for (int i = 0; i < 20; i++) {
		read_info >> fw_str;
		for (int j = 0; j < 20; j++) {
			read_info>>graph[i][j];
		}
	}

}


Graph::~Graph()
{
}

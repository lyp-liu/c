#include "stdafx.h"
#include "Graph.h"
#include<fstream>
#include<iostream>
#include<bits/stdc++.h>

using namespace std;
//int gra[20][20];//���ͼ���ڽӾ���
const int Func[20] = {366,0,160,242,161,176,77,151,226,244,241,234,380,100,193,253,329,80,199,374};//���������Ϣ
string cities[20];//�Գ��б�ŷֱ��Ӧ0~19
Graph::Graph()//��ʼ��ͼ
{
	ifstream read_info("maps.txt");
	for (int i = 0; i < 20; i++) {//��ȡtxt�е�һ�г�����
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

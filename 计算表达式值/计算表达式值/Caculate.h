#pragma once
#include<iostream>
#include<vector>
using namespace std;
//定义运算符优先级
constexpr auto ADD = 1;  //加
constexpr auto SUB = 1;  //减
constexpr auto MUL = 2;  //乘
constexpr auto DIV = 2;  //除
//constexpr auto Demo = 2; //求模取余

class Caculate {
public:
	bool is_Input = false;  //是否输入了表达式，默认false
	void show_Menu();  //展示菜单
	int get_Value(string operation);  //获取运算符优先级
	float result(float a, string str, float b);  //计算结果，a、b分别表示操作数1、2，str表示操作运算符
	void input_Infix();  //输入中缀表达式
	vector<string> infix_Expression;  //存储中缀表达式
	void caculate();
	//void show_Vector(vector<string>expression);
	void exit_System();  //退出系统

};
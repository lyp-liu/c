#pragma once
#include<iostream>
#include<vector>
using namespace std;
//������������ȼ�
constexpr auto ADD = 1;  //��
constexpr auto SUB = 1;  //��
constexpr auto MUL = 2;  //��
constexpr auto DIV = 2;  //��
//constexpr auto Demo = 2; //��ģȡ��

class Caculate {
public:
	bool is_Input = false;  //�Ƿ������˱��ʽ��Ĭ��false
	void show_Menu();  //չʾ�˵�
	int get_Value(string operation);  //��ȡ��������ȼ�
	float result(float a, string str, float b);  //��������a��b�ֱ��ʾ������1��2��str��ʾ���������
	void input_Infix();  //������׺���ʽ
	vector<string> infix_Expression;  //�洢��׺���ʽ
	void caculate();
	//void show_Vector(vector<string>expression);
	void exit_System();  //�˳�ϵͳ

};
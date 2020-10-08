#include<iostream>
#include<stack>
#include<string>
#include<stack>
#include<sstream>
#include<algorithm>
#include<math.h>
#include "Caculate.h"

using namespace std;




void Caculate::exit_System() {
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);    //退出系统
}


void Caculate::show_Menu() {   //展示菜单
	cout << endl;
	cout << "***********************************************" << endl;
	cout << "*************** 表达式求值计算器 ***************" << endl;
	cout << "***********************************************" << endl;
	cout << "*********** >1. 输入中缀表达式 ******************" << endl;
	cout << "*********** >2. 中缀表达式求值  ********************" << endl;
	cout << "************>3. 退出系统  ********************************" << endl;
	cout << "***********************************************" << endl;
	cout << "***********************************************" << endl;
	cout << endl;
}
int main() {
	Caculate ca;
	while (1) {
		ca.show_Menu();
		int choice = 0;
		cin >> choice;
		if (choice == 1) {
			ca.input_Infix();
			continue;
		}
		if (choice == 2) {
			ca.caculate();
			continue;
		}
		else {
			ca.exit_System();
			break;

		}
	}
	return 0;
}

int Caculate::get_Value(string operation) {  //获取元素优先级
	int value = 0;
	if (operation == "+") {
		value = ADD;
	}
	else if (operation == "-") {
		value = SUB;
	}
	else if (operation == "*") {
		value = MUL;
	}
	else if (operation == "/") {
		value = DIV;
	}
	/*else if (operation == "%") {
		value = Demo;
	}*/
	else {
		value = 0;
	}
	return value;
}

float Caculate::result(float a, string str, float b) {     //计算简单表达式
	float result = 0;
	if (str == "+") {
		result = a + b;
	}
	else if (str == "-") {
		result = a - b;
	}
	else if (str == "*") {
		result = a * b;
	}
	else if (str == "/") {
		result = a / b;
	}
	/*else if (str == "%") {
		result = a % b;
	}*/
	else {
		result = 0;
	}
	return result;
}



void Caculate::input_Infix() {           //输入中缀表达式
	this->infix_Expression.clear();		//清空容器，方便接收用户接下来的输入
	system("cls");

	cout << "请输入你想要计算的中缀表达式：" << endl;
	char cha[50];			//用来接收将要输入的表达式, 最多接收50个字符	
	cin.ignore();			//cin.getline默认以换行符为结束标志,要消耗掉前面的换行符需要多调用一次即使用两次cin.getline()									
	cin.getline(cha, 50);	//或者这之前使用cin.ignore();

	string str = string(cha);				//将字符数组强转成字符串
	int len = (int)str.length();		//表达式长度
	int i = 0;

	do {
		if (str[i] == '=' || str[i] == ' ') {			//当为空格或者‘=’ 的时候，就直接跳过
			i++;
		}
		else if (str[i] < 48 || str[i] > 57) {				//当ascii码不在0-9之间，就直接保存
			string temp = "";
			temp += str[i];
			this->infix_Expression.push_back(temp);
			i++;
		}
		else {
			string str_temp = "";
			while (i < len && str[i] >= 48 && str[i] <= 57) {	//当在0-9之间就拼接成原来的数字，然后再保存
				str_temp += str[i];
				i++;
			}
			this->infix_Expression.push_back(str_temp);
		}
	}

	while (i < len);
	this->is_Input = true;

	cout << "===========================" << endl;
	cout << "表达式输入成功！:)" << endl;
	cout << endl;

	system("pause");
	system("cls");
}


void Caculate::caculate() {        //中缀表达式求值
	  //定义两个栈，一个，一个
	stack<string> POTR;          //运算符栈
	stack<double> OPND;			//操作数栈
	vector<string>::iterator temp;//
	for (vector<string>::iterator it = this->infix_Expression.begin(); it != this->infix_Expression.end(); it++) {
		temp = it;//
		
		string str = *it;
		string tempstr = *temp;//
		stringstream ss;

		float num = 0;
		if (str[0] >= '0' && str[0] <= '9') {	//如果第一个字符为数字字符，则这个字符串是数字，用istringsteam 转成数字
			bool f = (temp != this->infix_Expression.end()-1);
			if (f==1) {
				if (*++temp == ".") {//
					str += *temp;
					temp++;
					str += *temp;

					istringstream istr(str);			//这样就可以实现多位整数的运算
					istr >> num;
					OPND.push(num);
					it++;
					it++;
					continue;
				}
				
			}
			
			istringstream istr(str);			//这样就可以实现多位整数的运算
			istr >> num;
			OPND.push(num);
			
			
		}

		else if (str == "(") {				//如果遇到左括号，就压进运算符栈
			//当前it在(处
			if (*++temp == "-") {
				string t1 = *temp;
				temp++;//temp在小数点前的数
				t1 += *temp;
				temp++;//temp为小数点
				it++;//it在-处
				if (*temp == ".") {
					t1 += *temp;
					temp++;
					t1 += *temp;
					it++;//有小数点时在小数点前数字
					it++;//指向小数点
				}
				it++;//如果括号内非小数则it在数字处
				//如果括号内有小数则在小数点右侧数字
				it++;//跳过右括号
				istringstream istr(t1);			//这样就可以实现多位整数的运算
				istr >> num;
				OPND.push(num);
				continue;
			}
			POTR.push(str);
		}
		else if (str == ")") {							//如果遇到右括号，就去匹配运算符栈中的左括号，当不匹配的时候，操作数栈弹出两个操作数，
			while (POTR.top() != "(") {		//和当前运算符栈的栈顶运算符进行运算，最后将结果保存到操作数栈
				float a = OPND.top();
				OPND.pop();
				float b = OPND.top();
				OPND.pop();
				float result = this->result(b, POTR.top(), a);
				OPND.push(result);
				POTR.pop();
			}
			POTR.pop();		//弹出"("
		}
		else {
			if (POTR.size() == 0 || POTR.top() == "(") {
				POTR.push(str);
			}
			else {
				while (POTR.size() != 0 && get_Value(POTR.top()) >= get_Value(str)) {
					float a = OPND.top();				//当当前运算符优先级小于等于栈顶元素优先级时，就从操作数栈弹出两个操作数
					OPND.pop();						//和栈顶运算符参与运算，将结果保存到操作数栈中
					float b = OPND.top();
					OPND.pop();
					float result = this->result(b, POTR.top(), a);
					OPND.push(result);
					POTR.pop();
				}
				POTR.push(str);					//之后将当前运算符压如运算符栈
			}
		}
	}

	while (POTR.size() != 0) {					//最后当运算符栈不为空的时候，再依次弹出运算
		float a = OPND.top();
		OPND.pop();
		float b = OPND.top();
		OPND.pop();
		float result = this->result(b, POTR.top(), a);
		OPND.push(result);
		POTR.pop();
	}

	cout << "运算结果为：" << OPND.top() << endl;
	OPND.pop();

	system("pause");
	system("cls");
}


/*void Caculate::show_Vector(vector<string> expression) {    //遍历展示vector容器中元素

	for (vector<string>::iterator it = expression.begin(); it != expression.end(); it++) {
		cout << (string)(*it) << " ";
	}
	cout << endl;
}*/


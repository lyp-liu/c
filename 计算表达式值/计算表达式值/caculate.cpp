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
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);    //�˳�ϵͳ
}


void Caculate::show_Menu() {   //չʾ�˵�
	cout << endl;
	cout << "***********************************************" << endl;
	cout << "*************** ���ʽ��ֵ������ ***************" << endl;
	cout << "***********************************************" << endl;
	cout << "*********** >1. ������׺���ʽ ******************" << endl;
	cout << "*********** >2. ��׺���ʽ��ֵ  ********************" << endl;
	cout << "************>3. �˳�ϵͳ  ********************************" << endl;
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

int Caculate::get_Value(string operation) {  //��ȡԪ�����ȼ�
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

float Caculate::result(float a, string str, float b) {     //����򵥱��ʽ
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



void Caculate::input_Infix() {           //������׺���ʽ
	this->infix_Expression.clear();		//�����������������û�������������
	system("cls");

	cout << "����������Ҫ�������׺���ʽ��" << endl;
	char cha[50];			//�������ս�Ҫ����ı��ʽ, ������50���ַ�	
	cin.ignore();			//cin.getlineĬ���Ի��з�Ϊ������־,Ҫ���ĵ�ǰ��Ļ��з���Ҫ�����һ�μ�ʹ������cin.getline()									
	cin.getline(cha, 50);	//������֮ǰʹ��cin.ignore();

	string str = string(cha);				//���ַ�����ǿת���ַ���
	int len = (int)str.length();		//���ʽ����
	int i = 0;

	do {
		if (str[i] == '=' || str[i] == ' ') {			//��Ϊ�ո���ߡ�=�� ��ʱ�򣬾�ֱ������
			i++;
		}
		else if (str[i] < 48 || str[i] > 57) {				//��ascii�벻��0-9֮�䣬��ֱ�ӱ���
			string temp = "";
			temp += str[i];
			this->infix_Expression.push_back(temp);
			i++;
		}
		else {
			string str_temp = "";
			while (i < len && str[i] >= 48 && str[i] <= 57) {	//����0-9֮���ƴ�ӳ�ԭ�������֣�Ȼ���ٱ���
				str_temp += str[i];
				i++;
			}
			this->infix_Expression.push_back(str_temp);
		}
	}

	while (i < len);
	this->is_Input = true;

	cout << "===========================" << endl;
	cout << "���ʽ����ɹ���:)" << endl;
	cout << endl;

	system("pause");
	system("cls");
}


void Caculate::caculate() {        //��׺���ʽ��ֵ
	  //��������ջ��һ����һ��
	stack<string> POTR;          //�����ջ
	stack<double> OPND;			//������ջ
	vector<string>::iterator temp;//
	for (vector<string>::iterator it = this->infix_Expression.begin(); it != this->infix_Expression.end(); it++) {
		temp = it;//
		
		string str = *it;
		string tempstr = *temp;//
		stringstream ss;

		float num = 0;
		if (str[0] >= '0' && str[0] <= '9') {	//�����һ���ַ�Ϊ�����ַ���������ַ��������֣���istringsteam ת������
			bool f = (temp != this->infix_Expression.end()-1);
			if (f==1) {
				if (*++temp == ".") {//
					str += *temp;
					temp++;
					str += *temp;

					istringstream istr(str);			//�����Ϳ���ʵ�ֶ�λ����������
					istr >> num;
					OPND.push(num);
					it++;
					it++;
					continue;
				}
				
			}
			
			istringstream istr(str);			//�����Ϳ���ʵ�ֶ�λ����������
			istr >> num;
			OPND.push(num);
			
			
		}

		else if (str == "(") {				//������������ţ���ѹ�������ջ
			//��ǰit��(��
			if (*++temp == "-") {
				string t1 = *temp;
				temp++;//temp��С����ǰ����
				t1 += *temp;
				temp++;//tempΪС����
				it++;//it��-��
				if (*temp == ".") {
					t1 += *temp;
					temp++;
					t1 += *temp;
					it++;//��С����ʱ��С����ǰ����
					it++;//ָ��С����
				}
				it++;//��������ڷ�С����it�����ִ�
				//�����������С������С�����Ҳ�����
				it++;//����������
				istringstream istr(t1);			//�����Ϳ���ʵ�ֶ�λ����������
				istr >> num;
				OPND.push(num);
				continue;
			}
			POTR.push(str);
		}
		else if (str == ")") {							//������������ţ���ȥƥ�������ջ�е������ţ�����ƥ���ʱ�򣬲�����ջ����������������
			while (POTR.top() != "(") {		//�͵�ǰ�����ջ��ջ��������������㣬��󽫽�����浽������ջ
				float a = OPND.top();
				OPND.pop();
				float b = OPND.top();
				OPND.pop();
				float result = this->result(b, POTR.top(), a);
				OPND.push(result);
				POTR.pop();
			}
			POTR.pop();		//����"("
		}
		else {
			if (POTR.size() == 0 || POTR.top() == "(") {
				POTR.push(str);
			}
			else {
				while (POTR.size() != 0 && get_Value(POTR.top()) >= get_Value(str)) {
					float a = OPND.top();				//����ǰ��������ȼ�С�ڵ���ջ��Ԫ�����ȼ�ʱ���ʹӲ�����ջ��������������
					OPND.pop();						//��ջ��������������㣬��������浽������ջ��
					float b = OPND.top();
					OPND.pop();
					float result = this->result(b, POTR.top(), a);
					OPND.push(result);
					POTR.pop();
				}
				POTR.push(str);					//֮�󽫵�ǰ�����ѹ�������ջ
			}
		}
	}

	while (POTR.size() != 0) {					//��������ջ��Ϊ�յ�ʱ�������ε�������
		float a = OPND.top();
		OPND.pop();
		float b = OPND.top();
		OPND.pop();
		float result = this->result(b, POTR.top(), a);
		OPND.push(result);
		POTR.pop();
	}

	cout << "������Ϊ��" << OPND.top() << endl;
	OPND.pop();

	system("pause");
	system("cls");
}


/*void Caculate::show_Vector(vector<string> expression) {    //����չʾvector������Ԫ��

	for (vector<string>::iterator it = expression.begin(); it != expression.end(); it++) {
		cout << (string)(*it) << " ";
	}
	cout << endl;
}*/


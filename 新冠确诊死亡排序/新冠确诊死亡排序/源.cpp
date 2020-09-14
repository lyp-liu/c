#include<iostream>
#include<fstream>
#include<string>
using namespace std;
typedef struct Node {
	int  quezhen_num;//ȷ����
	int siwang_num;//������
	string country_name;//����
	
	double death_radio;//������
}Country[100];
Country country;
int guojia_num = 0;//�ܹ����ٹ���

void sort_1() {
	for (int i = 0; i < guojia_num - 1; i++)
	{
		for (int j = 0; j < guojia_num - i - 1; j++)
		{
			if (country[j].quezhen_num > country[j + 1].quezhen_num) {
				//��[j]��ֵ������ʱ����
				string tempname = country[j].country_name;
				int tempdef = country[j].quezhen_num;
				int tempdeath = country[j].siwang_num;
				double tempradio = country[j].death_radio;
				//��[j+1]��ֵ����[j]
				country[j].country_name = country[1 + j].country_name;
				country[j].quezhen_num = country[1 + j].quezhen_num;
				country[j].siwang_num = country[1 + j].siwang_num;
				country[j].death_radio = country[1 + j].death_radio;
				//����ʱ������ֵ����[j+1]
				country[1 + j].country_name = tempname;
				country[1 + j].quezhen_num = tempdef;
				country[1 + j].siwang_num = tempdeath;
				country[1 + j].death_radio = tempradio;


			}

		}
	}
}
void sort_2() {
	for (int i = 0; i < guojia_num - 1; i++)
	{
		for (int j = 0; j < guojia_num - i - 1; j++)
		{
			if (country[j].siwang_num < country[j + 1].siwang_num) {
				string tempname = country[j].country_name;
				int tempdef = country[j].quezhen_num;
				int tempdeath = country[j].siwang_num;
				double tempradio = country[j].death_radio;
				country[j].country_name = country[1 + j].country_name;
				country[j].quezhen_num = country[1 + j].quezhen_num;
				country[j].siwang_num = country[1 + j].siwang_num;
				country[j].death_radio = country[1 + j].death_radio;
				country[1 + j].country_name = tempname;
				country[1 + j].quezhen_num = tempdef;
				country[1 + j].siwang_num = tempdeath;
				country[1 + j].death_radio = tempradio;


			}

		}
	}
}
void sort_3() {
	for (int i = 0; i < guojia_num - 1; i++)
	{
		for (int j = 0; j < guojia_num - i - 1; j++)
		{
			if (country[j].death_radio < country[j + 1].death_radio) {
				string tempname = country[j].country_name;
				int tempdef = country[j].quezhen_num;
				int tempdeath = country[j].siwang_num;
				double tempradio = country[j].death_radio;
				country[j].country_name = country[1 + j].country_name;
				country[j].quezhen_num = country[1 + j].quezhen_num;
				country[j].siwang_num = country[1 + j].siwang_num;
				country[j].death_radio = country[1 + j].death_radio;
				country[1 + j].country_name = tempname;
				country[1 + j].quezhen_num = tempdef;
				country[1 + j].siwang_num = tempdeath;
				country[1 + j].death_radio = tempradio;


			}

		}
	}
}

int main() {
	int c;
	FILE *fp;
	fp = fopen("data.txt", "rb");
	if (fp)//C�����룬���������ܹ�������
	{
		while ((c = fgetc(fp)) != EOF) {
			if (c == '\n')
				guojia_num++;
		}
		fclose(fp);
	}
	guojia_num--;
	ifstream infile;
	infile.open("data.txt");
	for (int i = 0; i < guojia_num; i++) {
		infile >> country[i].country_name >> country[i].quezhen_num >> country[i].siwang_num;
		country[i].death_radio = ((double)country[i].siwang_num) / ((double)country[i].quezhen_num);
	}
	infile.close();
	sort_1();
	cout << "��1��ȷ������С�������������\n���ң�\tȷ������\t������\n";
	for (int i = 0; i < guojia_num; i++) {
		cout << country[i].country_name << "       " << country[i].quezhen_num <<"         " << country[i].siwang_num << endl;
	}
	cout << endl << endl;
	sort_2();
	cout << "��2���������Ӷൽ�ٵ���������\n���ң�\tȷ������\t������\n";
	for (int i = 0; i < guojia_num; i++) {
		cout << country[i].country_name << "       " << country[i].quezhen_num << "         " << country[i].siwang_num << endl;
	}
	cout << endl << endl;
	sort_3();
	cout << "��3�������ʴӶൽ�ٵ���������\n���ң�    ȷ������    ������    ������\n";
	for (int i = 0; i < guojia_num; i++) {
		cout << country[i].country_name << "      " << country[i].quezhen_num << "       " << country[i].siwang_num <<"       "<<country[i].death_radio<< endl;
	}
	system("pause");
	return 0;
}
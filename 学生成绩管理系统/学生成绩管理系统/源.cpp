#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<cstdlib>
#include<math.h>
using namespace std;
class Student
{
public:
	Student();
	~Student();
	string m_id, m_name;
	int m_math, m_english, m_physics, m_all;
};
class Management {
public:
	Management();
	~Management();

	vector<Student>m_students;
};
Student::Student()
{
}
Student::~Student()
{
}
Management::Management()
{
}
Management::~Management()
{
}

Management mana;
int num_line = 0;
void Duquwj()//��ȡ����
{

	int ca;
	FILE *sub;
	sub = fopen("data.txt", "rb");
	if (sub)//���������ܹ�������
	{
		while ((ca = fgetc(sub)) != EOF) {
			if (ca == '\n')
				num_line++;
		}
		fclose(sub);
	}
	num_line++;
	ifstream intil;//��ȡ����
	intil.open("data.txt");
	string tm1, tm2; 
	int tm3, tm4, tm5;

	for (int i = 0; i < num_line; i++) {
		Student temp;
		intil >> tm1 >> tm2 >> tm3 >> tm4 >> tm5;
		temp.m_id = tm1;
		temp.m_name = tm2;
		temp.m_math = tm3;
		temp.m_english = tm4;
		temp.m_physics = tm5;
		mana.m_students.push_back(temp);
	}
	intil.close();
}
void tianjia() {//��Ӽ�¼
	cout << "������ѧ����ѧ�š���������ѧ�ɼ���Ӣ��ɼ�������ɼ�" << endl;
	string NAME, XUEHAO;
	char c='0';
	int math_score, english_score, physics_score;
	cin >> XUEHAO >> NAME >> math_score >> english_score >> physics_score;
	Student temp;
	temp.m_id = XUEHAO;
	temp.m_name = NAME;
	temp.m_math = math_score;
	temp.m_english = english_score;
	temp.m_physics = physics_score;
	mana.m_students.push_back(temp);
	num_line++;

	cout << "�Ƿ������ӣ�Y/N" << endl;
	if (c == 'Y'||c=='y')
		tianjia();
	else {
		ofstream otf;//����д�ص�txt�ĵ�
		otf.open("data.txt");
		for (int i = 0; i < num_line; i++) {
			otf << mana.m_students[i].m_id << '\t' << mana.m_students[i].m_name << '\t'
				<< mana.m_students[i].m_math << '\t' << mana.m_students[i].m_english << '\t'
				<< mana.m_students[i].m_physics << '\n';
		}
	}
}
void xiugai() {
	cout << "�޸ĵ�ѧ��ѧ��Ϊ��" << endl;
	string XUEHAO;
	cin >> XUEHAO;
	
	cout << "��������Ϣ:\nѧ��\t\t����\t��ѧ\tӢ��\t����\n";
	for (vector<Student>::iterator diedai = mana.m_students.begin(); diedai != mana.m_students.end(); diedai++) {        //��vector��ɾ��ָ����ĳһ��Ԫ�� 
		if (diedai->m_name == XUEHAO) {//ʹ�õ���������vector
			cout << diedai->m_id << '\t' << diedai->m_name << '\t' << diedai->m_math << '\t' << diedai->m_english << '\t' << diedai->m_physics << endl;

			mana.m_students.erase(diedai);
			num_line--;

			break;
		}
	}
	cout << "�������޸ĺ�ĸ�����Ϣ��ѧ�� ���� ��ѧ�ɼ� Ӣ��ɼ� ����ɼ���" << endl;
	int math_score, english_score, physics_score;
	string nm;
	cin >> XUEHAO >> nm >> math_score >> english_score >> physics_score;
	Student temp;
	temp.m_id = XUEHAO;
	temp.m_name = nm;
	temp.m_math = math_score;
	temp.m_english = english_score;
	temp.m_physics = physics_score;
	mana.m_students.push_back(temp);
	num_line++;
	ofstream outfile;//����д�ص�txt�ĵ�
	outfile.open("data.txt");
	for (int i = 0; i < num_line; i++) {
		outfile << mana.m_students[i].m_id << '\t' << mana.m_students[i].m_name << '\t'
			<< mana.m_students[i].m_math << '\t' << mana.m_students[i].m_english << '\t'
			<< mana.m_students[i].m_physics << '\n';
	}

};

void xianshi() {
	cout << "ȫ��ѧ������Ϣ\nѧ��\t\t����\t��ѧ\tӢ��\t����\n";
	for (vector<Student>::iterator diedai = mana.m_students.begin(); diedai != mana.m_students.end(); diedai++) {        //��vector��ɾ��ָ����ĳһ��Ԫ�� 
			cout << diedai->m_id << '\t' << diedai->m_name << '\t' << diedai->m_math << '\t' << diedai->m_english << '\t' << diedai->m_physics << endl;
	}
};
void Sort() {
	for (int i = 0; i < num_line; i++) {
		for (int j = 0; j < num_line - 1; j++) {
			
			if (mana.m_students[j].m_all > mana.m_students[1 + j].m_all)
				continue;
			if (mana.m_students[j].m_all == mana.m_students[1 + j].m_all&&mana.m_students[j].m_math > mana.m_students[1 + j].m_math)
				continue;
			if (mana.m_students[j].m_all == mana.m_students[1 + j].m_all&&mana.m_students[j].m_math == mana.m_students[1 + j].m_math&&mana.m_students[j].m_english > mana.m_students[1 + j].m_english)
				continue;
			if (mana.m_students[j].m_all == mana.m_students[1 + j].m_all&&mana.m_students[j].m_math == mana.m_students[1 + j].m_math&&mana.m_students[j].m_english == mana.m_students[1 + j].m_english&&mana.m_students[j].m_physics > mana.m_students[1 + j].m_physics)
				continue;
			if (mana.m_students[j].m_all == mana.m_students[1 + j].m_all&&mana.m_students[j].m_math == mana.m_students[1 + j].m_math&&mana.m_students[j].m_english == mana.m_students[1 + j].m_english&&mana.m_students[j].m_physics == mana.m_students[1 + j].m_physics&&mana.m_students[j].m_id > mana.m_students[j + 1].m_id)
				continue;
			swap(mana.m_students[j], mana.m_students[j + 1]);

		}
	}
}
void paixu() {
	
	for (int i = 0; i < num_line; i++) {
		mana.m_students[i].m_all = mana.m_students[i].m_math +
			mana.m_students[i].m_english + mana.m_students[i].m_physics;
	}
	Sort();
	cout << "��������Ϣ��\nѧ��\t\t����\t�ܷ�\t��ѧ\tӢ��\t����\n";
	for (vector<Student>::iterator itor = mana.m_students.begin(); itor != mana.m_students.end(); itor++) {        //��vector��ɾ��ָ����ĳһ��Ԫ�� 
		cout << itor->m_id << '\t' << itor->m_name << '\t' << itor->m_all << '\t' << itor->m_math << '\t' << itor->m_english << '\t' << itor->m_physics << endl;
	}
	//����д���µ�txt�ĵ�
	ofstream otf;
	otf.open("sortdata.txt");
	for (int i = 0; i < num_line; i++) {
		otf << mana.m_students[i].m_id << '\t' << mana.m_students[i].m_name << '\t'
			<< mana.m_students[i].m_math << '\t' << mana.m_students[i].m_english << '\t'
			<< mana.m_students[i].m_physics << '\t'<<mana.m_students[i].m_all<< '\n';
	}
};
void get_average(int choice) {
	double avscore = 0;
	if (choice == 1) {
		for (int j = 0; j < num_line; j++) {
			avscore += mana.m_students[j].m_math;
		}
		avscore = avscore / (double)num_line;
		cout << "��ѧƽ���ɼ�Ϊ" << avscore << endl;
	}
	else if (choice == 2) {
		for (int j = 0; j < num_line; j++) {
			avscore += mana.m_students[j].m_english;
		}
		avscore = avscore / (double)num_line;
		cout << "Ӣ��ƽ���ɼ�Ϊ" << avscore << endl;
	}
	else {
		for (int j = 0; j < num_line; j++) {
			avscore += mana.m_students[j].m_physics;
		}
		avscore = avscore / (double)num_line;
		cout << "����ƽ���ɼ�Ϊ" << avscore << endl;
	}
}
double get_average(double score) {
	double allaver = 0;
	for (int i = 0; i < num_line; i++) {
		allaver += mana.m_students[i].m_english + mana.m_students[i].m_math + mana.m_students[i].m_physics;
	}
	allaver /= num_line;
	cout << "������Ŀ��ƽ���ɼ�Ϊ" << allaver << endl;
	return allaver;
}
void tongjifx() {
	cout << "0.�󵥿�ƽ���ɼ�\n1.������ƽ���ɼ�" << endl;
	int a;
	cin >> a;
	double x = 0;
	if (a == 0) {
		cout << "����ѧ�ɼ�����1����Ӣ��ɼ�����2��������ɼ�����3" << endl;
		cin >> a;
		get_average(a);
	}
	else get_average(x);
};
void chazhaoxs() {
	cout << "������ѯ������1\nѧ�Ų�ѯ������0" << endl;
	int p = 0;
	string check;
	cin >> p;
	if (p == 1) {
		cout << "���ҵ�ѧ������Ϊ��" << endl;
		cin >> check;
		for (vector<Student>::iterator diedai = mana.m_students.begin(); diedai != mana.m_students.end(); diedai++) {        //��vector��ɾ��ָ����ĳһ��Ԫ�� 
			if (diedai->m_name == check) {//ʹ�õ�������������
				cout << "��ѧ����Ϣ��\nѧ��\t\t����\t��ѧ\tӢ��\t����\n";
				cout << diedai->m_id << '\t' << diedai->m_name << '\t' << diedai->m_math << '\t' << diedai->m_english << '\t' << diedai->m_physics << endl;
				break;
			}
		}
	}
	else {
		cout << "���ҵ�ѧ��ѧ��Ϊ:" << endl;
		cin >> check;
		for (vector<Student>::iterator diedai = mana.m_students.begin(); diedai != mana.m_students.end(); diedai++) {        //��vector��ɾ��ָ����ĳһ��Ԫ�� 
			if (diedai->m_id == check) {//ʹ�õ���������vector
				cout << "ѧ����Ϣ��\nѧ��\t\t����\t��ѧ\tӢ��\t����\n";
				cout << diedai->m_id << '\t' << diedai->m_name << '\t' << diedai->m_math << '\t' << diedai->m_english << '\t' << diedai->m_physics << endl;
				break;
			}
		}
	}
};
void chazhaofsd() {
	string subj;
	cout << "Ҫ��ѯ�Ŀ�Ŀ��Ϊ" << endl;
	cin >> subj;
	cout << "Ҫ��ѯ�ķ�����Ϊ:(�������½��������Ͻ�)" << endl;
	int lowj = 0;
	int highj = 0;
	cin >> lowj >> highj;

	cout << subj << "�ĳɼ���" << lowj << "��" << highj << "������Ϊ��" << endl;
	if (subj == "��ѧ") {
		for (vector<Student>::iterator diedai = mana.m_students.begin(); diedai != mana.m_students.end(); diedai++) {        //��vector��ɾ��ָ����ĳһ��Ԫ�� 
			if ((diedai->m_math <= highj) && (diedai->m_math > lowj)) {//ʹ�õ���������vector
				string tp = diedai->m_name;
				cout << tp << endl;
			}
		}
	}
	else if (subj == "����") {
		for (vector<Student>::iterator diedai = mana.m_students.begin(); diedai != mana.m_students.end(); diedai++) {        //��vector��ɾ��ָ����ĳһ��Ԫ�� 
			if ((diedai->m_physics <= highj) && (diedai->m_physics > lowj)) {//ʹ�õ���������vector
				string tp = diedai->m_name;
				cout << tp << endl;
			}
		}
	}
	else {
		for (vector<Student>::iterator diedai = mana.m_students.begin(); diedai !=mana.m_students.end(); diedai++) {        //��vector��ɾ��ָ����ĳһ��Ԫ�� 
			if ((diedai->m_english <= highj) && (diedai->m_english > lowj)) {//ʹ�õ���������vector
				string tp = diedai->m_name;
				cout << tp << endl;
			}
		}
	}
};
int shanchu() {
	while (1)
	{
		
		string name, choice; bool flag=false;
		cout << "Ҫɾ����ѧ������Ϊ��(����ģ������)" << endl;
		cin >> name;
		for (vector<Student>::iterator diedai = mana.m_students.begin(); diedai != mana.m_students.end(); diedai++) {
			if (name == diedai->m_name) {
				cout<< "ѧ����Ϣ��\nѧ��\t\t����\t��ѧ\tӢ��\t����\n";
				cout << diedai->m_id << '\t' << diedai->m_name << '\t' << diedai->m_math << '\t' << diedai->m_english << '\t' << diedai->m_physics << endl;
				cout << "�Ƿ�ȷ��ɾ���ü�¼Y/N" << endl;
				cin >> choice;
				if (choice == "Y" || choice == "y") {
					mana.m_students.erase(diedai);
					num_line--;
					flag = true;
				}
				ofstream otf;//����д�ص�txt�ĵ�
				otf.open("data.txt");
				for (int i = 0; i < num_line; i++) {
					otf << mana.m_students[i].m_id << '\t' << mana.m_students[i].m_name << '\t'
						<< mana.m_students[i].m_math << '\t' << mana.m_students[i].m_english << '\t'
						<< mana.m_students[i].m_physics << '\n';
				}
				cout << "�ɹ�ɾ�����Ƿ����ɾ�� Y/N" << endl;
				cin >> choice;
				if(choice == "Y" || choice == "y")
					break;
				else return 0;
				
			}
		}
		if (flag == false) {
			cout<< "ѧ����Ϣ��\nѧ��\t\t����\t��ѧ\tӢ��\t����\n";
			for (int i = 0; i < num_line; i++) {
				if (mana.m_students[i].m_name.find(name) != string::npos) {
					cout<< mana.m_students[i].m_id << '\t' << mana.m_students[i].m_name << '\t' << mana.m_students[i].m_math << '\t' << mana.m_students[i].m_english << '\t' << mana.m_students[i].m_physics << endl;
				}
			}
		}
	}
	
}
int main() {
	while (1)  //ѭ������
	{
		num_line = 0;
		
		cout << "\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
		cout << "\t\t\t^^^^^^^^^^^^^^^��ӭ��ʹ��ѧ���ɼ�����ϵͳ^^^^^^^^^^^\n";
		cout << "\t\t**********\t\t1�������µ�ѧ����¼**********\n";
		cout << "\t\t**********\t\t2����ѧ���ɼ������޸�\t\t\t**********\n";
		cout << "\t\t**********\t\t3��ɾ��ԭ�����еļ�¼\t\t\t**********\n";
		cout << "\t\t**********\t\t4������\t\t\t**********\n";
		cout << "\t\t**********\t\t5��ͳ�Ʒ���\t**********\n";
		cout << "\t\t**********\t\t6������ĳ��ѧ���ĳɼ�\t**********\n";
		cout << "\t\t**********\t\t7������ָ��������ѧ������\t**********\n";
		cout << "\t\t**********\t\t8����ʾȫ��ѧ����Ϣ\t*******************\n";
		cout << "\t\t**********\t\t9���˳�\t**********\n";
		Duquwj();
		int x;
		cin >> x;
		switch (x) {
		case 1:
			tianjia();
			break;
		case 2:
			xiugai();
			break;
		case 3:
			shanchu();
			break;
	
		case 4:
			paixu();

			break;
		case 5:
			tongjifx();

			break;
		case 6:
			chazhaoxs();

			break;
		case 7:
			chazhaofsd();
			break;
		case 8:
			xianshi();
			break;
		case 9:
			return 0;
		default:
			cout<<"��������������⣬����������!";
		}
		
		system("pause"); 
		system("cls");
	}
	return 0;
	
}
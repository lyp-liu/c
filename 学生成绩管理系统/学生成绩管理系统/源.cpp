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
void Duquwj()//读取数据
{

	int ca;
	FILE *sub;
	sub = fopen("data.txt", "rb");
	if (sub)//计算数据总共多少行
	{
		while ((ca = fgetc(sub)) != EOF) {
			if (ca == '\n')
				num_line++;
		}
		fclose(sub);
	}
	num_line++;
	ifstream intil;//读取数据
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
void tianjia() {//添加记录
	cout << "请输入学生的学号、姓名、数学成绩、英语成绩、物理成绩" << endl;
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

	cout << "是否继续添加？Y/N" << endl;
	if (c == 'Y'||c=='y')
		tianjia();
	else {
		ofstream otf;//数据写回到txt文档
		otf.open("data.txt");
		for (int i = 0; i < num_line; i++) {
			otf << mana.m_students[i].m_id << '\t' << mana.m_students[i].m_name << '\t'
				<< mana.m_students[i].m_math << '\t' << mana.m_students[i].m_english << '\t'
				<< mana.m_students[i].m_physics << '\n';
		}
	}
}
void xiugai() {
	cout << "修改的学生学号为：" << endl;
	string XUEHAO;
	cin >> XUEHAO;
	
	cout << "该生的信息:\n学号\t\t姓名\t数学\t英语\t物理\n";
	for (vector<Student>::iterator diedai = mana.m_students.begin(); diedai != mana.m_students.end(); diedai++) {        //从vector中删除指定的某一个元素 
		if (diedai->m_name == XUEHAO) {//使用迭代器遍历vector
			cout << diedai->m_id << '\t' << diedai->m_name << '\t' << diedai->m_math << '\t' << diedai->m_english << '\t' << diedai->m_physics << endl;

			mana.m_students.erase(diedai);
			num_line--;

			break;
		}
	}
	cout << "请输入修改后的该生信息（学号 姓名 数学成绩 英语成绩 物理成绩）" << endl;
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
	ofstream outfile;//数据写回到txt文档
	outfile.open("data.txt");
	for (int i = 0; i < num_line; i++) {
		outfile << mana.m_students[i].m_id << '\t' << mana.m_students[i].m_name << '\t'
			<< mana.m_students[i].m_math << '\t' << mana.m_students[i].m_english << '\t'
			<< mana.m_students[i].m_physics << '\n';
	}

};

void xianshi() {
	cout << "全部学生的信息\n学号\t\t姓名\t数学\t英语\t物理\n";
	for (vector<Student>::iterator diedai = mana.m_students.begin(); diedai != mana.m_students.end(); diedai++) {        //从vector中删除指定的某一个元素 
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
	cout << "排序后的信息：\n学号\t\t姓名\t总分\t数学\t英语\t物理\n";
	for (vector<Student>::iterator itor = mana.m_students.begin(); itor != mana.m_students.end(); itor++) {        //从vector中删除指定的某一个元素 
		cout << itor->m_id << '\t' << itor->m_name << '\t' << itor->m_all << '\t' << itor->m_math << '\t' << itor->m_english << '\t' << itor->m_physics << endl;
	}
	//数据写到新的txt文档
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
		cout << "数学平均成绩为" << avscore << endl;
	}
	else if (choice == 2) {
		for (int j = 0; j < num_line; j++) {
			avscore += mana.m_students[j].m_english;
		}
		avscore = avscore / (double)num_line;
		cout << "英语平均成绩为" << avscore << endl;
	}
	else {
		for (int j = 0; j < num_line; j++) {
			avscore += mana.m_students[j].m_physics;
		}
		avscore = avscore / (double)num_line;
		cout << "物理平均成绩为" << avscore << endl;
	}
}
double get_average(double score) {
	double allaver = 0;
	for (int i = 0; i < num_line; i++) {
		allaver += mana.m_students[i].m_english + mana.m_students[i].m_math + mana.m_students[i].m_physics;
	}
	allaver /= num_line;
	cout << "三个科目的平均成绩为" << allaver << endl;
	return allaver;
}
void tongjifx() {
	cout << "0.求单科平均成绩\n1.求三科平均成绩" << endl;
	int a;
	cin >> a;
	double x = 0;
	if (a == 0) {
		cout << "求数学成绩输入1，求英语成绩输入2，求物理成绩输入3" << endl;
		cin >> a;
		get_average(a);
	}
	else get_average(x);
};
void chazhaoxs() {
	cout << "姓名查询请输入1\n学号查询请输入0" << endl;
	int p = 0;
	string check;
	cin >> p;
	if (p == 1) {
		cout << "查找的学生姓名为：" << endl;
		cin >> check;
		for (vector<Student>::iterator diedai = mana.m_students.begin(); diedai != mana.m_students.end(); diedai++) {        //从vector中删除指定的某一个元素 
			if (diedai->m_name == check) {//使用迭代器遍历容器
				cout << "该学生信息：\n学号\t\t姓名\t数学\t英语\t物理\n";
				cout << diedai->m_id << '\t' << diedai->m_name << '\t' << diedai->m_math << '\t' << diedai->m_english << '\t' << diedai->m_physics << endl;
				break;
			}
		}
	}
	else {
		cout << "查找的学生学号为:" << endl;
		cin >> check;
		for (vector<Student>::iterator diedai = mana.m_students.begin(); diedai != mana.m_students.end(); diedai++) {        //从vector中删除指定的某一个元素 
			if (diedai->m_id == check) {//使用迭代器遍历vector
				cout << "学生信息：\n学号\t\t姓名\t数学\t英语\t物理\n";
				cout << diedai->m_id << '\t' << diedai->m_name << '\t' << diedai->m_math << '\t' << diedai->m_english << '\t' << diedai->m_physics << endl;
				break;
			}
		}
	}
};
void chazhaofsd() {
	string subj;
	cout << "要查询的科目名为" << endl;
	cin >> subj;
	cout << "要查询的分数段为:(先输入下界再输入上界)" << endl;
	int lowj = 0;
	int highj = 0;
	cin >> lowj >> highj;

	cout << subj << "的成绩从" << lowj << "到" << highj << "的名单为：" << endl;
	if (subj == "数学") {
		for (vector<Student>::iterator diedai = mana.m_students.begin(); diedai != mana.m_students.end(); diedai++) {        //从vector中删除指定的某一个元素 
			if ((diedai->m_math <= highj) && (diedai->m_math > lowj)) {//使用迭代器遍历vector
				string tp = diedai->m_name;
				cout << tp << endl;
			}
		}
	}
	else if (subj == "物理") {
		for (vector<Student>::iterator diedai = mana.m_students.begin(); diedai != mana.m_students.end(); diedai++) {        //从vector中删除指定的某一个元素 
			if ((diedai->m_physics <= highj) && (diedai->m_physics > lowj)) {//使用迭代器遍历vector
				string tp = diedai->m_name;
				cout << tp << endl;
			}
		}
	}
	else {
		for (vector<Student>::iterator diedai = mana.m_students.begin(); diedai !=mana.m_students.end(); diedai++) {        //从vector中删除指定的某一个元素 
			if ((diedai->m_english <= highj) && (diedai->m_english > lowj)) {//使用迭代器遍历vector
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
		cout << "要删除的学生姓名为：(可以模糊查找)" << endl;
		cin >> name;
		for (vector<Student>::iterator diedai = mana.m_students.begin(); diedai != mana.m_students.end(); diedai++) {
			if (name == diedai->m_name) {
				cout<< "学生信息：\n学号\t\t姓名\t数学\t英语\t物理\n";
				cout << diedai->m_id << '\t' << diedai->m_name << '\t' << diedai->m_math << '\t' << diedai->m_english << '\t' << diedai->m_physics << endl;
				cout << "是否确认删除该记录Y/N" << endl;
				cin >> choice;
				if (choice == "Y" || choice == "y") {
					mana.m_students.erase(diedai);
					num_line--;
					flag = true;
				}
				ofstream otf;//数据写回到txt文档
				otf.open("data.txt");
				for (int i = 0; i < num_line; i++) {
					otf << mana.m_students[i].m_id << '\t' << mana.m_students[i].m_name << '\t'
						<< mana.m_students[i].m_math << '\t' << mana.m_students[i].m_english << '\t'
						<< mana.m_students[i].m_physics << '\n';
				}
				cout << "成功删除，是否继续删除 Y/N" << endl;
				cin >> choice;
				if(choice == "Y" || choice == "y")
					break;
				else return 0;
				
			}
		}
		if (flag == false) {
			cout<< "学生信息：\n学号\t\t姓名\t数学\t英语\t物理\n";
			for (int i = 0; i < num_line; i++) {
				if (mana.m_students[i].m_name.find(name) != string::npos) {
					cout<< mana.m_students[i].m_id << '\t' << mana.m_students[i].m_name << '\t' << mana.m_students[i].m_math << '\t' << mana.m_students[i].m_english << '\t' << mana.m_students[i].m_physics << endl;
				}
			}
		}
	}
	
}
int main() {
	while (1)  //循环界面
	{
		num_line = 0;
		
		cout << "\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
		cout << "\t\t\t^^^^^^^^^^^^^^^欢迎您使用学生成绩管理系统^^^^^^^^^^^\n";
		cout << "\t\t**********\t\t1、增加新的学生记录**********\n";
		cout << "\t\t**********\t\t2、对学生成绩进行修改\t\t\t**********\n";
		cout << "\t\t**********\t\t3、删除原来已有的记录\t\t\t**********\n";
		cout << "\t\t**********\t\t4、排序\t\t\t**********\n";
		cout << "\t\t**********\t\t5、统计分析\t**********\n";
		cout << "\t\t**********\t\t6、查找某个学生的成绩\t**********\n";
		cout << "\t\t**********\t\t7、查找指定分数段学生名单\t**********\n";
		cout << "\t\t**********\t\t8、显示全部学生信息\t*******************\n";
		cout << "\t\t**********\t\t9、退出\t**********\n";
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
			cout<<"输入的数字有问题，请重新输入!";
		}
		
		system("pause"); 
		system("cls");
	}
	return 0;
	
}
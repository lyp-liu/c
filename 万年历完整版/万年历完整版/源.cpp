#include<iostream>//���������
#include<iomanip> //������  
#include<vector>//����
#include<string>//�ַ���
#include<fstream>//�ļ����������ڶ�ȡ��������
#include<time.h> 
using namespace std; //ʹ�������ռ�
//��ӡ������������������Ϣ����������
void p_year(); //��ӡ��ĺ���
void p_month(); //��ӡ�����ĺ���
void p_day(); //��ӡ������Ϣ�ĺ������������գ�
void input_command(); //������������ĺ���
//����ȫ������ �洢������������ÿ������
int NotLeapYear[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
int LeapYear[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
//����ÿ����յ��������� 
typedef struct
{
	string Name;   //������
	int mon;   //�ڼ���
	int da;   //�ڼ���
}Festival;  //����

typedef struct
{
	int year;
	int month;
	int day;
	int value;
}DATE; //�洢��ǰ���ڵ�����
//��Ķ��壬���еĲ������������������
//���еĲ��������������Ľӿں���
class Date
{
public:
	//Ĭ�Ϲ��캯��   //1940��1��һ������һ 
	Date() :year(1940), month(1), day(1), unique_value(0), week(1) {}
	//����汾�����ع��캯�� 
	//����Ǹ��������������
	Date(unsigned short y, unsigned short m, unsigned short d) :year(y), month(m), day(d)
	{
		//����󲢸�value��ֵ 
		DateTounique_value();
		//����������
		count_week();

	}
	//����Ǹ���Ψһֵ������ģ�һ�㲻�ã���Ϊ�޷�ȷ��Ψһֵ��ֻ��1940.1.1֪����0��
	Date(unsigned short value) :unique_value(value)
	{
		//�����Ϊ��   year month day ��ֵ 
		unique_valueToDate();
		//����������
		count_week();
	}
	//�ı����ڵĺ�������Ĭ��ֵ�ĺ���
	void change_date(unsigned short y = 1940, unsigned short m = 1, unsigned short d = 1)
	{
		//��ֵ
		year = y;
		month = m;
		day = d;
		//�ı���������ֵ����Ϊ��������ص�
		DateTounique_value();
		count_week();
	}
	//�ж��Ƿ�Ϊ����ĺ��� ������һ�������������ذ汾���������õ���ֵ�Ƕ����˽��ֵ
	bool IsLeapYear()
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}
	//��һ���汾�Ĵ��� �жϷǳ�Ա�Ƿ�Ϊ����ĺ��� 
	bool IsLeapYear(unsigned short other_year)
	{
		return (other_year % 4 == 0 && other_year % 100 != 0) || (other_year % 400 == 0);
	}
	//Ψһֵת���ڵĺ�������unique_valueȥ����year month��day��ֵ
	void unique_valueToDate()
	{
		unsigned i = 1940, j = 0;  //��ʼ������
		unsigned short temp = unique_value;    //��ֵ����ʱֵ
		year = 0; month = 0; day = 0;   //ת��ǰ���㣬������ܲ����� 
		//��ʼ��������
		while (temp > 365)
		{
			if (IsLeapYear(i))
			{
				temp -= 366;   //�������366
			}
			else
			{
				temp -= 365;   //���������365
			}
			i++;
		}  //ѭ������ ֱ�����С��һ�������
		j = 0;
		//����������겢��ʣ��365�죬��ô������һ��ĵ�һ�죨��Ϊ����δȷ����
		if ((!IsLeapYear(i)) && temp == 365)
		{
			//�������+1 �� ��Ϊһ��һ�� ����һ���������
			year = i + 1; month = 1; day = 1;
		}
		//��������겢����2�µĻ�����Ҳ����һ���������
		else if (IsLeapYear(i) && temp >= 31 + 28)
		{
			while (temp >= LeapYear[j])   //ѭ����ȥ�����·�
			{
				temp -= LeapYear[j];
				j++;
			}
			//���ѭ���õ���j���Ƕ����£��������±� 
			month = j;
			//������Ҫ��1����Ϊ�����0�Ļ��������1�ţ�������Ҫ��1
			day = temp + 1;
		}
		else   //���һ���ձ����
		{
			while (temp >= NotLeapYear[j])  //ͬ��
			{
				temp -= NotLeapYear[j];
				j++;
			}
			month = j;
			day = temp + 1;   //ͬ��
		}

	}
	//����תΨһֵ�ĺ�������year month ��dayȥ����unique_value
	void DateTounique_value()
	{
		unique_value = 0;  //����� ��ʼֵΪ0 ��ʾ 1940��1��1��
		for (int i = 1940; i < year; i++)    //��1940��ʼ
		{
			if (IsLeapYear(i))   //������+366 ��֮+365
				unique_value += 366;
			else
				unique_value += 365;
		}
		//��������ˣ���������Ƿ������꣬��غ������Ƿ��һ��
		if (IsLeapYear(year))
		{
			for (int j = 0; j < month - 1; j++)
			{
				unique_value += LeapYear[j];   //�ǵĻ�����������
			}
		}
		else
		{
			for (int j = 0; j < month - 1; j++)
			{
				unique_value += NotLeapYear[j];   //���ǵĻ��ӷ���������
			}
		}
		unique_value += day;   //�����������ϣ���Ϊ����õ���ֵ����һ�������һ���ֵ
	}
	//�������һ��Ψһֵ������������ڼ�����ֵ��week��
	void count_week()
	{
		DateTounique_value();  //�ȸ���Ψһֵ
		week = (unique_value % 7) % 7;   //���������ڼ����������쿪ʼ 0-6
	}
	void print_head()  //��ӡ��ʾһ���������ı�ͷ
	{
		cout << "SUN " << "MON " << "TUE " << "WED " << "THU " << "FRI " << "SAT " << endl;
	}
	void GetDate();   //��ȡ��ǰ���� ���䱣���� Local_date�ṹ�������
	void DateTounique_valueForLocalDate();   //��һ���������ñ�����Ϊ�ṹ���е�value��ֵ
	void print_day();  //��ӡ�����ĺ�������������Ϊyear month��day
	void print_day(unsigned y, unsigned m, unsigned d); //�趨�����ں��ӡ������Ϣ
	void print_year();   //��ӡ����year��ֵ�����ڵ���ݵ���Ϣ 
	void print_year(unsigned y);  //��ӡ�ض������Ϣ
	void print_month(unsigned y, unsigned m);  //��ӡ�ض������Ϣ�����ֵ�ᱻ����
	void print_month();   //��ӡ����������Ϣ
private:
	//year  month day������Ϊ0����Ȼ�������Ϊ0��
	unsigned short year;   //�� ֵ��1940-2040 ʵ�����unsigned short���������ô�Ͳ������
	unsigned short month;   //�� ֵ��1��12
	unsigned short day;     //�� ֵ�������ͷ���������
	unsigned short week;  // ֵΪ0-6  ����������
	//��0��ʼ�����2���ֽڵ�short���� ����65536�б仯����ȫ���Ա�ʾ��100�꣨1940-2040���ڵ�����һ�� 
	unsigned short unique_value;
	//�洢ÿ��Ĺ������յ��������ڹ��캯���г�ʼ��
	vector<Festival> fes;
	//�洢��ǰ����
	DATE Local_date;

};
//����̨�汾����ʾ����,��ʾ��ǰ����ֵ�����������ݸ������ڵ�ֵȷ��
void Date::print_year()
{
	int i = 0;
	month = 1; //���·ݺ��ն���Ϊ1��Ȼ��ѭ���������
	day = 1;
	DateTounique_value();   //ת����Ψһֵ
	count_week();   //���������ڼ�
	while (month <= 12)
	{
		print_month();    //��ӡÿ����
		month++;    //���·�����
		DateTounique_value();   //����Ψһֵ
		//ѭ��12�����
	}
}
void Date::print_day(unsigned y, unsigned m, unsigned d)
{
	change_date(y, m, d);  //���¶����˽��ֵ
	Date::print_day();  //���ô�ӡ
}
void Date::print_day()
{
	Festival temp;  //������ʱ�����������ļ���ֵ
	fstream infile("Festival.txt", ios::in);  //���ļ�
	if (!infile)  //�ж��Ƿ�ɹ���
		exit(0);  //�˳�
	//ѭ����ֵ��fes��������ѯ����ʱ��Ҫ�����Ա�
	while (!infile.eof() && (infile >> temp.Name >> temp.mon >> temp.da))
		fes.push_back(temp);
	infile.close();//�ر��ļ�
	DateTounique_value();  //ת��Ψһֵ
	GetDate(); //��ȡ��ǰ����
	count_week(); //�������ڣ�����һ��Ҫ��ס����תΨһֵ�ټ������ڣ�����
	cout << "�����ǣ�" << year << "��" << month << "��" << day << "��";
	//�ٴ�ӡ�����ڰ�
	switch (week)
	{
	case 0:
		cout << "  ������";
		break;
	case 1:
		cout << "  ����һ";
		break;
	case 2:
		cout << "  ���ڶ�";
		break;
	case 3:
		cout << "  ������";
		break;
	case 4:
		cout << "  ������";
		break;
	case 5:
		cout << "  ������";
		break;
	case 6:
		cout << "  ������";
		break;
	default:
		cerr << "����";
	}
	cout << "������컹�У�" << unique_value - Local_date.value << "��" << endl;
	//����д��ʾ�Ƿ��й������� �����ȶԱ�
	for (vector<Festival>::const_iterator it = fes.begin(); it != fes.end();it++)
	{
		if (month == it->mon&&day == it->da)
		{
			//�ҵ��˾ʹ�ӡ��Ϣ��û�ҵ��Ͳ���ʾ
			cout << "��һ����" << it->Name << endl;
			break;
		}
		
		else if(it==fes.end()-1)
			cout << "��һ�첻�ǹ�������" << endl;
	}
}
void Date::print_year(unsigned y)  //����̨�汾����ʾ����,��ʾ��ǰָ�������������ݸ������ڵ�ֵȷ��  
{
	change_date(y, 1, 1);  //����ֵ
	Date::print_year();  //���ô�ӡ
}
//����̨�汾����ʾ��������ʾһ���ض����µ�������������һ�����ذ汾
void Date::print_month(unsigned y, unsigned m)
{
	change_date(y, m, 1);   //����ֵ
	Date::print_month();  //���ô�ӡ
}
//����̨�汾����ʾ����,��ʾ��ǰ���µ��������·ݸ������ڵ�ֵȷ��
void Date::print_month()    //���д�ӡ�����ĺ���
{
	//��������ֵ ���ڶ�Ϊ����һ�ţ��������������Ѿ����£�����ֻ��ȷ��һ��Ψһֵ

	DateTounique_value();   //ת����Ψһֵ
	count_week();   //���������ڼ�
	//��ӡ
	cout << endl << month << "�£�" << endl;  //��ӡ��ʾ���·�
	print_head();  //�ȴ�ӡͷ
	int i = 0;  //��ʼ��
	for (; i < week; i++)   //�ճ��յ�����
	{
		cout << "    ";
	}
	cout.setf(ios::left);  //���������ʽ �����
	if (IsLeapYear())   //���������
	{
		for (int j = 0; j < LeapYear[month - 1]; j++)  //�������������ӡ
		{
			if (i != 0 && i % 7 == 0)   //ÿ7�����ڻ���һ�Σ���Ҫ����֮ǰ�ճ����ģ�������i
				cout << endl;
			cout << setw(4) << j + 1;
			i++;
		}
	}
	else   //������
	{
		for (int j = 0; j < NotLeapYear[month - 1]; j++)  //���÷����������ӡ
		{
			if (i != 0 && i % 7 == 0)    //ÿ7�����ڻ���һ�Σ���Ҫ����֮ǰ�ճ����ģ�������i
				cout << endl;
			cout << setw(4) << j + 1;
			i++;
		}
	}
	cout << endl;   //����ӡ�س�
}
int main()   //������
{
	while (1)  //ѭ������
	{
		system("cls");
		cout << "\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
		cout << "\t\t\t^^^^^^^^^^^��ӭ��ʹ��������^^^^^^^^^^^^^\n";
		cout << "\t\t\t^^^^^^^^^��ѡ����Ҫʵ�ֵĹ���^^^^^^^^^^^\n";
		cout << "\t\t*********\t\t1����ѯ����\t\t*********\n";
		cout << "\t\t*********\t\t2����ѯ����\t\t*********\n";
		cout << "\t\t*********\t\t3����ѯ����\t\t*********\n";
		cout << "\t\t*********\t\t4���˳�    \t\t*********\n";
		
		input_command(); //��������
		system("pause"); //��ͣ��
	}
	return 0;  //����
}
////����̨�������뺯��
void input_command()
{
	int y;
	cin >> y;
	switch (y)
	{
	case 1:
		p_year();  //����1ʱ���ô�ӡ�����ĺ���
		break;
	case 2:
		p_month();//����ʱ2ʱ���ô�ӡ�����ĺ���
		break;
	case 3:
		p_day();//����3ʱ���ô�ӡ������Ϣ�ĺ���
		break;
	case 4:
		exit(0);//����4ʱ�˳�
		break;
	default:
		cout << "�������!����������!";
	}
}
//��ӡ�����ĺ������ǳ�Ա����
void p_year()
{
	int a;  //����������
	cout << "������һ���������ʾ������:\n";
	cin >> a;
	Date D(a, 1, 1);  //��ʼ��Ϊ�����һ��
	D.print_year();  //ֱ�Ӵ�ӡ
}
void p_month()
{
	int a, c;  //��������
	cout << "������һ����ݼ��·�����ʾ������:\n";
	cin >> a >> c;
	Date D(a, c, 1);  //��ʼ��Ϊ������µ�һ�� 
	D.print_month(); //ֱ�Ӵ�ӡ
}
void p_day()
{
	int y, m, d;  //��������
	cout << "���������ڣ�(�������Կո���)";
	cin >> y >> m >> d;
	Date D(y, m, d); //��ʼ��Ϊy��m��d��
	D.print_day(y, m, d); //��ӡ������Ϣ

}
void Date::GetDate()   //��ȡ��ǰʱ��ĺ���
{
	time_t t;
	unsigned int value = 0;  //Ψһֵ
	time(&t);
	tm* t_tm = localtime(&t);
	Local_date.year = 1900 + t_tm->tm_year;
	Local_date.month = 1 + t_tm->tm_mon;
	Local_date.day = t_tm->tm_mday;
	//cout<<Local_date.year<<Local_date.month<<Local_date.day;
	DateTounique_valueForLocalDate();   //����ȡ֮�󣬽�year month dayת����Ψһֵvalue
}
//����תΨһֵ�ĺ�����Ϊ���㵱ǰ��������
void Date::DateTounique_valueForLocalDate()
{
	Local_date.value = 0;  //����� 
	for (int i = 1940; i < Local_date.year; i++)    //��1940��ʼ
	{
		if (IsLeapYear(i))   //������+366 ��֮+365
			Local_date.value += 366;
		else
			Local_date.value += 365;
	}
	//��������ˣ���������Ƿ������꣬��غ������Ƿ��һ��
	if (IsLeapYear(Local_date.year))
	{
		for (int j = 0; j < Local_date.month - 1; j++)
		{
			Local_date.value += LeapYear[j];   //�ǵĻ�����������
		}
	}
	else
	{
		for (int j = 0; j < Local_date.month - 1; j++)
		{
			Local_date.value += NotLeapYear[j];   //���ǵĻ��ӷ���������
		}
	}
	Local_date.value += Local_date.day;   //�����������ϣ���Ϊ����õ���ֵ����һ�������һ���ֵ
}

#include<iostream>//输入输出流
#include<iomanip> //操作子  
#include<vector>//容器
#include<string>//字符串
#include<fstream>//文件操作，用于读取公历节日
#include<time.h> 
using namespace std; //使用命名空间
//打印年历，月历，日期信息的三个函数
void p_year(); //打印年的函数
void p_month(); //打印月历的函数
void p_day(); //打印日期信息的函数（包括节日）
void input_command(); //键盘命令输入的函数
//两个全局数组 存储闰年与非闰年的每月天数
int NotLeapYear[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
int LeapYear[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
//定义每年节日的数据类型 
typedef struct
{
	string Name;   //节日名
	int mon;   //在几月
	int da;   //在几日
}Festival;  //别名

typedef struct
{
	int year;
	int month;
	int day;
	int value;
}DATE; //存储当前日期的类型
//类的定义，所有的操作都将基于类的数据
//所有的操作都将会基于类的接口函数
class Date
{
public:
	//默认构造函数   //1940年1月一日是周一 
	Date() :year(1940), month(1), day(1), unique_value(0), week(1) {}
	//多个版本的重载构造函数 
	//这个是根据日期来构造的
	Date(unsigned short y, unsigned short m, unsigned short d) :year(y), month(m), day(d)
	{
		//构造后并给value赋值 
		DateTounique_value();
		//并计算星期
		count_week();

	}
	//这个是根据唯一值来构造的，一般不用，因为无法确定唯一值（只有1940.1.1知道是0）
	Date(unsigned short value) :unique_value(value)
	{
		//构造后并为给   year month day 赋值 
		unique_valueToDate();
		//并计算星期
		count_week();
	}
	//改变日期的函数，带默认值的函数
	void change_date(unsigned short y = 1940, unsigned short m = 1, unsigned short d = 1)
	{
		//赋值
		year = y;
		month = m;
		day = d;
		//改变其他属性值，因为他们是相关的
		DateTounique_value();
		count_week();
	}
	//判断是否为闰年的函数 他还有一个带参数的重载版本，这里面用到的值是对象的私有值
	bool IsLeapYear()
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}
	//另一个版本的带参 判断非成员是否为闰年的函数 
	bool IsLeapYear(unsigned short other_year)
	{
		return (other_year % 4 == 0 && other_year % 100 != 0) || (other_year % 400 == 0);
	}
	//唯一值转日期的函数，用unique_value去计算year month和day的值
	void unique_valueToDate()
	{
		unsigned i = 1940, j = 0;  //初始化变量
		unsigned short temp = unique_value;    //赋值给临时值
		year = 0; month = 0; day = 0;   //转换前清零，这里可能不合适 
		//开始计算日期
		while (temp > 365)
		{
			if (IsLeapYear(i))
			{
				temp -= 366;   //是闰年减366
			}
			else
			{
				temp -= 365;   //不是闰年减365
			}
			i++;
		}  //循环继续 直到结果小于一年的天数
		j = 0;
		//如果不是闰年并且剩余365天，那么就是下一年的第一天（因为月日未确定）
		if ((!IsLeapYear(i)) && temp == 365)
		{
			//所以年份+1 月 日为一月一日 这是一种特殊情况
			year = i + 1; month = 1; day = 1;
		}
		//如果是闰年并超过2月的话，这也算是一种特殊情况
		else if (IsLeapYear(i) && temp >= 31 + 28)
		{
			while (temp >= LeapYear[j])   //循环减去闰年月份
			{
				temp -= LeapYear[j];
				j++;
			}
			//最后循环得到的j就是多少月，而不是下标 
			month = j;
			//日期需要加1，因为结果是0的话结果就是1号，所以需要加1
			day = temp + 1;
		}
		else   //最后一种普遍情况
		{
			while (temp >= NotLeapYear[j])  //同上
			{
				temp -= NotLeapYear[j];
				j++;
			}
			month = j;
			day = temp + 1;   //同上
		}

	}
	//日期转唯一值的函数，用year month 和day去计算unique_value
	void DateTounique_value()
	{
		unique_value = 0;  //清空它 初始值为0 表示 1940年1月1日
		for (int i = 1940; i < year; i++)    //从1940开始
		{
			if (IsLeapYear(i))   //是闰年+366 反之+365
				unique_value += 366;
			else
				unique_value += 365;
		}
		//年计算完了，计算该年是否是闰年，这关乎该年是否多一天
		if (IsLeapYear(year))
		{
			for (int j = 0; j < month - 1; j++)
			{
				unique_value += LeapYear[j];   //是的话加闰年数组
			}
		}
		else
		{
			for (int j = 0; j < month - 1; j++)
			{
				unique_value += NotLeapYear[j];   //不是的话加非闰年数组
			}
		}
		unique_value += day;   //最后把天数加上，因为这里得到的值是上一个月最后一天的值
	}
	//计算对于一个唯一值，求出它是星期几并赋值给week。
	void count_week()
	{
		DateTounique_value();  //先更新唯一值
		week = (unique_value % 7) % 7;   //计算是星期几，从星期天开始 0-6
	}
	void print_head()  //打印显示一个月日历的表头
	{
		cout << "SUN " << "MON " << "TUE " << "WED " << "THU " << "FRI " << "SAT " << endl;
	}
	void GetDate();   //获取当前日期 将其保存在 Local_date结构体变量中
	void DateTounique_valueForLocalDate();   //上一个函数调用本函数为结构体中的value赋值
	void print_day();  //打印年历的函数，所用数据为year month和day
	void print_day(unsigned y, unsigned m, unsigned d); //设定好日期后打印日期信息
	void print_year();   //打印类内year的值所等于的年份的信息 
	void print_year(unsigned y);  //打印特定年份信息
	void print_month(unsigned y, unsigned m);  //打印特定年的信息，类的值会被更新
	void print_month();   //打印类内年月信息
private:
	//year  month day都不能为0，虽然这里可以为0。
	unsigned short year;   //年 值从1940-2040 实际如果unsigned short不溢出，那么就不会出错
	unsigned short month;   //月 值从1到12
	unsigned short day;     //日 值遵从闰年和非闰年数组
	unsigned short week;  // 值为0-6  从周日算起
	//从0开始，针对2个字节的short类型 共有65536中变化，完全可以表示出100年（1940-2040）内的任意一天 
	unsigned short unique_value;
	//存储每年的公历节日的容器，在构造函数中初始化
	vector<Festival> fes;
	//存储当前日期
	DATE Local_date;

};
//控制台版本的显示函数,显示当前类内值年的日历，年份根据类内的值确定
void Date::print_year()
{
	int i = 0;
	month = 1; //把月份和日都设为1，然后循环遍历输出
	day = 1;
	DateTounique_value();   //转换成唯一值
	count_week();   //计算是星期几
	while (month <= 12)
	{
		print_month();    //打印每个月
		month++;    //让月份增加
		DateTounique_value();   //更新唯一值
		//循环12次完成
	}
}
void Date::print_day(unsigned y, unsigned m, unsigned d)
{
	change_date(y, m, d);  //更新对象的私有值
	Date::print_day();  //调用打印
}
void Date::print_day()
{
	Festival temp;  //设置临时变量，接受文件的值
	fstream infile("Festival.txt", ios::in);  //打开文件
	if (!infile)  //判断是否成功打开
		exit(0);  //退出
	//循环赋值给fes容器，查询日期时需要用它对比
	while (!infile.eof() && (infile >> temp.Name >> temp.mon >> temp.da))
		fes.push_back(temp);
	infile.close();//关闭文件
	DateTounique_value();  //转换唯一值
	GetDate(); //获取当前日期
	count_week(); //计算星期，这里一定要记住，先转唯一值再计算日期！！！
	cout << "日期是：" << year << "年" << month << "月" << day << "日";
	//再打印个星期吧
	switch (week)
	{
	case 0:
		cout << "  星期天";
		break;
	case 1:
		cout << "  星期一";
		break;
	case 2:
		cout << "  星期二";
		break;
	case 3:
		cout << "  星期三";
		break;
	case 4:
		cout << "  星期四";
		break;
	case 5:
		cout << "  星期五";
		break;
	case 6:
		cout << "  星期六";
		break;
	default:
		cerr << "错误";
	}
	cout << "距离今天还有：" << unique_value - Local_date.value << "天" << endl;
	//这里写显示是否有公历节日 所以先对比
	for (vector<Festival>::const_iterator it = fes.begin(); it != fes.end();it++)
	{
		if (month == it->mon&&day == it->da)
		{
			//找到了就打印信息，没找到就不显示
			cout << "这一天是" << it->Name << endl;
			break;
		}
		
		else if(it==fes.end()-1)
			cout << "这一天不是公历节日" << endl;
	}
}
void Date::print_year(unsigned y)  //控制台版本的显示函数,显示当前指定年的日历，年份根据类内的值确定  
{
	change_date(y, 1, 1);  //更新值
	Date::print_year();  //调用打印
}
//控制台版本的显示函数，显示一个特定年月的日历，它还有一个重载版本
void Date::print_month(unsigned y, unsigned m)
{
	change_date(y, m, 1);   //更新值
	Date::print_month();  //调用打印
}
//控制台版本的显示函数,显示当前年月的日历，月份根据类内的值确定
void Date::print_month()    //所有打印函数的核心
{
	//更新所有值 日期定为该月一号，在其他函数中已经更新，这里只再确定一次唯一值

	DateTounique_value();   //转换成唯一值
	count_week();   //计算是星期几
	//打印
	cout << endl << month << "月：" << endl;  //打印显示的月份
	print_head();  //先打印头
	int i = 0;  //初始化
	for (; i < week; i++)   //空出空的日期
	{
		cout << "    ";
	}
	cout.setf(ios::left);  //设置输出格式 左对齐
	if (IsLeapYear())   //如果是闰年
	{
		for (int j = 0; j < LeapYear[month - 1]; j++)  //则用闰年数组打印
		{
			if (i != 0 && i % 7 == 0)   //每7个日期换行一次，需要考虑之前空出来的，所以用i
				cout << endl;
			cout << setw(4) << j + 1;
			i++;
		}
	}
	else   //否则呢
	{
		for (int j = 0; j < NotLeapYear[month - 1]; j++)  //则用非闰年数组打印
		{
			if (i != 0 && i % 7 == 0)    //每7个日期换行一次，需要考虑之前空出来的，所以用i
				cout << endl;
			cout << setw(4) << j + 1;
			i++;
		}
	}
	cout << endl;   //最后打印回车
}
int main()   //主函数
{
	while (1)  //循环界面
	{
		system("cls");
		cout << "\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
		cout << "\t\t\t^^^^^^^^^^^欢迎您使用万年历^^^^^^^^^^^^^\n";
		cout << "\t\t\t^^^^^^^^^请选择您要实现的功能^^^^^^^^^^^\n";
		cout << "\t\t*********\t\t1、查询年历\t\t*********\n";
		cout << "\t\t*********\t\t2、查询月历\t\t*********\n";
		cout << "\t\t*********\t\t3、查询日期\t\t*********\n";
		cout << "\t\t*********\t\t4、退出    \t\t*********\n";
		
		input_command(); //输入命令
		system("pause"); //暂停下
	}
	return 0;  //返回
}
////控制台命令输入函数
void input_command()
{
	int y;
	cin >> y;
	switch (y)
	{
	case 1:
		p_year();  //输入1时调用打印年历的函数
		break;
	case 2:
		p_month();//输入时2时调用打印月历的函数
		break;
	case 3:
		p_day();//输入3时调用打印日期信息的函数
		break;
	case 4:
		exit(0);//输入4时退出
		break;
	default:
		cout << "输入错误!请重新输入!";
	}
}
//打印年历的函数，非成员函数
void p_year()
{
	int a;  //用作输入年
	cout << "请输入一个年份来显示其年历:\n";
	cin >> a;
	Date D(a, 1, 1);  //初始化为该年第一天
	D.print_year();  //直接打印
}
void p_month()
{
	int a, c;  //用作输入
	cout << "请输入一个年份及月份来显示其月历:\n";
	cin >> a >> c;
	Date D(a, c, 1);  //初始化为该年该月第一天 
	D.print_month(); //直接打印
}
void p_day()
{
	int y, m, d;  //用作输入
	cout << "请输入日期：(年月日以空格间隔)";
	cin >> y >> m >> d;
	Date D(y, m, d); //初始化为y年m月d日
	D.print_day(y, m, d); //打印该天信息

}
void Date::GetDate()   //获取当前时间的函数
{
	time_t t;
	unsigned int value = 0;  //唯一值
	time(&t);
	tm* t_tm = localtime(&t);
	Local_date.year = 1900 + t_tm->tm_year;
	Local_date.month = 1 + t_tm->tm_mon;
	Local_date.day = t_tm->tm_mday;
	//cout<<Local_date.year<<Local_date.month<<Local_date.day;
	DateTounique_valueForLocalDate();   //，获取之后，将year month day转换成唯一值value
}
//日期转唯一值的函数，为计算当前日期所用
void Date::DateTounique_valueForLocalDate()
{
	Local_date.value = 0;  //清空它 
	for (int i = 1940; i < Local_date.year; i++)    //从1940开始
	{
		if (IsLeapYear(i))   //是闰年+366 反之+365
			Local_date.value += 366;
		else
			Local_date.value += 365;
	}
	//年计算完了，计算该年是否是闰年，这关乎该年是否多一天
	if (IsLeapYear(Local_date.year))
	{
		for (int j = 0; j < Local_date.month - 1; j++)
		{
			Local_date.value += LeapYear[j];   //是的话加闰年数组
		}
	}
	else
	{
		for (int j = 0; j < Local_date.month - 1; j++)
		{
			Local_date.value += NotLeapYear[j];   //不是的话加非闰年数组
		}
	}
	Local_date.value += Local_date.day;   //最后把天数加上，因为这里得到的值是上一个月最后一天的值
}

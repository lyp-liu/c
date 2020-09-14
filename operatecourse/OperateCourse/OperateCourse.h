
// OperateCourse.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include<string>
using namespace std;
// COperateCourseApp:
// 有关此类的实现，请参阅 OperateCourse.cpp
//
extern string dqnum;
extern string nam;
class COperateCourseApp : public CWinApp
{
public:
	COperateCourseApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern COperateCourseApp theApp;
typedef struct node {
	string s_name;//学生姓名
	string s_id;//学号
	int s_banji;//班号
	int dqxuefen;//当前总学分
	string zhuanye;//专业

}Student[1000];
typedef struct Node {
	string t_name;//教师姓名
	string t_id;//教师工号
	string sub1;
	string sub2;
	string sub3;
	string sub4;
	string sub5;
	double avmyd=0;//平均满意度
}Teacher[100];
typedef struct snode {
	string id;//课程号
	double xuefen;
	int xueshi;
	string c_name;//课程名称
	string type;//课程类型
}Course[100];
typedef struct anode {
	string id;//所选课程id
	string name;//所选课程名称
	double xuefen;//所选课程学分
	string type;//课程类型
	int xueshi;
	int grade;
	string zhuren;//学生名
	string xh;//学生学号
}Stuinf[1000];
typedef struct enode {
	string teach;//老师姓名
	string stu;//学生姓名
	double score=0;//评分
	string pingjia;//评价
	double average;//平均分
}Manyidu[1000];
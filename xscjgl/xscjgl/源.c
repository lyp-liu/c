#include<stdio.h>
#include<string.h>
#include<Windows.h>
int shuju_num=0;//记录共有多少人的信息
typedef struct Node
{
	char id[10];//学号
	char name[15];
	int grade1;
	int grade2;
	int grade3;
	int grade4;
	int grade5;
	int allgrade;
	double average;
	
}Student[100];
Student student;
int strcomp(char a[], char b[]) {
	int lengtha = strlen(a);
	int lengthb = strlen(b);
	if (lengtha != lengthb)return 0;
	for (int i = 0; i < lengtha; i++) {
		if (a[i] == b[i])
			continue;
		else return 0;
	}
	return 1;
}

void addrecord() {//信息录入
	

	printf("请依次输入学号、姓名、成绩一~成绩五\n");
	scanf("%s%s%d%d%d%d%d", &student[shuju_num].id, student[shuju_num].name, &student[shuju_num].grade1, &student[shuju_num].grade2,& student[shuju_num].grade3, &student[shuju_num].grade4, &student[shuju_num].grade5);
	student[shuju_num].allgrade = student[shuju_num].grade1 + student[shuju_num].grade2 + student[shuju_num].grade3 + student[shuju_num].grade4 + student[shuju_num].grade5;
	student[shuju_num].average = (double)student[shuju_num].allgrade / 5;
	shuju_num++;
	printf("信息录入成功!");

}
void displayinf() {//信息显示
	printf("学号\t姓名\t成绩一\t成绩二\t成绩三\t成绩四\t成绩五\t总成绩\t平均成绩\n");
	for (int i = 0; i < shuju_num; i++) {
		printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%f\n", student[i].id, student[i].name, student[i].grade1, student[i].grade2, student[i].grade3, student[i].grade4, student[i].grade5, student[i].allgrade,student[i].average);
	}

}

int searchbyid() {//查询信息
	printf("请输入要查询/删除学生的学号");
	char y[10] = { 0 };
	scanf("%s", y);

	for (int i = 0; i < shuju_num; i++) {
		if (strcomp(y,student[i].id)) {
			printf("此同学信息为：\n");
			printf("学号\t姓名\t成绩一\t成绩二\t成绩三\t成绩四\t成绩五\t总成绩\t平均成绩\n");
			printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%f\n", student[i].id, student[i].name, student[i].grade1, student[i].grade2, student[i].grade3, student[i].grade4, student[i].grade5, student[i].allgrade, student[i].average);
			return i;
		}

	}
	printf("不存在此同学");
}
void deleteinf() {
	printf("请输入要删除的学生学号\n");
	char c[10];
	scanf("%s", c);
	for (int i = 0; i < shuju_num; i++) {
		if (strcomp(c, student[i].id)) {
			for (int j = i; j < shuju_num - 1; j++) {
				student[j] = student[j + 1];
			}
			shuju_num--;
		}

	}
	printf("删除成功\n");
}
void changeinf() {
	int a=searchbyid();
	printf("请输入修改后的学生学号、姓名、成绩一~成绩五\n");
	scanf("%s%s%d%d%d%d%d", &student[a].id, student[a].name, &student[a].grade1, &student[a].grade2, &student[a].grade3, &student[a].grade4, &student[a].grade5);
	student[a].allgrade = student[a].grade1 + student[a].grade2 + student[a].grade3 + student[a].grade4 + student[a].grade5;
	student[a].average = (double)student[a].allgrade / 5;
	printf("修改成功\n");
	
}
void sorts() {//冒泡排序
	for (int i = 0; i < shuju_num-1; i++) {
		for (int j = 0; j < shuju_num - i - 1; j++) {
			if (student[j].allgrade < student[j + 1].allgrade) {
				student[shuju_num] = student[j];
				student[j] = student[j + 1];
				student[j + 1] = student[shuju_num];
			}
		}
	}
	printf("排序后的学生信息如下：\n");
	displayinf();
}
int main() {
	while (1)  //循环界面
	{
		
		system("cls");
		printf("\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		printf("\t\t\t^^^^^^^^^^^^^^^^^欢迎您使用学生成绩管理系统^^^^^^^^^^^^^\n");
		printf("\t\t\t^^^^^^^^^^^^^^^^^^请选择您要实现的功能^^^^^^^^^^^^^^\n");
		printf("\t\t*********\t\t1、录入学生信息\t\t\t*********\n");
		printf("\t\t*********\t\t2、显示学生信息\t\t\t*********\n");
		printf("\t\t*********\t\t3、删除学生信息\t\t*********\n");
		printf("\t\t*********\t\t4、按学号查询学生信息\t*********\n");
		printf("\t\t*********\t\t5、修改学生信息\t*********\n");
		printf("\t\t*********\t\t6、学生信息排序\t*********\n");
		printf("\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		
		int y = 0;
		scanf("%d", &y);
		switch (y) {
		case 1:
			addrecord();
			break;
		case 2:
			displayinf();
			break;
		case 3:
			deleteinf();
			break;
		case 4:
			searchbyid();
			break;
		case 5:
			changeinf();
			break;
		case 6:
			sorts();
			break;

		}

		system("pause"); //暂停下

	}


}
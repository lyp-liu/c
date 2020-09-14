#include<stdio.h>
#include<string.h>
#include<Windows.h>
int shuju_num;//记录共有多少人的信息
typedef struct Node
{
	int id;//学号
	char name[15];
	int old;//年龄
	char sex[5];//性别
	char birth[15];
	char address[50];
	char num[15];//电话
	char mail[20];//Email
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
//按学号从大到小冒泡排序
void bigtosmall()
{
	for (int i = 0; i < shuju_num - 1; i++)
	{
		for (int j = 0; j < shuju_num - i - 1; j++)
		{
			if (student[j].id < student[j + 1].id)
			{
				int tempid, tempold;
				char tempname[15],tempsex[5],tempbirth[15],tempaddress[50],tempnum[15],tempmail[20];
				tempid = student[j].id;
				tempold = student[j].old;
				strcpy(tempname, student[j].name);
				strcpy(tempsex, student[j].sex);
				strcpy(tempbirth, student[j].birth);
				strcpy(tempaddress, student[j].address);
				strcpy(tempnum, student[j].num);
				strcpy(tempmail, student[j].mail);


				student[j].id = student[j + 1].id;
				student[j].old = student[j + 1].old;
				strcpy(student[j].name, student[j + 1].name);
				strcpy(student[j].sex, student[j + 1].sex);
				strcpy(student[j].birth, student[j + 1].birth);
				strcpy(student[j].address, student[j + 1].address);
				strcpy(student[j].num, student[j + 1].num);
				strcpy(student[j].mail, student[j + 1].mail);



				student[j + 1].id = tempid;
				student[j + 1].old = tempold;
				strcpy(student[j + 1].name, tempname);
				strcpy(student[j + 1].sex, tempsex);
				strcpy(student[j + 1].birth, tempbirth);
				strcpy(student[j + 1].address, tempaddress);
				strcpy(student[j + 1].num, tempnum);
				strcpy(student[j + 1].mail ,tempmail);
			}
		}
	}
}
void addrecord() {//信息录入
	FILE *out;
	out = fopen("information.txt", "ab+");
	if (out == NULL)
	{
		printf("Can't open the file!\n");
	}
	
	printf("请依次输入学号、姓名、年龄、性别、出生年月、地址、电话、E-mail\n");
	scanf("%d%s%d%s%s%s%s%s", &student[++shuju_num].id, student[shuju_num].name, &student[shuju_num].old, student[shuju_num].sex, student[shuju_num].birth, student[shuju_num].address, student[shuju_num].num, student[shuju_num].mail);
	fprintf(out, "%d\t%s\t%d\t%s\t%s\t%s\t%s\t%s\n", student[shuju_num].id, student[shuju_num].name, student[shuju_num].old, student[shuju_num].sex, student[shuju_num].birth, student[shuju_num].address, student[shuju_num].num, student[shuju_num].mail);
	
	fclose(out);
	printf("信息录入成功!");

}
void displayinf() {//信息显示
	printf("学号\t姓名\t年龄\t性别\t出生年月\t地址\t电话\tE-mail\n");
	for (int i = 0; i < shuju_num; i++) {
		printf("%d\t%s\t%d\t%s\t%s\t%s\t%s\t%s\n", student[i].id, student[i].name, student[i].old, student[i].sex, student[i].birth, student[i].address, student[i].num, student[i].mail);
	}

}
void sortbyid() {//按学号倒排

	bigtosmall();
	printf("学号\t姓名\t年龄\t性别\t出生年月\t地址\t电话\tE-mail\n");
	for (int i = 0; i < shuju_num; i++) {
		printf("%d\t%s\t%d\t%s\t%s\t%s\t%s\t%s\n", student[i].id, student[i].name, student[i].old, student[i].sex, student[i].birth, student[i].address, student[i].num, student[i].mail);
	}
}
int searchbyid() {//查询信息
	printf("请输入要查询学生的学号");
	int y=0;
	scanf("%d", &y);
	
	for (int i = 0; i < shuju_num; i++) {
		if (y == student[i].id) {
			printf("此同学信息为：\n");
			printf("学号\t姓名\t年龄\t性别\t出生年月\t地址\t电话\tE-mail\n");
			printf("%d\t%s\t%d\t%s\t%s\t%s\t%s\t%s\n", student[i].id, student[i].name, student[i].old, student[i].sex, student[i].birth, student[i].address, student[i].num, student[i].mail);
			return 1;
		}
		
	}
	printf("不存在此同学");
}

int searchbyname() {
	printf("请输入姓名");
	char y[15];
	scanf("%s", y);
	
	for (int i = 0; i < shuju_num; i++) {
		if (strcomp(y,student[i].name) ){
			printf("此同学信息为：\n");
			printf("学号\t姓名\t年龄\t性别\t出生年月\t地址\t电话\tE-mail\n");
			printf("%d\t%s\t%d\t%s\t%s\t%s\t%s\t%s\n", student[i].id, student[i].name, student[i].old, student[i].sex, student[i].birth, student[i].address, student[i].num, student[i].mail);
			return 1;
		}
		
		
	}
	printf("不存在此同学");
}

int main() {
	while (1)  //循环界面
	{
		shuju_num = 0;
		system("cls");
		printf("\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		printf("\t\t\t^^^^^^^^^^^^^^^^^欢迎您使用学生信息管理系统^^^^^^^^^^^^^\n");
		printf("\t\t\t^^^^^^^^^^^^^^^^^^请选择您要实现的功能^^^^^^^^^^^^^^\n");
		printf("\t\t*********\t\t1、录入学生信息\t\t\t*********\n");
		printf("\t\t*********\t\t2、显示学生信息\t\t\t*********\n");
		printf("\t\t*********\t\t3、按学号从大到小对学生信息排序\t\t*********\n");
		printf("\t\t*********\t\t4、按学号查询学生信息\t*********\n");
		printf("\t\t*********\t\t5、按姓名查询学生信息\t*********\n");
		printf("\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		int e;
		FILE *dq;

		dq = fopen("information.txt", "rb");
		if (dq)
		{
			while ((e = fgetc(dq)) != EOF)
				if (e == '\n') shuju_num++;
			
			fclose(dq);
		}
		shuju_num--;

		FILE *file = fopen("information.txt", "r");
		if (file == NULL) {
			printf("open error!\n");
			return 0;
		}
		fscanf(file, "%*[^\n]");  //跳过第一行文字
		for (int i = 0; i <= shuju_num-1; i++) {
			fscanf(file,"%d%s%d%s%s%s%s%s\n", &student[i].id, student[i].name, &student[i].old, student[i].sex, student[i].birth, student[i].address, student[i].num, student[i].mail);
			
		}
		fclose(file);
		int y=0;
		scanf("%d", &y);
		switch (y) {
		case 1:
			addrecord();
			break;
		case 2:
			displayinf();
			break;
		case 3:
			sortbyid();
			break;
		case 4:
			searchbyid();
			break;
		case 5:
			searchbyname();
			break;
		case 6:
			break;
		
		}
		
		system("pause"); //暂停下
	
	}


}
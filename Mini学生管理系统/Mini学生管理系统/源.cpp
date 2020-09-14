#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
typedef struct Node {//结构体
	char id[12];//学号
	char name[50];//姓名
	int grade1;
	int grade2;
	int grade3;
	int cishu;//点名次数
}Student[100];
Student student;
int lines = 0;//保存数据个数
int max_grade1 = 0;//最高分
int min_grade1 = 999;//最低分
void function_1() {
	
	srand(time(NULL));
		int num=rand() % lines;
		int jishu = 0;
		for (int i = 0; i < lines; i++) {
			if (student[num].cishu > student[i].cishu)
				jishu++;
		}
		if (jishu > (lines / 3)) {//当前同学被点名次数大于三分之一人的时候重新点名
			Sleep(300);
			function_1();
		}	
	printf("被点名的同学为：\n");
	printf("%s\n", student[num].name);
	student[num].cishu++;
	FILE *infile;
	infile = fopen("students.txt", "w");
	for (int i = 0; i < lines; i++) {
		fprintf(infile, "%s\t", student[i].id);
		fprintf(infile, "%s\t", student[i].name);
		fprintf(infile, "%d\t", student[i].grade1);
		fprintf(infile, "%d\t", student[i].grade2);
		fprintf(infile, "%d\t", student[i].grade3);
		fprintf(infile, "%d\n", student[i].cishu);
	}
	fclose(infile);
}
void function_2() {
	FILE *infile;
	infile = fopen("mResult.txt", "w");
	fprintf(infile, "最高分学生信息：\n学号：\t\t姓名：\t成绩1：\t成绩2：\t成绩3：\t被点名次数：\n");
	for (int i = 0; i < lines; i++) {
		if (student[i].grade1 == max_grade1) {
			fprintf(infile, "%s\t", student[i].id);
			fprintf(infile, "%s\t", student[i].name);
			fprintf(infile, "%d\t", student[i].grade1);
			fprintf(infile, "%d\t", student[i].grade2);
			fprintf(infile, "%d\t", student[i].grade3);
			fprintf(infile, "%d\n", student[i].cishu);
		}
	}
	fprintf(infile, "最低分学生信息：\n学号：\t\t姓名：\t成绩1：\t成绩2：\t成绩3：\t被点名次数：\n");
	for (int i = 0; i < lines; i++) {
		if (student[i].grade1 == min_grade1) {
			fprintf(infile, "%s\t", student[i].id);
			fprintf(infile, "%s\t", student[i].name);
			fprintf(infile, "%d\t", student[i].grade1);
			fprintf(infile, "%d\t", student[i].grade2);
			fprintf(infile, "%d\t", student[i].grade3);
			fprintf(infile, "%d\n", student[i].cishu);
		}
	}
	fclose(infile);
	printf("输出到文件成功！\n");
}
int input_command() {
	int y(0);
	scanf("%d", &y);
	switch (y) {
	case 1:
		function_1();
		return 1;
		break;
	case 2:
		function_2();
		return 1;
		break;
	case 3:
		return 0;
	}
}

int main() {
	while (1) {
		system("cls");
		lines = 0;
		printf("\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		printf("\t\t\t^^^^^^^^^^^^^^^^^欢迎您使用Mini学生管理系统^^^^^^^^^^^^^\n");
		printf("\t\t\t^^^^^^^^^^^^^^^^^^请选择您要实现的功能^^^^^^^^^^^^^^\n");
		printf("\t\t*********\t\t1、点名\t\t\t\t*********\n");
		printf("\t\t*********\t\t2、输出最高分最低分学生\t\t*********\n");
		printf("\t\t*********\t\t3、退出系统\t\t\t*********\n");
		int c;
		FILE *fp;
		fp = fopen("students.txt", "rb");
		if (fp)//计算数据总共多少行
		{
			while ((c = fgetc(fp)) != EOF) {
				if (c == '\n')
					lines++;
			}
			fclose(fp);
		}
		
		FILE *infile;
		infile=fopen("students.txt","r");
		for (int i = 0; i < lines; i++) {
			fscanf(infile, "%s", student[i].id);
			fscanf(infile, "%s", student[i].name);
			fscanf(infile, "%d", &student[i].grade1);
			fscanf(infile, "%d", &student[i].grade2);
			fscanf(infile, "%d", &student[i].grade3);
			fscanf(infile, "%d", &student[i].cishu);
			if (max_grade1 < student[i].grade1)
				max_grade1 = student[i].grade1;
			if (min_grade1 > student[i].grade1)
				min_grade1 = student[i].grade1;
		}
		fclose(infile);
		int f = input_command(); //输入命令
		if (f == 0)break;
		printf( "是否返回主菜单Y/N\n");
		char choice;
		scanf(" %c", &choice);
		if (choice == 'N' || choice == 'n') {
			break;
		}
	}
}
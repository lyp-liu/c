#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
typedef struct Node {//�ṹ��
	char id[12];//ѧ��
	char name[50];//����
	int grade1;
	int grade2;
	int grade3;
	int cishu;//��������
}Student[100];
Student student;
int lines = 0;//�������ݸ���
int max_grade1 = 0;//��߷�
int min_grade1 = 999;//��ͷ�
void function_1() {
	
	srand(time(NULL));
		int num=rand() % lines;
		int jishu = 0;
		for (int i = 0; i < lines; i++) {
			if (student[num].cishu > student[i].cishu)
				jishu++;
		}
		if (jishu > (lines / 3)) {//��ǰͬѧ������������������֮һ�˵�ʱ�����µ���
			Sleep(300);
			function_1();
		}	
	printf("��������ͬѧΪ��\n");
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
	fprintf(infile, "��߷�ѧ����Ϣ��\nѧ�ţ�\t\t������\t�ɼ�1��\t�ɼ�2��\t�ɼ�3��\t������������\n");
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
	fprintf(infile, "��ͷ�ѧ����Ϣ��\nѧ�ţ�\t\t������\t�ɼ�1��\t�ɼ�2��\t�ɼ�3��\t������������\n");
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
	printf("������ļ��ɹ���\n");
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
		printf("\t\t\t^^^^^^^^^^^^^^^^^��ӭ��ʹ��Miniѧ������ϵͳ^^^^^^^^^^^^^\n");
		printf("\t\t\t^^^^^^^^^^^^^^^^^^��ѡ����Ҫʵ�ֵĹ���^^^^^^^^^^^^^^\n");
		printf("\t\t*********\t\t1������\t\t\t\t*********\n");
		printf("\t\t*********\t\t2�������߷���ͷ�ѧ��\t\t*********\n");
		printf("\t\t*********\t\t3���˳�ϵͳ\t\t\t*********\n");
		int c;
		FILE *fp;
		fp = fopen("students.txt", "rb");
		if (fp)//���������ܹ�������
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
		int f = input_command(); //��������
		if (f == 0)break;
		printf( "�Ƿ񷵻����˵�Y/N\n");
		char choice;
		scanf(" %c", &choice);
		if (choice == 'N' || choice == 'n') {
			break;
		}
	}
}
#include<stdio.h>
#include<string.h>
#include<Windows.h>
int shuju_num=0;//��¼���ж����˵���Ϣ
typedef struct Node
{
	char id[10];//ѧ��
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

void addrecord() {//��Ϣ¼��
	

	printf("����������ѧ�š��������ɼ�һ~�ɼ���\n");
	scanf("%s%s%d%d%d%d%d", &student[shuju_num].id, student[shuju_num].name, &student[shuju_num].grade1, &student[shuju_num].grade2,& student[shuju_num].grade3, &student[shuju_num].grade4, &student[shuju_num].grade5);
	student[shuju_num].allgrade = student[shuju_num].grade1 + student[shuju_num].grade2 + student[shuju_num].grade3 + student[shuju_num].grade4 + student[shuju_num].grade5;
	student[shuju_num].average = (double)student[shuju_num].allgrade / 5;
	shuju_num++;
	printf("��Ϣ¼��ɹ�!");

}
void displayinf() {//��Ϣ��ʾ
	printf("ѧ��\t����\t�ɼ�һ\t�ɼ���\t�ɼ���\t�ɼ���\t�ɼ���\t�ܳɼ�\tƽ���ɼ�\n");
	for (int i = 0; i < shuju_num; i++) {
		printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%f\n", student[i].id, student[i].name, student[i].grade1, student[i].grade2, student[i].grade3, student[i].grade4, student[i].grade5, student[i].allgrade,student[i].average);
	}

}

int searchbyid() {//��ѯ��Ϣ
	printf("������Ҫ��ѯ/ɾ��ѧ����ѧ��");
	char y[10] = { 0 };
	scanf("%s", y);

	for (int i = 0; i < shuju_num; i++) {
		if (strcomp(y,student[i].id)) {
			printf("��ͬѧ��ϢΪ��\n");
			printf("ѧ��\t����\t�ɼ�һ\t�ɼ���\t�ɼ���\t�ɼ���\t�ɼ���\t�ܳɼ�\tƽ���ɼ�\n");
			printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%f\n", student[i].id, student[i].name, student[i].grade1, student[i].grade2, student[i].grade3, student[i].grade4, student[i].grade5, student[i].allgrade, student[i].average);
			return i;
		}

	}
	printf("�����ڴ�ͬѧ");
}
void deleteinf() {
	printf("������Ҫɾ����ѧ��ѧ��\n");
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
	printf("ɾ���ɹ�\n");
}
void changeinf() {
	int a=searchbyid();
	printf("�������޸ĺ��ѧ��ѧ�š��������ɼ�һ~�ɼ���\n");
	scanf("%s%s%d%d%d%d%d", &student[a].id, student[a].name, &student[a].grade1, &student[a].grade2, &student[a].grade3, &student[a].grade4, &student[a].grade5);
	student[a].allgrade = student[a].grade1 + student[a].grade2 + student[a].grade3 + student[a].grade4 + student[a].grade5;
	student[a].average = (double)student[a].allgrade / 5;
	printf("�޸ĳɹ�\n");
	
}
void sorts() {//ð������
	for (int i = 0; i < shuju_num-1; i++) {
		for (int j = 0; j < shuju_num - i - 1; j++) {
			if (student[j].allgrade < student[j + 1].allgrade) {
				student[shuju_num] = student[j];
				student[j] = student[j + 1];
				student[j + 1] = student[shuju_num];
			}
		}
	}
	printf("������ѧ����Ϣ���£�\n");
	displayinf();
}
int main() {
	while (1)  //ѭ������
	{
		
		system("cls");
		printf("\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		printf("\t\t\t^^^^^^^^^^^^^^^^^��ӭ��ʹ��ѧ���ɼ�����ϵͳ^^^^^^^^^^^^^\n");
		printf("\t\t\t^^^^^^^^^^^^^^^^^^��ѡ����Ҫʵ�ֵĹ���^^^^^^^^^^^^^^\n");
		printf("\t\t*********\t\t1��¼��ѧ����Ϣ\t\t\t*********\n");
		printf("\t\t*********\t\t2����ʾѧ����Ϣ\t\t\t*********\n");
		printf("\t\t*********\t\t3��ɾ��ѧ����Ϣ\t\t*********\n");
		printf("\t\t*********\t\t4����ѧ�Ų�ѯѧ����Ϣ\t*********\n");
		printf("\t\t*********\t\t5���޸�ѧ����Ϣ\t*********\n");
		printf("\t\t*********\t\t6��ѧ����Ϣ����\t*********\n");
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

		system("pause"); //��ͣ��

	}


}
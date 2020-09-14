#include<stdio.h>
#include<string.h>
#include<Windows.h>
int shuju_num;//��¼���ж����˵���Ϣ
typedef struct Node
{
	int id;//ѧ��
	char name[15];
	int old;//����
	char sex[5];//�Ա�
	char birth[15];
	char address[50];
	char num[15];//�绰
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
//��ѧ�ŴӴ�Сð������
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
void addrecord() {//��Ϣ¼��
	FILE *out;
	out = fopen("information.txt", "ab+");
	if (out == NULL)
	{
		printf("Can't open the file!\n");
	}
	
	printf("����������ѧ�š����������䡢�Ա𡢳������¡���ַ���绰��E-mail\n");
	scanf("%d%s%d%s%s%s%s%s", &student[++shuju_num].id, student[shuju_num].name, &student[shuju_num].old, student[shuju_num].sex, student[shuju_num].birth, student[shuju_num].address, student[shuju_num].num, student[shuju_num].mail);
	fprintf(out, "%d\t%s\t%d\t%s\t%s\t%s\t%s\t%s\n", student[shuju_num].id, student[shuju_num].name, student[shuju_num].old, student[shuju_num].sex, student[shuju_num].birth, student[shuju_num].address, student[shuju_num].num, student[shuju_num].mail);
	
	fclose(out);
	printf("��Ϣ¼��ɹ�!");

}
void displayinf() {//��Ϣ��ʾ
	printf("ѧ��\t����\t����\t�Ա�\t��������\t��ַ\t�绰\tE-mail\n");
	for (int i = 0; i < shuju_num; i++) {
		printf("%d\t%s\t%d\t%s\t%s\t%s\t%s\t%s\n", student[i].id, student[i].name, student[i].old, student[i].sex, student[i].birth, student[i].address, student[i].num, student[i].mail);
	}

}
void sortbyid() {//��ѧ�ŵ���

	bigtosmall();
	printf("ѧ��\t����\t����\t�Ա�\t��������\t��ַ\t�绰\tE-mail\n");
	for (int i = 0; i < shuju_num; i++) {
		printf("%d\t%s\t%d\t%s\t%s\t%s\t%s\t%s\n", student[i].id, student[i].name, student[i].old, student[i].sex, student[i].birth, student[i].address, student[i].num, student[i].mail);
	}
}
int searchbyid() {//��ѯ��Ϣ
	printf("������Ҫ��ѯѧ����ѧ��");
	int y=0;
	scanf("%d", &y);
	
	for (int i = 0; i < shuju_num; i++) {
		if (y == student[i].id) {
			printf("��ͬѧ��ϢΪ��\n");
			printf("ѧ��\t����\t����\t�Ա�\t��������\t��ַ\t�绰\tE-mail\n");
			printf("%d\t%s\t%d\t%s\t%s\t%s\t%s\t%s\n", student[i].id, student[i].name, student[i].old, student[i].sex, student[i].birth, student[i].address, student[i].num, student[i].mail);
			return 1;
		}
		
	}
	printf("�����ڴ�ͬѧ");
}

int searchbyname() {
	printf("����������");
	char y[15];
	scanf("%s", y);
	
	for (int i = 0; i < shuju_num; i++) {
		if (strcomp(y,student[i].name) ){
			printf("��ͬѧ��ϢΪ��\n");
			printf("ѧ��\t����\t����\t�Ա�\t��������\t��ַ\t�绰\tE-mail\n");
			printf("%d\t%s\t%d\t%s\t%s\t%s\t%s\t%s\n", student[i].id, student[i].name, student[i].old, student[i].sex, student[i].birth, student[i].address, student[i].num, student[i].mail);
			return 1;
		}
		
		
	}
	printf("�����ڴ�ͬѧ");
}

int main() {
	while (1)  //ѭ������
	{
		shuju_num = 0;
		system("cls");
		printf("\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		printf("\t\t\t^^^^^^^^^^^^^^^^^��ӭ��ʹ��ѧ����Ϣ����ϵͳ^^^^^^^^^^^^^\n");
		printf("\t\t\t^^^^^^^^^^^^^^^^^^��ѡ����Ҫʵ�ֵĹ���^^^^^^^^^^^^^^\n");
		printf("\t\t*********\t\t1��¼��ѧ����Ϣ\t\t\t*********\n");
		printf("\t\t*********\t\t2����ʾѧ����Ϣ\t\t\t*********\n");
		printf("\t\t*********\t\t3����ѧ�ŴӴ�С��ѧ����Ϣ����\t\t*********\n");
		printf("\t\t*********\t\t4����ѧ�Ų�ѯѧ����Ϣ\t*********\n");
		printf("\t\t*********\t\t5����������ѯѧ����Ϣ\t*********\n");
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
		fscanf(file, "%*[^\n]");  //������һ������
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
		
		system("pause"); //��ͣ��
	
	}


}
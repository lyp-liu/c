#include<stdio.h>
#include<Windows.h>
#include<string.h>
#include"��ͷ.h"
bool strcompare(char a[], char b[]) {//�Ƚ��ַ���
	int la = strlen(a);
	int lb = strlen(b);
	if (la != lb)return false;
	for (int i = 0; i < la; i++) {
		if (a[i] == b[i])
			continue;
		else return false;
	}
	return true;
}
void function_1()
{
	printf("����\t\t����\t��������\t\t��������\tͼ�����\t�������λ��\tͼ������\tͼ��״̬\n");
	for (int i = 0; i < lines; i++) {
		printf("%s\t%s\t%s\t%s\t\t%s\t\t%s\t%s\t\t%s\n", book[i].bookname, book[i].author, book[i].cbsname, book[i].date, book[i].type, book[i].locate, book[i].id, book[i].biaozhi);
	}
	system("pause");
}
void function_2() {
	printf("������Ҫ���ҵ�����:");
	char bkname[50];
	scanf("%s", bkname); char temp[50];
	printf("����\t\t����\t��������\t��������\tͼ�����\t�������λ��\tͼ������\t�Ƿ񱻽���\n");
	for (int i = 0; i < lines; i++) {
		if (strcompare(book[i].bookname, bkname)) {
			printf("%s\t%s\t%s\t%s\t%s\t\t%s\t%s\t\t%s\n", book[i].bookname, book[i].author, book[i].cbsname, book[i].date, book[i].type, book[i].locate, book[i].id, book[i].biaozhi);
		}
	}
	system("pause");
}
void function_3() {
	printf("������Ҫ���ҵ�������:");
	char atname[50];
	scanf("%s", atname); char temp[50];
	printf("����\t\t����\t��������\t��������\tͼ�����\t�������λ��\tͼ������\t�Ƿ񱻽���\n");
	for (int i = 0; i < lines; i++) {
		if (strcompare(book[i].author, atname)) {
			printf("%s\t%s\t%s\t%s\t%s\t\t%s\t%s\t\t%s\n", book[i].bookname, book[i].author, book[i].cbsname, book[i].date, book[i].type, book[i].locate, book[i].id, book[i].biaozhi);
		}
	}
	system("pause");
}
void function_4() {//���ͼ��
	while (1) {
		printf("�������������������ߡ������������������ڡ�ͼ������������λ�á�ͼ�����롢�Ƿ񱻽���\n");
		scanf("%s%s%s%s%s%s%s%s", book[lines].bookname, book[lines].author, book[lines].cbsname, book[lines].date, book[lines].type, book[lines].locate, book[lines].id, book[lines].biaozhi);
		lines++;
		printf("��ӳɹ���������������1,�˳�����0\n");
		int c;
		scanf("%d", &c);
		if (c ==0) {
			break;
		}
	}
	FILE *outfile;
	outfile = fopen("book.txt", "w");
	if (outfile == NULL)
	{
		printf("Can't open the file!\n");
	}
	for (int i = 0; i < lines; i++) {
		fprintf(outfile, "%s\t", book[i].bookname);
		fprintf(outfile, "%s\t", book[i].author);
		fprintf(outfile, "%s\t", book[i].cbsname);
		fprintf(outfile, "%s\t", book[i].date);
		fprintf(outfile, "%s\t", book[i].type);
		fprintf(outfile, "%s\t", book[i].locate);
		fprintf(outfile, "%s\t", book[i].id);
		fprintf(outfile, "%s\n", book[i].biaozhi);
	}
	fclose(outfile);
}
void function_5() {//ɾ��ͼ��
	printf("����������\n");
	char temp[50];
	scanf("%s", temp);
	for (int i = 0; i < lines; i++) {
		if (strcompare(book[i].bookname, temp)) {
			for (int j = i; j < lines - 1; j++) {
				strcpy(book[j].bookname , book[1 + j].bookname);
				strcpy(book[j].author, book[1+j].author);
				strcpy(book[j].biaozhi, book[j+1].biaozhi);
				strcpy(book[j].cbsname, book[j+1].cbsname);
				strcpy(book[j].date, book[j+1].date);
				strcpy(book[j].id, book[j+1].id);
				strcpy(book[j].locate, book[j+1].locate);
				strcpy(book[j].type, book[j+1].type);
			}
			lines--;
			break;
		}
	}
	FILE *outfile;
	outfile = fopen("book.txt", "w");
	if (outfile == NULL)
	{
		printf("Can't open the file!\n");
	}
	for (int i = 0; i < lines; i++) {
		fprintf(outfile, "%s\t", book[i].bookname);
		fprintf(outfile, "%s\t", book[i].author);
		fprintf(outfile, "%s\t", book[i].cbsname);
		fprintf(outfile, "%s\t", book[i].date);
		fprintf(outfile, "%s\t", book[i].type);
		fprintf(outfile, "%s\t", book[i].locate);
		fprintf(outfile, "%s\t", book[i].id);
		fprintf(outfile, "%s\n", book[i].biaozhi);
	}
	fclose(outfile);
	printf("ɾ���ɹ�");
	system("pause");
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
		function_3();
		return 1;
		break;
	case 4:
		function_4();
		return 1;
		break;
	case 5:
		function_5();
		return 1;
		break;
	case 6:
		return 0;
	default:
		printf("�������!����������!");
	}
}
int main() {
	while (1)  //ѭ������
	{
		lines = 0;
		system("cls");
		printf("\t\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		printf("\t\t\t^^^^^^^^^^^^^^^^^��ӭ��ʹ��ͼ��ݽ���ϵͳ^^^^^^^^^^^^^\n");
		printf("\t\t\t^^^^^^^^^^^^^^^^^^��ѡ����Ҫʵ�ֵĹ���^^^^^^^^^^^^^^\n");
		printf("\t\t*********\t\t1����ʾ�������ͼ��*********\n");
		printf("\t\t*********\t\t2������������ͼ��\t\t\t*********\n");
		printf("\t\t*********\t\t3�������߲���ͼ��\t\t\t*********\n");
		printf("\t\t*********\t\t4�����ͼ��\t\t\t*********\n");
		printf("\t\t*********\t\t5��ɾ��ͼ��\t*********\n");
		printf("\t\t*********\t\t6���˳�ϵͳ\t*********\n");
		int c;
		FILE *fp;
		fp = fopen("book.txt", "rb");
		if (fp)//���������ܹ�������
		{
			while ((c = fgetc(fp)) != EOF) {
				if (c == '\n')
					lines++;
			}
			fclose(fp);
		}
		lines++;
		FILE *file = fopen("book.txt", "r");
		if (file == NULL) {
			printf("open error!\n");
			return 0;
		}
		//��ȡ����
		for (int i = 0; i < lines; i++) {
			fscanf(file, "%s", book[i].bookname);
			fscanf(file, "%s", book[i].author);
			fscanf(file, "%s", book[i].cbsname);
			fscanf(file, "%s", book[i].date);
			fscanf(file, "%s", book[i].type);
			fscanf(file, "%s", book[i].locate);
		
			fscanf(file, "%s", book[i].id);
			fscanf(file, "%s\n", book[i].biaozhi);
			
		}
		fclose(file);
		int a=input_command(); //��������
		if (a == 0)break;
		printf("\n");
		
	}
	return 0;
}
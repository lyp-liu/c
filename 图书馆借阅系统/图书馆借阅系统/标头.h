#pragma once
#include<stdio.h>
typedef struct Tushu {
	char bookname[50];//����
	char author[15];//����
	char cbsname[100];//��������
	char date[15];//��������
	char type[15];//ͼ�����
	char locate[30];//�������λ��
	char  id[15];//ͼ�������
	char biaozhi[15];//��־�Ƿ񱻽���
}Book[1000];
Book book;
int lines = 0;//���ж��ٱ���
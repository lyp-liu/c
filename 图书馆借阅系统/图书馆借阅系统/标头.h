#pragma once
#include<stdio.h>
typedef struct Tushu {
	char bookname[50];//书名
	char author[15];//作者
	char cbsname[100];//出版社名
	char date[15];//出版日期
	char type[15];//图书类别
	char locate[30];//所在书架位置
	char  id[15];//图书条码号
	char biaozhi[15];//标志是否被借走
}Book[1000];
Book book;
int lines = 0;//共有多少本书
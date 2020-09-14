
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void Function1();
void Function2();
void Function3();
void Function4();
struct student {
	char name[20];
	char sex[3];
	int score;
	int num;
};
struct student stu[1001];
int main() {
	int n, m;
	char c;
	m = 1;
	while (m) {
		puts("******************");
		puts("\t1.查询录取分数线；2.查询各批次男女比例");
		puts("\t3.查看各批次录取情况：4.输入考生考号或姓名查询录取情况****");
		puts("******************");
		printf("输入选择：");
		scanf("%d", &n);
		getchar();
		switch (n) {
		case 1:
			Function1();
			break;
		case 2:
			Function2();
			break;
		case 3:
			Function3();
			break;
		case 4:
			Function4();
			break;
		printf("继续选择Y，退出选择N");
		scanf("%c", &c);
		if (c == 'y' || c == 'Y') {
			m = 1;
		}
		else m = 0;
		printf("\n");
		}
	}
	return 0;
}
void Function1() {
	//struct student stu[1000];
	int i=0, j, k;
	struct student t;
	FILE *fp= fopen("f1.txt","r");
	
	if (fp == NULL) {
		printf("open error!\n");
		return 0;
	}
	for (k = 0; k < 1000; k++) {
		
	
		fscanf(fp,"%d%s%s%d",&stu[k].num,stu[k].name,stu[k].sex,&stu[k].score);

	}
	fclose(fp);
	for (j = 0; j < 999; j++) {
		for (i = 0; i < 999 - j; i++) {
			if (stu[i].score > stu[i + 1].score) {
				t = stu[i];
				stu[i] = stu[i + 1];
				stu[i + 1] = t;
			}
		}
	}
	printf("一类本科分数线：\n");
	printf("%d\n", stu[899].score);
	printf("二类本科分数线：\n");
	printf("%d\n", stu[749].score);
	printf("三类本科分数线：\n");
	printf("%d\n", stu[549].score);
	printf("四类高职高专分数线：\n");
	printf("%d\n", stu[399].score);
	FILE *out;
	out = fopen("f2.txt", "w");
	if (out == NULL)
	{
		printf("Can't open the file!\n");
	}
	fprintf(out, "一类本科分数线：\n%d\n", stu[899].score);
	fprintf(out, "二类本科分数线：\n%d\n", stu[749].score);
	fprintf(out, "三类本科分数线：\n%d\n", stu[459].score);
	fprintf(out, "四类高职高专分数线：\n%d\n", stu[399].score);
	fclose(out);
	printf("信息已输出到文档中\n");
}
void Function2() {
	FILE *fp;
	fp = fopen("f1.txt", "r");
	struct student t;
	int i, j, m;
	for (i = 0; i < 1000; i++) {
		fscanf(fp,"%d%s%s%d", &stu[i].num, stu[i].name, stu[i].sex, &stu[i].score);
	}
	
	for (j = 0; j < 999; j++) {
		for (i = 0; i < 999 - j; i++) {
			if (stu[i].score > stu[i+1].score) {
				t = stu[i];
				stu[i] = stu[i + 1];
				stu[i + 1] = t;
			}
		}
	}
	int a, b, c, d, e, f, g, h;
	a = b = c = d = e = f = g = h = 0;
	for (m = 899; m <= 999; m++) {
		if (strcmp(stu[m].sex, "男") == 0)
			a++;
	}
	b = 100 - a;
	FILE *out;
	out = fopen("f3.txt", "w");
	if (out == NULL)
	{
		printf("Can't open the file!\n");
	}
	fprintf(out, "一类本科男生：女生：\n%d %d\n", a, b);
	printf("一类本科男生：女生：\n");
	printf("%d %d\n", a, b);
	for (m = 749; m < 899;m++) {
		if (strcmp(stu[m].sex, "男") == 0)
			c++;
	}
	d = 150 - c;
	fprintf(out, "二类本科男生：女生：\n%d %d\n", c, d);
	printf("二类本科男生：女生：\n");
	printf("%d %d\n", c, d);
	for (m = 549; m < 749; m++) {
		if (strcmp(stu[m].sex, "男") == 0)
			e++;
	}
	f = 200 - e;
	fprintf(out, "三类本科男生：女生：\n%d %d\n",e, f);
	printf("三类本科男生：女生：\n");
	printf("%d %d\n", e, f);
	for (m = 399; m < 549; m++) {
		if (strcmp(stu[m].sex, "男") == 0)
			g++;
	}
	h = 200 - g;
	fprintf(out, "高职高专男生：女生：\n%d %d\n", g, h);
	printf("高职高专男生：女生：\n");
	printf("%d %d\n", g, h);
	fclose(out);
	printf("信息已输出到文档中\n");
}
void Function3() {
	FILE *fp;
	fp = fopen("f1.txt", "r");
	struct student t;
	int i, j;
	for (i = 0; i < 1000; i++) {
		fscanf(fp, "%d%s%s%d", &stu[i].num, stu[i].name, stu[i].sex, &stu[i].score);
	}
	for (j = 0; j < 999; j++) {
		for (i = 0; i < 999 - j; i++) {
			if (stu[i].score > stu[i+1].score) {
				t = stu[i];
				stu[i] = stu[i + 1];
				stu[i + 1] = t;
			}
		}
	}
	for (i = 0; i < 1000; i++) {
		if (stu[i].score > stu[899].score)
			printf("%s被本一学校录取\n", stu[i].name);
		if(stu[i].score>stu[749].score&&stu[i].score<stu[899].score)
			printf("%s被本二学校录取\n", stu[i].name);
		if (stu[i].score > stu[549].score&&stu[i].score < stu[749].score)
			printf("%s被本三学校录取\n", stu[i].name);
		if (stu[i].score > stu[399].score&&stu[i].score < stu[549].score)
			printf("%s被高职高专学校录取\n", stu[i].name);
		else if (stu[i].score < stu[399].score)
			printf("%s未被录取\n", stu[i].name);
	}
}
void Function4() {
	FILE *fp;
	fp = fopen("f1.txt", "r");
	struct student t;
	int i, j, h,k;
	for (i = 0; i < 1000; i++) {
		fscanf(fp, "%d%s%s%d", &stu[i].num, stu[i].name, stu[i].sex, &stu[i].score);
	}
	for (j = 0; j < 999; j++) {
		for (i = 0; i < 999 - j; i++) {
			if (stu[i].score > stu[i+1].score) {
				t = stu[i];
				stu[i] = stu[i + 1];
				stu[i + 1] = t;
			}
		}
	}
	char m[20];
	puts("****1.根据考号查询：2.根据姓名查询****");
	printf("输入选择：");
	scanf("%d", &h);
	getchar();
	switch (h) {
	case 1:{
		printf("请输入考生考号");
		scanf("%ld", &h);
		for (i = 0; i < 1000; i++) 
			if (h == stu[i].num) {
				printf("%ld %s %s %d\n", stu[i].num, stu[i].name, stu[i].sex, stu[i].score);
				if (stu[i].score > stu[899].score)
					printf("%s被本一学校录取\n", stu[i].name);
				if (stu[i].score > stu[749].score&&stu[i].score < stu[899].score)
					printf("%s被本二学校录取\n", stu[i].name);
				if (stu[i].score > stu[549].score&&stu[i].score < stu[749].score)
					printf("%s被本三学校录取\n", stu[i].name);
				if (stu[i].score > stu[399].score&&stu[i].score < stu[549].score)
					printf("%s被高职高专学校录取\n", stu[i].name);
				if (stu[i].score < stu[399].score)
					printf("%s未被录取\n", stu[i].name);
				break;
			}
			if (h != stu[i].num)
				printf("输入的考号有误\n");
			
		}
		break;
	case 2: {
		printf("输入考生姓名：");
		scanf("%s", &m);
		for(k=0;k<1000;k++)
			if (strcmp(m, stu[k].name) == 0) {
				printf("%ld %s %s %d\n", stu[k].num, stu[k].name, stu[k].sex, stu[k].score);
				if (stu[k].score > stu[899].score)
					printf("%s被本一学校录取\n", stu[k].name);
				if (stu[k].score > stu[749].score&&stu[k].score < stu[899].score)
					printf("%s被本二学校录取\n", stu[k].name);
				if (stu[k].score > stu[549].score&&stu[k].score < stu[749].score)
					printf("%s被本三学校录取\n", stu[k].name);
				if (stu[k].score > stu[399].score&&stu[k].score < stu[549].score)
					printf("%s被高职高专学校录取\n", stu[k].name);
				else if (stu[k].score < stu[399].score)
					printf("%s未被录取\n", stu[k].name);
				break;
			}
		if (strcmp(m,stu[k].name)!=0)
			printf("输入的姓名有误\n");
		break;
		}
	}
}
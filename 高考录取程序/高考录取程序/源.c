
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
		puts("\t1.��ѯ¼ȡ�����ߣ�2.��ѯ��������Ů����");
		puts("\t3.�鿴������¼ȡ�����4.���뿼�����Ż�������ѯ¼ȡ���****");
		puts("******************");
		printf("����ѡ��");
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
		printf("����ѡ��Y���˳�ѡ��N");
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
	printf("һ�౾�Ʒ����ߣ�\n");
	printf("%d\n", stu[899].score);
	printf("���౾�Ʒ����ߣ�\n");
	printf("%d\n", stu[749].score);
	printf("���౾�Ʒ����ߣ�\n");
	printf("%d\n", stu[549].score);
	printf("�����ְ��ר�����ߣ�\n");
	printf("%d\n", stu[399].score);
	FILE *out;
	out = fopen("f2.txt", "w");
	if (out == NULL)
	{
		printf("Can't open the file!\n");
	}
	fprintf(out, "һ�౾�Ʒ����ߣ�\n%d\n", stu[899].score);
	fprintf(out, "���౾�Ʒ����ߣ�\n%d\n", stu[749].score);
	fprintf(out, "���౾�Ʒ����ߣ�\n%d\n", stu[459].score);
	fprintf(out, "�����ְ��ר�����ߣ�\n%d\n", stu[399].score);
	fclose(out);
	printf("��Ϣ��������ĵ���\n");
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
		if (strcmp(stu[m].sex, "��") == 0)
			a++;
	}
	b = 100 - a;
	FILE *out;
	out = fopen("f3.txt", "w");
	if (out == NULL)
	{
		printf("Can't open the file!\n");
	}
	fprintf(out, "һ�౾��������Ů����\n%d %d\n", a, b);
	printf("һ�౾��������Ů����\n");
	printf("%d %d\n", a, b);
	for (m = 749; m < 899;m++) {
		if (strcmp(stu[m].sex, "��") == 0)
			c++;
	}
	d = 150 - c;
	fprintf(out, "���౾��������Ů����\n%d %d\n", c, d);
	printf("���౾��������Ů����\n");
	printf("%d %d\n", c, d);
	for (m = 549; m < 749; m++) {
		if (strcmp(stu[m].sex, "��") == 0)
			e++;
	}
	f = 200 - e;
	fprintf(out, "���౾��������Ů����\n%d %d\n",e, f);
	printf("���౾��������Ů����\n");
	printf("%d %d\n", e, f);
	for (m = 399; m < 549; m++) {
		if (strcmp(stu[m].sex, "��") == 0)
			g++;
	}
	h = 200 - g;
	fprintf(out, "��ְ��ר������Ů����\n%d %d\n", g, h);
	printf("��ְ��ר������Ů����\n");
	printf("%d %d\n", g, h);
	fclose(out);
	printf("��Ϣ��������ĵ���\n");
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
			printf("%s����һѧУ¼ȡ\n", stu[i].name);
		if(stu[i].score>stu[749].score&&stu[i].score<stu[899].score)
			printf("%s������ѧУ¼ȡ\n", stu[i].name);
		if (stu[i].score > stu[549].score&&stu[i].score < stu[749].score)
			printf("%s������ѧУ¼ȡ\n", stu[i].name);
		if (stu[i].score > stu[399].score&&stu[i].score < stu[549].score)
			printf("%s����ְ��רѧУ¼ȡ\n", stu[i].name);
		else if (stu[i].score < stu[399].score)
			printf("%sδ��¼ȡ\n", stu[i].name);
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
	puts("****1.���ݿ��Ų�ѯ��2.����������ѯ****");
	printf("����ѡ��");
	scanf("%d", &h);
	getchar();
	switch (h) {
	case 1:{
		printf("�����뿼������");
		scanf("%ld", &h);
		for (i = 0; i < 1000; i++) 
			if (h == stu[i].num) {
				printf("%ld %s %s %d\n", stu[i].num, stu[i].name, stu[i].sex, stu[i].score);
				if (stu[i].score > stu[899].score)
					printf("%s����һѧУ¼ȡ\n", stu[i].name);
				if (stu[i].score > stu[749].score&&stu[i].score < stu[899].score)
					printf("%s������ѧУ¼ȡ\n", stu[i].name);
				if (stu[i].score > stu[549].score&&stu[i].score < stu[749].score)
					printf("%s������ѧУ¼ȡ\n", stu[i].name);
				if (stu[i].score > stu[399].score&&stu[i].score < stu[549].score)
					printf("%s����ְ��רѧУ¼ȡ\n", stu[i].name);
				if (stu[i].score < stu[399].score)
					printf("%sδ��¼ȡ\n", stu[i].name);
				break;
			}
			if (h != stu[i].num)
				printf("����Ŀ�������\n");
			
		}
		break;
	case 2: {
		printf("���뿼��������");
		scanf("%s", &m);
		for(k=0;k<1000;k++)
			if (strcmp(m, stu[k].name) == 0) {
				printf("%ld %s %s %d\n", stu[k].num, stu[k].name, stu[k].sex, stu[k].score);
				if (stu[k].score > stu[899].score)
					printf("%s����һѧУ¼ȡ\n", stu[k].name);
				if (stu[k].score > stu[749].score&&stu[k].score < stu[899].score)
					printf("%s������ѧУ¼ȡ\n", stu[k].name);
				if (stu[k].score > stu[549].score&&stu[k].score < stu[749].score)
					printf("%s������ѧУ¼ȡ\n", stu[k].name);
				if (stu[k].score > stu[399].score&&stu[k].score < stu[549].score)
					printf("%s����ְ��רѧУ¼ȡ\n", stu[k].name);
				else if (stu[k].score < stu[399].score)
					printf("%sδ��¼ȡ\n", stu[k].name);
				break;
			}
		if (strcmp(m,stu[k].name)!=0)
			printf("�������������\n");
		break;
		}
	}
}
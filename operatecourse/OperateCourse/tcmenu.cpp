// tcmenu.cpp: 实现文件
//

#include "stdafx.h"
#include "OperateCourse.h"
#include "tcmenu.h"
#include "afxdialogex.h"
#include<fstream>
#include<string>
#include<math.h>

using namespace std;

// tcmenu 对话框

IMPLEMENT_DYNAMIC(tcmenu, CDialogEx)

tcmenu::tcmenu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_tcmenu, pParent)
	, searchnm(_T(""))
	, searchxh(_T(""))
	, searchsub(_T(""))
	, xiaxian(0)
	, shangxian(0)
	, tjsub(_T(""))
	, avescore(0)
	, bzc(0)
	, jgl(0)
	, changescore(0)
	, changesub(_T(""))
	, addxh(_T(""))
	, addnm(_T(""))
	, addsub(_T(""))
	, adscore(0)
	, sortsub(_T(""))
{
	asdlg = NULL;
	myddlg = NULL;
}

tcmenu::~tcmenu()
{
	if (asdlg != NULL) {
		delete asdlg;
	}
	if (myddlg != NULL) {
		delete myddlg;
	}
}

void tcmenu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, searchnm);
	DDX_Text(pDX, IDC_EDIT2, searchxh);
	DDX_Control(pDX, IDC_LIST1, shuchu);
	DDX_Text(pDX, IDC_EDIT10, searchsub);
	DDX_Text(pDX, IDC_EDIT8, xiaxian);
	DDX_Text(pDX, IDC_EDIT9, shangxian);
	DDX_Text(pDX, IDC_EDIT4, tjsub);
	DDX_Text(pDX, IDC_EDIT5, avescore);
	DDX_Text(pDX, IDC_EDIT6, bzc);
	DDX_Text(pDX, IDC_EDIT7, jgl);
	DDX_Text(pDX, IDC_EDIT3, changescore);
	DDX_Text(pDX, IDC_EDIT11, changesub);
	DDX_Text(pDX, IDC_EDIT12, addxh);
	DDX_Text(pDX, IDC_EDIT13, addnm);
	DDX_Text(pDX, IDC_EDIT14, addsub);
	DDX_Text(pDX, IDC_EDIT15, adscore);
	DDX_Text(pDX, IDC_EDIT16, sortsub);
}


BEGIN_MESSAGE_MAP(tcmenu, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON1, &tcmenu::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &tcmenu::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &tcmenu::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &tcmenu::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &tcmenu::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &tcmenu::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON7, &tcmenu::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON6, &tcmenu::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &tcmenu::OnBnClickedButton8)
END_MESSAGE_MAP()


// tcmenu 消息处理程序





void tcmenu::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string tpxh, tpnm;
	tpxh = CT2A(searchxh.GetString());
	tpnm = CT2A(searchnm.GetString());
	for (int i = 0; i < 100; i++) {//删除表格中元素
		shuchu.DeleteColumn(0);
	}
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	shuchu.InsertColumn(1, _T("学号"), LVCFMT_LEFT, 100);
	shuchu.InsertColumn(2, _T("姓名"), LVCFMT_LEFT, 80);
	shuchu.InsertColumn(3, _T("课程名称"), LVCFMT_LEFT, 220);
	shuchu.InsertColumn(4, _T("分数"), LVCFMT_LEFT, 80);
	CString ID[50], NAME[50], SUB[50], GRADE[50];
	int e = 0;
	for (int i = 0; i < j; i++) {
		if (tpxh == stuinf[i].xh || tpnm == stuinf[i].zhuren) {
			ID[e] = stuinf[i].xh.c_str();
			NAME[e] = stuinf[i].zhuren.c_str();
			SUB[e] = stuinf[i].name.c_str();
			GRADE[e].Format(L"%d", stuinf[i].grade);
			shuchu.InsertItem(e, _T(""), 100);
			shuchu.SetItemText(e, 1, ID[e]);
			shuchu.SetItemText(e, 2, NAME[e]);
			shuchu.SetItemText(e, 3, SUB[e]);
			shuchu.SetItemText(e, 4, GRADE[e]);
		}
	}
}


BOOL tcmenu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	DWORD dwStyle = shuchu.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	shuchu.SetExtendedStyle(dwStyle);
	shuchu.InsertItem(0, _T(""), 0);
	for (int i=0; i < 40; i++) {
		shuchu.InsertItem(i, _T(""), 100);
	}
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	ifstream in;
	in.open("staff.txt");
	int i = 0;
	while (!in.eof()) {
		in >> tea[i].t_id >> tea[i].t_name >> tea[i].sub1
			>> tea[i].sub2 >> tea[i].sub3>> tea[i].sub4>> tea[i].sub5;
		i++;
	}
	i--;
	for (int m = 0; m< i; m++) {
		if (tea[m].t_id == dqnum) {
			tid = tea[m].t_id;
			tname = tea[m].t_name;
			t1 = tea[m].sub1;
			t2 = tea[m].sub2;
			t3 = tea[m].sub3;
			t4 = tea[m].sub4;
			t5 = tea[m].sub5;
		}
	}
	in.close();
	string tpid, tpnm, tpcourse;int  tpgrade;
	ifstream infile;
	infile.open("score.txt");
	while (1) {

		infile >> tpid >> tpnm >> tpcourse >> tpgrade;
		if (tpcourse == t1|| tpcourse == t2|| tpcourse == t3|| tpcourse == t4|| tpcourse == t5) {
			stuinf[j].xh = tpid;//保存与当前老师有关的学生课程信息
			stuinf[j].zhuren = tpnm;
			stuinf[j].name = tpcourse;//已知课程信息中的名称和分数
			stuinf[j].grade = tpgrade;
			j++;
		}
		else {
			tempid[jishu] = tpid;
			tempxm[jishu] = tpnm;
			tempcourse[jishu] = tpcourse;
			tempscore[jishu] = tpgrade;
			jishu++;
		}

		if (infile.eof())
			break;
	}
	infile.close();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void tcmenu::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string tpsub;//要查找的科目
	tpsub= CT2A(searchsub.GetString());
	for (int i = 0; i < 100; i++) {//删除表格中元素
		shuchu.DeleteColumn(0);
	}
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	shuchu.InsertColumn(1, _T("姓名"), LVCFMT_LEFT, 100);
	shuchu.InsertColumn(2, _T("成绩"), LVCFMT_LEFT, 100);
	int e = 0;
	CString NAME[50],GRADE[50];
	for (int m = 0; m < j; m++) {
		if (stuinf[m].name == tpsub && stuinf[m].grade > xiaxian&&stuinf[m].grade < shangxian) {
			GRADE[e].Format(L"%d", stuinf[m].grade);
				NAME[e]=stuinf[m].zhuren.c_str();
				shuchu.SetItemText(e, 1,NAME[e]);
			shuchu.SetItemText(e, 2, GRADE[e]);
			e++;
		}
	}
}
void tcmenu::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//先找出要修改的stuinf中的下标，然后修改
	string tpxh, tpnm,tpsub;
	tpxh = CT2A(searchxh.GetString());
	tpnm = CT2A(searchnm.GetString());
	tpsub = CT2A(changesub.GetString());
	for (int n = 0; n < j; n++) {//m为要找的下标
		if ((stuinf[n].zhuren == tpnm || stuinf[n].xh == tpxh)&&stuinf[n].name==tpsub) {
			stuinf[n].grade = changescore;
			ofstream out;
			out.open("score.txt");
			for (int m = 0; m < j; m++) {
				out << stuinf[m].xh << '\t' << stuinf[m].zhuren << '\t' << stuinf[m].name << '\t' << stuinf[m].grade << '\n';
			}
			for (int m = 0; m < jishu; m++) {
				out << tempid[m] << '\t' << tempxm[m] << '\t' << tempcourse[m] << '\t' << tempscore[m] << '\n';
			}
			out.close();
			MessageBox(L"修改成功");
			break;
		}
	}
}
void tcmenu::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string tpxh, tpnm, tpsub;
	tpxh = CT2A(addxh.GetString());
	tpnm = CT2A(addnm.GetString());
	tpsub = CT2A(addsub.GetString());
	stuinf[j].xh = tpxh;
	stuinf[j].zhuren = tpnm;
	stuinf[j].name = tpsub;
	stuinf[j].grade = adscore;
	j++;
	ofstream out;
	out.open("score.txt");
	for (int m = 0; m < j; m++) {
		out << stuinf[m].xh << '\t' << stuinf[m].zhuren << '\t' << stuinf[m].name << '\t' << stuinf[m].grade << '\n';
	}
	for (int m = 0; m < jishu; m++) {
		out << tempid[m] << '\t' << tempxm[m] << '\t' << tempcourse[m] << '\t' << tempscore[m] << '\n';
	}
	out.close();
	MessageBox(L"成绩录入成功！");
}
void tcmenu::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string tpsub;//要查找的科目
	tpsub = CT2A(tjsub.GetString());
	double allscore = 0;
	int num = 0;
	int jg = 0;
	int Grade[100] = { 0 };
	for (int m = 0; m < j; m++) {
		if (stuinf[m].name == tpsub) {
			Grade[num] = stuinf[m].grade;
			allscore+= stuinf[m].grade;
			num++;
			if (stuinf[m].grade >= 60)
				jg++;
		}
	}
	avescore = allscore / num;
	for (int m = 0; m < num; m++) {
		bzc += pow((Grade[m] - avescore), 2);
	}
	bzc = sqrt(bzc / (num - 1));
	jgl = (double)jg / (double)num;
	UpdateData(FALSE);
}



void tcmenu::OnBnClickedButton7()//排序
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string tpsub;
	tpsub = CT2A(sortsub.GetString());
	string NAME[50]; int GRADE[50];
	int num = 0;
	for (int m = 0; m < j; m++) {
		if (stuinf[m].name == tpsub) {
			NAME[num] = stuinf[m].zhuren;
			GRADE[num] = stuinf[m].grade;
			num++;
		}
	}
	for (int m = 0; m < num-1; m++) {
		for (int n = 0; n < num - m - 1; n++) {
			if (GRADE[n] < GRADE[n + 1]) {
				string temp1; int temp2;
				temp1 = NAME[n];
				temp2 = GRADE[n];
				NAME[n] = NAME[n + 1];
				GRADE[n] = GRADE[n + 1];
				NAME[n + 1] = temp1;
				GRADE[n + 1] = temp2;
			}

		}
	}
	for (int i = 0; i < 100; i++) {//删除表格中元素
		shuchu.DeleteColumn(0);
	}
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	shuchu.InsertColumn(1, _T("姓名"), LVCFMT_LEFT, 100);
	shuchu.InsertColumn(2, _T("成绩"), LVCFMT_LEFT, 100);
	CString te1[50], te2[50];
	for (int m = 0; m < num; m++) {
		te1[m] = NAME[m].c_str();
		te2[m].Format(L"%d", GRADE[m]);
		shuchu.InsertItem(m, _T(""), 100);
		shuchu.SetItemText(m, 1, te1[m]);
		shuchu.SetItemText(m, 2, te2[m]);
	}
}


void tcmenu::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	if (myddlg == NULL) {
		myddlg = new mydchakan();
		myddlg->Create(IDD_DIALOG2, this);
		
	}
	myddlg->ShowWindow(SW_SHOW);
}


void tcmenu::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFile = _T("");
	
	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.txt)|*.txt|All Files (*.*)|*.*||"), NULL);
	if (dlgFile.DoModal())
	{
		   strFile = dlgFile.GetPathName();
	}
	ifstream infile;
	infile.open(strFile);
	int num_1 = 0;
	string XUEHAO[100], NAME[100], SUB[100], GRADE[100];
	while (!infile.eof()) {
		infile >> XUEHAO[num_1] >> NAME[num_1] >> SUB[num_1] >> GRADE[num_1];

		num_1++;

	}
	
	infile.close();
	ofstream otf;
	otf.open("score.txt", ios::app);
	for (int i = 0; i < num_1; i++) {
		otf << XUEHAO[i]<<'\t' << NAME[i] << '\t' << SUB[i] << '\t' << GRADE[i] << '\n';
	}
	otf.close();
	MessageBox(L"录入成功");
}

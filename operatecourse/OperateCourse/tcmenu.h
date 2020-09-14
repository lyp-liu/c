#pragma once


// tcmenu 对话框
#include"addscore.h"
#include"mydchakan.h"
class tcmenu : public CDialogEx
{
	DECLARE_DYNAMIC(tcmenu)

public:
	tcmenu(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~tcmenu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_tcmenu };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnBnClickedButton1();
	CString searchnm;
	CString searchxh;
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	CListCtrl shuchu;
	Teacher tea;
	Stuinf stuinf;
	string tempid[1000], tempxm[1000], tempcourse[1000]; int tempscore[1000];
	int jishu = 0;
	int j = 0;
	string tid, tname, t1, t2, t3, t4, t5;
	CString searchsub;
	int xiaxian;
	int shangxian;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	CString tjsub;
	double avescore;
	double bzc;
	double jgl;
	afx_msg void OnBnClickedButton3();
	int changescore;
	CString changesub;
	addscore *asdlg;
	mydchakan *myddlg;
	CString addxh;
	CString addnm;
	CString addsub;
	int adscore;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton7();
	CString sortsub;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton8();
};

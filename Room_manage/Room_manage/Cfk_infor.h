#pragma once


// Cfk_infor 对话框
#include"dengji.h"
#include"tuifang.h"
#include"chaxun.h"
#include"huanfang.h"
class Cfk_infor : public CDialogEx
{
	DECLARE_DYNAMIC(Cfk_infor)

public:
	Cfk_infor(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cfk_infor();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void setInfo();
	dengji *djdlg;
	tuifang *tfdlg;
	chaxun *cxdlg;
	huanfang *hfdlg;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	//afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnPaint();
};

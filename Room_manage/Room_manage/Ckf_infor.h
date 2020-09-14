#pragma once
#include"operate_price.h"
#include"operate_room.h"
// Ckf_infor 对话框

class Ckf_infor : public CDialogEx
{
	DECLARE_DYNAMIC(Ckf_infor)

public:
	Ckf_infor(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Ckf_infor();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void setInfo();
	afx_msg void OnBnClickedButton1();
	CListCtrl shuchu;
	operate_price *opdlg;
	operate_room *oprdlg;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton7();
//	void OnPaint();
	afx_msg void OnPaint();
};

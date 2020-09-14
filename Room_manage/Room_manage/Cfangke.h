#pragma once
#include"Cfangke_info.h"

// Cfangke 对话框

class Cfangke : public CDialogEx
{
	DECLARE_DYNAMIC(Cfangke)

public:
	Cfangke(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cfangke();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	Cfangke_info *fk_info_dlg;
	afx_msg void OnBnClickedButton2();
//	void OnPaint();
	afx_msg void OnPaint();
};

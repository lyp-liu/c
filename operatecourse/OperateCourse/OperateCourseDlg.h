
// OperateCourseDlg.h: 头文件
//

#pragma once
#include"stumenu.h"
#include"tcmenu.h"
#include"admin.h"
// COperateCourseDlg 对话框
class COperateCourseDlg : public CDialogEx
{
// 构造
public:
	COperateCourseDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPERATECOURSE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	stumenu stdlg;
	tcmenu tcdlg;
	admin addlg;
	afx_msg void OnBnClickedButton1();
	CString m_yhm;
	CString m_pwd;
};
typedef struct 
{
	string id;
	string pwd;
	string sf;//身份
	string name;
}Denglu[100];

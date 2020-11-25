
// Romania_holidayDlg.h: 头文件
//

#pragma once
#include<atlimage.h>

// CRomaniaholidayDlg 对话框
class CRomaniaholidayDlg : public CDialogEx
{
// 构造
public:
	CRomaniaholidayDlg(CWnd* pParent = nullptr);	// 标准构造函数
	CImage image;
	CString BmpName;                               //保存图像文件文件名
	CString EntName;                               //保存图像文件扩展名
	CBitmap m_bitmap;                              //创建位图对象
	CImage* pNewImage;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROMANIA_HOLIDAY_DIALOG };
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
	
	int min = 9999;//设置耗散最小值
	int method_choice;
	int step_num = 0;//步数
	CListCtrl shuchu;
	afx_msg void OnBnClickedButton1();
	void BFS();
	void DFS();
	int dfs(int start,int dist,bool flag[20],int step[20]);
	void AStar();
	void Greedy_Best_First();
};

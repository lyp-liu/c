#pragma once


// paixushuchu 对话框

class paixushuchu : public CDialogEx
{
	DECLARE_DYNAMIC(paixushuchu)

public:
	paixushuchu(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~paixushuchu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Teacher teacher;
	Manyidu myd;
	int m_num=0,t_num=0;
	void setinfo();
	CListCtrl shuchu;
	virtual BOOL OnInitDialog();
};

#pragma once


// mydchakan 对话框

class mydchakan : public CDialogEx
{
	DECLARE_DYNAMIC(mydchakan)

public:
	mydchakan(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~mydchakan();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl shuchu;
	virtual BOOL OnInitDialog();
	Manyidu myd;
	int m_num=0;
};

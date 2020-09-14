#pragma once


// addscore 对话框

class addscore : public CDialogEx
{
	DECLARE_DYNAMIC(addscore)

public:
	addscore(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~addscore();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_addscore };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};

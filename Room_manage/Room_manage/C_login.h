#pragma once


// C_login 对话框

class C_login : public CDialogEx
{
	DECLARE_DYNAMIC(C_login)

public:
	C_login(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~C_login();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_login_name;
	CString m_login_pwd;
	afx_msg void OnBnClickedButton1();
	
	//void OnPaint();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedCancel();
};

#pragma once


// Cfangke_info 对话框

class Cfangke_info : public CDialogEx
{
	DECLARE_DYNAMIC(Cfangke_info)

public:
	Cfangke_info(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cfangke_info();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_guest_name;
	CString m_guest_sex;
	CString m_guest_nation;
	CString m_guest_place;
	CString m_guest_id;
	CString m_room_id;
	CString m_room_type;
	CString m_enter_time;
	CString m_time_long;
	void setInfo();
//	void OnPaint();
	afx_msg void OnPaint();
};

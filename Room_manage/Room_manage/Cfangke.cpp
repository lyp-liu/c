// Cfangke.cpp: 实现文件
//

#include "stdafx.h"
#include "Room_manage.h"
#include "Cfangke.h"
#include "afxdialogex.h"


// Cfangke 对话框

IMPLEMENT_DYNAMIC(Cfangke, CDialogEx)

Cfangke::Cfangke(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{
	fk_info_dlg = NULL;
}

Cfangke::~Cfangke()
{
	if (NULL != fk_info_dlg)
	{
		// 删除非模态对话框对象   
		delete fk_info_dlg;
	}
}

void Cfangke::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Cfangke, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Cfangke::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cfangke::OnBnClickedButton2)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Cfangke 消息处理程序


void Cfangke::OnBnClickedButton1()
{//查询入住信息
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == fk_info_dlg) {
		fk_info_dlg = new Cfangke_info();
		fk_info_dlg->Create(IDD_DIALOG3, this);
		fk_info_dlg->setInfo();
	}
	fk_info_dlg->ShowWindow(SW_SHOW);
	


}


void Cfangke::OnBnClickedButton2()
{//想退房需要把Guest表中的这个uid的所有信息全部删除
	//login表中这个uid的信息也删除
	//room表中的这个房号的Room_now改为未入住
	// TODO: 在此添加控件通知处理程序代码
	_RecordsetPtr m_pRecordset;
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	//先查到此uid的房号r_id
	int r_id; CString uid;
	m_pRecordset->Open("select * from Guest", m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	m_pRecordset->MoveFirst();
	while (!m_pRecordset->adoEOF) {
		uid= m_pRecordset->GetCollect("Guest_uid").bstrVal;
		uid.TrimRight();
		if (uid == yhid) {
			r_id = m_pRecordset->GetCollect("Guest_room");
		}
		else {
			m_pRecordset->MoveNext();
			continue;
		}
		break;
	}
	CString strsql1,strsql2,strsql3,weizhu(_T("未入住"));
	//删除Guest表中信息的sql语句
	strsql1 .Format(_T("delete from Guest where Guest_uid='%s'") , yhid);
	//删除login表中sql语句：
	strsql2= _T("delete from Log_in where Logid =") + _T(" '") + yhid+ _T("'");
	//修改room表中这个房号的Room_now
	strsql3.Format(_T("update Room_inf set Room_now='%s' where Room_id ='%d'"),weizhu, r_id);
	try {
		m_pConnection->Execute(_bstr_t(strsql1), 0, adCmdText);
		m_pConnection->Execute(_bstr_t(strsql2), 0, adCmdText);
		m_pConnection->Execute(_bstr_t(strsql3), 0, adCmdText);
		AfxMessageBox(_T("您已成功退房，可以退出系统了"));
	}
	catch (_com_error e)
	{
		MessageBox(e.Description());
		return;
	}

}


//void Cfangke::OnPaint()
//{
//	// TODO: 在此处添加实现代码.
//}


void Cfangke::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect   rect;
	GetClientRect(&rect);    //获取对话框长宽      
	CDC   dcBmp;             //定义并创建一个内存设备环境
	dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP1);    //载入资源中图片
	BITMAP   m_bitmap;                         //图片变量               
	bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
	//将位图选入临时内存设备环境
	CBitmap  *pbmpOld = dcBmp.SelectObject(&bmpBackground);
	//调用函数显示图片StretchBlt显示形状可变
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);

}

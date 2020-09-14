// Cfk_infor.cpp: 实现文件
//

#include "stdafx.h"
#include "Room_manage.h"
#include "Cfk_infor.h"
#include "afxdialogex.h"


// Cfk_infor 对话框

IMPLEMENT_DYNAMIC(Cfk_infor, CDialogEx)

Cfk_infor::Cfk_infor(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{
	djdlg = NULL;
	tfdlg = NULL;
	cxdlg = NULL;
	hfdlg = NULL;
}

Cfk_infor::~Cfk_infor()
{
	if (djdlg != NULL) {
		delete djdlg;
	}
	if (tfdlg != NULL) {
		delete tfdlg;
	}
	if (cxdlg != NULL) {
		delete cxdlg;
	}
	if (hfdlg != NULL) {
		delete hfdlg;
	}
}

void Cfk_infor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Cfk_infor, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Cfk_infor::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cfk_infor::OnBnClickedButton2)
	//ON_BN_CLICKED(IDC_BUTTON3, &Cfk_infor::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Cfk_infor::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &Cfk_infor::OnBnClickedButton3)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Cfk_infor 消息处理程序


void Cfk_infor::setInfo()
{
	// TODO: 在此处添加实现代码.
}


void Cfk_infor::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == djdlg) {
		djdlg = new dengji();
		djdlg->Create(IDD_DIALOGdengji, this);
		//kf_managedlg->setInfo();
	}
	djdlg->ShowWindow(SW_SHOW);
}


void Cfk_infor::OnBnClickedButton2()
{//退房
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == tfdlg) {
		tfdlg = new tuifang();
		tfdlg->Create(IDD_DIALOGtuifang, this);
		//kf_managedlg->setInfo();
	}
	tfdlg->ShowWindow(SW_SHOW);
}





void Cfk_infor::OnBnClickedButton4()
{//查询
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == cxdlg) {
		cxdlg = new chaxun();
		cxdlg->Create(IDD_DIALOGchaxun, this);
		//kf_managedlg->setInfo();
	}
	cxdlg->ShowWindow(SW_SHOW);
}


void Cfk_infor::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == hfdlg) {
		hfdlg = new huanfang();
		hfdlg->Create(IDD_DIALOGhuanfang, this);
		//kf_managedlg->setInfo();
	}
	hfdlg->ShowWindow(SW_SHOW);
}


void Cfk_infor::OnPaint()
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

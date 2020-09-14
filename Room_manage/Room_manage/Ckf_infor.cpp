// Ckf_infor.cpp: 实现文件
//

#include "stdafx.h"
#include "Room_manage.h"
#include "Ckf_infor.h"
#include "afxdialogex.h"


// Ckf_infor 对话框

IMPLEMENT_DYNAMIC(Ckf_infor, CDialogEx)

Ckf_infor::Ckf_infor(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{
	opdlg = NULL;
	oprdlg = NULL;
}

Ckf_infor::~Ckf_infor()
{
	if (NULL != opdlg)
	{
		// 删除非模态对话框对象   
		delete opdlg;
	}
	if (NULL != oprdlg)
	{
		// 删除非模态对话框对象   
		delete oprdlg;
	}
}

void Ckf_infor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, shuchu);
}


BEGIN_MESSAGE_MAP(Ckf_infor, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Ckf_infor::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Ckf_infor::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &Ckf_infor::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &Ckf_infor::OnBnClickedButton7)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Ckf_infor 消息处理程序


void Ckf_infor::setInfo()
{
	// TODO: 在此处添加实现代码.
	
}


void Ckf_infor::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DWORD dwStyle = shuchu.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	shuchu.SetExtendedStyle(dwStyle);
	for (int i = 0; i < 100; i++) {//删除表格中元素
		shuchu.DeleteColumn(0);
	}
	shuchu.InsertItem(0, _T(""), 0);
	shuchu.InsertItem(1, _T(""), 100);
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	shuchu.InsertColumn(1, _T(""), LVCFMT_LEFT, 150);
	shuchu.InsertColumn(2, _T(""), LVCFMT_LEFT, 150);
	shuchu.InsertColumn(3, _T(""), LVCFMT_LEFT, 150);
	shuchu.SetItemText(1, 1,_T("房间号") );
	shuchu.SetItemText(1, 2, _T("房间类型"));
	shuchu.SetItemText(1, 3, _T("房间状态"));
	int ii = 2;
	_RecordsetPtr  m_pRecordSet;   //数据集对象指针
	CString  type, now;
	int num;
	::CoInitialize(NULL);
	try {
		m_pRecordSet.CreateInstance(__uuidof(Recordset));
		m_pRecordSet->Open("select * from Room_inf", m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		m_pRecordSet->MoveFirst();//指针指向第一个数据
		while (!m_pRecordSet->adoEOF) {
				num= m_pRecordSet->GetCollect("Room_id");
				type= m_pRecordSet->GetCollect("Room_type").bstrVal;
				type.TrimRight();
				now= m_pRecordSet->GetCollect("Room_now").bstrVal;
				now.TrimRight();
				CString temp;
				temp.Format(_T("%d"), num);
				shuchu.InsertItem(ii, _T(""), 100);
				shuchu.SetItemText(ii, 1,temp );
				shuchu.SetItemText(ii, 2,type );
				shuchu.SetItemText(ii, 3,now );
				ii++;
				m_pRecordSet->MoveNext();//没查到指向下一条记录
				if (m_pRecordSet == NULL)break;
		}
	}
	catch (_com_error e)

	{

		::CoUninitialize();

		AfxMessageBox(e.ErrorMessage());

		return;

	}
}


void Ckf_infor::OnBnClickedButton2()
{//
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DWORD dwStyle = shuchu.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	shuchu.SetExtendedStyle(dwStyle);
	for (int i = 0; i < 100; i++) {//删除表格中元素
		shuchu.DeleteColumn(0);
	}
	shuchu.InsertItem(0, _T(""), 0);
	shuchu.InsertItem(1, _T(""), 100);
	shuchu.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	shuchu.InsertColumn(1, _T(""), LVCFMT_LEFT, 150);
	shuchu.InsertColumn(2, _T(""), LVCFMT_LEFT, 150);
	shuchu.InsertColumn(3, _T(""), LVCFMT_LEFT, 150);
	shuchu.SetItemText(1, 1, _T("房间类型"));
	shuchu.SetItemText(1, 2, _T("房间价格"));
	
	int ii = 2;
	_RecordsetPtr  m_pRecordSet;   //数据集对象指针
	CString  type;
	int jiage;
	
	::CoInitialize(NULL);
	try {
		m_pRecordSet.CreateInstance(__uuidof(Recordset));
		m_pRecordSet->Open("select * from Room_price", m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		m_pRecordSet->MoveFirst();//指针指向第一个数据
		while (!m_pRecordSet->adoEOF) {
			
			type = m_pRecordSet->GetCollect("Room_type").bstrVal;
			type.TrimRight();
			jiage = m_pRecordSet->GetCollect("Room_jiage");
			
			CString temp;
			temp.Format(_T("%d"), jiage);
			shuchu.InsertItem(ii, _T(""), 100);
			shuchu.SetItemText(ii, 1, type);
			shuchu.SetItemText(ii, 2, temp);
			
			ii++;
			m_pRecordSet->MoveNext();//没查到指向下一条记录
			if (m_pRecordSet == NULL)break;
		}
	}
	catch (_com_error e)

	{

		::CoUninitialize();

		AfxMessageBox(e.ErrorMessage());

		return;

	}
}


void Ckf_infor::OnBnClickedButton5()
{//弹出客房信息操作界面
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == oprdlg) {
		oprdlg = new operate_room();
		oprdlg->Create(IDD_DIALOG6, this);
		//kf_managedlg->setInfo();
	}
	oprdlg->ShowWindow(SW_SHOW);
}


void Ckf_infor::OnBnClickedButton7()
{//弹出房型信息操作界面
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == opdlg) {
		opdlg = new operate_price();
		opdlg->Create(IDD_DIALOG7, this);
		//kf_managedlg->setInfo();
	}
	opdlg->ShowWindow(SW_SHOW);
}


//void Ckf_infor::OnPaint()
//{
//	// TODO: 在此处添加实现代码.
//}


void Ckf_infor::OnPaint()
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

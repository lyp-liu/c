// chaxun.cpp: 实现文件
//

#include "stdafx.h"
#include "Room_manage.h"
#include "chaxun.h"
#include "afxdialogex.h"


// chaxun 对话框

IMPLEMENT_DYNAMIC(chaxun, CDialogEx)

chaxun::chaxun(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGchaxun, pParent)
	, m_xingming(_T(""))
	, m_fanghao(0)
{

}

chaxun::~chaxun()
{
}

void chaxun::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, shuchu);
	DDX_Text(pDX, IDC_EDIT1, m_xingming);
	DDX_Text(pDX, IDC_EDIT2, m_fanghao);
}


BEGIN_MESSAGE_MAP(chaxun, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &chaxun::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &chaxun::OnBnClickedButton2)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// chaxun 消息处理程序


void chaxun::OnBnClickedButton1()
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
	shuchu.InsertColumn(1, _T(""), LVCFMT_LEFT, 100);
	shuchu.InsertColumn(2, _T(""), LVCFMT_LEFT, 100);
	shuchu.InsertColumn(3, _T(""), LVCFMT_LEFT, 150);
	for (int i = 4; i < 15; i++) {
		shuchu.InsertColumn(i, _T(""), LVCFMT_LEFT, 100);
		
	}
	
	shuchu.SetItemText(1, 1, _T("姓名"));
	shuchu.SetItemText(1, 2, _T("性别"));
	shuchu.SetItemText(1, 3, _T("身份证号"));
	shuchu.SetItemText(1, 4, _T("民族"));
	shuchu.SetItemText(1, 5, _T("联系方式"));
	shuchu.SetItemText(1, 6, _T("房间号"));
	shuchu.SetItemText(1, 7, _T("房间类型"));
	shuchu.SetItemText(1, 8, _T("入住时间"));
	shuchu.SetItemText(1, 9, _T("剩余时间"));
	_RecordsetPtr  m_pRecordSet;   //数据集对象指针
	CString name, sex, id, nation, num,  type, time;
	int room, length;
	int ii = 2;
	::CoInitialize(NULL);
	try {
		m_pRecordSet.CreateInstance(__uuidof(Recordset));
		m_pRecordSet->Open("select * from Guest", m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		m_pRecordSet->MoveFirst();//指针指向第一个数据
		while (!m_pRecordSet->adoEOF) {
			name = m_pRecordSet->GetCollect("Guest_name").bstrVal;
			name.TrimRight();
			if (name == m_xingming) {
				sex= m_pRecordSet->GetCollect("Guest_sex").bstrVal;
				sex.TrimRight();
				id= m_pRecordSet->GetCollect("Guest_id").bstrVal;
				id.TrimRight();
				nation= m_pRecordSet->GetCollect("Guest_nation").bstrVal;
				nation.TrimRight();
				num= m_pRecordSet->GetCollect("Guest_num").bstrVal;
				num.TrimRight();
				type= m_pRecordSet->GetCollect("Guest_type").bstrVal;
				type.TrimRight();
				time= m_pRecordSet->GetCollect("Guest_time").bstrVal;
				time.TrimRight();
				length= m_pRecordSet->GetCollect("Guest_long");
				room= m_pRecordSet->GetCollect("Guest_room");
				CString temp1, temp2;
				temp1.Format(_T("%d"), room);
				temp2.Format(_T("%d"), length);
				shuchu.InsertItem(ii, _T(""), 100);
				shuchu.SetItemText(ii, 1, name);
				shuchu.SetItemText(ii, 2, sex);
				shuchu.SetItemText(ii, 3, id);
				shuchu.SetItemText(ii, 4, nation);
				shuchu.SetItemText(ii, 5, num);
				shuchu.SetItemText(ii, 6, temp1);
				shuchu.SetItemText(ii, 7, type);
				shuchu.SetItemText(ii, 8,time);
				shuchu.SetItemText(ii, 9, temp2);
				ii++;
				
			}
			else if(m_pRecordSet ->adoEOF) { 
				AfxMessageBox(_T("查无此人"));
				break; 
			}
			m_pRecordSet->MoveNext();
			
		}
	}
	catch (_com_error e)

	{

		::CoUninitialize();

		AfxMessageBox(e.ErrorMessage());

		return;

	}

}


void chaxun::OnBnClickedButton2()
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
	shuchu.InsertColumn(1, _T(""), LVCFMT_LEFT, 100);
	shuchu.InsertColumn(2, _T(""), LVCFMT_LEFT, 100);
	shuchu.InsertColumn(3, _T(""), LVCFMT_LEFT, 150);
	for (int i = 4; i < 15; i++) {
		shuchu.InsertColumn(i, _T(""), LVCFMT_LEFT, 100);

	}

	shuchu.SetItemText(1, 1, _T("姓名"));
	shuchu.SetItemText(1, 2, _T("性别"));
	shuchu.SetItemText(1, 3, _T("身份证号"));
	shuchu.SetItemText(1, 4, _T("民族"));
	shuchu.SetItemText(1, 5, _T("联系方式"));
	shuchu.SetItemText(1, 6, _T("房间号"));
	shuchu.SetItemText(1, 7, _T("房间类型"));
	shuchu.SetItemText(1, 8, _T("入住时间"));
	shuchu.SetItemText(1, 9, _T("剩余时间"));
	_RecordsetPtr  m_pRecordSet;   //数据集对象指针
	CString name, sex, id, nation, num, type, time;
	int room, length;
	int ii = 2;
	::CoInitialize(NULL);
	try {
		m_pRecordSet.CreateInstance(__uuidof(Recordset));
		m_pRecordSet->Open("select * from Guest", m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		m_pRecordSet->MoveFirst();//指针指向第一个数据
		while (!m_pRecordSet->adoEOF) {
			room = m_pRecordSet->GetCollect("Guest_room");
			
			if (room == m_fanghao) {
				name = m_pRecordSet->GetCollect("Guest_name").bstrVal;
				name.TrimRight();
				/*if (name.GetLength() <= 0) {
					AfxMessageBox(_T("此房间无人入住"));
					break;
				}*/
				sex = m_pRecordSet->GetCollect("Guest_sex").bstrVal;
				sex.TrimRight();
				id = m_pRecordSet->GetCollect("Guest_id").bstrVal;
				id.TrimRight();
				nation = m_pRecordSet->GetCollect("Guest_nation").bstrVal;
				nation.TrimRight();
				num = m_pRecordSet->GetCollect("Guest_num").bstrVal;
				num.TrimRight();
				type = m_pRecordSet->GetCollect("Guest_type").bstrVal;
				type.TrimRight();
				time = m_pRecordSet->GetCollect("Guest_time").bstrVal;
				time.TrimRight();
				length = m_pRecordSet->GetCollect("Guest_long");
			
				CString temp1, temp2;
				temp1.Format(_T("%d"), room);
				temp2.Format(_T("%d"), length);
				shuchu.InsertItem(ii, _T(""), 100);
				shuchu.SetItemText(ii, 1, name);
				shuchu.SetItemText(ii, 2, sex);
				shuchu.SetItemText(ii, 3, id);
				shuchu.SetItemText(ii, 4, nation);
				shuchu.SetItemText(ii, 5, num);
				shuchu.SetItemText(ii, 6, temp1);
				shuchu.SetItemText(ii, 7, type);
				shuchu.SetItemText(ii, 8, time);
				shuchu.SetItemText(ii, 9, temp2);
				ii++;

			}
			m_pRecordSet->MoveNext();
			if (room!=m_fanghao&&m_pRecordSet ->adoEOF) {
				AfxMessageBox(_T("此房间无人入住"));
				break;
			}
			
		}
	}
	catch (_com_error e)

	{

		::CoUninitialize();

		AfxMessageBox(e.ErrorMessage());

		return;

	}
}


//void chaxun::OnPaint()
//{
//	// TODO: 在此处添加实现代码.
//}


void chaxun::OnPaint()
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

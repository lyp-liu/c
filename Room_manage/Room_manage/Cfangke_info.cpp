// Cfangke_info.cpp: 实现文件
//

#include "stdafx.h"
#include "Room_manage.h"
#include "Cfangke_info.h"
#include "afxdialogex.h"


// Cfangke_info 对话框

IMPLEMENT_DYNAMIC(Cfangke_info, CDialogEx)

Cfangke_info::Cfangke_info(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_guest_name(_T(""))
	, m_guest_sex(_T(""))
	, m_guest_nation(_T(""))
	, m_guest_place(_T(""))
	, m_guest_id(_T(""))
	, m_room_id(_T(""))
	, m_room_type(_T(""))
	, m_enter_time(_T(""))
	, m_time_long(_T(""))
{

}

Cfangke_info::~Cfangke_info()
{
}

void Cfangke_info::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_guest_name);
	DDX_Text(pDX, IDC_EDIT2, m_guest_sex);
	DDX_Text(pDX, IDC_EDIT4, m_guest_nation);
	DDX_Text(pDX, IDC_EDIT6, m_guest_place);
	DDX_Text(pDX, IDC_EDIT3, m_guest_id);
	DDX_Text(pDX, IDC_EDIT7, m_room_id);
	DDX_Text(pDX, IDC_EDIT8, m_room_type);
	DDX_Text(pDX, IDC_EDIT9, m_enter_time);
	DDX_Text(pDX, IDC_EDIT10, m_time_long);
}


BEGIN_MESSAGE_MAP(Cfangke_info, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Cfangke_info 消息处理程序


void Cfangke_info::setInfo()
{
	// TODO: 在此处添加实现代码.
	UpdateData(TRUE);
	_RecordsetPtr  m_pRecordSet;   //数据集对象指针
	CString name, sex, nation, place, idnum, uid,  r_type, enter_ti;//存放读取到的数据
	int r_id, length;
	::CoInitialize(NULL);
	try {
		m_pRecordSet.CreateInstance(__uuidof(Recordset));
		//打开记录集
		m_pRecordSet->Open("select * from Guest", m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		m_pRecordSet->MoveFirst();//指针指向第一个数据
		while (!m_pRecordSet->adoEOF) {//遍历表中数据
			uid = m_pRecordSet->GetCollect("Guest_uid").bstrVal;
			uid.TrimRight();
			if (uid != yhid) {
				m_pRecordSet->MoveNext();//没查到指向下一条记录
				continue;
			}
			name = m_pRecordSet->GetCollect("Guest_name").bstrVal;
			name.TrimRight();
			sex = m_pRecordSet->GetCollect("Guest_sex").bstrVal;
			sex.TrimRight();
			nation = m_pRecordSet->GetCollect("Guest_nation").bstrVal;
			nation.TrimRight();
			place = m_pRecordSet->GetCollect("Guest_place").bstrVal;
			place.TrimRight();
			idnum = m_pRecordSet->GetCollect("Guest_id").bstrVal;
			idnum.TrimRight();
			r_type = m_pRecordSet->GetCollect("Guest_type").bstrVal;
			r_type.TrimRight();
			enter_ti = m_pRecordSet->GetCollect("Guest_time").bstrVal;
			enter_ti.TrimRight();
			length = m_pRecordSet->GetCollect("Guest_long");//不需要
			r_id = m_pRecordSet->GetCollect("Guest_room");//不需要
			break;
		}

	}
	catch (_com_error e)

	{

		::CoUninitialize();

		AfxMessageBox(e.ErrorMessage());

		return;

	}
	m_guest_name = name;
	m_guest_sex = sex;
	m_guest_nation = nation;
	m_guest_place = place;
	m_guest_id = idnum;
	m_room_id.Format( _T("%d"),r_id);
	m_room_type = r_type;
	m_enter_time = enter_ti;
	m_time_long .Format(_T("%d"), length);
	UpdateData(FALSE);
}


//void Cfangke_info::OnPaint()
//{
//	// TODO: 在此处添加实现代码.
//}


void Cfangke_info::OnPaint()
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

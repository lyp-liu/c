// C_login.cpp: 实现文件
//

#include "stdafx.h"
#include "Room_manage.h"
#include "C_login.h"
#include "afxdialogex.h"
#include"Adosql.h"
#include"Room_manageDlg.h"
#include"Cfangke.h"




// C_login 对话框

IMPLEMENT_DYNAMIC(C_login, CDialogEx)

C_login::C_login(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_login_name(_T(""))
	, m_login_pwd(_T(""))
{

}

C_login::~C_login()
{
	
}

void C_login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_login_name);
	DDX_Text(pDX, IDC_EDIT2, m_login_pwd);
}


BEGIN_MESSAGE_MAP(C_login, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &C_login::OnBnClickedButton1)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDCANCEL, &C_login::OnBnClickedCancel)
END_MESSAGE_MAP()


// C_login 消息处理程序


void C_login::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码	
	UpdateData(TRUE);
	_bstr_t m_sqlCmd;    //存储sql语句
	_RecordsetPtr  m_pRecordSet;   //数据集对象指针
	CString user, pass, author;//存放读取到的数据
	::CoInitialize(NULL);
	try
	{
		
		m_pConnection.CreateInstance("ADODB.Connection"); //创建Connection对象
		//1、新建一个文件，名字任意取，后缀名必须为udl（如hello.udl）
		//2、双击hello.udl文件，进入数据连接属性面板，填写好数据源（选择自己创建的数据源名字的）
		//3、再以记事本方式打开，第三行的数据就是连接字符
			m_pConnection->Open(m_bstrConn, "sa", "you205768", adModeUnknown);
			m_pRecordSet.CreateInstance(__uuidof(Recordset));
			//打开记录集
			m_pRecordSet->Open("select * from Log_in", m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			m_pRecordSet->MoveFirst();//指针指向第一个数据
			
			if (m_login_name.IsEmpty() || m_login_pwd.IsEmpty()) {
				MessageBox(_T("用户名或密码不能为空，请重新输入！"), _T("用户登录信息"), MB_ICONINFORMATION);
				m_login_name.Empty();   //清空界面上账号的值
				m_login_pwd.Empty();   //清空界面上密码的值
				UpdateData(FALSE);
				return;
			}
	
	
	//创建记录集指针对象实例
	
	//GetRecordSet(_T("select * from Log_in"));
	//初始化数据表选择Log_in表
	
	CString gly("管理员"),yh("用户");
	while (!m_pRecordSet->adoEOF) {//表中记录的遍历
		user = m_pRecordSet->GetCollect("Logid").bstrVal;
		pass= m_pRecordSet->GetCollect("Logkey").bstrVal;
		author= m_pRecordSet->GetCollect("Logpower").bstrVal;
		user.TrimRight();
		pass.TrimRight();
		author.TrimRight();
		if (user == m_login_name && pass == m_login_pwd && author == yh) {
			yhid = user;
			//新建一个用户的对话框
			CDialog::EndDialog(IDD_DIALOG2);
			Cfangke dlg;
			dlg.DoModal();
			return;
		}
		if (user == m_login_name && pass == m_login_pwd&&author==gly) {
			//应该新建一个管理员界面的对话框
			CDialog::EndDialog(IDD_DIALOG2);
			CRoommanageDlg dlg;
			dlg.DoModal();
			return;
		}
		
		m_pRecordSet->MoveNext();//没查到指向下一条记录
	}
	AfxMessageBox(_T("无此用户信息，请检查后输入"));
	}
	catch (_com_error e)

	{

		::CoUninitialize();

		AfxMessageBox(e.ErrorMessage());

		return;

	}
	
}





void C_login::OnPaint()
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


void C_login::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


// TTSControls_vs2015fw4Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TTSControls_vs2015fw4.h"
#include "TTSControls_vs2015fw4Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTTSControls_vs2015fw4Dlg 对话框



CTTSControls_vs2015fw4Dlg::CTTSControls_vs2015fw4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TTSCONTROLS_VS2015FW4_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTTSControls_vs2015fw4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboBox);
	DDX_Control(pDX, IDC_COMBO2, m_comboBox1);
	DDX_Control(pDX, IDC_EDIT1, m_EditCtrlTip);
	DDX_Control(pDX, IDC_LIST1, m_ListBoxCtrlEx);
	DDX_Control(pDX, IDC_STATICl, m_EditCtrlImage);
	DDX_Control(pDX, IDC_STATICr, m_EditCtrlImagRight);
	DDX_Control(pDX, IDC_LIST2, m_CListCtrlex);
	DDX_Control(pDX, IDC_BUTTON7, m_CMyButton);
}

BEGIN_MESSAGE_MAP(CTTSControls_vs2015fw4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTTSControls_vs2015fw4Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &CTTSControls_vs2015fw4Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &CTTSControls_vs2015fw4Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTTSControls_vs2015fw4Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CTTSControls_vs2015fw4Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON4, &CTTSControls_vs2015fw4Dlg::OnBnClickedButton4)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CTTSControls_vs2015fw4Dlg::OnCbnSelchangeCombo2)
	ON_LBN_SELCHANGE(IDC_LIST1, &CTTSControls_vs2015fw4Dlg::OnLbnSelchangeList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CTTSControls_vs2015fw4Dlg::OnNMDblclkList2)
	ON_BN_CLICKED(IDC_BUTTON8, &CTTSControls_vs2015fw4Dlg::OnBnClickedButton8)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CTTSControls_vs2015fw4Dlg::OnLvnItemchangedList2)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CTTSControls_vs2015fw4Dlg::OnNMClickList2)
	ON_BN_CLICKED(IDC_BUTTON9, &CTTSControls_vs2015fw4Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CTTSControls_vs2015fw4Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON12, &CTTSControls_vs2015fw4Dlg::OnBnClickedButton12)
END_MESSAGE_MAP()


// CTTSControls_vs2015fw4Dlg 消息处理程序

BOOL CTTSControls_vs2015fw4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码


	OnBnClickedButton5();
	
	//wjf  CComboBoxCtrlEx  控件初始化
	m_comboBox.InitControl();
	m_comboBox.SetCurSel(0);

	//m_comBox.AddString(_T(""));
	//m_comBox.AddString(_T("王建锋"));

	//wjf CEditCtrlImage  控件初始化  使用方法
	//CStatic控件，绑定到自绘控件类上
	//CEditCtrlImage m_EditCtrlImage;
	//DDX_Control(pDX, IDC_NEWEDIT, m_EditCtrlImage);

	//黄色 /黄色 /红色  RGB(255, 255, 0), RGB(255, 255, 0), RGB(255, 0, 0));
	//RGB(40, 138, 228);//蓝色 RGB(0, 0, 0);//黑色  RGB(141, 178, 227);//画刷恬蓝 RGB(160, 31, 208);//画笔紫色
	//左
	m_EditCtrlImage.Init(TRUE, AfxGetApp()->LoadIcon(IDI_ICON2), AfxGetApp()->LoadIcon(IDI_ICON2), 3, 2);
	m_EditCtrlImage.setNormalColor(RGB(160, 31, 208), RGB(141, 178, 227), RGB(0, 0, 0));
	//
	//右
	m_EditCtrlImagRight.Init(false, AfxGetApp()->LoadIcon(IDI_ICON2), AfxGetApp()->LoadIcon(IDI_ICON2), 3, 2);
	m_EditCtrlImagRight.setNormalColor(RGB(160, 31, 208), RGB(141, 178, 227), RGB(0, 0, 0));


	 //wjf CListBoxCtrlEx  控件初始化  使用方法
	//设置列表控件使用复选框
	//m_CListCtrlex.SetExtendedStyle(LVS_EX_CHECKBOXES);

	//设置列表视图的扩展风格
	LONG lStyle;
	lStyle = GetWindowLong(m_CListCtrlex.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位 
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_CListCtrlex.m_hWnd, GWL_STYLE, lStyle);//设置style

	//DWORD dwStyle = m_CListCtrlex.GetExtendedStyle();
	//dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl） 
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件  要让ListCtrl的每一行的第一列为CheckBox
	//m_CListCtrlex.SetExtendedStyle(dwStyle); //设置扩展风格 


	m_CListCtrlex.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES
		| LVS_EX_CHECKBOXES
		| LVS_EX_ONECLICKACTIVATE
		| LVS_EX_HEADERDRAGDROP);


	//m_CListCtrlex.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_CListCtrlex.AddColumn("Column 0", 0, 300);
	m_CListCtrlex.AddColumn("Column 1", 1, 250);
	m_CListCtrlex.AddColumn("Column 2", 2);

	m_CListCtrlex.AddItem(0, 0, "Row 0, Col 0 CListCtr", CListItemText::GenerateProperty(true, RGB(255, 0, 0)));
	m_CListCtrlex.AddItem(0, 1, "Row 0, Col 1 农业大脑", CListItemText::GenerateProperty(false, RGB(0, 255, 0)));
	m_CListCtrlex.AddItem(0, 2, "1", CListItemCheckBox::GenerateProperty());
	
	m_CListCtrlex.AddItem(1, 0, "Row 1, Col 0 CCSVColumn", CListItemText::GenerateProperty(true, RGB(0, 0, 255)));
	m_CListCtrlex.AddItem(1, 1, "Row 1, Col 1 CListItem");
	m_CListCtrlex.AddItem(1, 2, "1", CListItemCheckBox::GenerateProperty());
	
	m_CListCtrlex.AddItem(2, 0, "Row 2, Col 0", CListItemText::GenerateProperty(false, RGB(0, 0, 255)));
	m_CListCtrlex.AddItem(2, 1, "Row 2, Col 1 CSVLineParser");
	m_CListCtrlex.AddItem(2, 2, "1", CListItemCheckBox::GenerateProperty());
	
	m_CListCtrlex.AddItem(3, 0, "王建锋13384973071", CListItemText::GenerateProperty(true, RGB(0, 255, 0)));
	m_CListCtrlex.AddItem(3, 1, "是否为主键", CListItemText::GenerateProperty(false, RGB(255, 0, 0)));
	m_CListCtrlex.AddItem(3, 2, "1", CListItemCheckBox::GenerateProperty());

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE


	//


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTTSControls_vs2015fw4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTTSControls_vs2015fw4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTTSControls_vs2015fw4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTTSControls_vs2015fw4Dlg::OnBnClickedButton1()
{
	
	//四个条件缺一不可Owner Drawer : Variable, Type:Drop List; Has Strings : False; Sort:False
	// TODO: 在此添加控件通知处理程序代码
	ItemList* pItem = new ItemList;
	pItem->clrLeft = RGB(0, 132, 114);
	pItem->clrRight = RGB(0, 255, 125);
	pItem->hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	pItem->strTitle = _T("王建峰");
	pItem->strUrl = _T("http://www.qq.com");
	m_comboBox.AddString(_T("腾讯首页")); //不AddString, 那么数据就加不进去
	pItem->iItem = 2;
	m_comboBox.m_vecItemList.push_back(pItem);

	ItemList* pItem1 = new ItemList;
	pItem1->clrLeft = RGB(0, 132, 114);
	pItem1->clrRight = RGB(0, 255, 125);
	pItem1->hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	pItem1->strTitle = _T("王鹏飞");
	pItem1->strUrl = _T("http://www.google.com.hk");
	pItem1->iItem = 3;
	m_comboBox.AddString(_T("Google首页"));
	m_comboBox.m_vecItemList.push_back(pItem1);

	ItemList* pItem2 = new ItemList;
	pItem2->clrLeft = RGB(0, 133, 114);
	pItem2->clrRight = RGB(0, 221, 125);
	pItem2->hIcon = AfxGetApp()->LoadIcon(IDI_ICON3);
	pItem2->strTitle = _T("靳浩");
	pItem2->iItem = 4;
	pItem2->strUrl = _T("http://www.sina.cn");
	m_comboBox.AddString(_T("靳浩"));
	m_comboBox.m_vecItemList.push_back(pItem2);

	ItemList* pItem3 = new ItemList;
	pItem3->clrLeft = RGB(0, 132, 114);
	pItem3->clrRight = RGB(0, 255, 125);
	pItem3->hIcon = AfxGetApp()->LoadIcon(IDI_ICON4);
	pItem3->strTitle = _T("马云");
	pItem3->strUrl = _T("http://www.sina.cn");
	pItem3->iItem = 5;
	m_comboBox.AddString(_T("马云"));
	m_comboBox.m_vecItemList.push_back(pItem3);

	ItemList* pItem4 = new ItemList;
	pItem4->clrLeft = RGB(0, 132, 114);
	pItem4->clrRight = RGB(0, 255, 125);
	pItem4->hIcon = AfxGetApp()->LoadIcon(IDI_ICON5);
	pItem4->strTitle = _T("农业大数据");
	pItem4->strUrl = _T("http://www.kugou.cn");
	pItem4->iItem = 6;
	m_comboBox.AddString(_T("农业大数据"));
	m_comboBox.m_vecItemList.push_back(pItem4);

	//wjf  动态增加项目

	m_comboBox.SetCurSel(0);
	/*pItem1->iItem = 2;*/
	//m_comboBox.AddString(_T(""));
	//m_comboBox.AddString(_T("王建锋"));	// TODO: 在此添加控件通知处理程序代码
}


void CTTSControls_vs2015fw4Dlg::OnBnClickedButton5()
{
	//Owner Draw : Variable  Has Strings : True
	// TODO: 在此添加控件通知处理程序代码
	//m_UseListBox.SetItemHeight(1, 60);
	//m_oldlistbox.InsertString(0, _T("保护毒霸自身相关程序不被攻击、破坏"));
	m_ListBoxCtrlEx.InsertStr(_T("地图导航"), 0, _T("棚空间分布、每个大棚栽培地块分布、各类传感器位置分布、动力设备、环境温度、湿度调控设备位置分布以及相应的空间属性包括大棚型号、面积；环境监测、生物监测项目；设备名称；当前栽培作物等。"), MAKEINTRESOURCE(IDI_ICON1));
	m_ListBoxCtrlEx.InsertStr(_T("监测报警"), 1, _T("监测报警以基地为单位进行，分为报警和报警阈值设定两部分。报警包括环境报警联动视频监控。报警阈值设置可以针对不同大棚的不同作物不同生长发育期对环境要求在线设置报警值上下限。"), MAKEINTRESOURCE(IDI_ICON2));
	m_ListBoxCtrlEx.InsertStr(_T("实时环境、生物监测"), 2, _T("实时采集和传送环境数据包括室外温度、湿度、辐照度、风速、风向和雨量，室内温度、湿度、二氧化碳浓度和水温，灌溉量、回流量、灌溉营养液pH、EC等，生物数据包括叶面温度、植株水势、果实膨大等。"), MAKEINTRESOURCE(IDI_ICON3));
	m_ListBoxCtrlEx.InsertStr(_T("环境调节设备监控"), 3, _T("设备包括自动控制设置，手动控制两大部分。在线监控通过中间库与示范基地温室大棚监控主机闭环控制系统进行数据交换，基地监控主机的控制系统作为一个相对独立的系统运行。远程监控以状态监视报警为主，并实现组态动画显示设备运行状态、行程状态、开关状态和参数，如顶窗开闭、内外遮阳、保温网开闭行程状态；环流风机、增降温设施、补光照明、CO2释放、灌溉水泵等在线运行状态、参数进行监视。"), MAKEINTRESOURCE(IDI_ICON4));
	m_ListBoxCtrlEx.InsertStr(_T("视频监控"), 4, _T("当发生报警时，系统将自动创建媒体窗口，把相应报警区域的实时摄像图像切换到集成系统监控主屏幕，并可控制云台和变焦。"), MAKEINTRESOURCE(IDI_ICON5));
	m_ListBoxCtrlEx.InsertStr(_T("加载符号缓慢"), 5, _T("先取消勾选“Microsoft符号服务器”,清空符号缓存"), MAKEINTRESOURCE(IDI_ICON6));
	m_ListBoxCtrlEx.InsertStr(_T("指定符号加载行为 "), 6, _T("要从“符号文件(.pdb)位置”框位置自动加载的文件。"), MAKEINTRESOURCE(IDI_ICON7));
	m_ListBoxCtrlEx.InsertStr(_T("精准作业在线监测"), 7, _T("大田精准作业在线监测测产、变量施肥作业实时发送的数据，包括精准作业机械的空间移动位置（经度、纬度、海拔高度、航向、速度）、作业地块对象计量等数据[4]"), MAKEINTRESOURCE(IDI_ICON8));
	m_ListBoxCtrlEx.InsertStr(_T("观测报表递交"), 7, _T("作物生长发育观测报表、作物病虫害观测报表、设施蔬菜档案农业记载报表、大棚土壤理化测试记载表。"), MAKEINTRESOURCE(IDI_ICON9));
	m_ListBoxCtrlEx.InsertStr(_T("综合查询"), 7, _T("大棚外气象监测、大棚内气象、土壤、生物在线监测要素的逐时、逐日、月统计报表"), MAKEINTRESOURCE(IDI_ICON10));
	m_ListBoxCtrlEx.InsertStr(_T("王建锋农业数字化管理系统"), 7, _T("又称数字化农业管理系统"), MAKEINTRESOURCE(IDR_MAINFRAME));
	m_ListBoxCtrlEx.InsertStr(_T("欧洲应用系统的入口"), 7, _T("农业大数据平台"), MAKEINTRESOURCE(IDR_MAINFRAME));
	m_ListBoxCtrlEx.InsertStr(_T("应用系统的那些功能需要本土化开发"), 7, _T("中文版平台"), MAKEINTRESOURCE(IDR_MAINFRAME));
	m_ListBoxCtrlEx.InsertStr(_T("已有的数据库包括那些数据"), 7, _T("全球植被数据库3.0"), MAKEINTRESOURCE(IDR_MAINFRAME));

}


void CTTSControls_vs2015fw4Dlg::OnBnClickedButton2()
{
	//四个条件缺一Owner Draw — Variable(改变列表的高度和宽度) Has Strings — True
	// Type:Drop List  Sort:False
	// TODO: 在此添加控件通知处理程序代码
	m_imglist1.Create(16, 16, ILC_COLOR32 | ILC_MASK, 3, 1);
	m_imglist1.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	m_imglist1.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	m_imglist1.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_imglist1.Add(AfxGetApp()->LoadIcon(IDI_ICON4));

	CFont font;
	font.CreatePointFont(12, TEXT("黑体"));
	m_comboBox1.SetFont(&font);
	//点击一下那个combox控件的小三角, 现在拖动出现的那个框框的的长度, 拖到你觉得合适就行啦
	m_comboBox1.SetImageList(&m_imglist1);////必须保证图片数大于等于选项数目

	m_comboBox1.AddString(_T("王建锋"), 0);
	m_comboBox1.AddString(_T("王鹏飞"), 1);
	m_comboBox1.AddString(_T("肖文敏"), 2);
	m_comboBox1.AddString(_T("张老师"), 3);
	m_comboBox1.SetCurSel(1);

	//m_ComboBoxCtrltemp.AddNewString(_T("对弈"), IDI_ICON4);
	//m_ComboBoxCtrltemp.AddNewString(_T("无应"), IDI_ICON5);
	//m_ComboBoxCtrltemp.AddNewString(_T("攻守"), IDI_ICON6);
	//m_ComboBoxCtrltemp.SetFontType(10, _T("宋体"), false, RGB(0, 100, 255));
	//m_ComboBoxCtrltemp.SetRightButton(IDB_PNG1, IDB_PNG1);
	//m_ComboBoxCtrltemp.SetCurSel(0);

}


void CTTSControls_vs2015fw4Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_Teacher.GetWindowText(s2);

	m_EditCtrlTip.SetShowDimControl(FALSE);
	m_EditCtrlTip.SetWindowText(_T(""));
	m_EditCtrlTip.SetDimText(_T("王建锋提示：攻守对弈 应手无力"));
	m_EditCtrlTip.SetDimColor(RGB(0xC1, 0xCD, 0xC1));
	m_EditCtrlTip.SetDimOffset(-0x40, -0x40, -0x40);

	m_EditCtrlTip.SetShowDimControl(TRUE);


}


void CTTSControls_vs2015fw4Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tmp;
	m_EditCtrlImage.m_edit.GetWindowText(tmp);
	AfxMessageBox(tmp);
	m_EditCtrlImage.m_edit.SetWindowText(_T("收到了"));
	m_EditCtrlImage.m_edit.EnableWindow(TRUE);
	m_EditCtrlImage.m_edit.SetReadOnly(false);


	m_EditCtrlImagRight.m_edit.SetShowDimControl(FALSE);
	m_EditCtrlImagRight.m_edit.SetWindowText(_T(""));
	m_EditCtrlImagRight.m_edit.SetDimText(_T("waterwatch数据库包含30、100、150m的数据"));
	m_EditCtrlImagRight.m_edit.SetDimColor(RGB(0xC1, 0xCD, 0xC1));
	m_EditCtrlImagRight.m_edit.SetDimOffset(-0x40, -0x40, -0x40);
	m_EditCtrlImagRight.m_edit.SetShowDimControl(TRUE);


	//一定要加这一句
	//GetDlgItem(IDC_STATIC)->SetWindowText("your string");
	//GetDlgItem(IDC_STATIC)->GetParent()->RedrawWindow();
	//InvalidateRect(rc);
	// TODO: 在此添加控件通知处理程序代码
}


void CTTSControls_vs2015fw4Dlg::OnBnClickedButton4()
{
	CString col;    // 选择的字符串   
	CString col1;    // 选择的字符串   
	CString check;    // 选择的字符串 

	if (-1 != m_Row)        // 如果iItem不是-1，就说明有列表项被选择   
	{
		col = m_CListCtrlex.GetItemText(m_Row, 0);// 获取被选择列表项第一个子项的文本    
		col1 = m_CListCtrlex.GetItemText(m_Row, 1);// 获取被选择列表项第一个子项的文本    
		check = m_CListCtrlex.GetItemText(m_Row, 2);// 获取被选择列表项第一个子项的文本    

		
		//SetDlgItemText(IDC_LANG_SEL_EDIT, strLangName); // 将选择的语言显示与编辑框中  
		SetDlgItemText(IDC_EDITcol, col); // 将选择的语言显示与编辑框中  
		SetDlgItemText(IDC_EDITcol1, col1); // 将选择的语言显示与编辑框中 
		SetDlgItemText(IDC_CHECK1, check); // 将选择的语言显示与编辑框中
		GetDlgItem(IDC_CHECK1)->SetWindowText(check);

		if (check == "1")
		{
			CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
			pBtn->SetCheck(1);
		}
		else
		{
			CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
			pBtn->SetCheck(0);
		}
}
}

void CTTSControls_vs2015fw4Dlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tmp;
	m_comboBox1.GetWindowText(tmp);
	AfxMessageBox(tmp);
}


void CTTSControls_vs2015fw4Dlg::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tmp;
	m_ListBoxCtrlEx.GetText(m_ListBoxCtrlEx.GetCurSel(), tmp);
	AfxMessageBox(tmp);
}


void CTTSControls_vs2015fw4Dlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LVHITTESTINFO lvinfo; lvinfo.pt = point; lvinfo.flags = LVHT_ABOVE;//获取行信息

	//int nItem = m_ListCtrl.SubItemHitTest(&lvinfo); if (nItem != -1) {
	//	CString strtemp; strtemp.Format("单击的是第%d行第%d列", lvinfo.iItem, lvinfo.iSubItem);// lvinfo.iItem; //当前行号 vinfo.iSubItem 列//

	//显示当前单元格
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	DWORD   dwPos = GetMessagePos();
	CPoint   point(LOWORD(dwPos), HIWORD(dwPos));


	m_CListCtrlex.ScreenToClient(&point);


	LVHITTESTINFO   lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;

	int   nItem = m_CListCtrlex.SubItemHitTest(&lvinfo);
	if (nItem != -1)
	{
		CString   strtemp;
		strtemp.Format("单击的是第%d行第%d列 ", lvinfo.iItem, lvinfo.iSubItem);
		AfxMessageBox(strtemp);
	}
	// TODO: 在此添加控件通知处理程序代码

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1)
	{

		CString strtemp;
		strtemp.Format("单击的是第%d行第%d列，第一个子项的文本是%s",
			pNMListView->iItem, pNMListView->iSubItem, m_CListCtrlex.GetItemText(pNMListView->iItem, 0));// 获取被选择列表项第一个子项的文本    
		//SetDlgItemText(IDC_LANG_SEL_EDIT, strLangName); // 将选择的语言显示与编辑框中  

		AfxMessageBox(strtemp);
	}


	*pResult = 0;

}
void CTTSControls_vs2015fw4Dlg::OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult)
{

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CString col;    // 选择的字符串   
	CString col1;    // 选择的字符串   
	CString check;    // 选择的字符串   
	NMLISTVIEW* pNMListView = (NMLISTVIEW*)pNMHDR;// 可以想象成container_of() 

	m_Row = pNMListView->iItem;
	if (-1 != pNMListView->iItem)        // 如果iItem不是-1，就说明有列表项被选择   
	{
		/*
	//CString strWarn;
	//strWarn = m_CListCtrlex.GetItemText(0, 2);//显示第1行第3列的值
	//MessageBox("第1行第3列=" + strWarn);

	//m_CListCtrlex.SetItemText(0, 2, "1");
	//MessageBox("第1行第3列=1" );

		CString GetItemText(int nItem,	int nSubItem ) const;
		*/
		col = m_CListCtrlex.GetItemText(pNMListView->iItem, 0);// 获取被选择列表项第一个子项的文本    
		col1 = m_CListCtrlex.GetItemText(pNMListView->iItem, 1);// 获取被选择列表项第一个子项的文本    
		check = m_CListCtrlex.GetItemText(pNMListView->iItem, 2);// 获取被选择列表项第一个子项的文本    

		CString strtemp;
		strtemp.Format("单击的是第%d行第2列是%s",
			pNMListView->iItem, m_CListCtrlex.GetItemText(pNMListView->iItem, 2));// 获取被选择列表项第一个子项的文本    
		AfxMessageBox(strtemp);

		//SetDlgItemText(IDC_LANG_SEL_EDIT, strLangName); // 将选择的语言显示与编辑框中  
		SetDlgItemText(IDC_EDITcol, col); // 将选择的语言显示与编辑框中  
		SetDlgItemText(IDC_EDITcol1, col1); // 将选择的语言显示与编辑框中 
		SetDlgItemText(IDC_CHECK1, check); // 将选择的语言显示与编辑框中
		GetDlgItem(IDC_CHECK1)->SetWindowText(check);
		
		if (check == "1")
		{
			CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
			pBtn->SetCheck(1);
		}
		else
		{
			CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
			pBtn->SetCheck(0);
		}
	
	
	}
}

void CTTSControls_vs2015fw4Dlg::OnBnClickedButton8()
{
	CString wjf;
	wjf = "王建锋的butt";

	m_CMyButton.SetText(wjf);
	//设置文本颜色	
	m_CMyButton.SetForeColor(RGB(255, 255, 0)); ////文字颜色（黑色）
	//设置背景颜色
	m_CMyButton.SetBkColor(RGB(140, 140, 140));
	//设置字体(字体高度、字体名)
	//CFont  font; font.CreatePointFont(200, _T（＂宋体＂），NULL);
	//CreatePointFont(200, "Arial", pDC)
	m_CMyButton.SetTextFont(160,_T("宋体"));
	Invalidate();
	// TODO: 在此添加控件通知处理程序代码
}


void CTTSControls_vs2015fw4Dlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CTTSControls_vs2015fw4Dlg::OnBnClickedButton9()
{
	int m_nCurrentSel = m_CListCtrlex.GetSelectedCount();
	//点为空白处，没有点中某一行！不掉字段  逻辑与&&
	if ((m_nCurrentSel <= 0) || ((-1 == m_Row)))
	{
		AfxMessageBox("选中为空，没有点中某一行！");
		return;
	}
	

	CString check1;    // 选择的字符串
	CString col;    // 选择的字符串   
	CString col1;    // 选择的字符串   

	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	if (pBtn->GetCheck())//获取指定控件的指针 返回CWnd* 用于对话框类   

		m_CListCtrlex.SetItemText(m_Row, 2, "1");
	else
		m_CListCtrlex.SetItemText(m_Row, 2, "0");

	/*CListItemText::GenerateProperty(true, RGB(255, 0, 0));*/

	GetDlgItem(IDC_EDITcol)->GetWindowText(col);
	GetDlgItem(IDC_EDITcol1)->GetWindowText(col1);

	m_CListCtrlex.SetItemText(m_Row, 0, col);
	m_CListCtrlex.SetItemText(m_Row, 1, col1);

	//m_CListCtrlex.Invalidate();
	////if (GetDlgItemText(IDC_Number1, check1), check1 == "1")
	//if (GetDlgItem(IDC_EDITcol)->GetWindowText(check1), check1 == "1")//获取指定控件的指针 返回CWnd* 用于对话框类   
	//	m_CListCtrlex.SetItemText(0, 2, "1");
	// else
	//	 m_CListCtrlex.SetItemText(0, 2, "0");
 }


void CTTSControls_vs2015fw4Dlg::OnBnClickedButton10()
{
	int m_nCurrentSel = m_CListCtrlex.GetSelectedCount();
	//点为空白处，没有点中某一行！不掉字段
	if ((m_nCurrentSel <= 0) || ((-1 == m_Row)))
	{
		AfxMessageBox("选中为空，没有点中某一行！");
		return;
	}
	m_CListCtrlex.DeleteItem(m_Row);

}


void CTTSControls_vs2015fw4Dlg::OnBnClickedButton12()
{
	//主界面是对话框，可以直接调用    
	CDialog::OnOK();// 或者CDialog::OnCancel();
	//2、调用WINDOWS  API函数：
	//PostQuitMessage(0);//最常用 
	//ExitProcess(0);
}

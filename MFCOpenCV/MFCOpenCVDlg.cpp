
// MFCOpenCVDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCOpenCV.h"
#include "MFCOpenCVDlg.h"
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


// CMFCOpenCVDlg 对话框



CMFCOpenCVDlg::CMFCOpenCVDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCOPENCV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCOpenCVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCOpenCVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCOpenCVDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCOpenCVDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CMFCOpenCVDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDR_MAINFRAME, &CMFCOpenCVDlg::OnBnClickedMainframe)
	ON_BN_CLICKED(IDCANCEL, &CMFCOpenCVDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCOpenCVDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFCOpenCVDlg 消息处理程序

BOOL CMFCOpenCVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCOpenCVDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCOpenCVDlg::OnPaint()
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
HCURSOR CMFCOpenCVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//打开文件
void CMFCOpenCVDlg::OnBnClickedButton1()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT,
		NULL, this);   //选择文件对话框
	if (dlg.DoModal() == IDOK)
	{
		CString picPath = dlg.GetPathName();   //获取图片路径
		std::string spicPath = picPath.GetBuffer(0); //将CString类型转为string
		image = cv::imread(spicPath);
		showPic(image);
		showHis(image);

	}
}

//锐化
void CMFCOpenCVDlg::OnBnClickedButton2()
{
	cv::Mat result;
	sharpen(image, result);
	image = result.clone();
	result.release();
	showPic(image);
	showHis(image);
}




void CMFCOpenCVDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

//关闭图片
void CMFCOpenCVDlg::OnBnClickedMainframe()
{
	if (cv::getWindowProperty("Image", 0) != -1) {
		cv::destroyAllWindows();
		CWnd* pWnd = GetDlgItem(IDC_STATIC);
		pWnd->ShowWindow(FALSE);
		pWnd->ShowWindow(TRUE);
	}
}

void CMFCOpenCVDlg::OnBnClickedButton3()
{
	cv::Mat result;
	canny(image,result);
	image = result.clone();
	result.release();
	showPic(image);
}


void CMFCOpenCVDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


//显示图片
void CMFCOpenCVDlg::showPic(cv::Mat& myImage) const {
	if (cv::getWindowProperty("Image", 0) != -1) {
		cv::destroyAllWindows();
		CWnd* pWnd = GetDlgItem(IDC_STATIC);
		pWnd->ShowWindow(FALSE);
		pWnd->ShowWindow(TRUE);
	}

	CRect pect;
	CWnd* pWnd = GetDlgItem(IDC_STATIC);  //IDC_STATIC为picture控件ID
	pWnd->GetClientRect(&pect);
	int x = pect.Width();    //返回宽
	int y = pect.Height();   //返回高

	double proportion = myImage.cols / myImage.rows;
	cv::namedWindow("Image", CV_WINDOW_NORMAL);
	if (proportion < 1.0) {
		cv::resizeWindow("Image", y * myImage.cols / myImage.rows, y); //根据piccontrol的大下设置opencv窗口的大小
	}
	else {
		cv::resizeWindow("Image", x, myImage.rows * x / myImage.cols); //根据piccontrol的大下设置opencv窗口的大小
	}

	HWND hWnd = (HWND)cvGetWindowHandle("Image");//嵌套opencv窗口
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_STATIC)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	cv::imshow("Image", myImage);  //显示图像}
}

void CMFCOpenCVDlg::showHis(cv::Mat& myImage) const {
	Histogram1D h;
	cv::namedWindow("Histogram", 0);
	CRect pect;
	CWnd* pWnd = GetDlgItem(IDC_STATIC2);  //IDC_STATIC为picture控件ID
	pWnd->GetClientRect(&pect);
	int x = pect.Width();    //返回宽
	int y = pect.Height();   //返回高
	cv::resizeWindow("Histogram", x, y);
	HWND hWnd = (HWND)cvGetWindowHandle("Histogram");//嵌套opencv窗口
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_STATIC2)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	cv::imshow("Histogram", h.getHistogramImage(myImage));  //显示图像}
}


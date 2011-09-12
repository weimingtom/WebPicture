// WebPictureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WebPicture.h"
#include "WebPictureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWebPictureDlg dialog

CWebPictureDlg::CWebPictureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWebPictureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWebPictureDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWebPictureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWebPictureDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWebPictureDlg, CDialog)
	//{{AFX_MSG_MAP(CWebPictureDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(ID_VIEW, OnView)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWebPictureDlg message handlers

BOOL CWebPictureDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//拖放播放
	DragAcceptFiles(TRUE);			// 接收Drag & Drop(拖放)动作

	//窗体顶端显示
	//on top
	if ( GetExStyle() & WS_EX_TOPMOST )
    {
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0,
                SWP_NOSIZE | SWP_NOMOVE);
    }else
    {
        SetWindowPos(&wndTopMost, 0, 0, 0, 0,
                SWP_NOSIZE | SWP_NOMOVE);
    }

	CheckDlgButton(IDC_CHECK1,BST_CHECKED);
	CheckDlgButton(IDC_CHECK2,BST_CHECKED);
	CheckDlgButton(IDC_CHECK3,BST_CHECKED);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWebPictureDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWebPictureDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWebPictureDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CWebPictureDlg::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	//remove last outpug file
	OnRemove();

	SetActiveWindow();		// 使用中
	UINT nFiles = ::DragQueryFile(hDropInfo, (UINT)-1, NULL, 0);

	/*
	for (UINT i = 0; i < nFiles; i++) {
		char filename[MAX_PATH];
		::DragQueryFile(hDropInfo, i, filename, MAX_PATH);
	}
	*/

	UINT i = 0;
	char dirname[MAX_PATH];
	::DragQueryFile(hDropInfo, i, dirname, MAX_PATH);


	szLogName = dirname;
	szLogName += "\\list.html";
	FILE *fp;
	fp = fopen(szLogName,"w+");
	if(fp)
	{
		fprintf(fp,"<html>\n");
		fprintf(fp,"<head>\n");
		fprintf(fp,"<meta http-equiv=\"Content-Type\" content=\"text/html charset=UTF-8\">\n");
		fprintf(fp,"<title>My Pictures</title>\n");
		fprintf(fp,"<style type=\"text/css\">\n");
		fprintf(fp,"BODY {MARGIN-TOP: 70px; FONT-SIZE: 11px; BACKGROUND-ATTACHMENT: scroll; BACKGROUND-IMAGE: url(logo.gif); MARGIN-LEFT: 80px; BACKGROUND-REPEAT: no-repeat; FONT-FAMILY: Verdana, Arial, Helvetica, sans-serif; BACKGROUND-COLOR: #ffffff}\n");
		fprintf(fp,"TD {FONT-SIZE: 11px; FONT-FAMILY: Verdana, Arial, Helvetica, sans-serif}\n");
		fprintf(fp,"P  {	BACKGROUND: white}\n");
		fprintf(fp,"H1 {	FONT-SIZE: 12px; COLOR: #979797; FONT-FAMILY: Helvetica, Verdana, Arial}\n");
		fprintf(fp,"A:hover {	COLOR: #804c4c; BACKGROUND-COLOR: #f0efe3}\n");
		fprintf(fp,"H2 {	FONT-SIZE: 10px; COLOR: #000000; FONT-FAMILY: Verdana, Arial, Helvetica, sans-serif}\n");
		fprintf(fp,"H3 {	FONT-SIZE: 18px; COLOR: #000000; FONT-FAMILY: Verdana, Arial, Helvetica, sans-serif}\n");
		fprintf(fp,".textsm {	FONT-SIZE: 14px; COLOR: #000000; FONT-FAMILY: Verdana, Arial, Helvetica, sans-serif}\n");
		fprintf(fp,".textbg {	FONT-SIZE: 30px; COLOR: #000000; FONT-FAMILY: Verdana, Arial, Helvetica, sans-serif}\n");
		fprintf(fp,".textreg {	FONT-SIZE: 12px; COLOR: #979797; FONT-FAMILY: Verdana, Arial, Helvetica, sans-serif}\n");
		fprintf(fp,"</style>\n");
		fprintf(fp,"\n");
		fprintf(fp,"</head>\n");
		fprintf(fp,"<body bgcolor=\"#FFFFFF\" text=\"#000000\"><span class=\"textbg\">My Pictures</span><br>\n"); 
		fprintf(fp,"<span class=\"textsm\"></span><p>\n");
		fprintf(fp,"<span class=\"textreg\">My Pictures<br></span>\n");
		fprintf(fp,"<hr size=\"1\">\n");

		CFileFind ff;
		CString szDir = dirname;
		if(szDir.Right(1) != "\\")
			szDir += "\\";

		szDir += "*.*";

		BOOL res = ff.FindFile(szDir);

		while(res)
		{
			res = ff.FindNextFile();
			if(!ff.IsDirectory() && !ff.IsDots())
			{
				CString name = ff.GetFileName();
				CString szRight;
				szRight = name.Right(4);
				if(!szRight.CompareNoCase(".jpg") ||
				   !szRight.CompareNoCase(".png") ||
				   !szRight.CompareNoCase(".gif") ||
				   !szRight.CompareNoCase(".bmp"))
				{					
					fprintf(fp,"<p align=\"center\"><a href = \"%s\"><img src=\"%s\" title=\"%s\" bytes\" border=\"0\" width=\"640\"></a></p>\n",name,name,name);
				}
				else if(!szRight.CompareNoCase(".wav") ||
				   !szRight.CompareNoCase(".mp3") ||
				   !szRight.CompareNoCase(".avi") ||
				   !szRight.CompareNoCase(".mpg") ||
				   !szRight.CompareNoCase(".wma") ||
				   !szRight.CompareNoCase(".wmv") ||
				   !szRight.CompareNoCase(".mid"))
				{					
					fprintf(fp,"<p align=\"center\"><embed src=\"%s\" autostart=\"true\" loop=\"true\"></p>\n",name,name,name);
				}
			}
		}

		fprintf(fp,"</body>\n");
		fprintf(fp,"</html>\n");
		
		ff.Close();
		fclose(fp);
			
		//CString msg = dirname;
		//msg += _T("网页导出成功");
		//MessageBox(msg,"message",MB_OK);

		if(((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck())
		{
			ShowWindow(SW_MINIMIZE);
		}
		OnView();
	}
	else
	{
		MessageBox(_T("无法导出网页，请拖放一个可写的文件夹"),"message",MB_OK);
	}

	CDialog::OnDropFiles(hDropInfo);
}




void CWebPictureDlg::OnView() 
{
	// TODO: Add your control notification handler code here
	/*
	HKEY hkRoot,hSubKey; //定义注册表根关键字及子关键字 
	char ValueName[256]; 
	unsigned char DataValue[256]; 
	unsigned long cbValueName=256; 
	unsigned long cbDataValue=256; 
	CString ShellChar; //定义命令行 
	DWORD dwType; 
	
	if(szLogName == "")
		return;

	//打开注册表根关键字 
	if(RegOpenKey(HKEY_CLASSES_ROOT,NULL,&hkRoot)==ERROR_SUCCESS) 
	{ 
		//打开子关键字 
		if(RegOpenKeyEx(hkRoot, 
			"htmlfile\\shell\\open\\command", 
			0, 
			KEY_ALL_ACCESS, 
			&hSubKey)==ERROR_SUCCESS) 
		{ 
			//读取注册表，获取默认浏览器的命令行  
			RegEnumValue(hSubKey,  
				0, 
				ValueName, 
				&cbValueName, 
				NULL, 
				&dwType, 
				DataValue, 
				&cbDataValue); 
			// 调用参数（主页地址）赋值 
			ShellChar += (char *)DataValue; 
			ShellChar += " ";
			ShellChar += szLogName;
			//MessageBox(ShellChar);
			// 启动浏览器 
			//WinExec(ShellChar,SW_SHOW); 
			ShellExecute(GetSafeHwnd(),   
				NULL,   
				szLogName,   
				NULL, 
				NULL, 
				SW_SHOWNORMAL);
			//ShellExecute(NULL,_T("open"),_T("www.vcshare.net"),NULL,NULL, SW_MAXIMIZE);
			//ShellExecute(NULL,_T("open"), "iexplore.exe","www.xxx.net",NULL,SW_SHOW);   
		} 
		else 
			MessageBox("WEB浏览器打开错误！","错误",MB_OK); 
	} 
	else 
		MessageBox("WEB浏览器打开错误！","错误",MB_OK); 
	//关闭注册表 
	RegCloseKey(hSubKey); 
	RegCloseKey(hkRoot); 
	*/

	CString ShellChar; //定义命令行 
	
	if(szLogName == "")
		return;

	// 启动浏览器 
	ShellExecute(GetSafeHwnd(),   NULL,   szLogName,   NULL, NULL, SW_SHOWNORMAL);
	//ShellExecute(NULL,_T("open"),_T("www.vcshare.net"),NULL,NULL, SW_MAXIMIZE);
	//ShellExecute(NULL,_T("open"), "iexplore.exe","www.xxx.net",NULL,SW_SHOW);   
}

void CWebPictureDlg::OnRemove() 
{
	// TODO: Add your control notification handler code here
	if(((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck() && szLogName != "")
	{
		DeleteFile(	szLogName );
		szLogName = "";
	}
}

void CWebPictureDlg::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

void CWebPictureDlg::OnDestroy() 
{	

	OnRemove();	
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
}

void CWebPictureDlg::OnCheck3() 
{
	// TODO: Add your control notification handler code here
	//窗体顶端显示
	//on top
	if ( GetExStyle() & WS_EX_TOPMOST )
    {
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0,
                SWP_NOSIZE | SWP_NOMOVE);
    }else
    {
        SetWindowPos(&wndTopMost, 0, 0, 0, 0,
                SWP_NOSIZE | SWP_NOMOVE);
    }	
}

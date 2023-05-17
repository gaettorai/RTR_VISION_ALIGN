// RVisionDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "RVision.h"
#include "RVisionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CRVisionDlg* g_pDialog = NULL;
extern CRVisionDlg* g_pDialog;

HWND hCommWnd;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

extern ClickPoint stMeasure;
extern RecipeName stRecipe;
extern CameraParameter stCamera;
extern AlignParameter stAlign;
extern EdgeAlignParameter stEdgeAlign;
extern MarkAlignParameter stMarkAlign;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CRVisionDlg 대화 상자



CRVisionDlg::CRVisionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RVISION_DIALOG, pParent)
{
	g_pDialog = this;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_iStopBit = PORT_STOP;
	m_iSerialPort = PORT_NUM;
	m_iParity = PORT_PARITY;
	m_iDataBit = PORT_DATA;
	m_iBaudRate = PORT_BAUD;
}

void CRVisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ICON_LOGIN, m_icon_login);
	DDX_Control(pDX, IDC_BTN_MODE_ALIGN, m_btn_mode_align);
	DDX_Control(pDX, IDC_BTN_MODE_REVIEW, m_btn_mode_review);
	DDX_Control(pDX, IDC_BTN_MODE_FC, m_btn_mode_fc);
	DDX_Control(pDX, IDC_BTN_MODE_SETTING, m_btn_mode_setting);
	DDX_Control(pDX, IDC_ICON_HANDLE, m_icon_handle);
	DDX_Control(pDX, IDC_ICON_HEARTBEAT, m_icon_heartbeat);
	DDX_Control(pDX, IDC_ICON_CAMERA_1, m_icon_camera_1);
	DDX_Control(pDX, IDC_ICON_CAMERA_2, m_icon_camera_2);
	DDX_Control(pDX, IDC_ICON_CAMERA_3, m_icon_camera_3);
	DDX_Control(pDX, IDC_ICON_CAMERA_4, m_icon_camera_4);
	DDX_Control(pDX, IDC_ICON_CAMERA_5, m_icon_camera_5);
	DDX_Control(pDX, IDC_ICON_LIGHT, m_icon_light);
}

BEGIN_MESSAGE_MAP(CRVisionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_MODE_ALIGN, &CRVisionDlg::OnBnClickedBtnModeAlign)
	ON_BN_CLICKED(IDC_BTN_MODE_REVIEW, &CRVisionDlg::OnBnClickedBtnModeReview)
	ON_BN_CLICKED(IDC_BTN_MODE_FC, &CRVisionDlg::OnBnClickedBtnModeFc)
	ON_BN_CLICKED(IDC_BTN_MODE_SETTING, &CRVisionDlg::OnBnClickedBtnModeSetting)
	ON_STN_CLICKED(IDC_ICON_LOGIN, &CRVisionDlg::OnStnClickedIconLogin)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_HEARTBEAT, &CRVisionDlg::OnHeartbeat)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CRVisionDlg 메시지 처리기

BOOL CRVisionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	chkalarmdisplay = 0;
	// class 초기화
	InitClass();

	// 실행 파일 위치 찾기
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);
	strExeFilePath = chFilePath;
	int nInsert = strExeFilePath.Find(_T("RVision.exe"));

	strExeFilePath = strExeFilePath.Left(nInsert);
	strExeFilePath = strExeFilePath + _T("VisionData\\");	// 실행 파일 위치

	CString strRecipeNum;

	strRecipeNum = AfxGetApp()->GetProfileStringW(_T("RECIPE"), _T("RECIPE_NUM"));
	nSelectRecipe = _ttoi(strRecipeNum);

	strRecipeFilePath = strExeFilePath + _T("Recipe\\") + strRecipeNum + _T("\\");

	LoadRecipe(0);
	LoadRecipe(1);
	LoadRecipe(2);
	SaveRecipeName();

	// 초기화 Modify
	dAutosizing = 0;

	for (int i = 0; i < CamModify1; i++)
	{
		CamPoint_1[i].x = 0;
		CamPoint_1[i].y = 0;

		CamModifyPoint_1[i].x = 0;
		CamModifyPoint_1[i].y = 0;
	}


	for (int i = 0; i < CamModify2; i++)
	{
		CamPoint_2[i].x = 0;
		CamPoint_2[i].y = 0;

		CamModifyPoint_2[i].x = 0;
		CamModifyPoint_2[i].y = 0;
	}


	for (int i = 0; i < CamModify3; i++)
	{
		CamPoint_3[i].x = 0;
		CamPoint_3[i].y = 0;

		CamModifyPoint_3[i].x = 0;
		CamModifyPoint_3[i].y = 0;
	}


	for (int i = 0; i < CamModify4; i++)
	{
		CamPoint_4[i].x = 0;
		CamPoint_4[i].y = 0;

		CamModifyPoint_4[i].x = 0;
		CamModifyPoint_4[i].y = 0;
	}


	bool		bRet;
	CString		strPath;
	CString		strPath_2;
	CString		strData;
	TCHAR		szData[MAX_PATH];
	CString		strNum;

	int count;

	strPath = _T("D:\\R2R\\Files\\RVision\\ModifyCam\\Cam_1.ini");
	strPath_2 = _T("D:\\R2R\\Files\\RVision\\ModifyCam\\CamModify_1.ini");
	count = 0;

	for (int i = 0; i < CamModify1; i++)
	{
		strNum.Format(_T("%d"), i + 1);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(_T("X"), strNum, _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		CamPoint_1[count].x = _ttoi(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(_T("X"), strNum, _T("0"), szData, MAX_PATH, strPath_2);
		strData = szData;
		CamModifyPoint_1[count].x = _ttoi(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(_T("Y"), strNum, _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		CamPoint_1[count].y = _ttoi(szData);
		CamModifyPoint_1[count].y = _ttoi(szData);

		count++;
	}

	strPath = _T("D:\\R2R\\Files\\RVision\\ModifyCam\\Cam_2.ini");
	strPath_2 = _T("D:\\R2R\\Files\\RVision\\ModifyCam\\CamModify_2.ini");
	count = 0;

	for (int i = 0; i < CamModify2; i++)
	{
		strNum.Format(_T("%d"), i + 1);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(_T("X"), strNum, _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		CamPoint_2[count].x = _ttoi(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(_T("X"), strNum, _T("0"), szData, MAX_PATH, strPath_2);
		strData = szData;
		CamModifyPoint_2[count].x = _ttoi(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(_T("Y"), strNum, _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		CamPoint_2[count].y = _ttoi(szData);
		CamModifyPoint_2[count].y = _ttoi(szData);
		count++;
	}

	strPath = _T("D:\\R2R\\Files\\RVision\\ModifyCam\\Cam_3.ini");
	strPath_2 = _T("D:\\R2R\\Files\\RVision\\ModifyCam\\CamModify_3.ini");
	count = 0;

	for (int i = 0; i < CamModify3; i++)
	{
		strNum.Format(_T("%d"), i + 1);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(_T("X"), strNum, _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		CamPoint_3[count].x = _ttoi(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(_T("X"), strNum, _T("0"), szData, MAX_PATH, strPath_2);
		strData = szData;
		CamModifyPoint_3[count].x = _ttoi(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(_T("Y"), strNum, _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		CamPoint_3[count].y = _ttoi(szData);
		CamModifyPoint_3[count].y = _ttoi(szData);
		count++;
	}

	strPath = _T("D:\\R2R\\Files\\RVision\\ModifyCam\\Cam_4.ini");
	strPath_2 = _T("D:\\R2R\\Files\\RVision\\ModifyCam\\CamModify_4.ini");
	count = 0;

	for (int i = 0; i < CamModify4; i++)
	{
		strNum.Format(_T("%d"), i + 1);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(_T("X"), strNum, _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		CamPoint_4[count].x = _ttoi(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(_T("[X_MODIFY]"), strNum, _T("0"), szData, MAX_PATH, strPath_2);
		strData = szData;
		CamModifyPoint_4[count].x = _ttoi(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(_T("Y"), strNum, _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		CamPoint_4[count].y = _ttoi(szData);
		CamModifyPoint_4[count].y = _ttoi(szData);

		count++;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>

	CString SaveAlignMark;
	SaveAlignMark = strRecipeFilePath + _T("AlignMark.bmp");
	CT2CA ConvertStringAlign(SaveAlignMark);
	std::string	ImageNameAlign(ConvertStringAlign);
	MarkImageAlign = imread(ImageNameAlign);

	m_pBmpAlignMark = (BITMAPINFO*)m_chBmpAlignMark;
	m_pBmpAlignMark->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpAlignMark->bmiHeader.biWidth = MarkImageAlign.cols;
	m_pBmpAlignMark->bmiHeader.biHeight = -(MarkImageAlign.rows);
	m_pBmpAlignMark->bmiHeader.biBitCount = 24;
	m_pBmpAlignMark->bmiHeader.biPlanes = 1;
	m_pBmpAlignMark->bmiHeader.biCompression = BI_RGB;
	m_pBmpAlignMark->bmiHeader.biSizeImage = 0;
	m_pBmpAlignMark->bmiHeader.biXPelsPerMeter = 0;
	m_pBmpAlignMark->bmiHeader.biYPelsPerMeter = 0;
	m_pBmpAlignMark->bmiHeader.biClrUsed = 0;
	m_pBmpAlignMark->bmiHeader.biClrImportant = 0;

	CString strMarkFC;
	strMarkFC = strRecipeFilePath + _T("FieldCorrectionMark.bmp");
	CT2CA ConvertStringFC(strMarkFC);
	std::string	ImageNameFC(ConvertStringFC);
	MarkImageFC = imread(ImageNameFC);

	m_pBmpMark = (BITMAPINFO*)m_chBmpMark;
	m_pBmpMark->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpMark->bmiHeader.biWidth = MarkImageFC.cols;
	m_pBmpMark->bmiHeader.biHeight = -(MarkImageFC.rows);
	m_pBmpMark->bmiHeader.biBitCount = 24;
	m_pBmpMark->bmiHeader.biPlanes = 1;
	m_pBmpMark->bmiHeader.biCompression = BI_RGB;
	m_pBmpMark->bmiHeader.biSizeImage = 0;
	m_pBmpMark->bmiHeader.biXPelsPerMeter = 0;
	m_pBmpMark->bmiHeader.biYPelsPerMeter = 0;
	m_pBmpMark->bmiHeader.biClrUsed = 0;
	m_pBmpMark->bmiHeader.biClrImportant = 0;

	CString strMarkLaser;
	strMarkLaser = strExeFilePath + _T("Data\\LaserMark.bmp");
	CT2CA ConvertStringLaser(strMarkLaser);
	std::string	ImageNameLaser(ConvertStringLaser);
	MarkImageLaser = imread(ImageNameLaser);

	m_pBmpLaserMark = (BITMAPINFO*)m_chBmpLaserMark;
	m_pBmpLaserMark->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpLaserMark->bmiHeader.biWidth = MarkImageLaser.cols;
	m_pBmpLaserMark->bmiHeader.biHeight = -(MarkImageLaser.rows);
	m_pBmpLaserMark->bmiHeader.biBitCount = 24;
	m_pBmpLaserMark->bmiHeader.biPlanes = 1;
	m_pBmpLaserMark->bmiHeader.biCompression = BI_RGB;
	m_pBmpLaserMark->bmiHeader.biSizeImage = 0;
	m_pBmpLaserMark->bmiHeader.biXPelsPerMeter = 0;
	m_pBmpLaserMark->bmiHeader.biYPelsPerMeter = 0;
	m_pBmpLaserMark->bmiHeader.biClrUsed = 0;
	m_pBmpLaserMark->bmiHeader.biClrImportant = 0;

	resizeMagni = 2;

	// UI 설정 
	SettingUI();

	// 자식 다이얼로그 생성
	InitDialog();

	// 조명 연결 
	InitSocket();

	// 초기화 설정 
	SettingParam();

	// 카메라 설정 Display

	bChkCamera = false;
	ConnectCamera();

	ChkConnectCam1 = 0;
	ChkConnectCam2 = 0;
	ChkConnectCam3 = 0;
	ChkConnectCam4 = 0;
	ChkConnectCam5 = 0;

	LogWrite(NORMAL, "VISION PROGRAM 초기화 완료");

	Volume = NULL;
	Volume = AfxBeginThread(Volume_Thread, this);

	Proc = NULL;
	Proc = AfxBeginThread(Proc_Thread, this);

	SetTimer(1, 1000, NULL);

	stSendData.wdVisionErrorData.init();

	fontScale.CreatePointFont(100, _T("맑은 고딕"));

	dLCOffsetX = _wtof(AfxGetApp()->GetProfileStringW(_T("LASERCALIBRATION"), _T("OFFSET_X")));
	dLCOffsetY = _wtof(AfxGetApp()->GetProfileStringW(_T("LASERCALIBRATION"), _T("OFFSET_Y")));

	dManualOffsetX = _wtof(AfxGetApp()->GetProfileStringW(_T("ALIGN"), _T("MODIFYX")));
	dManualOffsetY = _wtof(AfxGetApp()->GetProfileStringW(_T("ALIGN"), _T("MODIFYY")));
	dManualOffsetT = _wtof(AfxGetApp()->GetProfileStringW(_T("ALIGN"), _T("MODIFYT")));

	bChkAlarm = false;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CRVisionDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CRVisionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CRVisionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CRVisionDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL CRVisionDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//CRect rect;

	//GetClientRect(rect);
	//pDC->FillSolidRect(rect, RGB(148, 148, 148));

	//return TRUE;

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL CRVisionDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CRVisionDlg::SettingUI()
{
	SetWindowPos(&wndTop, 0, 0, DialogWidth, WindowHeight, SWP_HIDEWINDOW);

	GetDlgItem(IDC_BTN_MODE_ALIGN)->MoveWindow(0, 0, 100, 25);
	GetDlgItem(IDC_BTN_MODE_REVIEW)->MoveWindow(100, 0, 100, 25);
	GetDlgItem(IDC_BTN_MODE_FC)->MoveWindow(200, 0, 100, 25);
	GetDlgItem(IDC_BTN_MODE_SETTING)->MoveWindow(300, 0, 100, 25);

	GetDlgItem(IDC_STATIC_RECIPE)->MoveWindow(420, 0, 110, 25);
	GetDlgItem(IDC_EDIT_RECIPE)->MoveWindow(530, 0, 82, 25);
	GetDlgItem(IDC_ICON_LOGIN)->MoveWindow(DialogWidth - 55, 0, 25, 25);

	GetDlgItem(IDC_ICON_HANDLE)->MoveWindow(DialogWidth - 30, 40, 30, 30);
	GetDlgItem(IDC_ICON_HEARTBEAT)->MoveWindow(DialogWidth - 30, 70, 30, 30);
	GetDlgItem(IDC_ICON_CAMERA_1)->MoveWindow(DialogWidth - 30, 100, 30, 30);
	GetDlgItem(IDC_ICON_CAMERA_2)->MoveWindow(DialogWidth - 30, 130, 30, 30);
	GetDlgItem(IDC_ICON_CAMERA_3)->MoveWindow(DialogWidth - 30, 160, 30, 30);
	GetDlgItem(IDC_ICON_CAMERA_4)->MoveWindow(DialogWidth - 30, 190, 30, 30);
	GetDlgItem(IDC_ICON_CAMERA_5)->MoveWindow(DialogWidth - 30, 220, 30, 30);
	GetDlgItem(IDC_ICON_LIGHT)->MoveWindow(DialogWidth - 30, 250, 30, 30);


	HFONT staticFont;
	staticFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_STATIC_RECIPE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);


	btnFont = new CFont;

	//폰트 생성
	btnFont->CreateFont(
		15,                            // 글자높이
		6,                            // 글자너비
		0,                            // 출력각도
		0,                            // 기준 선에서의각도
		FW_BOLD,                    // 글자굵기
		FALSE,                        // Italic 적용여부
		FALSE,                        // 밑줄적용여부
		FALSE,                        // 취소선적용여부
		DEFAULT_CHARSET,            // 문자셋종류
		OUT_DEFAULT_PRECIS,            // 출력정밀도
		CLIP_CHARACTER_PRECIS,        // 클리핑정밀도
		PROOF_QUALITY,                // 출력문자품질
		DEFAULT_PITCH,                // 글꼴Pitch
		_T("맑은 고딕")                // 글꼴
	);

	GetDlgItem(IDC_BTN_MODE_ALIGN)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_MODE_REVIEW)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_MODE_FC)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_MODE_SETTING)->SetFont(btnFont);

	m_btn_mode_align.EnableWindowsTheming(FALSE);
	m_btn_mode_review.EnableWindowsTheming(FALSE);
	m_btn_mode_fc.EnableWindowsTheming(FALSE);
	m_btn_mode_setting.EnableWindowsTheming(FALSE);

	m_btn_mode_align.SetFaceColor(ColorGreen);
	m_btn_mode_review.SetFaceColor(ColorBasic);
	m_btn_mode_fc.SetFaceColor(ColorBasic);
	m_btn_mode_setting.SetFaceColor(ColorBasic);

	m_bmp_login.LoadBitmapW(IDB_BITMAP_LOGIN);
	m_bmp_logout.LoadBitmapW(IDB_BITMAP_LOGOUT);

	m_bmp_ledon.LoadBitmapW(IDB_BITMAP_LED_ON);
	m_bmp_ledoff.LoadBitmapW(IDB_BITMAP_LED_OFF);
	m_bmp_ledon2.LoadBitmapW(IDB_BITMAP_LED_ON2);
	m_bmp_ledoff2.LoadBitmapW(IDB_BITMAP_LED_OFF2);

	m_bmp_markpos.LoadBitmapW(IDB_BITMAP_MARKPOS);
	m_bmp_edgepos.LoadBitmapW(IDB_BITMAP_EDGEPOS);

	m_icon_login.SetBitmap(m_bmp_logout);
	m_icon_handle.SetBitmap(m_bmp_ledoff);
	m_icon_heartbeat.SetBitmap(m_bmp_ledoff);
	m_icon_camera_1.SetBitmap(m_bmp_ledoff);
	m_icon_camera_2.SetBitmap(m_bmp_ledoff);
	m_icon_camera_3.SetBitmap(m_bmp_ledoff);
	m_icon_camera_4.SetBitmap(m_bmp_ledoff);
	m_icon_camera_5.SetBitmap(m_bmp_ledoff);
	m_icon_light.SetBitmap(m_bmp_ledoff);
}


void CRVisionDlg::InitDialog()
{
	dlgVisionAlign = new RVisionAlign;
	dlgVisionAlign->Create(IDD_RVISION_ALIGN, this);
	dlgVisionAlign->MoveWindow(0, 25, WindowWidth, WindowHeight - 25);
	dlgVisionAlign->ShowWindow(SW_SHOW);

	dlgVisionReview = new RVisionReview;
	dlgVisionReview->Create(IDD_RVISION_REVIEW, this);
	dlgVisionReview->MoveWindow(0, 25, WindowWidth, WindowHeight - 25);
	dlgVisionReview->ShowWindow(SW_HIDE);

	dlgVisionFC = new RVisionFC;
	dlgVisionFC->Create(IDD_RVISION_FC, this);
	dlgVisionFC->MoveWindow(0, 25, WindowWidth, WindowHeight - 25);
	dlgVisionFC->ShowWindow(SW_HIDE);

	dlgVisionSetting = new RVisionSetting;
	dlgVisionSetting->Create(IDD_RVISION_SETTING, this);
	dlgVisionSetting->MoveWindow(0, 25, WindowWidth, WindowHeight - 25);
	dlgVisionSetting->ShowWindow(SW_HIDE);

	dlgPopupAlarm = new PopupAlarm;
	dlgPopupAlarm->Create(IDD_POPUP_ALARM, this);
	dlgPopupAlarm->MoveWindow(1720, 980, 200, 80);
	dlgPopupAlarm->ShowWindow(SW_HIDE);

	dlgPopupPreprocessImg = new PopupPreprocessImg;
	dlgPopupPreprocessImg->Create(IDD_POPUP_PREPROCESS_IMG, this);
	dlgPopupPreprocessImg->ShowWindow(SW_HIDE);
}


void CRVisionDlg::ConnectCamera()
{
	cBaumer = new connect_Baumer;

	cBaumer->Init();
	cBaumer->Open();
	cBaumer->Connect();

	Vision = NULL;
	Vision = AfxBeginThread(Vision_Thread, this);

	//// 카메라 노출 초기화 
	for (int i = 0; i < 5; i++)
	{
		if (cBaumer->Status[i] == true)
		{
			cBaumer->m_camera_set[i].pDevicef->GetRemoteNode("ExposureTime")->SetDouble(stCamera.nExposureTime[i]);
		}
	}

	bChkCamera = true;
}


void CRVisionDlg::InitSocket()
{
	//m_comm = new CCommThread;

	if (mLightPort.m_bConnected == FALSE)//포트가 닫혀 있을 경우에만 포트를 열기 위해
	{
		if (mLightPort.OpenPort(byIndexComPort(m_iSerialPort), byIndexBaud(m_iBaudRate), byIndexData(m_iDataBit), byIndexStop(m_iStopBit), byIndexParity(m_iParity)) == TRUE)
		{
			//	ThreadWatchComm(m_comm);

			SetCSR(0);
			SetSVR(stCamera.nLight[0]);

			SetCSR(1);
			SetSVR(stCamera.nLight[1]);

			SetCSR(2);
			SetSVR(stCamera.nLight[2]);

			SetCSR(3);
			SetSVR(stCamera.nLight[3]);

			SetCSR(4);
			SetSVR(stCamera.nLight[4]);
		}
	}

	else
	{
		//AfxMessageBox(_T("Already Port open"));
	}
}


void CRVisionDlg::SettingParam()
{
	// 측정 관련 사항	
	MeasurementCount = 0;
	clickCount = 0;

	CHK_PROC = false;
	CHK_ALIGN = false;
	CHK_SETTING = false;
	ChkFindFC = false;
	ChkFindLaser = false;
	CHK_FC = false;

	hdcMarkFC = dlgVisionSetting->dlgSettingFC->GetDlgItem(IDC_PIC_MARK)->GetDC()->m_hDC;
	SetStretchBltMode(hdcMarkFC, COLORONCOLOR);

	hdcMarkAlign = dlgVisionSetting->dlgSettingAlignMark->GetDlgItem(IDC_PIC_MARK)->GetDC()->m_hDC;
	SetStretchBltMode(hdcMarkAlign, COLORONCOLOR);

	hdcMarkLaser = dlgVisionSetting->dlgSettingLaser->GetDlgItem(IDC_PIC_LASERMARK)->GetDC()->m_hDC;
	SetStretchBltMode(hdcMarkLaser, COLORONCOLOR);

	hdcProcImg = dlgPopupPreprocessImg->GetDlgItem(IDC_PIC_PREPROCESS_IMG)->GetDC()->m_hDC;
	SetStretchBltMode(hdcProcImg, COLORONCOLOR);

	hdcMarkPos = dlgVisionSetting->dlgSettingAlign->GetDlgItem(IDC_PIC_MARK_POS)->GetDC()->m_hDC;
	SetStretchBltMode(hdcMarkPos, COLORONCOLOR);

	if (bChkMark == 1)
	{
		dlgVisionAlign->DisplayMark(true);
		dlgVisionAlign->DisplayEdge(false);
	}
	else if (bChkEdge == 1)
	{
		dlgVisionAlign->DisplayMark(false);
		dlgVisionAlign->DisplayEdge(true);
	}

	CString strRecipeNum;
	strRecipeNum.Format(_T("#%d"), nSelectRecipe);

	GetDlgItem(IDC_EDIT_RECIPE)->SetWindowTextW(strRecipeNum);
	dlgVisionSetting->dlgSettingCamera->m_edit_recipe_select.SetWindowTextW(strRecipeNum);
	dlgVisionSetting->dlgSettingAlign->m_edit_recipe_select.SetWindowTextW(strRecipeNum);
	dlgVisionSetting->dlgSettingAlignMark->m_edit_recipe_select.SetWindowTextW(strRecipeNum);
	dlgVisionSetting->dlgSettingFC->m_edit_recipe_select.SetWindowTextW(strRecipeNum);

	dlgVisionSetting->dlgSettingCamera->m_edit_recipe_name.SetWindowTextW(stRecipe.strRecipeName[nSelectRecipe - 1]);
	dlgVisionSetting->dlgSettingAlign->m_edit_recipe_name.SetWindowTextW(stRecipe.strRecipeName[nSelectRecipe - 1]);
	dlgVisionSetting->dlgSettingAlignMark->m_edit_recipe_name.SetWindowTextW(stRecipe.strRecipeName[nSelectRecipe - 1]);
	dlgVisionSetting->dlgSettingFC->m_edit_recipe_name.SetWindowTextW(stRecipe.strRecipeName[nSelectRecipe - 1]);

	dlgVisionSetting->dlgSettingCamera->m_slider_light_1.SetRange(0, 255);
	dlgVisionSetting->dlgSettingCamera->m_slider_light_2.SetRange(0, 255);
	dlgVisionSetting->dlgSettingCamera->m_slider_light_3.SetRange(0, 255);
	dlgVisionSetting->dlgSettingCamera->m_slider_light_4.SetRange(0, 255);
	dlgVisionSetting->dlgSettingCamera->m_slider_light_5.SetRange(0, 255);

	// pen 색상
	cPenCrossline.CreatePen(PS_SOLID, 1, RGB(GetRValue(cCrossLineColor), GetGValue(cCrossLineColor), GetBValue(cCrossLineColor)));
	cPenROI.CreatePen(PS_SOLID, 1, RGB(GetRValue(cROIColor), GetGValue(cROIColor), GetBValue(cROIColor)));

	pen_red.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	pen_green.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	pen_white.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
}


void CRVisionDlg::PathSize()
{
	avail.QuadPart = 0L;
	total.QuadPart = 0L;
	free.QuadPart = 0L;


	CString strMsg;

	////////// Drive D
// D:\의 하드디스크 용량 정보를 받아 옴
	GetDiskFreeSpaceEx(TEXT("D:\\"), &avail, &total, &free);

	// GByte 로 표현을 하기 위한 부분
	nFree = (int)(free.QuadPart >> 30);

	// 사용 가능한 공간이 전체 공간의 20%이하일 경우 
	if (nAvail < nTotal * 0.8)
	{
		//CString path = _T("D:\\VisionData");

	}
}


void CRVisionDlg::ChkFolder(CString strPath)
{
	CFileFind finderCount;

	BOOL bWorkingCount = finderCount.FindFile(strPath + "\\*.*");
	int count = 0;

	// 전체 폴더의 갯수 확인
	while (bWorkingCount)
	{
		bWorkingCount = finderCount.FindNextFile();
		if (finderCount.IsDots())
			continue;

		if (finderCount.IsDirectory())
		{
			count++;
		}
	}

	CFileFind finder;
	CTime tCreate;

	BOOL bWorking = finder.FindFile(strPath + "\\*.*");

	pFolderInfo = new FolderInfo[count];
	count = 0;

	// 폴더의 생성일자 폴더명 확인
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
		{
			continue;
		}

		if (finder.IsDirectory())
		{
			CString strfilepath = finder.GetFilePath();
			finder.GetCreationTime(tCreate);

			pFolderInfo[count].nCreateTime = tCreate;
			pFolderInfo[count].strFolderName = strfilepath;
			count++;
		}
	}

	CTime min = pFolderInfo[0].nCreateTime;
	int num = 0;

	// 가장 오래된 폴더 찾기
	for (int i = 0; i < count; i++)
	{
		if (min > pFolderInfo[i].nCreateTime)
		{
			min = pFolderInfo[i].nCreateTime;
			num = i;
		}
	}

	DeleteFolder(pFolderInfo[num].strFolderName);
	RemoveDirectory(pFolderInfo[num].strFolderName);

	delete pFolderInfo;
}


void CRVisionDlg::DeleteFolder(CString strPath)
{
	CFileFind finder;
	CTime tCreate;

	BOOL bWorking = finder.FindFile(strPath + "\\*.*");

	// 폴더의 생성일자 폴더명 확인
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
		{
			continue;
		}

		if (finder.IsDirectory())
		{
			CString strfilepath = finder.GetFilePath();
			DeleteImage(strfilepath);
			RemoveDirectory(strfilepath);
		}
	}
}


void CRVisionDlg::DeleteImage(CString strPath)
{
	CFileFind finder;
	CTime tCreate;

	BOOL bWorking = finder.FindFile(strPath + "\\*.*");

	// 폴더의 생성일자 폴더명 확인
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
		{
			continue;
		}

		CString strfilepath = finder.GetFilePath();
		DeleteFile(strfilepath);
	}
}


void CRVisionDlg::SetCSR(int nCase)
{
	int nValue;
	if (nCase == 0)
		nValue = 1;

	else if (nCase == 1)
		nValue = 2;

	else if (nCase == 2)
		nValue = 4;

	else if (nCase == 3)
		nValue = 8;

	else if (nCase == 4)
		nValue = 16;

	BYTE bValue;
	bValue = (BYTE)nValue;

	BYTE SendData[6] = { 0x01, 0x00, 0x01, 0x20, bValue, 0x04 };

	mLightPort.WriteComm(SendData, sizeof(SendData));
	mLightPort.WriteComm(SendData, sizeof(SendData));
}


void CRVisionDlg::SetSVR(int nCase)
{
	BYTE SendData[6] = { 0x01, 0x00, 0x01, 0x28, nCase, 0x04 };
	mLightPort.WriteComm(SendData, sizeof(SendData));
	mLightPort.WriteComm(SendData, sizeof(SendData));
}


void CRVisionDlg::SelectRecipe(int nCase)
{
	CString strRecipeNum;

	strRecipeNum.Format(_T("Recipe\\%d\\"), nCase);

	strRecipeFilePath = strExeFilePath + strRecipeNum;

	LoadRecipe(0);
	LoadRecipe(1);
	LoadRecipe(2);

	if (bJigProcess == true)
	{
		bChkEdge = false;
		bChkMark = true;
	}

	dlgVisionSetting->dlgSettingCamera->DisplayParam();
	dlgVisionSetting->dlgSettingAlign->m_cmb_selectcam.SetCurSel(0);
	dlgVisionSetting->dlgSettingAlign->DisplayParam(0);
	dlgVisionSetting->dlgSettingAlignMark->DisplayParam();

	CString strDisplayNum;
	strDisplayNum.Format(_T("#%d"), nCase);
	GetDlgItem(IDC_EDIT_RECIPE)->SetWindowTextW(strDisplayNum);
	dlgVisionSetting->dlgSettingCamera->m_edit_recipe_select.SetWindowTextW(strDisplayNum);
	dlgVisionSetting->dlgSettingAlign->m_edit_recipe_select.SetWindowTextW(strDisplayNum);
	dlgVisionSetting->dlgSettingAlignMark->m_edit_recipe_select.SetWindowTextW(strDisplayNum);
	dlgVisionSetting->dlgSettingFC->m_edit_recipe_select.SetWindowTextW(strDisplayNum);
	dlgVisionSetting->dlgSettingCamera->m_edit_recipe_name.SetWindowTextW(stRecipe.strRecipeName[nCase - 1]);
	dlgVisionSetting->dlgSettingAlign->m_edit_recipe_name.SetWindowTextW(stRecipe.strRecipeName[nCase - 1]);
	dlgVisionSetting->dlgSettingAlignMark->m_edit_recipe_name.SetWindowTextW(stRecipe.strRecipeName[nCase - 1]);
	dlgVisionSetting->dlgSettingFC->m_edit_recipe_name.SetWindowTextW(stRecipe.strRecipeName[nCase - 1]);

	nSelectRecipe = nCase;

	if (bChkMark == 1)
	{
		dlgVisionAlign->DisplayMark(true);
		dlgVisionAlign->DisplayEdge(false);

		dlgVisionSetting->dlgSettingAlign->m_pic_mark_pos.SetBitmap(m_bmp_markpos);

		if (dlgVisionSetting->dlgSettingAlign->ChkModify == true)
			dlgVisionSetting->dlgSettingAlign->m_edit_align_width.EnableWindow(true);
	}

	else if (bChkEdge == 1)
	{
		dlgVisionAlign->DisplayMark(false);
		dlgVisionAlign->DisplayEdge(true);

		dlgVisionSetting->dlgSettingAlign->m_pic_mark_pos.SetBitmap(m_bmp_edgepos);

		dlgVisionSetting->dlgSettingAlign->m_edit_align_width.EnableWindow(false);
	}
}


void CRVisionDlg::InitClass()
{
	// CAMERA 설정 관련 CLASS
	for (int i = 0; i < 5; i++)
	{
		stCamera.strName[i] = _T("");
		stCamera.nExposureTime[i] = 0;
		stCamera.nLight[i] = 0;
		stCamera.dCenterX[i] = 0;
		stCamera.dCenterY[i] = 0;
	}

	cNameColor = 0;
	cCrossLineColor = 0;
	CHK_NAME = false;
	CHK_CROSSLINE = false;
	CHK_ROI = false;

	// REVIEW 측정 관련 CLASS
	for (int i = 0; i < 10; i++)
	{
		stMeasure.ChkMeasurement[i] = false;
		stMeasure.CaseMeasurement[i] = 0;
		stMeasure.FirstPoint[i].x = 0;
		stMeasure.FirstPoint[i].y = 0;
		stMeasure.SecondPoint[i].x = 0;
		stMeasure.SecondPoint[i].y = 0;
		stMeasure.ThirdPoint[i].x = 0;
		stMeasure.ThirdPoint[i].y = 0;
	}

	// ALIGN 에 사용되는 PARAMETER
	for (int i = 0; i < 4; i++)
	{
		stAlign.nBinaryLow[i] = 0;
		stAlign.nOpen[i] = 0;
		stAlign.nClose[i] = 0;

		stAlign.ROIStart[i].x = 0;
		stAlign.ROIStart[i].y = 0;
		stAlign.ROIEnd[i].x = 0;
		stAlign.ROIEnd[i].y = 0;

		stAlign.AlignPoint[i].x = 0;
		stAlign.AlignPoint[i].y = 0;
	}

	// ALIGN (EDGE) 검출 관련 CLASS
	for (int i = 0; i < 4; i++)
	{
		stEdgeAlign.EdgeStart[i].x = 0;
		stEdgeAlign.EdgeStart[i].y = 0;

		stEdgeAlign.EdgeEnd[i].x = 0;
		stEdgeAlign.EdgeEnd[i].y = 0;

		stEdgeAlign.ChkFind[i] = false;
		stEdgeAlign.ChkMistake[i] = false;

		stEdgeAlign.ClickPoint[i] = 0;
		stEdgeAlign.FirstPoint[i] = 0;
		stEdgeAlign.SecondPoint[i] = 0;

		stEdgeAlign.Slope[i] = 0.0;
	}

	// ALIGN (MARK) 검출 관련 CLASS
	for (int i = 0; i < 4; i++)
	{
		stMarkAlign.ChkFind[i] = false;
		stMarkAlign.nChkFindMark[i] = 0;
		stMarkAlign.ChkManualFind[i] = false;
		stMarkAlign.nChkManualMark[i] = 0;

		stMarkAlign.ClickPoint[i] = 0;
		stMarkAlign.FirstPoint[i] = 0;
		stMarkAlign.SecondPoint[i] = 0;
	}

	for (int i = 0; i < 100; i++)
	{
		stRecipe.nNum[i] = 0;
		stRecipe.bChkEmpty[i] = false;
		stRecipe.strRecipeName[i] = _T("empty");
	}
}


void CRVisionDlg::SaveRecipe(int nCase)
{
	bool		bRet;
	CString		strPath;
	CString		strTag;
	CString		strData;

	// Camera
	if (nCase == 0)
	{
		strPath = strRecipeFilePath + _T("RecipeCamera.ini");

		for (int i = 0; i < 5; i++)
		{
			strTag.Format(_T("CAMERA%d"), i);

			strData = stCamera.strName[i];
			WritePrivateProfileString(strTag, _T("NAME"), strData, strPath);

			strData.Format(_T("%d"), stCamera.nExposureTime[i]);
			WritePrivateProfileString(strTag, _T("EXPOSURETIME"), strData, strPath);

			strData.Format(_T("%d"), stCamera.nLight[i]);
			WritePrivateProfileString(strTag, _T("LIGHT"), strData, strPath);
		}

		strTag.Format(_T("DISPLAY"));

		strData.Format(_T("%d"), cNameColor);
		WritePrivateProfileString(strTag, _T("NAME_COLORREF"), strData, strPath);

		strData.Format(_T("%d"), cCrossLineColor);
		WritePrivateProfileString(strTag, _T("CROSSLINE_COLORREF"), strData, strPath);

		strData.Format(_T("%d"), cROIColor);
		WritePrivateProfileString(strTag, _T("ROI_COLORREF"), strData, strPath);

		if (CHK_NAME == true)
			strData = _T("1");

		else if (CHK_NAME == false)
			strData = _T("0");

		WritePrivateProfileString(strTag, _T("CHK_NAME"), strData, strPath);

		if (CHK_CROSSLINE == true)
			strData = _T("1");

		else if (CHK_CROSSLINE == false)
			strData = _T("0");

		WritePrivateProfileString(strTag, _T("CHK_CROSSLINE"), strData, strPath);

		if (CHK_ROI == true)
			strData = _T("1");

		else if (CHK_ROI == false)
			strData = _T("0");

		WritePrivateProfileString(strTag, _T("CHK_ROI"), strData, strPath);


		//strTag.Format(_T("CAMERA_POSITION"));

		//strData.Format(_T("%.3f"), dLGentryPos);
		//WritePrivateProfileString(strTag, _T("LEFT_GENTRY_POS"), strData, strPath);

		//strData.Format(_T("%.3f"), dRGentryPos);
		//WritePrivateProfileString(strTag, _T("RIGHT_GENTRY_POS"), strData, strPath);

		//strData.Format(_T("%.3f"), dCam1Pos);
		//WritePrivateProfileString(strTag, _T("CAMERA1_POS"), strData, strPath);

		//strData.Format(_T("%.3f"), dCam2Pos);
		//WritePrivateProfileString(strTag, _T("CAMERA2_POS"), strData, strPath);

		//strData.Format(_T("%.3f"), dCam3Pos);
		//WritePrivateProfileString(strTag, _T("CAMERA3_POS"), strData, strPath);

		//strData.Format(_T("%.3f"), dCam4Pos);
		//WritePrivateProfileString(strTag, _T("CAMERA4_POS"), strData, strPath);
	}

	// Align
	else if (nCase == 1)
	{
		strPath = strRecipeFilePath + _T("RecipeAlign.ini");

		for (int i = 0; i < 4; i++)
		{
			strTag.Format(_T("ALIGN%d"), i);

			strData.Format(_T("%d"), stAlign.nBinaryLow[i]);
			WritePrivateProfileString(strTag, _T("BINARY_LOW"), strData, strPath);

			strData.Format(_T("%d"), stAlign.nOpen[i]);
			WritePrivateProfileString(strTag, _T("OPEN"), strData, strPath);

			strData.Format(_T("%d"), stAlign.nClose[i]);
			WritePrivateProfileString(strTag, _T("CLOSE"), strData, strPath);

			strData.Format(_T("%d"), stAlign.ROIStart[i].x);
			WritePrivateProfileString(strTag, _T("STARTPOINT_X"), strData, strPath);

			strData.Format(_T("%d"), stAlign.ROIStart[i].y);
			WritePrivateProfileString(strTag, _T("STARTPOINT_Y"), strData, strPath);

			strData.Format(_T("%d"), stAlign.ROIEnd[i].x);
			WritePrivateProfileString(strTag, _T("ENDPOINT_X"), strData, strPath);

			strData.Format(_T("%d"), stAlign.ROIEnd[i].y);
			WritePrivateProfileString(strTag, _T("ENDPOINT_Y"), strData, strPath);
		}

		strTag.Format(_T("SETTING"));

		if (bChkEdge == true)
			strData = _T("1");

		else if (bChkEdge == false)
			strData = _T("0");

		WritePrivateProfileString(strTag, _T("USING_EDGE"), strData, strPath);

		if (bChkMark == true)
			strData = _T("1");

		else if (bChkMark == false)
			strData = _T("0");

		WritePrivateProfileString(strTag, _T("USING_MARK"), strData, strPath);

		strData.Format(_T("%d"), nSelecteAlignMethod);
		WritePrivateProfileString(strTag, _T("ALIGN_METHOD"), strData, strPath);

		strData.Format(_T("%.3f"), dAlignMatchrate);
		WritePrivateProfileString(strTag, _T("MATCHRATE"), strData, strPath);

		strData.Format(_T("%.3f"), dRangeHLevel);
		WritePrivateProfileString(strTag, _T("RANGE_LEVEL_H"), strData, strPath);

		strData.Format(_T("%.3f"), dRangeMistake);
		WritePrivateProfileString(strTag, _T("RANGE_MISTAKE"), strData, strPath);

		strData.Format(_T("%.3f"), dRangeX);
		WritePrivateProfileString(strTag, _T("RANGE_X"), strData, strPath);

		strData.Format(_T("%.3f"), dRangeY);
		WritePrivateProfileString(strTag, _T("RANGE_Y"), strData, strPath);

		strData.Format(_T("%.3f"), dRangeT);
		WritePrivateProfileString(strTag, _T("RANGE_T"), strData, strPath);

		strData.Format(_T("%.2f"), dAlignWidth);
		WritePrivateProfileString(strTag, _T("ALIGN_WIDTH"), strData, strPath);

		strData.Format(_T("%.2f"), dAlignHeight);
		WritePrivateProfileString(strTag, _T("ALIGN_HEIGHT"), strData, strPath);

		strData.Format(_T("%.3f"), dAlignOffsetX);
		WritePrivateProfileString(strTag, _T("ALIGN_OFFSET_X"), strData, strPath);

		strData.Format(_T("%.3f"), dAlignOffsetY);
		WritePrivateProfileString(strTag, _T("ALIGN_OFFSET_Y"), strData, strPath);

		strData.Format(_T("%.6f"), dAlignOffsetT);
		WritePrivateProfileString(strTag, _T("ALIGN_OFFSET_T"), strData, strPath);
	}

	// FC
	else if (nCase == 2)
	{
		strPath = strRecipeFilePath + _T("RecipeFC.ini");

		strTag.Format(_T("FieldCorrection"));

		strData.Format(_T("%.2f"), dMatchRate_FC);
		WritePrivateProfileString(strTag, _T("MATCHRATE"), strData, strPath);

		strData.Format(_T("%d"), nBinaryLow_FC);
		WritePrivateProfileString(strTag, _T("BINARY_LOW"), strData, strPath);

		strData.Format(_T("%d"), nOpen_FC);
		WritePrivateProfileString(strTag, _T("OPEN"), strData, strPath);

		strData.Format(_T("%d"), nClose_FC);
		WritePrivateProfileString(strTag, _T("CLOSE"), strData, strPath);
	}
}


void CRVisionDlg::LoadRecipe(int nCase)
{
	bool		bRet;
	CString		strPath;
	CString		strTag;
	CString		strData;
	TCHAR		szData[MAX_PATH];

	// camera setting
	if (nCase == 0)
	{
		strPath = strRecipeFilePath + _T("RecipeCamera.ini");

		for (int i = 0; i < 5; i++)
		{
			strTag.Format(_T("CAMERA%d"), i);

			ZeroMemory(szData, MAX_PATH);
			GetPrivateProfileString(strTag, _T("NAME"), _T("NAME"), szData, MAX_PATH, strPath);
			strData = szData;
			stCamera.strName[i] = szData;

			ZeroMemory(szData, MAX_PATH);
			GetPrivateProfileString(strTag, _T("EXPOSURETIME"), _T("40000"), szData, MAX_PATH, strPath);
			strData = szData;
			stCamera.nExposureTime[i] = _ttoi(szData);

			ZeroMemory(szData, MAX_PATH);
			GetPrivateProfileString(strTag, _T("LIGHT"), _T("125"), szData, MAX_PATH, strPath);
			strData = szData;
			stCamera.nLight[i] = _ttoi(szData);

			ZeroMemory(szData, MAX_PATH);
			GetPrivateProfileString(strTag, _T("CENTER_X"), _T("0"), szData, MAX_PATH, strPath);
			strData = szData;
			stCamera.dCenterX[i] = _wtof(szData);

			ZeroMemory(szData, MAX_PATH);
			GetPrivateProfileString(strTag, _T("CENTER_Y"), _T("0"), szData, MAX_PATH, strPath);
			strData = szData;
			stCamera.dCenterY[i] = _wtof(szData);
		}

		strTag = _T("DISPLAY");

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("NAME_COLORREF"), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		cNameColor = _ttoi(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("CROSSLINE_COLORREF"), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		cCrossLineColor = _ttoi(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("ROI_COLORREF"), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		cROIColor = _ttoi(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("CHK_NAME "), _T("1"), szData, MAX_PATH, strPath);
		strData = szData;

		if (_ttoi(szData) == 1)
			CHK_NAME = true;

		else if (_ttoi(szData) == 0)
			CHK_NAME = false;

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("CHK_CROSSLINE "), _T("1"), szData, MAX_PATH, strPath);
		strData = szData;

		if (_ttoi(szData) == 1)
			CHK_CROSSLINE = true;

		else if (_ttoi(szData) == 0)
			CHK_CROSSLINE = false;

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("CHK_ROI "), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;

		if (_ttoi(szData) == 1)
			CHK_ROI = true;

		else if (_ttoi(szData) == 0)
			CHK_ROI = false;


		strTag = _T("CAMERA_POSITION");

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("LEFT_GENTRY_POS "), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		dLGentryStdPos = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("RIGHT_GENTRY_POS "), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		dRGentryStdPos = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("CAMERA1_POS "), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		dCam1StdPos = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("CAMERA2_POS "), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		dCam2StdPos = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("CAMERA3_POS "), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		dCam3StdPos = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("CAMERA4_POS "), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		dCam4StdPos = _wtof(szData);
	}

	// align setting
	else if (nCase == 1)
	{
		strPath = strRecipeFilePath + _T("RecipeAlign.ini");

		for (int i = 0; i < 4; i++)
		{
			strTag.Format(_T("ALIGN%d"), i);

			ZeroMemory(szData, MAX_PATH);
			GetPrivateProfileString(strTag, _T("BINARY_LOW"), _T("0"), szData, MAX_PATH, strPath);
			strData = szData;
			stAlign.nBinaryLow[i] = _ttoi(szData);

			ZeroMemory(szData, MAX_PATH);
			GetPrivateProfileString(strTag, _T("OPEN"), _T("1"), szData, MAX_PATH, strPath);
			strData = szData;
			stAlign.nOpen[i] = _ttoi(szData);

			ZeroMemory(szData, MAX_PATH);
			GetPrivateProfileString(strTag, _T("CLOSE"), _T("1"), szData, MAX_PATH, strPath);
			strData = szData;
			stAlign.nClose[i] = _ttoi(szData);

			ZeroMemory(szData, MAX_PATH);
			GetPrivateProfileString(strTag, _T("STARTPOINT_X"), _T("0"), szData, MAX_PATH, strPath);
			strData = szData;
			stAlign.ROIStart[i].x = _ttoi(szData);

			ZeroMemory(szData, MAX_PATH);
			GetPrivateProfileString(strTag, _T("STARTPOINT_Y"), _T("0"), szData, MAX_PATH, strPath);
			strData = szData;
			stAlign.ROIStart[i].y = _ttoi(szData);

			ZeroMemory(szData, MAX_PATH);
			GetPrivateProfileString(strTag, _T("ENDPOINT_X"), _T("2448"), szData, MAX_PATH, strPath);
			strData = szData;
			stAlign.ROIEnd[i].x = _ttoi(szData);

			ZeroMemory(szData, MAX_PATH);
			GetPrivateProfileString(strTag, _T("ENDPOINT_Y"), _T("2048"), szData, MAX_PATH, strPath);
			strData = szData;
			stAlign.ROIEnd[i].y = _ttoi(szData);
		}

		strTag.Format(_T("SETTING"));

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("USING_EDGE"), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;

		if (_ttoi(strData) == 1)
			bChkEdge = true;

		else if (_ttoi(strData) == 0)
			bChkEdge = false;

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("USING_MARK"), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;

		if (_ttoi(strData) == 1)
			bChkMark = true;

		else if (_ttoi(strData) == 0)
			bChkMark = false;

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("ALIGN_METHOD"), _T("1"), szData, MAX_PATH, strPath);
		strData = szData;
		nSelecteAlignMethod = _ttoi(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("MATCHRATE"), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		dAlignMatchrate = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("RANGE_LEVEL_H "), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		dRangeHLevel = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("RANGE_MISTAKE "), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		dRangeMistake = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("RANGE_X"), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		dRangeX = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("RANGE_Y"), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		dRangeY = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("RANGE_T"), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		dRangeT = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("ALIGN_WIDTH "), _T("167"), szData, MAX_PATH, strPath);
		strData = szData;
		dAlignWidth = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("ALIGN_HEIGHT"), _T("167"), szData, MAX_PATH, strPath);
		strData = szData;
		dAlignHeight = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("ALIGN_OFFSET_X"), _T("0.000"), szData, MAX_PATH, strPath);
		strData = szData;
		dAlignOffsetX = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("ALIGN_OFFSET_Y"), _T("0.000"), szData, MAX_PATH, strPath);
		strData = szData;
		dAlignOffsetY = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("ALIGN_OFFSET_T"), _T("0.000000"), szData, MAX_PATH, strPath);
		strData = szData;
		dAlignOffsetT = _wtof(szData);

		//ZeroMemory(szData, MAX_PATH);
		//GetPrivateProfileString(strTag, _T("MANUAL_OFFSET_X"), _T("0.000"), szData, MAX_PATH, strPath);
		//strData = szData;
		//dManualOffsetX = _wtof(szData);

		//ZeroMemory(szData, MAX_PATH);
		//GetPrivateProfileString(strTag, _T("MANUAL_OFFSET_Y"), _T("0.00"), szData, MAX_PATH, strPath);
		//strData = szData;
		//dManualOffsetY = _wtof(szData);

		//ZeroMemory(szData, MAX_PATH);
		//GetPrivateProfileString(strTag, _T("MANUAL_OFFSET_T"), _T("0.000000"), szData, MAX_PATH, strPath);
		//strData = szData;
		//dManualOffsetT = _wtof(szData);
	}

	// fc setting
	else if (nCase == 2)
	{
		strPath = strRecipeFilePath + _T("RecipeFC.ini");

		strTag.Format(_T("FieldCorrection"));

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("MATCHRATE"), _T("80.0"), szData, MAX_PATH, strPath);
		strData = szData;
		dMatchRate_FC = _wtof(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("BINARY_LOW"), _T("0"), szData, MAX_PATH, strPath);
		strData = szData;
		nBinaryLow_FC = _ttoi(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("OPEN"), _T("1"), szData, MAX_PATH, strPath);
		strData = szData;
		nOpen_FC = _ttoi(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("CLOSE"), _T("1"), szData, MAX_PATH, strPath);
		strData = szData;
		nClose_FC = _ttoi(strData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("GAIN"), _T("1"), szData, MAX_PATH, strPath);
		strData = szData;
		dGain = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("NEWCAL"), _T(""), szData, MAX_PATH, strPath);
		strData = szData;
		dNewcal = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("POINT"), _T("3"), szData, MAX_PATH, strPath);
		strData = szData;
		nPatternPoint = _ttoi(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("LENGTH"), _T("10.0"), szData, MAX_PATH, strPath);
		strData = szData;
		dPatternLength = _wtof(szData);

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("OLDCTFILE "), _T("OLDCTFILE"), szData, MAX_PATH, strPath);
		strData = szData;
		strOldctFile = strData;

		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, _T("NEWCTFILE "), _T("NEWCTFILE"), szData, MAX_PATH, strPath);
		strData = szData;
		strNewctFile = strData;
	}
}


void CRVisionDlg::ExcutionDialog(int nCase)
{
	DisplayColor(nCase);

	dlgVisionAlign->ShowWindow(SW_HIDE);
	dlgVisionReview->ShowWindow(SW_HIDE);
	dlgVisionFC->ShowWindow(SW_HIDE);
	dlgVisionSetting->ShowWindow(SW_HIDE);


	if (nCase == 0)
	{
		dlgVisionAlign->ShowWindow(SW_SHOW);
		CHK_SETTING = false;
	}

	else if (nCase == 1)
	{
		dlgVisionReview->ShowWindow(SW_SHOW);
		CHK_SETTING = false;
	}

	else if (nCase == 2)
	{
		dlgVisionFC->ShowWindow(SW_SHOW);
		CHK_SETTING = false;
	}

	else if (nCase == 3)
	{
		dlgVisionSetting->ShowWindow(SW_SHOW);
		CHK_SETTING = true;

		dlgVisionSetting->m_btn_camera.SetFaceColor(ColorBasic);
		dlgVisionSetting->m_btn_align.SetFaceColor(ColorBasic);
		dlgVisionSetting->m_btn_alignmark.SetFaceColor(ColorBasic);
		dlgVisionSetting->m_btn_fc.SetFaceColor(ColorBasic);
		dlgVisionSetting->m_btn_laser.SetFaceColor(ColorGreen);

		dlgVisionSetting->dlgSettingCamera->ShowWindow(SW_HIDE);
		dlgVisionSetting->dlgSettingAlign->ShowWindow(SW_HIDE);
		dlgVisionSetting->dlgSettingAlignMark->ShowWindow(SW_HIDE);
		dlgVisionSetting->dlgSettingFC->ShowWindow(SW_HIDE);
		dlgVisionSetting->dlgSettingLaser->ShowWindow(SW_SHOW);

		dlgVisionSetting->dlgSettingCamera->SelectCam = 4;

		dlgVisionSetting->SelectSetting = 4;
	}

	else if (nCase == 4)
	{
		dlgVisionSetting->ShowWindow(SW_SHOW);
		CHK_SETTING = true;
	}
}


void CRVisionDlg::ExcutionManualAlign()
{
	CWnd* pWnd = AfxGetMainWnd();

	CRect rcManualAlign;
	GetWindowRect(rcManualAlign);

	rcManualAlign.top += 30;
	rcManualAlign.left;
	rcManualAlign.right = rcManualAlign.left + 624;
	rcManualAlign.bottom = rcManualAlign.top + 800;

	dlgPopupManualAlign.rcDialog = rcManualAlign;

	dlgPopupManualAlign.AlignResult1 = stAlign.AlignPoint[0];
	dlgPopupManualAlign.AlignResult2 = stAlign.AlignPoint[1];
	dlgPopupManualAlign.AlignResult3 = stAlign.AlignPoint[2];

	if (bJigProcess == true)
	{
		dlgPopupManualAlign.AlignResult4.x = 0;
		dlgPopupManualAlign.AlignResult4.y = 0;
	}

	else if (bJigProcess == false)
		dlgPopupManualAlign.AlignResult4 = stAlign.AlignPoint[3];

	dlgPopupManualAlign.dModifyX = dModifyX - dErrorX - dPostX - dLCOffsetX - dManualOffsetX;
	dlgPopupManualAlign.dModifyY = dModifyY - dErrorY - dPostY - dLCOffsetY - dManualOffsetY;
	dlgPopupManualAlign.dModifyT = dModifyT - dPostT - dManualOffsetT;


	strLogData.Format(_T("[Manual AutoSizing] dModify, dPost, dmanualoffset [%.8f, %.8f, %.8f]"), dModifyT, dPostT, dManualOffsetT);
	csLogData = CStringA(strLogData);
	cFullLog = csLogData;
	cpFullLog = const_cast<char*>(cFullLog);
	LogWrite(ALIGNMENT, cpFullLog);


	if (dlgVisionAlign->bChkLevel == true)
		dlgPopupManualAlign.ChkNG_LEVEL = true;

	else if (dlgVisionAlign->bChkLevel == false)
		dlgPopupManualAlign.ChkNG_LEVEL = false;

	if (dlgVisionAlign->bChkModifyX == true)
		dlgPopupManualAlign.ChkNG_X = true;

	else if (dlgVisionAlign->bChkModifyX == false)
		dlgPopupManualAlign.ChkNG_X = false;

	if (dlgVisionAlign->bChkModifyY == true)
		dlgPopupManualAlign.ChkNG_Y = true;

	else if (dlgVisionAlign->bChkModifyY == false)
		dlgPopupManualAlign.ChkNG_Y = false;

	if (dlgVisionAlign->bChkModifyT == true)
		dlgPopupManualAlign.ChkNG_T = true;

	else if (dlgVisionAlign->bChkModifyT == false)
		dlgPopupManualAlign.ChkNG_T = false;

	if (bChkEdge == 1)
		dlgPopupManualAlign.nCase = 0;

	else if (bChkMark == 1)
		dlgPopupManualAlign.nCase = 1;

	if (dlgPopupManualAlign.DoModal() == IDOK)   // 다이얼로그가 종료될 때 반환되는 값을 검사, OK 버튼으로 종료되었을 경우 IDOK를 반환
	{
		CString strValue;
		strValue.Format(_T("%.3f"), dlgPopupManualAlign.dModifyX);
		dlgVisionAlign->GetDlgItem(IDC_STATIC_XMODIFY_VALUE)->SetWindowTextW(strValue);

		strValue.Format(_T("%.3f"), dlgPopupManualAlign.dModifyY);
		dlgVisionAlign->GetDlgItem(IDC_STATIC_YMODIFY_VALUE)->SetWindowTextW(strValue);

		strValue.Format(_T("%.3f"), dlgPopupManualAlign.dModifyT);
		dlgVisionAlign->GetDlgItem(IDC_STATIC_TMODIFY_VALUE)->SetWindowTextW(strValue);

		if (abs(dlgPopupManualAlign.dModifyX) > dRangeX)
		{
			dlgVisionAlign->bChkModifyX = false;
			dlgVisionAlign->GetDlgItem(IDC_STATIC_XMODIFY_JUDGE)->SetWindowTextW(_T("NG"));
		}

		else if (abs(dlgPopupManualAlign.dModifyX) <= dRangeX)
		{
			dlgVisionAlign->bChkModifyX = true;
			dlgVisionAlign->GetDlgItem(IDC_STATIC_XMODIFY_JUDGE)->SetWindowTextW(_T("OK"));
		}

		if (abs(dlgPopupManualAlign.dModifyY) > dRangeY)
		{
			dlgVisionAlign->bChkModifyY = false;
			dlgVisionAlign->GetDlgItem(IDC_STATIC_YMODIFY_JUDGE)->SetWindowTextW(_T("NG"));
		}

		else if (abs(dlgPopupManualAlign.dModifyY) <= dRangeY)
		{
			dlgVisionAlign->bChkModifyY = true;
			dlgVisionAlign->GetDlgItem(IDC_STATIC_YMODIFY_JUDGE)->SetWindowTextW(_T("OK"));
		}

		if (abs(dlgPopupManualAlign.dModifyT) > dRangeT)
		{
			dlgVisionAlign->bChkModifyT = false;
			dlgVisionAlign->GetDlgItem(IDC_STATIC_TMODIFY_JUDGE)->SetWindowTextW(_T("NG"));
		}

		else if (abs(dlgPopupManualAlign.dModifyT) <= dRangeT)
		{
			dlgVisionAlign->bChkModifyT = true;
			dlgVisionAlign->GetDlgItem(IDC_STATIC_TMODIFY_JUDGE)->SetWindowTextW(_T("OK"));
		}

		dlgVisionAlign->bChkLevel = false;
		dlgVisionAlign->GetDlgItem(IDC_STATIC_LEVEL_H_JUDGE)->SetWindowTextW(_T("-"));

		dlgVisionAlign->bChkMistake = false;
		dlgVisionAlign->GetDlgItem(IDC_STATIC_MISTAKE_JUDGE)->SetWindowTextW(_T("-"));

		dModifyX = dlgPopupManualAlign.dModifyX;
		dModifyY = dlgPopupManualAlign.dModifyY;
		dModifyT = dlgPopupManualAlign.dModifyT;

		if (bChkEdge == true)
		{
			if (nSelecteAlignMethod == 1)
				strLogData.Format(_T("[EDGE ALIGN] CAM(1) ALIGN POINT [%d, %d] / CAM(2) ALIGN POINT [%d, %d] / CAM(3) ALIGN POINT [%d, %d] / CAM(4) ALIGN POINT [%d, %d]"),
					dlgPopupManualAlign.AlignResult1.x, dlgPopupManualAlign.AlignResult1.y, dlgPopupManualAlign.AlignResult2.x, dlgPopupManualAlign.AlignResult2.y,
					dlgPopupManualAlign.AlignResult3.x, dlgPopupManualAlign.AlignResult3.y, dlgPopupManualAlign.AlignResult4.x, dlgPopupManualAlign.AlignResult4.y);

			else if (nSelecteAlignMethod == 2)
				strLogData.Format(_T("[EDGE ALIGN] CAM(1) ALIGN POINT [%d, %d] / CAM(2) ALIGN POINT [%d, %d]"),
					dlgPopupManualAlign.AlignResult1.x, dlgPopupManualAlign.AlignResult1.y, dlgPopupManualAlign.AlignResult2.x, dlgPopupManualAlign.AlignResult2.y);

			else if (nSelecteAlignMethod == 3)
				strLogData.Format(_T("[EDGE ALIGN] CAM(3) ALIGN POINT [%d, %d] / CAM(4) ALIGN POINT [%d, %d]"),
					dlgPopupManualAlign.AlignResult3.x, dlgPopupManualAlign.AlignResult3.y, dlgPopupManualAlign.AlignResult4.x, dlgPopupManualAlign.AlignResult4.y);

			else if (nSelecteAlignMethod == 4)
				strLogData.Format(_T("[EDGE ALIGN] CAM(1) ALIGN POINT [%d, %d] / CAM(3) ALIGN POINT [%d, %d]"),
					dlgPopupManualAlign.AlignResult1.x, dlgPopupManualAlign.AlignResult1.y, dlgPopupManualAlign.AlignResult3.x, dlgPopupManualAlign.AlignResult3.y);

			else if (nSelecteAlignMethod == 5)
				strLogData.Format(_T("[EDGE ALIGN] CAM(2) ALIGN POINT [%d, %d] / CAM(4) ALIGN POINT [%d, %d]"),
					dlgPopupManualAlign.AlignResult2.x, dlgPopupManualAlign.AlignResult2.y, dlgPopupManualAlign.AlignResult4.x, dlgPopupManualAlign.AlignResult4.y);


			csLogData = CStringA(strLogData);
			cFullLog = csLogData;
			cpFullLog = const_cast<char*>(cFullLog);
			LogWrite(ALIGNMENT, cpFullLog);
		}

		if (bChkMark == true)
		{
			if (bJigProcess == true)
			{
				strLogData.Format(_T("[MARK ALIGN] CAM(1) ALIGN POINT [%d, %d] / CAM(2) ALIGN POINT [%d, %d] / CAM(3) ALIGN POINT [%d, %d]"),
					dlgPopupManualAlign.AlignResult1.x, dlgPopupManualAlign.AlignResult1.y, dlgPopupManualAlign.AlignResult2.x, dlgPopupManualAlign.AlignResult2.y,
					dlgPopupManualAlign.AlignResult3.x, dlgPopupManualAlign.AlignResult3.y);
			}

			else if (bJigProcess == false)
			{
				if (nSelecteAlignMethod == 1)
					strLogData.Format(_T("[MARK ALIGN] CAM(1) ALIGN POINT [%d, %d] / CAM(2) ALIGN POINT [%d, %d] / CAM(3) ALIGN POINT [%d, %d] / CAM(4) ALIGN POINT [%d, %d]"),
						dlgPopupManualAlign.AlignResult1.x, dlgPopupManualAlign.AlignResult1.y, dlgPopupManualAlign.AlignResult2.x, dlgPopupManualAlign.AlignResult2.y,
						dlgPopupManualAlign.AlignResult3.x, dlgPopupManualAlign.AlignResult3.y, dlgPopupManualAlign.AlignResult4.x, dlgPopupManualAlign.AlignResult4.y);

				else if (nSelecteAlignMethod == 2)
					strLogData.Format(_T("[MARK ALIGN] CAM(1) ALIGN POINT [%d, %d] / CAM(2) ALIGN POINT [%d, %d]"),
						dlgPopupManualAlign.AlignResult1.x, dlgPopupManualAlign.AlignResult1.y, dlgPopupManualAlign.AlignResult2.x, dlgPopupManualAlign.AlignResult2.y);

				else if (nSelecteAlignMethod == 3)
					strLogData.Format(_T("[MARK ALIGN] CAM(3) ALIGN POINT [%d, %d] / CAM(4) ALIGN POINT [%d, %d]"),
						dlgPopupManualAlign.AlignResult3.x, dlgPopupManualAlign.AlignResult3.y, dlgPopupManualAlign.AlignResult4.x, dlgPopupManualAlign.AlignResult4.y);

				else if (nSelecteAlignMethod == 4)
					strLogData.Format(_T("[MARK ALIGN] CAM(1) ALIGN POINT [%d, %d] / CAM(3) ALIGN POINT [%d, %d]"),
						dlgPopupManualAlign.AlignResult1.x, dlgPopupManualAlign.AlignResult1.y, dlgPopupManualAlign.AlignResult3.x, dlgPopupManualAlign.AlignResult3.y);

				else if (nSelecteAlignMethod == 5)
					strLogData.Format(_T("[MARK ALIGN] CAM(2) ALIGN POINT [%d, %d] / CAM(4) ALIGN POINT [%d, %d]"),
						dlgPopupManualAlign.AlignResult2.x, dlgPopupManualAlign.AlignResult2.y, dlgPopupManualAlign.AlignResult4.x, dlgPopupManualAlign.AlignResult4.y);
			}

			csLogData = CStringA(strLogData);
			cFullLog = csLogData;
			cpFullLog = const_cast<char*>(cFullLog);
			LogWrite(ALIGNMENT, cpFullLog);
		}

		if (nSelecteAlignMethod == 1)
		{
			// Position 계산
			dXPosition_1 = (dlgPopupManualAlign.AlignResult1.x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_2 = (dlgPopupManualAlign.AlignResult2.x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_3 = (dlgPopupManualAlign.AlignResult3.x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_4 = (dlgPopupManualAlign.AlignResult4.x - CamWidth / 2) * (AlignResolution / 1000);

			dYPosition_1 = (dlgPopupManualAlign.AlignResult1.y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_2 = (dlgPopupManualAlign.AlignResult2.y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_3 = (dlgPopupManualAlign.AlignResult3.y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_4 = (dlgPopupManualAlign.AlignResult4.y - CamHeight / 2) * (AlignResolution / 1000);

			dSizeX = (dAlignWidth + (((dXPosition_3 + dXPosition_4) / 2) - (dXPosition_1 + dXPosition_2) / 2)) / dAlignWidth;
			dSizeY = (dAlignHeight + (((dYPosition_2 + dYPosition_4) / 2) - (dYPosition_1 + dYPosition_3) / 2)) / dAlignHeight;
		}

		else if (nSelecteAlignMethod == 2)
		{
			dXPosition_1 = (dlgPopupManualAlign.AlignResult1.x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_2 = (dlgPopupManualAlign.AlignResult2.x - CamWidth / 2) * (AlignResolution / 1000);

			dYPosition_1 = (dlgPopupManualAlign.AlignResult1.y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_2 = (dlgPopupManualAlign.AlignResult2.y - CamHeight / 2) * (AlignResolution / 1000);

			dSizeX = 1.0;
			dSizeY = (dAlignHeight + (dYPosition_2 - dYPosition_1)) / dAlignHeight;
		}

		else if (nSelecteAlignMethod == 3)
		{
			dXPosition_3 = (dlgPopupManualAlign.AlignResult3.x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_4 = (dlgPopupManualAlign.AlignResult4.x - CamWidth / 2) * (AlignResolution / 1000);

			dYPosition_3 = (dlgPopupManualAlign.AlignResult3.y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_4 = (dlgPopupManualAlign.AlignResult4.y - CamHeight / 2) * (AlignResolution / 1000);

			dSizeX = 1.0;
			dSizeY = (dAlignHeight + (dYPosition_4 - dYPosition_3)) / dAlignHeight;
		}

		else if (nSelecteAlignMethod == 4)
		{
			dXPosition_1 = (dlgPopupManualAlign.AlignResult1.x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_3 = (dlgPopupManualAlign.AlignResult3.x - CamWidth / 2) * (AlignResolution / 1000);

			dYPosition_1 = (dlgPopupManualAlign.AlignResult1.y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_3 = (dlgPopupManualAlign.AlignResult3.y - CamHeight / 2) * (AlignResolution / 1000);

			dSizeX = (dAlignWidth + (dXPosition_3 - dXPosition_1)) / dAlignWidth;
			dSizeY = 1.0;
		}

		else if (nSelecteAlignMethod == 5)
		{
			dXPosition_2 = (dlgPopupManualAlign.AlignResult2.x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_4 = (dlgPopupManualAlign.AlignResult4.x - CamWidth / 2) * (AlignResolution / 1000);

			dYPosition_2 = (dlgPopupManualAlign.AlignResult2.y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_4 = (dlgPopupManualAlign.AlignResult4.y - CamHeight / 2) * (AlignResolution / 1000);

			dSizeX = (dAlignWidth + (dXPosition_4 - dXPosition_2)) / dAlignWidth;
			dSizeY = 1.0;
		}

		if (dAutosizing == 1)
		{
			dSizeX = 1.0;
			dSizeY = 1.0;
		}

		strLogData.Format(_T("[Manual AutoSizing] AutoSizing Return Value [%.8f, %.8f]"), dSizeX, dSizeY);
		csLogData = CStringA(strLogData);
		cFullLog = csLogData;
		cpFullLog = const_cast<char*>(cFullLog);
		LogWrite(ALIGNMENT, cpFullLog);

		// 값 display 
		strValue.Format(_T("%.3fmm"), dModifyX);
		dlgVisionAlign->GetDlgItem(IDC_STATIC_XMODIFY_VALUE)->SetWindowTextW(strValue);

		strValue.Format(_T("%.3fmm"), dModifyY);
		dlgVisionAlign->GetDlgItem(IDC_STATIC_YMODIFY_VALUE)->SetWindowTextW(strValue);

		strValue.Format(_T("%.6f˚"), dModifyT);
		dlgVisionAlign->GetDlgItem(IDC_STATIC_TMODIFY_VALUE)->SetWindowTextW(strValue);

		strLogData.Format(_T("[Manual Vision 오차] X축 보정 값 : %.3fmm[%d], Y축 보정 값 : %.3fmm[%d], THETA 보정 값 : %.6f˚[%d]"),
			dModifyX, dlgVisionAlign->bChkModifyX, dModifyY, dlgVisionAlign->bChkModifyY, dModifyT, dlgVisionAlign->bChkModifyT);

		csLogData = CStringA(strLogData);
		cFullLog = csLogData;
		cpFullLog = const_cast<char*>(cFullLog);
		LogWrite(ALIGNMENT, cpFullLog);

		dErrorLGentry = dLGentryPos - (dLGentryStdPos - ((dAlignWidth - 167) / 2));
		dErrorRGentry = (dRGentryStdPos - ((dAlignWidth - 167) / 2)) - dRGentryPos;

		dErrorCam1 = (dCam1StdPos - ((dAlignHeight - 167) / 2)) - dCam1Pos;
		dErrorCam2 = (dCam2StdPos + ((dAlignHeight - 167) / 2)) - dCam2Pos;
		dErrorCam3 = (dCam3StdPos - ((dAlignHeight - 167) / 2)) - dCam3Pos;
		dErrorCam4 = dCam4Pos - (dCam4StdPos - ((dAlignHeight - 167) / 2));

		dErrorX = (dErrorLGentry + dErrorRGentry) / 2;
		dErrorY = (dErrorCam1 + dErrorCam2 + dErrorCam3 + dErrorCam4) / 4;

		strLogData.Format(_T("[Position 오차] Gentry Shift Value : %.3fmm, Vision Cam Shift Value : %.3fmm"), dErrorX, dErrorY);
		csLogData = CStringA(strLogData);
		cFullLog = csLogData;
		cpFullLog = const_cast<char*>(cFullLog);
		LogWrite(ALIGNMENT, cpFullLog);

		dModifyX += dErrorX;
		dModifyY += dErrorY;

		CString strVal;
		double dVal;

		strLogData.Format(_T("[Laser Calibration offset] X축 offset : %.3fmm Y축 offset : %.3fmm"), dLCOffsetX, dLCOffsetY);
		csLogData = CStringA(strLogData);
		cFullLog = csLogData;
		cpFullLog = const_cast<char*>(cFullLog);
		LogWrite(ALIGNMENT, cpFullLog);

		dModifyX += dLCOffsetX;
		dModifyY -= dLCOffsetY;

		strLogData.Format(_T("[Manual offset] X축 offset : %.3fmm Y축 offset : %.3fmm Theta offset : %.6f˚"), dManualOffsetX, dManualOffsetY, dManualOffsetT);
		csLogData = CStringA(strLogData);
		cFullLog = csLogData;
		cpFullLog = const_cast<char*>(cFullLog);
		LogWrite(ALIGNMENT, cpFullLog);

		dModifyX += dManualOffsetX;
		dModifyY += dManualOffsetY;
		dModifyT += dManualOffsetT;

		/*double dPostX;
		double dPostY;
		double dPostT;*/

		dlgVisionSetting->dlgSettingAlign->m_edit_xoffset.GetWindowTextW(strVal);
		dPostX = (_wtof(strVal) / 1000);

		dlgVisionSetting->dlgSettingAlign->m_edit_yoffset.GetWindowTextW(strVal);
		dPostY = (_wtof(strVal) / 1000);

		dlgVisionSetting->dlgSettingAlign->m_edit_toffset.GetWindowTextW(strVal);
		dPostT = _wtof(strVal);

		strLogData.Format(_T("[Align Vision offset] X축 offset : %.3fmm, Y축 offset : %.3fmm, Theta offset : %.6f˚"), dPostX, dPostY, dPostT);
		csLogData = CStringA(strLogData);
		cFullLog = csLogData;
		cpFullLog = const_cast<char*>(cFullLog);
		LogWrite(ALIGNMENT, cpFullLog);

		dModifyX += dPostX;
		dModifyY += dPostY;
		dModifyT += dPostT;

		strLogData.Format(_T("[Manual Align Total Result] X축 보정 값 : %.3fmm, Y축 보정 값 : %.3fmm, THETA 보정 값 : %.6f˚"), dModifyX, dModifyY, dModifyT);
		csLogData = CStringA(strLogData);
		cFullLog = csLogData;
		cpFullLog = const_cast<char*>(cFullLog);
		LogWrite(ALIGNMENT, cpFullLog);

		LogWrite(ALIGNMENT, "MANUAL ALIGNMENT COMPLETE");
		stSendData.dXModify = dModifyX;
		stSendData.dYModify = dModifyY;
		stSendData.dTModify = dModifyT;
		stSendData.dScaleX = dSizeX;
		stSendData.dScaleY = dSizeY;
		
		stSendData.nResult = 0;

		stSendData.bClientReceive = true;

		stSend.lpData = &stSendData;
		stSend.cbData = sizeof(stSendData);
		stSend.dwData = 4;

		::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);

		dlgVisionAlign->GetDlgItem(IDC_STATIC_TOTALJUDGE)->SetWindowTextW(_T("OK"));
		dlgVisionAlign->bChkJudge = true;
		dlgVisionAlign->GetDlgItem(IDC_STATIC_TOTALJUDGE)->Invalidate(false);

		delete dlgPopupManualAlign;
	}

	else
	{
		//LogWrite(ALIGNMENT, "MANUAL ALIGNMENT X 보정 값 : [0mm]");
		//LogWrite(ALIGNMENT, "MANUAL ALIGNMENT Y 보정 값 : [0mm]");
		//LogWrite(ALIGNMENT, "MANUAL ALIGNMENT T 보정 값 : [0˚]");

		//LogWrite(ALIGNMENT, "MANUAL ALIGNMENT CANCEL");

		//// MANUAL ALIGN CANCEL
		//stSendData.dXModify = 0.0;
		//stSendData.dYModify = 0.0;
		//stSendData.dTModify = 0.0;
		//stSendData.nResult = 0;

		//stSendData.bClientReceive = true;

		//stSend.lpData = &stSendData;
		//stSend.cbData = sizeof(stSendData);
		//stSend.dwData = 4;

		//::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);

		dModifyX = 0;
		dModifyY = 0;
		dModifyT = 0;

		dSizeX = 1.0;
		dSizeY = 1.0;

		dErrorLGentry = dLGentryPos - (dLGentryStdPos - ((dAlignWidth - 167) / 2));
		dErrorRGentry = (dRGentryStdPos - ((dAlignWidth - 167) / 2)) - dRGentryPos;

		dErrorCam1 = (dCam1StdPos - ((dAlignHeight - 167) / 2)) - dCam1Pos;
		dErrorCam2 = (dCam2StdPos + ((dAlignHeight - 167) / 2)) - dCam2Pos;
		dErrorCam3 = (dCam3StdPos - ((dAlignHeight - 167) / 2)) - dCam3Pos;
		dErrorCam4 = dCam4Pos - (dCam4StdPos - ((dAlignHeight - 167) / 2));

		dErrorX = (dErrorLGentry + dErrorRGentry) / 2;

		if (bJigProcess == true)
			dErrorY = ((dErrorCam1 + dErrorCam3) / 2 + dErrorCam2) / 2;

		else if (bJigProcess == false)
			dErrorY = (dErrorCam1 + dErrorCam2 + dErrorCam3 + dErrorCam4) / 4;

		strLogData.Format(_T("[Position 오차] Gentry Shift Value : %.3fmm, Vision Cam Shift Value : %.3fmm"), dErrorX, dErrorY);
		csLogData = CStringA(strLogData);
		cFullLog = csLogData;
		cpFullLog = const_cast<char*>(cFullLog);
		LogWrite(ALIGNMENT, cpFullLog);

		dModifyX += dErrorX;
		dModifyY += dErrorY;

		strLogData.Format(_T("[Laser Calibration offset] X축 offset : %.3fmm Y축 offset : %.3fmm"), dLCOffsetX, dLCOffsetY);
		csLogData = CStringA(strLogData);
		cFullLog = csLogData;
		cpFullLog = const_cast<char*>(cFullLog);
		LogWrite(ALIGNMENT, cpFullLog);

		dModifyX += dLCOffsetX;
		dModifyY -= dLCOffsetY;

		strLogData.Format(_T("[Manual offset] X축 offset : %.3fmm Y축 offset : %.3fmm Theta offset : %.6f˚"), dManualOffsetX, dManualOffsetY, dManualOffsetT);
		csLogData = CStringA(strLogData);
		cFullLog = csLogData;
		cpFullLog = const_cast<char*>(cFullLog);
		LogWrite(ALIGNMENT, cpFullLog);

		dModifyX += dManualOffsetX;
		dModifyY += dManualOffsetY;
		dModifyT += dManualOffsetT;

		CString strVal;
		double dVal;

		dlgVisionSetting->dlgSettingAlign->m_edit_xoffset.GetWindowTextW(strVal);
		dPostX = (_wtof(strVal) / 1000);

		dlgVisionSetting->dlgSettingAlign->m_edit_yoffset.GetWindowTextW(strVal);
		dPostY = (_wtof(strVal) / 1000);

		dlgVisionSetting->dlgSettingAlign->m_edit_toffset.GetWindowTextW(strVal);
		dPostT = _wtof(strVal);

		strLogData.Format(_T("[Align Vision offset] X축 offset : %.3fmm, Y축 offset : %.3fmm, Theta offset : %.6f˚"), dPostX, dPostY, dPostT);
		csLogData = CStringA(strLogData);
		cFullLog = csLogData;
		cpFullLog = const_cast<char*>(cFullLog);
		LogWrite(ALIGNMENT, cpFullLog);

		dModifyX += dPostX;
		dModifyY += dPostY;
		dModifyT += dPostT;

		strLogData.Format(_T("[Align Total Result] X축 보정 값 : %.3fmm, Y축 보정 값 : %.3fmm, THETA 보정 값 : %.6f˚"), dModifyX, dModifyY, dModifyT);
		csLogData = CStringA(strLogData);
		cFullLog = csLogData;
		cpFullLog = const_cast<char*>(cFullLog);
		LogWrite(ALIGNMENT, cpFullLog);

		// 데이터 전송
		//stSendData.nResult = 1;

		stSendData.dXModify = dModifyX;
		stSendData.dYModify = dModifyY;
		stSendData.dTModify = dModifyT;
		stSendData.dScaleX = dSizeX;
		stSendData.dScaleY = dSizeY;

		stSendData.bClientReceive = false;
		stSendData.bServerReceive = true;

		stSend.lpData = &stSendData;
		stSend.cbData = sizeof(stSendData);
		stSend.dwData = 4;

		::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);

		delete dlgPopupManualAlign;
	}
}


void CRVisionDlg::ExcutionFC(int nCase)
{
	CWnd* pWnd = AfxGetMainWnd();

	double maxVAL;

	if (nCase == 0)
	{
		if (nCountFC < (nPatternPoint * nPatternPoint))
		{
			ImageSave(4, false);

			CString ImageName;;
			ImageName = strExeFilePath + _T("Data\\_OriginImage_5.bmp");
			CT2CA ConvertString(ImageName);
			std::string	Image_path(ConvertString);

			FCImage = imread(Image_path);

			// fc image 전처리
			Mat ImageClone;	// 이미지 복사본
			Mat ImageGray;	// GRAY 이미지 
			Mat ImageOpen;	// MORPHOLOGY OPEN
			Mat ImageClose;	// MORPHOLOGY CLOSE
			Mat ElementOpen(nOpen_FC, nOpen_FC, CV_8U, cv::Scalar(1));	// OPEN 파라미터
			Mat ElementClose(nClose_FC, nClose_FC, CV_8U, cv::Scalar(1));	// CLOSE 파라미터
			Mat ImageBinary;	// 이미지 이진화

			// clone 복사
			ImageClone = FCImage.clone();

			// rgb2gray
			cvtColor(ImageClone, ImageGray, COLOR_BGR2GRAY);

			// open, close morphology
			morphologyEx(ImageClone, ImageOpen, cv::MORPH_OPEN, ElementOpen);
			morphologyEx(ImageOpen, ImageClose, cv::MORPH_CLOSE, ElementClose);

			// binary
			threshold(ImageClose, ImageBinary, nBinaryLow_FC, 255/*고정 값*/, THRESH_BINARY);
			//

		//	resize(FCImage, FCImage_resize, Size(FCImage.cols / resizeMagni, FCImage.rows / resizeMagni));
			resize(ImageBinary, FCImage_resize, Size(ImageBinary.cols / resizeMagni, ImageBinary.rows / resizeMagni));
			resize(MarkImageFC, MarkImageFC_resize, Size(MarkImageFC.cols / resizeMagni, MarkImageFC.rows / resizeMagni));

			matchTemplate(FCImage_resize, MarkImageFC_resize, DetectResult, TM_CCOEFF_NORMED);

			minMaxLoc(DetectResult, NULL, &maxVAL, NULL, &findPoint);

			findPoint *= resizeMagni;

			CString strValue;
			strValue.Format(_T("%.3f %%"), maxVAL * 100);
			dlgVisionFC->GetDlgItem(IDC_STATIC_MATCHRATE_VALUE)->SetWindowTextW(strValue);

			// OK
			if ((maxVAL * 100) > dMatchRate_FC)
			{
				dErrorX_FC = ((CamWidth / 2) - (findPoint.x + (MarkImageFC.cols) / 2)) * FCResolution / 1000;
				dErrorY_FC = ((CamHeight / 2) - (findPoint.y + (MarkImageFC.rows) / 2)) * FCResolution / 1000;

				pFCResult[nCountFC].dXError = dErrorX_FC;
				pFCResult[nCountFC].dYError = dErrorY_FC;

				stSendData.nFCShot = 0;
				stSendData.bClientReceive = true;

				stSend.lpData = &stSendData;
				stSend.cbData = sizeof(stSendData);
				stSend.dwData = 7;

				::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);

				ChkFindFC = true;

				if (nCountFC == (nPatternPoint * nPatternPoint) - 1)
				{
					Sleep(5000);
					FCFileSave();
					CHK_FC = false;

					WinExec("D:\\Field Correction File\\correXionPro\\correXionPro.exe", SW_SHOW);
					dlgVisionFC->m_list_fc.DeleteAllItems();
					dlgVisionFC->nFCLogCount = 0;

				}
				nCountFC++;
			}

			// NG
			else
			{
				strLogData.Format(_T("FIELD CORRECTION [n : %d] MEASUREMENT FAIL"), nCountFC);
				csLogData = CStringA(strLogData);
				cFullLog = csLogData;
				cpFullLog = const_cast<char*>(cFullLog);
				LogWrite(FIELDCORRECTION, cpFullLog);

				ChkFindFC = true;

				stSendData.nFCShot = 2;
				stSendData.bClientReceive = true;

				stSend.lpData = &stSendData;
				stSend.cbData = sizeof(stSendData);
				stSend.dwData = 7;

				::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);

				delete pFCResult;
			}
		}
	}

	else if (nCase == 1)
	{
		ImageSave(4, false);

		CString FileName;
		FileName = strExeFilePath + _T("Data\\_OriginImage_5.bmp");
		CT2CA ConvertString(FileName);
		std::string	Image_path(ConvertString);

		// 원본 이미지 로딩
		FCImage = imread(Image_path);

		// fc image 전처리
		Mat ImageClone;	// 이미지 복사본
		Mat ImageGray;	// GRAY 이미지 
		Mat ImageOpen;	// MORPHOLOGY OPEN
		Mat ImageClose;	// MORPHOLOGY CLOSE
		Mat ElementOpen(nOpen_FC, nOpen_FC, CV_8U, cv::Scalar(1));	// OPEN 파라미터
		Mat ElementClose(nClose_FC, nClose_FC, CV_8U, cv::Scalar(1));	// CLOSE 파라미터
		Mat ImageBinary;	// 이미지 이진화

		// clone 복사
		ImageClone = FCImage.clone();

		// rgb2gray
		//cvtColor(ImageClone, ImageGray, COLOR_BGR2GRAY);

		// open, close morphology
		morphologyEx(ImageClone, ImageOpen, cv::MORPH_OPEN, ElementOpen);
		morphologyEx(ImageOpen, ImageClose, cv::MORPH_CLOSE, ElementClose);

		// binary
		threshold(ImageClose, ImageBinary, nBinaryLow_FC, 255/*고정 값*/, THRESH_BINARY);

		//	resize(FCImage, FCImage_resize, Size(FCImage.cols / resizeMagni, FCImage.rows / resizeMagni));
		resize(ImageBinary, FCImage_resize, Size(ImageBinary.cols / resizeMagni, ImageBinary.rows / resizeMagni));
		resize(MarkImageFC, MarkImageFC_resize, Size(MarkImageFC.cols / resizeMagni, MarkImageFC.rows / resizeMagni));

		matchTemplate(FCImage_resize, MarkImageFC_resize, DetectResult, TM_CCOEFF_NORMED);

		minMaxLoc(DetectResult, NULL, &maxVAL, NULL, &findPoint);

		findPoint *= resizeMagni;

		CString strValue;
		strValue.Format(_T("%.3f%%"), maxVAL * 100);
		dlgVisionFC->GetDlgItem(IDC_STATIC_MATCHRATE_VALUE)->SetWindowTextW(strValue);

		strValue.Format(_T("%.3fmm"), (((findPoint.x) + (MarkImageFC.cols / 2)) - CamWidth / 2) * FCResolution / 1000);
		dlgVisionFC->GetDlgItem(IDC_STATIC_ERROR_X_VALUE)->SetWindowTextW(strValue);

		strValue.Format(_T("%.3fmm"), (CamHeight / 2 - ((findPoint.y) + (MarkImageFC.rows) / 2)) * FCResolution / 1000);
		dlgVisionFC->GetDlgItem(IDC_STATIC_ERROR_Y_VALUE)->SetWindowTextW(strValue);

		ChkFindFC = true;
	}
}


void CRVisionDlg::ExcutionLaserCalibration()
{
	CWnd* pWnd = AfxGetMainWnd();

	ImageSave(4, false);

	CString FileName;
	FileName = strExeFilePath + _T("Data\\_OriginImage_5.bmp");
	CT2CA ConvertString(FileName);
	std::string	Image_path(ConvertString);

	// 원본 이미지 로딩
	FCImage = imread(Image_path);

	// fc image 전처리
	Mat ImageClone;	// 이미지 복사본
	Mat ImageGray;	// GRAY 이미지 
	Mat ImageOpen;	// MORPHOLOGY OPEN
	Mat ImageClose;	// MORPHOLOGY CLOSE
	Mat ElementOpen(nOpen_FC, nOpen_FC, CV_8U, cv::Scalar(1));	// OPEN 파라미터
	Mat ElementClose(nClose_FC, nClose_FC, CV_8U, cv::Scalar(1));	// CLOSE 파라미터
	Mat ImageBinary;	// 이미지 이진화

	// clone 복사
	ImageClone = FCImage.clone();

	resize(ImageClone, LaserImage_resize, Size(ImageClone.cols / resizeMagni, ImageClone.rows / resizeMagni));
	resize(MarkImageLaser, MarkImageLaser_resize, Size(MarkImageLaser.cols / resizeMagni, MarkImageLaser.rows / resizeMagni));

	matchTemplate(LaserImage_resize, MarkImageLaser_resize, DetectResult, TM_CCOEFF_NORMED);

	double maxVAL;

	minMaxLoc(DetectResult, NULL, &maxVAL, NULL, &findLaserPoint);

	findLaserPoint *= resizeMagni;

	CString strValue;
	strValue.Format(_T("%.3f%%"), maxVAL * 100);
	dlgVisionSetting->dlgSettingLaser->GetDlgItem(IDC_STATIC_LASERMARK_MEASURE_VALUE_1)->SetWindowTextW(strValue);

	strValue.Format(_T("%.3fmm"), (((findLaserPoint.x) + (MarkImageLaser.cols / 2)) - CamWidth / 2) * FCResolution / 1000);
	dlgVisionSetting->dlgSettingLaser->GetDlgItem(IDC_STATIC_LASERMARK_MEASURE_VALUE_2)->SetWindowTextW(strValue);
	dLCOffsetX = _wtof(strValue);

	strValue.Format(_T("%.3fmm"), (CamHeight / 2 - ((findLaserPoint.y) + (MarkImageLaser.rows) / 2)) * FCResolution / 1000);
	dlgVisionSetting->dlgSettingLaser->GetDlgItem(IDC_STATIC_LASERMARK_MEASURE_VALUE_3)->SetWindowTextW(strValue);
	dLCOffsetY = _wtof(strValue);

	ChkFindLaser = true;

	stSendData.nLCRun = 0;
	stSendData.bClientReceive = true;

	stSend.lpData = &stSendData;
	stSend.cbData = sizeof(stSendData);
	stSend.dwData = 9;

	::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);
}


void CRVisionDlg::AlignResultFile()
{
	CString buf;
	CFile	file;
	CString strText;
	CString FileName;

	int nBit;

	FileName = strAlignmentPath + _T("\\Result.txt");
	file.Open(FileName, CFile::modeCreate | CFile::modeWrite);

	buf = _T("[Vision Alignment Result]");
	file.Write(buf, buf.GetLength() * sizeof(TCHAR));

	CString strMethod;
	if (bChkMark == 1)
		strMethod = _T("MARK");

	else if (bChkEdge == 1)
		strMethod = _T("EDGE");

	buf.Format(_T("\nAlign Method : %s"), strMethod);
	file.Write(buf, buf.GetLength() * sizeof(TCHAR));

	buf.Format(_T("\n\nModify X : %.3f"), dModifyX);
	file.Write(buf, buf.GetLength() * sizeof(TCHAR));

	buf.Format(_T("\n\nModify Y : %.3f"), dModifyY);
	file.Write(buf, buf.GetLength() * sizeof(TCHAR));

	buf.Format(_T("\n\nModify Theta : %.8f"), dModifyT);
	file.Write(buf, buf.GetLength() * sizeof(TCHAR));

	file.Close();
}

void CRVisionDlg::FCFileSave()
{
	CWnd* pWnd = AfxGetMainWnd();

	char* buf;
	char* buf_add;
	CString buf_val;

	CFile	file;
	CString strText;
	CString FileName;

	CStringA csAFullAddr;
	const char* cFullAddr;

	static _TCHAR szLog[5096];

	int nBit;

	CTime strFCTime = CTime::GetCurrentTime();

	FileName.Format(_T("D:\\Field Correction File\\correXionPro\\_%04d%02d%02d_%02d%02d%02d.DAT"),
		strFCTime.GetYear(), strFCTime.GetMonth(), strFCTime.GetDay(), strFCTime.GetHour(), strFCTime.GetMinute(), strFCTime.GetSecond());
	//	strDayPath.Format(_T("D:\\VisionData\\_%04d_%02d%02d"), strCreateTime.GetYear(), strCreateTime.GetMonth(), strCreateTime.GetDay());
		//FileName = strExeFilePath + _T("Data\\File.DAT");

	file.Open(FileName, CFile::modeCreate | CFile::modeWrite);

	strText = ("OLDCTFILE = ");
	strText = strText + strOldctFile;
	csAFullAddr = CStringA(strText);
	cFullAddr = csAFullAddr;
	file.Write(cFullAddr, strlen(cFullAddr));

	strText = ("\nNEWCTFILE = ");
	strText = strText + strNewctFile;
	csAFullAddr = CStringA(strText);
	cFullAddr = csAFullAddr;
	file.Write(cFullAddr, strlen(cFullAddr));

	strText.Format(_T("\n\nTOLERANCE = %.3f"), dGain);
	csAFullAddr = CStringA(strText);
	cFullAddr = csAFullAddr;
	file.Write(cFullAddr, strlen(cFullAddr));

	strText.Format(_T("\n\nNEWCAL = %.3f"), dNewcal);
	csAFullAddr = CStringA(strText);
	cFullAddr = csAFullAddr;
	file.Write(cFullAddr, strlen(cFullAddr));

	buf = ("\n\n// RTC-X [Bit] RTC-Y[Bit] REAL-X[mm] REAL-Y[mm]\n");
	file.Write(buf, strlen(buf));

	int count = 0;

	double offsetfc_x;
	double offsetfc_y;

	offsetfc_x = pFCResult[((nPatternPoint * nPatternPoint) - 1) / 2].dXError;
	offsetfc_y = pFCResult[((nPatternPoint * nPatternPoint) - 1) / 2].dYError;

	// i == y
	for (int i = -((nPatternPoint - 1) / 2); i < (nPatternPoint - 1) / 2 + 1; i++)
	{
		// j == x
		for (int j = -((nPatternPoint - 1) / 2); j < (nPatternPoint - 1) / 2 + 1; j++)
		{
			strText.Format(_T("\n\t%d"), (int)(j * dPatternLength * dNewcal));

			csAFullAddr = CStringA(strText);
			cFullAddr = csAFullAddr;
			file.Write(cFullAddr, strlen(cFullAddr));

			strText.Format(_T(" %d"), (int)(i * dPatternLength * dNewcal));

			csAFullAddr = CStringA(strText);
			cFullAddr = csAFullAddr;
			file.Write(cFullAddr, strlen(cFullAddr));

			strText.Format(_T(" \t%.3f"), (j * dPatternLength) + pFCResult[count].dYError - offsetfc_y);

			csAFullAddr = CStringA(strText);
			cFullAddr = csAFullAddr;
			file.Write(cFullAddr, strlen(cFullAddr));

			strText.Format(_T(" %.3f"), (i * dPatternLength) + pFCResult[count].dXError - offsetfc_x);

			csAFullAddr = CStringA(strText);
			cFullAddr = csAFullAddr;
			file.Write(cFullAddr, strlen(cFullAddr));

			count++;
		}
		buf = "\n";
		file.Write(buf, strlen(buf));
	}

	file.Close();
	delete pFCResult;

	LogWrite(NORMAL, "Field Correction Dat 파일 생성 완료");

	LogWrite(NORMAL, "Field Correction 측정 완료");

	nCountFC++;

	stSendData.nFCRun = 0;
	stSendData.bClientReceive = true;

	stSend.lpData = &stSendData;
	stSend.cbData = sizeof(stSendData);
	stSend.dwData = 6;

	::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);

	nRun_FC = 1;
}


void CRVisionDlg::ServerReturn(int nCase)
{
	CWnd* pWnd = AfxGetMainWnd();

	stSendData.bServerReceive = false;
	stSendData.bClientReceive = true;

	if (nCase == 6)
		stSendData.nFCRun = 1;

	stSend.lpData = &stSendData;
	stSend.cbData = sizeof(stSendData);
	stSend.dwData = nCase;

	::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);
}


void CRVisionDlg::ImageSave(int camNum, bool nCase)
{
	BYTE* Img;

	Img = reinterpret_cast<BYTE*>(cBaumer->m_camera_set[camNum].m_buf);

	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;
	RGBQUAD rgb[256];

	memset(&fh, 0, sizeof(BITMAPFILEHEADER));
	memset(&ih, 0, sizeof(BITMAPINFOHEADER));
	memset(&rgb, 0, sizeof(RGBQUAD) * 256);
	fh.bfOffBits = 1078; // RGBQUAD + InfoHeader + FileHeader only 8bit mode if 24bit == 54; 40+ 14; 

	fh.bfSize = CamWidth * CamHeight + sizeof(RGBQUAD) * 256 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	fh.bfType = 19778;

	ih.biBitCount = 8;
	ih.biHeight = CamHeight;
	ih.biPlanes = 1;
	ih.biSize = 40;
	ih.biSizeImage = CamWidth * CamHeight;
	ih.biWidth = CamWidth;
	ih.biXPelsPerMeter = 0;
	ih.biYPelsPerMeter = 0;

	for (int i = 0; i < 256; i++)
	{
		rgb[i].rgbBlue = i;
		rgb[i].rgbGreen = i;
		rgb[i].rgbRed = i;
		rgb[i].rgbReserved = 0;
	}

	int rwsize = WIDTHBYTES(ih.biBitCount * ih.biWidth);

	BYTE* pData = new BYTE[CamWidth * CamHeight];
	memset(pData, 0, sizeof(CamWidth * CamHeight));

	for (int i = 0; i < ih.biHeight; i++)
	{
		for (int j = 0; j < rwsize; j++)
		{
			pData[i * rwsize + j] = Img[(ih.biHeight - i - 1) * rwsize + j];
		}
	}


	FILE* fp;

	CString strImageName;
	strImageName.Format(_T("Data\\_OriginImage_%d.bmp"), camNum + 1);

	CString strFileName;
	strFileName = strExeFilePath + strImageName;

	_bstr_t gg(strFileName);

	fopen_s(&fp, gg, "wb");
	fwrite(&fh, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&ih, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(rgb, sizeof(RGBQUAD), 256, fp);
	fwrite(pData, 1, CamWidth * CamHeight, fp);
	fclose(fp);

	if (nCase == true)
	{
		FILE* fp_alignment;

		strImageName.Format(_T("\\_Alignment_%d.bmp"), camNum + 1);
		strFileName = strAlignmentPath + strImageName;

		_bstr_t gg(strFileName);

		fopen_s(&fp_alignment, gg, "wb");
		fwrite(&fh, sizeof(BITMAPFILEHEADER), 1, fp_alignment);
		fwrite(&ih, sizeof(BITMAPINFOHEADER), 1, fp_alignment);
		fwrite(rgb, sizeof(RGBQUAD), 256, fp);
		fwrite(pData, 1, CamWidth * CamHeight, fp_alignment);
		fclose(fp_alignment);

	}

	delete[] pData;
	pData = NULL;
}


void CRVisionDlg::MarkExtraction(int camNum)
{
	Mat MarkImg;
	Mat LoadImg;;

	BITMAPINFO* m_pBitmapInfo;

	CString FileName;

	if (camNum == 0)
		FileName = strExeFilePath + _T("Data\\_OriginImage_1.bmp");

	else if (camNum == 1)
		FileName = strExeFilePath + _T("Data\\_OriginImage_2.bmp");

	else if (camNum == 2)
		FileName = strExeFilePath + _T("Data\\_OriginImage_3.bmp");

	else if (camNum == 3)
		FileName = strExeFilePath + _T("Data\\_OriginImage_4.bmp");

	else if (camNum == 4 || camNum == 5)
		FileName = strExeFilePath + _T("Data\\_OriginImage_5.bmp");

	CT2CA ConvertString(FileName);
	std::string	Image_path(ConvertString);

	LoadImg = imread(Image_path);


	if (camNum == 0 || camNum == 1 || camNum == 2 || camNum == 3)
	{
		dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect;
		MarkImg = LoadImg(Range(dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.top * 4, dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.bottom * 4),
			Range(dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.left * 4, dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.right * 4));

		CString SaveMark;
		SaveMark = strRecipeFilePath + _T("AlignMark.bmp");

		CT2CA ConvertStringMark(SaveMark);
		std::string	save_mark_path(ConvertStringMark);

		imwrite(save_mark_path, MarkImg);

		SaveMark = strRecipeFilePath + _T("AlignMarkOrigin.bmp");

		CT2CA ConvertStringMarkOrigin(SaveMark);
		std::string	save_mark_pathOrigin(ConvertStringMarkOrigin);

		imwrite(save_mark_pathOrigin, MarkImg);
	}

	else if (camNum == 4)
	{
		dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect;
		MarkImg = LoadImg(Range(dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.top * 4, dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.bottom * 4),
			Range(dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.left * 4, dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.right * 4));

		CString SaveMark;
		SaveMark = strRecipeFilePath + _T("FieldCorrectionMark.bmp");

		CT2CA ConvertStringMark(SaveMark);
		std::string	save_mark_path(ConvertStringMark);

		imwrite(save_mark_path, MarkImg);

		SaveMark = strRecipeFilePath + _T("FieldCorrectionMarkOrigin.bmp");

		CT2CA ConvertStringMarkOrigin(SaveMark);
		std::string	save_mark_pathOrigin(ConvertStringMarkOrigin);

		imwrite(save_mark_pathOrigin, MarkImg);
	}

	else if (camNum == 5)
	{
		dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect;
		MarkImg = LoadImg(Range(dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.top * 4, dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.bottom * 4),
			Range(dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.left * 4, dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.right * 4));

		CString SaveMark;
		SaveMark = strExeFilePath + _T("Data\\LaserMark.bmp");

		CT2CA ConvertStringMark(SaveMark);
		std::string	save_mark_path(ConvertStringMark);

		imwrite(save_mark_path, MarkImg);
	}
}

BOOL CRVisionDlg::EdgeFind(int camNum)
{
	BOOL bRet;
	bRet = true;
	CString FileName;

	ImageSave(camNum, true);

	// 이미지 LOAD
	if (camNum == 0)
		FileName = strExeFilePath + _T("Data\\_OriginImage_1.bmp");

	else if (camNum == 1)
		FileName = strExeFilePath + _T("Data\\_OriginImage_2.bmp");

	else if (camNum == 2)
		FileName = strExeFilePath + _T("Data\\_OriginImage_3.bmp");

	else if (camNum == 3)
		FileName = strExeFilePath + _T("Data\\_OriginImage_4.bmp");

	CT2CA ConvertString(FileName);
	std::string	Image_path(ConvertString);

	// 원본 이미지 로딩
	loadImage = imread(Image_path);

	Mat ImageClone;	// 이미지 복사본
	Mat ImageGray;	// GRAY 이미지 
	Mat ImageOpen;	// MORPHOLOGY OPEN
	Mat ImageClose;	// MORPHOLOGY CLOSE
	Mat ElementOpen(stAlign.nOpen[camNum], stAlign.nOpen[camNum], CV_8U, cv::Scalar(1));	// OPEN 파라미터
	Mat ElementClose(stAlign.nClose[camNum], stAlign.nClose[camNum], CV_8U, cv::Scalar(1));	// CLOSE 파라미터
	Mat ImageBinary;	// 이미지 이진화
	Mat ImageCanny;	// 이미지 CANNY
	Mat ImageResize;

	// clone 복사
	ImageClone = loadImage.clone();
	resize(ImageClone, ImageResize, Size(ImageClone.cols / resizeMagni, ImageClone.rows / resizeMagni));

	// rgb2gray
	cvtColor(ImageResize, ImageGray, COLOR_BGR2GRAY);

	// open, close morphology
	morphologyEx(ImageGray, ImageOpen, cv::MORPH_OPEN, ElementOpen);
	morphologyEx(ImageOpen, ImageClose, cv::MORPH_CLOSE, ElementClose);

	// binary
	threshold(ImageClose, ImageBinary, stAlign.nBinaryLow[camNum], 255/*고정 값*/, THRESH_BINARY);

	// Edge 검출 벡터
	std::vector<cv::Point> pointLine;
	Vec4f EdgeLine;

	int FindEdge[CamWidth] = { 0 };
	int count = 0;

	// 위에서 아래로
	if (camNum == 0 || camNum == 2)
	{
		for (int i = stAlign.ROIStart[camNum].x / resizeMagni; i < stAlign.ROIEnd[camNum].x / resizeMagni; i++)
		{
			for (int j = stAlign.ROIStart[camNum].y / resizeMagni; j < stAlign.ROIEnd[camNum].y / resizeMagni; j++)
			{
				if (ImageBinary.at<uchar>(j, i) != 0)
				{
					FindEdge[i] = j;
					pointLine.push_back(cv::Point(i * resizeMagni, j * resizeMagni));
					count++;
					break;
				}
			}
		}
	}

	// 아래에서 위로
	else if (camNum == 1 || camNum == 3)
	{
		for (int i = stAlign.ROIStart[camNum].x / resizeMagni; i < stAlign.ROIEnd[camNum].x / resizeMagni; i++)
		{
			for (int j = stAlign.ROIEnd[camNum].y / resizeMagni - 1; j >= stAlign.ROIStart[camNum].y / resizeMagni; j--)
			{
				if (ImageBinary.at<uchar>(j, i) != 0)
				{
					FindEdge[i] = j;
					pointLine.push_back(cv::Point(i * resizeMagni, j * resizeMagni));
					count++;
					break;
				}
			}
		}
	}

	CString strResult;

	if (count != 0)
	{
		fitLine(cv::Mat(pointLine), EdgeLine,
			DIST_L2,// 거리 유형
			0,   // L2 거리를 사용하지 않음
			0.01, 0.01); // 정확도

		double fSlope_vertical = EdgeLine.val[1] / EdgeLine.val[0];
		double fIntercept_vertical = EdgeLine.val[3] - fSlope_vertical * EdgeLine.val[2];

		stEdgeAlign.Slope[camNum] = fSlope_vertical;
		stEdgeAlign.EdgeStart[camNum].x = stAlign.ROIStart[camNum].x;
		stEdgeAlign.EdgeStart[camNum].y = stAlign.ROIStart[camNum].x * fSlope_vertical + fIntercept_vertical;

		stEdgeAlign.EdgeEnd[camNum].x = stAlign.ROIEnd[camNum].x;
		stEdgeAlign.EdgeEnd[camNum].y = stAlign.ROIEnd[camNum].x * fSlope_vertical + fIntercept_vertical;

		stAlign.AlignPoint[camNum].x = CamWidth / 2;
		stAlign.AlignPoint[camNum].y = (CamWidth / 2 * fSlope_vertical + fIntercept_vertical);// *2;

		stEdgeAlign.ChkFind[camNum] = true;

		if (camNum == 0)
			dlgVisionAlign->GetDlgItem(IDC_STATIC_ALIGN_1_DETECT)->SetWindowTextW(_T("OK"));

		else if (camNum == 1)
			dlgVisionAlign->GetDlgItem(IDC_STATIC_ALIGN_2_DETECT)->SetWindowTextW(_T("OK"));

		else if (camNum == 2)
			dlgVisionAlign->GetDlgItem(IDC_STATIC_ALIGN_3_DETECT)->SetWindowTextW(_T("OK"));

		else if (camNum == 3)
			dlgVisionAlign->GetDlgItem(IDC_STATIC_ALIGN_4_DETECT)->SetWindowTextW(_T("OK"));

		bRet = true;
		strResult = _T("Align Edge 검출 성공");

		strLogData.Format(_T("CAM[%d] EDGE DETECT SUCCES"), camNum + 1);
		csLogData = CStringA(strLogData);
		cFullLog = csLogData;
		cpFullLog = const_cast<char*>(cFullLog);
		LogWrite(ALIGNMENT, cpFullLog);
	}

	else
	{
		stEdgeAlign.EdgeStart[camNum].x = 0;
		stEdgeAlign.EdgeStart[camNum].y = 0;

		stEdgeAlign.EdgeEnd[camNum].x = 0;
		stEdgeAlign.EdgeEnd[camNum].y = 0;

		stEdgeAlign.ChkFind[camNum] = false;

		if (camNum == 0)
			dlgVisionAlign->GetDlgItem(IDC_STATIC_ALIGN_1_DETECT)->SetWindowTextW(_T("NG"));

		else if (camNum == 1)
			dlgVisionAlign->GetDlgItem(IDC_STATIC_ALIGN_2_DETECT)->SetWindowTextW(_T("NG"));

		else if (camNum == 2)
			dlgVisionAlign->GetDlgItem(IDC_STATIC_ALIGN_3_DETECT)->SetWindowTextW(_T("NG"));

		else if (camNum == 3)
			dlgVisionAlign->GetDlgItem(IDC_STATIC_ALIGN_4_DETECT)->SetWindowTextW(_T("NG"));

		bRet = false;
		strResult = _T("Align Edge 검출 실패");

		strLogData.Format(_T("CAM[%d] EDGE DETECT FAIL"), camNum + 1);
		csLogData = CStringA(strLogData);
		cFullLog = csLogData;
		cpFullLog = const_cast<char*>(cFullLog);
		LogWrite(ALIGNMENT, cpFullLog);
	}

	stMarkAlign.nChkFindMark[camNum] = 0;

	return bRet;
}


BOOL CRVisionDlg::MarkFind(int camNum, int nCase)
{
	bool bRet;
	bRet = true;

	CString FileName;
	CString MarkName;

	ImageSave(camNum, true);

		// 이미지 LOAD
	if (camNum == 0)
		FileName = strExeFilePath + _T("Data\\_OriginImage_1.bmp");

	else if (camNum == 1)
		FileName = strExeFilePath + _T("Data\\_OriginImage_2.bmp");

	else if (camNum == 2)
		FileName = strExeFilePath + _T("Data\\_OriginImage_3.bmp");

	else if (camNum == 3)
		FileName = strExeFilePath + _T("Data\\_OriginImage_4.bmp");

	CT2CA ConvertString(FileName);
	std::string	Image_path(ConvertString);

	if (bJigProcess == true)
	{
		if (camNum == 0)
			MarkName = strExeFilePath + _T("Data\\JigMark_1.bmp");

		else if (camNum == 1)
			MarkName = strExeFilePath + _T("Data\\JigMark_2.bmp");

		else if (camNum == 2)
			MarkName = strExeFilePath + _T("Data\\JigMark_3.bmp");
	}

	else if (bJigProcess == false)
	{
		MarkName = strRecipeFilePath + _T("AlignMark.bmp");
	}

	CT2CA ConvertStringMark(MarkName);
	std::string	Mark_path(ConvertStringMark);

	// 원본 이미지 로딩
	loadImage = imread(Image_path);
	MarkImageAlign = imread(Mark_path);

	Mat ImageOpen;	// MORPHOLOGY OPEN
	Mat ImageClose;	// MORPHOLOGY CLOSE
	Mat ElementOpen(stAlign.nOpen[camNum], stAlign.nOpen[camNum], CV_8U, cv::Scalar(1));	// OPEN 파라미터
	Mat ElementClose(stAlign.nClose[camNum], stAlign.nClose[camNum], CV_8U, cv::Scalar(1));	// CLOSE 파라미터
	Mat ImageBinary;	// 이미지 이진화
	Mat DetectResult;
	Mat ImageGray;

	Mat ImageResize;
	Mat MarkImageAlignResize;

	Mat ImageResizeBinary;
	Mat MarkImageAlignResizeBinary;

	resize(loadImage, ImageResize, Size(loadImage.cols / resizeMagni, loadImage.rows / resizeMagni));

	for (int i = 0; i < ImageResize.cols; i++)
	{
		for (int j = 0; j < ImageResize.rows; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				ImageResize.at<Vec3b>(j, i)[k] = saturate_cast<uchar>(2 * ImageResize.at<Vec3b>(j, i)[k] - 100);
			}
		}
	}

	// open, close morphology
	morphologyEx(ImageResize, ImageOpen, cv::MORPH_OPEN, ElementOpen);
	morphologyEx(ImageOpen, ImageClose, cv::MORPH_CLOSE, ElementClose);

	threshold(ImageClose, ImageResizeBinary, stAlign.nBinaryLow[camNum], 255/*고정 값*/, THRESH_BINARY);

	resize(MarkImageAlign, MarkImageAlignResize, Size(MarkImageAlign.cols / resizeMagni, MarkImageAlign.rows / resizeMagni));
	matchTemplate(ImageResizeBinary, MarkImageAlignResize, DetectResult, TM_CCOEFF_NORMED);

	imwrite("markmark.bmp", MarkImageAlignResize);
	double maxVAL;
	Point findMarkPoint;

	minMaxLoc(DetectResult, NULL, &maxVAL, NULL, &findMarkPoint);

	findMarkPoint *= resizeMagni;

	if (nCase == 0)
	{
		CString strVal;
		strVal.Format(_T("%.3f%%"), maxVAL * 100);

		if (camNum == 0)
			dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_1)->SetWindowTextW(strVal);

		else if (camNum == 1)
			dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_2)->SetWindowTextW(strVal);

		else if (camNum == 2)
			dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_3)->SetWindowTextW(strVal);

		else if (camNum == 3)
			dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_4)->SetWindowTextW(strVal);

		CString strResult;

		// align mark 검출율이 조건보다 큰 경우 (OK)
		if (maxVAL >= dAlignMatchrate / 100)
		{
			if (bJigProcess == true)
			{
				if (camNum == 0)
				{
					stAlign.AlignPoint[camNum].x = findMarkPoint.x;
					stAlign.AlignPoint[camNum].y = findMarkPoint.y;

					stMarkAlign.MarkStart[camNum].x = findMarkPoint.x;
					stMarkAlign.MarkStart[camNum].y = findMarkPoint.y;
				}

				else if (camNum == 1)
				{
					stAlign.AlignPoint[camNum].x = findMarkPoint.x;
					stAlign.AlignPoint[camNum].y = findMarkPoint.y + MarkImageAlign.rows;

					stMarkAlign.MarkStart[camNum].x = findMarkPoint.x;
					stMarkAlign.MarkStart[camNum].y = findMarkPoint.y + MarkImageAlign.rows;
				}

				else if (camNum == 2)
				{
					stAlign.AlignPoint[camNum].x = findMarkPoint.x + MarkImageAlign.cols;
					stAlign.AlignPoint[camNum].y = findMarkPoint.y;

					stMarkAlign.MarkStart[camNum].x = findMarkPoint.x + MarkImageAlign.cols;
					stMarkAlign.MarkStart[camNum].y = findMarkPoint.y;
				}
			}

			else if (bJigProcess == false)
			{
				stAlign.AlignPoint[camNum].x = findMarkPoint.x + (MarkImageAlign.cols / 2);
				stAlign.AlignPoint[camNum].y = findMarkPoint.y + (MarkImageAlign.rows / 2);

				stMarkAlign.MarkStart[camNum].x = findMarkPoint.x;
				stMarkAlign.MarkStart[camNum].y = findMarkPoint.y;
				stMarkAlign.MarkEnd[camNum].x = findMarkPoint.x + MarkImageAlign.cols;
				stMarkAlign.MarkEnd[camNum].y = findMarkPoint.y + MarkImageAlign.rows;
			}

			stMarkAlign.ChkFind[camNum] = true;

			if (camNum == 0)
				dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_1)->SetWindowTextW(_T("OK"));

			else if (camNum == 1)
				dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_2)->SetWindowTextW(_T("OK"));

			else if (camNum == 2)
				dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_3)->SetWindowTextW(_T("OK"));

			else if (camNum == 3)
				dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_4)->SetWindowTextW(_T("OK"));

			stMarkAlign.nChkFindMark[camNum] = 1;	// 1 : ok

			strLogData.Format(_T("CAM[%d] MARK DETECT SUCCES, MATCH RATE : %.3f%%"), camNum + 1, maxVAL * 100);
			csLogData = CStringA(strLogData);
			cFullLog = csLogData;
			cpFullLog = const_cast<char*>(cFullLog);
			LogWrite(ALIGNMENT, cpFullLog);
		}

		// (NG)
		else if (maxVAL < dAlignMatchrate / 100)
		{
			if (bJigProcess == true)
			{
				stAlign.AlignPoint[camNum].x = findMarkPoint.x;
				stAlign.AlignPoint[camNum].y = findMarkPoint.y;
			}

			else if (bJigProcess == false)
			{
				stAlign.AlignPoint[camNum].x = findMarkPoint.x + (MarkImageAlign.cols / 2);
				stAlign.AlignPoint[camNum].y = findMarkPoint.y + (MarkImageAlign.rows / 2);

				stMarkAlign.MarkStart[camNum].x = findMarkPoint.x;
				stMarkAlign.MarkStart[camNum].y = findMarkPoint.y;
				stMarkAlign.MarkEnd[camNum].x = findMarkPoint.x + MarkImageAlign.cols;
				stMarkAlign.MarkEnd[camNum].y = findMarkPoint.y + MarkImageAlign.rows;
			}

			stMarkAlign.ChkFind[camNum] = false;

			if (camNum == 0)
				dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_1)->SetWindowTextW(_T("NG"));

			else if (camNum == 1)
				dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_2)->SetWindowTextW(_T("NG"));

			else if (camNum == 2)
				dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_3)->SetWindowTextW(_T("NG"));

			else if (camNum == 3)
				dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_4)->SetWindowTextW(_T("NG"));

			stMarkAlign.nChkFindMark[camNum] = 2;	// 1 : ng

			strLogData.Format(_T("CAM[%d] MARK DETECT FAIL, MATCH RATE : %.3f%%"), camNum + 1, maxVAL * 100);
			csLogData = CStringA(strLogData);
			cFullLog = csLogData;
			cpFullLog = const_cast<char*>(cFullLog);
			LogWrite(ALIGNMENT, cpFullLog);
		}

		stEdgeAlign.ChkFind[camNum] = false;

		/*dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_1)->Invalidate(false);
		dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_2)->Invalidate(false);
		dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_3)->Invalidate(false);
		dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_4)->Invalidate(false);*/
	}

	else if (nCase == 1)
	{
		CString strVal;
		stAlign.AlignPoint[camNum].x = findMarkPoint.x + (MarkImageAlign.cols / 2);
		stAlign.AlignPoint[camNum].y = findMarkPoint.y + (MarkImageAlign.rows / 2);

		strVal.Format(_T("%.3fmm"), ((CamWidth / 2) - (findMarkPoint.x + (MarkImageAlign.cols / 2))) * AlignResolution / 1000);
		dlgVisionSetting->dlgSettingAlignMark->GetDlgItem(IDC_STATIC_MARK_MEASURE_X_VALUE)->SetWindowTextW(strVal);

		strVal.Format(_T("%.3fmm"), ((CamHeight / 2) - (findMarkPoint.y + (MarkImageAlign.rows / 2))) * AlignResolution / 1000);
		dlgVisionSetting->dlgSettingAlignMark->GetDlgItem(IDC_STATIC_MARK_MEASURE_Y_VALUE)->SetWindowTextW(strVal);

		strVal.Format(_T("%.3f%%"), maxVAL * 100);
		dlgVisionSetting->dlgSettingAlignMark->GetDlgItem(IDC_STATIC_MARK_MEASURE_RATE_VALUE)->SetWindowTextW(strVal);

		stMarkAlign.MarkStart[camNum].x = findMarkPoint.x;
		stMarkAlign.MarkStart[camNum].y = findMarkPoint.y;
		stMarkAlign.MarkEnd[camNum].x = findMarkPoint.x + MarkImageAlign.cols;
		stMarkAlign.MarkEnd[camNum].y = findMarkPoint.y + MarkImageAlign.rows;

		if (maxVAL * 100 > dAlignMatchrate)
			stMarkAlign.nChkManualMark[camNum] = 1;

		else if (maxVAL * 100 < dAlignMatchrate)
			stMarkAlign.nChkManualMark[camNum] = 2;

		stMarkAlign.ChkManualFind[camNum] = true;
	}

	return bRet;
}


void CRVisionDlg::ManualAlignDisplay()
{
}


void CRVisionDlg::AlignCalcuration()
{
	CWnd* pWnd = AfxGetMainWnd();

	CString strValue;
	CString strResult;
	BOOL bRet;
	bRet = true;

	dXPosition_1 = 0;
	dXPosition_2 = 0;
	dXPosition_3 = 0;
	dXPosition_4 = 0;

	dYPosition_1 = 0;
	dYPosition_2 = 0;
	dYPosition_3 = 0;
	dYPosition_4 = 0;

	dModifyX = 0;
	dModifyY = 0;

	dSizeX = 1.0;
	dSizeY = 1.0;

	dT12 = 0;
	dT34 = 0;
	dT13 = 0;
	dT24 = 0;

	dModifyT = 0;

	//edge의 경우 height 값과 width값이 동일
	if (bChkEdge == true)
		dAlignWidth = dAlignHeight;

	dlgVisionAlign->bChkLevel = true;
	dlgVisionAlign->GetDlgItem(IDC_STATIC_LEVEL_H_JUDGE)->SetWindowTextW(_T("OK"));

	dlgVisionAlign->bChkMistake = true;
	dlgVisionAlign->GetDlgItem(IDC_STATIC_MISTAKE_JUDGE)->SetWindowTextW(_T("OK"));

	// edge alignment
	if (bChkEdge == true)
	{
		if (nSelecteAlignMethod == 1)
			strLogData.Format(_T("[EDGE ALIGN] CAM(1) ALIGN POINT [%d, %d] / CAM(2) ALIGN POINT [%d, %d] / CAM(3) ALIGN POINT [%d, %d] / CAM(4) ALIGN POINT [%d, %d]"),
				stAlign.AlignPoint[0].x, stAlign.AlignPoint[0].y, stAlign.AlignPoint[1].x, stAlign.AlignPoint[1].y,
				stAlign.AlignPoint[2].x, stAlign.AlignPoint[2].y, stAlign.AlignPoint[3].x, stAlign.AlignPoint[3].y);

		else if (nSelecteAlignMethod == 2)
			strLogData.Format(_T("[EDGE ALIGN] CAM(1) ALIGN POINT [%d, %d] / CAM(2) ALIGN POINT [%d, %d]"),
				stAlign.AlignPoint[0].x, stAlign.AlignPoint[0].y, stAlign.AlignPoint[1].x, stAlign.AlignPoint[1].y);

		else if (nSelecteAlignMethod == 3)
			strLogData.Format(_T("[EDGE ALIGN] CAM(3) ALIGN POINT [%d, %d] / CAM(4) ALIGN POINT [%d, %d]"),
				stAlign.AlignPoint[2].x, stAlign.AlignPoint[2].y, stAlign.AlignPoint[3].x, stAlign.AlignPoint[3].y);

		else if (nSelecteAlignMethod == 4)
			strLogData.Format(_T("[EDGE ALIGN] CAM(1) ALIGN POINT [%d, %d] / CAM(3) ALIGN POINT [%d, %d]"),
				stAlign.AlignPoint[0].x, stAlign.AlignPoint[0].y, stAlign.AlignPoint[2].x, stAlign.AlignPoint[2].y);

		else if (nSelecteAlignMethod == 5)
			strLogData.Format(_T("[EDGE ALIGN] CAM(2) ALIGN POINT [%d, %d] / CAM(4) ALIGN POINT [%d, %d]"),
				stAlign.AlignPoint[1].x, stAlign.AlignPoint[1].y, stAlign.AlignPoint[3].x, stAlign.AlignPoint[3].y);


		csLogData = CStringA(strLogData);
		cFullLog = csLogData;
		cpFullLog = const_cast<char*>(cFullLog);
		LogWrite(ALIGNMENT, cpFullLog);
	}

	if (bChkMark == true)
	{
		if (bJigProcess == true)
		{
			strLogData.Format(_T("[MARK ALIGN] CAM(1) ALIGN POINT [%d, %d] / CAM(2) ALIGN POINT [%d, %d] / CAM(3) ALIGN POINT [%d, %d]"),
				stAlign.AlignPoint[0].x, stAlign.AlignPoint[0].y, stAlign.AlignPoint[1].x, stAlign.AlignPoint[1].y,
				stAlign.AlignPoint[2].x, stAlign.AlignPoint[2].y);
		}

		else if (bJigProcess == false)
		{
			if (nSelecteAlignMethod == 1)
				strLogData.Format(_T("[MARK ALIGN] CAM(1) ALIGN POINT [%d, %d] / CAM(2) ALIGN POINT [%d, %d] / CAM(3) ALIGN POINT [%d, %d] / CAM(4) ALIGN POINT [%d, %d]"),
					stAlign.AlignPoint[0].x, stAlign.AlignPoint[0].y, stAlign.AlignPoint[1].x, stAlign.AlignPoint[1].y,
					stAlign.AlignPoint[2].x, stAlign.AlignPoint[2].y, stAlign.AlignPoint[3].x, stAlign.AlignPoint[3].y);

			else if (nSelecteAlignMethod == 2)
				strLogData.Format(_T("[MARK ALIGN] CAM(1) ALIGN POINT [%d, %d] / CAM(2) ALIGN POINT [%d, %d]"),
					stAlign.AlignPoint[0].x, stAlign.AlignPoint[0].y, stAlign.AlignPoint[1].x, stAlign.AlignPoint[1].y);

			else if (nSelecteAlignMethod == 3)
				strLogData.Format(_T("[MARK ALIGN] CAM(3) ALIGN POINT [%d, %d] / CAM(4) ALIGN POINT [%d, %d]"),
					stAlign.AlignPoint[2].x, stAlign.AlignPoint[2].y, stAlign.AlignPoint[3].x, stAlign.AlignPoint[3].y);

			else if (nSelecteAlignMethod == 4)
				strLogData.Format(_T("[MARK ALIGN] CAM(1) ALIGN POINT [%d, %d] / CAM(3) ALIGN POINT [%d, %d]"),
					stAlign.AlignPoint[0].x, stAlign.AlignPoint[0].y, stAlign.AlignPoint[2].x, stAlign.AlignPoint[2].y);

			else if (nSelecteAlignMethod == 5)
				strLogData.Format(_T("[MARK ALIGN] CAM(2) ALIGN POINT [%d, %d] / CAM(4) ALIGN POINT [%d, %d]"),
					stAlign.AlignPoint[1].x, stAlign.AlignPoint[1].y, stAlign.AlignPoint[3].x, stAlign.AlignPoint[3].y);
		}

		csLogData = CStringA(strLogData);
		cFullLog = csLogData;
		cpFullLog = const_cast<char*>(cFullLog);
		LogWrite(ALIGNMENT, cpFullLog);
	}

	if (bJigProcess == true)
	{
		// Position 계산
		dXPosition_1 = (stAlign.AlignPoint[0].x - CamWidth / 2) * (AlignResolution / 1000);
		dXPosition_2 = (stAlign.AlignPoint[1].x - CamWidth / 2) * (AlignResolution / 1000);
		dXPosition_3 = (stAlign.AlignPoint[2].x - CamWidth / 2) * (AlignResolution / 1000);

		dYPosition_1 = (stAlign.AlignPoint[0].y - CamHeight / 2) * (AlignResolution / 1000);
		dYPosition_2 = (stAlign.AlignPoint[1].y - CamHeight / 2) * (AlignResolution / 1000);
		dYPosition_3 = (stAlign.AlignPoint[2].y - CamHeight / 2) * (AlignResolution / 1000);

		dModifyX = ((dXPosition_1 + dXPosition_2) / 2 + dXPosition_3) / 2;
		dModifyY = -((dYPosition_1 + dYPosition_2) / 2 + dYPosition_3) / 2;

		if (bChkMark == true)
			dModifyX -= 0.048;

		dModifyT = (dYPosition_1 - dYPosition_3) / (dAlignHeight - dXPosition_1 + dXPosition_3) * 180 / M_PI;

		dSizeX = (dAlignWidth + ((dXPosition_3) - (dXPosition_1 + dXPosition_2) / 2)) / dAlignWidth;
		dSizeY = (dAlignHeight + ((dYPosition_2) - (dYPosition_1 + dYPosition_3) / 2)) / dAlignHeight;
	}

	else if (bJigProcess == false)
	{
		if (nSelecteAlignMethod == 1)
		{
			// Position 계산
			dXPosition_1 = (stAlign.AlignPoint[0].x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_2 = (stAlign.AlignPoint[1].x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_3 = (stAlign.AlignPoint[2].x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_4 = (stAlign.AlignPoint[3].x - CamWidth / 2) * (AlignResolution / 1000);

			dYPosition_1 = (stAlign.AlignPoint[0].y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_2 = (stAlign.AlignPoint[1].y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_3 = (stAlign.AlignPoint[2].y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_4 = (stAlign.AlignPoint[3].y - CamHeight / 2) * (AlignResolution / 1000);

			dModifyX = (dXPosition_1 + dXPosition_2 + dXPosition_3 + dXPosition_4) / 4;
			dModifyY = -(dYPosition_1 + dYPosition_2 + dYPosition_3 + dYPosition_4) / 4;

			dModifyX -= 0.048;

			dT13 = (dYPosition_1 - dYPosition_3) / (dAlignWidth - dXPosition_1 + dXPosition_3) * 180 / M_PI;
			dT24 = (dYPosition_2 - dYPosition_4) / (dAlignWidth - dXPosition_2 + dXPosition_4) * 180 / M_PI;

			dModifyT = (dT13 + dT24) / 2;

			dSizeX = (dAlignWidth + (((dXPosition_3 + dXPosition_4) / 2) - (dXPosition_1 + dXPosition_2) / 2)) / dAlignWidth;
			dSizeY = (dAlignHeight + (((dYPosition_2 + dYPosition_4) / 2) - (dYPosition_1 + dYPosition_3) / 2)) / dAlignHeight;
		}

		else if (nSelecteAlignMethod == 2)
		{
			dXPosition_1 = (stAlign.AlignPoint[0].x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_2 = (stAlign.AlignPoint[1].x - CamWidth / 2) * (AlignResolution / 1000);

			dYPosition_1 = (stAlign.AlignPoint[0].y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_2 = (stAlign.AlignPoint[1].y - CamHeight / 2) * (AlignResolution / 1000);

			dModifyX = (dXPosition_1 + dXPosition_2) / 2;
			dModifyY = -(dYPosition_1 + dYPosition_2) / 2;

			dModifyX -= 0.048;

			dT12 = (dXPosition_1 - dXPosition_2) / (dAlignHeight - dYPosition_1 + dYPosition_2) * 180 / M_PI;

			dModifyT = dT12;

			dSizeX = 1.0;
			dSizeY = (dAlignHeight + (dYPosition_2 - dYPosition_1)) / dAlignHeight;
		}

		else if (nSelecteAlignMethod == 3)
		{
			dXPosition_3 = (stAlign.AlignPoint[2].x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_4 = (stAlign.AlignPoint[3].x - CamWidth / 2) * (AlignResolution / 1000);

			dYPosition_3 = (stAlign.AlignPoint[2].y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_4 = (stAlign.AlignPoint[3].y - CamHeight / 2) * (AlignResolution / 1000);

			dModifyX = (dXPosition_3 + dXPosition_4) / 2;
			dModifyY = -(dYPosition_3 + dYPosition_4) / 2;

			dModifyX -= 0.048;

			dT34 = (dXPosition_3 - dXPosition_4) / (dAlignHeight - dYPosition_3 + dYPosition_4) * 180 / M_PI;

			dModifyT = dT34;

			dSizeX = 1.0;
			dSizeY = (dAlignHeight + (dYPosition_4 - dYPosition_3)) / dAlignHeight;

		}

		else if (nSelecteAlignMethod == 4)
		{
			dXPosition_1 = (stAlign.AlignPoint[0].x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_3 = (stAlign.AlignPoint[2].x - CamWidth / 2) * (AlignResolution / 1000);

			dYPosition_1 = (stAlign.AlignPoint[0].y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_3 = (stAlign.AlignPoint[2].y - CamHeight / 2) * (AlignResolution / 1000);

			dModifyX = (dXPosition_1 + dXPosition_3) / 2;
			dModifyY = -(dYPosition_1 + dYPosition_3) / 2;

			dModifyX -= 0.048;

			dT13 = (dYPosition_1 - dYPosition_3) / (dAlignWidth - dXPosition_1 + dXPosition_3) * 180 / M_PI;

			dModifyT = dT13;

			dSizeX = (dAlignWidth + (dXPosition_3 - dXPosition_1)) / dAlignWidth;
			dSizeY = 1.0;
		}

		else if (nSelecteAlignMethod == 5)
		{
			dXPosition_2 = (stAlign.AlignPoint[1].x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_4 = (stAlign.AlignPoint[3].x - CamWidth / 2) * (AlignResolution / 1000);

			dYPosition_2 = (stAlign.AlignPoint[1].y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_4 = (stAlign.AlignPoint[3].y - CamHeight / 2) * (AlignResolution / 1000);

			dModifyX = (dXPosition_2 + dXPosition_4) / 2;
			dModifyY = -(dYPosition_2 + dYPosition_4) / 2;

			dModifyX -= 0.048;

			dT24 = (dYPosition_2 - dYPosition_4) / (dAlignWidth - dXPosition_2 + dXPosition_4) * 180 / M_PI;

			dModifyT = dT24;

			dSizeX = (dAlignWidth + (dXPosition_4 - dXPosition_2)) / dAlignWidth;
			dSizeY = 1.0;
		}
	}

	if (bChkEdge == true)
	{
		if (nSelecteAlignMethod == 1)
		{
			double dMistake = 0;
			double dLevel1 = 0;
			double dLevel2 = 0;
			double dMax = 0;
			CString strVal;

			dLevel1 = stAlign.AlignPoint[2].y - stAlign.AlignPoint[0].y;
			dLevel2 = stAlign.AlignPoint[3].y - stAlign.AlignPoint[1].y;

			double dLevel = dLevel1 - dLevel2;
			dLevel = abs(dLevel) * AlignResolution / 1000;

			if (dLevel > dRangeHLevel)
			{
				dlgVisionAlign->bChkLevel = false;
				dlgVisionAlign->GetDlgItem(IDC_STATIC_LEVEL_H_JUDGE)->SetWindowTextW(_T("NG"));
				bRet = false;
			}

			strVal.Format(_T("%.3fmm"), dLevel);
			dlgVisionAlign->GetDlgItem(IDC_STATIC_LEVEL_H_VALUE)->SetWindowTextW(strVal);

			for (int i = 0; i < 4; i++)
			{
				dMistake = stEdgeAlign.EdgeStart[i].y - stEdgeAlign.EdgeEnd[i].y;
				dMistake = abs(dMistake) * AlignResolution / 1000;

				if (dMistake > dMax)
					dMax = dMistake;

				if (dMistake >= dRangeMistake)
				{
					dlgVisionAlign->bChkMistake = false;
					dlgVisionAlign->GetDlgItem(IDC_STATIC_MISTAKE_JUDGE)->SetWindowTextW(_T("NG"));
					stEdgeAlign.ChkMistake[i] = false;
					bRet = false;
				}

				else
					stEdgeAlign.ChkMistake[i] = true;
			}

			strVal.Format(_T("%.3fmm"), dMax);
			dlgVisionAlign->GetDlgItem(IDC_STATIC_MISTAKE_VALUE)->SetWindowTextW(strVal);
		}
	}

	if (abs(dModifyX) > dRangeX)
	{
		dlgVisionAlign->bChkModifyX = false;
		dlgVisionAlign->GetDlgItem(IDC_STATIC_XMODIFY_JUDGE)->SetWindowTextW(_T("NG"));
		bRet = false;
	}

	else if (abs(dModifyX) <= dRangeX)
	{
		dlgVisionAlign->bChkModifyX = true;
		dlgVisionAlign->GetDlgItem(IDC_STATIC_XMODIFY_JUDGE)->SetWindowTextW(_T("OK"));
	}

	if (abs(dModifyY) > dRangeY)
	{
		dlgVisionAlign->bChkModifyY = false;
		dlgVisionAlign->GetDlgItem(IDC_STATIC_YMODIFY_JUDGE)->SetWindowTextW(_T("NG"));
		bRet = false;
	}

	else if (abs(dModifyY) <= dRangeY)
	{
		dlgVisionAlign->bChkModifyY = true;
		dlgVisionAlign->GetDlgItem(IDC_STATIC_YMODIFY_JUDGE)->SetWindowTextW(_T("OK"));
	}

	if (abs(dModifyT) > dRangeT)
	{
		dlgVisionAlign->bChkModifyT = false;
		dlgVisionAlign->GetDlgItem(IDC_STATIC_TMODIFY_JUDGE)->SetWindowTextW(_T("NG"));
		bRet = false;
	}

	else if (abs(dModifyT) <= dRangeT)
	{
		dlgVisionAlign->bChkModifyT = true;
		dlgVisionAlign->GetDlgItem(IDC_STATIC_TMODIFY_JUDGE)->SetWindowTextW(_T("OK"));
	}

	if (dAutosizing == 1)
	{
		dSizeX = 1.0;
		dSizeY = 1.0;
	}

	strLogData.Format(_T("[AutoSizing] AutoSizing Return Value [%.8f, %.8f]"), dSizeX, dSizeY);
	csLogData = CStringA(strLogData);
	cFullLog = csLogData;
	cpFullLog = const_cast<char*>(cFullLog);
	LogWrite(ALIGNMENT, cpFullLog);

	// 값 display 
	strValue.Format(_T("%.3fmm"), dModifyX);
	dlgVisionAlign->GetDlgItem(IDC_STATIC_XMODIFY_VALUE)->SetWindowTextW(strValue);

	strValue.Format(_T("%.3fmm"), dModifyY);
	dlgVisionAlign->GetDlgItem(IDC_STATIC_YMODIFY_VALUE)->SetWindowTextW(strValue);

	strValue.Format(_T("%.6f˚"), dModifyT);
	dlgVisionAlign->GetDlgItem(IDC_STATIC_TMODIFY_VALUE)->SetWindowTextW(strValue);

	strLogData.Format(_T("[Vision 오차] X축 보정 값 : %.3fmm[%d], Y축 보정 값 : %.3fmm[%d], THETA 보정 값 : %.6f˚[%d]"),
		dModifyX, dlgVisionAlign->bChkModifyX, dModifyY, dlgVisionAlign->bChkModifyY, dModifyT, dlgVisionAlign->bChkModifyT);
	csLogData = CStringA(strLogData);
	cFullLog = csLogData;
	cpFullLog = const_cast<char*>(cFullLog);
	LogWrite(ALIGNMENT, cpFullLog);

	dErrorLGentry = dLGentryPos - (dLGentryStdPos - ((dAlignWidth - 167) / 2));
	dErrorRGentry = (dRGentryStdPos - ((dAlignWidth - 167) / 2)) - dRGentryPos;

	dErrorCam1 = (dCam1StdPos - ((dAlignHeight - 167) / 2)) - dCam1Pos;
	dErrorCam2 = (dCam2StdPos + ((dAlignHeight - 167) / 2)) - dCam2Pos;
	dErrorCam3 = (dCam3StdPos - ((dAlignHeight - 167) / 2)) - dCam3Pos;
	dErrorCam4 = dCam4Pos - (dCam4StdPos - ((dAlignHeight - 167) / 2));

	dErrorX = (dErrorLGentry + dErrorRGentry) / 2;

	if (bJigProcess == true)
		dErrorY = ((dErrorCam1 + dErrorCam3) / 2 + dErrorCam2) / 2;

	else if (bJigProcess == false)
		dErrorY = (dErrorCam1 + dErrorCam2 + dErrorCam3 + dErrorCam4) / 4;

	strLogData.Format(_T("[Position 오차] Gentry Shift Value : %.3fmm, Vision Cam Shift Value : %.3fmm"), dErrorX, dErrorY);
	csLogData = CStringA(strLogData);
	cFullLog = csLogData;
	cpFullLog = const_cast<char*>(cFullLog);
	LogWrite(ALIGNMENT, cpFullLog);

	dModifyX += dErrorX;
	dModifyY += dErrorY;

	strLogData.Format(_T("[Laser Calibration offset] X축 offset : %.3fmm Y축 offset : %.3fmm"), dLCOffsetX, dLCOffsetY);
	csLogData = CStringA(strLogData);
	cFullLog = csLogData;
	cpFullLog = const_cast<char*>(cFullLog);
	LogWrite(ALIGNMENT, cpFullLog);

	dModifyX += dLCOffsetX;
	dModifyY -= dLCOffsetY;

	strLogData.Format(_T("[Manual offset] X축 offset : %.3fmm Y축 offset : %.3fmm Theta offset : %.6f˚"), dManualOffsetX, dManualOffsetY, dManualOffsetT);
	csLogData = CStringA(strLogData);
	cFullLog = csLogData;
	cpFullLog = const_cast<char*>(cFullLog);
	LogWrite(ALIGNMENT, cpFullLog);

	dModifyX += dManualOffsetX;
	dModifyY += dManualOffsetY;
	dModifyT += dManualOffsetT;

	CString strVal;
	double dVal;

	dlgVisionSetting->dlgSettingAlign->m_edit_xoffset.GetWindowTextW(strVal);
	dPostX = (_wtof(strVal) / 1000);

	dlgVisionSetting->dlgSettingAlign->m_edit_yoffset.GetWindowTextW(strVal);
	dPostY = (_wtof(strVal) / 1000);

	dlgVisionSetting->dlgSettingAlign->m_edit_toffset.GetWindowTextW(strVal);
	dPostT = _wtof(strVal);

	strLogData.Format(_T("[Align Vision offset] X축 offset : %.3fmm, Y축 offset : %.3fmm, Theta offset : %.6f˚"), dPostX, dPostY, dPostT);
	csLogData = CStringA(strLogData);
	cFullLog = csLogData;
	cpFullLog = const_cast<char*>(cFullLog);
	LogWrite(ALIGNMENT, cpFullLog);

	dModifyX += dPostX;
	dModifyY += dPostY;
	dModifyT += dPostT;

	strLogData.Format(_T("[Align Total Result] X축 보정 값 : %.3fmm, Y축 보정 값 : %.3fmm, THETA 보정 값 : %.6f˚"), dModifyX, dModifyY, dModifyT);
	csLogData = CStringA(strLogData);
	cFullLog = csLogData;
	cpFullLog = const_cast<char*>(cFullLog);
	LogWrite(ALIGNMENT, cpFullLog);

	if (bRet == false)
	{
		dlgVisionAlign->bChkJudge = false;
		dlgVisionAlign->GetDlgItem(IDC_STATIC_TOTALJUDGE)->SetWindowTextW(_T("NG"));
		strResult = _T("ALIGN 측정 결과 : NG");

		LogWrite(ALIGNMENT, "ALIGN RESULT [NG]");
	}


	else if (bRet == true)
	{
		dlgVisionAlign->bChkJudge = true;
		dlgVisionAlign->GetDlgItem(IDC_STATIC_TOTALJUDGE)->SetWindowTextW(_T("OK"));
		strResult = _T("ALIGN 측정 결과 : OK");

		LogWrite(ALIGNMENT, "ALIGN RESULT [OK]");
	}

	GetLocalTime(&AlignEndtime);

	int ProcTime;
	int n = 0;
	int count = 0;

	CString strTime;
	ProcTime = ((AlignEndtime.wSecond - AlignStarttime.wSecond) * 1000) + (AlignEndtime.wMilliseconds - AlignStarttime.wMilliseconds);

	while (ProcTime > 0)
	{
		count++;
		n = ProcTime % 10;
		ProcTime = ProcTime / 10;

		strTime.Format(L"%d" + strTime, n);

		if ((count % 3 == 0) && (ProcTime > 0))
			strTime.Format(L"," + strTime);
	}

	dlgVisionAlign->m_icon_alignstart.SetBitmap(m_bmp_ledoff2);
	dlgVisionAlign->m_icon_alignrun.SetBitmap(m_bmp_ledoff2);
	dlgVisionAlign->m_icon_alignend.SetBitmap(m_bmp_ledon2);


	CString result;

	result = _T("ProcTime : ") + strTime + _T("ms");
	dlgVisionAlign->GetDlgItem(IDC_STATIC_PROCTIME)->SetWindowTextW(result);

	strLogData = _T("ALIGN PROCESS TIME [") + strTime + _T("ms]");

	csLogData = CStringA(strLogData);
	cFullLog = csLogData;
	cpFullLog = const_cast<char*>(cFullLog);
	LogWrite(ALIGNMENT, cpFullLog);

	// 데이터 전송
	if (bRet == true)
		stSendData.nResult = 1;

	else if (bRet == false)
		stSendData.nResult = 0;

	stSendData.dXModify = dModifyX;
	stSendData.dYModify = dModifyY;
	stSendData.dTModify = dModifyT;
	stSendData.dScaleX = dSizeX;
	stSendData.dScaleY = dSizeY;

	stSendData.bClientReceive = true;
	stSendData.bServerReceive = false;

	stSend.lpData = &stSendData;
	stSend.cbData = sizeof(stSendData);
	stSend.dwData = 4;

	::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);

	//AlignResultFile();
}


void CRVisionDlg::OnBnClickedBtnModeAlign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CWnd* pWnd = AfxGetMainWnd();

	ExcutionDialog(0);
}


void CRVisionDlg::OnBnClickedBtnModeReview()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ExcutionDialog(1);
}


void CRVisionDlg::OnBnClickedBtnModeFc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ExcutionDialog(2);
}


void CRVisionDlg::OnBnClickedBtnModeSetting()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ExcutionDialog(4);
}


void CRVisionDlg::OnStnClickedIconLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CWnd* pWnd = AfxGetMainWnd();

	/*if (m_icon_login.GetBitmap() == m_bmp_logout)
	{
		m_icon_login.SetBitmap(m_bmp_login);
	}

	else if (m_icon_login.GetBitmap() == m_bmp_login)
	{
		m_icon_login.SetBitmap(m_bmp_logout);
	}

	ExcutionManualAlign();*/

	//ExcutionManualAlign();

	//stSendData.dXModify = 1.1;
	//stSendData.dYModify = 2.2;
	//stSendData.dTModify = 3.3;
	/*stSendData.nResult = 1;
	stSendData.nAlignMethod = 123;
	stSendData.bClientReceive = true;
	stSendData.bServerReceive = false;

	stSend->lpData = &stSendData;
	stSend->cbData = sizeof(stSendData);
	stSend->dwData = 4;

	::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)stSend);*/

	//PathSize();
	//CString path = _T("D:\\VisionData");
	//ChkFolder(_T("D:\\VisionData"));
	//DeleteFolder(path);
	//delete cBaumer;


	/*if (Vision != NULL)
	{
		bChkCamera = false;
		for (int i = 0; i < 5; i++)
		{
			if (cBaumer->Status[i] == true)
				cBaumer->m_camera_set[i].pDataStreamf->UnregisterNewBufferEvent();
		}

		Vision->SuspendThread();

		DWORD dwResult;
		::GetExitCodeThread(Vision->m_hThread, &dwResult);
		delete Vision;
		Vision = NULL;

		delete cBaumer;

		Sleep(1000);

		ConnectCamera();
	}

	else
	{
	}*/

	//ConnectCamera();

	//stSendData.wdVisionErrorData.setBit(0, false);
}

void CRVisionDlg::DisplayColor(int nCase)
{
	if (nCase == 0)
	{
		m_btn_mode_align.SetFaceColor(ColorGreen);
		m_btn_mode_review.SetFaceColor(ColorBasic);
		m_btn_mode_fc.SetFaceColor(ColorBasic);
		m_btn_mode_setting.SetFaceColor(ColorBasic);
	}

	else if (nCase == 1)
	{
		m_btn_mode_align.SetFaceColor(ColorBasic);
		m_btn_mode_review.SetFaceColor(ColorGreen);
		m_btn_mode_fc.SetFaceColor(ColorBasic);
		m_btn_mode_setting.SetFaceColor(ColorBasic);
	}

	else if (nCase == 2)
	{
		m_btn_mode_align.SetFaceColor(ColorBasic);
		m_btn_mode_review.SetFaceColor(ColorBasic);
		m_btn_mode_fc.SetFaceColor(ColorGreen);
		m_btn_mode_setting.SetFaceColor(ColorBasic);
	}

	else if (nCase == 3 || nCase == 4)
	{
		m_btn_mode_align.SetFaceColor(ColorBasic);
		m_btn_mode_review.SetFaceColor(ColorBasic);
		m_btn_mode_fc.SetFaceColor(ColorBasic);
		m_btn_mode_setting.SetFaceColor(ColorGreen);
	}
}


UINT CRVisionDlg::Vision_Thread(LPVOID pParam)
{
	CRVisionDlg* dlg_vision = (CRVisionDlg*)pParam;

	while (1)
	{
		// Align Camera 1
		if (dlg_vision->cBaumer->Status[0] == true)
		{
			if (dlg_vision->cBaumer->m_camera_set[0].m_updisplay == 1)
				dlg_vision->DisplayCam_0();
		}

		// Align Camera 2
		if (dlg_vision->cBaumer->Status[1] == true)
		{
			if (dlg_vision->cBaumer->m_camera_set[1].m_updisplay == 1)
				dlg_vision->DisplayCam_1();
		}

		// Align Camera 3
		if (dlg_vision->cBaumer->Status[2] == true)
		{
			if (dlg_vision->cBaumer->m_camera_set[2].m_updisplay == 1)
				dlg_vision->DisplayCam_2();
		}

		// Align Camera 4
		if (dlg_vision->cBaumer->Status[3] == true)
		{
			if (dlg_vision->cBaumer->m_camera_set[3].m_updisplay == 1)
				dlg_vision->DisplayCam_3();
		}

		// Review Camera
		if (dlg_vision->cBaumer->Status[4] == true)
		{
			if (dlg_vision->cBaumer->m_camera_set[4].m_updisplay == 1)
				dlg_vision->DisplayCam_4();
		}
	}
	return 0;
}


UINT CRVisionDlg::Volume_Thread(LPVOID pParam)
{
	CRVisionDlg* pDlg = (CRVisionDlg*)pParam;

	while (1)
	{
		GetDiskFreeSpaceEx(TEXT("D:\\"), &pDlg->avail, &pDlg->total, &pDlg->free);
		pDlg->nTotal = (int)(pDlg->total.QuadPart >> 30);
		pDlg->nAvail = (int)(pDlg->avail.QuadPart >> 30);
		pDlg->nFree = (int)(pDlg->free.QuadPart >> 30);

		if (pDlg->nFree < pDlg->nTotal * 0.20)
		{
			pDlg->ChkFolder(_T("D:\\VisionData\\Alignment"));
		}
	}

	return 0;
}


UINT CRVisionDlg::Proc_Thread(LPVOID pParam)
{
	CRVisionDlg* pDlg = (CRVisionDlg*)pParam;
	CWnd* pWnd = AfxGetMainWnd();

	while (1)
	{
		if (pDlg->CHK_PROC == 1)
		{
			// align 시작 시간 확인
			GetLocalTime(&pDlg->AlignStarttime);

			if (pDlg->bChkEdge == 1 && pDlg->bChkMark == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					// 12
					if (pDlg->nSelecteAlignMethod == 2)
					{
						if (i == 2 || i == 3)
							continue;
					}

					// 34
					else if (pDlg->nSelecteAlignMethod == 3)
					{
						if (i == 0 || i == 1)
							continue;
					}

					// 13
					else if (pDlg->nSelecteAlignMethod == 4)
					{
						if (i == 1 || i == 3)
							continue;
					}

					else if (pDlg->nSelecteAlignMethod == 5)
					{
						if (i == 0 || i == 2)
							continue;
					}

					pDlg->strLogData.Format(_T("CAM[%d] EDGE ALIGNMENT 동작"), i + 1);
					pDlg->csLogData = CStringA(pDlg->strLogData);
					pDlg->cFullLog = pDlg->csLogData;
					pDlg->cpFullLog = const_cast<char*>(pDlg->cFullLog);
					LogWrite(ALIGNMENT, pDlg->cpFullLog);

					pDlg->EdgeFind(i);
				}

				// 검출에 성공한 경우
				if (pDlg->nSelecteAlignMethod == 1 && ((stEdgeAlign.ChkFind[0] == true && stEdgeAlign.ChkFind[1] == true && stEdgeAlign.ChkFind[2] == true && stEdgeAlign.ChkFind[3] == true)) ||
					pDlg->nSelecteAlignMethod == 2 && ((stEdgeAlign.ChkFind[0] == true && stEdgeAlign.ChkFind[1] == true)) ||
					pDlg->nSelecteAlignMethod == 3 && ((stEdgeAlign.ChkFind[2] == true && stEdgeAlign.ChkFind[3] == true)) ||
					pDlg->nSelecteAlignMethod == 4 && ((stEdgeAlign.ChkFind[0] == true && stEdgeAlign.ChkFind[2] == true)) ||
					pDlg->nSelecteAlignMethod == 5 && ((stEdgeAlign.ChkFind[1] == true && stEdgeAlign.ChkFind[3] == true))
					)
				{
					pDlg->AlignCalcuration();
				}

				// 검출에 실패한 경우
				else
				{
					LogWrite(ALIGNMENT, "EDGE ALIGNMENT FAIL");

					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_TOTALJUDGE)->SetWindowTextW(_T("NG"));

					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_XMODIFY_VALUE)->SetWindowTextW(_T("-"));
					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_YMODIFY_VALUE)->SetWindowTextW(_T("-"));
					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_TMODIFY_VALUE)->SetWindowTextW(_T("-"));

					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_XMODIFY_JUDGE)->SetWindowTextW(_T("-"));
					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_YMODIFY_JUDGE)->SetWindowTextW(_T("-"));
					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_TMODIFY_JUDGE)->SetWindowTextW(_T("-"));

					// 데이터 전송
					pDlg->stSendData.dXModify = 0.0;
					pDlg->stSendData.dYModify = 0.0;
					pDlg->stSendData.dTModify = 0.0;
					pDlg->stSendData.dScaleX = 1.0;
					pDlg->stSendData.dScaleY = 1.0;

					pDlg->stSendData.nResult = 0;
					pDlg->stSendData.bClientReceive = true;
					pDlg->stSendData.bServerReceive = false;

					pDlg->stSend.lpData = &pDlg->stSendData;
					pDlg->stSend.cbData = sizeof(pDlg->stSendData);
					pDlg->stSend.dwData = 4;

					::SendMessage(pDlg->hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&pDlg->stSend);

					GetLocalTime(&pDlg->AlignEndtime);

					int ProcTime;
					int n = 0;
					int count = 0;

					CString strTime;
					ProcTime = ((pDlg->AlignEndtime.wSecond - pDlg->AlignStarttime.wSecond) * 1000) +
						(pDlg->AlignEndtime.wMilliseconds - pDlg->AlignStarttime.wMilliseconds);

					while (ProcTime > 0)
					{
						count++;
						n = ProcTime % 10;
						ProcTime = ProcTime / 10;

						strTime.Format(L"%d" + strTime, n);

						if ((count % 3 == 0) && (ProcTime > 0))
							strTime.Format(L"," + strTime);
					}

					pDlg->dlgVisionAlign->m_icon_alignstart.SetBitmap(pDlg->m_bmp_ledoff2);
					pDlg->dlgVisionAlign->m_icon_alignrun.SetBitmap(pDlg->m_bmp_ledoff2);
					pDlg->dlgVisionAlign->m_icon_alignend.SetBitmap(pDlg->m_bmp_ledon2);

					CString result;

					result = _T("ProcTime : ") + strTime + _T("ms");
					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_PROCTIME)->SetWindowTextW(result);

				}
			}

			else if (pDlg->bChkMark == 1 && pDlg->bChkEdge == 0)
			{
				// Jig Process
				if (pDlg->bJigProcess == true)
				{
					for (int i = 0; i < 3; i++)
					{
						pDlg->strLogData.Format(_T("CAM[%d] MARK ALIGNMENT 동작"), i + 1);
						pDlg->csLogData = CStringA(pDlg->strLogData);
						pDlg->cFullLog = pDlg->csLogData;
						pDlg->cpFullLog = const_cast<char*>(pDlg->cFullLog);
						LogWrite(ALIGNMENT, pDlg->cpFullLog);

						pDlg->MarkFind(i, 0);
					}
				}

				// else Sheet or Roll
				else if (pDlg->bJigProcess == false)
				{
					for (int i = 0; i < 4; i++)
					{
						if (pDlg->nAlignMethod == 2)
						{
							if (i == 2 || i == 3)
								continue;
						}

						// 34
						else if (pDlg->nAlignMethod == 3)
						{
							if (i == 0 || i == 1)
								continue;
						}

						// 13
						else if (pDlg->nAlignMethod == 4)
						{
							if (i == 1 || i == 3)
								continue;
						}

						else if (pDlg->nAlignMethod == 5)
						{
							if (i == 0 || i == 2)
								continue;
						}

						pDlg->strLogData.Format(_T("CAM[%d] MARK ALIGNMENT 동작"), i + 1);
						pDlg->csLogData = CStringA(pDlg->strLogData);
						pDlg->cFullLog = pDlg->csLogData;
						pDlg->cpFullLog = const_cast<char*>(pDlg->cFullLog);
						LogWrite(ALIGNMENT, pDlg->cpFullLog);

						pDlg->MarkFind(i, 0);
					}
				}

				// Jig Process 인 경우에 1번, 2번, 3번 카메라 검출이 성공되었을 경우
				if (pDlg->bJigProcess == true &&
					stMarkAlign.nChkFindMark[0] == 1 && stMarkAlign.nChkFindMark[1] == 1 &&
					stMarkAlign.nChkFindMark[2] == 1)
				{
					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_4)->SetWindowTextW(_T("-"));
					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_4)->SetWindowTextW(_T("-"));

					pDlg->AlignCalcuration();
				}

				// Jig Process 가 아닌 경우에 1, 2, 3, 4 번 카메라 모두 검출이 성공한 경우

				else if (pDlg->bJigProcess == false &&
					pDlg->nSelecteAlignMethod == 1 && ((stMarkAlign.nChkFindMark[0] == true && stMarkAlign.nChkFindMark[1] == true && stMarkAlign.nChkFindMark[2] == true && stMarkAlign.nChkFindMark[3] == true)) ||
					pDlg->nSelecteAlignMethod == 2 && ((stMarkAlign.nChkFindMark[0] == true && stMarkAlign.nChkFindMark[1] == true)) ||
					pDlg->nSelecteAlignMethod == 3 && ((stMarkAlign.nChkFindMark[2] == true && stMarkAlign.nChkFindMark[3] == true)) ||
					pDlg->nSelecteAlignMethod == 4 && ((stMarkAlign.nChkFindMark[0] == true && stMarkAlign.nChkFindMark[2] == true)) ||
					pDlg->nSelecteAlignMethod == 5 && ((stMarkAlign.nChkFindMark[1] == true && stMarkAlign.nChkFindMark[3] == true))
					)
				{
					pDlg->AlignCalcuration();
				}

				else
				{
					LogWrite(ALIGNMENT, "MARK ALIGNMENT FAIL");

					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_TOTALJUDGE)->SetWindowTextW(_T("NG"));

					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_XMODIFY_VALUE)->SetWindowTextW(_T("-"));
					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_YMODIFY_VALUE)->SetWindowTextW(_T("-"));
					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_TMODIFY_VALUE)->SetWindowTextW(_T("-"));

					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_XMODIFY_JUDGE)->SetWindowTextW(_T("-"));
					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_YMODIFY_JUDGE)->SetWindowTextW(_T("-"));
					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_TMODIFY_JUDGE)->SetWindowTextW(_T("-"));

					// 데이터 전송
					pDlg->stSendData.dXModify = 0.0;
					pDlg->stSendData.dYModify = 0.0;
					pDlg->stSendData.dTModify = 0.0;
					pDlg->stSendData.dScaleX = 1.0;
					pDlg->stSendData.dScaleY = 1.0;
					
					pDlg->stSendData.nResult = 0;

					pDlg->stSendData.bClientReceive = true;
					pDlg->stSendData.bServerReceive = false;

					pDlg->stSend.lpData = &pDlg->stSendData;
					pDlg->stSend.cbData = sizeof(pDlg->stSendData);
					pDlg->stSend.dwData = 4;

					::SendMessage(pDlg->hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&pDlg->stSend);
					GetLocalTime(&pDlg->AlignEndtime);

					int ProcTime;
					int n = 0;
					int count = 0;

					CString strTime;
					ProcTime = ((pDlg->AlignEndtime.wSecond - pDlg->AlignStarttime.wSecond) * 1000) +
						(pDlg->AlignEndtime.wMilliseconds - pDlg->AlignStarttime.wMilliseconds);

					while (ProcTime > 0)
					{
						count++;
						n = ProcTime % 10;
						ProcTime = ProcTime / 10;

						strTime.Format(L"%d" + strTime, n);

						if ((count % 3 == 0) && (ProcTime > 0))
							strTime.Format(L"," + strTime);
					}

					pDlg->dlgVisionAlign->m_icon_alignstart.SetBitmap(pDlg->m_bmp_ledoff2);
					pDlg->dlgVisionAlign->m_icon_alignrun.SetBitmap(pDlg->m_bmp_ledoff2);
					pDlg->dlgVisionAlign->m_icon_alignend.SetBitmap(pDlg->m_bmp_ledon2);

					CString result;

					result = _T("ProcTime : ") + strTime + _T("ms");
					pDlg->dlgVisionAlign->GetDlgItem(IDC_STATIC_PROCTIME)->SetWindowTextW(result);
				}
			}

			pDlg->CHK_PROC = false;
		}
	}

	return 0;
}


void CRVisionDlg::DisplayCam_0()
{
	CClientDC dc(dlgVisionAlign->dlgDrawAlign->GetDlgItem(IDC_PIC_ALIGN1));
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;
	CRect rect;


	CClientDC dcSetting(dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING));
	CDC memDC_setting;
	CBitmap* pOldBitmap_setting, bitmap_setting;
	CRect rectSetting;

	cBaumer->m_camera_set[0].m_updisplay = 0;

	memDC.CreateCompatibleDC(&dc);
	dlgVisionAlign->dlgDrawAlign->GetDlgItem(IDC_PIC_ALIGN1)->GetClientRect(&rect);
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), BLACKNESS);

	BYTE* Img_0;

	Img_0 = reinterpret_cast<BYTE*>(cBaumer->m_camera_set[0].m_buf);

	CamModify_1 = Mat(2048, 2448, CV_8UC1, Img_0);

	for (int i = 0; i < CamModify1; i += 2)
	{
		CamModify_1.at<char>(CamPoint_1[i].y, CamPoint_1[i].x) = CamModify_1.at<char>(CamModifyPoint_1[i].y, CamModifyPoint_1[i].x);
	}

	// setting dialog를 선택하였을 경우에만
	if (CHK_SETTING == true)
	{
		// camera 설정일 경우
		if (dlgVisionSetting->SelectSetting == 0)
		{
			if (dlgVisionSetting->dlgSettingCamera->SelectCam == 0)
			{
				memDC_setting.CreateCompatibleDC(&dcSetting);
				dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING)->GetClientRect(&rectSetting);
				bitmap_setting.CreateCompatibleBitmap(&dcSetting, rectSetting.Width(), rectSetting.Height());
				pOldBitmap_setting = memDC_setting.SelectObject(&bitmap_setting);
				memDC_setting.PatBlt(0, 0, rectSetting.Width(), rectSetting.Height(), BLACKNESS);

				DisplayDrawSetting(&memDC_setting, 0);

				dcSetting.BitBlt(0, 0, rectSetting.Width(), rectSetting.Height(), &memDC_setting, 0, 0, SRCCOPY);
				memDC_setting.SelectObject(pOldBitmap_setting);

				memDC_setting.DeleteDC();
				bitmap_setting.DeleteObject();
			}
		}

		// align 설정일 경우
		else if (dlgVisionSetting->SelectSetting == 1)
		{
			if (dlgVisionSetting->dlgSettingAlign->SelectCam == 0)
			{
				memDC_setting.CreateCompatibleDC(&dcSetting);
				dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING)->GetClientRect(&rectSetting);
				bitmap_setting.CreateCompatibleBitmap(&dcSetting, rectSetting.Width(), rectSetting.Height());
				pOldBitmap_setting = memDC_setting.SelectObject(&bitmap_setting);
				memDC_setting.PatBlt(0, 0, rectSetting.Width(), rectSetting.Height(), BLACKNESS);

				DisplayDrawSetting(&memDC_setting, 0);

				dcSetting.BitBlt(0, 0, rectSetting.Width(), rectSetting.Height(), &memDC_setting, 0, 0, SRCCOPY);
				memDC_setting.SelectObject(pOldBitmap_setting);

				memDC_setting.DeleteDC();
				bitmap_setting.DeleteObject();
			}
		}

		else if (dlgVisionSetting->SelectSetting == 2)
		{
			if (dlgVisionSetting->dlgSettingAlignMark->SelectCam == 0)
			{
				memDC_setting.CreateCompatibleDC(&dcSetting);
				dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING)->GetClientRect(&rectSetting);
				bitmap_setting.CreateCompatibleBitmap(&dcSetting, rectSetting.Width(), rectSetting.Height());
				pOldBitmap_setting = memDC_setting.SelectObject(&bitmap_setting);
				memDC_setting.PatBlt(0, 0, rectSetting.Width(), rectSetting.Height(), BLACKNESS);

				DisplayDrawSetting(&memDC_setting, 0);

				dcSetting.BitBlt(0, 0, rectSetting.Width(), rectSetting.Height(), &memDC_setting, 0, 0, SRCCOPY);
				memDC_setting.SelectObject(pOldBitmap_setting);

				memDC_setting.DeleteDC();
				bitmap_setting.DeleteObject();
			}
		}
	}

	DisplayDrawAlign(&memDC, 0);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);

	memDC.DeleteDC();
	bitmap.DeleteObject();

	if (dlgPopupManualAlign.ChkActive == true)
	{
		if (dlgPopupManualAlign.SelectCam == 0)
		{
			CClientDC dc_manual(dlgPopupManualAlign.GetDlgItem(IDC_PIC_MANUALALIGN));
			CDC memDC_manual;
			CBitmap* pOldBitmap_manual, bitmap_manual;
			CRect rect_manual;

			memDC_manual.CreateCompatibleDC(&dc_manual);
			dlgPopupManualAlign.GetDlgItem(IDC_PIC_MANUALALIGN)->GetClientRect(&rect_manual);
			bitmap_manual.CreateCompatibleBitmap(&dc_manual, rect_manual.Width(), rect_manual.Height());
			pOldBitmap_manual = memDC_manual.SelectObject(&bitmap_manual);
			memDC_manual.PatBlt(0, 0, rect_manual.Width(), rect_manual.Height(), BLACKNESS);

			DisplayDrawManualAlign(&memDC_manual, 0);

			dc_manual.BitBlt(0, 0, rect_manual.Width(), rect_manual.Height(), &memDC_manual, 0, 0, SRCCOPY);
			memDC_manual.SelectObject(pOldBitmap_manual);

			memDC_manual.DeleteDC();
			bitmap_manual.DeleteObject();
		}
	}
}


void CRVisionDlg::DisplayCam_1()
{
	CClientDC dc(dlgVisionAlign->dlgDrawAlign->GetDlgItem(IDC_PIC_ALIGN2));
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;
	CRect rect;

	CClientDC dcSetting(dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING));
	CDC memDC_setting;
	CBitmap* pOldBitmap_setting, bitmap_setting;
	CRect rectSetting;

	cBaumer->m_camera_set[1].m_updisplay = 0;

	memDC.CreateCompatibleDC(&dc);
	dlgVisionAlign->dlgDrawAlign->GetDlgItem(IDC_PIC_ALIGN2)->GetClientRect(&rect);
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), BLACKNESS);

	BYTE* Img_0;

	Img_0 = reinterpret_cast<BYTE*>(cBaumer->m_camera_set[1].m_buf);

	CamModify_2 = Mat(2048, 2448, CV_8UC1, Img_0);

	for (int i = 0; i < CamModify2; i += 2)
	{
		CamModify_2.at<char>(CamPoint_2[i].y, CamPoint_2[i].x) = CamModify_2.at<char>(CamModifyPoint_2[i].y, CamModifyPoint_2[i].x);
	}
	// setting dialog를 선택하였을 경우에만
	if (CHK_SETTING == true)
	{
		// camera 설정일 경우
		if (dlgVisionSetting->SelectSetting == 0)
		{
			if (dlgVisionSetting->dlgSettingCamera->SelectCam == 1)
			{
				memDC_setting.CreateCompatibleDC(&dcSetting);
				dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING)->GetClientRect(&rectSetting);
				bitmap_setting.CreateCompatibleBitmap(&dcSetting, rectSetting.Width(), rectSetting.Height());
				pOldBitmap_setting = memDC_setting.SelectObject(&bitmap_setting);
				memDC_setting.PatBlt(0, 0, rectSetting.Width(), rectSetting.Height(), BLACKNESS);

				DisplayDrawSetting(&memDC_setting, 1);

				dcSetting.BitBlt(0, 0, rectSetting.Width(), rectSetting.Height(), &memDC_setting, 0, 0, SRCCOPY);
				memDC_setting.SelectObject(pOldBitmap_setting);

				memDC_setting.DeleteDC();
				bitmap_setting.DeleteObject();
			}
		}

		// align 설정일 경우
		else if (dlgVisionSetting->SelectSetting == 1)
		{
			if (dlgVisionSetting->dlgSettingAlign->SelectCam == 1)
			{
				memDC_setting.CreateCompatibleDC(&dcSetting);
				dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING)->GetClientRect(&rectSetting);
				bitmap_setting.CreateCompatibleBitmap(&dcSetting, rectSetting.Width(), rectSetting.Height());
				pOldBitmap_setting = memDC_setting.SelectObject(&bitmap_setting);
				memDC_setting.PatBlt(0, 0, rectSetting.Width(), rectSetting.Height(), BLACKNESS);

				DisplayDrawSetting(&memDC_setting, 1);

				dcSetting.BitBlt(0, 0, rectSetting.Width(), rectSetting.Height(), &memDC_setting, 0, 0, SRCCOPY);
				memDC_setting.SelectObject(pOldBitmap_setting);

				memDC_setting.DeleteDC();
				bitmap_setting.DeleteObject();
			}
		}

		// align 설정일 경우
		else if (dlgVisionSetting->SelectSetting == 2)
		{
			if (dlgVisionSetting->dlgSettingAlignMark->SelectCam == 1)
			{
				memDC_setting.CreateCompatibleDC(&dcSetting);
				dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING)->GetClientRect(&rectSetting);
				bitmap_setting.CreateCompatibleBitmap(&dcSetting, rectSetting.Width(), rectSetting.Height());
				pOldBitmap_setting = memDC_setting.SelectObject(&bitmap_setting);
				memDC_setting.PatBlt(0, 0, rectSetting.Width(), rectSetting.Height(), BLACKNESS);

				DisplayDrawSetting(&memDC_setting, 1);

				dcSetting.BitBlt(0, 0, rectSetting.Width(), rectSetting.Height(), &memDC_setting, 0, 0, SRCCOPY);
				memDC_setting.SelectObject(pOldBitmap_setting);

				memDC_setting.DeleteDC();
				bitmap_setting.DeleteObject();
			}
		}
	}

	DisplayDrawAlign(&memDC, 1);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);

	memDC.DeleteDC();
	bitmap.DeleteObject();

	if (dlgPopupManualAlign.ChkActive == true)
	{
		if (dlgPopupManualAlign.SelectCam == 1)
		{
			CClientDC dc_manual(dlgPopupManualAlign.GetDlgItem(IDC_PIC_MANUALALIGN));
			CDC memDC_manual;
			CBitmap* pOldBitmap_manual, bitmap_manual;
			CRect rect_manual;

			memDC_manual.CreateCompatibleDC(&dc_manual);
			dlgPopupManualAlign.GetDlgItem(IDC_PIC_MANUALALIGN)->GetClientRect(&rect_manual);
			bitmap_manual.CreateCompatibleBitmap(&dc_manual, rect_manual.Width(), rect_manual.Height());
			pOldBitmap_manual = memDC_manual.SelectObject(&bitmap_manual);
			memDC_manual.PatBlt(0, 0, rect_manual.Width(), rect_manual.Height(), BLACKNESS);

			DisplayDrawManualAlign(&memDC_manual, 1);

			dc_manual.BitBlt(0, 0, rect_manual.Width(), rect_manual.Height(), &memDC_manual, 0, 0, SRCCOPY);
			memDC_manual.SelectObject(pOldBitmap_manual);

			memDC_manual.DeleteDC();
			bitmap_manual.DeleteObject();
		}
	}
}


void CRVisionDlg::DisplayCam_2()
{
	CClientDC dc(dlgVisionAlign->dlgDrawAlign->GetDlgItem(IDC_PIC_ALIGN3));
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;
	CRect rect;

	CClientDC dcSetting(dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING));
	CDC memDC_setting;
	CBitmap* pOldBitmap_setting, bitmap_setting;
	CRect rectSetting;

	cBaumer->m_camera_set[2].m_updisplay = 0;

	memDC.CreateCompatibleDC(&dc);
	dlgVisionAlign->dlgDrawAlign->GetDlgItem(IDC_PIC_ALIGN3)->GetClientRect(&rect);
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), BLACKNESS);

	BYTE* Img_0;

	Img_0 = reinterpret_cast<BYTE*>(cBaumer->m_camera_set[2].m_buf);

	CamModify_3 = Mat(2048, 2448, CV_8UC1, Img_0);

	for (int i = 0; i < CamModify3; i += 2)
	{
		CamModify_3.at<char>(CamPoint_3[i].y, CamPoint_3[i].x) = CamModify_3.at<char>(CamModifyPoint_3[i].y, CamModifyPoint_3[i].x);
	}
	// setting dialog를 선택하였을 경우에만
	if (CHK_SETTING == true)
	{
		// camera 설정일 경우
		if (dlgVisionSetting->SelectSetting == 0)
		{
			if (dlgVisionSetting->dlgSettingCamera->SelectCam == 2)
			{
				memDC_setting.CreateCompatibleDC(&dcSetting);
				dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING)->GetClientRect(&rectSetting);
				bitmap_setting.CreateCompatibleBitmap(&dcSetting, rectSetting.Width(), rectSetting.Height());
				pOldBitmap_setting = memDC_setting.SelectObject(&bitmap_setting);
				memDC_setting.PatBlt(0, 0, rectSetting.Width(), rectSetting.Height(), BLACKNESS);

				DisplayDrawSetting(&memDC_setting, 2);

				dcSetting.BitBlt(0, 0, rectSetting.Width(), rectSetting.Height(), &memDC_setting, 0, 0, SRCCOPY);
				memDC_setting.SelectObject(pOldBitmap_setting);

				memDC_setting.DeleteDC();
				bitmap_setting.DeleteObject();
			}
		}

		// align 설정일 경우
		else if (dlgVisionSetting->SelectSetting == 1)
		{
			if (dlgVisionSetting->dlgSettingAlign->SelectCam == 2)
			{
				memDC_setting.CreateCompatibleDC(&dcSetting);
				dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING)->GetClientRect(&rectSetting);
				bitmap_setting.CreateCompatibleBitmap(&dcSetting, rectSetting.Width(), rectSetting.Height());
				pOldBitmap_setting = memDC_setting.SelectObject(&bitmap_setting);
				memDC_setting.PatBlt(0, 0, rectSetting.Width(), rectSetting.Height(), BLACKNESS);

				DisplayDrawSetting(&memDC_setting, 2);

				dcSetting.BitBlt(0, 0, rectSetting.Width(), rectSetting.Height(), &memDC_setting, 0, 0, SRCCOPY);
				memDC_setting.SelectObject(pOldBitmap_setting);

				memDC_setting.DeleteDC();
				bitmap_setting.DeleteObject();
			}
		}

		// align 설정일 경우
		else if (dlgVisionSetting->SelectSetting == 2)
		{
			if (dlgVisionSetting->dlgSettingAlignMark->SelectCam == 2)
			{
				memDC_setting.CreateCompatibleDC(&dcSetting);
				dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING)->GetClientRect(&rectSetting);
				bitmap_setting.CreateCompatibleBitmap(&dcSetting, rectSetting.Width(), rectSetting.Height());
				pOldBitmap_setting = memDC_setting.SelectObject(&bitmap_setting);
				memDC_setting.PatBlt(0, 0, rectSetting.Width(), rectSetting.Height(), BLACKNESS);

				DisplayDrawSetting(&memDC_setting, 2);

				dcSetting.BitBlt(0, 0, rectSetting.Width(), rectSetting.Height(), &memDC_setting, 0, 0, SRCCOPY);
				memDC_setting.SelectObject(pOldBitmap_setting);

				memDC_setting.DeleteDC();
				bitmap_setting.DeleteObject();
			}
		}
	}

	DisplayDrawAlign(&memDC, 2);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);

	memDC.DeleteDC();
	bitmap.DeleteObject();

	if (dlgPopupManualAlign.ChkActive == true)
	{
		if (dlgPopupManualAlign.SelectCam == 2)
		{
			CClientDC dc_manual(dlgPopupManualAlign.GetDlgItem(IDC_PIC_MANUALALIGN));
			CDC memDC_manual;
			CBitmap* pOldBitmap_manual, bitmap_manual;
			CRect rect_manual;

			memDC_manual.CreateCompatibleDC(&dc_manual);
			dlgPopupManualAlign.GetDlgItem(IDC_PIC_MANUALALIGN)->GetClientRect(&rect_manual);
			bitmap_manual.CreateCompatibleBitmap(&dc_manual, rect_manual.Width(), rect_manual.Height());
			pOldBitmap_manual = memDC_manual.SelectObject(&bitmap_manual);
			memDC_manual.PatBlt(0, 0, rect_manual.Width(), rect_manual.Height(), BLACKNESS);

			DisplayDrawManualAlign(&memDC_manual, 2);

			dc_manual.BitBlt(0, 0, rect_manual.Width(), rect_manual.Height(), &memDC_manual, 0, 0, SRCCOPY);
			memDC_manual.SelectObject(pOldBitmap_manual);

			memDC_manual.DeleteDC();
			bitmap_manual.DeleteObject();
		}
	}
}


void CRVisionDlg::DisplayCam_3()
{
	CClientDC dc(dlgVisionAlign->dlgDrawAlign->GetDlgItem(IDC_PIC_ALIGN4));
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;
	CRect rect;

	CClientDC dcSetting(dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING));
	CDC memDC_setting;
	CBitmap* pOldBitmap_setting, bitmap_setting;
	CRect rectSetting;

	cBaumer->m_camera_set[3].m_updisplay = 0;

	memDC.CreateCompatibleDC(&dc);
	dlgVisionAlign->dlgDrawAlign->GetDlgItem(IDC_PIC_ALIGN4)->GetClientRect(&rect);
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), BLACKNESS);

	BYTE* Img_0;

	Img_0 = reinterpret_cast<BYTE*>(cBaumer->m_camera_set[3].m_buf);

	CamModify_4 = Mat(2048, 2448, CV_8UC1, Img_0);

	for (int i = 0; i < CamModify4; i += 2)
	{
		CamModify_4.at<char>(CamPoint_4[i].y, CamPoint_4[i].x) = CamModify_4.at<char>(CamModifyPoint_4[i].y, CamModifyPoint_4[i].x);

	}
	// setting dialog를 선택하였을 경우에만
	if (CHK_SETTING == true)
	{
		// camera 설정일 경우
		if (dlgVisionSetting->SelectSetting == 0)
		{
			if (dlgVisionSetting->dlgSettingCamera->SelectCam == 3)
			{
				memDC_setting.CreateCompatibleDC(&dcSetting);
				dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING)->GetClientRect(&rectSetting);
				bitmap_setting.CreateCompatibleBitmap(&dcSetting, rectSetting.Width(), rectSetting.Height());
				pOldBitmap_setting = memDC_setting.SelectObject(&bitmap_setting);
				memDC_setting.PatBlt(0, 0, rectSetting.Width(), rectSetting.Height(), BLACKNESS);

				DisplayDrawSetting(&memDC_setting, 3);

				dcSetting.BitBlt(0, 0, rectSetting.Width(), rectSetting.Height(), &memDC_setting, 0, 0, SRCCOPY);
				memDC_setting.SelectObject(pOldBitmap_setting);

				memDC_setting.DeleteDC();
				bitmap_setting.DeleteObject();
			}
		}

		// align 설정일 경우
		else if (dlgVisionSetting->SelectSetting == 1)
		{
			if (dlgVisionSetting->dlgSettingAlign->SelectCam == 3)
			{
				memDC_setting.CreateCompatibleDC(&dcSetting);
				dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING)->GetClientRect(&rectSetting);
				bitmap_setting.CreateCompatibleBitmap(&dcSetting, rectSetting.Width(), rectSetting.Height());
				pOldBitmap_setting = memDC_setting.SelectObject(&bitmap_setting);
				memDC_setting.PatBlt(0, 0, rectSetting.Width(), rectSetting.Height(), BLACKNESS);

				DisplayDrawSetting(&memDC_setting, 3);

				dcSetting.BitBlt(0, 0, rectSetting.Width(), rectSetting.Height(), &memDC_setting, 0, 0, SRCCOPY);
				memDC_setting.SelectObject(pOldBitmap_setting);

				memDC_setting.DeleteDC();
				bitmap_setting.DeleteObject();
			}
		}

		// align 설정일 경우
		else if (dlgVisionSetting->SelectSetting == 2)
		{
			if (dlgVisionSetting->dlgSettingAlignMark->SelectCam == 3)
			{
				memDC_setting.CreateCompatibleDC(&dcSetting);
				dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING)->GetClientRect(&rectSetting);
				bitmap_setting.CreateCompatibleBitmap(&dcSetting, rectSetting.Width(), rectSetting.Height());
				pOldBitmap_setting = memDC_setting.SelectObject(&bitmap_setting);
				memDC_setting.PatBlt(0, 0, rectSetting.Width(), rectSetting.Height(), BLACKNESS);

				DisplayDrawSetting(&memDC_setting, 3);

				dcSetting.BitBlt(0, 0, rectSetting.Width(), rectSetting.Height(), &memDC_setting, 0, 0, SRCCOPY);
				memDC_setting.SelectObject(pOldBitmap_setting);

				memDC_setting.DeleteDC();
				bitmap_setting.DeleteObject();
			}
		}
	}

	DisplayDrawAlign(&memDC, 3);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);

	memDC.DeleteDC();
	bitmap.DeleteObject();

	if (dlgPopupManualAlign.ChkActive == true)
	{
		if (dlgPopupManualAlign.SelectCam == 3)
		{
			CClientDC dc_manual(dlgPopupManualAlign.GetDlgItem(IDC_PIC_MANUALALIGN));
			CDC memDC_manual;
			CBitmap* pOldBitmap_manual, bitmap_manual;
			CRect rect_manual;

			memDC_manual.CreateCompatibleDC(&dc_manual);
			dlgPopupManualAlign.GetDlgItem(IDC_PIC_MANUALALIGN)->GetClientRect(&rect_manual);
			bitmap_manual.CreateCompatibleBitmap(&dc_manual, rect_manual.Width(), rect_manual.Height());
			pOldBitmap_manual = memDC_manual.SelectObject(&bitmap_manual);
			memDC_manual.PatBlt(0, 0, rect_manual.Width(), rect_manual.Height(), BLACKNESS);

			DisplayDrawManualAlign(&memDC_manual, 3);

			dc_manual.BitBlt(0, 0, rect_manual.Width(), rect_manual.Height(), &memDC_manual, 0, 0, SRCCOPY);
			memDC_manual.SelectObject(pOldBitmap_manual);

			memDC_manual.DeleteDC();
			bitmap_manual.DeleteObject();
		}
	}
}


void CRVisionDlg::DisplayCam_4()
{
	CClientDC dcReview(dlgVisionReview->dlgDrawReview->GetDlgItem(IDC_PIC_REVIEW));
	CDC memDC_review;
	CBitmap* pOldBitmap_review, bitmap_review;
	CRect rectReview;

	CClientDC dcNavigator(dlgVisionReview->GetDlgItem(IDC_PIC_NAVIGATOR));
	CDC memDC_navigator;
	CBitmap* pOldBitmap_navigator, bitmap_navigator;
	CRect rectNavigator;

	CClientDC dcFC(dlgVisionFC->dlgDrawFC->GetDlgItem(IDC_PIC_FC));
	CDC memDC_fc;
	CBitmap* pOldBitmap_fc, bitmap_fc;
	CRect rectFC;

	CClientDC dcSetting(dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING));
	CDC memDC_setting;
	CBitmap* pOldBitmap_setting, bitmap_setting;
	CRect rectSetting;

	cBaumer->m_camera_set[4].m_updisplay = 0;

	// setting dialog를 선택하였을 경우에만
	if (CHK_SETTING == true)
	{
		// camera 설정일 경우
		if (dlgVisionSetting->SelectSetting == 0)
		{
			if (dlgVisionSetting->dlgSettingCamera->SelectCam == 4)
			{
				memDC_setting.CreateCompatibleDC(&dcSetting);
				dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING)->GetClientRect(&rectSetting);
				bitmap_setting.CreateCompatibleBitmap(&dcSetting, rectSetting.Width(), rectSetting.Height());
				pOldBitmap_setting = memDC_setting.SelectObject(&bitmap_setting);
				memDC_setting.PatBlt(0, 0, rectSetting.Width(), rectSetting.Height(), BLACKNESS);

				DisplayDrawSetting(&memDC_setting, 4);

				dcSetting.BitBlt(0, 0, rectSetting.Width(), rectSetting.Height(), &memDC_setting, 0, 0, SRCCOPY);
				memDC_setting.SelectObject(pOldBitmap_setting);

				memDC_setting.DeleteDC();
				bitmap_setting.DeleteObject();
			}
		}

		else if (dlgVisionSetting->SelectSetting == 3)
		{
			memDC_setting.CreateCompatibleDC(&dcSetting);
			dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING)->GetClientRect(&rectSetting);
			bitmap_setting.CreateCompatibleBitmap(&dcSetting, rectSetting.Width(), rectSetting.Height());
			pOldBitmap_setting = memDC_setting.SelectObject(&bitmap_setting);
			memDC_setting.PatBlt(0, 0, rectSetting.Width(), rectSetting.Height(), BLACKNESS);

			DisplayDrawSetting(&memDC_setting, 4);

			dcSetting.BitBlt(0, 0, rectSetting.Width(), rectSetting.Height(), &memDC_setting, 0, 0, SRCCOPY);
			memDC_setting.SelectObject(pOldBitmap_setting);

			memDC_setting.DeleteDC();
			bitmap_setting.DeleteObject();
		}

		else if (dlgVisionSetting->SelectSetting == 4)
		{
			memDC_setting.CreateCompatibleDC(&dcSetting);
			dlgVisionSetting->GetDlgItem(IDC_PIC_SETTING)->GetClientRect(&rectSetting);
			bitmap_setting.CreateCompatibleBitmap(&dcSetting, rectSetting.Width(), rectSetting.Height());
			pOldBitmap_setting = memDC_setting.SelectObject(&bitmap_setting);
			memDC_setting.PatBlt(0, 0, rectSetting.Width(), rectSetting.Height(), BLACKNESS);

			DisplayDrawSetting(&memDC_setting, 4);

			dcSetting.BitBlt(0, 0, rectSetting.Width(), rectSetting.Height(), &memDC_setting, 0, 0, SRCCOPY);
			memDC_setting.SelectObject(pOldBitmap_setting);

			memDC_setting.DeleteDC();
			bitmap_setting.DeleteObject();
		}

	}

	memDC_review.CreateCompatibleDC(&dcReview);
	dlgVisionReview->dlgDrawReview->GetDlgItem(IDC_PIC_REVIEW)->GetClientRect(&rectReview);
	bitmap_review.CreateCompatibleBitmap(&dcReview, rectReview.Width(), rectReview.Height());
	pOldBitmap_review = memDC_review.SelectObject(&bitmap_review);
	memDC_review.PatBlt(0, 0, rectReview.Width(), rectReview.Height(), BLACKNESS);

	memDC_navigator.CreateCompatibleDC(&dcNavigator);
	dlgVisionReview->GetDlgItem(IDC_PIC_NAVIGATOR)->GetClientRect(&rectNavigator);
	bitmap_navigator.CreateCompatibleBitmap(&dcNavigator, rectNavigator.Width(), rectNavigator.Height());
	pOldBitmap_navigator = memDC_navigator.SelectObject(&bitmap_navigator);
	memDC_navigator.PatBlt(0, 0, rectNavigator.Width(), rectNavigator.Height(), BLACKNESS);

	memDC_fc.CreateCompatibleDC(&dcFC);
	dlgVisionFC->dlgDrawFC->GetDlgItem(IDC_PIC_FC)->GetClientRect(&rectFC);
	bitmap_fc.CreateCompatibleBitmap(&dcFC, rectFC.Width(), rectFC.Height());
	pOldBitmap_fc = memDC_fc.SelectObject(&bitmap_fc);
	memDC_fc.PatBlt(0, 0, rectFC.Width(), rectFC.Height(), BLACKNESS);

	DisplayDrawReview(&memDC_review);
	DisplayDrawNavigator(&memDC_navigator);
	DisplayDrawFC(&memDC_fc);

	dcReview.BitBlt(0, 0, rectReview.Width(), rectReview.Height(), &memDC_review, 0, 0, SRCCOPY);
	memDC_review.SelectObject(pOldBitmap_review);

	dcNavigator.BitBlt(0, 0, rectNavigator.Width(), rectNavigator.Height(), &memDC_navigator, 0, 0, SRCCOPY);
	memDC_navigator.SelectObject(pOldBitmap_navigator);

	dcFC.BitBlt(0, 0, rectFC.Width(), rectFC.Height(), &memDC_fc, 0, 0, SRCCOPY);
	memDC_fc.SelectObject(pOldBitmap_fc);

	memDC_review.DeleteDC();
	bitmap_review.DeleteObject();

	memDC_navigator.DeleteDC();
	bitmap_navigator.DeleteObject();

	memDC_fc.DeleteDC();
	bitmap_fc.DeleteObject();
}


void BGAPI2CALL BufferHandler1(void* callBackOwner, Buffer* pBufferFilled)
{
	if (pBufferFilled == NULL)
	{

	}
	else if (pBufferFilled->GetIsIncomplete() == true)
	{

		pBufferFilled->QueueBuffer();
	}
	else if (pBufferFilled->GetIsIncomplete() == false)
	{
		g_pDialog->cBaumer->m_camera_set[0].m_buf = pBufferFilled->GetMemPtr();
		g_pDialog->cBaumer->m_camera_set[0].m_updisplay = 1;
		g_pDialog->Invalidate(FALSE);
		pBufferFilled->QueueBuffer();
	}
	return;
}

void BGAPI2CALL BufferHandler2(void* callBackOwner, Buffer* pBufferFilled)
{
	if (pBufferFilled == NULL)
	{

	}
	else if (pBufferFilled->GetIsIncomplete() == true)
	{

		pBufferFilled->QueueBuffer();
	}
	else if (pBufferFilled->GetIsIncomplete() == false)
	{
		g_pDialog->cBaumer->m_camera_set[1].m_buf = pBufferFilled->GetMemPtr();
		g_pDialog->cBaumer->m_camera_set[1].m_updisplay = 1;
		g_pDialog->Invalidate(FALSE);
		pBufferFilled->QueueBuffer();
	}
	return;
}

void BGAPI2CALL BufferHandler3(void* callBackOwner, Buffer* pBufferFilled)
{
	if (pBufferFilled == NULL)
	{

	}
	else if (pBufferFilled->GetIsIncomplete() == true)
	{

		pBufferFilled->QueueBuffer();
	}
	else if (pBufferFilled->GetIsIncomplete() == false)
	{
		g_pDialog->cBaumer->m_camera_set[2].m_buf = pBufferFilled->GetMemPtr();
		g_pDialog->cBaumer->m_camera_set[2].m_updisplay = 1;
		g_pDialog->Invalidate(FALSE);
		pBufferFilled->QueueBuffer();
	}
	return;
}

void BGAPI2CALL BufferHandler4(void* callBackOwner, Buffer* pBufferFilled)
{
	if (pBufferFilled == NULL)
	{

	}
	else if (pBufferFilled->GetIsIncomplete() == true)
	{

		pBufferFilled->QueueBuffer();
	}
	else if (pBufferFilled->GetIsIncomplete() == false)
	{
		g_pDialog->cBaumer->m_camera_set[3].m_buf = pBufferFilled->GetMemPtr();
		g_pDialog->cBaumer->m_camera_set[3].m_updisplay = 1;
		g_pDialog->Invalidate(FALSE);
		pBufferFilled->QueueBuffer();
	}
	return;
}

void BGAPI2CALL BufferHandler5(void* callBackOwner, Buffer* pBufferFilled)
{
	if (pBufferFilled == NULL)
	{

	}
	else if (pBufferFilled->GetIsIncomplete() == true)
	{
		pBufferFilled->QueueBuffer();
	}
	else if (pBufferFilled->GetIsIncomplete() == false)
	{
		g_pDialog->cBaumer->m_camera_set[4].m_buf = pBufferFilled->GetMemPtr();
		g_pDialog->cBaumer->m_camera_set[4].m_updisplay = 1;
		g_pDialog->Invalidate(FALSE);
		pBufferFilled->QueueBuffer();
	}
	return;
}


void CRVisionDlg::DisplayDrawAlign(CDC* pDC, int nCase)
{
	pDC->SetStretchBltMode(COLORONCOLOR);
	HDC hDC = pDC->GetSafeHdc();

	cBaumer->m_camera_set[nCase].m_pBitmapInfo->bmiHeader.biWidth = cBaumer->m_camera_set[nCase].m_SizeX;
	cBaumer->m_camera_set[nCase].m_pBitmapInfo->bmiHeader.biHeight = -cBaumer->m_camera_set[nCase].m_SizeY;

	int nSrcX = 0;
	int nSrcY = 0;
	int nSrcW = cBaumer->m_camera_set[nCase].m_SizeX;
	int nSrcH = cBaumer->m_camera_set[nCase].m_SizeY;

	int nRatio = 8;

	int nDstX = 0;
	int nDstY = 0;
	int nDstW = nSrcW / nRatio;
	int nDstH = nSrcH / nRatio;


	StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH,
		cBaumer->m_camera_set[nCase].m_buf, cBaumer->m_camera_set[nCase].m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

	if (nCase == 0)
	{
		StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH,
			CamModify_1.data, cBaumer->m_camera_set[nCase].m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	}

	else if (nCase == 1)
	{
		StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH,
			CamModify_2.data, cBaumer->m_camera_set[nCase].m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	}

	else if (nCase == 2)
	{
		StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH,
			CamModify_3.data, cBaumer->m_camera_set[nCase].m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	}

	else if (nCase == 3)
	{
		StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH,
			CamModify_4.data, cBaumer->m_camera_set[nCase].m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	}

	/*else
	{
		StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH,
			cBaumer->m_camera_set[nCase].m_buf, cBaumer->m_camera_set[nCase].m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	}*/


	pDC->SelectStockObject(NULL_BRUSH);

	if (CHK_NAME == true)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(GetRValue(cNameColor), GetGValue(cNameColor), GetBValue(cNameColor)));

		pDC->TextOutW(nDstW - 60, 0, stCamera.strName[nCase]);
	}

	if (CHK_CROSSLINE == true)
	{
		cPenCrossline.DeleteObject();
		cPenCrossline.CreatePen(PS_SOLID, 1, RGB(GetRValue(cCrossLineColor), GetGValue(cCrossLineColor), GetBValue(cCrossLineColor)));

		pDC->SelectObject(&cPenCrossline);

		pDC->MoveTo(nDstW / 2, 0);
		pDC->LineTo(nDstW / 2, nDstH);

		pDC->MoveTo(0, nDstH / 2);
		pDC->LineTo(nDstW, nDstH / 2);
	}

	if (CHK_ROI == true)
	{
		cPenROI.DeleteObject();
		cPenROI.CreatePen(PS_SOLID, 1, RGB(GetRValue(cROIColor), GetGValue(cROIColor), GetBValue(cROIColor)));

		pDC->SelectObject(&cPenROI);

		pDC->Rectangle(stAlign.ROIStart[nCase].x / 8, stAlign.ROIStart[nCase].y / 8,
			stAlign.ROIEnd[nCase].x / 8, stAlign.ROIEnd[nCase].y / 8);
	}

	if (stEdgeAlign.ChkFind[nCase] == true && stMarkAlign.nChkFindMark[nCase] == 0)
	{
		if (stEdgeAlign.ChkMistake[nCase] == true)
			pDC->SelectObject(&pen_green);

		else if (stEdgeAlign.ChkMistake[nCase] == false)
			pDC->SelectObject(&pen_red);

		pDC->MoveTo(stEdgeAlign.EdgeStart[nCase].x / 8, stEdgeAlign.EdgeStart[nCase].y / 8);
		pDC->LineTo(stEdgeAlign.EdgeEnd[nCase].x / 8, stEdgeAlign.EdgeEnd[nCase].y / 8);
	}

	if (stEdgeAlign.ChkFind[nCase] == false && stMarkAlign.nChkFindMark[nCase] == 1)
	{
		pDC->SelectObject(&pen_green);

		if (bJigProcess == false)
		{
			pDC->Rectangle(stMarkAlign.MarkStart[nCase].x / 8, stMarkAlign.MarkStart[nCase].y / 8, stMarkAlign.MarkEnd[nCase].x / 8, stMarkAlign.MarkEnd[nCase].y / 8);

			pDC->MoveTo((stMarkAlign.MarkStart[nCase].x + (MarkImageAlign.cols / 2)) / 8, (stMarkAlign.MarkStart[nCase].y + (MarkImageAlign.rows / 2)) / 8 - 5);
			pDC->LineTo((stMarkAlign.MarkStart[nCase].x + (MarkImageAlign.cols / 2)) / 8, (stMarkAlign.MarkStart[nCase].y + (MarkImageAlign.rows / 2)) / 8 + 5);

			pDC->MoveTo((stMarkAlign.MarkStart[nCase].x + (MarkImageAlign.cols / 2)) / 8 - 5, (stMarkAlign.MarkStart[nCase].y + (MarkImageAlign.rows / 2)) / 8);
			pDC->LineTo((stMarkAlign.MarkStart[nCase].x + (MarkImageAlign.cols / 2)) / 8 + 5, (stMarkAlign.MarkStart[nCase].y + (MarkImageAlign.rows / 2)) / 8);
		}

		else if (bJigProcess == true)
		{
			pDC->MoveTo(0, stMarkAlign.MarkStart[nCase].y / 8);
			pDC->LineTo(stMarkAlign.MarkStart[nCase].x / 8 - 10, stMarkAlign.MarkStart[nCase].y / 8);

			pDC->MoveTo(stMarkAlign.MarkStart[nCase].x / 8 - 5, stMarkAlign.MarkStart[nCase].y / 8);
			pDC->LineTo(stMarkAlign.MarkStart[nCase].x / 8 + 5, stMarkAlign.MarkStart[nCase].y / 8);

			pDC->MoveTo(stMarkAlign.MarkStart[nCase].x / 8 + 10, stMarkAlign.MarkStart[nCase].y / 8);
			pDC->LineTo(CamWidth / 8, stMarkAlign.MarkStart[nCase].y / 8);

			pDC->MoveTo(stMarkAlign.MarkStart[nCase].x / 8, 0);
			pDC->LineTo(stMarkAlign.MarkStart[nCase].x / 8, stMarkAlign.MarkStart[nCase].y / 8 - 10);

			pDC->MoveTo(stMarkAlign.MarkStart[nCase].x / 8, stMarkAlign.MarkStart[nCase].y / 8 - 5);
			pDC->LineTo(stMarkAlign.MarkStart[nCase].x / 8, stMarkAlign.MarkStart[nCase].y / 8 + 5);

			pDC->MoveTo(stMarkAlign.MarkStart[nCase].x / 8, stMarkAlign.MarkStart[nCase].y / 8 + 10);
			pDC->LineTo(stMarkAlign.MarkStart[nCase].x / 8, CamHeight / 8);
		}
	}

	else if (stEdgeAlign.ChkFind[nCase] == false && stMarkAlign.nChkFindMark[nCase] == 2)
	{
		pDC->SelectObject(&pen_red);

		if (bJigProcess == false)
		{
			pDC->Rectangle(stMarkAlign.MarkStart[nCase].x / 8, stMarkAlign.MarkStart[nCase].y / 8, stMarkAlign.MarkEnd[nCase].x / 8, stMarkAlign.MarkEnd[nCase].y / 8);

			pDC->MoveTo((stMarkAlign.MarkStart[nCase].x + (MarkImageAlign.cols / 2)) / 8, (stMarkAlign.MarkStart[nCase].y + (MarkImageAlign.rows / 2)) / 8 - 5);
			pDC->LineTo((stMarkAlign.MarkStart[nCase].x + (MarkImageAlign.cols / 2)) / 8, (stMarkAlign.MarkStart[nCase].y + (MarkImageAlign.rows / 2)) / 8 + 5);

			pDC->MoveTo((stMarkAlign.MarkStart[nCase].x + (MarkImageAlign.cols / 2)) / 8 - 5, (stMarkAlign.MarkStart[nCase].y + (MarkImageAlign.rows / 2)) / 8);
			pDC->LineTo((stMarkAlign.MarkStart[nCase].x + (MarkImageAlign.cols / 2)) / 8 + 5, (stMarkAlign.MarkStart[nCase].y + (MarkImageAlign.rows / 2)) / 8);
		}

		else if (bJigProcess == true)
		{
			pDC->MoveTo(stMarkAlign.MarkStart[nCase].x / 8, stMarkAlign.MarkStart[nCase].y / 8 - 5);
			pDC->LineTo(stMarkAlign.MarkStart[nCase].x / 8, stMarkAlign.MarkStart[nCase].y / 8 + 5);

			pDC->MoveTo(stMarkAlign.MarkStart[nCase].x / 8 - 5, stMarkAlign.MarkStart[nCase].y / 8);
			pDC->LineTo(stMarkAlign.MarkStart[nCase].x / 8 + 5, stMarkAlign.MarkStart[nCase].y / 8);
		}
	}

	pDC->SelectObject(&pen_white);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(0, 0, 2448, 2048);
}


void CRVisionDlg::DisplayDrawManualAlign(CDC* pDC, int nCase)
{
	pDC->SetStretchBltMode(COLORONCOLOR);
	HDC hDC = pDC->GetSafeHdc();

	cBaumer->m_camera_set[nCase].m_pBitmapInfo->bmiHeader.biWidth = cBaumer->m_camera_set[nCase].m_SizeX;
	cBaumer->m_camera_set[nCase].m_pBitmapInfo->bmiHeader.biHeight = -cBaumer->m_camera_set[nCase].m_SizeY;

	int nSrcX = 0;
	int nSrcY = 0;
	int nSrcW = cBaumer->m_camera_set[nCase].m_SizeX;
	int nSrcH = cBaumer->m_camera_set[nCase].m_SizeY;

	int nRatio = dlgPopupManualAlign.dlgDrawManualAlign->magni;

	int nDstX = 0;
	int nDstY = 0;
	int nDstW = nSrcW / nRatio;
	int nDstH = nSrcH / nRatio;

	StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH,
		cBaumer->m_camera_set[nCase].m_buf, cBaumer->m_camera_set[nCase].m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

	pDC->SelectStockObject(NULL_BRUSH);

	if (dlgPopupManualAlign.nCase == 0)
	{
		if (dlgPopupManualAlign.ChkClick == true)
		{
			CPoint nEdgeStart;
			CPoint nEdgeEnd;

			nEdgeStart.x = dlgPopupManualAlign.ManualFirstPoint.x;
			nEdgeStart.y = dlgPopupManualAlign.ManualFirstPoint.y;
			nEdgeEnd.x = dlgPopupManualAlign.ManualSecondPoint.x;
			nEdgeEnd.y = dlgPopupManualAlign.ManualSecondPoint.y;

			pDC->SelectObject(&pen_red);
			pDC->MoveTo(nEdgeStart.x, nEdgeStart.y);
			pDC->LineTo(nEdgeEnd.x, nEdgeEnd.y);

		}

		pDC->SelectObject(&pen_green);

		pDC->MoveTo(stEdgeAlign.EdgeStart[nCase].x / 4, stEdgeAlign.EdgeStart[nCase].y / 4);
		pDC->LineTo(stEdgeAlign.EdgeEnd[nCase].x / 4, stEdgeAlign.EdgeEnd[nCase].y / 4);
	}

	else if (dlgPopupManualAlign.nCase == 1)
	{
		if (dlgPopupManualAlign.ChkClick == true)
		{
			pDC->SelectObject(&pen_red);

			if (bJigProcess == false)
			{
				// 사각형
				pDC->Rectangle(dlgPopupManualAlign.ManualMarkPoint.x - (MarkImageAlign.cols / 8), dlgPopupManualAlign.ManualMarkPoint.y - (MarkImageAlign.rows / 8),
					dlgPopupManualAlign.ManualMarkPoint.x + (MarkImageAlign.cols / 8), dlgPopupManualAlign.ManualMarkPoint.y + (MarkImageAlign.rows / 8));

				// center line
				pDC->MoveTo(dlgPopupManualAlign.ManualMarkPoint.x, dlgPopupManualAlign.ManualMarkPoint.y - 5);
				pDC->LineTo(dlgPopupManualAlign.ManualMarkPoint.x, dlgPopupManualAlign.ManualMarkPoint.y + 5);

				pDC->MoveTo(dlgPopupManualAlign.ManualMarkPoint.x - 5, dlgPopupManualAlign.ManualMarkPoint.y);
				pDC->LineTo(dlgPopupManualAlign.ManualMarkPoint.x + 5, dlgPopupManualAlign.ManualMarkPoint.y);
			}

			else if (bJigProcess == true)
			{
				pDC->MoveTo(dlgPopupManualAlign.ManualMarkPoint.x, 0);
				pDC->LineTo(dlgPopupManualAlign.ManualMarkPoint.x, dlgPopupManualAlign.ManualMarkPoint.y - 10);

				pDC->MoveTo(dlgPopupManualAlign.ManualMarkPoint.x, dlgPopupManualAlign.ManualMarkPoint.y - 5);
				pDC->LineTo(dlgPopupManualAlign.ManualMarkPoint.x, dlgPopupManualAlign.ManualMarkPoint.y + 5);

				pDC->MoveTo(dlgPopupManualAlign.ManualMarkPoint.x, dlgPopupManualAlign.ManualMarkPoint.y + 10);
				pDC->LineTo(dlgPopupManualAlign.ManualMarkPoint.x, 2448);

				pDC->MoveTo(0, dlgPopupManualAlign.ManualMarkPoint.y);
				pDC->LineTo(dlgPopupManualAlign.ManualMarkPoint.x - 10, dlgPopupManualAlign.ManualMarkPoint.y);

				pDC->MoveTo(dlgPopupManualAlign.ManualMarkPoint.x - 5, dlgPopupManualAlign.ManualMarkPoint.y);
				pDC->LineTo(dlgPopupManualAlign.ManualMarkPoint.x + 5, dlgPopupManualAlign.ManualMarkPoint.y);

				pDC->MoveTo(dlgPopupManualAlign.ManualMarkPoint.x + 10, dlgPopupManualAlign.ManualMarkPoint.y);
				pDC->LineTo(2448, dlgPopupManualAlign.ManualMarkPoint.y);
			}
		}

		pDC->SelectObject(&pen_green);

		if (bJigProcess == false)
		{
			pDC->Rectangle(stMarkAlign.MarkStart[nCase].x / 4, stMarkAlign.MarkStart[nCase].y / 4, stMarkAlign.MarkEnd[nCase].x / 4, stMarkAlign.MarkEnd[nCase].y / 4);

			// center line
			pDC->MoveTo(stMarkAlign.MarkStart[nCase].x / 4 + MarkImageAlign.cols / 8 - 5, stMarkAlign.MarkStart[nCase].y / 4 + MarkImageAlign.rows / 8);
			pDC->LineTo(stMarkAlign.MarkStart[nCase].x / 4 + MarkImageAlign.cols / 8 + 5, stMarkAlign.MarkStart[nCase].y / 4 + MarkImageAlign.rows / 8);

			pDC->MoveTo(stMarkAlign.MarkStart[nCase].x / 4 + MarkImageAlign.cols / 8, stMarkAlign.MarkStart[nCase].y / 4 + MarkImageAlign.rows / 8 - 5);
			pDC->LineTo(stMarkAlign.MarkStart[nCase].x / 4 + MarkImageAlign.cols / 8, stMarkAlign.MarkStart[nCase].y / 4 + MarkImageAlign.rows / 8 + 5);
		}

		else if (bJigProcess == true)
		{
			pDC->MoveTo(stMarkAlign.MarkStart[nCase].x / 4, 0);
			pDC->LineTo(stMarkAlign.MarkStart[nCase].x / 4, stMarkAlign.MarkStart[nCase].y / 4 - 10);

			pDC->MoveTo(stMarkAlign.MarkStart[nCase].x / 4, stMarkAlign.MarkStart[nCase].y / 4 - 5);
			pDC->LineTo(stMarkAlign.MarkStart[nCase].x / 4, stMarkAlign.MarkStart[nCase].y / 4 + 5);

			pDC->MoveTo(stMarkAlign.MarkStart[nCase].x / 4, stMarkAlign.MarkStart[nCase].y / 4 + 10);
			pDC->LineTo(stMarkAlign.MarkStart[nCase].x / 4, 2048 / 4);

			pDC->MoveTo(0, stMarkAlign.MarkStart[nCase].y / 4);
			pDC->LineTo(stMarkAlign.MarkStart[nCase].x / 4 - 10, stMarkAlign.MarkStart[nCase].y / 4);

			pDC->MoveTo(stMarkAlign.MarkStart[nCase].x / 4 - 5, stMarkAlign.MarkStart[nCase].y / 4);
			pDC->LineTo(stMarkAlign.MarkStart[nCase].x / 4 + 5, stMarkAlign.MarkStart[nCase].y / 4);

			pDC->MoveTo(stMarkAlign.MarkStart[nCase].x / 4 + 10, stMarkAlign.MarkStart[nCase].y / 4);
			pDC->LineTo(2448 / 4, stMarkAlign.MarkStart[nCase].y / 4);
		}
	}
}


void CRVisionDlg::DisplayDrawReview(CDC* pDC)
{
	pDC->SetStretchBltMode(COLORONCOLOR);
	HDC hDC = pDC->GetSafeHdc();

	cBaumer->m_camera_set[4].m_pBitmapInfo->bmiHeader.biWidth = cBaumer->m_camera_set[4].m_SizeX;
	cBaumer->m_camera_set[4].m_pBitmapInfo->bmiHeader.biHeight = -cBaumer->m_camera_set[4].m_SizeY;

	int nSrcX = 0;
	int nSrcY = 0;
	int nSrcW = cBaumer->m_camera_set[4].m_SizeX;
	int nSrcH = cBaumer->m_camera_set[4].m_SizeY;

	// align 이미지
	int nRatio = dlgVisionReview->dlgDrawReview->magni;

	int nDstX = 0;
	int nDstY = 0;
	int nDstW = nSrcW / nRatio;
	int nDstH = nSrcH / nRatio;

	StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH,
		cBaumer->m_camera_set[4].m_buf, cBaumer->m_camera_set[4].m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

	pDC->SelectStockObject(NULL_BRUSH);

	if (dlgVisionReview->m_chk_scale.GetCheck() == 1)
	{
		pDC->SelectObject(&pen_white);

		pDC->MoveTo(536 + dlgVisionReview->dlgDrawReview->mouse_scroll_x, 485 + dlgVisionReview->dlgDrawReview->mouse_scroll_y);
		pDC->LineTo(536 + dlgVisionReview->dlgDrawReview->mouse_scroll_x, 495 + dlgVisionReview->dlgDrawReview->mouse_scroll_y);

		pDC->MoveTo(536 + dlgVisionReview->dlgDrawReview->mouse_scroll_x, 490 + dlgVisionReview->dlgDrawReview->mouse_scroll_y);
		pDC->LineTo(594 + dlgVisionReview->dlgDrawReview->mouse_scroll_x, 490 + dlgVisionReview->dlgDrawReview->mouse_scroll_y);

		pDC->MoveTo(594 + dlgVisionReview->dlgDrawReview->mouse_scroll_x, 485 + dlgVisionReview->dlgDrawReview->mouse_scroll_y);
		pDC->LineTo(594 + dlgVisionReview->dlgDrawReview->mouse_scroll_x, 495 + dlgVisionReview->dlgDrawReview->mouse_scroll_y);

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));

		pDC->SelectObject(&fontScale);

		CString strScale;
		strScale.Format(_T("%.3fmm"), (double)dlgVisionReview->dlgDrawReview->magni * 50 / 1000);

		pDC->TextOutW(540 + dlgVisionReview->dlgDrawReview->mouse_scroll_x, 470 + dlgVisionReview->dlgDrawReview->mouse_scroll_y, strScale);
	}

	if (CHK_CROSSLINE == true)
	{
		cPenCrossline.DeleteObject();
		cPenCrossline.CreatePen(PS_SOLID, 1, RGB(GetRValue(cCrossLineColor), GetGValue(cCrossLineColor), GetBValue(cCrossLineColor)));

		pDC->SelectObject(&cPenCrossline);

		pDC->MoveTo(nDstW / 2, 0);
		pDC->LineTo(nDstW / 2, nDstH);

		pDC->MoveTo(0, nDstH / 2);
		pDC->LineTo(nDstW, nDstH / 2);
	}

	for (int i = 0; i < 10; i++)
	{
		CString strValue;
		strValue.Format(_T("%d"), i + 1);

		if (stMeasure.ChkMeasurement[i] == true)
		{
			// line
			if (stMeasure.CaseMeasurement[i] == 1)
			{
				pDC->SelectObject(&pen_red);

				if (dlgVisionReview->dlgDrawReview->magni == 1)
				{
					pDC->MoveTo(stMeasure.FirstPoint[i].x, stMeasure.FirstPoint[i].y);
					pDC->LineTo(stMeasure.SecondPoint[i].x, stMeasure.SecondPoint[i].y);
					pDC->TextOutW(stMeasure.FirstPoint[i].x, stMeasure.FirstPoint[i].y, strValue);
				}

				else if (dlgVisionReview->dlgDrawReview->magni == 2)
				{
					pDC->MoveTo(stMeasure.FirstPoint[i].x / 2, stMeasure.FirstPoint[i].y / 2);
					pDC->LineTo(stMeasure.SecondPoint[i].x / 2, stMeasure.SecondPoint[i].y / 2);
					pDC->TextOutW(stMeasure.FirstPoint[i].x / 2, stMeasure.FirstPoint[i].y / 2, strValue);
				}

				else if (dlgVisionReview->dlgDrawReview->magni == 4)
				{
					pDC->MoveTo(stMeasure.FirstPoint[i].x / 4, stMeasure.FirstPoint[i].y / 4);
					pDC->LineTo(stMeasure.SecondPoint[i].x / 4, stMeasure.SecondPoint[i].y / 4);
					pDC->TextOutW(stMeasure.FirstPoint[i].x / 4, stMeasure.FirstPoint[i].y / 4, strValue);
				}
			}

			// rectangle
			else if (stMeasure.CaseMeasurement[i] == 2)
			{
				pDC->SelectObject(&pen_red);

				if (dlgVisionReview->dlgDrawReview->magni == 1)
				{
					pDC->Rectangle(stMeasure.FirstPoint[i].x, stMeasure.FirstPoint[i].y, stMeasure.SecondPoint[i].x, stMeasure.SecondPoint[i].y);
					pDC->TextOutW(stMeasure.FirstPoint[i].x, stMeasure.FirstPoint[i].y, strValue);
				}

				else if (dlgVisionReview->dlgDrawReview->magni == 2)
				{
					pDC->Rectangle(stMeasure.FirstPoint[i].x / 2, stMeasure.FirstPoint[i].y / 2, stMeasure.SecondPoint[i].x / 2, stMeasure.SecondPoint[i].y / 2);
					pDC->TextOutW(stMeasure.FirstPoint[i].x / 2, stMeasure.FirstPoint[i].y / 2, strValue);
				}

				else if (dlgVisionReview->dlgDrawReview->magni == 4)
				{
					pDC->Rectangle(stMeasure.FirstPoint[i].x / 4, stMeasure.FirstPoint[i].y / 4, stMeasure.SecondPoint[i].x / 4, stMeasure.SecondPoint[i].y / 4);
					pDC->TextOutW(stMeasure.FirstPoint[i].x / 4, stMeasure.FirstPoint[i].y / 4, strValue);
				}
			}

			// angle
			else if (stMeasure.CaseMeasurement[i] == 3)
			{
				pDC->SelectObject(&pen_red);

				if (dlgVisionReview->dlgDrawReview->magni == 1)
				{
					pDC->MoveTo(stMeasure.FirstPoint[i]);
					pDC->LineTo(stMeasure.SecondPoint[i]);
					pDC->MoveTo(stMeasure.SecondPoint[i]);
					pDC->LineTo(stMeasure.ThirdPoint[i]);
					pDC->TextOutW(stMeasure.FirstPoint[i].x, stMeasure.FirstPoint[i].y, strValue);
				}

				else if (dlgVisionReview->dlgDrawReview->magni == 2)
				{
					pDC->MoveTo(stMeasure.FirstPoint[i].x / 2, stMeasure.FirstPoint[i].y / 2);
					pDC->LineTo(stMeasure.SecondPoint[i].x / 2, stMeasure.SecondPoint[i].y / 2);
					pDC->MoveTo(stMeasure.SecondPoint[i].x / 2, stMeasure.SecondPoint[i].y / 2);
					pDC->LineTo(stMeasure.ThirdPoint[i].x / 2, stMeasure.ThirdPoint[i].y / 2);
					pDC->TextOutW(stMeasure.FirstPoint[i].x / 2, stMeasure.FirstPoint[i].y / 2, strValue);
				}

				else if (dlgVisionReview->dlgDrawReview->magni == 4)
				{
					pDC->MoveTo(stMeasure.FirstPoint[i].x / 4, stMeasure.FirstPoint[i].y / 4);
					pDC->LineTo(stMeasure.SecondPoint[i].x / 4, stMeasure.SecondPoint[i].y / 4);
					pDC->MoveTo(stMeasure.SecondPoint[i].x / 4, stMeasure.SecondPoint[i].y / 4);
					pDC->LineTo(stMeasure.ThirdPoint[i].x / 4, stMeasure.ThirdPoint[i].y / 4);
					pDC->TextOutW(stMeasure.FirstPoint[i].x / 4, stMeasure.FirstPoint[i].y / 4, strValue);
				}
			}

			else if (stMeasure.CaseMeasurement[i] == 4)
			{
				pDC->SelectObject(&pen_red);

				if (dlgVisionReview->dlgDrawReview->magni == 1)
				{
					pDC->Ellipse(stMeasure.FirstPoint[i].x, stMeasure.FirstPoint[i].y, stMeasure.SecondPoint[i].x, stMeasure.SecondPoint[i].y);
					pDC->TextOutW(stMeasure.FirstPoint[i].x, stMeasure.FirstPoint[i].y, strValue);
				}

				else if (dlgVisionReview->dlgDrawReview->magni == 2)
				{
					pDC->Ellipse(stMeasure.FirstPoint[i].x / 2, stMeasure.FirstPoint[i].y / 2, stMeasure.SecondPoint[i].x / 2, stMeasure.SecondPoint[i].y / 2);
					pDC->TextOutW(stMeasure.FirstPoint[i].x / 2, stMeasure.FirstPoint[i].y / 2, strValue);
				}

				else if (dlgVisionReview->dlgDrawReview->magni == 4)
				{
					pDC->Ellipse(stMeasure.FirstPoint[i].x / 4, stMeasure.FirstPoint[i].y / 4, stMeasure.SecondPoint[i].x / 4, stMeasure.SecondPoint[i].y / 4);
					pDC->TextOutW(stMeasure.FirstPoint[i].x / 4, stMeasure.FirstPoint[i].y / 4, strValue);
				}
			}

			else if (stMeasure.CaseMeasurement[i] == 5)
			{
				pDC->SelectObject(&pen_red);

				if (dlgVisionReview->dlgDrawReview->magni == 1)
				{
					pDC->Rectangle(stMeasure.FirstPoint[i].x, stMeasure.FirstPoint[i].y, 1224, 1024);
					pDC->TextOutW(stMeasure.FirstPoint[i].x, stMeasure.FirstPoint[i].y, strValue);
				}

				else if (dlgVisionReview->dlgDrawReview->magni == 2)
				{
					pDC->Rectangle(stMeasure.FirstPoint[i].x / 2, stMeasure.FirstPoint[i].y / 2, 612, 512);
					pDC->TextOutW(stMeasure.FirstPoint[i].x / 2, stMeasure.FirstPoint[i].y / 2, strValue);
				}

				else if (dlgVisionReview->dlgDrawReview->magni == 4)
				{
					pDC->Rectangle(stMeasure.FirstPoint[i].x / 4, stMeasure.FirstPoint[i].y / 4, 306, 256);
					pDC->TextOutW(stMeasure.FirstPoint[i].x / 4, stMeasure.FirstPoint[i].y / 4, strValue);
				}
			}
		}
	}
}


void CRVisionDlg::DisplayDrawNavigator(CDC* pDC)
{
	pDC->SetStretchBltMode(COLORONCOLOR);
	HDC hDC = pDC->GetSafeHdc();

	cBaumer->m_camera_set[4].m_pBitmapInfo->bmiHeader.biWidth = cBaumer->m_camera_set[4].m_SizeX;
	cBaumer->m_camera_set[4].m_pBitmapInfo->bmiHeader.biHeight = -cBaumer->m_camera_set[4].m_SizeY;

	int nSrcX = 0;
	int nSrcY = 0;
	int nSrcW = cBaumer->m_camera_set[4].m_SizeX;
	int nSrcH = cBaumer->m_camera_set[4].m_SizeY;

	// align 이미지
	int nRatio = 16;

	int nDstX = 0;
	int nDstY = 0;
	int nDstW = nSrcW / nRatio;
	int nDstH = nSrcH / nRatio;

	StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH,
		cBaumer->m_camera_set[4].m_buf, cBaumer->m_camera_set[4].m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

	pDC->SelectStockObject(NULL_BRUSH);

	pDC->SelectObject(&pen_red);

	if (dlgVisionReview->dlgDrawReview->magni == 4)
		pDC->Rectangle(dlgVisionReview->dlgDrawReview->mouse_scroll_x, dlgVisionReview->dlgDrawReview->mouse_scroll_y, 153 + dlgVisionReview->dlgDrawReview->mouse_scroll_x, 128 + dlgVisionReview->dlgDrawReview->mouse_scroll_y);

	else if (dlgVisionReview->dlgDrawReview->magni == 2)
		pDC->Rectangle(dlgVisionReview->dlgDrawReview->mouse_scroll_x / 8, dlgVisionReview->dlgDrawReview->mouse_scroll_y / 8, 76 + dlgVisionReview->dlgDrawReview->mouse_scroll_x / 8, 61 + dlgVisionReview->dlgDrawReview->mouse_scroll_y / 8);

	else if (dlgVisionReview->dlgDrawReview->magni == 1)
		pDC->Rectangle(dlgVisionReview->dlgDrawReview->mouse_scroll_x / 16, dlgVisionReview->dlgDrawReview->mouse_scroll_y / 16, 37 + dlgVisionReview->dlgDrawReview->mouse_scroll_x / 16, 31 + dlgVisionReview->dlgDrawReview->mouse_scroll_y / 16);
}


void CRVisionDlg::DisplayDrawFC(CDC* pDC)
{
	pDC->SetStretchBltMode(COLORONCOLOR);
	HDC hDC = pDC->GetSafeHdc();
	CString strValue_X;
	CString strValue_Y;
	CString strValue_Run;

	cBaumer->m_camera_set[4].m_pBitmapInfo->bmiHeader.biWidth = cBaumer->m_camera_set[4].m_SizeX;
	cBaumer->m_camera_set[4].m_pBitmapInfo->bmiHeader.biHeight = -cBaumer->m_camera_set[4].m_SizeY;

	int nSrcX = 0;
	int nSrcY = 0;
	int nSrcW = cBaumer->m_camera_set[4].m_SizeX;
	int nSrcH = cBaumer->m_camera_set[4].m_SizeY;

	// align 이미지
	int nRatio = 4;

	int nDstX = 0;
	int nDstY = 0;
	int nDstW = nSrcW / nRatio;
	int nDstH = nSrcH / nRatio;

	StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH,
		cBaumer->m_camera_set[4].m_buf, cBaumer->m_camera_set[4].m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

	pDC->SelectStockObject(NULL_BRUSH);


	if (CHK_CROSSLINE == true)
	{
		cPenCrossline.DeleteObject();
		cPenCrossline.CreatePen(PS_SOLID, 1, RGB(GetRValue(cCrossLineColor), GetGValue(cCrossLineColor), GetBValue(cCrossLineColor)));

		pDC->SelectObject(&cPenCrossline);

		pDC->MoveTo(nDstW / 2, 0);
		pDC->LineTo(nDstW / 2, nDstH);

		pDC->MoveTo(0, nDstH / 2);
		pDC->LineTo(nDstW, nDstH / 2);
	}

	if (ChkFindFC == true)
	{
		pDC->SelectObject(&pen_red);
		pDC->Rectangle(findPoint.x / 4, findPoint.y / 4, findPoint.x / 4 + MarkImageFC.cols / 4, findPoint.y / 4 + MarkImageFC.rows / 4);

		pDC->MoveTo((findPoint.x / 4 + MarkImageFC.cols / 8) - 10, findPoint.y / 4 + MarkImageFC.rows / 8);
		pDC->LineTo((findPoint.x / 4 + MarkImageFC.cols / 8) + 10, findPoint.y / 4 + MarkImageFC.rows / 8);

		pDC->MoveTo(findPoint.x / 4 + MarkImageFC.cols / 8, (findPoint.y / 4 + MarkImageFC.rows / 8) - 10);
		pDC->LineTo(findPoint.x / 4 + MarkImageFC.cols / 8, (findPoint.y / 4 + MarkImageFC.rows / 8) + 10);

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(GetRValue(cNameColor), GetGValue(cNameColor), GetBValue(cNameColor)));

		strValue_X.Format(_T("%.3f"), dErrorX_FC);
		pDC->TextOutW(100, 40, strValue_X);

		strValue_Y.Format(_T("%.3f"), dErrorY_FC);
		pDC->TextOutW(100, 70, strValue_Y);

		strValue_Run.Format(_T("%d"), nRun_FC);
		pDC->TextOutW(120, 100, strValue_Run);
	}

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(GetRValue(cNameColor), GetGValue(cNameColor), GetBValue(cNameColor)));

	pDC->TextOutW(10, 10, _T("Field Correction"));
	pDC->TextOutW(10, 40, _T("X_Error : "));
	pDC->TextOutW(10, 70, _T("Y_Error : "));
	pDC->TextOutW(10, 100, _T("FC Run : "));
}


void CRVisionDlg::DisplayDrawSetting(CDC* pDC, int nCase)
{
	pDC->SetStretchBltMode(COLORONCOLOR);
	HDC hDC = pDC->GetSafeHdc();

	cBaumer->m_camera_set[nCase].m_pBitmapInfo->bmiHeader.biWidth = cBaumer->m_camera_set[nCase].m_SizeX;
	cBaumer->m_camera_set[nCase].m_pBitmapInfo->bmiHeader.biHeight = -cBaumer->m_camera_set[nCase].m_SizeY;

	int nSrcX = 0;
	int nSrcY = 0;
	int nSrcW = cBaumer->m_camera_set[nCase].m_SizeX;
	int nSrcH = cBaumer->m_camera_set[nCase].m_SizeY;

	int nRatio = 4;

	int nDstX = 0;
	int nDstY = 0;
	int nDstW = nSrcW / nRatio;
	int nDstH = nSrcH / nRatio;

	StretchDIBits(hDC, nDstX, nDstY, nDstW, nDstH, nSrcX, nSrcY, nSrcW, nSrcH,
		cBaumer->m_camera_set[nCase].m_buf, cBaumer->m_camera_set[nCase].m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

	pDC->SelectStockObject(NULL_BRUSH);

	CString SaveAlignMark;
	SaveAlignMark = strRecipeFilePath + _T("AlignMark.bmp");
	CT2CA ConvertStringAlign(SaveAlignMark);
	std::string	ImageNameAlign(ConvertStringAlign);
	MarkImageAlign = imread(ImageNameAlign);

	m_pBmpAlignMark = (BITMAPINFO*)m_chBmpAlignMark;
	m_pBmpAlignMark->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpAlignMark->bmiHeader.biWidth = MarkImageAlign.cols;
	m_pBmpAlignMark->bmiHeader.biHeight = -(MarkImageAlign.rows);
	m_pBmpAlignMark->bmiHeader.biBitCount = 24;
	m_pBmpAlignMark->bmiHeader.biPlanes = 1;
	m_pBmpAlignMark->bmiHeader.biCompression = BI_RGB;
	m_pBmpAlignMark->bmiHeader.biSizeImage = 0;
	m_pBmpAlignMark->bmiHeader.biXPelsPerMeter = 0;
	m_pBmpAlignMark->bmiHeader.biYPelsPerMeter = 0;
	m_pBmpAlignMark->bmiHeader.biClrUsed = 0;
	m_pBmpAlignMark->bmiHeader.biClrImportant = 0;

	StretchDIBits(hdcMarkAlign, 0, 0, 120, 120, 0, 0, MarkImageAlign.cols, MarkImageAlign.rows, MarkImageAlign.data, m_pBmpAlignMark, DIB_RGB_COLORS, SRCCOPY);

	CString strMarkFC;
	strMarkFC = strRecipeFilePath + _T("FieldCorrectionMark.bmp");
	CT2CA ConvertStringFC(strMarkFC);
	std::string	ImageNameFC(ConvertStringFC);
	MarkImageFC = imread(ImageNameFC);

	m_pBmpMark = (BITMAPINFO*)m_chBmpMark;
	m_pBmpMark->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpMark->bmiHeader.biWidth = MarkImageFC.cols;
	m_pBmpMark->bmiHeader.biHeight = -(MarkImageFC.rows);
	m_pBmpMark->bmiHeader.biBitCount = 24;
	m_pBmpMark->bmiHeader.biPlanes = 1;
	m_pBmpMark->bmiHeader.biCompression = BI_RGB;
	m_pBmpMark->bmiHeader.biSizeImage = 0;
	m_pBmpMark->bmiHeader.biXPelsPerMeter = 0;
	m_pBmpMark->bmiHeader.biYPelsPerMeter = 0;
	m_pBmpMark->bmiHeader.biClrUsed = 0;
	m_pBmpMark->bmiHeader.biClrImportant = 0;

	StretchDIBits(hdcMarkFC, 0, 0, 120, 120, 0, 0, MarkImageFC.cols, MarkImageFC.rows, MarkImageFC.data, m_pBmpMark, DIB_RGB_COLORS, SRCCOPY);

	CString strMarkLaser;
	strMarkLaser = strExeFilePath + _T("Data\\LaserMark.bmp");
	CT2CA ConvertStringLaser(strMarkLaser);
	std::string	ImageNameLaser(ConvertStringLaser);
	MarkImageLaser = imread(ImageNameLaser);

	m_pBmpLaserMark = (BITMAPINFO*)m_chBmpLaserMark;
	m_pBmpLaserMark->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpLaserMark->bmiHeader.biWidth = MarkImageLaser.cols;
	m_pBmpLaserMark->bmiHeader.biHeight = -(MarkImageLaser.rows);
	m_pBmpLaserMark->bmiHeader.biBitCount = 24;
	m_pBmpLaserMark->bmiHeader.biPlanes = 1;
	m_pBmpLaserMark->bmiHeader.biCompression = BI_RGB;
	m_pBmpLaserMark->bmiHeader.biSizeImage = 0;
	m_pBmpLaserMark->bmiHeader.biXPelsPerMeter = 0;
	m_pBmpLaserMark->bmiHeader.biYPelsPerMeter = 0;
	m_pBmpLaserMark->bmiHeader.biClrUsed = 0;
	m_pBmpLaserMark->bmiHeader.biClrImportant = 0;

	StretchDIBits(hdcMarkLaser, 0, 0, 120, 120, 0, 0, MarkImageLaser.cols, MarkImageLaser.rows, MarkImageLaser.data, m_pBmpLaserMark, DIB_RGB_COLORS, SRCCOPY);

	// align
	if (nCase != 4)
	{
		if (CHK_MANUALALIGN == true)
		{
			pDC->SelectObject(&pen_red);

			pDC->MoveTo(MeasureStart.x, MeasureStart.y);
			pDC->LineTo(MeasureEnd.x, MeasureEnd.y);
		}

		if (dlgVisionSetting->dlgSettingAlign->ChkModify == true)
		{
			pDC->SelectObject(&pen_green);

			CString start_x, start_y;
			CString end_x, end_y;

			dlgVisionSetting->dlgSettingAlign->m_edit_edge_roi_start_x.GetWindowTextW(start_x);
			dlgVisionSetting->dlgSettingAlign->m_edit_edge_roi_start_y.GetWindowTextW(start_y);
			dlgVisionSetting->dlgSettingAlign->m_edit_edge_roi_end_x.GetWindowTextW(end_x);
			dlgVisionSetting->dlgSettingAlign->m_edit_edge_roi_end_y.GetWindowTextW(end_y);

			CPoint nStart;
			CPoint nEnd;

			nStart.x = _ttoi(start_x);
			nStart.y = _ttoi(start_y);
			nEnd.x = _ttoi(end_x);
			nEnd.y = _ttoi(end_y);

			DisplaySettingRoi(4, &nStart, &nEnd);
			pDC->Rectangle(nStart.x, nStart.y, nEnd.x, nEnd.y);
		}

		if (dlgVisionSetting->dlgSettingAlignMark->bChkMarkAlign == true)
		{
			pDC->SelectObject(&pen_red);
			pDC->Rectangle(dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect);

			pDC->MoveTo(dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.left +
				((dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.right - dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.left) / 2),
				dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.bottom - (dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.bottom - dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.top) / 2 - 10);
			pDC->LineTo(dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.left +
				((dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.right - dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.left) / 2),
				dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.bottom - (dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.bottom - dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.top) / 2 + 10);

			pDC->MoveTo(dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.left +
				((dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.right - dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.left) / 2 - 10),
				dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.bottom - (dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.bottom - dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.top) / 2);
			pDC->LineTo(dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.left +
				((dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.right - dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.left) / 2 + 10),
				dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.bottom - (dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.bottom - dlgVisionSetting->dlgSettingAlignMark->mMarkTracker.m_rect.top) / 2);
		}

		if (stMarkAlign.ChkManualFind[nCase] == true)
		{
			if (stMarkAlign.nChkManualMark[nCase] == 1)
				pDC->SelectObject(&pen_green);

			else if (stMarkAlign.nChkManualMark[nCase] == 2)
				pDC->SelectObject(&pen_red);

			pDC->Rectangle(stMarkAlign.MarkStart[nCase].x / 4, stMarkAlign.MarkStart[nCase].y / 4, stMarkAlign.MarkEnd[nCase].x / 4, stMarkAlign.MarkEnd[nCase].y / 4);
		}
	}

	// field correction 
	else if (nCase == 4)
	{
		if (dlgVisionSetting->dlgSettingFC->ChkModify == true)
		{
			pDC->SelectObject(&pen_green);

			CString start_x, start_y;
			CString end_x, end_y;

			dlgVisionSetting->dlgSettingFC->m_edit_fc_roi_start_x.GetWindowTextW(start_x);
			dlgVisionSetting->dlgSettingFC->m_edit_fc_roi_start_y.GetWindowTextW(start_y);
			dlgVisionSetting->dlgSettingFC->m_edit_fc_roi_end_x.GetWindowTextW(end_x);
			dlgVisionSetting->dlgSettingFC->m_edit_fc_roi_end_y.GetWindowTextW(end_y);

			CPoint nStart;
			CPoint nEnd;

			nStart.x = _ttoi(start_x);
			nStart.y = _ttoi(start_y);
			nEnd.x = _ttoi(end_x);
			nEnd.y = _ttoi(end_y);

			DisplaySettingRoi(4, &nStart, &nEnd);

			pDC->Rectangle(nStart.x, nStart.y, nEnd.x, nEnd.y);
		}

		if (dlgVisionSetting->dlgSettingFC->bChkMarkFC == true)
		{
			pDC->SelectObject(&pen_red);
			pDC->Rectangle(dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect);

			pDC->MoveTo(dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.left +
				((dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.right - dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.left) / 2),
				dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.bottom - (dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.bottom - dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.top) / 2 - 10);
			pDC->LineTo(dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.left +
				((dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.right - dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.left) / 2),
				dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.bottom - (dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.bottom - dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.top) / 2 + 10);

			pDC->MoveTo(dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.left +
				((dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.right - dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.left) / 2 - 10),
				dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.bottom - (dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.bottom - dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.top) / 2);
			pDC->LineTo(dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.left +
				((dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.right - dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.left) / 2 + 10),
				dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.bottom - (dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.bottom - dlgVisionSetting->dlgSettingFC->mMarkTracker.m_rect.top) / 2);
		}

		if (dlgVisionSetting->dlgSettingLaser->bChkMarkLaser == true)
		{
			pDC->SelectObject(&pen_green);
			pDC->Rectangle(dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect);

			pDC->MoveTo(dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.left +
				((dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.right - dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.left) / 2),
				dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.bottom - (dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.bottom - dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.top) / 2 - 10);
			pDC->LineTo(dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.left +
				((dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.right - dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.left) / 2),
				dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.bottom - (dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.bottom - dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.top) / 2 + 10);

			pDC->MoveTo(dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.left +
				((dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.right - dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.left) / 2 - 10),
				dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.bottom - (dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.bottom - dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.top) / 2);
			pDC->LineTo(dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.left +
				((dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.right - dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.left) / 2 + 10),
				dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.bottom - (dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.bottom - dlgVisionSetting->dlgSettingLaser->mMarkTracker.m_rect.top) / 2);
		}

		if (ChkFindLaser == true)
		{
			pDC->SelectObject(&pen_green);
			pDC->Rectangle(findLaserPoint.x / 4, findLaserPoint.y / 4, findLaserPoint.x / 4 + MarkImageLaser.cols / 4, findLaserPoint.y / 4 + MarkImageLaser.rows / 4);

			pDC->MoveTo((findLaserPoint.x / 4 + MarkImageLaser.cols / 8) - 10, findLaserPoint.y / 4 + MarkImageLaser.rows / 8);
			pDC->LineTo((findLaserPoint.x / 4 + MarkImageLaser.cols / 8) + 10, findLaserPoint.y / 4 + MarkImageLaser.rows / 8);

			pDC->MoveTo(findLaserPoint.x / 4 + MarkImageLaser.cols / 8, (findLaserPoint.y / 4 + MarkImageLaser.rows / 8) - 10);
			pDC->LineTo(findLaserPoint.x / 4 + MarkImageLaser.cols / 8, (findLaserPoint.y / 4 + MarkImageLaser.rows / 8) + 10);
		}
	}
}


void CRVisionDlg::DisplayMagni(int nMagni, CPoint* EdgeStartPoint, CPoint* EdgeEndPoint)
{
	if (EdgeStartPoint->x != 0)
		EdgeStartPoint->x /= nMagni;

	else
		EdgeStartPoint->x = 0;

	if (EdgeStartPoint->y != 0)
		EdgeStartPoint->y /= nMagni;

	else
		EdgeStartPoint->y = 0;

	if (EdgeEndPoint->x != 0)
		EdgeEndPoint->x /= nMagni;

	else
		EdgeEndPoint->x = 0;

	if (EdgeEndPoint->y != 0)
		EdgeEndPoint->y /= nMagni;

	else
		EdgeEndPoint->y = 0;
}


void CRVisionDlg::DisplaySettingRoi(int nMagni, CPoint* startPos, CPoint* endPos)
{
	if (startPos->x != 0)
		startPos->x /= nMagni;

	else
		startPos->x = 0;

	if (startPos->y != 0)
		startPos->y /= nMagni;

	else
		startPos->y = 0;

	if (endPos->x != 0)
		endPos->x /= nMagni;

	else
		endPos->x = 0;

	if (endPos->y != 0)
		endPos->y /= nMagni;

	else
		endPos->y = 0;

}

LRESULT CRVisionDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	COPYDATASTRUCT* pReceive = (COPYDATASTRUCT*)lParam;

	switch (message)
	{
	case WM_COPYDATA:
	{
		if (hServerHandle == NULL)
		{
			if ((HWND)wParam != NULL)
			{
				CWnd* pWnd = AfxGetMainWnd();

				// 핸들 값 입력 완료
				hServerHandle = (HWND)wParam;
				dlgVisionAlign->m_icon_heartbeat.SetBitmap(m_bmp_ledon2);

				LogWrite(NORMAL, "LASER PROGRAM 통신 연결 완료");

				ServerReturn(0);
			}
		}

		else
		{
			if (hServerHandle == (HWND)wParam)
			{
				//R2RCommData stReceiveData;

				memcpy(&stReceiveData, pReceive->lpData, sizeof(R2RCommData));

				// dialog 변경
				if (pReceive->dwData == 1)
				{
					ServerReturn(1);

					if (stReceiveData.nVisionMode != -1)
						ExcutionDialog(stReceiveData.nVisionMode);
				}

				// align run
				else if (pReceive->dwData == 3)
				{
					CWnd* pWnd = AfxGetMainWnd();


					//
					for (int i = 0; i < 4; i++)
					{
						stAlign.nBinaryLow[i] = 0;
						stAlign.nOpen[i] = 0;
						stAlign.nClose[i] = 0;

						stAlign.ROIStart[i].x = 0;
						stAlign.ROIStart[i].y = 0;
						stAlign.ROIEnd[i].x = 0;
						stAlign.ROIEnd[i].y = 0;

						stAlign.AlignPoint[i].x = 0;
						stAlign.AlignPoint[i].y = 0;
					}

					for (int i = 0; i < 4; i++)
					{
						stEdgeAlign.EdgeStart[i].x = 0;
						stEdgeAlign.EdgeStart[i].y = 0;

						stEdgeAlign.EdgeEnd[i].x = 0;
						stEdgeAlign.EdgeEnd[i].y = 0;

						stEdgeAlign.ChkFind[i] = false;
						stEdgeAlign.ChkMistake[i] = false;

						stEdgeAlign.ClickPoint[i] = 0;
						stEdgeAlign.FirstPoint[i] = 0;
						stEdgeAlign.SecondPoint[i] = 0;

						stEdgeAlign.Slope[i] = 0.0;
					}

					// ALIGN (MARK) 검출 관련 CLASS
					for (int i = 0; i < 4; i++)
					{
						stMarkAlign.ChkFind[i] = false;
						stMarkAlign.nChkFindMark[i] = 0;
						stMarkAlign.ChkManualFind[i] = false;
						stMarkAlign.nChkManualMark[i] = 0;

						stMarkAlign.ClickPoint[i] = 0;
						stMarkAlign.FirstPoint[i] = 0;
						stMarkAlign.SecondPoint[i] = 0;
					}
					// 
					// 
					dlgVisionAlign->GetDlgItem(IDC_STATIC_ALIGN_1_DETECT)->SetWindowTextW(_T("-"));
					dlgVisionAlign->GetDlgItem(IDC_STATIC_ALIGN_2_DETECT)->SetWindowTextW(_T("-"));
					dlgVisionAlign->GetDlgItem(IDC_STATIC_ALIGN_3_DETECT)->SetWindowTextW(_T("-"));
					dlgVisionAlign->GetDlgItem(IDC_STATIC_ALIGN_4_DETECT)->SetWindowTextW(_T("-"));

					dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_1)->SetWindowTextW(_T("-"));
					dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_2)->SetWindowTextW(_T("-"));
					dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_3)->SetWindowTextW(_T("-"));
					dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_4)->SetWindowTextW(_T("-"));

					dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_1)->SetWindowTextW(_T("-"));
					dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_2)->SetWindowTextW(_T("-"));
					dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_3)->SetWindowTextW(_T("-"));
					dlgVisionAlign->GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_4)->SetWindowTextW(_T("-"));

					// Jig 검사 유무 확인
					bJigProcess = stReceiveData.nJig;

					// 받았다는 응답 신호 리턴
					ServerReturn(3);

					nSelectRecipe = stReceiveData.nVisionRecipe;

					// recipe가 있는 경우
					if (stRecipe.bChkEmpty[nSelectRecipe - 1] == true)
					{
						SelectRecipe(nSelectRecipe);	// Recipe 선택

						strLogData.Format(_T("SELECT VISION RECIPE NUMBER : [%d]"), nSelectRecipe);
						csLogData = CStringA(strLogData);
						cFullLog = csLogData;
						cpFullLog = const_cast<char*>(cFullLog);
						LogWrite(ALIGNMENT, cpFullLog);

						// 데이터 값 수신
						dLGentryPos = stReceiveData.dLGentryPos;
						dRGentryPos = stReceiveData.dRGentryPos;
						dCam1Pos = stReceiveData.dCam1Pos;
						dCam2Pos = stReceiveData.dCam2Pos;
						dCam3Pos = stReceiveData.dCam3Pos;
						dCam4Pos = stReceiveData.dCam4Pos;

						strLogData.Format(_T("LEFT GENTRY : [%.3f], RIGHT GENTRY : [%.3f], ALIGN CAM(1) : [%.3f], ALIGN CAM(2) : [%.3f], ALIGN CAM(3): [%.3f], ALIGN CAM(4) : [%.3f]"),
							dLGentryPos, dRGentryPos, dCam1Pos, dCam2Pos, dCam3Pos, dCam4Pos);
						csLogData = CStringA(strLogData);
						cFullLog = csLogData;
						cpFullLog = const_cast<char*>(cFullLog);
						LogWrite(ALIGNMENT, cpFullLog);

						LogWrite(ALIGNMENT, "ALIGN 파라미터[CAM POS] 입력 완료");

						CString strVal;

						dAlignWidth = stReceiveData.dWidth;
						strVal.Format(_T("%.2f"), dAlignWidth);
						dlgVisionSetting->dlgSettingAlign->GetDlgItem(IDC_EDIT_ALIGN_WIDTH)->SetWindowTextW(strVal);

						dAlignHeight = stReceiveData.dHeight;
						strVal.Format(_T("%.2f"), dAlignHeight);
						dlgVisionSetting->dlgSettingAlign->GetDlgItem(IDC_EDIT_ALIGN_HEIGHT)->SetWindowTextW(strVal);

						strLogData.Format(_T("WIDTH : [%.3f], HEIGHT: [%.3f]"), dAlignWidth, dAlignHeight);
						csLogData = CStringA(strLogData);
						cFullLog = csLogData;
						cpFullLog = const_cast<char*>(cFullLog);
						LogWrite(ALIGNMENT, cpFullLog);

						CString		strPath;
						CString		strTag;
						CString		strData;

						strPath = strRecipeFilePath + _T("RecipeAlign.ini");

						strTag.Format(_T("SETTING"));

						strData.Format(_T("%.2f"), dAlignWidth);
						WritePrivateProfileString(strTag, _T("ALIGN_WIDTH"), strData, strPath);

						strData.Format(_T("%.2f"), dAlignHeight);
						WritePrivateProfileString(strTag, _T("ALIGN_HEIGHT"), strData, strPath);

						if (stReceiveData.nAlignRun == 1 || stReceiveData.nAlignRun == 2)
						{
							dAutosizing = stReceiveData.nAlignRun;

							LogWrite(ALIGNMENT, "ALIGN 동작 신호 입력");

							//if(dAutosizing == 1)
							//	LogWrite(NORMAL, "autosizing run");

							//else if (dAutosizing == 2)
							//	LogWrite(NORMAL, "autosizing pass");


							dlgVisionAlign->m_icon_alignstart.SetBitmap(m_bmp_ledon2);
							dlgVisionAlign->m_icon_alignend.SetBitmap(m_bmp_ledoff2);

							// alignment 이미지 저장 폴더 생성
							CTime strCreateTime = CTime::GetCurrentTime();

							strDayPath.Format(_T("D:\\VisionData\\Alignment\\_%04d_%02d%02d"), strCreateTime.GetYear(), strCreateTime.GetMonth(), strCreateTime.GetDay());
							CreateDirectory(strDayPath, NULL);

							CString strTime;
							strTime.Format(_T("\\_%02d%02d%02d"), strCreateTime.GetHour(), strCreateTime.GetMinute(), strCreateTime.GetSecond());
							strAlignmentPath = strDayPath + strTime;
							CreateDirectory(strAlignmentPath, NULL);
							dlgVisionAlign->m_icon_alignrun.SetBitmap(m_bmp_ledon2);

							Sleep(1000);

							CHK_PROC = true;
						}
					}

					else if (stRecipe.bChkEmpty[nSelectRecipe - 1] == false)
					{
						strLogData.Format(_T("선택된 레시피[%d]이(가) 존재하지 않습니다. "), nSelectRecipe);
						csLogData = CStringA(strLogData);
						cFullLog = csLogData;
						cpFullLog = const_cast<char*>(cFullLog);
						LogWrite(NG, cpFullLog);

						dlgPopupAlarm->DisplayMessage(_T("Recipe가 존재하지 않습니다."));
						dlgPopupAlarm->ShowWindow(SW_SHOW);

						bChkAlarm = true;


						/*stSendData.wdVisionErrorData.setBit(5, true);

						stSendData.bClientReceive = true;

						stSend.lpData = &stSendData;
						stSend.cbData = sizeof(stSendData);
						stSend.dwData = 8;

						::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);*/
					}
				}

				else if (pReceive->dwData == 5)
				{
					if (stReceiveData.nAlignMethod == 0)
					{
						CWnd* pWnd = AfxGetMainWnd();

						LogWrite(ALIGNMENT, "ALIGN PASS MODE 동작 신호 입력 완료");

						dModifyX = 0;
						dModifyY = 0;
						dModifyT = 0;
						dSizeX = 1.0;
						dSizeY = 1.0;

						dErrorLGentry = dLGentryPos - (dLGentryStdPos - ((dAlignWidth - 167) / 2));
						dErrorRGentry = (dRGentryStdPos - ((dAlignWidth - 167) / 2)) - dRGentryPos;

						dErrorCam1 = (dCam1StdPos - ((dAlignHeight - 167) / 2)) - dCam1Pos;
						dErrorCam2 = (dCam2StdPos + ((dAlignHeight - 167) / 2)) - dCam2Pos;
						dErrorCam3 = (dCam3StdPos - ((dAlignHeight - 167) / 2)) - dCam3Pos;
						dErrorCam4 = dCam4Pos - (dCam4StdPos - ((dAlignHeight - 167) / 2));

						dErrorX = (dErrorLGentry + dErrorRGentry) / 2;

						if (bJigProcess == true)
							dErrorY = ((dErrorCam1 + dErrorCam3) / 2 + dErrorCam2) / 2;

						else if (bJigProcess == false)
							dErrorY = (dErrorCam1 + dErrorCam2 + dErrorCam3 + dErrorCam4) / 4;

						strLogData.Format(_T("[Position 오차] Gentry Shift Value : %.3fmm, Vision Cam Shift Value : %.3fmm"), dErrorX, dErrorY);
						csLogData = CStringA(strLogData);
						cFullLog = csLogData;
						cpFullLog = const_cast<char*>(cFullLog);
						LogWrite(ALIGNMENT, cpFullLog);

						dModifyX += dErrorX;
						dModifyY += dErrorY;

						strLogData.Format(_T("[Laser Calibration offset] X축 offset : %.3fmm Y축 offset : %.3fmm"), dLCOffsetX, dLCOffsetY);
						csLogData = CStringA(strLogData);
						cFullLog = csLogData;
						cpFullLog = const_cast<char*>(cFullLog);
						LogWrite(ALIGNMENT, cpFullLog);

						dModifyX += dLCOffsetX;
						dModifyY -= dLCOffsetY;

						strLogData.Format(_T("[Manual offset] X축 offset : %.3fmm Y축 offset : %.3fmm Theta offset : %.6f˚"), dManualOffsetX, dManualOffsetY, dManualOffsetT);
						csLogData = CStringA(strLogData);
						cFullLog = csLogData;
						cpFullLog = const_cast<char*>(cFullLog);
						LogWrite(ALIGNMENT, cpFullLog);

						dModifyX += dManualOffsetX;
						dModifyY += dManualOffsetY;
						dModifyT += dManualOffsetT;

						CString strVal;
						double dVal;

						dlgVisionSetting->dlgSettingAlign->m_edit_xoffset.GetWindowTextW(strVal);
						dPostX = (_wtof(strVal) / 1000);

						dlgVisionSetting->dlgSettingAlign->m_edit_yoffset.GetWindowTextW(strVal);
						dPostY = (_wtof(strVal) / 1000);

						dlgVisionSetting->dlgSettingAlign->m_edit_toffset.GetWindowTextW(strVal);
						dPostT = _wtof(strVal);

						strLogData.Format(_T("[Align Vision offset] X축 offset : %.3fmm, Y축 offset : %.3fmm, Theta offset : %.6f˚"), dPostX, dPostY, dPostT);
						csLogData = CStringA(strLogData);
						cFullLog = csLogData;
						cpFullLog = const_cast<char*>(cFullLog);
						LogWrite(ALIGNMENT, cpFullLog);

						dModifyX += dPostX;
						dModifyY += dPostY;
						dModifyT += dPostT;

						strLogData.Format(_T("[Align Total Result] X축 보정 값 : %.3fmm, Y축 보정 값 : %.3fmm, THETA 보정 값 : %.6f˚"), dModifyX, dModifyY, dModifyT);
						csLogData = CStringA(strLogData);
						cFullLog = csLogData;
						cpFullLog = const_cast<char*>(cFullLog);
						LogWrite(ALIGNMENT, cpFullLog);

						// 데이터 전송
						//stSendData.nResult = 1;

						stSendData.dXModify = dModifyX;
						stSendData.dYModify = dModifyY;
						stSendData.dTModify = dModifyT;
						stSendData.dScaleX = dSizeX;
						stSendData.dScaleY = dSizeY;

						stSendData.bClientReceive = false;
						stSendData.bServerReceive = true;

						stSend.lpData = &stSendData;
						stSend.cbData = sizeof(stSendData);
						stSend.dwData = 5;

						::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);

						//ServerReturn(5);
					}

					else if (stReceiveData.nAlignMethod == 1)
					{
						LogWrite(ALIGNMENT, "ALIGN MANUAL MODE 동작 신호 입력 완료");

						ServerReturn(5);

						ExcutionManualAlign();
					}
				}

				else if (pReceive->dwData == 6)
				{
					if (stReceiveData.nFCRun == 1)
					{
						LogWrite(FIELDCORRECTION, "Field Correction 동작 신호 입력 완료");

						ServerReturn(6);

						dGain = stReceiveData.dGain;
						dNewcal = stReceiveData.dNewcal;
						nPatternPoint = stReceiveData.nPatternPoint;
						dPatternLength = stReceiveData.dPatternLength;

						strNewctFile = strOldctFile;
						int nInsert = strNewctFile.Find(_T(".ct5"));
						strNewctFile.Insert(nInsert, _T("(2)"));

						dlgVisionFC->DisplayParam();

						pFCResult = new FCResult[(nPatternPoint) * (nPatternPoint)];

						for (int i = 0; i < nPatternPoint * nPatternPoint; i++)
						{
							pFCResult[i].dXError = 0;
							pFCResult[i].dYError = 0;
						}

						dErrorX_FC = 0.0;
						dErrorY_FC = 0.0;
						nRun_FC = 0;
						nCountFC = 0;

						tRealTime = CTime::GetCurrentTime();
						strRealTime.Format(_T("%04d.%02d.%02d_%02d%02d%02d"), tRealTime.GetYear(), tRealTime.GetMonth(), tRealTime.GetDay(), tRealTime.GetHour(), tRealTime.GetMinute(), tRealTime.GetSecond());
						dlgVisionFC->m_list_fc.InsertItem(dlgVisionFC->nFCLogCount, strRealTime);
						dlgVisionFC->m_list_fc.SetItemText(dlgVisionFC->nFCLogCount, 1, _T("Field Correction"));
						dlgVisionFC->m_list_fc.SetItemText(dlgVisionFC->nFCLogCount, 2, _T("Field Correction 동작 신호"));
						dlgVisionFC->nFCLogCount++;

						CHK_FC = true;

					}
				}

				else if (pReceive->dwData == 7)
				{
					if (stReceiveData.nFCShot == 1)
					{
						LogWrite(FIELDCORRECTION, "Field Correction 측정 신호 입력 완료");

						ServerReturn(7);

						tRealTime = CTime::GetCurrentTime();
						strRealTime.Format(_T("%04d.%02d.%02d_%02d%02d%02d"), tRealTime.GetYear(), tRealTime.GetMonth(), tRealTime.GetDay(), tRealTime.GetHour(), tRealTime.GetMinute(), tRealTime.GetSecond());
						dlgVisionFC->m_list_fc.InsertItem(dlgVisionFC->nFCLogCount, strRealTime);
						dlgVisionFC->m_list_fc.SetItemText(dlgVisionFC->nFCLogCount, 1, _T("Field Correction"));

						CString strFC;
						strFC.Format(_T("Field Correction 측정 신호(%d번째)"), nCountFC + 1);

						dlgVisionFC->m_list_fc.SetItemText(dlgVisionFC->nFCLogCount, 2, strFC);
						dlgVisionFC->nFCLogCount++;

						Sleep(1000);
						ExcutionFC(0);
					}

					if (stReceiveData.bClientReceive == true)
					{
						CWnd* pWnd = AfxGetMainWnd();

						if (nCountFC == (nPatternPoint * nPatternPoint))
						{
							stSendData.nFCRun = 0;
							stSendData.bClientReceive = true;

							stSend.lpData = &stSendData;
							stSend.cbData = sizeof(stSendData);
							stSend.dwData = 6;

							::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);
						}
					}
				}

				else if (pReceive->dwData == 9)
				{
					if (stReceiveData.nLCRun == 1)
					{
						LogWrite(FIELDCORRECTION, "Laser Calibration 측정 신호 입력 완료");

						ServerReturn(9);

						// append 230109
						Sleep(1000);
						ExcutionLaserCalibration();
					}
				}

				// 데이터 보낼 때 bClientReceive 를 TRUE로 전송
				// Server에서 bClientReceive 값을 FALSE 로 전송 시 데이터를 정상적으로 받은 것으로 확인
				if (stReceiveData.bClientReceive == false)
				{
				}
			}
		}
	}break;

	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}


CString CRVisionDlg::byIndexComPort(int xPort)
{
	CString PortName = _T("");
	switch (xPort)
	{
	case 0:		PortName = "COM1"; 			break;

	case 1:		PortName = "COM2";			break;

	case 2:		PortName = "COM3"; 			break;

	case 3:		PortName = "COM4";			break;

	case 4:		PortName = "\\\\.\\COM5"; 	break;

	case 5:		PortName = "\\\\.\\COM6";	break;

	case 6:		PortName = "\\\\.\\COM7"; 	break;

	case 7:		PortName = "\\\\.\\COM8";	break;

	case 8:		PortName = "\\\\.\\COM9"; 	break;

	case 9:		PortName = "\\\\.\\COM10";	break;
	}

	return PortName;
}

DWORD CRVisionDlg::byIndexBaud(int xBaud)
{
	DWORD dwBaud = 0;
	switch (xBaud)
	{
	case 0:		dwBaud = CBR_4800;		break;

	case 1:		dwBaud = CBR_9600;		break;

	case 2:		dwBaud = CBR_14400;		break;

	case 3:		dwBaud = CBR_19200;		break;

	case 4:		dwBaud = CBR_38400;		break;

	case 5:		dwBaud = CBR_56000;		break;

	case 6:		dwBaud = CBR_57600;		break;

	case 7:		dwBaud = CBR_115200;	break;
	}

	return dwBaud;
}

BYTE CRVisionDlg::byIndexData(int xData)
{
	BYTE byData = 0;
	switch (xData)
	{
	case 0:	byData = 5;			break;

	case 1:	byData = 6;			break;

	case 2:	byData = 7;			break;

	case 3:	byData = 8;			break;
	}
	return byData;
}

BYTE CRVisionDlg::byIndexStop(int xStop)
{
	BYTE byStop = 0;
	if (xStop == 0)
	{
		byStop = ONESTOPBIT;
	}
	else
	{
		byStop = TWOSTOPBITS;
	}
	return byStop;
}

BYTE CRVisionDlg::byIndexParity(int xParity)
{
	BYTE byParity = 0;
	switch (xParity)
	{
	case 0:	byParity = NOPARITY;	break;

	case 1:	byParity = ODDPARITY;	break;

	case 2:	byParity = EVENPARITY;	break;
	}

	return byParity;
}


void CRVisionDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	/*KillTimer(1);

	LogWrite(END, "ONTIMER 해제");

	if (Vision != NULL)
	{
		for (int i = 0; i < 5; i++)
		{
			if (cBaumer->Status[i] == true)
			{
				cBaumer->m_camera_set[i].pDataStreamf->UnregisterNewBufferEvent();
			}
		}

		Vision->SuspendThread();

		DWORD dwResult;
		::GetExitCodeThread(Vision->m_hThread, &dwResult);
		delete Vision;
		Vision = NULL;

		delete cBaumer;

		LogWrite(END, "VISION THREAD 종료");
	}

	if (Volume != NULL)
	{
		Volume->SuspendThread();

		DWORD dwResult;
		::GetExitCodeThread(Volume->m_hThread, &dwResult);
		delete Volume;
		Volume = NULL;

		LogWrite(END, "VOLUME CHECK THREAD 종료");
	}

	delete btnFont;
	LogWrite(END, "VISION 프로그램 종료");*/
	CDialogEx::OnClose();
}


afx_msg LRESULT CRVisionDlg::OnHeartbeat(WPARAM wParam, LPARAM lParam)
{
	if (lParam == 1)
	{
		//dlgVisionAlign->m_icon_heartbeat.SetBitmap(m_bmp_ledon2);
		nHeartbeat = 1;
	}


	return 0;
}


void CRVisionDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nIDEvent == 1)
	{
		CWnd* pWnd = AfxGetMainWnd();

		if (bChkCamera == true)
		{
			// camera 1 연결 에러
			try
			{
				cBaumer->m_camera_set[0].pDevicef->GetRemoteNode("TimestampLatch")->Execute();
				ChkConnectCam1 = cBaumer->m_camera_set[0].pDevicef->GetRemoteNode("TimestampLatchValue")->GetInt();
				dlgVisionAlign->m_icon_cam1.SetBitmap(m_bmp_ledon2);
			}

			catch (BGAPI2::Exceptions::IException& ex)
			{
				stSendData.wdVisionErrorData.setBit(0, true);
				dlgVisionAlign->m_icon_cam1.SetBitmap(m_bmp_ledoff2);

				stSendData.bClientReceive = true;

				stSend.lpData = &stSendData;
				stSend.cbData = sizeof(stSendData);
				stSend.dwData = 8;

				::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);
			}

			// camera 2 연결 에러
			try
			{
				cBaumer->m_camera_set[1].pDevicef->GetRemoteNode("TimestampLatch")->Execute();
				ChkConnectCam1 = cBaumer->m_camera_set[1].pDevicef->GetRemoteNode("TimestampLatchValue")->GetInt();
				dlgVisionAlign->m_icon_cam2.SetBitmap(m_bmp_ledon2);
			}

			catch (BGAPI2::Exceptions::IException& ex)
			{
				stSendData.wdVisionErrorData.setBit(1, true);
				dlgVisionAlign->m_icon_cam2.SetBitmap(m_bmp_ledoff2);

				stSendData.bClientReceive = true;

				stSend.lpData = &stSendData;
				stSend.cbData = sizeof(stSendData);
				stSend.dwData = 8;

				::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);
			}

			// camera 3 연결 에러
			try
			{
				cBaumer->m_camera_set[2].pDevicef->GetRemoteNode("TimestampLatch")->Execute();
				ChkConnectCam1 = cBaumer->m_camera_set[2].pDevicef->GetRemoteNode("TimestampLatchValue")->GetInt();
				dlgVisionAlign->m_icon_cam3.SetBitmap(m_bmp_ledon2);
			}

			catch (BGAPI2::Exceptions::IException& ex)
			{
				stSendData.wdVisionErrorData.setBit(2, true);
				dlgVisionAlign->m_icon_cam3.SetBitmap(m_bmp_ledoff2);

				stSendData.bClientReceive = true;

				stSend.lpData = &stSendData;
				stSend.cbData = sizeof(stSendData);
				stSend.dwData = 8;

				::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);
			}

			// camera 4 연결 에러
			try
			{
				cBaumer->m_camera_set[3].pDevicef->GetRemoteNode("TimestampLatch")->Execute();
				ChkConnectCam1 = cBaumer->m_camera_set[3].pDevicef->GetRemoteNode("TimestampLatchValue")->GetInt();
				dlgVisionAlign->m_icon_cam4.SetBitmap(m_bmp_ledon2);
			}

			catch (BGAPI2::Exceptions::IException& ex)
			{
				stSendData.wdVisionErrorData.setBit(3, true);
				dlgVisionAlign->m_icon_cam4.SetBitmap(m_bmp_ledoff2);

				stSendData.bClientReceive = true;

				stSend.lpData = &stSendData;
				stSend.cbData = sizeof(stSendData);
				stSend.dwData = 8;

				::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);
			}

			// camera 5 연결 에러
			try
			{
				cBaumer->m_camera_set[4].pDevicef->GetRemoteNode("TimestampLatch")->Execute();
				ChkConnectCam1 = cBaumer->m_camera_set[4].pDevicef->GetRemoteNode("TimestampLatchValue")->GetInt();
				dlgVisionAlign->m_icon_cam5.SetBitmap(m_bmp_ledon2);
			}

			catch (BGAPI2::Exceptions::IException& ex)
			{
				stSendData.wdVisionErrorData.setBit(4, true);
				dlgVisionAlign->m_icon_cam5.SetBitmap(m_bmp_ledoff2);

				stSendData.bClientReceive = true;

				stSend.lpData = &stSendData;
				stSend.cbData = sizeof(stSendData);
				stSend.dwData = 8;

				::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);

			}
		}

		if (chkalarmdisplay == 1)
			ReconnectCamera();

		if (bChkAlarm == true)
		{
			Sleep(2000);

			dlgPopupAlarm->ShowWindow(SW_HIDE);
			bChkAlarm = false;
		}

	}

	CDialogEx::OnTimer(nIDEvent);
}


void InputAlignLog(int nCase, int nCam, bool Result, bool totalResult)
{


}


void CRVisionDlg::SaveRecipeName()
{
	CFileFind file;
	CString strFile;

	CString		strPath;
	CString		strTag;
	CString		strData;
	CString		strName;
	TCHAR		szData[MAX_PATH];

	strPath = strExeFilePath + _T("RecipeName.ini");
	strTag = _T("RecipeName");

	// 폴더 확인
	for (int i = 0; i < 100; i++)
	{
		strFile.Format(_T("%d"), i + 1);

		if (file.FindFile(strExeFilePath + _T("Recipe\\") + strFile))
		{
			stRecipe.bChkEmpty[i] = true;
		}

		else
		{
			stRecipe.bChkEmpty[i] = false;
			// Camera
			strPath = strExeFilePath + _T("RecipeName.ini");
			strTag = _T("RecipeName");

			strName.Format(_T("Recipe%d"), i + 1);

			strData = _T("Empty");
			WritePrivateProfileString(strTag, strName, strData, strPath);

		}
	}

	// RECIPE NAME 저장
	for (int i = 0; i < 100; i++)
	{
		strName.Format(_T("Recipe%d"), i + 1);
		ZeroMemory(szData, MAX_PATH);
		GetPrivateProfileString(strTag, strName, _T("empty"), szData, MAX_PATH, strPath);
		strData = szData;
		stRecipe.strRecipeName[i] = szData;
	}
}


void CRVisionDlg::RecipeSelect()
{
	SaveRecipeName();

	CRect rcRecipeSelect;
	GetWindowRect(rcRecipeSelect);

	rcRecipeSelect.top += 500;
	rcRecipeSelect.left += 150;
	rcRecipeSelect.right = rcRecipeSelect.left + 340;
	rcRecipeSelect.bottom = rcRecipeSelect.top + 140;

	dlgPopupRecipeSelect.rcDialog = rcRecipeSelect;
	dlgPopupRecipeSelect.filePath = strExeFilePath + _T("Recipe\\");
	dlgPopupRecipeSelect.nSelectNum = nSelectRecipe;

	if (dlgPopupRecipeSelect.DoModal() == IDOK)
	{
		SelectRecipe(nSelectRecipe);
	}

	else
	{

	}
}


void CRVisionDlg::RecipeAdd()
{
	SaveRecipeName();

	CRect rcRecipeAdd;
	GetWindowRect(rcRecipeAdd);

	rcRecipeAdd.top += 500;
	rcRecipeAdd.left += 150;
	rcRecipeAdd.right = rcRecipeAdd.left + 340;
	rcRecipeAdd.bottom = rcRecipeAdd.top + 140;


	dlgPopupRecipeAdd.rcDialog = rcRecipeAdd;

	if (dlgPopupRecipeAdd.DoModal() == IDOK)   // 다이얼로그가 종료될 때 반환되는 값을 검사, OK 버튼으로 종료되었을 경우 IDOK를 반환
	{
		CString strFromRecipe;
		CString strtoRecipe;

		CString strFromNum;
		CString strToNum;

		strFromNum.Format(_T("Recipe\\%d"), nSelectRecipe);
		strFromRecipe = strExeFilePath + strFromNum;


		strtoRecipe.Format(_T("Recipe\\%d"), nCopyRecipe);

		strtoRecipe = strExeFilePath + strtoRecipe;

		CopyFolder(strFromRecipe, strtoRecipe);

		CString		strPath;
		CString		strTag;
		CString		strName;
		CString		strData;

		// Camera
		strPath = strExeFilePath + _T("RecipeName.ini");
		strTag = _T("RecipeName");

		for (int i = 0; i < 100; i++)
		{
			strName.Format(_T("Recipe%d"), i + 1);

			strData = stRecipe.strRecipeName[i];
			WritePrivateProfileString(strTag, strName, strData, strPath);
		}

		stRecipe.bChkEmpty[nCopyRecipe - 1] = true;

		SelectRecipe(nCopyRecipe);
	}

	else
	{

	}

}


void CRVisionDlg::CopyFolder(CString szFrom, CString szTo)
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	BOOL bResult = TRUE;
	TCHAR WildCard[MAX_PATH];
	TCHAR SrcFile[MAX_PATH];
	TCHAR DestFile[MAX_PATH];

	wsprintf(WildCard, _T("%s\\*.*"), szFrom);
	CreateDirectory(szTo, NULL);
	hSrch = FindFirstFile(WildCard, &wfd);
	//if (hSrch == INVALID_HANDLE_VALUE)
	//	return FALSE;

	while (bResult)
	{
		wsprintf(SrcFile, _T("%s\\%s"), szFrom, wfd.cFileName);
		wsprintf(DestFile, _T("%s\\%s"), szTo, wfd.cFileName);

		// 서브 디렉토리가 발견되면 서브 디렉토리를 복사한다. 
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (lstrcmp(wfd.cFileName, _T(".")) && lstrcmp(wfd.cFileName, _T("..")))
			{
				CopyFolder(SrcFile, DestFile);
			}
		}
		else { CopyFile(SrcFile, DestFile, FALSE); } bResult = FindNextFile(hSrch, &wfd);
	} FindClose(hSrch);
}


void CRVisionDlg::DisplayAlarm()
{
	dlgPopupAlarm->DisplayMessage(_T("카메라 재 연결 중..."));
	dlgPopupAlarm->ShowWindow(SW_SHOW);

	chkalarmdisplay = 1;
}


void CRVisionDlg::ReconnectCamera()
{
	CWnd* pWnd = AfxGetMainWnd();

	if (Vision != NULL)
	{
		bChkCamera = false;
		for (int i = 0; i < 5; i++)
		{
			if (cBaumer->Status[i] == true)
				cBaumer->m_camera_set[i].pDataStreamf->UnregisterNewBufferEvent();
		}

		Vision->SuspendThread();

		DWORD dwResult;
		::GetExitCodeThread(Vision->m_hThread, &dwResult);
		delete Vision;
		Vision = NULL;

		delete cBaumer;

		ConnectCamera();
		LogWrite(NORMAL, "CAMERA RECONNECT COMPLETE");
	}

	if (cBaumer->Status[0] == true)
		stSendData.wdVisionErrorData.setBit(0, false);

	if (cBaumer->Status[1] == true)
		stSendData.wdVisionErrorData.setBit(1, false);

	if (cBaumer->Status[2] == true)
		stSendData.wdVisionErrorData.setBit(2, false);

	if (cBaumer->Status[3] == true)
		stSendData.wdVisionErrorData.setBit(3, false);

	if (cBaumer->Status[4] == true)
		stSendData.wdVisionErrorData.setBit(4, false);

	stSendData.bClientReceive = true;

	stSend.lpData = &stSendData;
	stSend.cbData = sizeof(stSendData);
	stSend.dwData = 8;

	::SendMessage(hServerHandle, WM_COPYDATA, (WPARAM)pWnd->m_hWnd, (LPARAM)&stSend);

	dlgPopupAlarm->ShowWindow(SW_HIDE);
	chkalarmdisplay = 0;
}


void CRVisionDlg::DisplayPreprocessImg(int nCam, bool nCase)
{
	CRect rcPreprocImg;
	GetWindowRect(rcPreprocImg);

	rcPreprocImg.top += 500;
	rcPreprocImg.left += (WindowWidth - 306) / 2;

	dlgPopupPreprocessImg->MoveWindow(rcPreprocImg.left, rcPreprocImg.top, 306, 290);

	if (nCase == true)
		dlgPopupPreprocessImg->ShowWindow(SW_SHOW);

	else if (nCase == false)
		dlgPopupPreprocessImg->ShowWindow(SW_HIDE);

	// align 
	if (nCam == 1)
	{
		Mat LoadImg;;

		CString FileName;
		if (dlgVisionSetting->dlgSettingAlign->SelectCam == 0)
			FileName = strExeFilePath + _T("Data\\_ProcImage_1.bmp");

		else if (dlgVisionSetting->dlgSettingAlign->SelectCam == 1)
			FileName = strExeFilePath + _T("Data\\_ProcImage_2.bmp");

		else if (dlgVisionSetting->dlgSettingAlign->SelectCam == 2)
			FileName = strExeFilePath + _T("Data\\_ProcImage_3.bmp");

		else if (dlgVisionSetting->dlgSettingAlign->SelectCam == 3)
			FileName = strExeFilePath + _T("Data\\_ProcImage_4.bmp");

		CT2CA ConvertString(FileName);
		std::string	Image_path(ConvertString);

		LoadImg = imread(Image_path);

		m_pBmpProcImg = (BITMAPINFO*)m_chBmpProcImg;
		m_pBmpProcImg->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		m_pBmpProcImg->bmiHeader.biWidth = LoadImg.cols;
		m_pBmpProcImg->bmiHeader.biHeight = -(LoadImg.rows);
		m_pBmpProcImg->bmiHeader.biBitCount = 24;
		m_pBmpProcImg->bmiHeader.biPlanes = 1;
		m_pBmpProcImg->bmiHeader.biCompression = BI_RGB;
		m_pBmpProcImg->bmiHeader.biSizeImage = 0;
		m_pBmpProcImg->bmiHeader.biXPelsPerMeter = 0;
		m_pBmpProcImg->bmiHeader.biYPelsPerMeter = 0;
		m_pBmpProcImg->bmiHeader.biClrUsed = 0;
		m_pBmpProcImg->bmiHeader.biClrImportant = 0;

		StretchDIBits(hdcProcImg, 0, 0, 302, 256, 0, 0, LoadImg.cols, LoadImg.rows, LoadImg.data, m_pBmpProcImg, DIB_RGB_COLORS, SRCCOPY);
	}

	// fc
	else if (nCam == 2)
	{
		Mat LoadImg;;

		CString FileName;

		FileName = strExeFilePath + _T("Data\\_ProcImage_5.bmp");

		CT2CA ConvertString(FileName);
		std::string	Image_path(ConvertString);

		LoadImg = imread(Image_path);

		m_pBmpProcImg = (BITMAPINFO*)m_chBmpProcImg;
		m_pBmpProcImg->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		m_pBmpProcImg->bmiHeader.biWidth = LoadImg.cols;
		m_pBmpProcImg->bmiHeader.biHeight = -(LoadImg.rows);
		m_pBmpProcImg->bmiHeader.biBitCount = 24;
		m_pBmpProcImg->bmiHeader.biPlanes = 1;
		m_pBmpProcImg->bmiHeader.biCompression = BI_RGB;
		m_pBmpProcImg->bmiHeader.biSizeImage = 0;
		m_pBmpProcImg->bmiHeader.biXPelsPerMeter = 0;
		m_pBmpProcImg->bmiHeader.biYPelsPerMeter = 0;
		m_pBmpProcImg->bmiHeader.biClrUsed = 0;
		m_pBmpProcImg->bmiHeader.biClrImportant = 0;

		StretchDIBits(hdcProcImg, 0, 0, 302, 256, 0, 0, LoadImg.cols, LoadImg.rows, LoadImg.data, m_pBmpProcImg, DIB_RGB_COLORS, SRCCOPY);
	}
}


void CRVisionDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CString strRegValue;

	//dlgVisionSetting->dlgSettingAlign->m_edit_xoffset.GetWindowTextW(strRegValue);
	//AfxGetApp()->WriteProfileStringW(_T("ALIGN"), _T("XOFFSET"), strRegValue);

	//dlgVisionSetting->dlgSettingAlign->m_edit_yoffset.GetWindowTextW(strRegValue);
	//AfxGetApp()->WriteProfileStringW(_T("ALIGN"), _T("YOFFSET"), strRegValue);

	dlgVisionSetting->dlgSettingAlignMark->m_edit_mark_thread.GetWindowTextW(strRegValue);
	AfxGetApp()->WriteProfileStringW(_T("MARK"), _T("THREAD"), strRegValue);

	dlgVisionSetting->dlgSettingAlignMark->m_edit_mark_open.GetWindowTextW(strRegValue);
	AfxGetApp()->WriteProfileStringW(_T("MARK"), _T("OPEN"), strRegValue);

	dlgVisionSetting->dlgSettingAlignMark->m_edit_mark_close.GetWindowTextW(strRegValue);
	AfxGetApp()->WriteProfileStringW(_T("MARK"), _T("CLOSE"), strRegValue);

	dlgVisionSetting->dlgSettingFC->m_edit_fcmark_binary_low.GetWindowTextW(strRegValue);
	AfxGetApp()->WriteProfileStringW(_T("FCMARK"), _T("THREAD"), strRegValue);

	dlgVisionSetting->dlgSettingFC->m_edit_fcmark_open.GetWindowTextW(strRegValue);
	AfxGetApp()->WriteProfileStringW(_T("FCMARK"), _T("OPEN"), strRegValue);

	dlgVisionSetting->dlgSettingFC->m_edit_fcmark_close.GetWindowTextW(strRegValue);
	AfxGetApp()->WriteProfileStringW(_T("FCMARK"), _T("CLOSE"), strRegValue);

	strRegValue.Format(_T("%d"), nSelectRecipe);
	AfxGetApp()->WriteProfileStringW(_T("RECIPE"), _T("RECIPE_NUM"), strRegValue);

	strRegValue.Format(_T("%.3f"), dLCOffsetX);
	AfxGetApp()->WriteProfileStringW(_T("LASERCALIBRATION"), _T("OFFSET_X"), strRegValue);

	strRegValue.Format(_T("%.3f"), dLCOffsetY);
	AfxGetApp()->WriteProfileStringW(_T("LASERCALIBRATION"), _T("OFFSET_Y"), strRegValue);

	strRegValue.Format(_T("%.3f"), dManualOffsetX);
	AfxGetApp()->WriteProfileStringW(_T("ALIGN"), _T("MODIFYX"), strRegValue);

	strRegValue.Format(_T("%.3f"), dManualOffsetY);
	AfxGetApp()->WriteProfileStringW(_T("ALIGN"), _T("MODIFYY"), strRegValue);

	strRegValue.Format(_T("%.3f"), dManualOffsetT);
	AfxGetApp()->WriteProfileStringW(_T("ALIGN"), _T("MODIFYT"), strRegValue);


	KillTimer(1);

	LogWrite(END, "ONTIMER 해제");

	if (Vision != NULL)
	{
		for (int i = 0; i < 5; i++)
		{
			if (cBaumer->Status[i] == true)
			{
				cBaumer->m_camera_set[i].pDataStreamf->UnregisterNewBufferEvent();
			}
		}

		Vision->SuspendThread();

		DWORD dwResult;
		::GetExitCodeThread(Vision->m_hThread, &dwResult);
		delete Vision;
		Vision = NULL;

		delete cBaumer;

		LogWrite(END, "VISION THREAD 종료");
	}

	if (Volume != NULL)
	{
		Volume->SuspendThread();

		DWORD dwResult;
		::GetExitCodeThread(Volume->m_hThread, &dwResult);
		delete Volume;
		Volume = NULL;

		LogWrite(END, "VOLUME CHECK THREAD 종료");
	}

	if (Proc != NULL)
	{
		Proc->SuspendThread();

		DWORD dwResult;
		::GetExitCodeThread(Proc->m_hThread, &dwResult);
		delete Proc;
		Proc = NULL;

		LogWrite(END, "PROCESS THREAD 종료");
	}

	delete btnFont;
	LogWrite(END, "VISION 프로그램 종료");
}

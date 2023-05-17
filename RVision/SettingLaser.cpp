// SettingLaser.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "SettingLaser.h"
#include "afxdialogex.h"

#include "RVisionDlg.h"

// SettingLaser 대화 상자

IMPLEMENT_DYNAMIC(SettingLaser, CDialogEx)

SettingLaser::SettingLaser(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_LASER, pParent)
{

}

SettingLaser::~SettingLaser()
{
}

void SettingLaser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LASER_SPEED, m_edit_laser_speed);
	DDX_Control(pDX, IDC_EDIT_LASER_HZ, m_edit_laser_hz);
	DDX_Control(pDX, IDC_EDIT_LASER_SIZE, m_edit_laser_size);
	DDX_Control(pDX, IDC_EDIT_LASER_POWER, m_edit_laser_power);
	DDX_Control(pDX, IDC_EDIT_DFOCUS, m_edit_dfocus);
	DDX_Control(pDX, IDC_BTN_OFFSET, m_btn_offset);
}


BEGIN_MESSAGE_MAP(SettingLaser, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_CALCULATION, &SettingLaser::OnBnClickedBtnCalculation)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &SettingLaser::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_LASERMARK_ENROLL, &SettingLaser::OnBnClickedBtnLasermarkEnroll)
	ON_BN_CLICKED(IDC_BTN_LASERMARK_APPLY, &SettingLaser::OnBnClickedBtnLasermarkApply)
	ON_BN_CLICKED(IDC_BTN_LASERMARK_CANCEL, &SettingLaser::OnBnClickedBtnLasermarkCancel)
	ON_BN_CLICKED(IDC_BTN_LASERMARK_UP, &SettingLaser::OnBnClickedBtnLasermarkUp)
	ON_BN_CLICKED(IDC_BTN_LASERMARK_DOWN, &SettingLaser::OnBnClickedBtnLasermarkDown)
	ON_BN_CLICKED(IDC_BTN_LASERMARK_LEFT, &SettingLaser::OnBnClickedBtnLasermarkLeft)
	ON_BN_CLICKED(IDC_BTN_LASERMARK_RIGHT, &SettingLaser::OnBnClickedBtnLasermarkRight)
	ON_BN_CLICKED(IDC_BTN_LASERMARK_MEASURE, &SettingLaser::OnBnClickedBtnLasermarkMeasure)
	ON_BN_CLICKED(IDC_BTN_LASERMARK_CLEAR, &SettingLaser::OnBnClickedBtnLasermarkClear)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_OFFSET, &SettingLaser::OnBnClickedBtnOffset)
END_MESSAGE_MAP()


// SettingLaser 메시지 처리기


int SettingLaser::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH SettingLaser::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL SettingLaser::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	GetDlgItem(IDC_BTN_OFFSET)->MoveWindow(10, 10, 60, 25);

	GetDlgItem(IDC_PIC_LASER)->MoveWindow(10, 40, 280, 120);

	GetDlgItem(IDC_STATIC_LASER_SPEED)->MoveWindow(10, 170, 110, 20);
	GetDlgItem(IDC_STATIC_LASER_HZ)->MoveWindow(10, 200, 110, 20);
	GetDlgItem(IDC_STATIC_LASER_SIZE)->MoveWindow(10, 230, 110, 20);
	GetDlgItem(IDC_STATIC_LASER_POWER)->MoveWindow(10, 260, 110, 20);
	GetDlgItem(IDC_STATIC_DFOCUS)->MoveWindow(10, 290, 110, 20);

	GetDlgItem(IDC_EDIT_LASER_SPEED)->MoveWindow(130, 170, 40, 20);
	GetDlgItem(IDC_EDIT_LASER_HZ)->MoveWindow(130, 200, 40, 20);
	GetDlgItem(IDC_EDIT_LASER_SIZE)->MoveWindow(130, 230, 40, 20);
	GetDlgItem(IDC_EDIT_LASER_POWER)->MoveWindow(130, 260, 40, 20);
	GetDlgItem(IDC_EDIT_DFOCUS)->MoveWindow(130, 290, 40, 20);

	GetDlgItem(IDC_BTN_CALCULATION)->MoveWindow(190, 170, 50, 20);
	GetDlgItem(IDC_BTN_CLEAR)->MoveWindow(250, 170, 50, 20);
	GetDlgItem(IDC_STATIC_PTP)->MoveWindow(190, 200, 60, 20);
	GetDlgItem(IDC_STATIC_OVERLAP_RATE)->MoveWindow(190, 230, 60, 20);
	GetDlgItem(IDC_STATIC_ENERGY)->MoveWindow(190, 260, 40, 20);
	GetDlgItem(IDC_STATIC_SPOT_ERROR)->MoveWindow(190, 290, 60, 20);

	GetDlgItem(IDC_STATIC_PTP_VALUE)->MoveWindow(250, 200, 50, 20);
	GetDlgItem(IDC_STATIC_OVERLAP_RATE_VALUE)->MoveWindow(250, 230, 50, 20);
	GetDlgItem(IDC_STATIC_ENERGY_VALUE)->MoveWindow(240, 260, 60, 20);
	GetDlgItem(IDC_STATIC_SPOT_ERROR_VALUE)->MoveWindow(250, 290, 50, 20);

	GetDlgItem(IDC_GRP_MEASURE)->MoveWindow(320, 240, 280, 80);
	GetDlgItem(IDC_STATIC_LASERMARK_MEASURE_1)->MoveWindow(380, 260, 70, 20);
	GetDlgItem(IDC_STATIC_LASERMARK_MEASURE_2)->MoveWindow(450, 260, 70, 20);
	GetDlgItem(IDC_STATIC_LASERMARK_MEASURE_3)->MoveWindow(520, 260, 70, 20);
	GetDlgItem(IDC_STATIC_LASERMARK_MEASURE_VALUE_1)->MoveWindow(380, 290, 70, 20);
	GetDlgItem(IDC_STATIC_LASERMARK_MEASURE_VALUE_2)->MoveWindow(450, 290, 70, 20);
	GetDlgItem(IDC_STATIC_LASERMARK_MEASURE_VALUE_3)->MoveWindow(520, 290, 70, 20);

	GetDlgItem(IDC_BTN_LASERMARK_MEASURE)->MoveWindow(330, 260, 50, 20);
	GetDlgItem(IDC_BTN_LASERMARK_CLEAR)->MoveWindow(330, 290, 50, 20);

	GetDlgItem(IDC_GRP_MARK)->MoveWindow(360, 20, 240, 210);
	GetDlgItem(IDC_BTN_LASERMARK_ENROLL)->MoveWindow(380, 50, 70, 20);
	GetDlgItem(IDC_BTN_LASERMARK_APPLY)->MoveWindow(380, 80, 70, 20);
	GetDlgItem(IDC_BTN_LASERMARK_CANCEL)->MoveWindow(380, 110, 70, 20);
	GetDlgItem(IDC_BTN_LASERMARK_UP)->MoveWindow(405, 150, 20, 20);
	GetDlgItem(IDC_BTN_LASERMARK_LEFT)->MoveWindow(385, 170, 20, 20);
	GetDlgItem(IDC_BTN_LASERMARK_RIGHT)->MoveWindow(425, 170, 20, 20);
	GetDlgItem(IDC_BTN_LASERMARK_DOWN)->MoveWindow(405, 190, 20, 20);
	GetDlgItem(IDC_PIC_LASERMARK)->MoveWindow(470, 70, 120, 120);
	GetDlgItem(IDC_STATIC_LASERMARK_MATCHRATE)->MoveWindow(470, 190, 60, 20);
	GetDlgItem(IDC_EDIT_LASERMARK_MATCHRATE)->MoveWindow(530, 190, 60, 20);



	HFONT staticFont;
	staticFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_GRP_MARK)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LASERMARK_MATCHRATE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_GRP_MEASURE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LASERMARK_MEASURE_1)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LASERMARK_MEASURE_2)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LASERMARK_MEASURE_3)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LASERMARK_MEASURE_VALUE_1)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LASERMARK_MEASURE_VALUE_2)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LASERMARK_MEASURE_VALUE_3)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);

	HFONT staticsmallFont;
	staticsmallFont = CreateFont(14, 5, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_STATIC_LASER_SPEED)->SendMessage(WM_SETFONT, (WPARAM)staticsmallFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LASER_HZ)->SendMessage(WM_SETFONT, (WPARAM)staticsmallFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LASER_SIZE)->SendMessage(WM_SETFONT, (WPARAM)staticsmallFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LASER_POWER)->SendMessage(WM_SETFONT, (WPARAM)staticsmallFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_DFOCUS)->SendMessage(WM_SETFONT, (WPARAM)staticsmallFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_PTP)->SendMessage(WM_SETFONT, (WPARAM)staticsmallFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_PTP_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticsmallFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_OVERLAP_RATE)->SendMessage(WM_SETFONT, (WPARAM)staticsmallFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_OVERLAP_RATE_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticsmallFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ENERGY)->SendMessage(WM_SETFONT, (WPARAM)staticsmallFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ENERGY_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticsmallFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_SPOT_ERROR)->SendMessage(WM_SETFONT, (WPARAM)staticsmallFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_SPOT_ERROR_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticsmallFont, (LPARAM)TRUE);

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

	GetDlgItem(IDC_BTN_CALCULATION)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_CLEAR)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_LASERMARK_ENROLL)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_LASERMARK_APPLY)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_LASERMARK_CANCEL)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_LASERMARK_UP)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_LASERMARK_LEFT)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_LASERMARK_RIGHT)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_LASERMARK_DOWN)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_LASERMARK_MEASURE)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_LASERMARK_CLEAR)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_OFFSET)->SetFont(btnFont);

	pen_white.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	pen_red.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	m_edit_laser_speed.SetWindowTextW(_T("2000"));
	m_edit_laser_hz.SetWindowTextW(_T("500"));
	m_edit_laser_size.SetWindowTextW(_T("0.02"));
	m_edit_laser_power.SetWindowTextW(_T("30"));
	m_edit_dfocus.SetWindowTextW(_T("1"));

	mMarkTracker.m_nStyle = 0;
	mMarkTracker.m_nStyle |= CRectTracker::dottedLine;
	mMarkTracker.m_nStyle |= CRectTracker::resizeOutside;

	GetDlgItem(IDC_BTN_LASERMARK_ENROLL)->EnableWindow(true);
	GetDlgItem(IDC_BTN_LASERMARK_APPLY)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LASERMARK_CANCEL)->EnableWindow(false);

	GetDlgItem(IDC_BTN_LASERMARK_UP)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LASERMARK_DOWN)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LASERMARK_LEFT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LASERMARK_RIGHT)->EnableWindow(false);


	SetTimer(1, 1, NULL);

	bChkAlarm = false;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL SettingLaser::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}

void SettingLaser::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CClientDC dcPic(GetDlgItem(IDC_PIC_LASER));

	dcPic.SelectStockObject(BLACK_BRUSH);
	dcPic.Rectangle(0, 0, 280, 120);

}


void SettingLaser::OnBnClickedBtnCalculation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();


	CClientDC dc(GetDlgItem(IDC_PIC_LASER));

	dc.SelectObject(pen_white);
	dc.SelectStockObject(BLACK_BRUSH);
	dc.Rectangle(0, 0, 280, 120);

	dc.SelectObject(pen_red);
	dc.SelectStockObject(NULL_BRUSH);

	m_edit_laser_speed.GetWindowTextW(strValue);
	dScanSpeed = _wtof(strValue);

	m_edit_laser_hz.GetWindowTextW(strValue);
	dHz = _wtof(strValue) * 1000;

	m_edit_laser_size.GetWindowTextW(strValue);
	dSpotSize = _wtof(strValue);

	m_edit_laser_power.GetWindowTextW(strValue);
	dLaserPower = _wtof(strValue);

	m_edit_dfocus.GetWindowTextW(strValue);
	dDFocus = _wtof(strValue);

	dDFocus = abs(dDFocus);

	dPTP = dScanSpeed / dHz;
	strValue.Format(_T("%.3fmm"), dPTP);
	GetDlgItem(IDC_STATIC_PTP_VALUE)->SetWindowTextW(strValue);

	dOverlapRate = ((dSpotSize - (dScanSpeed / dHz)) / dSpotSize) * 100;
	strValue.Format(_T("%.2f%%"), dOverlapRate);
	GetDlgItem(IDC_STATIC_OVERLAP_RATE_VALUE)->SetWindowTextW(strValue);

	dEnergy = (dLaserPower / dHz) / (M_PI * pow((dSpotSize / 10) / 2, 2));
	strValue.Format(_T("%.2fJ/cm2"), dEnergy);
	GetDlgItem(IDC_STATIC_ENERGY_VALUE)->SetWindowTextW(strValue);

	dSpotError = (14 / 528.3) * dDFocus * 1000;
	strValue.Format(_T("%.2f㎛"), dSpotError);
	GetDlgItem(IDC_STATIC_SPOT_ERROR_VALUE)->SetWindowTextW(strValue);


	int nCircleStart;
	int nCircleEnd;

	dc.Ellipse(10, 10, 110, 110);

	nCircleStart = 10;
	nCircleEnd = nCircleStart + 100;

	if (dOverlapRate < 99)
	{
		while (1)
		{
			nCircleStart += (100 - dOverlapRate);
			nCircleEnd = nCircleStart + 100;

			if (nCircleEnd > 270)
				break;

			dc.Ellipse(nCircleStart, 10, nCircleEnd, 110);
		}
	}

	else
	{
		pDlg->dlgPopupAlarm->DisplayMessage(_T("설정 값 확인"));
		pDlg->dlgPopupAlarm->ShowWindow(SW_SHOW);

		bChkAlarm = true;
	}	
}


void SettingLaser::OnBnClickedBtnClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CClientDC dc(GetDlgItem(IDC_PIC_LASER));

	dc.SelectObject(pen_white);
	dc.SelectStockObject(BLACK_BRUSH);
	dc.Rectangle(0, 0, 280, 120);

	GetDlgItem(IDC_STATIC_PTP_VALUE)->SetWindowTextW(_T("0.000mm"));
	GetDlgItem(IDC_STATIC_OVERLAP_RATE_VALUE)->SetWindowTextW(_T("00.00%"));
	GetDlgItem(IDC_STATIC_ENERGY_VALUE)->SetWindowTextW(_T("00.00J/cm2"));
	GetDlgItem(IDC_STATIC_SPOT_ERROR_VALUE)->SetWindowTextW(_T("00.00㎛"));
}


void SettingLaser::OnBnClickedBtnLasermarkEnroll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	rectMark = { 100, 100, 200, 200 };
	mMarkTracker.m_rect = rectMark;

	bChkMarkLaser = true;

	GetDlgItem(IDC_BTN_LASERMARK_ENROLL)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LASERMARK_APPLY)->EnableWindow(true);
	GetDlgItem(IDC_BTN_LASERMARK_CANCEL)->EnableWindow(true);

	GetDlgItem(IDC_BTN_LASERMARK_UP)->EnableWindow(true);
	GetDlgItem(IDC_BTN_LASERMARK_DOWN)->EnableWindow(true);
	GetDlgItem(IDC_BTN_LASERMARK_LEFT)->EnableWindow(true);
	GetDlgItem(IDC_BTN_LASERMARK_RIGHT)->EnableWindow(true);
}


void SettingLaser::OnBnClickedBtnLasermarkApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	GetDlgItem(IDC_BTN_LASERMARK_ENROLL)->EnableWindow(true);
	GetDlgItem(IDC_BTN_LASERMARK_APPLY)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LASERMARK_CANCEL)->EnableWindow(false);

	GetDlgItem(IDC_BTN_LASERMARK_UP)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LASERMARK_DOWN)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LASERMARK_LEFT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LASERMARK_RIGHT)->EnableWindow(false);

	pDlg->ImageSave(4, false);
	pDlg->MarkExtraction(5);

	bChkMarkLaser = false;

	rectMark = { 0, 0, 0, 0 };
	mMarkTracker.m_rect = rectMark;
}


void SettingLaser::OnBnClickedBtnLasermarkCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	GetDlgItem(IDC_BTN_LASERMARK_ENROLL)->EnableWindow(true);
	GetDlgItem(IDC_BTN_LASERMARK_APPLY)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LASERMARK_CANCEL)->EnableWindow(false);

	GetDlgItem(IDC_BTN_LASERMARK_UP)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LASERMARK_DOWN)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LASERMARK_LEFT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LASERMARK_RIGHT)->EnableWindow(false);

	bChkMarkLaser = false;

	rectMark = { 0, 0, 0, 0 };
	mMarkTracker.m_rect = rectMark;
}


void SettingLaser::OnBnClickedBtnLasermarkUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void SettingLaser::OnBnClickedBtnLasermarkDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void SettingLaser::OnBnClickedBtnLasermarkLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void SettingLaser::OnBnClickedBtnLasermarkRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void SettingLaser::OnBnClickedBtnLasermarkMeasure()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	pDlg->ExcutionLaserCalibration();
}


void SettingLaser::OnBnClickedBtnLasermarkClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	pDlg->ChkFindLaser = false;
}


void SettingLaser::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	if (nIDEvent == 1)
	{
		if (bChkAlarm == true)
		{
			Sleep(2000);

			pDlg->dlgPopupAlarm->ShowWindow(SW_HIDE);
			bChkAlarm = false;
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void SettingLaser::OnBnClickedBtnOffset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();


	CRect rcManualAlign;
	GetWindowRect(rcManualAlign);

	rcManualAlign.top += 30;
	rcManualAlign.left += 100;
	rcManualAlign.right = rcManualAlign.left + 200;
	rcManualAlign.bottom = rcManualAlign.top + 250;

	dlgSettingHide.rcDialog = rcManualAlign;

	if (dlgSettingHide.DoModal() == IDOK)   // 다이얼로그가 종료될 때 반환되는 값을 검사, OK 버튼으로 종료되었을 경우 IDOK를 반환
	{
		CString strRegValue;

		strRegValue.Format(_T("%.3f"), dlgSettingHide.dModifyX);
		AfxGetApp()->WriteProfileStringW(_T("ALIGN"), _T("MODIFYX"), strRegValue);
		pDlg->dManualOffsetX = dlgSettingHide.dModifyX;

		strRegValue.Format(_T("%.3f"), dlgSettingHide.dModifyY);
		AfxGetApp()->WriteProfileStringW(_T("ALIGN"), _T("MODIFYY"), strRegValue);
		pDlg->dManualOffsetY = dlgSettingHide.dModifyY;

		strRegValue.Format(_T("%.3f"), dlgSettingHide.dModifyT);
		AfxGetApp()->WriteProfileStringW(_T("ALIGN"), _T("MODIFYT"), strRegValue);
		pDlg->dManualOffsetT = dlgSettingHide.dModifyT;
	}

	else
	{
	}

}

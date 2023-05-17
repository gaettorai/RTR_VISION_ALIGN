// RVisionSetting.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "RVisionSetting.h"
#include "afxdialogex.h"

#include "RVisionDlg.h"

// RVisionSetting 대화 상자

IMPLEMENT_DYNAMIC(RVisionSetting, CDialogEx)

RVisionSetting::RVisionSetting(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RVISION_SETTING, pParent)
{

}

RVisionSetting::~RVisionSetting()
{
}

void RVisionSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_CAMERA, m_btn_camera);
	DDX_Control(pDX, IDC_BTN_ALIGN, m_btn_align);
	DDX_Control(pDX, IDC_BTN_FC, m_btn_fc);
	DDX_Control(pDX, IDC_BTN_ALIGNMARK, m_btn_alignmark);
	DDX_Control(pDX, IDC_BTN_LASER, m_btn_laser);
}


BEGIN_MESSAGE_MAP(RVisionSetting, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_CAMERA, &RVisionSetting::OnBnClickedBtnCamera)
	ON_BN_CLICKED(IDC_BTN_ALIGN, &RVisionSetting::OnBnClickedBtnAlign)
	ON_BN_CLICKED(IDC_BTN_FC, &RVisionSetting::OnBnClickedBtnFc)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_BTN_ALIGNMARK, &RVisionSetting::OnBnClickedBtnAlignmark)
	ON_BN_CLICKED(IDC_BTN_LASER, &RVisionSetting::OnBnClickedBtnLaser)
END_MESSAGE_MAP()


// RVisionSetting 메시지 처리기


int RVisionSetting::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH RVisionSetting::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL RVisionSetting::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL RVisionSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	GetDlgItem(IDC_BTN_CAMERA)->MoveWindow(1, CamHeight / 4, 80, 20);
	GetDlgItem(IDC_BTN_ALIGN)->MoveWindow(81, CamHeight / 4, 80, 20);
	GetDlgItem(IDC_BTN_ALIGNMARK)->MoveWindow(161, CamHeight / 4, 80, 20);
	GetDlgItem(IDC_BTN_FC)->MoveWindow(241, CamHeight / 4, 80, 20);
	GetDlgItem(IDC_BTN_LASER)->MoveWindow(321, CamHeight / 4, 80, 20);

	GetDlgItem(IDC_PIC_SETTING)->MoveWindow(0, 0, WindowWidth, CamHeight / 4);

	dlgSettingCamera = new SettingCamera;
	dlgSettingCamera->Create(IDD_SETTING_CAMERA, this);
	dlgSettingCamera->MoveWindow(0, CamHeight / 4 + 20, WindowWidth, 330);
	dlgSettingCamera->ShowWindow(SW_SHOW);

	dlgSettingAlign = new SettingAlign;
	dlgSettingAlign->Create(IDD_SETTING_ALIGN, this);
	dlgSettingAlign->MoveWindow(0, CamHeight / 4 + 20, WindowWidth, 330);
	dlgSettingAlign->ShowWindow(SW_HIDE);

	dlgSettingAlignMark = new SettingAlignMark;
	dlgSettingAlignMark->Create(IDD_SETTING_ALIGNMARK, this);
	dlgSettingAlignMark->MoveWindow(0, CamHeight / 4 + 20, WindowWidth, 330);
	dlgSettingAlignMark->ShowWindow(SW_HIDE);

	dlgSettingFC = new SettingFC;
	dlgSettingFC->Create(IDD_SETTING_FC, this);
	dlgSettingFC->MoveWindow(0, CamHeight / 4 + 20, WindowWidth, 330);
	dlgSettingFC->ShowWindow(SW_HIDE);

	dlgSettingLaser = new SettingLaser;
	dlgSettingLaser->Create(IDD_SETTING_LASER, this);
	dlgSettingLaser->MoveWindow(0, CamHeight / 4 + 20, WindowWidth, 330);
	dlgSettingLaser->ShowWindow(SW_HIDE);

	CFont* btnFont;
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

	GetDlgItem(IDC_BTN_CAMERA)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_ALIGN)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_ALIGNMARK)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_FC)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_LASER)->SetFont(btnFont);

	m_btn_camera.EnableWindowsTheming(FALSE);
	m_btn_align.EnableWindowsTheming(FALSE);
	m_btn_alignmark.EnableWindowsTheming(FALSE);
	m_btn_fc.EnableWindowsTheming(FALSE);
	m_btn_laser.EnableWindowsTheming(FALSE);

	m_btn_camera.SetFaceColor(ColorGreen);
	m_btn_align.SetFaceColor(ColorBasic);
	m_btn_alignmark.SetFaceColor(ColorBasic);
	m_btn_fc.SetFaceColor(ColorBasic);
	m_btn_laser.SetFaceColor(ColorBasic);

	// 0 : Camera, 1 : ALIGN, 2 : FC
	SelectSetting = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL RVisionSetting::PreTranslateMessage(MSG* pMsg)
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


void RVisionSetting::OnBnClickedBtnCamera()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_camera.SetFaceColor(ColorGreen);
	m_btn_align.SetFaceColor(ColorBasic);
	m_btn_alignmark.SetFaceColor(ColorBasic);
	m_btn_fc.SetFaceColor(ColorBasic);
	m_btn_laser.SetFaceColor(ColorBasic);

	dlgSettingCamera->ShowWindow(SW_SHOW);
	dlgSettingAlign->ShowWindow(SW_HIDE);
	dlgSettingAlignMark->ShowWindow(SW_HIDE);
	dlgSettingFC->ShowWindow(SW_HIDE);
	dlgSettingLaser->ShowWindow(SW_HIDE);

	dlgSettingCamera->SelectCam = 0;

	SelectSetting = 0;
}


void RVisionSetting::OnBnClickedBtnAlign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_camera.SetFaceColor(ColorBasic);
	m_btn_align.SetFaceColor(ColorGreen);
	m_btn_alignmark.SetFaceColor(ColorBasic);
	m_btn_fc.SetFaceColor(ColorBasic);
	m_btn_laser.SetFaceColor(ColorBasic);

	dlgSettingCamera->ShowWindow(SW_HIDE);
	dlgSettingAlign->ShowWindow(SW_SHOW);
	dlgSettingAlignMark->ShowWindow(SW_HIDE);
	dlgSettingFC->ShowWindow(SW_HIDE);
	dlgSettingLaser->ShowWindow(SW_HIDE);

	dlgSettingAlign->SelectCam = 0;

	SelectSetting = 1;
}


void RVisionSetting::OnBnClickedBtnAlignmark()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_camera.SetFaceColor(ColorBasic);
	m_btn_align.SetFaceColor(ColorBasic);
	m_btn_alignmark.SetFaceColor(ColorGreen);
	m_btn_fc.SetFaceColor(ColorBasic);
	m_btn_laser.SetFaceColor(ColorBasic);

	dlgSettingCamera->ShowWindow(SW_HIDE);
	dlgSettingAlign->ShowWindow(SW_HIDE);
	dlgSettingAlignMark->ShowWindow(SW_SHOW);
	dlgSettingFC->ShowWindow(SW_HIDE);
	dlgSettingLaser->ShowWindow(SW_HIDE);

	dlgSettingAlignMark->SelectCam = 0;

	SelectSetting = 2;
}


void RVisionSetting::OnBnClickedBtnFc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_camera.SetFaceColor(ColorBasic);
	m_btn_align.SetFaceColor(ColorBasic);
	m_btn_alignmark.SetFaceColor(ColorBasic);
	m_btn_fc.SetFaceColor(ColorGreen);
	m_btn_laser.SetFaceColor(ColorBasic);

	dlgSettingCamera->ShowWindow(SW_HIDE);
	dlgSettingAlign->ShowWindow(SW_HIDE);
	dlgSettingAlignMark->ShowWindow(SW_HIDE);
	dlgSettingFC->ShowWindow(SW_SHOW);
	dlgSettingLaser->ShowWindow(SW_HIDE);

	dlgSettingCamera->SelectCam = 4;

	SelectSetting = 3;
}


void RVisionSetting::OnBnClickedBtnLaser()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btn_camera.SetFaceColor(ColorBasic);
	m_btn_align.SetFaceColor(ColorBasic);
	m_btn_alignmark.SetFaceColor(ColorBasic);
	m_btn_fc.SetFaceColor(ColorBasic);
	m_btn_laser.SetFaceColor(ColorGreen);

	dlgSettingCamera->ShowWindow(SW_HIDE);
	dlgSettingAlign->ShowWindow(SW_HIDE);
	dlgSettingAlignMark->ShowWindow(SW_HIDE);
	dlgSettingFC->ShowWindow(SW_HIDE);
	dlgSettingLaser->ShowWindow(SW_SHOW);

	dlgSettingCamera->SelectCam = 4;

	SelectSetting = 4;
}


void RVisionSetting::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CRect recctSetting;
	((CStatic*)GetDlgItem(IDC_PIC_SETTING))->GetWindowRect(&recctSetting);

	ScreenToClient(&recctSetting);

	if (recctSetting.PtInRect(point)) // 픽쳐 컨트롤의 사각형 영역에 마우스 클릭 좌표(point) 가 있으면...TRUE
	{
		// ALIGN SETTING(ROI영역)
		if (SelectSetting == 1)
		{
			if (dlgSettingAlign->mRoiTracker.HitTest(point) > 0)
			{
				if (dlgSettingAlign->mRoiTracker.Track(this, point, true))
				{
					dlgSettingAlign->mRoiTracker.m_rect.NormalizeRect();

					CString strValue;

					strValue.Format(_T("%d"), dlgSettingAlign->mRoiTracker.m_rect.left * 4);
					dlgSettingAlign->GetDlgItem(IDC_EDIT_EDGE_ROI_START_X)->SetWindowTextW(strValue);

					strValue.Format(_T("%d"), dlgSettingAlign->mRoiTracker.m_rect.top * 4);
					dlgSettingAlign->GetDlgItem(IDC_EDIT_EDGE_ROI_START_Y)->SetWindowTextW(strValue);

					strValue.Format(_T("%d"), dlgSettingAlign->mRoiTracker.m_rect.right * 4);
					dlgSettingAlign->GetDlgItem(IDC_EDIT_EDGE_ROI_END_X)->SetWindowTextW(strValue);

					strValue.Format(_T("%d"), dlgSettingAlign->mRoiTracker.m_rect.bottom * 4);
					dlgSettingAlign->GetDlgItem(IDC_EDIT_EDGE_ROI_END_Y)->SetWindowTextW(strValue);
				}
			}
		}

		// ALIGN MARK SETTING
		else if (SelectSetting == 2)
		{
			if (dlgSettingAlignMark->mMarkTracker.HitTest(point) > 0)
			{
				if (dlgSettingAlignMark->mMarkTracker.Track(this, point, true))
					dlgSettingAlignMark->mMarkTracker.m_rect.NormalizeRect();
			}

		}

		// FIELD CORRECTION MARK SETTING
		else if (SelectSetting == 3)
		{
			if (dlgSettingFC->mMarkTracker.HitTest(point) > 0)
			{
				if (dlgSettingFC->mMarkTracker.Track(this, point, true))
					dlgSettingFC->mMarkTracker.m_rect.NormalizeRect();
			}
		}
		
		else if (SelectSetting == 4)
		{
			if (dlgSettingLaser->mMarkTracker.HitTest(point) > 0)
			{
				if (dlgSettingLaser->mMarkTracker.Track(this, point, true))
					dlgSettingLaser->mMarkTracker.m_rect.NormalizeRect();
			}
		}
	}

	else  // 픽쳐 컨트롤 영역에 마우스 클릭 좌표가 없으면... FALSE
	{

	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


BOOL RVisionSetting::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (dlgSettingFC->mMarkTracker.SetCursor(pWnd, nHitTest))
		return TRUE;

	if (dlgSettingAlign->mRoiTracker.SetCursor(pWnd, nHitTest))
		return TRUE;

	if (dlgSettingAlignMark->mMarkTracker.SetCursor(pWnd, nHitTest))
		return TRUE;

	if (dlgSettingLaser->mMarkTracker.SetCursor(pWnd, nHitTest))
		return TRUE;

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


BOOL RVisionSetting::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (zDelta > 0)
	{
		// align
		if (SelectSetting == 2)
		{
			if (dlgSettingAlignMark->bChkMarkAlign == true)
			{
				dlgSettingAlignMark->mMarkTracker.m_rect.top -= 1;
				dlgSettingAlignMark->mMarkTracker.m_rect.bottom += 1;
				dlgSettingAlignMark->mMarkTracker.m_rect.left -= 1;
				dlgSettingAlignMark->mMarkTracker.m_rect.right += 1;
			}
		}

		// fc
		else if (SelectSetting == 3)
		{
			if (dlgSettingFC->bChkMarkFC == true)
			{
				dlgSettingFC->mMarkTracker.m_rect.top -= 1;
				dlgSettingFC->mMarkTracker.m_rect.bottom += 1;
				dlgSettingFC->mMarkTracker.m_rect.left -= 1;
				dlgSettingFC->mMarkTracker.m_rect.right += 1;
			}
		}
		
		// laser mark
		else if (SelectSetting == 4)
		{
			if (dlgSettingLaser->bChkMarkLaser == true)
			{
				dlgSettingLaser->mMarkTracker.m_rect.top -= 1;
				dlgSettingLaser->mMarkTracker.m_rect.bottom += 1;
				dlgSettingLaser->mMarkTracker.m_rect.left -= 1;
				dlgSettingLaser->mMarkTracker.m_rect.right += 1;
			}
		}
	}



	else if (zDelta < 0)
	{
		// align
		if (SelectSetting == 2)
		{
			if (dlgSettingAlignMark->bChkMarkAlign == true)
			{
				dlgSettingAlignMark->mMarkTracker.m_rect.top += 1;
				dlgSettingAlignMark->mMarkTracker.m_rect.bottom -= 1;
				dlgSettingAlignMark->mMarkTracker.m_rect.left += 1;
				dlgSettingAlignMark->mMarkTracker.m_rect.right -= 1;
			}
		}

		// fc
		else if (SelectSetting == 3)
		{
			if (dlgSettingFC->bChkMarkFC == true)
			{
				dlgSettingFC->mMarkTracker.m_rect.top += 1;
				dlgSettingFC->mMarkTracker.m_rect.bottom -= 1;
				dlgSettingFC->mMarkTracker.m_rect.left += 1;
				dlgSettingFC->mMarkTracker.m_rect.right -= 1;
			}
		}

		// laser
		else if (SelectSetting == 4)
		{
			if (dlgSettingLaser->bChkMarkLaser == true)
			{
				dlgSettingLaser->mMarkTracker.m_rect.top += 1;
				dlgSettingLaser->mMarkTracker.m_rect.bottom -= 1;
				dlgSettingLaser->mMarkTracker.m_rect.left += 1;
				dlgSettingLaser->mMarkTracker.m_rect.right -= 1;
			}
		}
	}



	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

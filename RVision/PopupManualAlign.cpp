// PopupManualAlign.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "PopupManualAlign.h"
#include "afxdialogex.h"

#include "RVisionDlg.h"

// PopupManualAlign 대화 상자

IMPLEMENT_DYNAMIC(PopupManualAlign, CDialogEx)

extern CameraParameter stCamera;
extern AlignParameter	stAlign;
extern EdgeAlignParameter stEdgeAlign;
extern MarkAlignParameter stMarkAlign;

PopupManualAlign::PopupManualAlign(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POPUP_MANUALALIGN, pParent)
{

}

PopupManualAlign::~PopupManualAlign()
{
}

void PopupManualAlign::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRP_POINT, m_grp_point);
	DDX_Control(pDX, IDC_GRP_MODIFY, m_grp_modify);
	DDX_Control(pDX, IDC_BTN_APPLY, m_btn_apply);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btn_cancel);
	DDX_Control(pDX, IDC_BTN_ALIGN1, m_btn_align1);
	DDX_Control(pDX, IDC_BTN_ALIGN2, m_btn_align2);
	DDX_Control(pDX, IDC_BTN_ALIGN3, m_btn_align3);
	DDX_Control(pDX, IDC_BTN_ALIGN4, m_btn_align4);
	DDX_Control(pDX, IDC_PIC_MANUALALIGN, m_pic_manualalign);
}


BEGIN_MESSAGE_MAP(PopupManualAlign, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_MANUALALIGN, &PopupManualAlign::OnBnClickedBtnManualalign)
	ON_BN_CLICKED(IDOK, &PopupManualAlign::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &PopupManualAlign::OnBnClickedCancel)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BTN_APPLY, &PopupManualAlign::OnBnClickedBtnApply)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &PopupManualAlign::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BTN_ALIGN1, &PopupManualAlign::OnBnClickedBtnAlign1)
	ON_BN_CLICKED(IDC_BTN_ALIGN2, &PopupManualAlign::OnBnClickedBtnAlign2)
	ON_BN_CLICKED(IDC_BTN_ALIGN3, &PopupManualAlign::OnBnClickedBtnAlign3)
	ON_BN_CLICKED(IDC_BTN_ALIGN4, &PopupManualAlign::OnBnClickedBtnAlign4)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_UP, &PopupManualAlign::OnBnClickedBtnUp)
	ON_BN_CLICKED(IDC_BTN_DOWN, &PopupManualAlign::OnBnClickedBtnDown)
	ON_BN_CLICKED(IDC_BTN_LEFT, &PopupManualAlign::OnBnClickedBtnLeft)
	ON_BN_CLICKED(IDC_BTN_RIGHT, &PopupManualAlign::OnBnClickedBtnRight)
END_MESSAGE_MAP()


// PopupManualAlign 메시지 처리기


int PopupManualAlign::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	ChkActive = false;

	return 0;
}


HBRUSH PopupManualAlign::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	// TODO:  여기서 DC의 특성을 변경합니다.
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_MODIFY_X_JUDGE)
		{
			if (ChkNG_X == true)
				pDC->SetTextColor(RGB(0, 176, 80));

			else
				pDC->SetTextColor(RGB(255, 0, 0));
		}

		if (pWnd->GetDlgCtrlID() == IDC_STATIC_MODIFY_Y_JUDGE)
		{
			if (ChkNG_Y == true)
				pDC->SetTextColor(RGB(0, 176, 80));

			else
				pDC->SetTextColor(RGB(255, 0, 0));
		}

		if (pWnd->GetDlgCtrlID() == IDC_STATIC_MODIFY_T_JUDGE)
		{
			if (ChkNG_T == true)
				pDC->SetTextColor(RGB(0, 176, 80));

			else
				pDC->SetTextColor(RGB(255, 0, 0));
		}
	}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL PopupManualAlign::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL PopupManualAlign::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	MoveWindow(rcDialog);

	dlgDrawManualAlign = new DrawManualAlign;
	dlgDrawManualAlign->Create(IDD_DRAW_MANUALALIGN, this);
	dlgDrawManualAlign->MoveWindow(0, 50, WindowWidth, CamHeight / 4);
	dlgDrawManualAlign->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BTN_ALIGN1)->MoveWindow(0, 0, 80, 20);
	GetDlgItem(IDC_BTN_ALIGN2)->MoveWindow(80, 0, 80, 20);
	GetDlgItem(IDC_BTN_ALIGN3)->MoveWindow(160, 0, 80, 20);
	GetDlgItem(IDC_BTN_ALIGN4)->MoveWindow(240, 0, 80, 20);
	GetDlgItem(IDC_PIC_MANUALALIGN)->MoveWindow(0, 20, WindowWidth, CamHeight / 4);

	GetDlgItem(IDC_BTN_MANUALALIGN)->MoveWindow(10, CamHeight / 4 + 40, 60, 30);

	GetDlgItem(IDC_BTN_UP)->MoveWindow(30, CamHeight / 4 + 40 + 40, 20, 20);
	GetDlgItem(IDC_BTN_LEFT)->MoveWindow(10, CamHeight / 4 + 40 + 60, 20, 20);
	GetDlgItem(IDC_BTN_RIGHT)->MoveWindow(50, CamHeight / 4 + 40 + 60, 20, 20);
	GetDlgItem(IDC_BTN_DOWN)->MoveWindow(30, CamHeight / 4 + 40 + 80, 20, 20);

	GetDlgItem(IDC_BTN_APPLY)->MoveWindow(10, CamHeight / 4 + 40 + 120, 60, 30);
	GetDlgItem(IDC_BTN_CANCEL)->MoveWindow(10, CamHeight / 4 + 40 + 160, 60, 30);

	GetDlgItem(IDC_GRP_POINT)->MoveWindow(100, CamHeight / 4 + 40, 240, 190);
	GetDlgItem(IDC_STATIC_POINT_X)->MoveWindow(200, CamHeight / 4 + 40 + 20, 50, 30);
	GetDlgItem(IDC_STATIC_POINT_Y)->MoveWindow(270, CamHeight / 4 + 40 + 20, 50, 30);

	GetDlgItem(IDC_STATIC_ALIGN_1)->MoveWindow(120, CamHeight / 4 + 40 + 20 + 30, 60, 30);
	GetDlgItem(IDC_STATIC_ALIGN_2)->MoveWindow(120, CamHeight / 4 + 40 + 20 + 60, 60, 30);
	GetDlgItem(IDC_STATIC_ALIGN_3)->MoveWindow(120, CamHeight / 4 + 40 + 20 + 90, 60, 30);
	GetDlgItem(IDC_STATIC_ALIGN_4)->MoveWindow(120, CamHeight / 4 + 40 + 20 + 120, 60, 30);

	GetDlgItem(IDC_STATIC_ALIGN_1_X)->MoveWindow(200, CamHeight / 4 + 40 + 20 + 30, 50, 30);
	GetDlgItem(IDC_STATIC_ALIGN_1_Y)->MoveWindow(270, CamHeight / 4 + 40 + 20 + 30, 50, 30);
	GetDlgItem(IDC_STATIC_ALIGN_2_X)->MoveWindow(200, CamHeight / 4 + 40 + 20 + 60, 50, 30);
	GetDlgItem(IDC_STATIC_ALIGN_2_Y)->MoveWindow(270, CamHeight / 4 + 40 + 20 + 60, 50, 30);
	GetDlgItem(IDC_STATIC_ALIGN_3_X)->MoveWindow(200, CamHeight / 4 + 40 + 20 + 90, 50, 30);
	GetDlgItem(IDC_STATIC_ALIGN_3_Y)->MoveWindow(270, CamHeight / 4 + 40 + 20 + 90, 50, 30);
	GetDlgItem(IDC_STATIC_ALIGN_4_X)->MoveWindow(200, CamHeight / 4 + 40 + 20 + 120, 50, 30);
	GetDlgItem(IDC_STATIC_ALIGN_4_Y)->MoveWindow(270, CamHeight / 4 + 40 + 20 + 120, 50, 30);

	GetDlgItem(IDC_GRP_MODIFY)->MoveWindow(350, CamHeight / 4 + 40, 230, 150);
	GetDlgItem(IDC_STATIC_MODIFY_X)->MoveWindow(370, CamHeight / 4 + 40 + 20 + 30, 60, 30);
	GetDlgItem(IDC_STATIC_MODIFY_Y)->MoveWindow(370, CamHeight / 4 + 40 + 20 + 60, 60, 30);
	GetDlgItem(IDC_STATIC_MODIFY_T)->MoveWindow(370, CamHeight / 4 + 40 + 20 + 90, 60, 30);

	GetDlgItem(IDC_STATIC_MODIFY_X_VALUE)->MoveWindow(450, CamHeight / 4 + 40 + 20 + 30, 60, 30);
	GetDlgItem(IDC_STATIC_MODIFY_Y_VALUE)->MoveWindow(450, CamHeight / 4 + 40 + 20 + 60, 60, 30);
	GetDlgItem(IDC_STATIC_MODIFY_T_VALUE)->MoveWindow(450, CamHeight / 4 + 40 + 20 + 90, 60, 30);

	GetDlgItem(IDC_STATIC_MODIFY_X_JUDGE)->MoveWindow(530, CamHeight / 4 + 40 + 20 + 30, 30, 30);
	GetDlgItem(IDC_STATIC_MODIFY_Y_JUDGE)->MoveWindow(530, CamHeight / 4 + 40 + 20 + 60, 30, 30);
	GetDlgItem(IDC_STATIC_MODIFY_T_JUDGE)->MoveWindow(530, CamHeight / 4 + 40 + 20 + 90, 30, 30);

	GetDlgItem(IDOK)->MoveWindow(450, CamHeight / 4 + 40 + 160, 60, 30);
	GetDlgItem(IDCANCEL)->MoveWindow(520, CamHeight / 4 + 40 + 160, 60, 30);


	HFONT staticFont;
	staticFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_STATIC_ALIGN_1)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_2)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_3)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_4)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MODIFY_X)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MODIFY_Y)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MODIFY_T)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MODIFY_X_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MODIFY_Y_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MODIFY_T_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_POINT_X)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_POINT_Y)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_1_X)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_1_Y)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_2_X)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_2_Y)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_3_X)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_3_Y)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_4_X)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_4_Y)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MODIFY_X_JUDGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MODIFY_Y_JUDGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MODIFY_T_JUDGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);

	CFont* btnFont;
	btnFont = new CFont;

	//폰트 생성
	btnFont->CreateFont(
		15,                            // 글자높이
		5,                            // 글자너비
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


	GetDlgItem(IDC_BTN_ALIGN1)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_ALIGN2)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_ALIGN3)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_ALIGN4)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_MANUALALIGN)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_APPLY)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_CANCEL)->SetFont(btnFont);
	GetDlgItem(IDOK)->SetFont(btnFont);
	GetDlgItem(IDCANCEL)->SetFont(btnFont);

	CFont* pFont = new CFont;
	pFont->CreateFont(20, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_GRP_POINT)->SetFont(pFont, TRUE);
	GetDlgItem(IDC_GRP_MODIFY)->SetFont(pFont, TRUE);

	GetDlgItem(IDC_BTN_UP)->EnableWindow(false);
	GetDlgItem(IDC_BTN_DOWN)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LEFT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_RIGHT)->EnableWindow(false);

	m_btn_apply.EnableWindow(FALSE);
	m_btn_cancel.EnableWindow(FALSE);

	AnimateWindow(200, AW_SLIDE | AW_BLEND);

	CString strValue;
	strValue.Format(_T("%.3fmm"), dModifyX);
	GetDlgItem(IDC_STATIC_MODIFY_X_VALUE)->SetWindowTextW(strValue);
	strValue.Format(_T("%.3fmm"), dModifyY);
	GetDlgItem(IDC_STATIC_MODIFY_Y_VALUE)->SetWindowTextW(strValue);
	strValue.Format(_T("%.6f˚"), dModifyT);
	GetDlgItem(IDC_STATIC_MODIFY_T_VALUE)->SetWindowTextW(strValue);

	dModifyX_result = dModifyX;
	dModifyY_result = dModifyY;
	dModifyT_result = dModifyT;

	DisplayAlignPoint();

	DisplayWindow();

	ChkActive = true;
	ChkClick = false;
	nClickCount = 0;

	ManualFirstPoint.x = stEdgeAlign.EdgeStart[0].x / 4;
	ManualFirstPoint.y = stEdgeAlign.EdgeStart[0].y / 4;

	ManualSecondPoint.x = stEdgeAlign.EdgeEnd[0].x / 4;
	ManualSecondPoint.y = stEdgeAlign.EdgeEnd[0].y / 4;

	ManualMarkPoint.x = AlignResult1.x / 4;
	ManualMarkPoint.y = AlignResult1.y / 4;

	DisplayJudge();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void PopupManualAlign::DisplayWindow()
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	m_btn_align1.EnableWindowsTheming(FALSE);
	m_btn_align2.EnableWindowsTheming(FALSE);
	m_btn_align3.EnableWindowsTheming(FALSE);
	m_btn_align4.EnableWindowsTheming(FALSE);

	m_btn_align1.EnableWindow(FALSE);
	m_btn_align2.EnableWindow(FALSE);
	m_btn_align3.EnableWindow(FALSE);
	m_btn_align4.EnableWindow(FALSE);

	if (pDlg->nSelecteAlignMethod == 1)
	{
		m_btn_align1.SetFaceColor(ColorGreen);
		m_btn_align2.SetFaceColor(ColorBasic);
		m_btn_align3.SetFaceColor(ColorBasic);
		m_btn_align4.SetFaceColor(ColorBasic);

		m_btn_align1.EnableWindow(TRUE);
		m_btn_align2.EnableWindow(TRUE);
		m_btn_align3.EnableWindow(TRUE);
		m_btn_align4.EnableWindow(TRUE);

		SelectCam = 0;
	}

	else if (pDlg->nSelecteAlignMethod == 2)
	{
		m_btn_align1.SetFaceColor(ColorGreen);
		m_btn_align2.SetFaceColor(ColorBasic);
		m_btn_align3.SetFaceColor(ColorBasic);
		m_btn_align4.SetFaceColor(ColorBasic);

		m_btn_align1.EnableWindow(TRUE);
		m_btn_align2.EnableWindow(TRUE);

		SelectCam = 0;
	}
	
	else if (pDlg->nSelecteAlignMethod == 3)
	{
		m_btn_align1.SetFaceColor(ColorBasic);
		m_btn_align2.SetFaceColor(ColorBasic);
		m_btn_align3.SetFaceColor(ColorGreen);
		m_btn_align4.SetFaceColor(ColorBasic);

		m_btn_align3.EnableWindow(TRUE);
		m_btn_align4.EnableWindow(TRUE);

		SelectCam = 2;
	}

	else if (pDlg->nSelecteAlignMethod == 4)
	{
		m_btn_align1.SetFaceColor(ColorGreen);
		m_btn_align2.SetFaceColor(ColorBasic);
		m_btn_align3.SetFaceColor(ColorBasic);
		m_btn_align4.SetFaceColor(ColorBasic);

		m_btn_align1.EnableWindow(TRUE);
		m_btn_align3.EnableWindow(TRUE);

		SelectCam = 0;
	}

	else if (pDlg->nSelecteAlignMethod == 5)
	{
		m_btn_align1.SetFaceColor(ColorBasic);
		m_btn_align2.SetFaceColor(ColorGreen);
		m_btn_align3.SetFaceColor(ColorBasic);
		m_btn_align4.SetFaceColor(ColorBasic);

		m_btn_align2.EnableWindow(TRUE);
		m_btn_align4.EnableWindow(TRUE);

		SelectCam = 1;
	}
}


void PopupManualAlign::DisplayAlignPoint()
{
	CString strValue;

	strValue.Format(_T("%d"), AlignResult1.x);
	GetDlgItem(IDC_STATIC_ALIGN_1_X)->SetWindowTextW(strValue);
	strValue.Format(_T("%d"), AlignResult1.y);
	GetDlgItem(IDC_STATIC_ALIGN_1_Y)->SetWindowTextW(strValue);

	strValue.Format(_T("%d"), AlignResult2.x);
	GetDlgItem(IDC_STATIC_ALIGN_2_X)->SetWindowTextW(strValue);
	strValue.Format(_T("%d"), AlignResult2.y);
	GetDlgItem(IDC_STATIC_ALIGN_2_Y)->SetWindowTextW(strValue);

	strValue.Format(_T("%d"), AlignResult3.x);
	GetDlgItem(IDC_STATIC_ALIGN_3_X)->SetWindowTextW(strValue);
	strValue.Format(_T("%d"), AlignResult3.y);
	GetDlgItem(IDC_STATIC_ALIGN_3_Y)->SetWindowTextW(strValue);

	strValue.Format(_T("%d"), AlignResult4.x);
	GetDlgItem(IDC_STATIC_ALIGN_4_X)->SetWindowTextW(strValue);
	strValue.Format(_T("%d"), AlignResult4.y);
	GetDlgItem(IDC_STATIC_ALIGN_4_Y)->SetWindowTextW(strValue);
}


void PopupManualAlign::CalcurationAlign(int nCase)
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	// EDGE
	if (nCase == 0)
	{
		int dx;
		int dy;

		dx = ManualSecondPoint.x * 4 - ManualFirstPoint.x * 4;
		dy = ManualSecondPoint.y * 4 - ManualFirstPoint.y * 4;

		double gradient;

		gradient = (double)dy / dx;

		double intercept;

		intercept = ManualFirstPoint.y * 4 - (gradient * ManualFirstPoint.x * 4);

		int value;
		value = (gradient * (CamWidth / 2) + intercept);

		CString strValue;
		strValue.Format(_T("%d"), value);

		if (pDlg->dlgPopupManualAlign.SelectCam == 0)
		{
			AlignResult1.x = CamWidth / 2;
			AlignResult1.y = value;
		}

		else if (pDlg->dlgPopupManualAlign.SelectCam == 1)
		{
			AlignResult2.x = CamWidth / 2;
			AlignResult2.y = value;
		}

		else if (pDlg->dlgPopupManualAlign.SelectCam == 2)
		{
			AlignResult3.x = CamWidth / 2;
			AlignResult3.y = value;
		}

		else if (pDlg->dlgPopupManualAlign.SelectCam == 3)
		{
			AlignResult4.x = CamWidth / 2;
			AlignResult4.y = value;
		}
	}

	else if (nCase == 1)
	{
		if (pDlg->dlgPopupManualAlign.SelectCam == 0)
		{
			AlignResult1.x = ManualMarkPoint.x * 4;
			AlignResult1.y = ManualMarkPoint.y * 4;
		}

		else if (pDlg->dlgPopupManualAlign.SelectCam == 1)
		{
			AlignResult2.x = ManualMarkPoint.x * 4;
			AlignResult2.y = ManualMarkPoint.y * 4;
		}

		else if (pDlg->dlgPopupManualAlign.SelectCam == 2)
		{
			AlignResult3.x = ManualMarkPoint.x * 4;
			AlignResult3.y = ManualMarkPoint.y * 4;
		}

		else if (pDlg->dlgPopupManualAlign.SelectCam == 3)
		{
			AlignResult4.x = ManualMarkPoint.x * 4;
			AlignResult4.y = ManualMarkPoint.y * 4;
		}
	}
}


void PopupManualAlign::CalcurationResult()
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CString strValue;
	CString strResult;
	BOOL bRet;

	if (pDlg->bChkEdge == true)
		pDlg->dAlignWidth = pDlg->dAlignHeight;

	double dXPosition_1 = 0;
	double dXPosition_2 = 0;
	double dXPosition_3 = 0;
	double dXPosition_4 = 0;

	double dYPosition_1 = 0;
	double dYPosition_2 = 0;
	double dYPosition_3 = 0;
	double dYPosition_4 = 0;
	
	dModifyX = 0;
	dModifyY = 0;
	dModifyT = 0;

	dModifyX_result = 0;
	dModifyY_result = 0;
	dModifyT_result = 0;

	double dT12 = 0;
	double dT34 = 0;
	double dT13 = 0;
	double dT24 = 0;


	if (pDlg->bJigProcess == true)
	{
		// Position 계산
		dXPosition_1 = (AlignResult1.x - CamWidth / 2) * (AlignResolution / 1000);
		dXPosition_2 = (AlignResult2.x - CamWidth / 2) * (AlignResolution / 1000);
		dXPosition_3 = (AlignResult3.x - CamWidth / 2) * (AlignResolution / 1000);

		dYPosition_1 = (AlignResult1.y - CamHeight / 2) * (AlignResolution / 1000);
		dYPosition_2 = (AlignResult2.y - CamHeight / 2) * (AlignResolution / 1000);
		dYPosition_3 = (AlignResult3.y - CamHeight / 2) * (AlignResolution / 1000);

		dModifyX = ((dXPosition_1 + dXPosition_2) / 2 + dXPosition_3) / 2;
		dModifyY = -((dYPosition_1 + dYPosition_2) / 2 + dYPosition_3) / 2;

		if (pDlg->bChkMark == true)
			dModifyX -= 0.048;

		dModifyT = (dYPosition_1 - dYPosition_3) / (pDlg->dAlignHeight - dXPosition_1 + dXPosition_3) * 180 / M_PI;
	}

	else if (pDlg->bJigProcess == false)
	{
		/*dXPosition_1 = (AlignResult1.x - CamWidth / 2) * (AlignResolution / 1000);
		dXPosition_2 = (AlignResult2.x - CamWidth / 2) * (AlignResolution / 1000);
		dXPosition_3 = (AlignResult3.x - CamWidth / 2) * (AlignResolution / 1000);
		dXPosition_4 = (AlignResult4.x - CamWidth / 2) * (AlignResolution / 1000);

		dYPosition_1 = (AlignResult1.y - CamHeight / 2) * (AlignResolution / 1000);
		dYPosition_2 = (AlignResult2.y - CamHeight / 2) * (AlignResolution / 1000);
		dYPosition_3 = (AlignResult3.y - CamHeight / 2) * (AlignResolution / 1000);
		dYPosition_4 = (AlignResult4.y - CamHeight / 2) * (AlignResolution / 1000);

		dModifyX = (dXPosition_1 + dXPosition_2 + dXPosition_3 + dXPosition_4) / 4;
		dModifyY = -(dYPosition_1 + dYPosition_2 + dYPosition_3 + dYPosition_4) / 4;

		double dT13;
		double dT24;

		dT13 = (dYPosition_1 - dYPosition_3) / (pDlg->dAlignWidth - dXPosition_1 + dXPosition_3) * 180 / M_PI;
		dT24 = (dYPosition_2 - dYPosition_4) / (pDlg->dAlignWidth - dXPosition_2 + dXPosition_4) * 180 / M_PI;

		dModifyT = (dT13 + dT24) / 2;*/

		if (pDlg->nSelecteAlignMethod == 1)
		{
			// Position 계산
			dXPosition_1 = (AlignResult1.x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_2 = (AlignResult2.x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_3 = (AlignResult3.x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_4 = (AlignResult4.x - CamWidth / 2) * (AlignResolution / 1000);

			dYPosition_1 = (AlignResult1.y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_2 = (AlignResult2.y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_3 = (AlignResult3.y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_4 = (AlignResult4.y - CamHeight / 2) * (AlignResolution / 1000);

			dModifyX = (dXPosition_1 + dXPosition_2 + dXPosition_3 + dXPosition_4) / 4;
			dModifyY = -(dYPosition_1 + dYPosition_2 + dYPosition_3 + dYPosition_4) / 4;

			if (pDlg->bChkMark == true)
				dModifyX -= 0.048;

			dT13 = (dYPosition_1 - dYPosition_3) / (pDlg->dAlignWidth - dXPosition_1 + dXPosition_3) * 180 / M_PI;
			dT24 = (dYPosition_2 - dYPosition_4) / (pDlg->dAlignWidth - dXPosition_2 + dXPosition_4) * 180 / M_PI;

			dModifyT = (dT13 + dT24) / 2;
		}

		else if (pDlg->nSelecteAlignMethod == 2)
		{
			dXPosition_1 = (AlignResult1.x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_2 = (AlignResult2.x - CamWidth / 2) * (AlignResolution / 1000);

			dYPosition_1 = (AlignResult1.y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_2 = (AlignResult2.y - CamHeight / 2) * (AlignResolution / 1000);

			dModifyX = (dXPosition_1 + dXPosition_2) / 2;
			dModifyY = -(dYPosition_1 + dYPosition_2) / 2;

			if (pDlg->bChkMark == true)
				dModifyX -= 0.048;

			dT12 = (dXPosition_1 - dXPosition_2) / (pDlg->dAlignHeight - dYPosition_1 + dYPosition_2) * 180 / M_PI;

			dModifyT = dT12;
		}

		else if (pDlg->nSelecteAlignMethod == 3)
		{
			dXPosition_3 = (AlignResult3.x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_4 = (AlignResult4.x - CamWidth / 2) * (AlignResolution / 1000);

			dYPosition_3 = (AlignResult3.y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_4 = (AlignResult4.y - CamHeight / 2) * (AlignResolution / 1000);

			dModifyX = (dXPosition_3 + dXPosition_4) / 2;
			dModifyY = -(dYPosition_3 + dYPosition_4) / 2;

			if (pDlg->bChkMark == true)
				dModifyX -= 0.048;

			dT34 = (dXPosition_3 - dXPosition_4) / (pDlg->dAlignHeight - dYPosition_3 + dYPosition_4) * 180 / M_PI;

			dModifyT = dT34;
		}

		else if (pDlg->nSelecteAlignMethod == 4)
		{
			dXPosition_1 = (AlignResult1.x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_3 = (AlignResult3.x - CamWidth / 2) * (AlignResolution / 1000);

			dYPosition_1 = (AlignResult1.y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_3 = (AlignResult3.y - CamHeight / 2) * (AlignResolution / 1000);

			dModifyX = (dXPosition_1 + dXPosition_3) / 2;
			dModifyY = -(dYPosition_1 + dYPosition_3) / 2;

			if (pDlg->bChkMark == true)
				dModifyX -= 0.048;

			dT13 = (dYPosition_1 - dYPosition_3) / (pDlg->dAlignWidth - dXPosition_1 + dXPosition_3) * 180 / M_PI;

			dModifyT = dT13;
		}

		else if (pDlg->nSelecteAlignMethod == 5)
		{
			dXPosition_2 = (AlignResult2.x - CamWidth / 2) * (AlignResolution / 1000);
			dXPosition_4 = (AlignResult4.x - CamWidth / 2) * (AlignResolution / 1000);

			dYPosition_2 = (AlignResult2.y - CamHeight / 2) * (AlignResolution / 1000);
			dYPosition_4 = (AlignResult4.y - CamHeight / 2) * (AlignResolution / 1000);

			dModifyX = (dXPosition_2 + dXPosition_4) / 2;
			dModifyY = -(dYPosition_2 + dYPosition_4) / 2;

			if (pDlg->bChkMark == true)
				dModifyX -= 0.048;

			dT24 = (dYPosition_2 - dYPosition_4) / (pDlg->dAlignWidth - dXPosition_2 + dXPosition_4) * 180 / M_PI;

			dModifyT = dT24;
		}
	}


	strValue.Format(_T("%.3fmm"), dModifyX);
	GetDlgItem(IDC_STATIC_MODIFY_X_VALUE)->SetWindowTextW(strValue);

	strValue.Format(_T("%.3fmm"), dModifyY);
	GetDlgItem(IDC_STATIC_MODIFY_Y_VALUE)->SetWindowTextW(strValue);

	strValue.Format(_T("%.6f˚"), dModifyT);
	GetDlgItem(IDC_STATIC_MODIFY_T_VALUE)->SetWindowTextW(strValue);

	Invalidate(false);

	// x축 오차 확인
	// 오차 값보다 큰 경우
	if (abs(dModifyX) > pDlg->dRangeX)
	{
		GetDlgItem(IDC_STATIC_MODIFY_X_JUDGE)->SetWindowTextW(_T("NG"));
		ChkNG_X = false;
	}

	else if (abs(dModifyX) <= pDlg->dRangeX)
	{
		GetDlgItem(IDC_STATIC_MODIFY_X_JUDGE)->SetWindowTextW(_T("OK"));
		ChkNG_X = true;
	}

	if (abs(dModifyY) > pDlg->dRangeY)
	{
		GetDlgItem(IDC_STATIC_MODIFY_Y_JUDGE)->SetWindowTextW(_T("NG"));
		ChkNG_Y = false;
	}

	else if (abs(dModifyX) <= pDlg->dRangeX)
	{
		GetDlgItem(IDC_STATIC_MODIFY_Y_JUDGE)->SetWindowTextW(_T("OK"));
		ChkNG_Y = true;
	}

	if (abs(dModifyT) > pDlg->dRangeT)
	{
		GetDlgItem(IDC_STATIC_MODIFY_T_JUDGE)->SetWindowTextW(_T("NG"));
		ChkNG_T = false;
	}

	else if (abs(dModifyT) <= pDlg->dRangeT)
	{
		GetDlgItem(IDC_STATIC_MODIFY_T_JUDGE)->SetWindowTextW(_T("OK"));
		ChkNG_T = true;
	}
}


BOOL PopupManualAlign::PreTranslateMessage(MSG* pMsg)
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


void PopupManualAlign::OnBnClickedBtnManualalign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	GetDlgItem(IDC_BTN_MANUALALIGN)->EnableWindow(false);

	GetDlgItem(IDC_BTN_UP)->EnableWindow(true);
	GetDlgItem(IDC_BTN_DOWN)->EnableWindow(true);
	GetDlgItem(IDC_BTN_LEFT)->EnableWindow(true);
	GetDlgItem(IDC_BTN_RIGHT)->EnableWindow(true);
	GetDlgItem(IDC_BTN_APPLY)->EnableWindow(true);
	GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(true);

	ChkClick = true;
}


void PopupManualAlign::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ChkActive = false;

	dModifyX_result = dModifyX;
	dModifyY_result = dModifyY;
	dModifyT_result = dModifyT;

	CDialogEx::OnOK();
}


void PopupManualAlign::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ChkActive = false;

	CDialogEx::OnCancel();
}


void PopupManualAlign::OnBnClickedBtnApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	GetDlgItem(IDC_BTN_MANUALALIGN)->EnableWindow(true);

	GetDlgItem(IDC_BTN_UP)->EnableWindow(false);
	GetDlgItem(IDC_BTN_DOWN)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LEFT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_RIGHT)->EnableWindow(false);

	GetDlgItem(IDC_BTN_APPLY)->EnableWindow(false);
	GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(false);

	ChkClick = false;

	CalcurationAlign(nCase);
	DisplayAlignPoint();
	CalcurationResult();

	if (SelectCam == 0)
		stAlign.AlignPoint[0] = { AlignResult1.x, AlignResult1.y };

	else if (SelectCam == 1)
		stAlign.AlignPoint[1] = { AlignResult2.x, AlignResult2.y };

	else if (SelectCam == 2)
		stAlign.AlignPoint[2] = { AlignResult3.x, AlignResult3.y };

	else if (SelectCam == 3)
		stAlign.AlignPoint[3] = { AlignResult4.x, AlignResult4.y };


	if (nCase == 0)
	{
		stEdgeAlign.EdgeStart[SelectCam].x = ManualFirstPoint.x * 4;
		stEdgeAlign.EdgeStart[SelectCam].y = ManualFirstPoint.y * 4;
		stEdgeAlign.EdgeEnd[SelectCam].x = ManualSecondPoint.x * 4;
		stEdgeAlign.EdgeEnd[SelectCam].y = ManualSecondPoint.y * 4;
	}

	else if (nCase == 1)
	{
		if (pDlg->bJigProcess == false)
		{
			stMarkAlign.MarkStart[SelectCam].x = (ManualMarkPoint.x - (pDlg->MarkImageAlign.cols / 8)) * 4;
			stMarkAlign.MarkStart[SelectCam].y = (ManualMarkPoint.y - (pDlg->MarkImageAlign.rows / 8)) * 4;
			stMarkAlign.MarkEnd[SelectCam].x = (ManualMarkPoint.x + (pDlg->MarkImageAlign.cols / 8)) * 4;
			stMarkAlign.MarkEnd[SelectCam].y = (ManualMarkPoint.y + (pDlg->MarkImageAlign.rows / 8)) * 4;
		}
		else if (pDlg->bJigProcess == true)
		{
			stMarkAlign.MarkStart[SelectCam].x = ManualMarkPoint.x * 4;
			stMarkAlign.MarkStart[SelectCam].y = ManualMarkPoint.y * 4;
		}
	}

	CString strValue;
	GetDlgItem(IDC_STATIC_MODIFY_X_VALUE)->GetWindowTextW(strValue);
	dModifyX = _wtof(strValue);
	GetDlgItem(IDC_STATIC_MODIFY_Y_VALUE)->GetWindowTextW(strValue);
	dModifyY = _wtof(strValue);
	GetDlgItem(IDC_STATIC_MODIFY_T_VALUE)->GetWindowTextW(strValue);
	dModifyT = _wtof(strValue);
}


void PopupManualAlign::OnBnClickedBtnCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	GetDlgItem(IDC_BTN_MANUALALIGN)->EnableWindow(true);

	GetDlgItem(IDC_BTN_UP)->EnableWindow(false);
	GetDlgItem(IDC_BTN_DOWN)->EnableWindow(false);
	GetDlgItem(IDC_BTN_LEFT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_RIGHT)->EnableWindow(false);

	GetDlgItem(IDC_BTN_APPLY)->EnableWindow(false);
	GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(false);

	ChkClick = false;

	CString strValue;

	strValue.Format(_T("%d"), stAlign.AlignPoint[0].x);
	GetDlgItem(IDC_STATIC_ALIGN_1_X)->SetWindowTextW(strValue);

	strValue.Format(_T("%d"), stAlign.AlignPoint[0].y);
	GetDlgItem(IDC_STATIC_ALIGN_1_Y)->SetWindowTextW(strValue);

	strValue.Format(_T("%d"), stAlign.AlignPoint[1].x);
	GetDlgItem(IDC_STATIC_ALIGN_2_X)->SetWindowTextW(strValue);

	strValue.Format(_T("%d"), stAlign.AlignPoint[1].y);
	GetDlgItem(IDC_STATIC_ALIGN_2_Y)->SetWindowTextW(strValue);

	strValue.Format(_T("%d"), stAlign.AlignPoint[2].x);
	GetDlgItem(IDC_STATIC_ALIGN_3_X)->SetWindowTextW(strValue);

	strValue.Format(_T("%d"), stAlign.AlignPoint[2].y);
	GetDlgItem(IDC_STATIC_ALIGN_3_Y)->SetWindowTextW(strValue);

	if (pDlg->bJigProcess == true)
	{
		stAlign.AlignPoint[3].x = 0;
		stAlign.AlignPoint[3].y = 0;
	}

	strValue.Format(_T("%d"), stAlign.AlignPoint[3].x);
	GetDlgItem(IDC_STATIC_ALIGN_4_X)->SetWindowTextW(strValue);

	strValue.Format(_T("%d"), stAlign.AlignPoint[3].y);
	GetDlgItem(IDC_STATIC_ALIGN_4_Y)->SetWindowTextW(strValue);

	AlignResult1.x = stAlign.AlignPoint[0].x;
	AlignResult2.x = stAlign.AlignPoint[1].x;
	AlignResult3.x = stAlign.AlignPoint[2].x;
	AlignResult4.x = stAlign.AlignPoint[3].x;

	AlignResult1.y = stAlign.AlignPoint[0].y;
	AlignResult2.y = stAlign.AlignPoint[1].y;
	AlignResult3.y = stAlign.AlignPoint[2].y;
	AlignResult4.y = stAlign.AlignPoint[3].y;

	CalcurationResult();
}

void PopupManualAlign::OnBnClickedBtnAlign1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (ChkClick == false)
	{
		m_btn_align1.SetFaceColor(ColorGreen);
		m_btn_align2.SetFaceColor(ColorBasic);
		m_btn_align3.SetFaceColor(ColorBasic);
		m_btn_align4.SetFaceColor(ColorBasic);

		SelectCam = 0;

		ManualMarkPoint.x = AlignResult1.x / 4;
		ManualMarkPoint.y = AlignResult1.y / 4;

		ManualFirstPoint.x = stEdgeAlign.EdgeStart[0].x / 4;
		ManualFirstPoint.y = stEdgeAlign.EdgeStart[0].y / 4;

		ManualSecondPoint.x = stEdgeAlign.EdgeEnd[0].x / 4;
		ManualSecondPoint.y = stEdgeAlign.EdgeEnd[0].y / 4;
	}
}


void PopupManualAlign::OnBnClickedBtnAlign2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (ChkClick == false)
	{
		m_btn_align1.SetFaceColor(ColorBasic);
		m_btn_align2.SetFaceColor(ColorGreen);
		m_btn_align3.SetFaceColor(ColorBasic);
		m_btn_align4.SetFaceColor(ColorBasic);

		SelectCam = 1;

		ManualMarkPoint.x = AlignResult2.x / 4;
		ManualMarkPoint.y = AlignResult2.y / 4;

		ManualFirstPoint.x = stEdgeAlign.EdgeStart[1].x / 4;
		ManualFirstPoint.y = stEdgeAlign.EdgeStart[1].y / 4;

		ManualSecondPoint.x = stEdgeAlign.EdgeEnd[1].x / 4;
		ManualSecondPoint.y = stEdgeAlign.EdgeEnd[1].y / 4;
	}
}


void PopupManualAlign::OnBnClickedBtnAlign3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (ChkClick == false)
	{
		m_btn_align1.SetFaceColor(ColorBasic);
		m_btn_align2.SetFaceColor(ColorBasic);
		m_btn_align3.SetFaceColor(ColorGreen);
		m_btn_align4.SetFaceColor(ColorBasic);

		SelectCam = 2;

		ManualMarkPoint.x = AlignResult3.x / 4;
		ManualMarkPoint.y = AlignResult3.y / 4;

		ManualFirstPoint.x = stEdgeAlign.EdgeStart[2].x / 4;
		ManualFirstPoint.y = stEdgeAlign.EdgeStart[2].y / 4;

		ManualSecondPoint.x = stEdgeAlign.EdgeEnd[2].x / 4;
		ManualSecondPoint.y = stEdgeAlign.EdgeEnd[2].y / 4;
	}
}


void PopupManualAlign::OnBnClickedBtnAlign4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (ChkClick == false)
	{
		m_btn_align1.SetFaceColor(ColorBasic);
		m_btn_align2.SetFaceColor(ColorBasic);
		m_btn_align3.SetFaceColor(ColorBasic);
		m_btn_align4.SetFaceColor(ColorGreen);

		SelectCam = 3;

		ManualMarkPoint.x = AlignResult4.x / 4;
		ManualMarkPoint.y = AlignResult4.y / 4;

		ManualFirstPoint.x = stEdgeAlign.EdgeStart[3].x / 4;
		ManualFirstPoint.y = stEdgeAlign.EdgeStart[3].y / 4;

		ManualSecondPoint.x = stEdgeAlign.EdgeEnd[3].x / 4;
		ManualSecondPoint.y = stEdgeAlign.EdgeEnd[3].y / 4;
	}
}


void PopupManualAlign::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CString strValue;

	if (nCase == 0)
	{
		if (point.y > 20 && point.y < 20 + CamHeight / 4)
		{
			if (/*pDlg->dlgPopupManualAlign.*/ChkClick == true)
			{
				if (nClickCount == 0)
				{

					ManualFirstPoint.x = point.x;
					ManualFirstPoint.y = (point.y - 20);

					ManualSecondPoint.x = point.x;
					ManualSecondPoint.y = (point.y - 20);

					nClickCount = 1;
				}

				else if (nClickCount == 1)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
						ManualSecondPoint.y = ManualFirstPoint.y;


					else
					{
						ManualSecondPoint.x = point.x;
						ManualSecondPoint.y = (point.y - 20);
					}

					CalcurationAlign(nCase);
					DisplayAlignPoint();
					CalcurationResult();

					nClickCount = 0;
				}
			}
		}
	}

	else if (nCase == 1)
	{
		if (point.y > 20 && point.y < 20 + CamHeight / 4)
		{
			if (/*pDlg->dlgPopupManualAlign.*/ChkClick == true)
			{
				ManualMarkPoint.x = point.x;
				ManualMarkPoint.y = point.y - 20;

				CalcurationAlign(nCase);
				DisplayAlignPoint();
				CalcurationResult();
			}
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void PopupManualAlign::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	if (nCase == 0)
	{
		if (pDlg->dlgPopupManualAlign.ChkClick == true)
		{
			if (nClickCount == 1)
			{
				ManualSecondPoint.x = point.x;
				ManualSecondPoint.y = (point.y - 20);

				// SHIFT 누르고 이동했을 경우 
				if (GetKeyState(VK_LSHIFT) & 0x8000)
					ManualSecondPoint.y = ManualFirstPoint.y;
			}
		}
	}


	CDialogEx::OnMouseMove(nFlags, point);
}


void PopupManualAlign::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CDialogEx::OnLButtonUp(nFlags, point);
}


void PopupManualAlign::DisplayJudge()
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	if (pDlg->bJigProcess == true)
		GetDlgItem(IDC_BTN_ALIGN4)->EnableWindow(false);

	if (ChkNG_X == true)
		GetDlgItem(IDC_STATIC_MODIFY_X_JUDGE)->SetWindowTextW(_T("OK"));

	else if (ChkNG_X == false)
		GetDlgItem(IDC_STATIC_MODIFY_X_JUDGE)->SetWindowTextW(_T("NG"));

	if (ChkNG_Y == true)
		GetDlgItem(IDC_STATIC_MODIFY_Y_JUDGE)->SetWindowTextW(_T("OK"));

	else if (ChkNG_Y == false)
		GetDlgItem(IDC_STATIC_MODIFY_Y_JUDGE)->SetWindowTextW(_T("NG"));

	if (ChkNG_T == true)
		GetDlgItem(IDC_STATIC_MODIFY_T_JUDGE)->SetWindowTextW(_T("OK"));

	else if (ChkNG_T == false)
		GetDlgItem(IDC_STATIC_MODIFY_T_JUDGE)->SetWindowTextW(_T("NG"));

}

void PopupManualAlign::OnBnClickedBtnUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ManualMarkPoint.y -= 1;

	ManualFirstPoint.y -= 1;
	ManualSecondPoint.y -= 1;


	CalcurationAlign(nCase);
	DisplayAlignPoint();
	CalcurationResult();
}


void PopupManualAlign::OnBnClickedBtnDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ManualMarkPoint.y += 1;

	ManualFirstPoint.y += 1;
	ManualSecondPoint.y += 1;

	CalcurationAlign(nCase);
	DisplayAlignPoint();
	CalcurationResult();
}


void PopupManualAlign::OnBnClickedBtnLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	if (pDlg->bChkMark == true)
	{
		ManualMarkPoint.x -= 1;

		CalcurationAlign(nCase);
		DisplayAlignPoint();
		CalcurationResult();
	}
}


void PopupManualAlign::OnBnClickedBtnRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	if (pDlg->bChkMark == true)
	{
		ManualMarkPoint.x += 1;

		CalcurationAlign(nCase);
		DisplayAlignPoint();
		CalcurationResult();
	}
}

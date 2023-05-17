// SettingCamera.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "SettingCamera.h"
#include "afxdialogex.h"

#include "RVisionDlg.h"

// SettingCamera 대화 상자

IMPLEMENT_DYNAMIC(SettingCamera, CDialogEx)

extern RecipeName stRecipe;
extern CameraParameter stCamera;

SettingCamera::SettingCamera(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_CAMERA, pParent)
{

}

SettingCamera::~SettingCamera()
{
}

void SettingCamera::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_NAME, m_chk_name);
	DDX_Control(pDX, IDC_CHK_CROSSLINE, m_chk_crossline);
	DDX_Control(pDX, IDC_COLOR_NAME, m_color_name);
	DDX_Control(pDX, IDC_COLOR_CROSSLINE, m_color_crossline);
	DDX_Control(pDX, IDC_CHK_ROI, m_chk_roi);
	DDX_Control(pDX, IDC_COLOR_ROI, m_color_roi);
	DDX_Control(pDX, IDC_EDIT_LIGHT_ALIGN1, m_edit_light_align1);
	DDX_Control(pDX, IDC_EDIT_LIGHT_ALIGN2, m_edit_light_align2);
	DDX_Control(pDX, IDC_EDIT_LIGHT_ALIGN3, m_edit_light_align3);
	DDX_Control(pDX, IDC_EDIT_LIGHT_ALIGN4, m_edit_light_align4);
	DDX_Control(pDX, IDC_EDIT_LIGHT_REVIEW, m_edit_light_review);
	DDX_Control(pDX, IDC_CMB_SELECTCAM, m_cmb_selectcam);
	DDX_Control(pDX, IDC_SLIDER_LIGHT_1, m_slider_light_1);
	DDX_Control(pDX, IDC_EDIT_RECIPE_SELECT, m_edit_recipe_select);
	DDX_Control(pDX, IDC_SLIDER_LIGHT_2, m_slider_light_2);
	DDX_Control(pDX, IDC_SLIDER_LIGHT_3, m_slider_light_3);
	DDX_Control(pDX, IDC_SLIDER_LIGHT_4, m_slider_light_4);
	DDX_Control(pDX, IDC_SLIDER_LIGHT_5, m_slider_light_5);
	DDX_Control(pDX, IDC_EDIT_RECIPE_NAME, m_edit_recipe_name);
	DDX_Control(pDX, IDC_EDIT_X_OFFSET, m_edit_x_offset);
	DDX_Control(pDX, IDC_EDIT_Y_OFFSET, m_edit_y_offset);
}


BEGIN_MESSAGE_MAP(SettingCamera, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_CHK_NAME, &SettingCamera::OnBnClickedChkName)
	ON_BN_CLICKED(IDC_CHK_CROSSLINE, &SettingCamera::OnBnClickedChkCrossline)
	ON_BN_CLICKED(IDC_BTN_APPLY, &SettingCamera::OnBnClickedBtnApply)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &SettingCamera::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BTN_MODIFY, &SettingCamera::OnBnClickedBtnModify)
	ON_BN_CLICKED(IDC_CHK_ROI, &SettingCamera::OnBnClickedChkRoi)
	ON_EN_CHANGE(IDC_EDIT_LIGHT_ALIGN1, &SettingCamera::OnEnChangeEditLightAlign1)
	ON_EN_CHANGE(IDC_EDIT_LIGHT_ALIGN2, &SettingCamera::OnEnChangeEditLightAlign2)
	ON_EN_CHANGE(IDC_EDIT_LIGHT_ALIGN3, &SettingCamera::OnEnChangeEditLightAlign3)
	ON_EN_CHANGE(IDC_EDIT_LIGHT_ALIGN4, &SettingCamera::OnEnChangeEditLightAlign4)
	ON_EN_CHANGE(IDC_EDIT_LIGHT_REVIEW, &SettingCamera::OnEnChangeEditLightReview)
	ON_CBN_SELCHANGE(IDC_CMB_SELECTCAM, &SettingCamera::OnCbnSelchangeCmbSelectcam)
	ON_BN_CLICKED(IDC_BTN_RECIPE_LOAD, &SettingCamera::OnBnClickedBtnRecipeLoad)
	ON_BN_CLICKED(IDC_BTN_ADD, &SettingCamera::OnBnClickedBtnAdd)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// SettingCamera 메시지 처리기


int SettingCamera::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH SettingCamera::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL SettingCamera::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL SettingCamera::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	GetDlgItem(IDC_GRP_LIGHT)->MoveWindow(10, 40, 300, 220);
	GetDlgItem(IDC_STATIC_LIGHT_ALIGN1)->MoveWindow(20, 70, 60, 30);
	GetDlgItem(IDC_SLIDER_LIGHT_1)->MoveWindow(80, 70, 140, 20);
	GetDlgItem(IDC_EDIT_LIGHT_ALIGN1)->MoveWindow(240, 70, 60, 20);
	GetDlgItem(IDC_STATIC_LIGHT_ALIGN2)->MoveWindow(20, 105, 60, 30);
	GetDlgItem(IDC_SLIDER_LIGHT_2)->MoveWindow(80, 105, 140, 20);
	GetDlgItem(IDC_EDIT_LIGHT_ALIGN2)->MoveWindow(240, 105, 60, 20);
	GetDlgItem(IDC_STATIC_LIGHT_ALIGN3)->MoveWindow(20, 140, 60, 30);
	GetDlgItem(IDC_SLIDER_LIGHT_3)->MoveWindow(80, 140, 140, 20);
	GetDlgItem(IDC_EDIT_LIGHT_ALIGN3)->MoveWindow(240, 140, 60, 20);
	GetDlgItem(IDC_STATIC_LIGHT_ALIGN4)->MoveWindow(20, 175, 60, 30);
	GetDlgItem(IDC_SLIDER_LIGHT_4)->MoveWindow(80, 175, 140, 20);
	GetDlgItem(IDC_EDIT_LIGHT_ALIGN4)->MoveWindow(240, 175, 60, 20);
	GetDlgItem(IDC_STATIC_LIGHT_REVIEW)->MoveWindow(20, 210, 60, 30);
	GetDlgItem(IDC_SLIDER_LIGHT_5)->MoveWindow(80, 210, 140, 20);
	GetDlgItem(IDC_EDIT_LIGHT_REVIEW)->MoveWindow(240, 210, 60, 20);

	GetDlgItem(IDC_CMB_SELECTCAM)->MoveWindow(WindowWidth - 90, 0, 90, 30);

	GetDlgItem(IDC_STATIC_X_OFFSET)->MoveWindow(330, 50, 50, 30);
	GetDlgItem(IDC_STATIC_Y_OFFSET)->MoveWindow(460, 50, 50, 30);
	GetDlgItem(IDC_EDIT_X_OFFSET)->MoveWindow(390, 55, 60, 20);
	GetDlgItem(IDC_EDIT_Y_OFFSET)->MoveWindow(520, 55, 60, 20);

	GetDlgItem(IDC_GRP_DISPLAY)->MoveWindow(330, 100, 270, 160);
	GetDlgItem(IDC_CHK_NAME)->MoveWindow(350, 135, 150, 30);
	GetDlgItem(IDC_CHK_CROSSLINE)->MoveWindow(350, 170, 150, 30);
	GetDlgItem(IDC_CHK_ROI)->MoveWindow(350, 205, 150, 30);
	GetDlgItem(IDC_COLOR_NAME)->MoveWindow(520, 140, 60, 20);
	GetDlgItem(IDC_COLOR_CROSSLINE)->MoveWindow(520, 175, 60, 20);
	GetDlgItem(IDC_COLOR_ROI)->MoveWindow(520, 210, 60, 20);

	GetDlgItem(IDC_BTN_RECIPE_LOAD)->MoveWindow(10, 287, 60, 30);
	GetDlgItem(IDC_EDIT_RECIPE_SELECT)->MoveWindow(80, 292, 50, 25);
	GetDlgItem(IDC_EDIT_RECIPE_NAME)->MoveWindow(140, 292, 150, 25);
	GetDlgItem(IDC_BTN_ADD)->MoveWindow(WindowWidth - 280, 287, 60, 30);
	GetDlgItem(IDC_BTN_MODIFY)->MoveWindow(WindowWidth - 210, 287, 60, 30);
	GetDlgItem(IDC_BTN_APPLY)->MoveWindow(WindowWidth - 140, 287, 60, 30);
	GetDlgItem(IDC_BTN_CANCEL)->MoveWindow(WindowWidth - 70, 287, 60, 30);

	HFONT staticFont;
	staticFont = CreateFont(15, 5, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_CHK_NAME)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_CHK_CROSSLINE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_CHK_ROI)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);


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

	GetDlgItem(IDC_BTN_RECIPE_LOAD)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_ADD)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_MODIFY)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_APPLY)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_CANCEL)->SetFont(btnFont);

	CFont* pFont = new CFont;
	pFont->CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_GRP_LIGHT)->SetFont(pFont, TRUE);
	GetDlgItem(IDC_GRP_DISPLAY)->SetFont(pFont, TRUE);
	GetDlgItem(IDC_STATIC_X_OFFSET)->SetFont(pFont, TRUE);
	GetDlgItem(IDC_STATIC_Y_OFFSET)->SetFont(pFont, TRUE);

	
	ChkModify = false;
	EditEnable(false);

	m_slider_light_1.SetRange(0, 255);
	m_slider_light_2.SetRange(0, 255);
	m_slider_light_3.SetRange(0, 255);
	m_slider_light_4.SetRange(0, 255);
	m_slider_light_5.SetRange(0, 255);

	DisplayParam();

	m_cmb_selectcam.SetCurSel(0);

	GetDlgItem(IDC_EDIT_X_OFFSET)->EnableWindow(false);
	GetDlgItem(IDC_EDIT_Y_OFFSET)->EnableWindow(false);
	//m_slider_light_1.SetPos(0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL SettingCamera::PreTranslateMessage(MSG* pMsg)
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


void SettingCamera::DisplayParam()
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CString strValue;

	if (pDlg->CHK_NAME == true)
		m_chk_name.SetCheck(1);

	else if (pDlg->CHK_NAME == false)
		m_chk_name.SetCheck(0);

	if (pDlg->CHK_CROSSLINE == true)
		m_chk_crossline.SetCheck(1);

	else if (pDlg->CHK_CROSSLINE == false)
		m_chk_crossline.SetCheck(0);

	if (pDlg->CHK_ROI == true)
		m_chk_roi.SetCheck(1);

	else if (pDlg->CHK_ROI == false)
		m_chk_roi.SetCheck(0);

	int nValue;

	strValue.Format(_T("%d"), stCamera.nLight[0]);
	nValue = _ttoi(strValue);
	m_edit_light_align1.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), stCamera.nLight[1]);
	nValue = _ttoi(strValue);
	m_edit_light_align2.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), stCamera.nLight[2]);
	nValue = _ttoi(strValue);
	m_edit_light_align3.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), stCamera.nLight[3]);
	nValue = _ttoi(strValue);
	m_edit_light_align4.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), stCamera.nLight[4]);
	nValue = _ttoi(strValue);
	m_edit_light_review.SetWindowTextW(strValue);

	m_color_name.SetColor(pDlg->cNameColor);
	m_color_crossline.SetColor(pDlg->cCrossLineColor);
	m_color_roi.SetColor(pDlg->cROIColor);
}


void SettingCamera::OnBnClickedChkName()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	if (m_chk_name.GetCheck() == 0)
		pDlg->CHK_NAME = false;

	else if (m_chk_name.GetCheck() == 1)
		pDlg->CHK_NAME = true;

}


void SettingCamera::OnBnClickedChkCrossline()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	if (m_chk_crossline.GetCheck() == 0)
		pDlg->CHK_CROSSLINE = false;

	else if (m_chk_crossline.GetCheck() == 1)
		pDlg->CHK_CROSSLINE = true;
}


void SettingCamera::OnBnClickedChkRoi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	if (m_chk_roi.GetCheck() == 0)
		pDlg->CHK_ROI = false;

	else if (m_chk_roi.GetCheck() == 1)
		pDlg->CHK_ROI = true;
}


void SettingCamera::OnBnClickedBtnModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EditEnable(true);
}


void SettingCamera::OnBnClickedBtnApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CString strValue;

	EditEnable(false);

	m_edit_light_align1.GetWindowTextW(strValue);
	stCamera.nLight[0] = _ttoi(strValue);

	m_edit_light_align2.GetWindowTextW(strValue);
	stCamera.nLight[1] = _ttoi(strValue);

	m_edit_light_align3.GetWindowTextW(strValue);
	stCamera.nLight[2] = _ttoi(strValue);

	m_edit_light_align4.GetWindowTextW(strValue);
	stCamera.nLight[3] = _ttoi(strValue);

	m_edit_light_review.GetWindowTextW(strValue);
	stCamera.nLight[4] = _ttoi(strValue);

	pDlg->cNameColor = m_color_name.GetColor();
	pDlg->cCrossLineColor = m_color_crossline.GetColor();
	pDlg->cROIColor = m_color_roi.GetColor();

	pDlg->SaveRecipe(0);

	m_edit_recipe_name.GetWindowTextW(strValue);
	pDlg->dlgVisionSetting->dlgSettingFC->m_edit_recipe_name.SetWindowTextW(strValue);
	pDlg->dlgVisionSetting->dlgSettingAlign->m_edit_recipe_name.SetWindowTextW(strValue);
	pDlg->dlgVisionSetting->dlgSettingAlignMark->m_edit_recipe_name.SetWindowTextW(strValue);

	stRecipe.strRecipeName[pDlg->nSelectRecipe - 1] = strValue;

	CString		strPath;
	CString		strTag;
	CString		strName;
	CString		strData;

	strPath = pDlg->strExeFilePath + _T("RecipeName.ini");
	strTag = _T("RecipeName");

	for (int i = 0; i < 100; i++)
	{
		strName.Format(_T("Recipe%d"), i + 1);

		strData = stRecipe.strRecipeName[i];
		WritePrivateProfileString(strTag, strName, strData, strPath);
	}
}


void SettingCamera::OnBnClickedBtnCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DisplayParam();
	EditEnable(false);
}


void SettingCamera::EditEnable(bool nCase)
{
	if (nCase == true)
	{
		GetDlgItem(IDC_BTN_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);

		ChkModify = true;
	}

	else if (nCase == false)
	{
		GetDlgItem(IDC_BTN_MODIFY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ADD)->EnableWindow(TRUE);

		ChkModify = false;
	}

	m_slider_light_1.EnableWindow(nCase);
	m_slider_light_2.EnableWindow(nCase);
	m_slider_light_3.EnableWindow(nCase);
	m_slider_light_4.EnableWindow(nCase);
	m_slider_light_5.EnableWindow(nCase);

	m_edit_light_align1.EnableWindow(nCase);
	m_edit_light_align2.EnableWindow(nCase);
	m_edit_light_align3.EnableWindow(nCase);
	m_edit_light_align4.EnableWindow(nCase);
	m_edit_light_review.EnableWindow(nCase);

	m_chk_name.EnableWindow(nCase);
	m_chk_crossline.EnableWindow(nCase);
	m_chk_roi.EnableWindow(nCase);
	m_color_name.EnableWindow(nCase);
	m_color_crossline.EnableWindow(nCase);
	m_color_roi.EnableWindow(nCase);

	GetDlgItem(IDC_EDIT_RECIPE_NAME)->EnableWindow(nCase);
	//GetDlgItem(IDC_BTN_ADD)->EnableWindow(nCase);
	GetDlgItem(IDC_BTN_APPLY)->EnableWindow(nCase);
	GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(nCase);
}

void SettingCamera::OnEnChangeEditLightAlign1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	int nValue;
	CString strValue;

	m_edit_light_align1.GetWindowTextW(strValue);
	nValue = _ttoi(strValue);

	if (nValue < 0)
		nValue = 0;

	else if (nValue > 255)
		nValue = 255;

	pDlg->SetCSR(0);
	pDlg->SetSVR(nValue);

	m_slider_light_1.SetPos(nValue);
}


void SettingCamera::OnEnChangeEditLightAlign2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	int nValue;
	CString strValue;

	m_edit_light_align2.GetWindowTextW(strValue);
	nValue = _ttoi(strValue);

	if (nValue < 0)
		nValue = 0;

	else if (nValue > 255)
		nValue = 255;

	pDlg->SetCSR(1);
	pDlg->SetSVR(nValue);

	m_slider_light_2.SetPos(nValue);
}


void SettingCamera::OnEnChangeEditLightAlign3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	int nValue;
	CString strValue;

	m_edit_light_align3.GetWindowTextW(strValue);
	nValue = _ttoi(strValue);

	if (nValue < 0)
		nValue = 0;

	else if (nValue > 255)
		nValue = 255;

	pDlg->SetCSR(2);
	pDlg->SetSVR(nValue);

	m_slider_light_3.SetPos(nValue);
}


void SettingCamera::OnEnChangeEditLightAlign4()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	int nValue;
	CString strValue;

	m_edit_light_align4.GetWindowTextW(strValue);
	nValue = _ttoi(strValue);

	if (nValue < 0)
		nValue = 0;

	else if (nValue > 255)
		nValue = 255;

	pDlg->SetCSR(3);
	pDlg->SetSVR(nValue);

	m_slider_light_4.SetPos(nValue);
}


void SettingCamera::OnEnChangeEditLightReview()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	int nValue;
	CString strValue;

	m_edit_light_review.GetWindowTextW(strValue);
	nValue = _ttoi(strValue);

	if (nValue < 0)
		nValue = 0;

	else if (nValue > 255)
		nValue = 255;

	pDlg->SetCSR(4);
	pDlg->SetSVR(nValue);

	m_slider_light_5.SetPos(nValue);
}


void SettingCamera::OnCbnSelchangeCmbSelectcam()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nCase;

	nCase = m_cmb_selectcam.GetCurSel();
	SelectCam = nCase;
}

void SettingCamera::OnBnClickedBtnRecipeLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	pDlg->RecipeSelect();
}


void SettingCamera::OnBnClickedBtnAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	pDlg->RecipeAdd();

	EditEnable(false);
}


void SettingCamera::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (pScrollBar == (CScrollBar*)&m_slider_light_1)
	{
		int nPos = m_slider_light_1.GetPos();
		CString strPos;
		strPos.Format(_T("%d"), nPos);
		m_edit_light_align1.SetWindowTextW(strPos);
	}

	if (pScrollBar == (CScrollBar*)&m_slider_light_2)
	{
		int nPos = m_slider_light_2.GetPos();
		CString strPos;
		strPos.Format(_T("%d"), nPos);
		m_edit_light_align2.SetWindowTextW(strPos);
	}

	if (pScrollBar == (CScrollBar*)&m_slider_light_3)
	{
		int nPos = m_slider_light_3.GetPos();
		CString strPos;
		strPos.Format(_T("%d"), nPos);
		m_edit_light_align3.SetWindowTextW(strPos);
	}

	if (pScrollBar == (CScrollBar*)&m_slider_light_4)
	{
		int nPos = m_slider_light_4.GetPos();
		CString strPos;
		strPos.Format(_T("%d"), nPos);
		m_edit_light_align4.SetWindowTextW(strPos);
	}

	if (pScrollBar == (CScrollBar*)&m_slider_light_5)
	{
		int nPos = m_slider_light_5.GetPos();
		CString strPos;
		strPos.Format(_T("%d"), nPos);
		m_edit_light_review.SetWindowTextW(strPos);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

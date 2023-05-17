// SettingFC.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "SettingFC.h"
#include "afxdialogex.h"

#include "RVisionDlg.h"
// SettingFC 대화 상자

IMPLEMENT_DYNAMIC(SettingFC, CDialogEx)

extern 	RecipeName stRecipe;

SettingFC::SettingFC(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_FC, pParent)
{

}

SettingFC::~SettingFC()
{
}

void SettingFC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MATCHRATE, m_edit_matchrate);
	DDX_Control(pDX, IDC_EDIT_FC_ROI_START_X, m_edit_fc_roi_start_x);
	DDX_Control(pDX, IDC_EDIT_FC_ROI_START_Y, m_edit_fc_roi_start_y);
	DDX_Control(pDX, IDC_EDIT_FC_ROI_END_X, m_edit_fc_roi_end_x);
	DDX_Control(pDX, IDC_EDIT_FC_ROI_END_Y, m_edit_fc_roi_end_y);
	DDX_Control(pDX, IDC_EDIT_BINARY_LOW, m_edit_binary_low);
	DDX_Control(pDX, IDC_EDIT_RECIPE_SELECT, m_edit_recipe_select);
	DDX_Control(pDX, IDC_EDIT_RECIPE_NAME, m_edit_recipe_name);
	DDX_Control(pDX, IDC_EDIT_FC_OPEN, m_edit_fc_open);
	DDX_Control(pDX, IDC_EDIT_FC_CLOSE, m_edit_fc_close);
	DDX_Control(pDX, IDC_EDIT_FCMARK_BINARY_LOW, m_edit_fcmark_binary_low);
	DDX_Control(pDX, IDC_EDIT_FCMARK_OPEN, m_edit_fcmark_open);
	DDX_Control(pDX, IDC_EDIT_FCMARK_CLOSE, m_edit_fcmark_close);
}


BEGIN_MESSAGE_MAP(SettingFC, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_MODIFY, &SettingFC::OnBnClickedBtnModify)
	ON_BN_CLICKED(IDC_BTN_APPLY, &SettingFC::OnBnClickedBtnApply)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &SettingFC::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BTN_FCMARK_ENROLL, &SettingFC::OnBnClickedBtnFcmarkEnroll)
	ON_BN_CLICKED(IDC_BTN_FCMARK_APPLY, &SettingFC::OnBnClickedBtnFcmarkApply)
	ON_BN_CLICKED(IDC_BTN_FCMARK_CANCEL, &SettingFC::OnBnClickedBtnFcmarkCancel)
	ON_BN_CLICKED(IDC_BTN_RECIPE_LOAD, &SettingFC::OnBnClickedBtnRecipeLoad)
	ON_BN_CLICKED(IDC_BTN_ADD, &SettingFC::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_FCMARK_UP, &SettingFC::OnBnClickedBtnFcmarkUp)
	ON_BN_CLICKED(IDC_BTN_FCMARK_DOWN, &SettingFC::OnBnClickedBtnFcmarkDown)
	ON_BN_CLICKED(IDC_BTN_FCMARK_LEFT, &SettingFC::OnBnClickedBtnFcmarkLeft)
	ON_BN_CLICKED(IDC_BTN_FCMARK_RIGHT, &SettingFC::OnBnClickedBtnFcmarkRight)
	ON_BN_CLICKED(IDC_BTN_PREPROCESS_SHOW2, &SettingFC::OnBnClickedBtnPreprocessShow2)
	ON_BN_CLICKED(IDC_BTN_PREPROCESS_APPLY, &SettingFC::OnBnClickedBtnPreprocessApply)
	ON_BN_CLICKED(IDC_BTN_FCMARK_PREPROCESS_APPLY, &SettingFC::OnBnClickedBtnFcmarkPreprocessApply)
	ON_BN_CLICKED(IDC_BTN_FCMARK_PREPROCESS_CANCEL, &SettingFC::OnBnClickedBtnFcmarkPreprocessCancel)
END_MESSAGE_MAP()


// SettingFC 메시지 처리기


int SettingFC::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH SettingFC::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL SettingFC::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL SettingFC::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	GetDlgItem(IDC_GRP_FC_PARAM)->MoveWindow(10, 40, 160, 180);
	GetDlgItem(IDC_STATIC_BINARY)->MoveWindow(20, 70, 80, 20);
	GetDlgItem(IDC_EDIT_BINARY_LOW)->MoveWindow(100, 70, 60, 20);
	GetDlgItem(IDC_STATIC_OPEN)->MoveWindow(20, 100, 80, 20);
	GetDlgItem(IDC_EDIT_FC_OPEN)->MoveWindow(100, 100, 60, 20);
	GetDlgItem(IDC_STATIC_CLOSE)->MoveWindow(20, 130, 80, 20);
	GetDlgItem(IDC_EDIT_FC_CLOSE)->MoveWindow(100, 130, 60, 20);
	GetDlgItem(IDC_BTN_PREPROCESS_SHOW2)->MoveWindow(30, 180, 60, 20);
	GetDlgItem(IDC_BTN_PREPROCESS_APPLY)->MoveWindow(100, 180, 60, 20);
	GetDlgItem(IDC_STATIC_START)->MoveWindow(20, 150, 70, 20);
	GetDlgItem(IDC_EDIT_FC_ROI_START_X)->MoveWindow(30, 180, 60, 20);
	GetDlgItem(IDC_EDIT_FC_ROI_START_Y)->MoveWindow(100, 180, 60, 20);
	GetDlgItem(IDC_STATIC_END)->MoveWindow(20, 210, 70, 20);
	GetDlgItem(IDC_EDIT_FC_ROI_END_X)->MoveWindow(30, 240, 60, 20);
	GetDlgItem(IDC_EDIT_FC_ROI_END_Y)->MoveWindow(100, 240, 60, 20);

	GetDlgItem(IDC_GRP_PREPROCESS)->MoveWindow(180, 40, 160, 180);
	GetDlgItem(IDC_STATIC_FCMARK_BINARY)->MoveWindow(200, 70, 60, 20);
	GetDlgItem(IDC_EDIT_FCMARK_BINARY_LOW)->MoveWindow(280, 70, 50, 20);
	GetDlgItem(IDC_STATIC_FCMARK_OPEN)->MoveWindow(200, 100, 60, 20);
	GetDlgItem(IDC_EDIT_FCMARK_OPEN)->MoveWindow(280, 100, 50, 20);
	GetDlgItem(IDC_STATIC_FCMARK_CLOSE)->MoveWindow(200, 130, 60, 20);
	GetDlgItem(IDC_EDIT_FCMARK_CLOSE)->MoveWindow(280, 130, 50, 20);
	GetDlgItem(IDC_BTN_FCMARK_PREPROCESS_APPLY)->MoveWindow(200, 180, 60, 20);
	GetDlgItem(IDC_BTN_FCMARK_PREPROCESS_CANCEL)->MoveWindow(270, 180, 60, 20);


	GetDlgItem(IDC_GRP_ENROLL)->MoveWindow(360, 40, 240, 220);
	GetDlgItem(IDC_BTN_FCMARK_ENROLL)->MoveWindow(380, 70, 70, 20);
	GetDlgItem(IDC_BTN_FCMARK_APPLY)->MoveWindow(380, 100, 70, 20);
	GetDlgItem(IDC_BTN_FCMARK_CANCEL)->MoveWindow(380, 130, 70, 20);
	GetDlgItem(IDC_BTN_FCMARK_UP)->MoveWindow(405, 170, 20, 20);
	GetDlgItem(IDC_BTN_FCMARK_LEFT)->MoveWindow(385, 190, 20, 20);
	GetDlgItem(IDC_BTN_FCMARK_RIGHT)->MoveWindow(425, 190, 20, 20);
	GetDlgItem(IDC_BTN_FCMARK_DOWN)->MoveWindow(405, 210, 20, 20);

	GetDlgItem(IDC_PIC_MARK)->MoveWindow(470, 70, 120, 120);
	GetDlgItem(IDC_STATIC_MATCHRATE)->MoveWindow(470, 210, 60, 20);
	GetDlgItem(IDC_EDIT_MATCHRATE)->MoveWindow(530, 210, 60, 20);

	GetDlgItem(IDC_BTN_RECIPE_LOAD)->MoveWindow(10, 287, 60, 30);
	GetDlgItem(IDC_EDIT_RECIPE_SELECT)->MoveWindow(80, 292, 50, 25);
	GetDlgItem(IDC_EDIT_RECIPE_NAME)->MoveWindow(140, 292, 150, 25);
	GetDlgItem(IDC_BTN_ADD)->MoveWindow(WindowWidth - 280, 287, 60, 30);
	GetDlgItem(IDC_BTN_MODIFY)->MoveWindow(WindowWidth - 210, 287, 60, 30);
	GetDlgItem(IDC_BTN_APPLY)->MoveWindow(WindowWidth - 140, 287, 60, 30);
	GetDlgItem(IDC_BTN_CANCEL)->MoveWindow(WindowWidth - 70, 287, 60, 30);


	HFONT staticFont;
	staticFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));

	GetDlgItem(IDC_STATIC_MATCHRATE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_BINARY)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_OPEN)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CLOSE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_START)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_END)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_PREPROCESS_SHOW2)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_BTN_PREPROCESS_APPLY)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_FCMARK_BINARY)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_FCMARK_OPEN)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_FCMARK_CLOSE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_GRP_FC_PARAM)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_GRP_ENROLL)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_GRP_PREPROCESS)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);

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
	GetDlgItem(IDC_BTN_FCMARK_PREPROCESS_APPLY)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_FCMARK_PREPROCESS_CANCEL)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_FCMARK_ENROLL)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_FCMARK_APPLY)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_FCMARK_CANCEL)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_FCMARK_UP)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_FCMARK_LEFT)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_FCMARK_RIGHT)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_FCMARK_DOWN)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_MODIFY)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_APPLY)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_CANCEL)->SetFont(btnFont);

	DisplayParam();
	EditEnable(false);

	ChkModify = false;
	bChkMarkFC = false;

	mMarkTracker.m_nStyle = 0;
	mMarkTracker.m_nStyle |= CRectTracker::dottedLine;
	mMarkTracker.m_nStyle |= CRectTracker::resizeOutside;

	//mRoiTracker.m_nStyle = 0;
	//mRoiTracker.m_nStyle |= CRectTracker::dottedLine;
	//mRoiTracker.m_nStyle |= CRectTracker::resizeOutside;


	nFCMarkThread = _ttoi(AfxGetApp()->GetProfileStringW(_T("FCMARK"), _T("THREAD")));
	nFCMarkOpen = _ttoi(AfxGetApp()->GetProfileStringW(_T("FCMARK"), _T("OPEN")));
	nFCMarkClose = _ttoi(AfxGetApp()->GetProfileStringW(_T("FCMARK"), _T("CLOSE")));

	m_edit_fcmark_binary_low.SetWindowTextW(AfxGetApp()->GetProfileStringW(_T("FCMARK"), _T("THREAD")));
	m_edit_fcmark_open.SetWindowTextW(AfxGetApp()->GetProfileStringW(_T("FCMARK"), _T("OPEN")));
	m_edit_fcmark_close.SetWindowTextW(AfxGetApp()->GetProfileStringW(_T("FCMARK"), _T("CLOSE")));


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL SettingFC::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}

		if (bChkMarkFC == true)
		{
			if (pMsg->wParam == VK_UP)
			{
				mMarkTracker.m_rect.top -= 1;
				mMarkTracker.m_rect.bottom -= 1;
			}

			if (pMsg->wParam == VK_DOWN)
			{
				mMarkTracker.m_rect.top += 1;
				mMarkTracker.m_rect.bottom += 1;
			}

			if (pMsg->wParam == VK_LEFT)
			{
				mMarkTracker.m_rect.left -= 1;
				mMarkTracker.m_rect.right -= 1;
			}

			if (pMsg->wParam == VK_RIGHT)
			{
				mMarkTracker.m_rect.left += 1;
				mMarkTracker.m_rect.right += 1;
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void SettingFC::DisplayParam()
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();
	CString strValue;

	strValue.Format(_T("%.2f%%"), pDlg->dMatchRate_FC);
	m_edit_matchrate.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), pDlg->StartPoint_FC.x);
	m_edit_fc_roi_start_x.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), pDlg->StartPoint_FC.y);
	m_edit_fc_roi_start_y.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), pDlg->EndPoint_FC.x);
	m_edit_fc_roi_end_x.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), pDlg->EndPoint_FC.y);
	m_edit_fc_roi_end_y.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), pDlg->nBinaryLow_FC);
	m_edit_binary_low.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), pDlg->nOpen_FC);
	m_edit_fc_open.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), pDlg->nClose_FC);
	m_edit_fc_close.SetWindowTextW(strValue);
}


void SettingFC::EditEnable(bool nCase)
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

	GetDlgItem(IDC_BTN_FCMARK_ENROLL)->EnableWindow(nCase);
	GetDlgItem(IDC_BTN_FCMARK_APPLY)->EnableWindow(false);
	GetDlgItem(IDC_BTN_FCMARK_CANCEL)->EnableWindow(false);

	GetDlgItem(IDC_BTN_FCMARK_UP)->EnableWindow(false);
	GetDlgItem(IDC_BTN_FCMARK_DOWN)->EnableWindow(false);
	GetDlgItem(IDC_BTN_FCMARK_LEFT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_FCMARK_RIGHT)->EnableWindow(false);

	m_edit_matchrate.EnableWindow(nCase);

	m_edit_fc_roi_start_x.EnableWindow(nCase);
	m_edit_fc_roi_start_y.EnableWindow(nCase);
	m_edit_fc_roi_end_x.EnableWindow(nCase);
	m_edit_fc_roi_end_y.EnableWindow(nCase);
	m_edit_binary_low.EnableWindow(nCase);
	m_edit_fc_open.EnableWindow(nCase);
	m_edit_fc_close.EnableWindow(nCase);

	GetDlgItem(IDC_BTN_PREPROCESS_SHOW2)->EnableWindow(nCase);
	GetDlgItem(IDC_BTN_PREPROCESS_APPLY)->EnableWindow(nCase);

	m_edit_fcmark_binary_low.EnableWindow(nCase);
	m_edit_fcmark_open.EnableWindow(nCase);
	m_edit_fcmark_close.EnableWindow(nCase);

	GetDlgItem(IDC_BTN_FCMARK_PREPROCESS_APPLY)->EnableWindow(nCase);
	GetDlgItem(IDC_BTN_FCMARK_PREPROCESS_CANCEL)->EnableWindow(nCase);


	GetDlgItem(IDC_EDIT_RECIPE_NAME)->EnableWindow(nCase);
	GetDlgItem(IDC_BTN_APPLY)->EnableWindow(nCase);
	GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(nCase);

}


void SettingFC::OnBnClickedBtnModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	EditEnable(true);

	//rectRoi = { pDlg->StartPoint_FC.x / 4, pDlg->StartPoint_FC.y / 4, pDlg->EndPoint_FC.x / 4, pDlg->EndPoint_FC.y / 4 };

	//mRoiTracker.m_rect = rectRoi;

	ChkModify = true;
}


void SettingFC::OnBnClickedBtnApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CString strValue;

	m_edit_matchrate.GetWindowTextW(strValue);
	pDlg->dMatchRate_FC = _wtof(strValue);

	m_edit_fc_roi_start_x.GetWindowTextW(strValue);
	pDlg->StartPoint_FC.x = _ttoi(strValue);

	m_edit_fc_roi_start_y.GetWindowTextW(strValue);
	pDlg->StartPoint_FC.y = _ttoi(strValue);

	m_edit_fc_roi_end_x.GetWindowTextW(strValue);
	pDlg->EndPoint_FC.x = _ttoi(strValue);

	m_edit_fc_roi_end_y.GetWindowTextW(strValue);
	pDlg->EndPoint_FC.y = _ttoi(strValue);

	m_edit_binary_low.GetWindowTextW(strValue);
	pDlg->nBinaryLow_FC = _ttoi(strValue);

	m_edit_fc_open.GetWindowTextW(strValue);
	pDlg->nOpen_FC = _ttoi(strValue);

	m_edit_fc_close.GetWindowTextW(strValue);
	pDlg->nClose_FC = _ttoi(strValue);

	pDlg->SaveRecipe(2);

	EditEnable(FALSE);

	m_edit_fcmark_binary_low.GetWindowTextW(strValue);
	AfxGetApp()->WriteProfileStringW(_T("FCMARK"), _T("THREAD"), strValue);
	nFCMarkThread = _ttoi(strValue);

	m_edit_fcmark_open.GetWindowTextW(strValue);
	AfxGetApp()->WriteProfileStringW(_T("FCMARK"), _T("OPEN"), strValue);
	nFCMarkOpen = _ttoi(strValue);

	m_edit_fcmark_close.GetWindowTextW(strValue);
	AfxGetApp()->WriteProfileStringW(_T("FCMARK"), _T("CLOSE"), strValue);
	nFCMarkClose = _ttoi(strValue);

	m_edit_recipe_name.GetWindowTextW(strValue);
	pDlg->dlgVisionSetting->dlgSettingCamera->m_edit_recipe_name.SetWindowTextW(strValue);
	pDlg->dlgVisionSetting->dlgSettingAlign->m_edit_recipe_name.SetWindowTextW(strValue);
	pDlg->dlgVisionSetting->dlgSettingAlignMark->m_edit_recipe_name.SetWindowTextW(strValue);

	stRecipe.strRecipeName[pDlg->nSelectRecipe - 1] = strValue;

	CString		strPath;
	CString		strTag;
	CString		strName;
	CString		strData;

	//rectRoi = { 0,0,0,0 };
	//mRoiTracker.m_rect = rectRoi;

	strPath = pDlg->strExeFilePath + _T("RecipeName.ini");
	strTag = _T("RecipeName");

	for (int i = 0; i < 100; i++)
	{
		strName.Format(_T("Recipe%d"), i + 1);

		strData = stRecipe.strRecipeName[i];
		WritePrivateProfileString(strTag, strName, strData, strPath);
	}

	// 기존 AlignMark를 Backup 에 복사
	Mat SaveImg;

	CString SaveFCMark;
	SaveFCMark = pDlg->strRecipeFilePath + _T("FieldCorrectionMark.bmp");
	CT2CA ConvertStringFC(SaveFCMark);
	std::string	ImageNameFC(ConvertStringFC);
	SaveImg = imread(ImageNameFC);

	CString SaveMark;
	SaveMark = pDlg->strRecipeFilePath + _T("FieldCorrectionMarkBackup.bmp");

	CT2CA ConvertStringMark(SaveMark);
	std::string	save_mark_path(ConvertStringMark);
	imwrite(save_mark_path, SaveImg);
}


void SettingFC::OnBnClickedBtnCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DisplayParam();

	//rectRoi = { 0,0,0,0 };
	//mRoiTracker.m_rect = rectRoi;

	EditEnable(FALSE);
}


void SettingFC::OnBnClickedBtnFcmarkEnroll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	rectMark = { 100, 100, 200, 200 };
	mMarkTracker.m_rect = rectMark;

	bChkMarkFC = true;

	GetDlgItem(IDC_BTN_FCMARK_ENROLL)->EnableWindow(false);
	GetDlgItem(IDC_BTN_FCMARK_APPLY)->EnableWindow(true);
	GetDlgItem(IDC_BTN_FCMARK_CANCEL)->EnableWindow(true);

	GetDlgItem(IDC_BTN_FCMARK_UP)->EnableWindow(true);
	GetDlgItem(IDC_BTN_FCMARK_DOWN)->EnableWindow(true);
	GetDlgItem(IDC_BTN_FCMARK_LEFT)->EnableWindow(true);
	GetDlgItem(IDC_BTN_FCMARK_RIGHT)->EnableWindow(true);

	ChkModify = false;
	//rectRoi = { 0,0,0,0 };
	//mRoiTracker.m_rect = rectRoi;
}


void SettingFC::OnBnClickedBtnFcmarkApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	GetDlgItem(IDC_BTN_FCMARK_ENROLL)->EnableWindow(true);
	GetDlgItem(IDC_BTN_FCMARK_APPLY)->EnableWindow(false);
	GetDlgItem(IDC_BTN_FCMARK_CANCEL)->EnableWindow(false);

	GetDlgItem(IDC_BTN_FCMARK_UP)->EnableWindow(false);
	GetDlgItem(IDC_BTN_FCMARK_DOWN)->EnableWindow(false);
	GetDlgItem(IDC_BTN_FCMARK_LEFT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_FCMARK_RIGHT)->EnableWindow(false);

	pDlg->ImageSave(4, false);
	pDlg->MarkExtraction(4);

	bChkMarkFC = false;

	rectMark = { 0, 0, 0, 0 };
	mMarkTracker.m_rect = rectMark;

	ChkModify = true;
	//rectRoi = { pDlg->StartPoint_FC.x / 4, pDlg->StartPoint_FC.y / 4, pDlg->EndPoint_FC.x / 4, pDlg->EndPoint_FC.y / 4 };

	//mRoiTracker.m_rect = rectRoi;
}


void SettingFC::OnBnClickedBtnFcmarkCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	GetDlgItem(IDC_BTN_FCMARK_ENROLL)->EnableWindow(true);
	GetDlgItem(IDC_BTN_FCMARK_APPLY)->EnableWindow(false);
	GetDlgItem(IDC_BTN_FCMARK_CANCEL)->EnableWindow(false);

	GetDlgItem(IDC_BTN_FCMARK_UP)->EnableWindow(false);
	GetDlgItem(IDC_BTN_FCMARK_DOWN)->EnableWindow(false);
	GetDlgItem(IDC_BTN_FCMARK_LEFT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_FCMARK_RIGHT)->EnableWindow(false);

	bChkMarkFC = false;

	rectMark = { 0, 0, 0, 0 };
	mMarkTracker.m_rect = rectMark;

	ChkModify = true;
}


void SettingFC::OnBnClickedBtnRecipeLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	pDlg->RecipeSelect();
}


void SettingFC::OnBnClickedBtnAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	pDlg->RecipeAdd();

	EditEnable(false);
}


void SettingFC::OnBnClickedBtnFcmarkUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mMarkTracker.m_rect.top -= 1;
	mMarkTracker.m_rect.bottom -= 1;
}


void SettingFC::OnBnClickedBtnFcmarkDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mMarkTracker.m_rect.top += 1;
	mMarkTracker.m_rect.bottom += 1;
}


void SettingFC::OnBnClickedBtnFcmarkLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mMarkTracker.m_rect.left -= 1;
	mMarkTracker.m_rect.right -= 1;
}


void SettingFC::OnBnClickedBtnFcmarkRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mMarkTracker.m_rect.left += 1;
	mMarkTracker.m_rect.right += 1;
}


void SettingFC::OnBnClickedBtnPreprocessApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CString strVal;
	int nVal;

	Mat LoadImg;
	Mat ProcessImg;
	Mat ImageOpen;	// MORPHOLOGY OPEN
	Mat ImageClose;	// MORPHOLOGY CLOSE
	CString FileName;

	pDlg->ImageSave(4, false);
	FileName = pDlg->strExeFilePath + _T("Data\\_OriginImage_5.bmp");

	CT2CA ConvertString(FileName);
	std::string	Image_path(ConvertString);

	// 원본 이미지 로딩
	LoadImg = imread(Image_path);

	ProcessImg = LoadImg.clone();

	m_edit_fc_open.GetWindowTextW(strVal);
	nVal = _ttoi(strVal);
	Mat ElementOpen(nVal, nVal, CV_8U, cv::Scalar(1));	// OPEN 파라미터

	m_edit_fc_close.GetWindowTextW(strVal);
	nVal = _ttoi(strVal);
	Mat ElementClose(nVal, nVal, CV_8U, cv::Scalar(1));	// CLOSE 파라미터


	// open, close morphology
	morphologyEx(ProcessImg, ImageOpen, cv::MORPH_OPEN, ElementOpen);
	morphologyEx(ImageOpen, ImageClose, cv::MORPH_CLOSE, ElementClose);

	m_edit_binary_low.GetWindowTextW(strVal);
	nVal = _ttoi(strVal);

	// binary
	threshold(ImageClose, ProcessImg, nVal, 255, THRESH_BINARY);


	CString SaveProcImg;

	SaveProcImg = pDlg->strExeFilePath + _T("Data\\_ProcImage_5.bmp");

	CT2CA ConvertStringImg(SaveProcImg);
	std::string	save_Img_path(ConvertStringImg);

	imwrite(save_Img_path, ProcessImg);
}


void SettingFC::OnBnClickedBtnPreprocessShow2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	pDlg->DisplayPreprocessImg(2, true);

}


void SettingFC::OnBnClickedBtnFcmarkPreprocessApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CString strVal;
	int nVal;

	Mat LoadMark;
	Mat MarkProcessImg;
	Mat ImageOpen;	// MORPHOLOGY OPEN
	Mat ImageClose;	// MORPHOLOGY CLOSE

	m_edit_fcmark_open.GetWindowTextW(strVal);
	nVal = _ttoi(strVal);
	Mat ElementOpen(nVal, nVal, CV_8U, cv::Scalar(1));	// OPEN 파라미터

	m_edit_fcmark_close.GetWindowTextW(strVal);
	nVal = _ttoi(strVal);
	Mat ElementClose(nVal, nVal, CV_8U, cv::Scalar(1));	// CLOSE 파라미터

	CString SaveAlignMark;
	SaveAlignMark = pDlg->strRecipeFilePath + _T("FieldCorrectionMark.bmp");
	CT2CA ConvertStringAlign(SaveAlignMark);
	std::string	ImageNameAlign(ConvertStringAlign);
	LoadMark = imread(ImageNameAlign);

	m_edit_fcmark_binary_low.GetWindowTextW(strVal);
	nVal = _ttoi(strVal);
	MarkProcessImg = LoadMark.clone();

	// open, close morphology
	morphologyEx(LoadMark, ImageOpen, cv::MORPH_OPEN, ElementOpen);
	morphologyEx(ImageOpen, ImageClose, cv::MORPH_CLOSE, ElementClose);

	// binary
	threshold(ImageClose, MarkProcessImg, nVal, 255, THRESH_BINARY);

	CString SaveMark;
	SaveMark = pDlg->strRecipeFilePath + _T("FieldCorrectionMark.bmp");

	CT2CA ConvertStringMark(SaveMark);
	std::string	save_mark_path(ConvertStringMark);

	imwrite(save_mark_path, MarkProcessImg);
}


void SettingFC::OnBnClickedBtnFcmarkPreprocessCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	Mat procImg;

	CString SaveAlignMark;
	SaveAlignMark = pDlg->strRecipeFilePath + _T("FieldCorrectionMarkOrigin.bmp");
	CT2CA ConvertStringAlign(SaveAlignMark);
	std::string	ImageNameAlign(ConvertStringAlign);
	procImg = imread(ImageNameAlign);

	CString SaveMark;
	SaveMark = pDlg->strRecipeFilePath + _T("FieldCorrectionMark.bmp");

	CT2CA ConvertStringMark(SaveMark);
	std::string	save_mark_path(ConvertStringMark);

	imwrite(save_mark_path, procImg);
}

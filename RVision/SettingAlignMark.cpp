// SettingAlignMark.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "SettingAlignMark.h"
#include "afxdialogex.h"

#include "RVisionDlg.h"
// SettingAlignMark 대화 상자

IMPLEMENT_DYNAMIC(SettingAlignMark, CDialogEx)

extern RecipeName stRecipe;
extern AlignParameter	stAlign;
extern EdgeAlignParameter stEdgeAlign;
extern MarkAlignParameter stMarkAlign;

SettingAlignMark::SettingAlignMark(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_ALIGNMARK, pParent)
{

}

SettingAlignMark::~SettingAlignMark()
{
}

void SettingAlignMark::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_SELECTCAM, m_cmb_selectcam);
	DDX_Control(pDX, IDC_EDIT_RECIPE_SELECT, m_edit_recipe_select);
	DDX_Control(pDX, IDC_EDIT_RECIPE_NAME, m_edit_recipe_name);
	DDX_Control(pDX, IDC_EDIT_MARK_MATCHRATE, m_edit_mark_matchrate);
	DDX_Control(pDX, IDC_EDIT_MARK_THREAD, m_edit_mark_thread);
	DDX_Control(pDX, IDC_EDIT_MARK_OPEN, m_edit_mark_open);
	DDX_Control(pDX, IDC_EDIT_MARK_CLOSE, m_edit_mark_close);
}


BEGIN_MESSAGE_MAP(SettingAlignMark, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_RECIPE_LOAD, &SettingAlignMark::OnBnClickedBtnRecipeLoad)
	ON_BN_CLICKED(IDC_BTN_ADD, &SettingAlignMark::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_MODIFY, &SettingAlignMark::OnBnClickedBtnModify)
	ON_BN_CLICKED(IDC_BTN_APPLY, &SettingAlignMark::OnBnClickedBtnApply)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &SettingAlignMark::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BTN_MARK_REG, &SettingAlignMark::OnBnClickedBtnMarkReg)
	ON_BN_CLICKED(IDC_BTN_MARK_APPLY, &SettingAlignMark::OnBnClickedBtnMarkApply)
	ON_BN_CLICKED(IDC_BTN_MARK_CANCEL, &SettingAlignMark::OnBnClickedBtnMarkCancel)
	ON_BN_CLICKED(IDC_BTN_MARK_UP, &SettingAlignMark::OnBnClickedBtnMarkUp)
	ON_BN_CLICKED(IDC_BTN_MARK_DOWN, &SettingAlignMark::OnBnClickedBtnMarkDown)
	ON_BN_CLICKED(IDC_BTN_MARK_LEFT, &SettingAlignMark::OnBnClickedBtnMarkLeft)
	ON_BN_CLICKED(IDC_BTN_MARK_RIGHT, &SettingAlignMark::OnBnClickedBtnMarkRight)
	ON_BN_CLICKED(IDC_BTN_PREPROCESS_APPLY, &SettingAlignMark::OnBnClickedBtnPreprocessApply)
	ON_BN_CLICKED(IDC_BTN_PREPROCESS_CANCEL, &SettingAlignMark::OnBnClickedBtnPreprocessCancel)
	ON_BN_CLICKED(IDC_BTN_MARK_MEASURE, &SettingAlignMark::OnBnClickedBtnMarkMeasure)
	ON_CBN_SELCHANGE(IDC_CMB_SELECTCAM, &SettingAlignMark::OnCbnSelchangeCmbSelectcam)
END_MESSAGE_MAP()


// SettingAlignMark 메시지 처리기


int SettingAlignMark::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH SettingAlignMark::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL SettingAlignMark::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	GetDlgItem(IDC_GRP_MEASUREMENT)->MoveWindow(10, 40, 150, 180);
	GetDlgItem(IDC_BTN_MARK_MEASURE)->MoveWindow(30, 70, 70, 20);
	GetDlgItem(IDC_STATIC_MARK_MEASURE_X)->MoveWindow(30, 120, 30, 20);
	GetDlgItem(IDC_STATIC_MARK_MEASURE_Y)->MoveWindow(30, 150, 30, 20);
	GetDlgItem(IDC_STATIC_MARK_MEASURE_RATE)->MoveWindow(30, 180, 60, 20);
	GetDlgItem(IDC_STATIC_MARK_MEASURE_X_VALUE)->MoveWindow(80, 120, 70, 20);
	GetDlgItem(IDC_STATIC_MARK_MEASURE_Y_VALUE)->MoveWindow(80, 150, 70, 20);
	GetDlgItem(IDC_STATIC_MARK_MEASURE_RATE_VALUE)->MoveWindow(100, 180, 50, 20);

	GetDlgItem(IDC_GRP_PREPROCESS)->MoveWindow(180, 40, 160, 180);
	GetDlgItem(IDC_STATIC_MARK_THREAD)->MoveWindow(200, 70, 70, 20);
	GetDlgItem(IDC_STATIC_MARK_OPEN)->MoveWindow(200, 100, 70, 20);
	GetDlgItem(IDC_STATIC_MARK_CLOSE)->MoveWindow(200, 130, 70, 20);
	GetDlgItem(IDC_EDIT_MARK_THREAD)->MoveWindow(280, 70, 50, 20);
	GetDlgItem(IDC_EDIT_MARK_OPEN)->MoveWindow(280, 100, 50, 20);
	GetDlgItem(IDC_EDIT_MARK_CLOSE)->MoveWindow(280, 130, 50, 20);
	GetDlgItem(IDC_BTN_PREPROCESS_APPLY)->MoveWindow(200, 180, 60, 20);
	GetDlgItem(IDC_BTN_PREPROCESS_CANCEL)->MoveWindow(270, 180, 60, 20);

	GetDlgItem(IDC_GRP_MARK)->MoveWindow(360, 40, 240, 220);
	GetDlgItem(IDC_BTN_MARK_REG)->MoveWindow(380, 70, 70, 20);
	GetDlgItem(IDC_BTN_MARK_APPLY)->MoveWindow(380, 100, 70, 20);
	GetDlgItem(IDC_BTN_MARK_CANCEL)->MoveWindow(380, 130, 70, 20);
	GetDlgItem(IDC_BTN_MARK_UP)->MoveWindow(405, 170, 20, 20);
	GetDlgItem(IDC_BTN_MARK_LEFT)->MoveWindow(385, 190, 20, 20);
	GetDlgItem(IDC_BTN_MARK_RIGHT)->MoveWindow(425, 190, 20, 20);
	GetDlgItem(IDC_BTN_MARK_DOWN)->MoveWindow(405, 210, 20, 20);
	GetDlgItem(IDC_PIC_MARK)->MoveWindow(470, 70, 120, 120);
	GetDlgItem(IDC_STATIC_MARK_MATCHRATE)->MoveWindow(470, 210, 60, 20);
	GetDlgItem(IDC_EDIT_MARK_MATCHRATE)->MoveWindow(530, 210, 60, 20);


	GetDlgItem(IDC_CMB_SELECTCAM)->MoveWindow(WindowWidth - 90, 0, 90, 30);
	GetDlgItem(IDC_BTN_RECIPE_LOAD)->MoveWindow(10, 287, 60, 30);
	GetDlgItem(IDC_EDIT_RECIPE_SELECT)->MoveWindow(80, 292, 50, 25);
	GetDlgItem(IDC_EDIT_RECIPE_NAME)->MoveWindow(140, 292, 150, 25);
	GetDlgItem(IDC_BTN_ADD)->MoveWindow(WindowWidth - 280, 287, 60, 30);
	GetDlgItem(IDC_BTN_MODIFY)->MoveWindow(WindowWidth - 210, 287, 60, 30);
	GetDlgItem(IDC_BTN_APPLY)->MoveWindow(WindowWidth - 140, 287, 60, 30);
	GetDlgItem(IDC_BTN_CANCEL)->MoveWindow(WindowWidth - 70, 287, 60, 30);

	HFONT staticFont;
	staticFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_GRP_MARK)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_GRP_MEASUREMENT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_GRP_PREPROCESS)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MARK_MEASURE_X)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MARK_MEASURE_Y)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MARK_MEASURE_RATE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MARK_MEASURE_X_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MARK_MEASURE_Y_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MARK_MEASURE_RATE_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MARK_THREAD)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MARK_OPEN)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MARK_CLOSE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MARK_MATCHRATE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);

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

	GetDlgItem(IDC_BTN_MARK_MEASURE)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_MARK_REG)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_MARK_APPLY)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_MARK_CANCEL)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_MARK_UP)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_MARK_LEFT)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_MARK_RIGHT)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_MARK_DOWN)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_PREPROCESS_APPLY)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_PREPROCESS_CANCEL)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_RECIPE_LOAD)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_ADD)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_MODIFY)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_APPLY)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_CANCEL)->SetFont(btnFont);

	EditEnable(FALSE);
	DisplayParam();

	m_cmb_selectcam.SetCurSel(0);

	mMarkTracker.m_nStyle = 0;
	mMarkTracker.m_nStyle |= CRectTracker::dottedLine;
	mMarkTracker.m_nStyle |= CRectTracker::resizeOutside;

	nMarkThread = _ttoi(AfxGetApp()->GetProfileStringW(_T("MARK"), _T("THREAD")));
	nMarkOpen = _ttoi(AfxGetApp()->GetProfileStringW(_T("MARK"), _T("OPEN")));
	nMarkClose = _ttoi(AfxGetApp()->GetProfileStringW(_T("MARK"), _T("CLOSE")));

	m_edit_mark_thread.SetWindowTextW(AfxGetApp()->GetProfileStringW(_T("MARK"), _T("THREAD")));
	m_edit_mark_open.SetWindowTextW(AfxGetApp()->GetProfileStringW(_T("MARK"), _T("OPEN")));
	m_edit_mark_close.SetWindowTextW(AfxGetApp()->GetProfileStringW(_T("MARK"), _T("CLOSE")));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL SettingAlignMark::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void SettingAlignMark::EditEnable(bool nCase)
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	if (nCase == true)
	{
		GetDlgItem(IDC_BTN_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
	}

	else if (nCase == false)
	{
		GetDlgItem(IDC_BTN_MODIFY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ADD)->EnableWindow(TRUE);

		GetDlgItem(IDC_BTN_MARK_APPLY)->EnableWindow(false);
		GetDlgItem(IDC_BTN_MARK_CANCEL)->EnableWindow(false);

		GetDlgItem(IDC_BTN_MARK_UP)->EnableWindow(nCase);
		GetDlgItem(IDC_BTN_MARK_DOWN)->EnableWindow(nCase);
		GetDlgItem(IDC_BTN_MARK_LEFT)->EnableWindow(nCase);
		GetDlgItem(IDC_BTN_MARK_RIGHT)->EnableWindow(nCase);

		bChkMarkAlign = false;

		for (int i = 0; i < 4; i++)
		{
			stMarkAlign.ChkManualFind[i] = false;
		}

		rectMark = { 0, 0, 0, 0 };
		mMarkTracker.m_rect = rectMark;
	}

	GetDlgItem(IDC_BTN_MARK_MEASURE)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_MARK_MEASURE_X_VALUE)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_MARK_MEASURE_Y_VALUE)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_MARK_MEASURE_RATE_VALUE)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_MARK_THREAD)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_MARK_OPEN)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_MARK_CLOSE)->EnableWindow(nCase);
	GetDlgItem(IDC_BTN_PREPROCESS_APPLY)->EnableWindow(nCase);
	GetDlgItem(IDC_BTN_PREPROCESS_CANCEL)->EnableWindow(nCase);
	GetDlgItem(IDC_EDIT_MARK_MATCHRATE)->EnableWindow(nCase);
	GetDlgItem(IDC_BTN_MARK_REG)->EnableWindow(nCase);


	GetDlgItem(IDC_EDIT_RECIPE_NAME)->EnableWindow(nCase);
	GetDlgItem(IDC_BTN_APPLY)->EnableWindow(nCase);
	GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(nCase);
}


void SettingAlignMark::DisplayParam()
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();
	CString strValue;

	strValue.Format(_T("%.2f%%"), pDlg->dAlignMatchrate);
	m_edit_mark_matchrate.SetWindowTextW(strValue);
}


void SettingAlignMark::OnBnClickedBtnRecipeLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();
	pDlg->RecipeSelect();
}


void SettingAlignMark::OnBnClickedBtnAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	pDlg->RecipeAdd();
	EditEnable(FALSE);
}


void SettingAlignMark::OnBnClickedBtnModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	EditEnable(true);
}


void SettingAlignMark::OnBnClickedBtnApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CString strValue;

	m_edit_mark_matchrate.GetWindowTextW(strValue);
	pDlg->dAlignMatchrate = _wtof(strValue);

	pDlg->SaveRecipe(1);

	EditEnable(FALSE);

	m_edit_mark_thread.GetWindowTextW(strValue);
	AfxGetApp()->WriteProfileStringW(_T("MARK"), _T("THREAD"), strValue);
	nMarkThread = _ttoi(strValue);

	m_edit_mark_open.GetWindowTextW(strValue);
	AfxGetApp()->WriteProfileStringW(_T("MARK"), _T("OPEN"), strValue);
	nMarkOpen = _ttoi(strValue);
	
	m_edit_mark_close.GetWindowTextW(strValue);
	AfxGetApp()->WriteProfileStringW(_T("MARK"), _T("CLOSE"), strValue);
	nMarkClose = _ttoi(strValue);

	// 기존 AlignMark를 Backup 에 복사
	Mat SaveImg;

	CString SaveAlignMark;
	SaveAlignMark = pDlg->strRecipeFilePath + _T("AlignMark.bmp");
	CT2CA ConvertStringAlign(SaveAlignMark);
	std::string	ImageNameAlign(ConvertStringAlign);
	SaveImg = imread(ImageNameAlign);

	CString SaveMark;
	SaveMark = pDlg->strRecipeFilePath + _T("AlignMarkBackup.bmp");

	CT2CA ConvertStringMark(SaveMark);
	std::string	save_mark_path(ConvertStringMark);
	imwrite(save_mark_path, SaveImg);

	m_edit_recipe_name.GetWindowTextW(strValue);
	pDlg->dlgVisionSetting->dlgSettingCamera->m_edit_recipe_name.SetWindowTextW(strValue);
	pDlg->dlgVisionSetting->dlgSettingAlign->m_edit_recipe_name.SetWindowTextW(strValue);
	pDlg->dlgVisionSetting->dlgSettingFC->m_edit_recipe_name.SetWindowTextW(strValue);

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


void SettingAlignMark::OnBnClickedBtnCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	DisplayParam();

	EditEnable(FALSE);

	CString strRegValue;

	strRegValue.Format(_T("%d"), nMarkThread);
	m_edit_mark_thread.SetWindowTextW(strRegValue);

	strRegValue.Format(_T("%d"), nMarkOpen);
	m_edit_mark_open.SetWindowTextW(strRegValue);

	strRegValue.Format(_T("%d"), nMarkClose);
	m_edit_mark_close.SetWindowTextW(strRegValue);

	Mat procImg;

	CString SaveAlignMark;
	SaveAlignMark = pDlg->strRecipeFilePath + _T("AlignMarkBackup.bmp");
	CT2CA ConvertStringAlign(SaveAlignMark);
	std::string	ImageNameAlign(ConvertStringAlign);
	procImg = imread(ImageNameAlign);

	CString SaveMark;
	SaveMark = pDlg->strRecipeFilePath + _T("AlignMark.bmp");

	CT2CA ConvertStringMark(SaveMark);
	std::string	save_mark_path(ConvertStringMark);

	imwrite(save_mark_path, procImg);
}


void SettingAlignMark::OnBnClickedBtnMarkReg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	rectMark = { 100, 100, 200, 200 };
	mMarkTracker.m_rect = rectMark;

	bChkMarkAlign = true;

	GetDlgItem(IDC_BTN_MARK_REG)->EnableWindow(false);

	GetDlgItem(IDC_BTN_MARK_APPLY)->EnableWindow(true);
	GetDlgItem(IDC_BTN_MARK_CANCEL)->EnableWindow(true);

	GetDlgItem(IDC_BTN_MARK_UP)->EnableWindow(true);
	GetDlgItem(IDC_BTN_MARK_DOWN)->EnableWindow(true);
	GetDlgItem(IDC_BTN_MARK_LEFT)->EnableWindow(true);
	GetDlgItem(IDC_BTN_MARK_RIGHT)->EnableWindow(true);
}


void SettingAlignMark::OnBnClickedBtnMarkApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	GetDlgItem(IDC_BTN_MARK_REG)->EnableWindow(true);
	GetDlgItem(IDC_BTN_MARK_APPLY)->EnableWindow(false);
	GetDlgItem(IDC_BTN_MARK_CANCEL)->EnableWindow(false);

	GetDlgItem(IDC_BTN_MARK_UP)->EnableWindow(false);
	GetDlgItem(IDC_BTN_MARK_DOWN)->EnableWindow(false);
	GetDlgItem(IDC_BTN_MARK_LEFT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_MARK_RIGHT)->EnableWindow(false);

	pDlg->ImageSave(SelectCam, false);
	pDlg->MarkExtraction(SelectCam);

	bChkMarkAlign = false;

	rectMark = { 0, 0, 0, 0 };
	mMarkTracker.m_rect = rectMark;
}


void SettingAlignMark::OnBnClickedBtnMarkCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	GetDlgItem(IDC_BTN_MARK_REG)->EnableWindow(true);
	GetDlgItem(IDC_BTN_MARK_APPLY)->EnableWindow(false);
	GetDlgItem(IDC_BTN_MARK_CANCEL)->EnableWindow(false);

	GetDlgItem(IDC_BTN_MARK_UP)->EnableWindow(false);
	GetDlgItem(IDC_BTN_MARK_DOWN)->EnableWindow(false);
	GetDlgItem(IDC_BTN_MARK_LEFT)->EnableWindow(false);
	GetDlgItem(IDC_BTN_MARK_RIGHT)->EnableWindow(false);

	bChkMarkAlign = false;
}


void SettingAlignMark::OnBnClickedBtnMarkUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mMarkTracker.m_rect.top -= 1;
	mMarkTracker.m_rect.bottom -= 1;
}


void SettingAlignMark::OnBnClickedBtnMarkDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mMarkTracker.m_rect.top += 1;
	mMarkTracker.m_rect.bottom += 1;
}


void SettingAlignMark::OnBnClickedBtnMarkLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mMarkTracker.m_rect.left -= 1;
	mMarkTracker.m_rect.right -= 1;
}


void SettingAlignMark::OnBnClickedBtnMarkRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mMarkTracker.m_rect.left += 1;
	mMarkTracker.m_rect.right += 1;
}


void SettingAlignMark::OnBnClickedBtnPreprocessApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CString strVal;
	int nVal;

	Mat LoadMark;
	Mat MarkProcessImg;
	Mat ImageOpen;	// MORPHOLOGY OPEN
	Mat ImageClose;	// MORPHOLOGY CLOSE

	m_edit_mark_open.GetWindowTextW(strVal);
	nVal = _ttoi(strVal);
	Mat ElementOpen(nVal, nVal, CV_8U, cv::Scalar(1));	// OPEN 파라미터

	m_edit_mark_close.GetWindowTextW(strVal);
	nVal = _ttoi(strVal);
	Mat ElementClose(nVal, nVal, CV_8U, cv::Scalar(1));	// CLOSE 파라미터

	CString SaveAlignMark;
	SaveAlignMark = pDlg->strRecipeFilePath + _T("AlignMark.bmp");
	CT2CA ConvertStringAlign(SaveAlignMark);
	std::string	ImageNameAlign(ConvertStringAlign);
	LoadMark = imread(ImageNameAlign);

	m_edit_mark_thread.GetWindowTextW(strVal);
	nVal = _ttoi(strVal);
	MarkProcessImg = LoadMark.clone();

	// open, close morphology
	morphologyEx(LoadMark, ImageOpen, cv::MORPH_OPEN, ElementOpen);
	morphologyEx(ImageOpen, ImageClose, cv::MORPH_CLOSE, ElementClose);

	// binary
	threshold(ImageClose, MarkProcessImg, nVal, 255, THRESH_BINARY);

	CString SaveMark;
	SaveMark = pDlg->strRecipeFilePath + _T("AlignMark.bmp");

	CT2CA ConvertStringMark(SaveMark);
	std::string	save_mark_path(ConvertStringMark);

	imwrite(save_mark_path, MarkProcessImg);
}


void SettingAlignMark::OnBnClickedBtnPreprocessCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	Mat procImg;

	CString SaveAlignMark;
	SaveAlignMark = pDlg->strRecipeFilePath + _T("AlignMarkOrigin.bmp");
	CT2CA ConvertStringAlign(SaveAlignMark);
	std::string	ImageNameAlign(ConvertStringAlign);
	procImg = imread(ImageNameAlign);

	CString SaveMark;
	SaveMark = pDlg->strRecipeFilePath + _T("AlignMark.bmp");

	CT2CA ConvertStringMark(SaveMark);
	std::string	save_mark_path(ConvertStringMark);

	imwrite(save_mark_path, procImg);
}


void SettingAlignMark::OnBnClickedBtnMarkMeasure()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	pDlg->MarkFind(SelectCam, 1);
}


void SettingAlignMark::OnCbnSelchangeCmbSelectcam()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	int nCase;

	nCase = m_cmb_selectcam.GetCurSel();
	SelectCam = nCase;
}

// SettingAlign.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "SettingAlign.h"
#include "afxdialogex.h"

#include "RVisionDlg.h"

// SettingAlign 대화 상자

IMPLEMENT_DYNAMIC(SettingAlign, CDialogEx)

extern RecipeName stRecipe;
extern AlignParameter	stAlign;
extern EdgeAlignParameter stEdgeAlign;


SettingAlign::SettingAlign(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_ALIGN, pParent)
{

}

SettingAlign::~SettingAlign()
{
}

void SettingAlign::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_EDGE_ROI_START_X, m_edit_edge_roi_start_x);
	DDX_Control(pDX, IDC_EDIT_EDGE_ROI_START_Y, m_edit_edge_roi_start_y);
	DDX_Control(pDX, IDC_EDIT_EDGE_ROI_END_X, m_edit_edge_roi_end_x);
	DDX_Control(pDX, IDC_EDIT_EDGE_ROI_END_Y, m_edit_edge_roi_end_y);
	DDX_Control(pDX, IDC_EDIT_BINARY_LOW, m_edit_binary_low);
	DDX_Control(pDX, IDC_CMB_SELECTCAM, m_cmb_selectcam);
	DDX_Control(pDX, IDC_BTN_EDGE, m_btn_edge);
	DDX_Control(pDX, IDC_BTN_MARK, m_btn_mark);
	DDX_Control(pDX, IDC_EDIT_X_RANGE, m_edit_x_range);
	DDX_Control(pDX, IDC_EDIT_Y_RANGE, m_edit_y_range);
	DDX_Control(pDX, IDC_EDIT_T_RANGE, m_edit_t_range);
	DDX_Control(pDX, IDC_EDIT_RECIPE_SELECT, m_edit_recipe_select);
	DDX_Control(pDX, IDC_EDIT_RECIPE_NAME, m_edit_recipe_name);
	DDX_Control(pDX, IDC_EDIT_XOFFSET, m_edit_xoffset);
	DDX_Control(pDX, IDC_EDIT_YOFFSET, m_edit_yoffset);
	DDX_Control(pDX, IDC_EDIT_OPEN, m_edit_open);
	DDX_Control(pDX, IDC_EDIT_CLOSE, m_edit_close);
	DDX_Control(pDX, IDC_BTN_PREPROCESS_APPLY, m_btn_preprocess_apply);
	DDX_Control(pDX, IDC_BTN_PREPROCESS_SHOW, m_btn_preprocess_show);
	DDX_Control(pDX, IDC_PIC_MARK_POS, m_pic_mark_pos);
	DDX_Control(pDX, IDC_EDIT_ALIGN_WIDTH, m_edit_align_width);
	DDX_Control(pDX, IDC_EDIT_ALIGN_HEIGHT, m_edit_align_height);
	DDX_Control(pDX, IDC_EDIT_LEVEL_RANGE, m_edit_level_range);
	DDX_Control(pDX, IDC_EDIT_MISTAKE_RANGE, m_edit_mistake_range);
	DDX_Control(pDX, IDC_EDIT_TOFFSET, m_edit_toffset);
	DDX_Control(pDX, IDC_BTN_ALIGN_METHOD, m_btn_align_method);
}


BEGIN_MESSAGE_MAP(SettingAlign, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_BTN_APPLY, &SettingAlign::OnBnClickedBtnApply)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &SettingAlign::OnBnClickedBtnCancel)
	ON_BN_CLICKED(IDC_BTN_MODIFY, &SettingAlign::OnBnClickedBtnModify)
	ON_EN_CHANGE(IDC_EDIT_EDGE_ROI_START_X, &SettingAlign::OnEnChangeEditEdgeRoiStartX)
	ON_EN_CHANGE(IDC_EDIT_EDGE_ROI_START_Y, &SettingAlign::OnEnChangeEditEdgeRoiStartY)
	ON_EN_CHANGE(IDC_EDIT_EDGE_ROI_END_X, &SettingAlign::OnEnChangeEditEdgeRoiEndX)
	ON_EN_CHANGE(IDC_EDIT_EDGE_ROI_END_Y, &SettingAlign::OnEnChangeEditEdgeRoiEndY)
	ON_CBN_SELCHANGE(IDC_CMB_SELECTCAM, &SettingAlign::OnCbnSelchangeCmbSelectcam)
	ON_BN_CLICKED(IDC_BTN_EDGE, &SettingAlign::OnBnClickedBtnEdge)
	ON_BN_CLICKED(IDC_BTN_MARK, &SettingAlign::OnBnClickedBtnMark)
	ON_BN_CLICKED(IDC_BTN_RECIPE_LOAD, &SettingAlign::OnBnClickedBtnRecipeLoad)
	ON_BN_CLICKED(IDC_BTN_ADD, &SettingAlign::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_PREPROCESS_APPLY, &SettingAlign::OnBnClickedBtnPreprocessApply)
	ON_BN_CLICKED(IDC_BTN_PREPROCESS_SHOW, &SettingAlign::OnBnClickedBtnPreprocessShow)
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_BTN_ALIGN_METHOD, &SettingAlign::OnBnClickedBtnAlignMethod)
END_MESSAGE_MAP()


// SettingAlign 메시지 처리기


int SettingAlign::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH SettingAlign::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL SettingAlign::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL SettingAlign::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	GetDlgItem(IDC_GRP_PARAM)->MoveWindow(10, 40, 180, 180);
	GetDlgItem(IDC_STATIC_X_RANGE)->MoveWindow(30, 60, 70, 20);
	GetDlgItem(IDC_EDIT_X_RANGE)->MoveWindow(110, 60, 60, 20);
	GetDlgItem(IDC_STATIC_Y_RANGE)->MoveWindow(30, 90, 70, 20);
	GetDlgItem(IDC_EDIT_Y_RANGE)->MoveWindow(110, 90, 60, 20);
	GetDlgItem(IDC_STATIC_T_RANGE)->MoveWindow(30, 120, 70, 20);
	GetDlgItem(IDC_EDIT_T_RANGE)->MoveWindow(110, 120, 60, 20);
	GetDlgItem(IDC_STATIC_LEVEL_RANGE)->MoveWindow(30, 150, 70, 20);
	GetDlgItem(IDC_EDIT_LEVEL_RANGE)->MoveWindow(110, 150, 60, 20);
	GetDlgItem(IDC_STATIC_MISTAKE_RANGE)->MoveWindow(30, 180, 70, 20);
	GetDlgItem(IDC_EDIT_MISTAKE_RANGE)->MoveWindow(110, 180, 60, 20);


	/*GetDlgItem(IDC_STATIC_START)->MoveWindow(30, 150, 70, 20);
	GetDlgItem(IDC_EDIT_EDGE_ROI_START_X)->MoveWindow(40, 180, 60, 20);
	GetDlgItem(IDC_EDIT_EDGE_ROI_START_Y)->MoveWindow(110, 180, 60, 20);
	GetDlgItem(IDC_STATIC_END)->MoveWindow(30, 210, 70, 20);
	GetDlgItem(IDC_EDIT_EDGE_ROI_END_X)->MoveWindow(40, 240, 60, 20);
	GetDlgItem(IDC_EDIT_EDGE_ROI_END_Y)->MoveWindow(110, 240, 60, 20);*/

	GetDlgItem(IDC_GRP_PREPROCESS)->MoveWindow(210, 40, 180, 150);
	GetDlgItem(IDC_STATIC_BINARY)->MoveWindow(230, 60, 60, 20);
	GetDlgItem(IDC_EDIT_BINARY_LOW)->MoveWindow(310, 60, 60, 20);
	GetDlgItem(IDC_STATIC_OPEN)->MoveWindow(230, 90, 60, 20);
	GetDlgItem(IDC_EDIT_OPEN)->MoveWindow(310, 90, 60, 20);
	GetDlgItem(IDC_STATIC_CLOSE)->MoveWindow(230, 120, 60, 20);
	GetDlgItem(IDC_EDIT_CLOSE)->MoveWindow(310, 120, 60, 20);
	GetDlgItem(IDC_BTN_PREPROCESS_SHOW)->MoveWindow(240, 160, 60, 20);
	GetDlgItem(IDC_BTN_PREPROCESS_APPLY)->MoveWindow(310, 160, 60, 20);

	GetDlgItem(IDC_GRP_POSTPROCESS)->MoveWindow(10, 230, 430, 50);
	GetDlgItem(IDC_STATIC_XOFFSET)->MoveWindow(20, 250, 70, 20);
	GetDlgItem(IDC_EDIT_XOFFSET)->MoveWindow(90, 250, 60, 20);
	GetDlgItem(IDC_STATIC_YOFFSET)->MoveWindow(160, 250, 70, 20);
	GetDlgItem(IDC_EDIT_YOFFSET)->MoveWindow(230, 250, 60, 20);
	GetDlgItem(IDC_STATIC_TOFFSET)->MoveWindow(300, 250, 70, 20);
	GetDlgItem(IDC_EDIT_TOFFSET)->MoveWindow(370, 250, 60, 20);

	GetDlgItem(IDC_BTN_EDGE)->MoveWindow(470, 60, 60, 20);
	GetDlgItem(IDC_BTN_MARK)->MoveWindow(540, 60, 60, 20);
	GetDlgItem(IDC_BTN_ALIGN_METHOD)->MoveWindow(520, 30, 80, 20);
	GetDlgItem(IDC_EDIT_ALIGN_WIDTH)->MoveWindow(505, 120, 50, 20);
	GetDlgItem(IDC_EDIT_ALIGN_HEIGHT)->MoveWindow(410, 190, 50, 20);
	GetDlgItem(IDC_PIC_MARK_POS)->MoveWindow(470, 150, 120, 100);

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
	GetDlgItem(IDC_GRP_PARAM)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_GRP_MARK)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_GRP_PREPROCESS)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_GRP_POSTPROCESS)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_START)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_END)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_BINARY)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MATCHRATE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_X_RANGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_Y_RANGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_T_RANGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LEVEL_RANGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MISTAKE_RANGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_OPEN)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CLOSE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_XOFFSET)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_YOFFSET)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TOFFSET)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);


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


	GetDlgItem(IDC_BTN_EDGE)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_MARK)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_ALIGN_METHOD)->SetFont(btnFont);

	GetDlgItem(IDC_BTN_PREPROCESS_SHOW)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_PREPROCESS_APPLY)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_RECIPE_LOAD)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_ADD)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_MODIFY)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_APPLY)->SetFont(btnFont);
	GetDlgItem(IDC_BTN_CANCEL)->SetFont(btnFont);

	ChkModify = false;

	//ChangeCamera(0);
	DisplayParam(0);

	EditEnable(false);

	m_cmb_selectcam.SetCurSel(0);

	mRoiTracker.m_nStyle = 0;
	mRoiTracker.m_nStyle |= CRectTracker::dottedLine;
	mRoiTracker.m_nStyle |= CRectTracker::resizeOutside;

//	m_edit_xoffset.SetWindowTextW(AfxGetApp()->GetProfileStringW(_T("ALIGN"), _T("XOFFSET")));
//	m_edit_yoffset.SetWindowTextW(AfxGetApp()->GetProfileStringW(_T("ALIGN"), _T("YOFFSET")));


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL SettingAlign::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}

		/*	if (bChkMarkAlign == true)
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
			}*/
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void SettingAlign::DisplayParam(int nCase)
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();
	CString strValue;

	strValue.Format(_T("%d"), stAlign.nBinaryLow[nCase]);
	m_edit_binary_low.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), stAlign.nOpen[nCase]);
	m_edit_open.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), stAlign.nClose[nCase]);
	m_edit_close.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), stAlign.ROIStart[nCase].x);
	m_edit_edge_roi_start_x.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), stAlign.ROIStart[nCase].y);
	m_edit_edge_roi_start_y.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), stAlign.ROIEnd[nCase].x);
	m_edit_edge_roi_end_x.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), stAlign.ROIEnd[nCase].y);
	m_edit_edge_roi_end_y.SetWindowTextW(strValue);

	pDlg->nAlignMethod = pDlg->nSelecteAlignMethod;

	if (pDlg->bChkMark == 1 && pDlg->bChkEdge == 0)
	{
		m_btn_edge.SetFaceColor(ColorBasic);
		m_btn_mark.SetFaceColor(ColorGreen);

		m_pic_mark_pos.SetBitmap(pDlg->m_bmp_markpos);
	}

	else if (pDlg->bChkEdge == 1 && pDlg->bChkMark == 0)
	{
		m_btn_edge.SetFaceColor(ColorGreen);
		m_btn_mark.SetFaceColor(ColorBasic);

		m_pic_mark_pos.SetBitmap(pDlg->m_bmp_edgepos);
	}

	strValue.Format(_T("%.3f"), pDlg->dRangeHLevel);
	m_edit_level_range.SetWindowTextW(strValue);

	strValue.Format(_T("%.3f"), pDlg->dRangeMistake);
	m_edit_mistake_range.SetWindowTextW(strValue);

	strValue.Format(_T("%.3f"), pDlg->dRangeX);
	m_edit_x_range.SetWindowTextW(strValue);

	strValue.Format(_T("%.3f"), pDlg->dRangeY);
	m_edit_y_range.SetWindowTextW(strValue);

	strValue.Format(_T("%.3f"), pDlg->dRangeT);
	m_edit_t_range.SetWindowTextW(strValue);

	strValue.Format(_T("%.2f"),pDlg->dAlignWidth);
	m_edit_align_width.SetWindowTextW(strValue);

	strValue.Format(_T("%.2f"), pDlg->dAlignHeight);
	m_edit_align_height.SetWindowTextW(strValue);

	strValue.Format(_T("%.3f"), pDlg->dAlignOffsetX);
	m_edit_xoffset.SetWindowTextW(strValue);

	strValue.Format(_T("%.3f"), pDlg->dAlignOffsetY);
	m_edit_yoffset.SetWindowTextW(strValue);

	strValue.Format(_T("%.6f"), pDlg->dAlignOffsetT);
	m_edit_toffset.SetWindowTextW(strValue);
}


void SettingAlign::DisplayAlign(bool nCase)
{
	GetDlgItem(IDC_GRP_EDGE)->ShowWindow(nCase);
	GetDlgItem(IDC_STATIC_BINARY)->ShowWindow(nCase);
	GetDlgItem(IDC_EDIT_BINARY_LOW)->ShowWindow(nCase);
	GetDlgItem(IDC_STATIC_START)->ShowWindow(nCase);
	GetDlgItem(IDC_EDIT_EDGE_ROI_START_X)->ShowWindow(nCase);
	GetDlgItem(IDC_EDIT_EDGE_ROI_START_Y)->ShowWindow(nCase);
	GetDlgItem(IDC_STATIC_END)->ShowWindow(nCase);
	GetDlgItem(IDC_EDIT_EDGE_ROI_END_X)->ShowWindow(nCase);
	GetDlgItem(IDC_EDIT_EDGE_ROI_END_Y)->ShowWindow(nCase);
}


void SettingAlign::DisplaySetting(bool nCase)
{
	GetDlgItem(IDC_GRP_ALIGNCAM_POS)->ShowWindow(nCase);

	GetDlgItem(IDC_STATIC_ALIGN1)->ShowWindow(nCase);
	GetDlgItem(IDC_STATIC_ALIGN2)->ShowWindow(nCase);
	GetDlgItem(IDC_STATIC_ALIGN3)->ShowWindow(nCase);
	GetDlgItem(IDC_STATIC_ALIGN4)->ShowWindow(nCase);

	GetDlgItem(IDC_STATIC_JUDGE_RANGE_X)->ShowWindow(nCase);
	GetDlgItem(IDC_STATIC_JUDGE_RANGE_Y)->ShowWindow(nCase);
	GetDlgItem(IDC_STATIC_JUDGE_RANGE_T)->ShowWindow(nCase);
	GetDlgItem(IDC_EDIT_JUDGE_RANGE_X)->ShowWindow(nCase);
	GetDlgItem(IDC_EDIT_JUDGE_RANGE_Y)->ShowWindow(nCase);
	GetDlgItem(IDC_EDIT_JUDGE_RANGE_T)->ShowWindow(nCase);
}


BOOL SettingAlign::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void SettingAlign::OnBnClickedBtnModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	EditEnable(true);

	rectRoi = { stAlign.ROIStart[SelectCam].x / 4, stAlign.ROIStart[SelectCam].y / 4,
		stAlign.ROIEnd[SelectCam].x / 4, stAlign.ROIEnd[SelectCam].y / 4 };

	mRoiTracker.m_rect = rectRoi;

	ChkModify = true;
}


void SettingAlign::OnBnClickedBtnApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CString strValue;

	m_edit_binary_low.GetWindowTextW(strValue);
	stAlign.nBinaryLow[SelectCam] = _ttoi(strValue);

	m_edit_open.GetWindowTextW(strValue);
	stAlign.nOpen[SelectCam] = _ttoi(strValue);

	m_edit_close.GetWindowTextW(strValue);
	stAlign.nClose[SelectCam] = _ttoi(strValue);

	m_edit_edge_roi_start_x.GetWindowTextW(strValue);
	stAlign.ROIStart[SelectCam].x = _ttoi(strValue);

	m_edit_edge_roi_start_y.GetWindowTextW(strValue);
	stAlign.ROIStart[SelectCam].y = _ttoi(strValue);

	m_edit_edge_roi_end_x.GetWindowTextW(strValue);
	stAlign.ROIEnd[SelectCam].x = _ttoi(strValue);

	m_edit_edge_roi_end_y.GetWindowTextW(strValue);
	stAlign.ROIEnd[SelectCam].y = _ttoi(strValue);

	m_edit_level_range.GetWindowTextW(strValue);
	pDlg->dRangeHLevel = _wtof(strValue);

	m_edit_mistake_range.GetWindowTextW(strValue);
	pDlg->dRangeMistake = _wtof(strValue);

	m_edit_x_range.GetWindowTextW(strValue);
	pDlg->dRangeX = _wtof(strValue);

	m_edit_y_range.GetWindowTextW(strValue);
	pDlg->dRangeY = _wtof(strValue);

	m_edit_t_range.GetWindowTextW(strValue);
	pDlg->dRangeT = _wtof(strValue);

	m_edit_align_width.GetWindowTextW(strValue);
	pDlg->dAlignWidth = _wtof(strValue);

	m_edit_align_height.GetWindowTextW(strValue);
	pDlg->dAlignHeight = _wtof(strValue);

	m_edit_xoffset.GetWindowTextW(strValue);
	pDlg->dAlignOffsetX = _wtof(strValue);

	m_edit_yoffset.GetWindowTextW(strValue);
	pDlg->dAlignOffsetY = _wtof(strValue);

	m_edit_toffset.GetWindowTextW(strValue);
	pDlg->dAlignOffsetT = _wtof(strValue);

	pDlg->nSelecteAlignMethod = pDlg->nAlignMethod;

	pDlg->SaveRecipe(1);

	EditEnable(FALSE);

	rectRoi = { 0,0,0,0 };
	mRoiTracker.m_rect = rectRoi;

	if (pDlg->bChkMark == 1)
	{
		pDlg->dlgVisionAlign->DisplayMark(true);
		pDlg->dlgVisionAlign->DisplayEdge(false);
	}

	else if (pDlg->bChkEdge == 1)
	{
		pDlg->dlgVisionAlign->DisplayMark(false);
		pDlg->dlgVisionAlign->DisplayEdge(true);
	}

	m_edit_recipe_name.GetWindowTextW(strValue);
	pDlg->dlgVisionSetting->dlgSettingCamera->m_edit_recipe_name.SetWindowTextW(strValue);
	pDlg->dlgVisionSetting->dlgSettingAlignMark->m_edit_recipe_name.SetWindowTextW(strValue);
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

	//m_edit_xoffset.GetWindowTextW(strValue);
	//AfxGetApp()->WriteProfileStringW(_T("ALIGN"), _T("XOFFSET"), strValue);
	//pDlg->dXOffset = _wtof(strValue);

	//m_edit_yoffset.GetWindowTextW(strValue);
	//AfxGetApp()->WriteProfileStringW(_T("ALIGN"), _T("YOFFSET"), strValue);
	//pDlg->dYOffset = _wtof(strValue);

	//m_edit_toffset.GetWindowTextW(strValue);
	//AfxGetApp()->WriteProfileStringW(_T("ALIGN"), _T("TOFFSET"), strValue);
	//pDlg->dTOffset = _wtof(strValue);

}


void SettingAlign::OnBnClickedBtnCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	DisplayParam(SelectCam);

	EditEnable(FALSE);

	rectRoi = { 0,0,0,0 };
	mRoiTracker.m_rect = rectRoi;

	pDlg->dXOffset = _ttoi(AfxGetApp()->GetProfileStringW(_T("ALIGN"), _T("XOFFSET")));
	pDlg->dYOffset = _ttoi(AfxGetApp()->GetProfileStringW(_T("ALIGN"), _T("YOFFSET")));

	//CString strRegValue;

	//strRegValue.Format(_T("%.1f"), pDlg->dXOffset);
	//m_edit_xoffset.SetWindowTextW(strRegValue);

	//strRegValue.Format(_T("%.1f"), pDlg->dYOffset);
	//m_edit_yoffset.SetWindowTextW(strRegValue);
}


void SettingAlign::EditEnable(bool nCase)
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

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

	m_btn_edge.EnableWindow(nCase);
	m_btn_mark.EnableWindow(nCase);
	m_btn_align_method.EnableWindow(nCase);
	
	if (pDlg->bChkMark == true)
		m_edit_align_width.EnableWindow(true);

	else if (pDlg->bChkEdge == true)
		m_edit_align_width.EnableWindow(false);
	
	m_btn_preprocess_show.EnableWindow(nCase);
	m_btn_preprocess_apply.EnableWindow(nCase);

	m_edit_x_range.EnableWindow(nCase);
	m_edit_y_range.EnableWindow(nCase);
	m_edit_t_range.EnableWindow(nCase);

	m_edit_level_range.EnableWindow(nCase);
	m_edit_mistake_range.EnableWindow(nCase);

	//m_edit_align_width.EnableWindow(nCase);
	m_edit_align_height.EnableWindow(nCase);

	m_edit_edge_roi_start_x.EnableWindow(nCase);
	m_edit_edge_roi_start_y.EnableWindow(nCase);
	m_edit_edge_roi_end_x.EnableWindow(nCase);
	m_edit_edge_roi_end_y.EnableWindow(nCase);

	m_edit_binary_low.EnableWindow(nCase);
	m_edit_open.EnableWindow(nCase);
	m_edit_close.EnableWindow(nCase);

	m_edit_xoffset.EnableWindow(nCase);
	m_edit_yoffset.EnableWindow(nCase);
	m_edit_toffset.EnableWindow(nCase);

	GetDlgItem(IDC_EDIT_RECIPE_NAME)->EnableWindow(nCase);
	GetDlgItem(IDC_BTN_APPLY)->EnableWindow(nCase);
	GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(nCase);

	if(nCase == false)
		m_edit_align_width.EnableWindow(false);

}


void SettingAlign::OnEnChangeEditEdgeRoiStartX()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CString strVal;
	int nVal;

	m_edit_edge_roi_start_x.GetWindowTextW(strVal);
	nVal = _ttoi(strVal);

	if (nVal < 0)
	{
		nVal = 0;
		m_edit_edge_roi_start_x.SetWindowTextW(_T("0"));
	}

	else if (nVal > CamWidth)
	{
		nVal = 2448;
		m_edit_edge_roi_start_x.SetWindowTextW(_T("2448"));
	}
}


void SettingAlign::OnEnChangeEditEdgeRoiStartY()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CString strVal;
	int nVal;

	m_edit_edge_roi_start_y.GetWindowTextW(strVal);
	nVal = _ttoi(strVal);

	if (nVal < 0)
	{
		nVal = 0;
		m_edit_edge_roi_start_y.SetWindowTextW(_T("0"));
	}

	else if (nVal > CamHeight)
	{
		nVal = 2048;
		m_edit_edge_roi_start_y.SetWindowTextW(_T("2048"));
	}
}


void SettingAlign::OnEnChangeEditEdgeRoiEndX()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CString strVal;
	int nVal;

	m_edit_edge_roi_end_x.GetWindowTextW(strVal);
	nVal = _ttoi(strVal);

	if (nVal < 0)
	{
		nVal = 0;
		m_edit_edge_roi_end_x.SetWindowTextW(_T("0"));
	}

	else if (nVal > CamWidth)
	{
		nVal = 2448;
		m_edit_edge_roi_end_x.SetWindowTextW(_T("2448"));
	}
}


void SettingAlign::OnEnChangeEditEdgeRoiEndY()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CString strVal;
	int nVal;

	m_edit_edge_roi_end_y.GetWindowTextW(strVal);
	nVal = _ttoi(strVal);

	if (nVal < 0)
	{
		nVal = 0;
		m_edit_edge_roi_end_y.SetWindowTextW(_T("0"));
	}

	else if (nVal > CamHeight)
	{
		nVal = 2048;
		m_edit_edge_roi_end_y.SetWindowTextW(_T("2048"));
	}
}

void SettingAlign::OnCbnSelchangeCmbSelectcam()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	int nCase;

	nCase = m_cmb_selectcam.GetCurSel();
	SelectCam = nCase;
	DisplayParam(nCase);

	if (ChkModify == true)
	{
		rectRoi = { stAlign.ROIStart[SelectCam].x / 4, stAlign.ROIStart[SelectCam].y / 4,
		stAlign.ROIEnd[SelectCam].x / 4, stAlign.ROIEnd[SelectCam].y / 4 };

		mRoiTracker.m_rect = rectRoi;
	}
}


void SettingAlign::OnBnClickedBtnEdge()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	m_btn_edge.SetFaceColor(ColorGreen);
	m_btn_mark.SetFaceColor(ColorBasic);
	m_edit_align_width.EnableWindow(false);

	pDlg->bChkMark = false;
	pDlg->bChkEdge = true;

	m_pic_mark_pos.SetBitmap(pDlg->m_bmp_edgepos);
}


void SettingAlign::OnBnClickedBtnMark()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	m_btn_edge.SetFaceColor(ColorBasic);
	m_btn_mark.SetFaceColor(ColorGreen);
	m_edit_align_width.EnableWindow(true);

	pDlg->bChkMark = true;
	pDlg->bChkEdge = false;

	m_pic_mark_pos.SetBitmap(pDlg->m_bmp_markpos);
}


void SettingAlign::OnBnClickedBtnRecipeLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();
	pDlg->RecipeSelect();
}


void SettingAlign::OnBnClickedBtnAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	pDlg->RecipeAdd();
	EditEnable(FALSE);

}

void SettingAlign::OnBnClickedBtnPreprocessApply()
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

	pDlg->ImageSave(SelectCam, false);
	
	if (SelectCam == 0)
		FileName = pDlg->strExeFilePath + _T("Data\\_OriginImage_1.bmp");

	else if (SelectCam == 1)
		FileName = pDlg->strExeFilePath + _T("Data\\_OriginImage_2.bmp");

	else if (SelectCam == 2)
		FileName = pDlg->strExeFilePath + _T("Data\\_OriginImage_3.bmp");

	else if (SelectCam == 3)
		FileName = pDlg->strExeFilePath + _T("Data\\_OriginImage_4.bmp");

	CT2CA ConvertString(FileName);
	std::string	Image_path(ConvertString);

	// 원본 이미지 로딩
	LoadImg = imread(Image_path);

	ProcessImg = LoadImg.clone();

	m_edit_open.GetWindowTextW(strVal);
	nVal = _ttoi(strVal);
	Mat ElementOpen(nVal, nVal, CV_8U, cv::Scalar(1));	// OPEN 파라미터

	m_edit_close.GetWindowTextW(strVal);
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
	
	if (SelectCam == 0)
		SaveProcImg = pDlg->strExeFilePath + _T("Data\\_ProcImage_1.bmp");

	else if (SelectCam == 1)
		SaveProcImg = pDlg->strExeFilePath + _T("Data\\_ProcImage_2.bmp");

	else if (SelectCam == 2)
		SaveProcImg = pDlg->strExeFilePath + _T("Data\\_ProcImage_3.bmp");

	else if (SelectCam == 3)
		SaveProcImg = pDlg->strExeFilePath + _T("Data\\_ProcImage_4.bmp");

	CT2CA ConvertStringImg(SaveProcImg);
	std::string	save_Img_path(ConvertStringImg);

	imwrite(save_Img_path, ProcessImg);
}


void SettingAlign::OnBnClickedBtnPreprocessShow()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	pDlg->DisplayPreprocessImg(1, true);
}


void SettingAlign::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	//if (point.x > 10 && point.x < 180)
	//{
	//	if (point.y > 10 && point.y < 30)
	//	{
	//		CRect rcManualAlign;
	//		GetWindowRect(rcManualAlign);

	//		rcManualAlign.top += 30;
	//		rcManualAlign.left += 100;
	//		rcManualAlign.right = rcManualAlign.left + 200;
	//		rcManualAlign.bottom = rcManualAlign.top + 250;

	//		dlgSettingHide.rcDialog = rcManualAlign;

	//		if (dlgSettingHide.DoModal() == IDOK)   // 다이얼로그가 종료될 때 반환되는 값을 검사, OK 버튼으로 종료되었을 경우 IDOK를 반환
	//		{
	//			CString strRegValue;

	//			strRegValue.Format(_T("%.3f"), dlgSettingHide.dModifyX);
	//			AfxGetApp()->WriteProfileStringW(_T("ALIGN"), _T("MODIFYX"), strRegValue);
	//			pDlg->dManualOffsetX = dlgSettingHide.dModifyX;

	//			strRegValue.Format(_T("%.3f"), dlgSettingHide.dModifyY);
	//			AfxGetApp()->WriteProfileStringW(_T("ALIGN"), _T("MODIFYY"), strRegValue);
	//			pDlg->dManualOffsetY = dlgSettingHide.dModifyY;

	//			strRegValue.Format(_T("%.3f"), dlgSettingHide.dModifyT);
	//			AfxGetApp()->WriteProfileStringW(_T("ALIGN"), _T("MODIFYT"), strRegValue);
	//			pDlg->dManualOffsetT = dlgSettingHide.dModifyT;
	//		}
	//		
	//		else
	//		{
	//		}
	//	}
	//}
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void SettingAlign::OnBnClickedBtnAlignMethod()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();


	CRect rcManualAlign;
	GetWindowRect(rcManualAlign);

	
	rcManualAlign.left += (WindowWidth - 350) / 2;
	rcManualAlign.right = rcManualAlign.left + 350;
	rcManualAlign.bottom = rcManualAlign.top + 290;

	dlgSettingAlign.rcDialog = rcManualAlign;

	if (dlgSettingAlign.DoModal() == IDOK)   // 다이얼로그가 종료될 때 반환되는 값을 검사, OK 버튼으로 종료되었을 경우 IDOK를 반환
	{
		pDlg->nAlignMethod = dlgSettingAlign.nSelectedMethod;
	}

	else
	{
	}
}



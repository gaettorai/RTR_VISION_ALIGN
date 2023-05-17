// RVisionFC.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "RVisionFC.h"
#include "afxdialogex.h"

#include "RVisionDlg.h"
// RVisionFC 대화 상자

IMPLEMENT_DYNAMIC(RVisionFC, CDialogEx)

RVisionFC::RVisionFC(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RVISION_FC, pParent)
{

}

RVisionFC::~RVisionFC()
{
}

void RVisionFC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FC, m_list_fc);
	DDX_Control(pDX, IDC_EDIT_GAIN, m_edit_gain);
	DDX_Control(pDX, IDC_EDIT_NEWCAL, m_edit_newcal);
	DDX_Control(pDX, IDC_EDIT_POINT_X, m_edit_point_x);
	DDX_Control(pDX, IDC_EDIT_POINT_Y, m_edit_point_y);
	DDX_Control(pDX, IDC_EDIT_LENGTH_X, m_edit_length_x);
	DDX_Control(pDX, IDC_EDIT_LENGTH_Y, m_edit_length_y);
	DDX_Control(pDX, IDC_EDIT_OLDCTFILE, m_edit_oldctfile);
	DDX_Control(pDX, IDC_EDIT_NEWCTFILE, m_edit_newctfile);
}


BEGIN_MESSAGE_MAP(RVisionFC, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_OLDCTFILE, &RVisionFC::OnBnClickedBtnOldctfile)
	ON_BN_CLICKED(IDC_BTN_NEWCTFILE, &RVisionFC::OnBnClickedBtnNewctfile)
	ON_BN_CLICKED(IDC_BTN_MEASUREMENT, &RVisionFC::OnBnClickedBtnMeasurement)
END_MESSAGE_MAP()


// RVisionFC 메시지 처리기


int RVisionFC::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH RVisionFC::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL RVisionFC::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL RVisionFC::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	dlgDrawFC = new DrawFC;
	dlgDrawFC->Create(IDD_DRAW_FC, this);
	dlgDrawFC->MoveWindow(0, 0, WindowWidth, CamHeight / 4);
	dlgDrawFC->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_BTN_MEASUREMENT)->MoveWindow(10, CamHeight / 4 + 20, 60, 30);

	GetDlgItem(IDC_GRP_RESULT)->MoveWindow(10, CamHeight / 4 + 70, 170, 120);
	GetDlgItem(IDC_STATIC_MATCHRATE)->MoveWindow(20, CamHeight / 4 + 90, 60, 30);
	GetDlgItem(IDC_STATIC_ERROR_X)->MoveWindow(20, CamHeight / 4 + 120, 60, 30);
	GetDlgItem(IDC_STATIC_ERROR_Y)->MoveWindow(20, CamHeight / 4 + 150, 60, 30);
	GetDlgItem(IDC_STATIC_MATCHRATE_VALUE)->MoveWindow(90, CamHeight / 4 + 90, 60, 30);
	GetDlgItem(IDC_STATIC_ERROR_X_VALUE)->MoveWindow(90, CamHeight / 4 + 120, 60, 30);
	GetDlgItem(IDC_STATIC_ERROR_Y_VALUE)->MoveWindow(90, CamHeight / 4 + 150, 60, 30);

	GetDlgItem(IDC_GRP_PARAM)->MoveWindow(190, CamHeight / 4 + 10, 400, 180);
	GetDlgItem(IDC_STATIC_GAIN)->MoveWindow(200, CamHeight / 4 + 30, 60, 30);
	GetDlgItem(IDC_EDIT_GAIN)->MoveWindow(270, CamHeight / 4 + 35, 80, 20);
	GetDlgItem(IDC_STATIC_NEWCAL)->MoveWindow(200, CamHeight / 4 + 70, 60, 30);
	GetDlgItem(IDC_EDIT_NEWCAL)->MoveWindow(270, CamHeight / 4 + 75, 80, 20);
	GetDlgItem(IDC_STATIC_POINT)->MoveWindow(380, CamHeight / 4 + 30, 60, 30);
	GetDlgItem(IDC_EDIT_POINT_X)->MoveWindow(450, CamHeight / 4 + 35, 50, 20);
	GetDlgItem(IDC_STATIC_POINT_X)->MoveWindow(500, CamHeight / 4 + 35, 30, 20);
	GetDlgItem(IDC_EDIT_POINT_Y)->MoveWindow(530, CamHeight / 4 + 35, 50, 20);
	GetDlgItem(IDC_STATIC_LENGTH)->MoveWindow(380, CamHeight / 4 + 70, 60, 30);
	GetDlgItem(IDC_EDIT_LENGTH_X)->MoveWindow(450, CamHeight / 4 + 75, 50, 20);
	GetDlgItem(IDC_STATIC_LENGTH_X)->MoveWindow(500, CamHeight / 4 + 75, 30, 20);
	GetDlgItem(IDC_EDIT_LENGTH_Y)->MoveWindow(530, CamHeight / 4 + 75, 50, 20);
	GetDlgItem(IDC_STATIC_OLDCTFILE)->MoveWindow(200, CamHeight / 4 + 110, 60, 30);
	GetDlgItem(IDC_EDIT_OLDCTFILE)->MoveWindow(270, CamHeight / 4 + 115, 280, 20);
	GetDlgItem(IDC_BTN_OLDCTFILE)->MoveWindow(560, CamHeight / 4 + 115, 20, 20);
	GetDlgItem(IDC_STATIC_NEWCTFILE)->MoveWindow(200, CamHeight / 4 + 150, 60, 30);
	GetDlgItem(IDC_EDIT_NEWCTFILE)->MoveWindow(270, CamHeight / 4 + 155, 280, 20);
	GetDlgItem(IDC_BTN_NEWCTFILE)->MoveWindow(560, CamHeight / 4 + 155, 20, 20);

	GetDlgItem(IDC_LIST_FC)->MoveWindow(10, CamHeight / 4 + 200, CamWidth / 4 - 25, 110);

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

	GetDlgItem(IDC_BTN_MEASUREMENT)->SetFont(btnFont);


	HFONT staticFont;
	staticFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_GRP_RESULT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MATCHRATE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ERROR_X)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ERROR_Y)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MATCHRATE_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ERROR_X_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ERROR_Y_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_GRP_PARAM)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_GAIN)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_NEWCAL)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_POINT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LENGTH)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_OLDCTFILE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_NEWCTFILE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);

	m_list_fc.InsertColumn(1, _T("Day"), LVCFMT_CENTER, 125);
	m_list_fc.InsertColumn(2, _T("Where"), LVCFMT_CENTER, 140);
	m_list_fc.InsertColumn(3, _T("Message"), LVCFMT_CENTER, 250);
	m_list_fc.InsertColumn(4, _T("Remark"), LVCFMT_CENTER, 72);

	DisplayParam();

	nFCLogCount = 0;
	bChkNewctfile = false;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL RVisionFC::PreTranslateMessage(MSG* pMsg)
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


void RVisionFC::DisplayParam()
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CString strValue;

	strValue.Format(_T("%.3f"), pDlg->dGain);
	m_edit_gain.SetWindowTextW(strValue);

	strValue.Format(_T("%.3f"), pDlg->dNewcal);
	m_edit_newcal.SetWindowTextW(strValue);

	strValue.Format(_T("%d"), pDlg->nPatternPoint);
	m_edit_point_x.SetWindowTextW(strValue);
	m_edit_point_y.SetWindowTextW(strValue);

	strValue.Format(_T("%.3f"), pDlg->dPatternLength * pDlg->nPatternPoint);

	m_edit_length_x.SetWindowTextW(strValue);
	m_edit_length_y.SetWindowTextW(strValue);

	strValue = pDlg->strOldctFile;
	m_edit_oldctfile.SetWindowTextW(strValue);

	strValue = pDlg->strNewctFile;
	m_edit_newctfile.SetWindowTextW(strValue);

}

void RVisionFC::OnBnClickedBtnOldctfile()
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("All files(*.*)|*.*|"); // 모든 파일 표시
	// _T("Excel 파일 (*.xls, *.xlsx) |*.xls; *.xlsx|"); 와 같이 확장자를 제한하여 표시할 수 있음
	CFileDialog dlg(TRUE, _T("*.ct5"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	if (dlg.DoModal() == IDOK)
	{
		CString strPathName = dlg.GetPathName();
		// 파일 경로를 가져와 사용할 경우, Edit Control에 값 저장
		SetDlgItemText(IDC_EDIT_OLDCTFILE, strPathName);
		pDlg->strOldctFile = strPathName;

		int length = strPathName.GetLength();
		//int nInsert = strPathName.Find(_T(".ct5"));

		//strPathName.Insert(nInsert, _T("(2)"));

		strPathName.Insert(length - 4, _T("(2)"));

		SetDlgItemText(IDC_EDIT_NEWCTFILE, strPathName);
		pDlg->strNewctFile = strPathName;
	}
}


void RVisionFC::OnBnClickedBtnNewctfile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	if (bChkNewctfile == false)
	{
		m_edit_newctfile.EnableWindow(true);
		bChkNewctfile = true;
	}

	else if (bChkNewctfile == true)
	{
		m_edit_newctfile.GetWindowTextW(pDlg->strNewctFile);
		m_edit_newctfile.EnableWindow(false);
		bChkNewctfile = false;
	}

}


void RVisionFC::OnBnClickedBtnMeasurement()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	pDlg->ExcutionFC(1);
}

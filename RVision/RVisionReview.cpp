// RVisionReview.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "RVisionReview.h"
#include "afxdialogex.h"

#include "RVisionDlg.h"
// RVisionReview 대화 상자

IMPLEMENT_DYNAMIC(RVisionReview, CDialogEx)

extern 	ClickPoint stMeasure;

RVisionReview::RVisionReview(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RVISION_REVIEW, pParent)
{

}

RVisionReview::~RVisionReview()
{
}

void RVisionReview::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_MODE, m_btn_mode);
	DDX_Control(pDX, IDC_BTN_LINE, m_btn_line);
	DDX_Control(pDX, IDC_BTN_RECTANGLE, m_btn_rectangle);
	DDX_Control(pDX, IDC_BTN_ANGLE, m_btn_angle);
	DDX_Control(pDX, IDC_BTN_CLEAR, m_btn_clear);
	DDX_Control(pDX, IDC_BTN_ZOOMIN, m_btn_zoomin);
	DDX_Control(pDX, IDC_BTN_ZOOMOUT, m_btn_zoomout);
	DDX_Control(pDX, IDC_LIST_MEASUREMENT, m_list_measurement);
	DDX_Control(pDX, IDC_BTN_CLEARALL, m_btn_clearall);
	DDX_Control(pDX, IDC_BTN_CIRCLE, m_btn_circle);
	DDX_Control(pDX, IDC_CHK_SCALE, m_chk_scale);
	DDX_Control(pDX, IDC_BTN_CENTER_DIST, m_btn_center_dist);
	DDX_Control(pDX, IDC_CHK_ALL, m_chk_all);
}


BEGIN_MESSAGE_MAP(RVisionReview, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_MODE, &RVisionReview::OnBnClickedBtnMode)
	ON_BN_CLICKED(IDC_BTN_LINE, &RVisionReview::OnBnClickedBtnLine)
	ON_BN_CLICKED(IDC_BTN_RECTANGLE, &RVisionReview::OnBnClickedBtnRectangle)
	ON_BN_CLICKED(IDC_BTN_ANGLE, &RVisionReview::OnBnClickedBtnAngle)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &RVisionReview::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_ZOOMIN, &RVisionReview::OnBnClickedBtnZoomin)
	ON_BN_CLICKED(IDC_BTN_ZOOMOUT, &RVisionReview::OnBnClickedBtnZoomout)
	ON_BN_CLICKED(IDC_BTN_CAPTURE, &RVisionReview::OnBnClickedBtnCapture)
	ON_BN_CLICKED(IDC_BTN_CLEARALL, &RVisionReview::OnBnClickedBtnClearall)
	ON_BN_CLICKED(IDC_BTN_CIRCLE, &RVisionReview::OnBnClickedBtnCircle)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_CENTER_DIST, &RVisionReview::OnBnClickedBtnCenterDist)
	ON_BN_CLICKED(IDC_CHK_ALL, &RVisionReview::OnBnClickedChkAll)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_MEASUREMENT, &RVisionReview::OnColumnclickListMeasurement)
END_MESSAGE_MAP()


// RVisionReview 메시지 처리기


int RVisionReview::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH RVisionReview::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL RVisionReview::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL RVisionReview::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	dlgDrawReview = new DrawReview;
	dlgDrawReview->Create(IDD_DRAW_REVIEW, this);
	dlgDrawReview->MoveWindow(0, 0, WindowWidth, CamHeight / 4);
	dlgDrawReview->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_LIST_MEASUREMENT)->MoveWindow(10, CamHeight / 4 + 10, 325, 240);
	GetDlgItem(IDC_BTN_MODE)->MoveWindow(10, CamHeight / 4 + 10 + 240 + 20, 40, 40);
	GetDlgItem(IDC_BTN_LINE)->MoveWindow(70, CamHeight / 4 + 10 + 240 + 20, 40, 40);
	GetDlgItem(IDC_BTN_RECTANGLE)->MoveWindow(110, CamHeight / 4 + 10 + 240 + 20, 40, 40);
	GetDlgItem(IDC_BTN_ANGLE)->MoveWindow(150, CamHeight / 4 + 10 + 240 + 20, 40, 40);
	GetDlgItem(IDC_BTN_CIRCLE)->MoveWindow(190, CamHeight / 4 + 10 + 240 + 20, 40, 40);
	GetDlgItem(IDC_BTN_CENTER_DIST)->MoveWindow(230, CamHeight / 4 + 10 + 240 + 20, 40, 40);

	GetDlgItem(IDC_BTN_CLEAR)->MoveWindow(295, CamHeight / 4 + 10 + 240 + 20, 40, 40);
	GetDlgItem(IDC_BTN_CLEARALL)->MoveWindow(295, CamHeight / 4 + 10 + 240 + 20, 40, 40);

	GetDlgItem(IDC_CHK_SCALE)->MoveWindow(WindowWidth - (CamWidth) / 16 + 50, 732, 100, 30);
	GetDlgItem(IDC_PIC_NAVIGATOR)->MoveWindow(WindowWidth - (CamWidth / 16) - 10, CamHeight / 4 + 10, CamWidth / 16, CamHeight / 16);
	GetDlgItem(IDC_STATIC_MAGNI)->MoveWindow(WindowWidth - (CamWidth / 16) - 10, CamHeight / 4 + 10 + CamHeight / 16 + 10, 70, 30);
	GetDlgItem(IDC_BTN_ZOOMIN)->MoveWindow(WindowWidth - 75, CamHeight / 4 + 10 + CamHeight / 16 + 10, 30, 30);
	GetDlgItem(IDC_BTN_ZOOMOUT)->MoveWindow(WindowWidth - 40, CamHeight / 4 + 10 + CamHeight / 16 + 10, 30, 30);

	GetDlgItem(IDC_BTN_CAPTURE)->MoveWindow(WindowWidth - 100, WindowHeight - 70, 90, 30);

	HFONT staticFont;
	staticFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_STATIC_MAGNI)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_CHK_SCALE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);

	m_bmp_graphic_on.LoadBitmapW(IDB_BITMAP_GRAPHIC_ON);
	m_bmp_graphic_off.LoadBitmapW(IDB_BITMAP_GRAPHIC_OFF);
	m_bmp_line_on.LoadBitmapW(IDB_BITMAP_LINE_ON);
	m_bmp_line_off.LoadBitmapW(IDB_BITMAP_LINE_OFF);
	m_bmp_rectangle_on.LoadBitmapW(IDB_BITMAP_RECTANGLE_ON);
	m_bmp_rectangle_off.LoadBitmapW(IDB_BITMAP_RECTANGLE_OFF);
	m_bmp_angle_on.LoadBitmapW(IDB_BITMAP_ANGLE_ON);
	m_bmp_angle_off.LoadBitmapW(IDB_BITMAP_ANGLE_OFF);
	m_bmp_centerdist_on.LoadBitmapW(IDB_BITMAP_CENTERDIST_ON);
	m_bmp_centerdist_off.LoadBitmapW(IDB_BITMAP_CENTERDIST_OFF);
	m_bmp_circle_on.LoadBitmapW(IDB_BITMAP_CIRCLE_ON);
	m_bmp_circle_off.LoadBitmapW(IDB_BITMAP_CIRCLE_OFF);
	m_bmp_clear.LoadBitmapW(IDB_BITMAP_CLEAR);
	m_bmp_zoomin.LoadBitmapW(IDB_BITMAP_ZOOMIN);
	m_bmp_zoomout.LoadBitmapW(IDB_BITMAP_ZOOMOUT);

	m_btn_mode.SetBitmap(m_bmp_graphic_off);
	m_btn_line.SetBitmap(m_bmp_line_off);
	m_btn_rectangle.SetBitmap(m_bmp_rectangle_off);
	m_btn_angle.SetBitmap(m_bmp_angle_off);
	m_btn_circle.SetBitmap(m_bmp_circle_off);
	m_btn_center_dist.SetBitmap(m_bmp_centerdist_off);

	m_btn_line.EnableWindow(FALSE);
	m_btn_rectangle.EnableWindow(FALSE);
	m_btn_angle.EnableWindow(FALSE);
	m_btn_circle.EnableWindow(FALSE);
	m_btn_center_dist.EnableWindow(FALSE);

	m_btn_clear.SetBitmap(m_bmp_clear);
	m_btn_clearall.SetBitmap(m_bmp_clear);
	m_btn_zoomin.SetBitmap(m_bmp_zoomin);
	m_btn_zoomout.SetBitmap(m_bmp_zoomout);

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

	GetDlgItem(IDC_BTN_CAPTURE)->SetFont(btnFont);

	CFont* listFont;
	listFont = new CFont;

	//폰트 생성
	listFont->CreateFont(
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

	GetDlgItem(IDC_LIST_MEASUREMENT)->SetFont(listFont);

	m_list_measurement.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES | LVS_EX_TRACKSELECT);

	m_list_measurement.InsertColumn(1, _T("No."), LVCFMT_CENTER, 50);
	m_list_measurement.InsertColumn(2, _T("Type"), LVCFMT_CENTER, 75);
	m_list_measurement.InsertColumn(3, _T("Value_1"), LVCFMT_CENTER, 100);
	m_list_measurement.InsertColumn(4, _T("Value_2"), LVCFMT_CENTER, 100);

	for (int i = 0; i < 10; i++)
	{
		CString str;
		str.Format(_T("%d"), i + 1);
		m_list_measurement.InsertItem(i, str);
	}

	clickCount = 0;

	x_point = 516;
	y_point = 579;

	m_nHdelta = 0;
	m_nVdelta = 0;

	m_chk_scale.SetCheck(1);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL RVisionReview::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	if (pMsg->message == WM_MOUSEMOVE)
	{
		CRect rc[8];
		this->GetDlgItem(IDC_BTN_MODE)->GetWindowRect(&rc[0]);
		this->GetDlgItem(IDC_BTN_LINE)->GetWindowRect(&rc[1]);
		this->GetDlgItem(IDC_BTN_RECTANGLE)->GetWindowRect(&rc[2]);
		this->GetDlgItem(IDC_BTN_ANGLE)->GetWindowRect(&rc[3]);
		this->GetDlgItem(IDC_BTN_CLEAR)->GetWindowRect(&rc[4]);
		this->GetDlgItem(IDC_BTN_CLEARALL)->GetWindowRect(&rc[5]);
		this->GetDlgItem(IDC_BTN_ZOOMIN)->GetWindowRect(&rc[6]);
		this->GetDlgItem(IDC_BTN_ZOOMOUT)->GetWindowRect(&rc[7]);

		bool checkStatus = false;
		for (int ii = 0; ii < 8; ii++)
		{
			if (PtInRect(&rc[ii], pMsg->pt)) checkStatus = true;
		}
		if (checkStatus)
		{
			HCURSOR hCursor = AfxGetApp()->LoadStandardCursor(MAKEINTRESOURCE(32649));
			SetCursor(hCursor);
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void RVisionReview::SelectGraphic(int nCase)
{
	// line
	if (nCase == 0)
	{
		m_btn_line.SetBitmap(m_bmp_line_on);
		m_btn_rectangle.SetBitmap(m_bmp_rectangle_off);
		m_btn_angle.SetBitmap(m_bmp_angle_off);
		m_btn_circle.SetBitmap(m_bmp_circle_off);
		m_btn_center_dist.SetBitmap(m_bmp_centerdist_off);
	}

	// draw
	else if (nCase == 1)
	{
		m_btn_line.SetBitmap(m_bmp_line_off);
		m_btn_rectangle.SetBitmap(m_bmp_rectangle_on);
		m_btn_angle.SetBitmap(m_bmp_angle_off);
		m_btn_circle.SetBitmap(m_bmp_circle_off);
		m_btn_center_dist.SetBitmap(m_bmp_centerdist_off);
	}

	// angle
	else if (nCase == 2)
	{
		m_btn_line.SetBitmap(m_bmp_line_off);
		m_btn_rectangle.SetBitmap(m_bmp_rectangle_off);
		m_btn_angle.SetBitmap(m_bmp_angle_on);
		m_btn_circle.SetBitmap(m_bmp_circle_off);
		m_btn_center_dist.SetBitmap(m_bmp_centerdist_off);
	}

	else if (nCase == 3)
	{
		m_btn_line.SetBitmap(m_bmp_line_off);
		m_btn_rectangle.SetBitmap(m_bmp_rectangle_off);
		m_btn_angle.SetBitmap(m_bmp_angle_off);
		m_btn_circle.SetBitmap(m_bmp_circle_on);
		m_btn_center_dist.SetBitmap(m_bmp_centerdist_off);
	}

	else if (nCase == 4)
	{
		m_btn_line.SetBitmap(m_bmp_line_off);
		m_btn_rectangle.SetBitmap(m_bmp_rectangle_off);
		m_btn_angle.SetBitmap(m_bmp_angle_off);
		m_btn_circle.SetBitmap(m_bmp_circle_off);
		m_btn_center_dist.SetBitmap(m_bmp_centerdist_on);
	}
}

void RVisionReview::OnBnClickedBtnMode()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	if (m_btn_mode.GetBitmap() == m_bmp_graphic_off)
	{
		m_btn_mode.SetBitmap(m_bmp_graphic_on);

		m_btn_line.EnableWindow(TRUE);
		m_btn_rectangle.EnableWindow(TRUE);
		m_btn_angle.EnableWindow(TRUE);
		m_btn_circle.EnableWindow(TRUE);
		m_btn_center_dist.EnableWindow(TRUE);

		pDlg->CHK_GRAPHIC = true;
	}

	else if (m_btn_mode.GetBitmap() == m_bmp_graphic_on)
	{
		m_btn_mode.SetBitmap(m_bmp_graphic_off);

		m_btn_line.EnableWindow(FALSE);
		m_btn_rectangle.EnableWindow(FALSE);
		m_btn_angle.EnableWindow(FALSE);
		m_btn_circle.EnableWindow(FALSE);
		m_btn_center_dist.EnableWindow(FALSE);

		pDlg->CHK_GRAPHIC = false;
	}

	m_btn_line.SetBitmap(m_bmp_line_off);
	m_btn_rectangle.SetBitmap(m_bmp_rectangle_off);
	m_btn_angle.SetBitmap(m_bmp_angle_off);
	m_btn_circle.SetBitmap(m_bmp_circle_off);
	m_btn_center_dist.SetBitmap(m_bmp_centerdist_off);
}


void RVisionReview::OnBnClickedBtnLine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	SelectGraphic(0);

	pDlg->MeasurementCase = 1;
}


void RVisionReview::OnBnClickedBtnRectangle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	SelectGraphic(1);

	pDlg->MeasurementCase = 2;
}


void RVisionReview::OnBnClickedBtnAngle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	SelectGraphic(2);

	pDlg->MeasurementCase = 3;
}


void RVisionReview::OnBnClickedBtnCircle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	SelectGraphic(3);

	pDlg->MeasurementCase = 4;
}




void RVisionReview::OnBnClickedBtnCenterDist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	SelectGraphic(4);

	pDlg->MeasurementCase = 5;
}


void RVisionReview::OnBnClickedBtnClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	int nLen = m_list_measurement.GetItemCount();
	int check_num[10];

	CString check_value1[10];
	CString check_value2[10];
	CString check_value3[10];

	int count = 0;

	for (int i = 0; i < 10; i++)
	{
		check_num[i] = 0;

		check_value1[i] = m_list_measurement.GetItemText(i, 1);
		check_value2[i] = m_list_measurement.GetItemText(i, 2);
		check_value3[i] = m_list_measurement.GetItemText(i, 3);
	}

	CString str;

	for (int i = 0; i < nLen; i++)
	{
		if (m_list_measurement.GetCheck(i))
		{
			str = m_list_measurement.GetItemText(i, 0);
			check_num[i] = _ttoi(str);
			check_value1[i] = _T("");
			check_value2[i] = _T("");
			check_value3[i] = _T("");
			stMeasure.ChkMeasurement[i] = 0;
		}

		else
			count++;
	}

	if (count == 10)
	{
		for (int i = 0; i < 10; i++)
		{
			CString strNum;
			strNum.Format(_T("%d"), i + 1);

			stMeasure.ChkMeasurement[i] = false;
			m_list_measurement.DeleteItem(i);
			m_list_measurement.InsertItem(i, strNum);
		}

		pDlg->MeasurementCount = 0;
	}

	else
	{
		for (int i = 0; i < 10; i++)
		{
			if (check_value1[i] == _T(""))
			{
				for (int j = 0; j < 10 - i; j++)
				{
					if (check_value1[i + j] != _T(""))
					{
						check_value1[i] = check_value1[i + j];
						check_value2[i] = check_value2[i + j];
						check_value3[i] = check_value3[i + j];
						check_value1[i + j] = _T("");
						check_value2[i + j] = _T("");
						check_value3[i + j] = _T("");
						stMeasure.CaseMeasurement[i] = stMeasure.CaseMeasurement[i + j];
						stMeasure.FirstPoint[i] = stMeasure.FirstPoint[i + j];
						stMeasure.SecondPoint[i] = stMeasure.SecondPoint[i + j];
						stMeasure.ThirdPoint[i] = stMeasure.ThirdPoint[i + j];
						stMeasure.ChkMeasurement[i] = stMeasure.ChkMeasurement[i + j];
						stMeasure.ChkMeasurement[i + j] = 0;

						break;
					}

				}

			}
		}

		m_list_measurement.DeleteAllItems();

		for (int i = 0; i < 10; i++)
		{
			CString strNum;
			strNum.Format(_T("%d"), i + 1);

			m_list_measurement.InsertItem(i, strNum);
		}

		for (int i = 0; i < 10; i++)
		{
			m_list_measurement.SetItemText(i, 1, check_value1[i]);
			m_list_measurement.SetItemText(i, 2, check_value2[i]);
			m_list_measurement.SetItemText(i, 3, check_value3[i]);

			if (check_value1[i] == _T(""))
			{
				pDlg->MeasurementCount = i;
				break;
			}
		}
	}
}


void RVisionReview::OnBnClickedBtnClearall()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	for (int i = 0; i < 10; i++)
	{
		CString strNum;
		strNum.Format(_T("%d"), i + 1);

		stMeasure.ChkMeasurement[i] = false;
		m_list_measurement.DeleteItem(i);
		m_list_measurement.InsertItem(i, strNum);
	}

	pDlg->MeasurementCount = 0;
}


void RVisionReview::OnBnClickedBtnZoomin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	if (dlgDrawReview->magni > 1)
	{
		dlgDrawReview->magni = dlgDrawReview->magni / 2;

		dlgDrawReview->scrollpos = 0;
		dlgDrawReview->VScrollPos_ = 0;
		dlgDrawReview->HScrollPos_ = 0;
		dlgDrawReview->mouse_scroll_x = 0;
		dlgDrawReview->mouse_scroll_y = 0;

		RECT rc;
		GetClientRect(&rc);
		dlgDrawReview->SendMessage(WM_SIZE, (WPARAM)SIZE_RESTORED, MAKELPARAM(rc.right - rc.left, rc.bottom - rc.top));

		dlgDrawReview->x_start = (WindowWidth - (2448 / dlgDrawReview->magni)) / 2;
		dlgDrawReview->y_start = (((WindowWidth * CamHeight / CamWidth)) - (2048 / dlgDrawReview->magni)) / 2;

		if (dlgDrawReview->x_start < 0)
			dlgDrawReview->x_start = 0;

		if (dlgDrawReview->y_start < 0)
			dlgDrawReview->y_start = 0;

		dlgDrawReview->GetDlgItem(IDC_PIC_REVIEW)->MoveWindow(dlgDrawReview->x_start, dlgDrawReview->y_start, 2448 / dlgDrawReview->magni, 2048 / dlgDrawReview->magni);

		CString strMagni;
		strMagni.Format(_T("x1/%d"), dlgDrawReview->magni);
		if (dlgDrawReview->magni == 1)
			strMagni = _T("x1");

		GetDlgItem(IDC_STATIC_MAGNI)->SetWindowTextW(strMagni);

		if (dlgDrawReview->magni == 1)
		{
			x_point = 467;
			y_point = 540;
		}

		else if (dlgDrawReview->magni == 2)
		{
			x_point = 486;
			y_point = 555;
		}

		else if (dlgDrawReview->magni == 4)
		{
			x_point = 516;
			y_point = 579;
		}
	}
}


void RVisionReview::OnBnClickedBtnZoomout()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (dlgDrawReview->magni < 4)
	{
		dlgDrawReview->magni = dlgDrawReview->magni * 2;

		dlgDrawReview->scrollpos = 0;
		dlgDrawReview->VScrollPos_ = 0;
		dlgDrawReview->HScrollPos_ = 0;
		dlgDrawReview->mouse_scroll_x = 0;
		dlgDrawReview->mouse_scroll_y = 0;

		RECT rc;
		GetClientRect(&rc);
		dlgDrawReview->SendMessage(WM_SIZE, (WPARAM)SIZE_RESTORED, MAKELPARAM(rc.right - rc.left, rc.bottom - rc.top));

		dlgDrawReview->x_start = (WindowWidth - (2448 / dlgDrawReview->magni)) / 2;
		dlgDrawReview->y_start = (((WindowWidth * CamHeight / CamWidth)) - (2048 / dlgDrawReview->magni)) / 2;

		if (dlgDrawReview->x_start < 0)
			dlgDrawReview->x_start = 0;

		if (dlgDrawReview->y_start < 0)
			dlgDrawReview->y_start = 0;

		dlgDrawReview->GetDlgItem(IDC_PIC_REVIEW)->MoveWindow(dlgDrawReview->x_start, dlgDrawReview->y_start, 2448 / dlgDrawReview->magni, 2048 / dlgDrawReview->magni);

		CString strMagni;
		strMagni.Format(_T("x1/%d"), dlgDrawReview->magni);
		GetDlgItem(IDC_STATIC_MAGNI)->SetWindowTextW(strMagni);

		if (dlgDrawReview->magni == 1)
		{
			x_point = 467;
			y_point = 540;
		}

		else if (dlgDrawReview->magni == 2)
		{
			x_point = 486;
			y_point = 555;
		}

		else if (dlgDrawReview->magni == 4)
		{
			x_point = 516;
			y_point = 579;
		}
	}
}


void RVisionReview::OnBnClickedBtnCapture()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CClientDC dc(this);
	HDC hDC = dc.m_hDC; //picture control 크기 

	RECT rc;
	GetClientRect(&rc);

	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, rc.right, rc.bottom);
	HBITMAP hBmpOld = (HBITMAP)SelectObject(hMemDC, hBitmap);

	BitBlt(hMemDC, 0, 0, rc.right, rc.bottom, hDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, hBmpOld); DeleteDC(hMemDC); //비트맵사양설정 

	BITMAPINFOHEADER bmih;
	ZeroMemory(&bmih, sizeof(BITMAPINFOHEADER));
	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biWidth = rc.right;
	bmih.biHeight = rc.bottom;
	bmih.biPlanes = 1;
	bmih.biBitCount = 24;
	bmih.biCompression = BI_RGB; // 비트맵(DIB) 데이터 추출 

	GetDIBits(hDC, hBitmap, 0, rc.bottom, NULL, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);

	LPBYTE lpBits = new BYTE[bmih.biSizeImage];
	GetDIBits(hDC, hBitmap, 0, rc.bottom, lpBits, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
	//ReleaseDC();
	DeleteObject(hBitmap); // 비트맵 파일 헤더 설정 

	BITMAPFILEHEADER bmfh;
	bmfh.bfType = 'MB';
	bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmih.biSizeImage;
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// 파일명설정 
	SYSTEMTIME time; GetLocalTime(&time);
	CString Name;
	CString path_Name;

	CString Time;

	//path_Name = dlg_ability->strPath;
	path_Name.Format(_T("D:\\VisionData\\Capture\\_%04d_%02d%02d"), time.wYear, time.wMonth, time.wDay);
	CreateDirectory(path_Name, NULL);


	//	Time.Format(_T("D:\\VisionData\\Capture\\_%4d%2d%2d_%2d%2d%2d.bmp"), time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	Time.Format(_T("\\_%02d%02d%02d.bmp"), time.wHour, time.wMinute, time.wSecond);
	Name = path_Name + Time;

	_bstr_t gg(Name);
	BSTR lpszFileName = gg.copy();

	// 비트맵 파일 생성 및 데이터 저장 
	DWORD dwWritten;
	HANDLE hFile = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, &bmfh, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	WriteFile(hFile, &bmih, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
	WriteFile(hFile, lpBits, bmih.biSizeImage, &dwWritten, NULL);
	CloseHandle(hFile);
	delete[] lpBits;
}


void RVisionReview::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// navigator 영역 클릭 시 영역 지정 
	if (point.x > 449 && point.x < 602 && point.y > 525 && point.y < 650)
	{
		clickCount = 1;

		/*if (dlgDrawReview->magni == 4)
		{
			if (point.x < 516)
				point.x = 516;

			else if (point.x > 520)
				point.x = 520;

			if (point.y < 579)
				point.y = 579;

			else if (point.y > 595)
				point.y = 595;

			m_nHdelta = point.x - x_point;

			if (dlgDrawReview->mouse_scroll_x + m_nHdelta < 0)
				m_nHdelta = -dlgDrawReview->mouse_scroll_x;

			if (dlgDrawReview->mouse_scroll_x + m_nHdelta > 19)
				m_nHdelta = 19 - dlgDrawReview->mouse_scroll_x;

			if (m_nHdelta != 0)
			{
				dlgDrawReview->SetScrollPos(SB_HORZ, point.x - 516, TRUE);
				dlgDrawReview->ScrollWindow(-(m_nHdelta), 0);
			}

			m_nVdelta = point.y - y_point;

			if (dlgDrawReview->mouse_scroll_y + m_nVdelta < 0)
				m_nVdelta = -dlgDrawReview->mouse_scroll_y;

			if (dlgDrawReview->mouse_scroll_y + m_nVdelta > 16)
				m_nVdelta = 16 - dlgDrawReview->mouse_scroll_y;

			if (m_nVdelta != 0)
			{
				dlgDrawReview->SetScrollPos(SB_VERT, point.y - 579, TRUE);
				dlgDrawReview->ScrollWindow(0, -(m_nVdelta));
			}

			dlgDrawReview->HScrollPos_ = point.x - 516;
			dlgDrawReview->mouse_scroll_x = point.x - 516;
			dlgDrawReview->mouse_scroll_y = point.y - 579;
			x_point = point.x;
			y_point = point.y;
		}*/

		if (dlgDrawReview->magni == 2)
		{
			if (point.x < 486)
				point.x = 486;

			else if (point.x > 563)
				point.x = 563;

			if (point.y < 555)
				point.y = 555;

			else if (point.y > 619)
				point.y = 619;

			m_nHdelta = point.x - x_point;

			if (dlgDrawReview->mouse_scroll_x + m_nHdelta < 0)
				m_nHdelta = -dlgDrawReview->mouse_scroll_x;

			if (dlgDrawReview->mouse_scroll_x + m_nHdelta > 632)
				m_nHdelta = 632 - dlgDrawReview->mouse_scroll_x;

			if (m_nHdelta != 0)
			{
				dlgDrawReview->SetScrollPos(SB_HORZ, (point.x - 486) * 8, TRUE);
				dlgDrawReview->ScrollWindow(-(m_nHdelta) * 8, 0);
			}

			m_nVdelta = point.y - y_point;

			if (dlgDrawReview->mouse_scroll_y + m_nVdelta < 0)
				m_nVdelta = -dlgDrawReview->mouse_scroll_y;

			if (dlgDrawReview->mouse_scroll_y + m_nVdelta > 512)
				m_nVdelta = 512 - dlgDrawReview->mouse_scroll_y;

			if (m_nVdelta != 0)
			{
				dlgDrawReview->SetScrollPos(SB_VERT, (point.y - 555) * 8, TRUE);
				dlgDrawReview->ScrollWindow(0, -(m_nVdelta) * 8);
			}

			
			dlgDrawReview->mouse_scroll_x = (point.x - 486) * 8;
			dlgDrawReview->mouse_scroll_y = (point.y - 555) * 8;
			x_point = point.x;
			y_point = point.y;
		}


		else if (dlgDrawReview->magni == 1)
		{
			if (point.x < 467)
				point.x = 467;

			else if (point.x > 582)
				point.x = 582;

			if (point.y < 540)
				point.y = 540;

			else if (point.y > 634)
				point.y = 634;

			m_nHdelta = point.x - x_point;

			if (dlgDrawReview->mouse_scroll_x + m_nHdelta < 0)
				m_nHdelta = -dlgDrawReview->mouse_scroll_x;

			if (dlgDrawReview->mouse_scroll_x + m_nHdelta > 1856)
				m_nHdelta = 1856 - dlgDrawReview->mouse_scroll_x;

			if (m_nHdelta != 0)
			{
				dlgDrawReview->SetScrollPos(SB_HORZ, (point.x - 467) * 16, TRUE);
				dlgDrawReview->ScrollWindow(-(m_nHdelta) * 16, 0);
			}

			m_nVdelta = point.y - y_point;

			if (dlgDrawReview->mouse_scroll_y + m_nVdelta < 0)
				m_nVdelta = -dlgDrawReview->mouse_scroll_y;

			if (dlgDrawReview->mouse_scroll_y + m_nVdelta > 1504)
				m_nVdelta = 1504 - dlgDrawReview->mouse_scroll_y;

			if (m_nVdelta != 0)
			{
				dlgDrawReview->SetScrollPos(SB_VERT, (point.y - 540) * 16, TRUE);
				dlgDrawReview->ScrollWindow(0, -(m_nVdelta) * 16);
			}

			dlgDrawReview->mouse_scroll_x = (point.x - 467) * 16;
			dlgDrawReview->mouse_scroll_y = (point.y - 540) * 16;
			x_point = point.x;
			y_point = point.y;
		}

		x_point = point.x;
		y_point = point.y;
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void RVisionReview::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	CDialogEx::OnMouseMove(nFlags, point);
}


void RVisionReview::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	CDialogEx::OnLButtonUp(nFlags, point);
}



void RVisionReview::OnBnClickedChkAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_chk_all.GetCheck() == 1)
	{
		for (int i = 0; i < 10; i++)
		{
			m_list_measurement.SetCheck(i, true);
		}
	}

	else if (m_chk_all.GetCheck() == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			m_list_measurement.SetCheck(i, false);
		}
	}
}


void RVisionReview::OnColumnclickListMeasurement(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int n = 0;
}

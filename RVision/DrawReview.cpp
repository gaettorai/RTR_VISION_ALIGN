// DrawReview.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "DrawReview.h"
#include "afxdialogex.h"

#include "RVisionDlg.h"

// DrawReview 대화 상자

IMPLEMENT_DYNAMIC(DrawReview, CDialogEx)

extern ClickPoint stMeasure;

const int m_nLineSize = 10;
const int m_nBasic = 10;
const int m_nRepeat = 10;


DrawReview::DrawReview(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRAW_REVIEW, pParent)
{

}

DrawReview::~DrawReview()
{
}

void DrawReview::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_REVIEW, m_pic_review);
}


BEGIN_MESSAGE_MAP(DrawReview, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// DrawReview 메시지 처리기


int DrawReview::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	magni = 4;
	return 0;
}


HBRUSH DrawReview::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL DrawReview::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}


void DrawReview::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ViewWidth_ = CamWidth / magni;
	ViewHeight_ = CamHeight / magni;

	int HScrollMax = 0;
	HPageSize_ = 0;

	if (cx < ViewWidth_)
	{
		HScrollMax = ViewWidth_ - 1;
		HPageSize_ = cx;
		HScrollPos_ = min(HScrollPos_, ViewWidth_ - HPageSize_ - 1);
	}

	SCROLLINFO si;
	si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
	si.nMin = 0;
	si.nMax = HScrollMax;
	si.nPos = HScrollPos_;
	si.nPage = HPageSize_;
	SetScrollInfo(SB_HORZ, &si, TRUE);

	int VScrollMax = 0;
	VPageSize_ = 0;

	if (cy < ViewHeight_)
	{
		VScrollMax = ViewHeight_ - 1;
		VPageSize_ = cy;
		VScrollPos_ = min(VScrollPos_, ViewHeight_ - VPageSize_ - 1);
	}

	si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
	si.nMin = 0;
	si.nMax = VScrollMax;
	si.nPos = VScrollPos_;
	si.nPage = VPageSize_;
	SetScrollInfo(SB_VERT, &si, TRUE);
}


void DrawReview::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_nHdelta = 0;

	switch (nSBCode)
	{
	case SB_LINELEFT:
		m_nHdelta = -m_nBasic;
		break;
	case SB_PAGELEFT:
		m_nHdelta = -HPageSize_;
		break;
	case SB_THUMBTRACK:
		m_nHdelta = static_cast<int>(nPos) - HScrollPos_;
		break;
	case SB_PAGERIGHT:
		m_nHdelta = HPageSize_;
		break;
	case SB_LINERIGHT:
		m_nHdelta = m_nBasic;
		break;
	default:
		return;
	}

	int scrollpos = HScrollPos_ + m_nHdelta;
	int maxpos = ViewWidth_ - HPageSize_;

	if (scrollpos < 0)
		m_nHdelta = -HScrollPos_;
	else
		if (scrollpos > maxpos)
			m_nHdelta = maxpos - HScrollPos_;

	mouse_scroll_x = scrollpos;

	if (m_nHdelta != 0)
	{
		HScrollPos_ += m_nHdelta;
		SetScrollPos(SB_HORZ, HScrollPos_, TRUE);
		ScrollWindow(-m_nHdelta, 0);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void DrawReview::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int delta;

	switch (nSBCode)
	{
	case SB_LINEUP:
		delta = -m_nBasic;
		break;
	case SB_PAGEUP:
		delta = -VPageSize_;
		break;
	case SB_THUMBTRACK:
		delta = static_cast<int>(nPos) - VScrollPos_;
		break;
	case SB_PAGEDOWN:
		delta = VPageSize_;
		break;
	case SB_LINEDOWN:
		delta = m_nBasic;
		break;
	default:
		return;
	}

	scrollpos = VScrollPos_ + delta;
	int maxpos = ViewHeight_ - VPageSize_;
	if (scrollpos < 0)
		delta = -VScrollPos_;
	else
		if (scrollpos > maxpos)
			delta = maxpos - VScrollPos_;

	mouse_scroll_y = scrollpos;
	if (delta != 0)
	{
		VScrollPos_ += delta;
		SetScrollPos(SB_VERT, VScrollPos_, TRUE);
		ScrollWindow(0, -delta);
	}

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL DrawReview::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	dlgDrawScaleH = new DrawScaleH;
	dlgDrawScaleH->Create(IDD_DRAW_SCALE_H, this);
	dlgDrawScaleH->MoveWindow(0, 0, WindowWidth, 20);
	dlgDrawScaleH->ShowWindow(SW_SHOW);

	x_start = (WindowWidth - (2448 / magni)) / 2;
	y_start = ((CamHeight / 4) - (2048 / magni)) / 2;

	if (x_start < 0)
		x_start = 0;

	if (y_start < 0)
		y_start = 0;

	GetDlgItem(IDC_PIC_REVIEW)->MoveWindow(x_start, y_start, 2448 / magni, 2048 / magni);

	scrollpos = 0;
	VScrollPos_ = 0;
	HScrollPos_ = 0;
	mouse_scroll_x = 0;
	mouse_scroll_y = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DrawReview::PreTranslateMessage(MSG* pMsg)
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


void DrawReview::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	int dx;
	int dy;

	if (pDlg->CHK_GRAPHIC == true)
	{
		if (pDlg->MeasurementCase == 1 || pDlg->MeasurementCase == 2 || pDlg->MeasurementCase == 4 || pDlg->MeasurementCase == 5)
		{
			if (pDlg->clickCount == 0)
			{
				stMeasure.ChkMeasurement[pDlg->MeasurementCount] = true;

				if (pDlg->MeasurementCase == 1)
					pDlg->dlgVisionReview->m_list_measurement.SetItemText(pDlg->MeasurementCount, 1, _T("선"));

				else if (pDlg->MeasurementCase == 2)
					pDlg->dlgVisionReview->m_list_measurement.SetItemText(pDlg->MeasurementCount, 1, _T("사각형"));

				else if (pDlg->MeasurementCase == 4)
					pDlg->dlgVisionReview->m_list_measurement.SetItemText(pDlg->MeasurementCount, 1, _T("원"));

				else if (pDlg->MeasurementCase == 5)
					pDlg->dlgVisionReview->m_list_measurement.SetItemText(pDlg->MeasurementCount, 1, _T("중심 거리"));

				stMeasure.CaseMeasurement[pDlg->MeasurementCount] = pDlg->MeasurementCase;

				if (magni == 1)
				{
					stMeasure.FirstPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
					stMeasure.FirstPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;

					stMeasure.SecondPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
					stMeasure.SecondPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
				}

				else if (magni == 2)
				{
					stMeasure.FirstPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
					stMeasure.FirstPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;

					stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
					stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
				}

				else if (magni == 4)
				{
					stMeasure.FirstPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
					stMeasure.FirstPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;

					stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
					stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
				}

				if (pDlg->MeasurementCase == 5)
				{
					CenterDistMeasure(pDlg->MeasurementCount, stMeasure.FirstPoint[pDlg->MeasurementCount]);
				
					if (pDlg->MeasurementCount < 9)
						pDlg->MeasurementCount++;

					else if (pDlg->MeasurementCount >= 9)
						pDlg->MeasurementCount = 0;
				}

				else
				{
					pDlg->clickCount = 1;
				}
			}

			else if (pDlg->clickCount == 1)
			{
				if (magni == 1)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.FirstPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x);
						dy = stMeasure.FirstPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y);

						if (pDlg->MeasurementCase == 1)
						{
							if (abs(dx) > abs(dy))
							{
								stMeasure.SecondPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
								stMeasure.SecondPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;
							}

							else if (abs(dx) <= abs(dy))
							{
								stMeasure.SecondPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
								stMeasure.SecondPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;
							}
						}

						else if (pDlg->MeasurementCase == 2)
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
						}
					}

					else
					{
						stMeasure.SecondPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
						stMeasure.SecondPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
					}
				}

				else if (magni == 2)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.FirstPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x) * 2;
						dy = stMeasure.FirstPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y) * 2;

						if (pDlg->MeasurementCase == 1)
						{
							if (abs(dx) > abs(dy))
							{
								stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
								stMeasure.SecondPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;
							}

							else if (abs(dx) <= abs(dy))
							{
								stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
								stMeasure.SecondPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;
							}
						}

						else if (pDlg->MeasurementCase == 2)
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
						}
					}

					else
					{
						stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
						stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
					}
				}

				else if (magni == 4)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.FirstPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x) * 4;
						dy = stMeasure.FirstPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y) * 4;

						if (pDlg->MeasurementCase == 1)
						{
							if (abs(dx) > abs(dy))
							{
								stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
								stMeasure.SecondPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;
							}

							else if (abs(dx) <= abs(dy))
							{
								stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
								stMeasure.SecondPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;
							}
						}

						else if (pDlg->MeasurementCase == 2)
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
						}
					}

					else
					{
						stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
						stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
					}
				}

				if (pDlg->MeasurementCase == 1)
					LineMeasure(pDlg->MeasurementCount, stMeasure.FirstPoint[pDlg->MeasurementCount], stMeasure.SecondPoint[pDlg->MeasurementCount]);

				else if (pDlg->MeasurementCase == 2)
					RectangleMeasure(pDlg->MeasurementCount, stMeasure.FirstPoint[pDlg->MeasurementCount], stMeasure.SecondPoint[pDlg->MeasurementCount]);

				else if (pDlg->MeasurementCase == 4)
					CircleMeasure(pDlg->MeasurementCount, stMeasure.FirstPoint[pDlg->MeasurementCount], stMeasure.SecondPoint[pDlg->MeasurementCount]);

				if (pDlg->MeasurementCount < 9)
					pDlg->MeasurementCount++;

				else if (pDlg->MeasurementCount >= 9)
					pDlg->MeasurementCount = 0;

				pDlg->clickCount = 0;
			}
		}

		else if (pDlg->MeasurementCase == 3)
		{
			if (pDlg->clickCount == 0)
			{
				stMeasure.ChkMeasurement[pDlg->MeasurementCount] = true;

				pDlg->dlgVisionReview->m_list_measurement.SetItemText(pDlg->MeasurementCount, 1, _T("각도"));

				stMeasure.CaseMeasurement[pDlg->MeasurementCount] = pDlg->MeasurementCase;

				if (magni == 1)
				{
					stMeasure.FirstPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
					stMeasure.FirstPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;

					stMeasure.SecondPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
					stMeasure.SecondPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;

					stMeasure.ThirdPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
					stMeasure.ThirdPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
				}

				else if (magni == 2)
				{
					stMeasure.FirstPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
					stMeasure.FirstPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;

					stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
					stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;

					stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
					stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
				}

				else if (magni == 4)
				{
					stMeasure.FirstPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
					stMeasure.FirstPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;

					stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
					stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;

					stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
					stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
				}

				pDlg->clickCount = 1;
			}

			else if (pDlg->clickCount == 1)
			{
				if (magni == 1)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.FirstPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x);
						dy = stMeasure.FirstPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y);

						if (abs(dx) > abs(dy))
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;

							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;
						}

						else if (abs(dx) <= abs(dy))
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;

							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;
						}
					}

					else
					{
						stMeasure.SecondPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
						stMeasure.SecondPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;

						stMeasure.ThirdPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
						stMeasure.ThirdPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
					}
				}

				else if (magni == 2)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.FirstPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x) * 2;
						dy = stMeasure.FirstPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y) * 2;

						if (abs(dx) > abs(dy))
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;

							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;
						}

						else if (abs(dx) <= abs(dy))
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;

							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;
						}
					}

					else
					{
						stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
						stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;

						stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
						stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
					}
				}

				else if (magni == 4)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.FirstPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x) * 4;
						dy = stMeasure.FirstPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y) * 4;

						if (abs(dx) > abs(dy))
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;

							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;
						}

						else if (abs(dx) <= abs(dy))
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;

							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;
						}
					}

					else
					{
						stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
						stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;

						stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
						stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
					}
				}

				pDlg->clickCount = 2;
			}

			else if (pDlg->clickCount == 2)
			{
				if (magni == 1)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.SecondPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x);
						dy = stMeasure.SecondPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y);

						if (abs(dx) > abs(dy))
						{
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = stMeasure.SecondPoint[pDlg->MeasurementCount].y;
						}

						else if (abs(dx) <= abs(dy))
						{
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = stMeasure.SecondPoint[pDlg->MeasurementCount].x;
						}
					}

					else
					{
						stMeasure.ThirdPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
						stMeasure.ThirdPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
					}
				}

				else if (magni == 2)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.SecondPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x) * 2;
						dy = stMeasure.SecondPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y) * 2;

						if (abs(dx) > abs(dy))
						{
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = stMeasure.SecondPoint[pDlg->MeasurementCount].y;
						}

						else if (abs(dx) <= abs(dy))
						{
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = stMeasure.SecondPoint[pDlg->MeasurementCount].x;
						}
					}

					else
					{
						stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
						stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
					}
				}

				else if (magni == 4)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.SecondPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x) * 4;
						dy = stMeasure.SecondPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y) * 4;

						if (abs(dx) > abs(dy))
						{
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = stMeasure.SecondPoint[pDlg->MeasurementCount].y;
						}

						else if (abs(dx) <= abs(dy))
						{
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = stMeasure.SecondPoint[pDlg->MeasurementCount].x;
						}
					}

					else
					{
						stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
						stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
					}
				}

				AngleMeasure(pDlg->MeasurementCount, stMeasure.FirstPoint[pDlg->MeasurementCount], stMeasure.SecondPoint[pDlg->MeasurementCount], stMeasure.ThirdPoint[pDlg->MeasurementCount]);

				if (pDlg->MeasurementCount < 9)
					pDlg->MeasurementCount++;

				else if (pDlg->MeasurementCount >= 9)
					pDlg->MeasurementCount = 0;

				pDlg->clickCount = 0;
			}
		}
		pDlg->MeasurementCount;
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void DrawReview::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	int dx;
	int dy;

	if (pDlg->CHK_GRAPHIC == true)
	{
		if (pDlg->MeasurementCase == 1 || pDlg->MeasurementCase == 2 || pDlg->MeasurementCase == 4)
		{
			if (pDlg->clickCount == 1)
			{
				if (magni == 1)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.FirstPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x);
						dy = stMeasure.FirstPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y);

						if (pDlg->MeasurementCase == 1)
						{
							if (abs(dx) > abs(dy))
							{
								stMeasure.SecondPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
								stMeasure.SecondPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;
							}

							else if (abs(dx) <= abs(dy))
							{
								stMeasure.SecondPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
								stMeasure.SecondPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;
							}
						}

						else if (pDlg->MeasurementCase == 2)
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
						}

						else if (pDlg->MeasurementCase == 4)
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
						}
					}

					else
					{
						stMeasure.SecondPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
						stMeasure.SecondPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
					}
				}

				else if (magni == 2)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.FirstPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x) * 2;
						dy = stMeasure.FirstPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y) * 2;

						if (pDlg->MeasurementCase == 1)
						{
							if (abs(dx) > abs(dy))
							{
								stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
								stMeasure.SecondPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;
							}

							else if (abs(dx) <= abs(dy))
							{
								stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
								stMeasure.SecondPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;
							}
						}

						else if (pDlg->MeasurementCase == 2)
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
						}

						else if (pDlg->MeasurementCase == 4)
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
						}
					}

					else
					{
						stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
						stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
					}
				}

				else if (magni == 4)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.FirstPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x) * 4;
						dy = stMeasure.FirstPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y) * 4;

						if (pDlg->MeasurementCase == 1)
						{
							if (abs(dx) > abs(dy))
							{
								stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
								stMeasure.SecondPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;
							}

							else if (abs(dx) <= abs(dy))
							{
								stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
								stMeasure.SecondPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;
							}
						}

						else if (pDlg->MeasurementCase == 2)
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
						}

						else if (pDlg->MeasurementCase == 4)
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
						}
					}

					else
					{
						stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
						stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
					}
				}
			}
		}

		else if (pDlg->MeasurementCase == 3)
		{
			if (pDlg->clickCount == 1)
			{
				if (magni == 1)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.FirstPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x);
						dy = stMeasure.FirstPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y);

						if (abs(dx) > abs(dy))
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;

							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;
						}

						else if (abs(dx) <= abs(dy))
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;

							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;
						}
					}

					else
					{
						stMeasure.SecondPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
						stMeasure.SecondPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;

						stMeasure.ThirdPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
						stMeasure.ThirdPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
					}
				}

				else if (magni == 2)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.FirstPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x) * 2;
						dy = stMeasure.FirstPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y) * 2;

						if (abs(dx) > abs(dy))
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;

							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;
						}

						else if (abs(dx) <= abs(dy))
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;

							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;
						}
					}

					else
					{
						stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
						stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;

						stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
						stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
					}
				}

				else if (magni == 4)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.FirstPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x) * 4;
						dy = stMeasure.FirstPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y) * 4;

						if (abs(dx) > abs(dy))
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;

							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = stMeasure.FirstPoint[pDlg->MeasurementCount].y;
						}

						else if (abs(dx) <= abs(dy))
						{
							stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
							stMeasure.SecondPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;

							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = stMeasure.FirstPoint[pDlg->MeasurementCount].x;
						}
					}

					else
					{
						stMeasure.SecondPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
						stMeasure.SecondPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;

						stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
						stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
					}
				}
			}

			else if (pDlg->clickCount == 2)
			{
				if (magni == 1)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.SecondPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x);
						dy = stMeasure.SecondPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y);

						if (abs(dx) > abs(dy))
						{
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = stMeasure.SecondPoint[pDlg->MeasurementCount].y;
						}

						else if (abs(dx) <= abs(dy))
						{
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = stMeasure.SecondPoint[pDlg->MeasurementCount].x;
						}
					}

					else
					{
						stMeasure.ThirdPoint[pDlg->MeasurementCount].x = point.x + mouse_scroll_x;
						stMeasure.ThirdPoint[pDlg->MeasurementCount].y = point.y + mouse_scroll_y;
					}
				}

				else if (magni == 2)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.SecondPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x) * 2;
						dy = stMeasure.SecondPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y) * 2;

						if (abs(dx) > abs(dy))
						{
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = stMeasure.SecondPoint[pDlg->MeasurementCount].y;
						}

						else if (abs(dx) <= abs(dy))
						{
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = stMeasure.SecondPoint[pDlg->MeasurementCount].x;
						}
					}

					else
					{
						stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 2;
						stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 2;
					}
				}

				else if (magni == 4)
				{
					if (GetKeyState(VK_LSHIFT) & 0x8000)
					{
						dx = stMeasure.SecondPoint[pDlg->MeasurementCount].x - (point.x + mouse_scroll_x) * 4;
						dy = stMeasure.SecondPoint[pDlg->MeasurementCount].y - (point.y + mouse_scroll_y) * 4;

						if (abs(dx) > abs(dy))
						{
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = stMeasure.SecondPoint[pDlg->MeasurementCount].y;
						}

						else if (abs(dx) <= abs(dy))
						{
							stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
							stMeasure.ThirdPoint[pDlg->MeasurementCount].x = stMeasure.SecondPoint[pDlg->MeasurementCount].x;
						}
					}

					else
					{
						stMeasure.ThirdPoint[pDlg->MeasurementCount].x = (point.x + mouse_scroll_x) * 4;
						stMeasure.ThirdPoint[pDlg->MeasurementCount].y = (point.y + mouse_scroll_y) * 4;
					}
				}
			}
		}

	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void DrawReview::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CDialogEx::OnLButtonUp(nFlags, point);
}


BOOL DrawReview::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	if (zDelta > 0 && GetKeyState(VK_CONTROL) & 0x8000)
	{
		if (magni > 1)
		{
			magni = magni / 2;

			scrollpos = 0;
			VScrollPos_ = 0;
			HScrollPos_ = 0;
			mouse_scroll_x = 0;
			mouse_scroll_y = 0;

			RECT rc;
			GetClientRect(&rc);
			SendMessage(WM_SIZE, (WPARAM)SIZE_RESTORED, MAKELPARAM(rc.right - rc.left, rc.bottom - rc.top));

			x_start = (WindowWidth - (2448 / magni)) / 2;
			y_start = (((WindowWidth * CamHeight / CamWidth)) - (2048 / magni)) / 2;

			if (x_start < 0)
				x_start = 0;

			if (y_start < 0)
				y_start = 0;

			GetDlgItem(IDC_PIC_REVIEW)->MoveWindow(x_start, y_start, 2448 / magni, 2048 / magni);

			CString strMagni;
			strMagni.Format(_T("x1/%d"), magni);
			if (magni == 1)
				strMagni = _T("x1");
			pDlg->dlgVisionReview->GetDlgItem(IDC_STATIC_MAGNI)->SetWindowTextW(strMagni);

			if (magni == 1)
			{
				pDlg->dlgVisionReview->x_point = 467;
				pDlg->dlgVisionReview->y_point = 540;
			}

			else if (magni == 2)
			{
				pDlg->dlgVisionReview->x_point = 486;
				pDlg->dlgVisionReview->y_point = 555;
			}

			else if (magni == 4)
			{
				pDlg->dlgVisionReview->x_point = 516;
				pDlg->dlgVisionReview->y_point = 579;
			}
		}
	}

	else if (zDelta < 0 && GetKeyState(VK_CONTROL) & 0x8000)
	{
		if (magni < 4)
		{
			magni = magni * 2;

			scrollpos = 0;
			VScrollPos_ = 0;
			HScrollPos_ = 0;
			mouse_scroll_x = 0;
			mouse_scroll_y = 0;

			RECT rc;
			GetClientRect(&rc);
			SendMessage(WM_SIZE, (WPARAM)SIZE_RESTORED, MAKELPARAM(rc.right - rc.left, rc.bottom - rc.top));

			x_start = (WindowWidth - (2448 / magni)) / 2;
			y_start = (((WindowWidth * CamHeight / CamWidth)) - (2048 / magni)) / 2;

			if (x_start < 0)
				x_start = 0;

			if (y_start < 0)
				y_start = 0;

			GetDlgItem(IDC_PIC_REVIEW)->MoveWindow(x_start, y_start, 2448 / magni, 2048 / magni);

			CString strMagni;
			strMagni.Format(_T("x1/%d"), magni);
			pDlg->dlgVisionReview->GetDlgItem(IDC_STATIC_MAGNI)->SetWindowTextW(strMagni);

			if (magni == 1)
			{
				pDlg->dlgVisionReview->x_point = 467;
				pDlg->dlgVisionReview->y_point = 540;
			}

			else if (magni == 2)
			{
				pDlg->dlgVisionReview->x_point = 486;
				pDlg->dlgVisionReview->y_point = 555;
			}

			else if (magni == 4)
			{
				pDlg->dlgVisionReview->x_point = 516;
				pDlg->dlgVisionReview->y_point = 579;
			}
		}
	}
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void DrawReview::LineMeasure(int nCase, CPoint FirstPoint, CPoint secondPoint)
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	int dx;
	CString strValue;

	dx = sqrt(((secondPoint.x - FirstPoint.x) * (secondPoint.x - FirstPoint.x)) + ((secondPoint.y - FirstPoint.y) * (secondPoint.y - FirstPoint.y)));
	strValue.Format(_T("%.3fmm(D)"), dx * ReviewResolution / 1000);
	
	pDlg->dlgVisionReview->m_list_measurement.SetItemText(pDlg->MeasurementCount, 2, strValue);
}


void DrawReview::RectangleMeasure(int nCase, CPoint FirstPoint, CPoint secondPoint)
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	int dx;
	int dy;

	CString strValue;

	dx = abs((secondPoint.x - FirstPoint.x));
	strValue.Format(_T("%.3fmm(H)"), dx * ReviewResolution / 1000);
	pDlg->dlgVisionReview->m_list_measurement.SetItemText(pDlg->MeasurementCount, 2, strValue);

	dy = abs((secondPoint.y - FirstPoint.y));
	strValue.Format(_T("%.3fmm(V)"), dy * ReviewResolution / 1000);
	pDlg->dlgVisionReview->m_list_measurement.SetItemText(pDlg->MeasurementCount, 3, strValue);
}


void DrawReview::AngleMeasure(int nCase, CPoint FirstPoint, CPoint SecondPoint, CPoint ThirdPoint)
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	double angle_1;
	double angle_2;
	double result_angle;
	CString strValue;

	angle_1 = atan2(FirstPoint.y - SecondPoint.y, FirstPoint.x - SecondPoint.x);
	angle_1 = angle_1 * 57.2957951;

	angle_2 = atan2(ThirdPoint.y - SecondPoint.y, ThirdPoint.x - SecondPoint.x);
	angle_2 = angle_2 * 57.2957951;

	if (angle_1 > angle_2)
		result_angle = angle_1 - angle_2;

	else if (angle_1 <= angle_2)
		result_angle = angle_2 - angle_1;

	strValue.Format(_T("%.2f˚"), result_angle);
	pDlg->dlgVisionReview->m_list_measurement.SetItemText(pDlg->MeasurementCount, 2, strValue);
}


void DrawReview::CircleMeasure(int nCase, CPoint FirstPoint, CPoint secondPoint)
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	int dx;
	int dy;

	CString strValue;

	dx = abs((secondPoint.x - FirstPoint.x));
	strValue.Format(_T("%.3fmm(H)"), dx * ReviewResolution / 1000);
	pDlg->dlgVisionReview->m_list_measurement.SetItemText(pDlg->MeasurementCount, 2, strValue);

	dy = abs((secondPoint.y - FirstPoint.y));
	strValue.Format(_T("%.3fmm(V)"), dy * ReviewResolution / 1000);
	pDlg->dlgVisionReview->m_list_measurement.SetItemText(pDlg->MeasurementCount, 3, strValue);
}

void DrawReview::CenterDistMeasure(int nCase, CPoint FirstPoint)
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	int dx;
	int dy;

	CString strValue;

	dx = abs((1224 - FirstPoint.x));
	strValue.Format(_T("%.3fmm(H)"), dx * ReviewResolution / 1000);
	pDlg->dlgVisionReview->m_list_measurement.SetItemText(pDlg->MeasurementCount, 2, strValue);

	dy = abs((1024 - FirstPoint.y));
	strValue.Format(_T("%.3fmm(V)"), dy * ReviewResolution / 1000);
	pDlg->dlgVisionReview->m_list_measurement.SetItemText(pDlg->MeasurementCount, 3, strValue);
}


void DrawReview::MouseClick(CPoint clickPoint)
{
}
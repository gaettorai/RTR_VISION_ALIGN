// DrawSetting.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "DrawSetting.h"
#include "afxdialogex.h"

#include "RVisionDlg.h"

// DrawSetting 대화 상자

IMPLEMENT_DYNAMIC(DrawSetting, CDialogEx)

const int m_nLineSize = 10;
const int m_nBasic = 10;
const int m_nRepeat = 10;

DrawSetting::DrawSetting(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRAW_SETTING, pParent)
{

}

DrawSetting::~DrawSetting()
{
}

void DrawSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_SETTING, m_pic_setting);
}


BEGIN_MESSAGE_MAP(DrawSetting, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// DrawSetting 메시지 처리기


int DrawSetting::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	magni = 1;

	return 0;
}


HBRUSH DrawSetting::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL DrawSetting::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}


void DrawSetting::OnSize(UINT nType, int cx, int cy)
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


void DrawSetting::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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


void DrawSetting::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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


BOOL DrawSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	x_start = (WindowWidth - (2448 / magni)) / 2;
	y_start = ((CamHeight / 4 + 30) - (2048 / magni)) / 2;

	if (x_start < 0)
		x_start = 0;

	if (y_start < 0)
		y_start = 0;

	GetDlgItem(IDC_PIC_SETTING)->MoveWindow(x_start, y_start, 2448 / magni, 2048 / magni);

	scrollpos = 0;
	VScrollPos_ = 0;
	HScrollPos_ = 0;
	mouse_scroll_x = 0;
	mouse_scroll_y = 0;

	rectMark = { 10, 10, 100, 100 };

	mMarkTracker.m_rect = rectMark;
	mMarkTracker.m_nStyle = 0;
	mMarkTracker.m_nStyle |= CRectTracker::dottedLine;
	mMarkTracker.m_nStyle |= CRectTracker::resizeOutside;

	CHK_MARK_ALIGN = false;
	CHK_MARK_FC = false;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DrawSetting::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void DrawSetting::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CRect rt_align_1;

	((CStatic*)GetDlgItem(IDC_PIC_SETTING))->GetWindowRect(&rt_align_1);

	ScreenToClient(&rt_align_1);

	if (rt_align_1.PtInRect(point)) // 픽쳐 컨트롤의 사각형 영역에 마우스 클릭 좌표(point) 가 있으면...TRUE
	{
		if (mMarkTracker.HitTest(point) < 0)
		{
			//CRectTracker track;
			//if (track.TrackRubberBand(this, point, true)) {
			//	track.m_rect.NormalizeRect();
			//	pDlg->m_tracker.m_rect = track.m_rect;
			//	//SetImageRectSelection(pDoc,&(m_tracker.m_rect));
			//}
			//else {
			//	pDlg->m_tracker.m_rect = CRect(0, 0, 0, 0);
			//}
		}
		else
		{
			if (mMarkTracker.Track(this, point, true)) {
				mMarkTracker.m_rect.NormalizeRect();
				//	pDlg->Mark_roi();
				//SetImageRectSelection(pDoc,&(m_tracker.m_rect));
			}
			else
			{
			}
		}
	}

	else  // 픽쳐 컨트롤 영역에 마우스 클릭 좌표가 없으면... FALSE
	{

	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void DrawSetting::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL DrawSetting::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	if (mMarkTracker.SetCursor(pWnd, nHitTest))
		return TRUE;

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


BOOL DrawSetting::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
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

			GetDlgItem(IDC_PIC_SETTING)->MoveWindow(x_start, y_start, 2448 / magni, 2048 / magni);
		}
	}

	else if (zDelta < 0 && GetKeyState(VK_CONTROL) & 0x8000)
	{
		if (magni < 8)
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

			GetDlgItem(IDC_PIC_SETTING)->MoveWindow(x_start, y_start, 2448 / magni, 2048 / magni);
		}
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

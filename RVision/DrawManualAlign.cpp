// DrawManualAlign.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "DrawManualAlign.h"
#include "afxdialogex.h"

#include "RVisionDlg.h"

// DrawManualAlign 대화 상자

IMPLEMENT_DYNAMIC(DrawManualAlign, CDialogEx)

const int m_nLineSize = 10;
const int m_nBasic = 10;
const int m_nRepeat = 10;

extern EdgeAlignParameter stEdgeAlign;

DrawManualAlign::DrawManualAlign(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRAW_MANUALALIGN, pParent)
{

}

DrawManualAlign::~DrawManualAlign()
{
}

void DrawManualAlign::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_MANUALALIGN, m_pic_manualalign);
}


BEGIN_MESSAGE_MAP(DrawManualAlign, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// DrawManualAlign 메시지 처리기


int DrawManualAlign::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	magni = 4;

	return 0;
}


HBRUSH DrawManualAlign::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void DrawManualAlign::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

}


void DrawManualAlign::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void DrawManualAlign::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL DrawManualAlign::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL DrawManualAlign::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	x_start = (WindowWidth - (2448 / magni)) / 2;
	y_start = ((CamHeight / 4 + 30) - (2048 / magni)) / 2;

	if (x_start < 0)
		x_start = 0;

	if (y_start < 0)
		y_start = 0;

	GetDlgItem(IDC_PIC_MANUALALIGN)->MoveWindow(0, 0, 2448 / magni, 2048 / magni);

	scrollpos = 0;
	VScrollPos_ = 0;
	HScrollPos_ = 0;
	mouse_scroll_x = 0;
	mouse_scroll_y = 0;

	nClickCount = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DrawManualAlign::PreTranslateMessage(MSG* pMsg)
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


BOOL DrawManualAlign::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void DrawManualAlign::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CString strValue;
	if (pDlg->dlgPopupManualAlign.ChkClick == true)
	{
		if (nClickCount == 0)
		{
			stEdgeAlign.FirstPoint[pDlg->dlgPopupManualAlign.SelectCam].x = point.x + mouse_scroll_x;
			stEdgeAlign.FirstPoint[pDlg->dlgPopupManualAlign.SelectCam].y = point.y + mouse_scroll_y;

			stEdgeAlign.SecondPoint[pDlg->dlgPopupManualAlign.SelectCam].x = point.x + mouse_scroll_x;
			stEdgeAlign.SecondPoint[pDlg->dlgPopupManualAlign.SelectCam].y = point.y + mouse_scroll_y;

			nClickCount = 1;
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void DrawManualAlign::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	if (pDlg->dlgPopupManualAlign.ChkClick == true)
	{
		if (nClickCount == 1)
		{
			stEdgeAlign.SecondPoint[pDlg->dlgPopupManualAlign.SelectCam].x = point.x + mouse_scroll_x;
			stEdgeAlign.SecondPoint[pDlg->dlgPopupManualAlign.SelectCam].y = point.y + mouse_scroll_y;
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void DrawManualAlign::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	if (pDlg->dlgPopupManualAlign.ChkClick == true)
	{
		if (nClickCount == 1)
		{
			stEdgeAlign.SecondPoint[pDlg->dlgPopupManualAlign.SelectCam].x = point.x + mouse_scroll_x;
			stEdgeAlign.SecondPoint[pDlg->dlgPopupManualAlign.SelectCam].y = point.y + mouse_scroll_y;

			// SHIFT 누르고 이동했을 경우 
			if (GetKeyState(VK_LSHIFT) & 0x8000)
			{

			}

			nClickCount = 0;
		}
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}

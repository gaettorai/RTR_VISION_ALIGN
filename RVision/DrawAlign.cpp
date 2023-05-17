// DrawAlign.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "DrawAlign.h"
#include "afxdialogex.h"

#include "RVisionDlg.h"

// DrawAlign 대화 상자

IMPLEMENT_DYNAMIC(DrawAlign, CDialogEx)

DrawAlign::DrawAlign(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRAW_ALIGN, pParent)
{

}

DrawAlign::~DrawAlign()
{
}

void DrawAlign::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_ALIGN1, m_pic_align1);
	DDX_Control(pDX, IDC_PIC_ALIGN2, m_pic_align2);
	DDX_Control(pDX, IDC_PIC_ALIGN3, m_pic_align3);
	DDX_Control(pDX, IDC_PIC_ALIGN4, m_pic_align4);
}


BEGIN_MESSAGE_MAP(DrawAlign, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// DrawAlign 메시지 처리기


int DrawAlign::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH DrawAlign::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL DrawAlign::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL DrawAlign::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	GetDlgItem(IDC_PIC_ALIGN1)->MoveWindow(0, 0, CamWidth / 8, CamHeight / 8);
	GetDlgItem(IDC_PIC_ALIGN2)->MoveWindow(0, CamHeight / 8, CamWidth / 8, CamHeight / 8);
	GetDlgItem(IDC_PIC_ALIGN3)->MoveWindow(0 + CamWidth / 8, 0, CamWidth / 8, CamHeight / 8);
	GetDlgItem(IDC_PIC_ALIGN4)->MoveWindow(0 + CamWidth / 8, CamHeight / 8, CamWidth / 8, CamHeight / 8);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL DrawAlign::PreTranslateMessage(MSG* pMsg)
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


void DrawAlign::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CDialogEx::OnLButtonDown(nFlags, point);
}


void DrawAlign::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnMouseMove(nFlags, point);
}


void DrawAlign::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnLButtonUp(nFlags, point);
}


BOOL DrawAlign::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}
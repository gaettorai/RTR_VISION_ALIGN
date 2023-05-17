// RVisionAlign.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "RVisionAlign.h"
#include "afxdialogex.h"

#include "RVisionDlg.h"

// RVisionAlign 대화 상자

IMPLEMENT_DYNAMIC(RVisionAlign, CDialogEx)

extern EdgeAlignParameter stEdgeAlign;
extern MarkAlignParameter stMarkAlign;


RVisionAlign::RVisionAlign(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RVISION_ALIGN, pParent)
{

}

RVisionAlign::~RVisionAlign()
{
}

void RVisionAlign::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ICON_ALIGNSTART, m_icon_alignstart);
	DDX_Control(pDX, IDC_ICON_ALIGNRUN, m_icon_alignrun);
	DDX_Control(pDX, IDC_ICON_ALIGNEND, m_icon_alignend);
	DDX_Control(pDX, IDC_ICON_HEARTBEAT, m_icon_heartbeat);
	DDX_Control(pDX, IDC_ICON_CAM1, m_icon_cam1);
	DDX_Control(pDX, IDC_ICON_CAM2, m_icon_cam2);
	DDX_Control(pDX, IDC_ICON_CAM3, m_icon_cam3);
	DDX_Control(pDX, IDC_ICON_CAM4, m_icon_cam4);
	DDX_Control(pDX, IDC_ICON_CAM5, m_icon_cam5);
}


BEGIN_MESSAGE_MAP(RVisionAlign, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_STN_CLICKED(IDC_ICON_RECONNECT, &RVisionAlign::OnStnClickedIconReconnect)
END_MESSAGE_MAP()


// RVisionAlign 메시지 처리기


int RVisionAlign::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	
	return 0;
}


HBRUSH RVisionAlign::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	// TODO:  여기서 DC의 특성을 변경합니다.
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_TOTALJUDGE)
		{
			if (bChkJudge == true)
				pDC->SetTextColor(RGB(0, 176, 80));

			else
				pDC->SetTextColor(RGB(255, 0, 0));

		}

		if (pWnd->GetDlgCtrlID() == IDC_STATIC_ALIGN_1_DETECT)
		{
			if (stEdgeAlign.ChkFind[0] == true)
				pDC->SetTextColor(RGB(0, 176, 80));

			else
				pDC->SetTextColor(RGB(255, 0, 0));
		}


		if (pWnd->GetDlgCtrlID() == IDC_STATIC_ALIGN_2_DETECT)
		{
			if (stEdgeAlign.ChkFind[1] == true)
				pDC->SetTextColor(RGB(0, 176, 80));

			else
				pDC->SetTextColor(RGB(255, 0, 0));
		}


		if (pWnd->GetDlgCtrlID() == IDC_STATIC_ALIGN_3_DETECT)
		{
			if (stEdgeAlign.ChkFind[2] == true)
				pDC->SetTextColor(RGB(0, 176, 80));

			else
				pDC->SetTextColor(RGB(255, 0, 0));
		}


		if (pWnd->GetDlgCtrlID() == IDC_STATIC_ALIGN_4_DETECT)
		{
			if (stEdgeAlign.ChkFind[3] == true)
				pDC->SetTextColor(RGB(0, 176, 80));

			else
				pDC->SetTextColor(RGB(255, 0, 0));
		}

		if (pWnd->GetDlgCtrlID() == IDC_STATIC_MATCHRATE_JUDGE_1)
		{
			if (stMarkAlign.ChkFind[0] == true)
				pDC->SetTextColor(RGB(0, 176, 80));

			else
				pDC->SetTextColor(RGB(255, 0, 0));
		}

		if (pWnd->GetDlgCtrlID() == IDC_STATIC_MATCHRATE_JUDGE_2)
		{
			if (stMarkAlign.ChkFind[1] == true)
				pDC->SetTextColor(RGB(0, 176, 80));

			else
				pDC->SetTextColor(RGB(255, 0, 0));
		}

		if (pWnd->GetDlgCtrlID() == IDC_STATIC_MATCHRATE_JUDGE_3)
		{
			if (stMarkAlign.ChkFind[2] == true)
				pDC->SetTextColor(RGB(0, 176, 80));

			else
				pDC->SetTextColor(RGB(255, 0, 0));
		}

		if (pWnd->GetDlgCtrlID() == IDC_STATIC_MATCHRATE_JUDGE_4)
		{
			if (stMarkAlign.ChkFind[3] == true)
				pDC->SetTextColor(RGB(0, 176, 80));

			else
				pDC->SetTextColor(RGB(255, 0, 0));
		}

		if (pWnd->GetDlgCtrlID() == IDC_STATIC_XMODIFY_JUDGE)
		{
			if (bChkModifyX == true)
				pDC->SetTextColor(RGB(0, 176, 80));

			else
				pDC->SetTextColor(RGB(255, 0, 0));
		}

		if (pWnd->GetDlgCtrlID() == IDC_STATIC_YMODIFY_JUDGE)
		{
			if (bChkModifyY == true)
				pDC->SetTextColor(RGB(0, 176, 80));

			else
				pDC->SetTextColor(RGB(255, 0, 0));
		}

		if (pWnd->GetDlgCtrlID() == IDC_STATIC_TMODIFY_JUDGE)
		{
			if (bChkModifyT == true)
				pDC->SetTextColor(RGB(0, 176, 80));

			else
				pDC->SetTextColor(RGB(255, 0, 0));
		}

		if (pWnd->GetDlgCtrlID() == IDC_STATIC_LEVEL_H_JUDGE)
		{
			if (bChkLevel == true)
				pDC->SetTextColor(RGB(0, 176, 80));

			else
				pDC->SetTextColor(RGB(255, 0, 0));
		}

		if (pWnd->GetDlgCtrlID() == IDC_STATIC_MISTAKE_JUDGE)
		{
			if (bChkMistake == true)
				pDC->SetTextColor(RGB(0, 176, 80));

			else
				pDC->SetTextColor(RGB(255, 0, 0));
		}
	}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL RVisionAlign::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//CRect rect;

	//GetClientRect(rect);
	//pDC->FillSolidRect(rect, RGB(148, 148, 148));

	//return TRUE;

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL RVisionAlign::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	dlgDrawAlign = new DrawAlign;
	dlgDrawAlign->Create(IDD_DRAW_ALIGN, this);
	dlgDrawAlign->MoveWindow(0, 0, WindowWidth, CamHeight / 4);
	dlgDrawAlign->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_GRP_DETECT)->MoveWindow(10, CamHeight / 4 + 10, 190, 150);
	GetDlgItem(IDC_STATIC_ALIGN_1)->MoveWindow(20, CamHeight / 4 + 35, 60, 30);
	GetDlgItem(IDC_STATIC_ALIGN_2)->MoveWindow(20, CamHeight / 4 + 65, 60, 30);
	GetDlgItem(IDC_STATIC_ALIGN_3)->MoveWindow(20, CamHeight / 4 + 95, 60, 30);
	GetDlgItem(IDC_STATIC_ALIGN_4)->MoveWindow(20, CamHeight / 4 + 125, 60, 30);
	GetDlgItem(IDC_STATIC_ALIGN_1_DETECT)->MoveWindow(160, CamHeight / 4 + 35, 30, 30);
	GetDlgItem(IDC_STATIC_ALIGN_2_DETECT)->MoveWindow(160, CamHeight / 4 + 65, 30, 30);
	GetDlgItem(IDC_STATIC_ALIGN_3_DETECT)->MoveWindow(160, CamHeight / 4 + 95, 30, 30);
	GetDlgItem(IDC_STATIC_ALIGN_4_DETECT)->MoveWindow(160, CamHeight / 4 + 125, 30, 30);
	
	GetDlgItem(IDC_GRP_JUDGE)->MoveWindow(10, CamHeight / 4 + 170, 190, 80);
	GetDlgItem(IDC_STATIC_LEVEL_H)->MoveWindow(20, CamHeight / 4 + 185, 60, 30);
	GetDlgItem(IDC_STATIC_MISTAKE)->MoveWindow(20, CamHeight / 4 + 215, 60, 30);
	GetDlgItem(IDC_STATIC_LEVEL_H_VALUE)->MoveWindow(80, CamHeight / 4 + 185, 80, 30);
	GetDlgItem(IDC_STATIC_LEVEL_H_JUDGE)->MoveWindow(160, CamHeight / 4 + 185, 30, 30);
	GetDlgItem(IDC_STATIC_MISTAKE_VALUE)->MoveWindow(80, CamHeight / 4 + 215, 80, 30);
	GetDlgItem(IDC_STATIC_MISTAKE_JUDGE)->MoveWindow(160, CamHeight / 4 + 215, 30, 30);

	GetDlgItem(IDC_GRP_MATCHRATE)->MoveWindow(210, CamHeight / 4 + 10, 220, 150);
	GetDlgItem(IDC_STATIC_MATCHRATE_1)->MoveWindow(220, CamHeight / 4 + 35, 60, 30);
	GetDlgItem(IDC_STATIC_MATCHRATE_2)->MoveWindow(220, CamHeight / 4 + 65, 60, 30);
	GetDlgItem(IDC_STATIC_MATCHRATE_3)->MoveWindow(220, CamHeight / 4 + 95, 60, 30);
	GetDlgItem(IDC_STATIC_MATCHRATE_4)->MoveWindow(220, CamHeight / 4 + 125, 60, 30);
	GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_1)->MoveWindow(280, CamHeight / 4 + 35, 100, 30);
	GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_2)->MoveWindow(280, CamHeight / 4 + 65, 100, 30);
	GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_3)->MoveWindow(280, CamHeight / 4 + 95, 100, 30);
	GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_4)->MoveWindow(280, CamHeight / 4 + 125, 100, 30);
	GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_1)->MoveWindow(380, CamHeight / 4 + 35, 40, 30);
	GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_2)->MoveWindow(380, CamHeight / 4 + 65, 40, 30);
	GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_3)->MoveWindow(380, CamHeight / 4 + 95, 40, 30);
	GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_4)->MoveWindow(380, CamHeight / 4 + 125, 40, 30);

	GetDlgItem(IDC_GRP_MODIFY)->MoveWindow(210, CamHeight / 4 + 170, 220, 110);
	GetDlgItem(IDC_STATIC_XMODIFY)->MoveWindow(220, CamHeight / 4 + 185, 60, 30);
	GetDlgItem(IDC_STATIC_YMODIFY)->MoveWindow(220, CamHeight / 4 + 215, 60, 30);
	GetDlgItem(IDC_STATIC_TMODIFY)->MoveWindow(220, CamHeight / 4 + 245, 60, 30);
	GetDlgItem(IDC_STATIC_XMODIFY_VALUE)->MoveWindow(280, CamHeight / 4 + 185, 100, 30);
	GetDlgItem(IDC_STATIC_YMODIFY_VALUE)->MoveWindow(280, CamHeight / 4 + 215, 100, 30);
	GetDlgItem(IDC_STATIC_TMODIFY_VALUE)->MoveWindow(280, CamHeight / 4 + 245, 100, 30);
	GetDlgItem(IDC_STATIC_XMODIFY_JUDGE)->MoveWindow(380, CamHeight / 4 + 185, 40, 30);
	GetDlgItem(IDC_STATIC_YMODIFY_JUDGE)->MoveWindow(380, CamHeight / 4 + 215, 40, 30);
	GetDlgItem(IDC_STATIC_TMODIFY_JUDGE)->MoveWindow(380, CamHeight / 4 + 245, 40, 30);

	GetDlgItem(IDC_STATIC_TOTALJUDGE)->MoveWindow(WindowWidth - 140, CamHeight / 4 + 10, 120, 100);
	GetDlgItem(IDC_STATIC_PROCTIME)->MoveWindow(WindowWidth - 160, CamHeight / 4 + 115, 140, 30);
	
	GetDlgItem(IDC_STATIC_ALIGNSTART)->MoveWindow(WindowWidth - 130, CamHeight / 4 + 185, 80, 30);
	GetDlgItem(IDC_STATIC_ALIGNRUN)->MoveWindow(WindowWidth - 130, CamHeight / 4 + 215, 80, 30);
	GetDlgItem(IDC_STATIC_ALIGNEND)->MoveWindow(WindowWidth - 130, CamHeight / 4 + 245, 80, 30);
	GetDlgItem(IDC_ICON_ALIGNSTART)->MoveWindow(WindowWidth - 40, CamHeight / 4 + 185, 30, 30);
	GetDlgItem(IDC_ICON_ALIGNRUN)->MoveWindow(WindowWidth - 40, CamHeight / 4 + 215, 30, 30);
	GetDlgItem(IDC_ICON_ALIGNEND)->MoveWindow(WindowWidth - 40, CamHeight / 4 + 245, 30, 30);

	GetDlgItem(IDC_STATIC_RECONNECT)->MoveWindow(10, CamHeight / 4 + 275, 100, 30);
	GetDlgItem(IDC_ICON_RECONNECT)->MoveWindow(130, CamHeight / 4 + 275, 30, 30);

	GetDlgItem(IDC_STATIC_CHK_HEARTBEAT)->MoveWindow(10, CamHeight / 4 + 310, 60, 30);
	GetDlgItem(IDC_STATIC_CHK_CAM1)->MoveWindow(110, CamHeight / 4 + 310, 60, 30);
	GetDlgItem(IDC_STATIC_CHK_CAM2)->MoveWindow(210, CamHeight / 4 + 310, 60, 30);
	GetDlgItem(IDC_STATIC_CHK_CAM3)->MoveWindow(310, CamHeight / 4 + 310, 60, 30);
	GetDlgItem(IDC_STATIC_CHK_CAM4)->MoveWindow(410, CamHeight / 4 + 310, 60, 30);
	GetDlgItem(IDC_STATIC_CHK_CAM5)->MoveWindow(510, CamHeight / 4 + 310, 60, 30);

	GetDlgItem(IDC_ICON_HEARTBEAT)->MoveWindow(72, CamHeight / 4 + 310, 30, 30);
	GetDlgItem(IDC_ICON_CAM1)->MoveWindow(172, CamHeight / 4 + 310, 30, 30);
	GetDlgItem(IDC_ICON_CAM2)->MoveWindow(272, CamHeight / 4 + 310, 30, 30);
	GetDlgItem(IDC_ICON_CAM3)->MoveWindow(372, CamHeight / 4 + 310, 30, 30);
	GetDlgItem(IDC_ICON_CAM4)->MoveWindow(472, CamHeight / 4 + 310, 30, 30);
	GetDlgItem(IDC_ICON_CAM5)->MoveWindow(572, CamHeight / 4 + 310, 30, 30);

	HFONT titleFont;
	titleFont = CreateFont(100, 30, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_STATIC_TOTALJUDGE)->SendMessage(WM_SETFONT, (WPARAM)titleFont, (LPARAM)TRUE);

	HFONT staticFont;
	staticFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_STATIC_ALIGN_1)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_2)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_3)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_4)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_1_DETECT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_2_DETECT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_3_DETECT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGN_4_DETECT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LEVEL_H)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MISTAKE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_XMODIFY)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_YMODIFY)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TMODIFY)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_XMODIFY_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_YMODIFY_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TMODIFY_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_XMODIFY_JUDGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_YMODIFY_JUDGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_TMODIFY_JUDGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MATCHRATE_1)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MATCHRATE_2)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MATCHRATE_3)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MATCHRATE_4)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_1)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_2)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_3)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_4)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_1)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_2)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_3)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_4)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LEVEL_H_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MISTAKE_VALUE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_LEVEL_H_JUDGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_MISTAKE_JUDGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_PROCTIME)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_GRP_DETECT)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_GRP_MODIFY)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_GRP_MATCHRATE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_GRP_JUDGE)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGNSTART)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGNRUN)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_ALIGNEND)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);

	HFONT chkFont;
	chkFont = CreateFont(13, 5, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));

	GetDlgItem(IDC_STATIC_RECONNECT)->SendMessage(WM_SETFONT, (WPARAM)chkFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CHK_HEARTBEAT)->SendMessage(WM_SETFONT, (WPARAM)chkFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CHK_CAM1)->SendMessage(WM_SETFONT, (WPARAM)chkFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CHK_CAM2)->SendMessage(WM_SETFONT, (WPARAM)chkFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CHK_CAM3)->SendMessage(WM_SETFONT, (WPARAM)chkFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CHK_CAM4)->SendMessage(WM_SETFONT, (WPARAM)chkFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_CHK_CAM5)->SendMessage(WM_SETFONT, (WPARAM)chkFont, (LPARAM)TRUE);


	bChkJudge = false;
	bChkModifyX = false;
	bChkModifyY = false;
	bChkModifyT = false;
	bChkLevel = false;
	bChkMatchrate1 = false;
	bChkMatchrate2 = false;
	bChkMatchrate3 = false;
	bChkMatchrate4 = false;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL RVisionAlign::PreTranslateMessage(MSG* pMsg)
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


void RVisionAlign::DisplayEdge(bool nCase)
{
	GetDlgItem(IDC_STATIC_ALIGN_1)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_ALIGN_2)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_ALIGN_3)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_ALIGN_4)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_ALIGN_1_DETECT)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_ALIGN_2_DETECT)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_ALIGN_3_DETECT)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_ALIGN_4_DETECT)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_LEVEL_H)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_MISTAKE)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_LEVEL_H_VALUE)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_MISTAKE_VALUE)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_LEVEL_H_JUDGE)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_MISTAKE_JUDGE)->EnableWindow(nCase);

}

void RVisionAlign::DisplayMark(bool nCase)
{
	GetDlgItem(IDC_STATIC_MATCHRATE_1)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_MATCHRATE_2)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_MATCHRATE_3)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_MATCHRATE_4)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_1)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_2)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_3)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_MATCHRATE_VALUE_4)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_1)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_2)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_3)->EnableWindow(nCase);
	GetDlgItem(IDC_STATIC_MATCHRATE_JUDGE_4)->EnableWindow(nCase);
}


void RVisionAlign::OnStnClickedIconReconnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	if(pDlg->chkalarmdisplay != 1)
		pDlg->DisplayAlarm();
}

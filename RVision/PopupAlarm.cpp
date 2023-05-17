// PopupAlarm.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "PopupAlarm.h"
#include "afxdialogex.h"


// PopupAlarm 대화 상자

IMPLEMENT_DYNAMIC(PopupAlarm, CDialogEx)

PopupAlarm::PopupAlarm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POPUP_ALARM, pParent)
{

}

PopupAlarm::~PopupAlarm()
{
}

void PopupAlarm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PopupAlarm, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// PopupAlarm 메시지 처리기


BOOL PopupAlarm::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//MoveWindow(rcDialog);

	//GetDlgItem(IDC_STATIC_ALARM)->SetWindowTextW(_T("카메라 재 연결 중..."));
	GetDlgItem(IDC_STATIC_ALARM)->MoveWindow(0, 0, 200, 60);

	HFONT staticFont;
	staticFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_STATIC_ALARM)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);

	DisplayMessage(strMessage);
	//AnimateWindow(200, AW_SLIDE | AW_BLEND);

	//SetTimer(0, 3000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL PopupAlarm::PreTranslateMessage(MSG* pMsg)
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


void PopupAlarm::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//EndDialog(0);
	CDialogEx::OnTimer(nIDEvent);
}


void PopupAlarm::EndWindodw()
{
	EndDialog(0);
}


void PopupAlarm::DisplayMessage(CString strMessage)
{
	GetDlgItem(IDC_STATIC_ALARM)->SetWindowTextW(strMessage);
}
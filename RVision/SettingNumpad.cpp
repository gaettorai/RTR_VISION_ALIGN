// SettingNumpad.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "SettingNumpad.h"
#include "afxdialogex.h"


// SettingNumpad 대화 상자

IMPLEMENT_DYNAMIC(SettingNumpad, CDialogEx)

SettingNumpad::SettingNumpad(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_NUMPAD, pParent)
{

}

SettingNumpad::~SettingNumpad()
{
}

void SettingNumpad::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SettingNumpad, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// SettingNumpad 메시지 처리기


int SettingNumpad::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH SettingNumpad::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL SettingNumpad::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL SettingNumpad::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL SettingNumpad::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}

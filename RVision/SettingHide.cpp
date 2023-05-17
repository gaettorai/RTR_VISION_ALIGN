// SettingHide.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "SettingHide.h"
#include "afxdialogex.h"


// SettingHide 대화 상자

IMPLEMENT_DYNAMIC(SettingHide, CDialogEx)

SettingHide::SettingHide(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_HIDE, pParent)
{

}

SettingHide::~SettingHide()
{
}

void SettingHide::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_HIDE1, m_edit_hide1);
	DDX_Control(pDX, IDC_EDIT_HIDE2, m_edit_hide2);
	DDX_Control(pDX, IDC_EDIT_HIDE3, m_edit_hide3);
	DDX_Control(pDX, IDC_EDIT_HIDE4, m_edit_hide4);
	DDX_Control(pDX, IDC_EDIT_HIDE5, m_edit_hide5);
}


BEGIN_MESSAGE_MAP(SettingHide, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &SettingHide::OnBnClickedOk)
END_MESSAGE_MAP()


// SettingHide 메시지 처리기


int SettingHide::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH SettingHide::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL SettingHide::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL SettingHide::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(rcDialog);

	GetDlgItem(IDC_STATIC_HIDE1)->MoveWindow(10, 10, 100, 30);
	GetDlgItem(IDC_STATIC_HIDE2)->MoveWindow(10, 50, 100, 30);
	GetDlgItem(IDC_STATIC_HIDE3)->MoveWindow(10, 90, 100, 30);
	GetDlgItem(IDC_STATIC_HIDE4)->MoveWindow(10, 130, 100, 30);
	GetDlgItem(IDC_STATIC_HIDE5)->MoveWindow(10, 170, 100, 30);

	GetDlgItem(IDC_EDIT_HIDE1)->MoveWindow(110, 15, 80, 20);
	GetDlgItem(IDC_EDIT_HIDE2)->MoveWindow(110, 55, 80, 20);
	GetDlgItem(IDC_EDIT_HIDE3)->MoveWindow(110, 95, 80, 20);
	GetDlgItem(IDC_EDIT_HIDE4)->MoveWindow(110, 135, 80, 20);
	GetDlgItem(IDC_EDIT_HIDE5)->MoveWindow(110, 175, 80, 20);

	GetDlgItem(IDOK)->MoveWindow(10, 210, 80, 30);
	GetDlgItem(IDCANCEL)->MoveWindow(110, 210, 80, 30);

	HFONT staticFont;
	staticFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_STATIC_HIDE1)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_HIDE2)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_HIDE3)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_HIDE4)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_STATIC_HIDE5)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDOK)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDCANCEL)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);

	DisplayParam();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void SettingHide::DisplayParam()
{
	CString strVal;

	dModifyX = _wtof(AfxGetApp()->GetProfileStringW(_T("ALIGN"), _T("MODIFYX")));
	dModifyY = _wtof(AfxGetApp()->GetProfileStringW(_T("ALIGN"), _T("MODIFYY")));
	dModifyT = _wtof(AfxGetApp()->GetProfileStringW(_T("ALIGN"), _T("MODIFYT")));

	strVal.Format(_T("%.3f"), dModifyX);
	m_edit_hide1.SetWindowTextW(strVal);

	strVal.Format(_T("%.3f"), dModifyY);
	m_edit_hide2.SetWindowTextW(strVal);

	strVal.Format(_T("%.3f"), dModifyT);
	m_edit_hide3.SetWindowTextW(strVal);
}

void SettingHide::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strVal;
	
	m_edit_hide1.GetWindowTextW(strVal);
	dModifyX = _wtof(strVal);

	m_edit_hide2.GetWindowTextW(strVal);
	dModifyY = _wtof(strVal);

	m_edit_hide3.GetWindowTextW(strVal);
	dModifyT = _wtof(strVal);

	CDialogEx::OnOK();
}

// SettingAlignMethod.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "afxdialogex.h"
#include "SettingAlignMethod.h"

#include "RVisionDlg.h"

// SettingAlignMethod 대화 상자

IMPLEMENT_DYNAMIC(SettingAlignMethod, CDialogEx)

SettingAlignMethod::SettingAlignMethod(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_ALIGN_METHOD, pParent)

{

}

SettingAlignMethod::~SettingAlignMethod()
{
}

void SettingAlignMethod::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_ALIGN_ALL, m_chk_align_all);
	DDX_Control(pDX, IDC_CHK_ALIGN_12, m_chk_align_12);
	DDX_Control(pDX, IDC_CHK_ALIGN_34, m_chk_align_34);
	DDX_Control(pDX, IDC_CHK_ALIGN_13, m_chk_align_13);
	DDX_Control(pDX, IDC_CHK_ALIGN_24, m_chk_align_24);
}


BEGIN_MESSAGE_MAP(SettingAlignMethod, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_CHK_ALIGN_ALL, &SettingAlignMethod::OnBnClickedChkAlignAll)
	ON_BN_CLICKED(IDC_CHK_ALIGN_12, &SettingAlignMethod::OnBnClickedChkAlign12)
	ON_BN_CLICKED(IDC_CHK_ALIGN_34, &SettingAlignMethod::OnBnClickedChkAlign34)
	ON_BN_CLICKED(IDC_CHK_ALIGN_13, &SettingAlignMethod::OnBnClickedChkAlign13)
	ON_BN_CLICKED(IDC_CHK_ALIGN_24, &SettingAlignMethod::OnBnClickedChkAlign24)
END_MESSAGE_MAP()


// SettingAlignMethod 메시지 처리기


int SettingAlignMethod::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH SettingAlignMethod::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	// TODO:  여기서 DC의 특성을 변경합니다.

	//if(pWnd->GetDlgCtrlID() == IDC_CHK_ALIGN_ALL)
	//{
	//	pDC->SetBkMode(TRANSPARENT);
	//	hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
	//}


	return hbr;
}


BOOL SettingAlignMethod::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL SettingAlignMethod::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	MoveWindow(rcDialog);

	GetDlgItem(IDC_CHK_ALIGN_ALL)->MoveWindow(10, 10, 100, 20);
	GetDlgItem(IDC_PIC_ALIGN_ALL)->MoveWindow(10, 40, 100, 100);

	GetDlgItem(IDOK)->MoveWindow(10, 230, 80, 20);
	GetDlgItem(IDCANCEL)->MoveWindow(10, 260, 80, 20);
	GetDlgItem(IDC_CHK_ALIGN_12)->MoveWindow(120, 10, 100, 20);
	GetDlgItem(IDC_PIC_ALIGN_12)->MoveWindow(120, 40, 100, 100);
	GetDlgItem(IDC_CHK_ALIGN_34)->MoveWindow(120, 150, 100, 20);
	GetDlgItem(IDC_PIC_ALIGN_34)->MoveWindow(120, 180, 100, 100);

	GetDlgItem(IDC_CHK_ALIGN_13)->MoveWindow(230, 10, 100, 20);
	GetDlgItem(IDC_PIC_ALIGN_13)->MoveWindow(230, 40, 100, 100);
	GetDlgItem(IDC_CHK_ALIGN_24)->MoveWindow(230, 150, 100, 20);
	GetDlgItem(IDC_PIC_ALIGN_24)->MoveWindow(230, 180, 100, 100);

	HFONT staticFont;
	staticFont = CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	GetDlgItem(IDC_CHK_ALIGN_ALL)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_CHK_ALIGN_12)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_CHK_ALIGN_34)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_CHK_ALIGN_13)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDC_CHK_ALIGN_24)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	
	GetDlgItem(IDOK)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);
	GetDlgItem(IDCANCEL)->SendMessage(WM_SETFONT, (WPARAM)staticFont, (LPARAM)TRUE);

	SelectMethod();

	SetWindowTheme(GetDlgItem(IDC_CHK_ALIGN_ALL)->GetSafeHwnd(), _T(""), _T(""));


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL SettingAlignMethod::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void SettingAlignMethod::SelectMethod()
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	m_chk_align_all.SetCheck(0);
	m_chk_align_12.SetCheck(0);
	m_chk_align_34.SetCheck(0);
	m_chk_align_13.SetCheck(0);
	m_chk_align_24.SetCheck(0);

	if (pDlg->nAlignMethod == 1)
		m_chk_align_all.SetCheck(1);

	else if (pDlg->nAlignMethod == 2)
		m_chk_align_12.SetCheck(1);

	else if (pDlg->nAlignMethod == 3)
		m_chk_align_34.SetCheck(1);

	else if (pDlg->nAlignMethod == 4)
		m_chk_align_13.SetCheck(1);

	else if (pDlg->nAlignMethod == 5)
		m_chk_align_24.SetCheck(1);

}

void SettingAlignMethod::OnBnClickedChkAlignAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_chk_align_all.SetCheck(1);
	m_chk_align_12.SetCheck(0);
	m_chk_align_34.SetCheck(0);
	m_chk_align_13.SetCheck(0);
	m_chk_align_24.SetCheck(0);

	nSelectedMethod = 1;
}


void SettingAlignMethod::OnBnClickedChkAlign12()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_chk_align_all.SetCheck(0);
	m_chk_align_12.SetCheck(1);
	m_chk_align_34.SetCheck(0);
	m_chk_align_13.SetCheck(0);
	m_chk_align_24.SetCheck(0);

	nSelectedMethod = 2;
}


void SettingAlignMethod::OnBnClickedChkAlign34()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_chk_align_all.SetCheck(0);
	m_chk_align_12.SetCheck(0);
	m_chk_align_34.SetCheck(1);
	m_chk_align_13.SetCheck(0);
	m_chk_align_24.SetCheck(0);

	nSelectedMethod = 3;
}


void SettingAlignMethod::OnBnClickedChkAlign13()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_chk_align_all.SetCheck(0);
	m_chk_align_12.SetCheck(0);
	m_chk_align_34.SetCheck(0);
	m_chk_align_13.SetCheck(1);
	m_chk_align_24.SetCheck(0);

	nSelectedMethod = 4;
}


void SettingAlignMethod::OnBnClickedChkAlign24()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_chk_align_all.SetCheck(0);
	m_chk_align_12.SetCheck(0);
	m_chk_align_34.SetCheck(0);
	m_chk_align_13.SetCheck(0);
	m_chk_align_24.SetCheck(1);

	nSelectedMethod = 5;
}

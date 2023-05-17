// PopupPreprocessImg.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "PopupPreprocessImg.h"
#include "afxdialogex.h"

#include "RVisionDlg.h"

// PopupPreprocessImg 대화 상자

IMPLEMENT_DYNAMIC(PopupPreprocessImg, CDialogEx)

PopupPreprocessImg::PopupPreprocessImg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POPUP_PREPROCESS_IMG, pParent)
{

}

PopupPreprocessImg::~PopupPreprocessImg()
{
}

void PopupPreprocessImg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PopupPreprocessImg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_EXIT, &PopupPreprocessImg::OnBnClickedBtnExit)
END_MESSAGE_MAP()


// PopupPreprocessImg 메시지 처리기


int PopupPreprocessImg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH PopupPreprocessImg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL PopupPreprocessImg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//MoveWindow(rcDialog);


	GetDlgItem(IDC_PIC_PREPROCESS_IMG)->MoveWindow(0, 0, 306, 256);
	GetDlgItem(IDC_BTN_EXIT)->MoveWindow(261, 260, 40, 20);

	CFont* btnFont;

	btnFont = new CFont;

	//폰트 생성
	btnFont->CreateFont(
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

	GetDlgItem(IDC_BTN_EXIT)->SetFont(btnFont);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL PopupPreprocessImg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void PopupPreprocessImg::OnBnClickedBtnExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	pDlg->DisplayPreprocessImg(0, false);
}

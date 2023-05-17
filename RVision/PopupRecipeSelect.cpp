// PopupRecipeSelect.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "PopupRecipeSelect.h"
#include "afxdialogex.h"

#include "RVisionDlg.h"
// PopupRecipeSelect 대화 상자

extern 	RecipeName stRecipe;

IMPLEMENT_DYNAMIC(PopupRecipeSelect, CDialogEx)

PopupRecipeSelect::PopupRecipeSelect(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POPUP_RECIPE_SELECT, pParent)
{

}

PopupRecipeSelect::~PopupRecipeSelect()
{
}

void PopupRecipeSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_RECIPE_SELECT, m_cmb_recipe_select);
}


BEGIN_MESSAGE_MAP(PopupRecipeSelect, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_CMB_RECIPE_SELECT, &PopupRecipeSelect::OnCbnSelchangeCmbRecipeSelect)
	ON_BN_CLICKED(IDOK, &PopupRecipeSelect::OnBnClickedOk)
END_MESSAGE_MAP()


// PopupRecipeSelect 메시지 처리기


int PopupRecipeSelect::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH PopupRecipeSelect::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL PopupRecipeSelect::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	MoveWindow(rcDialog);

	GetDlgItem(IDC_CMB_RECIPE_SELECT)->MoveWindow(10, 10, 230, 50);
	GetDlgItem(IDOK)->MoveWindow(250, 10, 60, 30);
	GetDlgItem(IDCANCEL)->MoveWindow(250, 50, 60, 30);

	ComboListRenew();
	m_cmb_recipe_select.SetCurSel(nSelectNum - 1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL PopupRecipeSelect::PreTranslateMessage(MSG* pMsg)
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


void PopupRecipeSelect::OnCbnSelchangeCmbRecipeSelect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	int nCase = m_cmb_recipe_select.GetCurSel();

	if (stRecipe.bChkEmpty[nCase] == false)
		GetDlgItem(IDOK)->EnableWindow(false);

	else if (stRecipe.bChkEmpty[nCase] == true)
		GetDlgItem(IDOK)->EnableWindow(true);

	nSelectNum = stRecipe.nNum[nCase];
}



void PopupRecipeSelect::ComboListRenew()
{
	CString strList;
	CString strName;
	CString strDisplay;

	for (int i = 0; i < 100; i++)
	{
		//if (pDlg->pRecipeName[i].bChkEmpty == true)
		//{
			strList.Format(_T("#%d"), i + 1);
			stRecipe.nNum[i] = i + 1;
			strName = stRecipe.strRecipeName[i];
			strDisplay = strList + _T("   ") + strName;

			m_cmb_recipe_select.AddString(strDisplay);
		//}
	}
}

void PopupRecipeSelect::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	pDlg->nSelectRecipe = nSelectNum;

	CDialogEx::OnOK();
}

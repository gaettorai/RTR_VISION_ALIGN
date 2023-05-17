// PopupRecipeAdd.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "PopupRecipeAdd.h"
#include "afxdialogex.h"

#include "RVisionDlg.h"

// PopupRecipeAdd 대화 상자

IMPLEMENT_DYNAMIC(PopupRecipeAdd, CDialogEx)

extern RecipeName stRecipe;

PopupRecipeAdd::PopupRecipeAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POPUP_RECIPE_ADD, pParent)
{

}

PopupRecipeAdd::~PopupRecipeAdd()
{
}

void PopupRecipeAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_RECIPE_ADD, m_cmb_recipe_add);
}


BEGIN_MESSAGE_MAP(PopupRecipeAdd, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &PopupRecipeAdd::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_CMB_RECIPE_ADD, &PopupRecipeAdd::OnCbnSelchangeCmbRecipeAdd)
END_MESSAGE_MAP()


// PopupRecipeAdd 메시지 처리기


int PopupRecipeAdd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


HBRUSH PopupRecipeAdd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL PopupRecipeAdd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	MoveWindow(rcDialog);

	GetDlgItem(IDC_CMB_RECIPE_ADD)->MoveWindow(10, 10, 230, 50);
	GetDlgItem(IDOK)->MoveWindow(250, 10, 60, 30);
	GetDlgItem(IDCANCEL)->MoveWindow(250, 50, 60, 30);

	nSelectNum = 1;
	ComboListRenew();
	m_cmb_recipe_add.SetCurSel(nSelectNum - 1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL PopupRecipeAdd::PreTranslateMessage(MSG* pMsg)
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


void PopupRecipeAdd::ComboListRenew()
{
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	CString strList;
	CString strName;
	CString strDisplay;
	

	for (int i = 0; i < 100; i++)
	{
		//if (pDlg->pRecipeName[i].bChkEmpty == false)
		//{
			strList.Format(_T("#%d"), i + 1);
			stRecipe.nNum[i] = i + 1;
			strName = stRecipe.strRecipeName[i];
			strDisplay = strList + _T("   ") + strName;

			m_cmb_recipe_add.AddString(strDisplay);
		//}
	}
}


void PopupRecipeAdd::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	pDlg->nCopyRecipe = nSelectNum;
	CDialogEx::OnOK();
}


void PopupRecipeAdd::OnCbnSelchangeCmbRecipeAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRVisionDlg* pDlg = (CRVisionDlg*)AfxGetMainWnd();

	int nCase;
	CString strRecipeName;

	nCase = m_cmb_recipe_add.GetCurSel();

	nSelectNum = stRecipe.nNum[nCase];
	
	pDlg->dlgVisionSetting->dlgSettingCamera->m_edit_recipe_name.GetWindowTextW(strRecipeName);
	stRecipe.strRecipeName[nCase] = strRecipeName;
}

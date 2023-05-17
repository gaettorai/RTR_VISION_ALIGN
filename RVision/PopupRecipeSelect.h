#pragma once


// PopupRecipeSelect 대화 상자
class PopupRecipeSelect : public CDialogEx
{
	DECLARE_DYNAMIC(PopupRecipeSelect)

public:
	PopupRecipeSelect(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~PopupRecipeSelect();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POPUP_RECIPE_SELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_cmb_recipe_select;

	CRect rcDialog;
	CString filePath;

	afx_msg void OnCbnSelchangeCmbRecipeSelect();
	void ComboListRenew();

	afx_msg void OnBnClickedOk();

	int nSelectNum;

};
#pragma once


// SettingFC 대화 상자

class SettingFC : public CDialogEx
{
	DECLARE_DYNAMIC(SettingFC)

public:
	SettingFC(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SettingFC();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_FC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void DisplayParam();
	void EditEnable(bool nCase);

	CEdit m_edit_matchrate;
	CEdit m_edit_repeat;
	CEdit m_edit_fc_roi_start_x;
	CEdit m_edit_fc_roi_start_y;
	CEdit m_edit_fc_roi_end_x;
	CEdit m_edit_fc_roi_end_y;
	CEdit m_edit_binary_low;
	CEdit m_edit_binary_high;
	afx_msg void OnBnClickedBtnModify();
	afx_msg void OnBnClickedBtnApply();
	afx_msg void OnBnClickedBtnCancel();

	BOOL ChkModify;
	afx_msg void OnBnClickedBtnFcmarkEnroll();
	afx_msg void OnBnClickedBtnFcmarkApply();
	afx_msg void OnBnClickedBtnFcmarkCancel();

	BOOL bChkMarkFC;

	CRect rectMark;
	CRectTracker mMarkTracker;

	CEdit m_edit_recipe_select;
	afx_msg void OnBnClickedBtnRecipeLoad();
	afx_msg void OnBnClickedBtnAdd();
	CEdit m_edit_recipe_name;

	CFont* btnFont;
	afx_msg void OnBnClickedBtnFcmarkUp();
	afx_msg void OnBnClickedBtnFcmarkDown();
	afx_msg void OnBnClickedBtnFcmarkLeft();
	afx_msg void OnBnClickedBtnFcmarkRight();
	CEdit m_edit_fc_open;
	CEdit m_edit_fc_close;
	CEdit m_edit_fcmark_binary_low;
	CEdit m_edit_fcmark_open;
	CEdit m_edit_fcmark_close;

	int nFCMarkThread;
	int nFCMarkOpen;
	int nFCMarkClose;

	afx_msg void OnBnClickedBtnPreprocessShow2();
	afx_msg void OnBnClickedBtnPreprocessApply();
	afx_msg void OnBnClickedBtnFcmarkPreprocessApply();
	afx_msg void OnBnClickedBtnFcmarkPreprocessCancel();
};

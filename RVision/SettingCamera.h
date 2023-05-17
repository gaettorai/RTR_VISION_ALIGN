#pragma once


// SettingCamera 대화 상자

class SettingCamera : public CDialogEx
{
	DECLARE_DYNAMIC(SettingCamera)

public:
	SettingCamera(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SettingCamera();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_CAMERA };
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

	int SelectCam;

	afx_msg void OnBnClickedChkName();
	afx_msg void OnBnClickedChkCrossline();
	afx_msg void OnBnClickedBtnApply();
	afx_msg void OnBnClickedBtnCancel();

	CEdit m_edit_light_align1;
	CEdit m_edit_light_align2;
	CEdit m_edit_light_align3;
	CEdit m_edit_light_align4;
	CEdit m_edit_light_review;

	int nLight1;
	int nLight2;
	int nLight3;
	int nLight4;
	int nLight5;

	CButton m_chk_name;
	CButton m_chk_crossline;

	CMFCColorButton m_color_name;
	CMFCColorButton m_color_crossline;

	afx_msg void OnBnClickedBtnModify();

	BOOL ChkModify;

	void EditEnable(bool nCase);
	CButton m_chk_roi;
	CMFCColorButton m_color_roi;
	afx_msg void OnBnClickedChkRoi();

	void DisplayParam();
	afx_msg void OnEnChangeEditLightAlign1();
	afx_msg void OnEnChangeEditLightAlign2();
	afx_msg void OnEnChangeEditLightAlign3();
	afx_msg void OnEnChangeEditLightAlign4();
	afx_msg void OnEnChangeEditLightReview();
	CComboBox m_cmb_selectcam;
	afx_msg void OnCbnSelchangeCmbSelectcam();
	CSliderCtrl m_slider_light_1;
	CEdit m_edit_recipe_select;
	afx_msg void OnBnClickedBtnRecipeLoad();
	afx_msg void OnBnClickedBtnAdd();
	CSliderCtrl m_slider_light_2;
	CSliderCtrl m_slider_light_3;
	CSliderCtrl m_slider_light_4;
	CSliderCtrl m_slider_light_5;
	CEdit m_edit_recipe_name;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CEdit m_edit_x_offset;
	CEdit m_edit_y_offset;

	CFont* btnFont;
};
#pragma once


// SettingAlignMark 대화 상자

class SettingAlignMark : public CDialogEx
{
	DECLARE_DYNAMIC(SettingAlignMark)

public:
	SettingAlignMark(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SettingAlignMark();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_ALIGNMARK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_cmb_selectcam;

	CFont* btnFont;
	void EditEnable(bool nCase);
	afx_msg void OnBnClickedBtnRecipeLoad();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnModify();
	afx_msg void OnBnClickedBtnApply();
	afx_msg void OnBnClickedBtnCancel();
	afx_msg void OnBnClickedBtnMarkReg();
	afx_msg void OnBnClickedBtnMarkApply();
	afx_msg void OnBnClickedBtnMarkCancel();
	afx_msg void OnBnClickedBtnMarkUp();
	afx_msg void OnBnClickedBtnMarkDown();
	afx_msg void OnBnClickedBtnMarkLeft();
	afx_msg void OnBnClickedBtnMarkRight();
	afx_msg void OnBnClickedBtnPreprocessApply();
	afx_msg void OnBnClickedBtnPreprocessCancel();
	afx_msg void OnBnClickedBtnMarkMeasure();

	int SelectCam;

	BOOL bChkMarkAlign;

	CRect rectMark;
	CRectTracker mMarkTracker;
	CEdit m_edit_recipe_select;
	CEdit m_edit_recipe_name;
	CEdit m_edit_mark_matchrate;
	CEdit m_edit_mark_thread;
	CEdit m_edit_mark_open;
	CEdit m_edit_mark_close;

	void DisplayParam();
	afx_msg void OnCbnSelchangeCmbSelectcam();

	int nMarkThread;
	int nMarkOpen;
	int nMarkClose;

};

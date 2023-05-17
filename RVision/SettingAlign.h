#pragma once

#include "SettingAlignMethod.h"
// SettingAlign 대화 상자

class SettingAlign : public CDialogEx
{
	DECLARE_DYNAMIC(SettingAlign)

public:
	SettingAlign(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SettingAlign();
	SettingAlignMethod	dlgSettingAlign;


	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_ALIGN };
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

	void DisplayParam(int nCase);
	void DisplayAlign(bool nCase);
	void DisplaySetting(bool nCase);

	afx_msg void OnBnClickedBtnApply();
	afx_msg void OnBnClickedBtnCancel();
	afx_msg void OnBnClickedBtnModify();

	afx_msg void OnCbnSelchangeCmbSelectcam();
	afx_msg void OnBnClickedBtnEdge();
	afx_msg void OnBnClickedBtnMark();

	afx_msg void OnEnChangeEditEdgeRoiStartX();
	afx_msg void OnEnChangeEditEdgeRoiStartY();
	afx_msg void OnEnChangeEditEdgeRoiEndX();
	afx_msg void OnEnChangeEditEdgeRoiEndY();

	afx_msg void OnBnClickedBtnRecipeLoad();
	afx_msg void OnBnClickedBtnAdd();

	afx_msg void OnBnClickedBtnPreprocessApply();

	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	void EditEnable(bool nCase);

	int SelectCam;

	BOOL ChkModify;

	// parameter
	// 검사 영역
	CEdit m_edit_edge_roi_start_x;
	CEdit m_edit_edge_roi_start_y;
	CEdit m_edit_edge_roi_end_x;
	CEdit m_edit_edge_roi_end_y;

	// 전처리 관련
	CEdit m_edit_binary_low;
	CEdit m_edit_open;
	CEdit m_edit_close;

	// 후처리 관련
	CEdit m_edit_xoffset;
	CEdit m_edit_yoffset;



	CComboBox m_cmb_selectcam;
	CMFCButton m_btn_edge;
	CMFCButton m_btn_mark;

	CEdit m_edit_recipe_name;

	CRect rectRoi;
	CRectTracker mRoiTracker;

	//CRect rectMark;
	//CRectTracker mMarkTracker;

	CEdit m_edit_x_range;
	CEdit m_edit_y_range;
	CEdit m_edit_t_range;
	CEdit m_edit_recipe_select;

	BOOL bChkMarkAlign;

	CFont* btnFont;

	CMFCButton m_btn_preprocess_apply;
	afx_msg void OnBnClickedBtnPreprocessShow();
	CMFCButton m_btn_preprocess_show;
	CStatic m_pic_mark_pos;
	CEdit m_edit_align_width;
	CEdit m_edit_align_height;
	CEdit m_edit_level_range;
	CEdit m_edit_mistake_range;
	CEdit m_edit_toffset;
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnAlignMethod();
	CMFCButton m_btn_align_method;
	CMFCButton m_btn_offset;
};

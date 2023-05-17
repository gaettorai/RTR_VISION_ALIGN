#pragma once

#include "SettingCamera.h"
#include "SettingAlign.h"
#include "SettingAlignMark.h"
#include "SettingFC.h"
#include "SettingLaser.h"
// RVisionSetting 대화 상자

class RVisionSetting : public CDialogEx
{
	DECLARE_DYNAMIC(RVisionSetting)

public:
	RVisionSetting(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~RVisionSetting();
	SettingCamera* dlgSettingCamera;
	SettingAlign* dlgSettingAlign;
	SettingAlignMark* dlgSettingAlignMark;
	SettingFC* dlgSettingFC;
	SettingLaser* dlgSettingLaser;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RVISION_SETTING };
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
	afx_msg void OnBnClickedBtnCamera();
	afx_msg void OnBnClickedBtnAlign();

	CMFCButton m_btn_camera;
	CMFCButton m_btn_align;

	int SelectSetting;
	afx_msg void OnBnClickedBtnFc();
	CMFCButton m_btn_fc;

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	CMFCButton m_btn_alignmark;
	CMFCButton m_btn_laser;
	afx_msg void OnBnClickedBtnAlignmark();
	afx_msg void OnBnClickedBtnLaser();
};

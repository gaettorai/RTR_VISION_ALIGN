#pragma once
#include "SettingHide.h"



// SettingLaser 대화 상자

#define _USE_MATH_DEFINES
#include <math.h>

class SettingLaser : public CDialogEx
{
	DECLARE_DYNAMIC(SettingLaser)

public:
	SettingLaser(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SettingLaser();

	SettingHide dlgSettingHide;


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_LASER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();

	CFont* btnFont;

	CPen pen_white;
	CPen pen_red;

	afx_msg void OnBnClickedBtnCalculation();
	CEdit m_edit_laser_speed;
	CEdit m_edit_laser_hz;
	CEdit m_edit_laser_size;
	CEdit m_edit_laser_power;


	CString strValue;
	
	double dScanSpeed;
	double dHz;
	double dSpotSize;
	double dLaserPower;
	double dDFocus;

	double dPTP;
	double dOverlapRate;
	double dEnergy;
	double dSpotError;

	afx_msg void OnBnClickedBtnClear();

	CRect rectMark;
	CRectTracker mMarkTracker;

	BOOL bChkMarkLaser;

	afx_msg void OnBnClickedBtnLasermarkEnroll();
	afx_msg void OnBnClickedBtnLasermarkApply();
	afx_msg void OnBnClickedBtnLasermarkCancel();
	afx_msg void OnBnClickedBtnLasermarkUp();
	afx_msg void OnBnClickedBtnLasermarkDown();
	afx_msg void OnBnClickedBtnLasermarkLeft();
	afx_msg void OnBnClickedBtnLasermarkRight();
	afx_msg void OnBnClickedBtnLasermarkMeasure();
	CEdit m_edit_dfocus;
	afx_msg void OnBnClickedBtnLasermarkClear();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	BOOL bChkAlarm;
	CMFCButton m_btn_offset;
	afx_msg void OnBnClickedBtnOffset();
};

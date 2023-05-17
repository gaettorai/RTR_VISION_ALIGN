#pragma once

#include "DrawFC.h"

// RVisionFC 대화 상자

class RVisionFC : public CDialogEx
{
	DECLARE_DYNAMIC(RVisionFC)

public:
	RVisionFC(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~RVisionFC();
	DrawFC* dlgDrawFC;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RVISION_FC };
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
	CListCtrl m_list_fc;
	CEdit m_edit_gain;
	CEdit m_edit_newcal;
	CEdit m_edit_point_x;
	CEdit m_edit_point_y;
	CEdit m_edit_length_x;
	CEdit m_edit_length_y;
	CEdit m_edit_oldctfile;
	CEdit m_edit_newctfile;

	int nFCLogCount;
	afx_msg void OnBnClickedBtnOldctfile();
	afx_msg void OnBnClickedBtnNewctfile();

	BOOL bChkNewctfile;
	afx_msg void OnBnClickedBtnMeasurement();

	CFont* btnFont;
};

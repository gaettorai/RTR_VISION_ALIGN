#pragma once

#include "DrawReview.h"

// RVisionReview 대화 상자

class RVisionReview : public CDialogEx
{
	DECLARE_DYNAMIC(RVisionReview)

public:
	RVisionReview(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~RVisionReview();
	DrawReview* dlgDrawReview;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RVISION_REVIEW };
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

	CBitmap	m_bmp_graphic_on;
	CBitmap	m_bmp_graphic_off;
	CBitmap m_bmp_line_on;
	CBitmap m_bmp_line_off;
	CBitmap m_bmp_rectangle_on;
	CBitmap m_bmp_rectangle_off;
	CBitmap m_bmp_angle_on;
	CBitmap m_bmp_angle_off;
	CBitmap m_bmp_circle_on;
	CBitmap m_bmp_circle_off;
	CBitmap m_bmp_centerdist_on;
	CBitmap m_bmp_centerdist_off;
	CBitmap m_bmp_clear;
	CBitmap m_bmp_zoomin;
	CBitmap m_bmp_zoomout;
	
	CButton m_btn_mode;
	CButton m_btn_line;
	CButton m_btn_rectangle;
	CButton m_btn_angle;
	CButton m_btn_clear;
	CButton m_btn_clearall;
	CButton m_btn_zoomin;
	CButton m_btn_zoomout;
	CListCtrl m_list_measurement;

	void SelectGraphic(int nCase);
	afx_msg void OnBnClickedBtnMode();
	afx_msg void OnBnClickedBtnLine();
	afx_msg void OnBnClickedBtnRectangle();
	afx_msg void OnBnClickedBtnAngle();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnZoomin();
	afx_msg void OnBnClickedBtnZoomout();
	afx_msg void OnBnClickedBtnCapture();
	afx_msg void OnBnClickedBtnClearall();
	CButton m_btn_circle;
	afx_msg void OnBnClickedBtnCircle();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	int clickCount;
	int x_point;
	int y_point;

	int m_nHdelta;
	int m_nVdelta;
	CButton m_chk_scale;
	afx_msg void OnBnClickedBtnCenterDist();
	CButton m_btn_center_dist;
	CButton m_chk_all;
	afx_msg void OnBnClickedChkAll();
	afx_msg void OnColumnclickListMeasurement(NMHDR* pNMHDR, LRESULT* pResult);
};

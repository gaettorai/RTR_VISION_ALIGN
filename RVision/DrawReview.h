#pragma once

#include "DrawScaleH.h"

// DrawReview 대화 상자

class DrawReview : public CDialogEx
{
	DECLARE_DYNAMIC(DrawReview)

public:
	DrawReview(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DrawReview();
	DrawScaleH* dlgDrawScaleH;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAW_REVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CStatic m_pic_review;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	int ViewWidth_;
	int ViewHeight_;
	int HScrollPos_;
	int VScrollPos_;
	int HPageSize_;
	int VPageSize_;
	int delta;
	int m_nHdelta;

	int scrollpos;

	int magni;

	int mouse_scroll_x;
	int mouse_scroll_y;

	int x_start;
	int y_start;
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	void LineMeasure(int nCase, CPoint FirstPoint, CPoint SecondPoint);
	void RectangleMeasure(int nCase, CPoint FirstPoint, CPoint SecondPoint);
	void AngleMeasure(int nCase, CPoint FirstPoint, CPoint SecondPoint, CPoint ThirdPoint);
	void CircleMeasure(int nCase, CPoint FirstPoint, CPoint SecondPoint);
	void CenterDistMeasure(int nCase, CPoint FirstPoint);
	void MouseClick(CPoint clickPoint);
};

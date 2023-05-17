#pragma once


// DrawSetting 대화 상자

class DrawSetting : public CDialogEx
{
	DECLARE_DYNAMIC(DrawSetting)

public:
	DrawSetting(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DrawSetting();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAW_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CStatic m_pic_setting;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);


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

	CRect rectMark;
	CRectTracker mMarkTracker;

	BOOL CHK_MARK_ALIGN;
	BOOL CHK_MARK_FC;

	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

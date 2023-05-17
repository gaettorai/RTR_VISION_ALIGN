#pragma once


// DrawManualAlign 대화 상자

class DrawManualAlign : public CDialogEx
{
	DECLARE_DYNAMIC(DrawManualAlign)

public:
	DrawManualAlign(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DrawManualAlign();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAW_MANUALALIGN };
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
	CStatic m_pic_manualalign;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
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

	int nClickCount;
};

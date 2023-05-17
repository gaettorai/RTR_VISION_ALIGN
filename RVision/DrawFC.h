#pragma once


// DrawFC 대화 상자

class DrawFC : public CDialogEx
{
	DECLARE_DYNAMIC(DrawFC)

public:
	DrawFC(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DrawFC();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAW_FC };
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
	CStatic m_pic_fc;
};

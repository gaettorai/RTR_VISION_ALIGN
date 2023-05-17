#pragma once\

#include "DrawAlign.h"

// RVisionAlign 대화 상자

class RVisionAlign : public CDialogEx
{
	DECLARE_DYNAMIC(RVisionAlign)

public:
	RVisionAlign(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~RVisionAlign();
	DrawAlign* dlgDrawAlign;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RVISION_ALIGN };
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

	BOOL bChkJudge;
	BOOL bChkModifyX;
	BOOL bChkModifyY;
	BOOL bChkModifyT;
	BOOL bChkLevel;
	BOOL bChkMistake;
	BOOL bChkMatchrate1;
	BOOL bChkMatchrate2;
	BOOL bChkMatchrate3;
	BOOL bChkMatchrate4;


	void DisplayMark(bool nCase);
	void DisplayEdge(bool nCase);
	CStatic m_icon_alignstart;
	CStatic m_icon_alignrun;
	CStatic m_icon_alignend;

	CBitmap m_bmp_ledoff;
	CBitmap m_bmp_ledon;
	CStatic m_icon_heartbeat;
	CStatic m_icon_cam1;
	CStatic m_icon_cam2;
	CStatic m_icon_cam3;
	CStatic m_icon_cam4;
	CStatic m_icon_cam5;
	afx_msg void OnStnClickedIconReconnect();
};

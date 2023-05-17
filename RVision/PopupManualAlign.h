#pragma once

#include "DrawManualAlign.h"

// PopupManualAlign 대화 상자

class PopupManualAlign : public CDialogEx
{
	DECLARE_DYNAMIC(PopupManualAlign)

public:
	PopupManualAlign(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~PopupManualAlign();
	DrawManualAlign* dlgDrawManualAlign;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POPUP_MANUALALIGN };
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

	CRect rcDialog;
	
	int nCase;	// 0 : edge, 1: mark

	CComboBox m_cmb_selectcam;
	afx_msg void OnBnClickedBtnManualalign();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CStatic m_grp_point;
	CStatic m_grp_modify;

	BOOL ChkActive;
	
	CMFCButton m_btn_apply;
	CMFCButton m_btn_cancel;

	BOOL ChkClick;
	afx_msg void OnBnClickedBtnApply();
	afx_msg void OnBnClickedBtnCancel();

	CPoint AlignResult1;
	CPoint AlignResult2;
	CPoint AlignResult3;
	CPoint AlignResult4;

	// ALIGN 오차 값
	double dModifyX;
	double dModifyY;
	double dModifyT;

	// ALIGN 최종 값
	double dModifyX_result;
	double dModifyY_result;
	double dModifyT_result;

	// 카메라 센터와 laser 센터와의 오차 
	double dXOffset;
	double dYOffset;

	int SelectCam;
	int nClickCount;

	CPoint ManualFirstPoint;
	CPoint ManualSecondPoint;
	CPoint ManualMarkPoint;

	void DisplayWindow();
	void DisplayAlignPoint();
	void CalcurationAlign(int nCase);
	CMFCButton m_btn_align1;
	CMFCButton m_btn_align2;
	CMFCButton m_btn_align3;
	CMFCButton m_btn_align4;
	CStatic m_pic_manualalign;
	afx_msg void OnBnClickedBtnAlign1();
	afx_msg void OnBnClickedBtnAlign2();
	afx_msg void OnBnClickedBtnAlign3();
	afx_msg void OnBnClickedBtnAlign4();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);


	BOOL ChkNG_X;
	BOOL ChkNG_Y;
	BOOL ChkNG_T;
	BOOL ChkNG_LEVEL;

	void CalcurationResult();
	void DisplayJudge();
	afx_msg void OnBnClickedBtnUp();
	afx_msg void OnBnClickedBtnDown();
	afx_msg void OnBnClickedBtnLeft();
	afx_msg void OnBnClickedBtnRight();
};

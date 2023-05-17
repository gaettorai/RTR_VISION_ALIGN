#pragma once
#include "afxdialogex.h"


// SettingAlignMethod 대화 상자

class SettingAlignMethod : public CDialogEx
{
	DECLARE_DYNAMIC(SettingAlignMethod)

public:
	SettingAlignMethod(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SettingAlignMethod();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_ALIGN_METHOD };
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

	void SelectMethod();
	CButton m_chk_align_all;
	CButton m_chk_align_12;
	CButton m_chk_align_34;
	CButton m_chk_align_13;
	CButton m_chk_align_24;
	afx_msg void OnBnClickedChkAlignAll();
	afx_msg void OnBnClickedChkAlign12();
	afx_msg void OnBnClickedChkAlign34();
	afx_msg void OnBnClickedChkAlign13();
	afx_msg void OnBnClickedChkAlign24();

	int nSelectedMethod;
};

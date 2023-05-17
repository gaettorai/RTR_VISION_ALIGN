#pragma once


// SettingNumpad 대화 상자

class SettingNumpad : public CDialogEx
{
	DECLARE_DYNAMIC(SettingNumpad)

public:
	SettingNumpad(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SettingNumpad();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_NUMPAD };
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
};

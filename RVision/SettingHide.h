#pragma once


// SettingHide 대화 상자

class SettingHide : public CDialogEx
{
	DECLARE_DYNAMIC(SettingHide)

public:
	SettingHide(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SettingHide();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_HIDE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

	CRect rcDialog;

	double dModifyX;
	double dModifyY;
	double dModifyT;

	void DisplayParam();
	CEdit m_edit_hide1;
	CEdit m_edit_hide2;
	CEdit m_edit_hide3;
	CEdit m_edit_hide4;
	CEdit m_edit_hide5;
	afx_msg void OnBnClickedOk();

	CFont* staticFont;

};

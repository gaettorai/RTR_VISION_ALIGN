#pragma once


// PopupAlarm 대화 상자

class PopupAlarm : public CDialogEx
{
	DECLARE_DYNAMIC(PopupAlarm)

public:
	PopupAlarm(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~PopupAlarm();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POPUP_ALARM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CRect rcDialog;
	void EndWindodw();

	CString strMessage;
	void DisplayMessage(CString strMessage);
};

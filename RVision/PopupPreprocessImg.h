#pragma once


// PopupPreprocessImg 대화 상자

class PopupPreprocessImg : public CDialogEx
{
	DECLARE_DYNAMIC(PopupPreprocessImg)

public:
	PopupPreprocessImg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~PopupPreprocessImg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POPUP_PREPROCESS_IMG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CRect rcDialog;

	afx_msg void OnBnClickedBtnExit();
};


// RVisionDlg.h: 헤더 파일
//

#include "connect_Baumer.h"

#include "RVisionAlign.h"
#include "RVisionReview.h"
#include "RVisionFC.h"
#include "RVisionSetting.h"

#include "PopupManualAlign.h"
#include "PopupRecipeSelect.h"
#include "PopupRecipeAdd.h"
#include "PopupAlarm.h"
#include "PopupPreprocessImg.h"

#include "CommThread.h"

#include <cmath>

#include <atltime.h>
#include <time.h>

#pragma once

void BGAPI2CALL BufferHandler1(void* callBackOwner, Buffer* pBufferFilled);
void BGAPI2CALL BufferHandler2(void* callBackOwner, Buffer* pBufferFilled);
void BGAPI2CALL BufferHandler3(void* callBackOwner, Buffer* pBufferFilled);
void BGAPI2CALL BufferHandler4(void* callBackOwner, Buffer* pBufferFilled);
void BGAPI2CALL BufferHandler5(void* callBackOwner, Buffer* pBufferFilled);

union WORD_DATA
{
	unsigned short int   nValue;
	short   int       Value;
	struct _Ch {
		unsigned char low;
		unsigned char high;
	} Ch;
	struct BIT {        // Bit Field Structure
		unsigned b0 : 1;
		unsigned b1 : 1;
		unsigned b2 : 1;
		unsigned b3 : 1;
		unsigned b4 : 1;
		unsigned b5 : 1;
		unsigned b6 : 1;
		unsigned b7 : 1;
	} bit;
	void init() {
		ZeroMemory(this, sizeof(*this));
	}
	WORD_DATA() {
		init();
	}
	bool getBit(int nIdx) {
		return ((nValue >> nIdx) & 0x0001);
	}
	void setBit(int nBitIdx, bool bOn) {
		if (bOn)
			nValue = nValue | (0x01 << nBitIdx);
		else
			nValue = nValue & ~(0x01 << nBitIdx);
	}
};

typedef struct _R2RCommData
{
	int nVisionMode;
	int nVisionReply;
	int nAlignRun;

	int nJig;

	double dXModify;
	double dYModify;
	double dTModify;

	// autosizing 추가 관련 변수
	double dScaleX;
	double dScaleY;

	int nResult;
	int nAlignMethod;

	double dLGentryPos;
	double dRGentryPos;

	double dCam1Pos;
	double dCam2Pos;
	double dCam3Pos;
	double dCam4Pos;

	int nFCRun;
	int nFCShot;

	double dGain;
	double dNewcal;
	int nPatternPoint;
	double dPatternLength;

	int nLCRun;  

	bool bServerReceive;
	bool bClientReceive;

	WORD_DATA wdVisionErrorData;

	int nVisionRecipe;

	double dWidth;
	double dHeight;

	_R2RCommData()
	{
		nVisionMode = -1;
		nVisionReply = -1;
		nAlignRun = 0;

		nJig = 0;

		dXModify = 0.0;
		dYModify = 0.0;
		dTModify = 0.0;

		dScaleX = 0.0;
		dScaleY = 0.0;

		nResult = 0;
		nAlignMethod = -1;

		dLGentryPos = 0.0;
		dRGentryPos = 0.0;
		dCam1Pos = 0.0;
		dCam2Pos = 0.0;
		dCam3Pos = 0.0;
		dCam4Pos = 0.0;

		nFCRun = 0;
		nFCShot = 0;

		dGain = 0.0;
		dNewcal = 0.0;
		nPatternPoint = 0;
		dPatternLength = 0.0;

		nLCRun = -1;

		bServerReceive = false;
		bClientReceive = false;

		nVisionRecipe = 0;

		dWidth = 0.0;
		dHeight = 0.0;
	}

}R2RCommData;



// CRVisionDlg 대화 상자
class FCResult;
class FolderInfo;
class CRVisionDlg : public CDialogEx
{
// 생성입니다.
public:
	CRVisionDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	
	connect_Baumer*	cBaumer;
	RVisionAlign* dlgVisionAlign;
	RVisionReview* dlgVisionReview;
	RVisionFC* dlgVisionFC;
	RVisionSetting* dlgVisionSetting;
	PopupManualAlign dlgPopupManualAlign;
	PopupRecipeSelect dlgPopupRecipeSelect;
	PopupRecipeAdd	dlgPopupRecipeAdd;
	PopupAlarm*	dlgPopupAlarm;
	PopupPreprocessImg* dlgPopupPreprocessImg;

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RVISION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnModeAlign();
	afx_msg void OnBnClickedBtnModeReview();
	afx_msg void OnBnClickedBtnModeFc();
	afx_msg void OnBnClickedBtnModeSetting();
	afx_msg void OnStnClickedIconLogin();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	CStatic m_icon_login;
	
	CMFCButton m_btn_mode_align;
	CMFCButton m_btn_mode_review;
	CMFCButton m_btn_mode_fc;
	CMFCButton m_btn_mode_setting;

	CCommThread* m_comm;
	CCommThread	mLightPort;

	int m_iSerialPort;
	int m_iBaudRate;
	int m_iDataBit;
	int m_iStopBit;
	int m_iParity;

	CString strExeFilePath;
	CString strRecipeFilePath;
	CString strAlignmentPath;
	CString strDayPath;

	void SelectRecipe(int nCase);

	int nSelectRecipe;
	int nCopyRecipe;

	// 초기화
	void InitClass();
	void SettingUI();
	void InitDialog();
	void ConnectCamera();
	void InitSocket();
	void SettingParam();

	bool bChkCamera;
	bool bChkAlarm;

	void PathSize();
	void ChkFolder(CString strPath);
	void DeleteFolder(CString strPath);
	void DeleteImage(CString strPath);

	// light controller
	void SetCSR(int nCase);	// LIGHT CHANNEL
	void SetSVR(int nCase);	// LIGHT VALUE

	// recipe
	void SaveRecipe(int nCase);
	void LoadRecipe(int nCase);

	// 이미지 저장 및 align
	void ImageSave(int camNum, bool nCase);	// 원본 이미지 저장, nCase : 1(alignment)
	void MarkExtraction(int camNum);	// mark 추출
	BOOL EdgeFind(int camNum);	// edge 검출	// 0 : auto , 1 : manual
	BOOL MarkFind(int camNum, int nCase);	// case : 0 (auto), 1 : manual

	void ManualAlignDisplay();

	// process 실행(windowproc)
	void ExcutionDialog(int nCase);
	void ExcutionManualAlign();
	void ExcutionFC(int nCase);	// 0 : auto, 1 : manual
	void ExcutionLaserCalibration();
	void AlignResultFile();
	void FCFileSave();

	void ServerReturn(int nCase);

	CString byIndexComPort(int xPort);// 포트이름 받기 
	DWORD byIndexBaud(int xBaud);// 전송률 받기
	BYTE byIndexData(int xData);//데이터 비트 받기
	BYTE byIndexStop(int xStop);// 스톱비트 받기 
	BYTE byIndexParity(int xParity);// 펠리티 받기

	double dLGentryPos;
	double dRGentryPos;

	double dCam1Pos;
	double dCam2Pos;
	double dCam3Pos;
	double dCam4Pos;

	double dLGentryStdPos;
	double dRGentryStdPos;

	double dCam1StdPos;
	double dCam2StdPos;
	double dCam3StdPos;
	double dCam4StdPos;

	BOOL bChkAlignProc;
	BOOL bChkEdge;
	BOOL bChkMark;
	int nAlignMethod;
	int nSelecteAlignMethod;


	double dErrorLGentry;
	double dErrorRGentry;

	double dErrorCam1;
	double dErrorCam2;
	double dErrorCam3;
	double dErrorCam4;

	double dErrorX;
	double dErrorY;

	double dXPosition_1;
	double dXPosition_2;
	double dXPosition_3;
	double dXPosition_4;

	double dYPosition_1;
	double dYPosition_2;
	double dYPosition_3;
	double dYPosition_4;

	double dT12;
	double dT34;
	double dT13;
	double dT24;

	double dPostX;
	double dPostY;
	double dPostT;

	double dAlignMatchrate;
	double dRangeHLevel;
	double dRangeMistake;

	double dRangeX;
	double dRangeY;
	double dRangeT;

	double dAlignWidth;
	double dAlignHeight;

	double dLCOffsetX;
	double dLCOffsetY;

	double dManualOffsetX;
	double dManualOffsetY;
	double dManualOffsetT;

	double dAlignOffsetX;
	double dAlignOffsetY;
	double dAlignOffsetT;

	bool bJigProcess;

	int resizeMagni;

	void AlignCalcuration();

	int nRecRed;
	int nRecGreen;
	int nRecBlue;

	Mat loadImage;
	Mat MarkImageAlign;
	Mat MarkImageFC;
	Mat MarkImageLaser;

	Mat FCImage;
	Mat DetectResult;
	Mat FCImage_resize;
	Mat MarkImageFC_resize;

	Mat LaserImage_resize;
	Mat MarkImageLaser_resize;

	static UINT Vision_Thread(LPVOID pParam);
	CWinThread* Vision = NULL;

	static UINT Volume_Thread(LPVOID pParam);
	CWinThread* Volume = NULL;

	static UINT Proc_Thread(LPVOID pParam);
	CWinThread* Proc = NULL;


	// log 사용 시간
	CTime tRealTime;

	// align 측정 시간 
	CTime tAlignStartTime;
	CTime tAlignEndTime;
	CTimeSpan tAlignProcTime;


	SYSTEMTIME AlignStarttime;
	SYSTEMTIME AlignEndtime;
	SYSTEMTIME betweentime;

	CString strRealTime;

	void DisplayCam_0();
	void DisplayCam_1();
	void DisplayCam_2();
	void DisplayCam_3();
	void DisplayCam_4();

	void DisplayDrawAlign(CDC* pDC, int nCase);		// align
	void DisplayDrawManualAlign(CDC* pDC, int nCase);	// manual align
	void DisplayDrawReview(CDC* pDC);				// review
	void DisplayDrawNavigator(CDC* pDC);			// navigator
	void DisplayDrawFC(CDC* pDC);					// field correction
	void DisplayDrawSetting(CDC* pDC, int nCase);	// setting

	void DisplayColor(int nCase);

	void DisplayMagni(int nMagn, CPoint* StartPoint, CPoint* EndPoint);
	void DisplaySettingRoi(int nMagni, CPoint* startPos, CPoint* endPos);

	void CopyFolder(CString strFrom, CString strTo);

	BOOL CHK_PROC;
	BOOL CHK_ALIGN;
	BOOL CHK_SETTING;
	BOOL CHK_FC;
	BOOL CHK_MANUALALIGN;

	CBitmap m_bmp_login;
	CBitmap m_bmp_logout;
	CBitmap m_bmp_ledon;
	CBitmap m_bmp_ledoff;
	CBitmap m_bmp_ledon2;
	CBitmap m_bmp_ledoff2;

	CBitmap m_bmp_markpos;
	CBitmap m_bmp_edgepos;

	CPen pen_red;
	CPen pen_green;
	CPen pen_white;

	BOOL CHK_GRAPHIC;
	
	int MeasurementCase;

	CPoint MeasureStart;
	CPoint MeasureEnd;

	// Camera 설정 값 
	COLORREF cNameColor;
	COLORREF cCrossLineColor;
	COLORREF cROIColor;

	BOOL CHK_NAME;
	BOOL CHK_CROSSLINE;
	BOOL CHK_ROI;

	CPen cPenCrossline;
	CPen cPenROI;

	// ALIGN 오차 값
	double dModifyX;
	double dModifyY;
	double dModifyT;

	double dSizeX;
	double dSizeY;

	// 카메라와 laser 센터의 오차
	double dXOffset;
	double dYOffset;
	double dTOffset;

	double dAutosizing;

	// review
//	ClickPoint* pMeasurement;
	int MeasurementCount;
	int clickCount;;

	// fc result
	FCResult* pFCResult;

	FolderInfo* pFolderInfo;

	// field correction
	double dGain;
	double dNewcal;
	int nPatternPoint;
	double dPatternLength;
	CString strOldctFile;
	CString strNewctFile;

	double dMatchRate_FC;
	int nBinaryLow_FC;
	int nOpen_FC;
	int nClose_FC;

	CPoint StartPoint_FC;
	CPoint EndPoint_FC;

	BOOL ChkFindFC;
	Point findPoint;

	BOOL ChkFindLaser;
	Point findLaserPoint;

	int nCountFC;

	double dErrorX_FC;
	double dErrorY_FC;
	int nRun_FC;

	HWND hServerHandle;
	COPYDATASTRUCT stSend;
	R2RCommData stSendData;


	afx_msg void OnClose();

	int nHeartbeat;

	//
	int ChkConnectCam1;
	int ChkConnectCam2;
	int ChkConnectCam3;
	int ChkConnectCam4;
	int ChkConnectCam5;

	R2RCommData stReceiveData;

protected:
	afx_msg LRESULT OnHeartbeat(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_icon_handle;
	CStatic m_icon_heartbeat;

	HDC hdcMarkFC;
	HDC hdcMarkAlign;
	HDC hdcMarkLaser;

	HDC hdcMarkPos;

	HDC hdcProcImg;
	//Mat MarkImg;

	char m_chBmpMark[2048];
	BITMAPINFO* m_pBmpMark = NULL;

	char m_chBmpAlignMark[2048];
	BITMAPINFO* m_pBmpAlignMark = NULL;

	char m_chBmpLaserMark[2048];
	BITMAPINFO* m_pBmpLaserMark = NULL;

	char m_chBmpProcImg[2048];
	BITMAPINFO* m_pBmpProcImg = NULL;

	void RecipeSelect();
	void RecipeAdd();
	CStatic m_icon_camera_1;
	CStatic m_icon_camera_2;
	CStatic m_icon_camera_3;
	CStatic m_icon_camera_4;
	CStatic m_icon_camera_5;
	CStatic m_icon_light;

	void SaveRecipeName();

	ULARGE_INTEGER avail, total, free;
	double nAvail, nTotal, nFree;

	void DisplayAlarm();
	void ReconnectCamera();
	void DisplayPreprocessImg(int nCam, bool nCase);

	BOOL chkDisplayProc;

	int chkalarmdisplay;
	CFont* btnFont;

	// log write 관련 변수
	CString strLogData;
	CStringA csLogData;
	const char* cFullLog;
	char* cpFullLog;
	afx_msg void OnDestroy();

	CFont fontScale;


	//Mat tt;

	Mat CamModify_1;
	Mat CamModify_2;
	Mat CamModify_3;
	Mat CamModify_4;

	CPoint CamPoint_1[CamModify1];
	CPoint CamPoint_2[CamModify2];
	CPoint CamPoint_3[CamModify3];
	CPoint CamPoint_4[CamModify4];

	CPoint CamModifyPoint_1[CamModify1];
	CPoint CamModifyPoint_2[CamModify2];
	CPoint CamModifyPoint_3[CamModify3];
	CPoint CamModifyPoint_4[CamModify4];

};


class FCResult
{
public:
	double dXError;
	double dYError;
};


class FolderInfo
{
public:
	CTime nCreateTime;
	CString strFolderName;
};
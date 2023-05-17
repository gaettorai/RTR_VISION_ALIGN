// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

#define DialogWidth		642

#define WindowWidth		612
#define WindowHeight	885 
//#define WindowHeight	975

#define CamWidth		2448
#define CamHeight		2048

#define AlignResolution		1.725
#define ReviewResolution	0.8625
#define FCResolution		0.8625

#define CamCount		5

#define CamName1		_T("ALIGN1")
#define CamName2		_T("ALIGN2")
#define CamName3		_T("ALIGN3")
#define CamName4		_T("ALIGN4")
#define CamName5		_T("REVIEW")

#define ColorBasic		RGB(240,240,240)
#define ColorGreen		RGB(0,255,0)
#define ColorYellow		RGB(255,255,0)

#define PORT_NUM 9
#define PORT_BAUD 3
#define PORT_DATA 3
#define PORT_PARITY 0
#define PORT_STOP 0

#define WIDTHBYTES(bits) (((bits)+31)/32*4)

#define WM_HEARTBEAT	WM_USER + 17


#define CamModify1	1188
#define CamModify2	59
#define CamModify3	284
#define CamModify4	558

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "bgapi2_genicam.hpp"

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.

#include <afxdisp.h>        // MFC 자동화 클래스입니다.

using namespace cv;
using namespace std;
using namespace BGAPI2;

extern CCriticalSection g_criticalLog;
extern CCriticalSection g_criticlaDbg;
extern CCriticalSection	g_criticalExe;


enum LogType
{
	NORMAL = 0,
	NG,
	END,
	ALIGNMENT,
	REVIEW,
	FIELDCORRECTION,
	LASERCALIBRATION
};

void LogWrite(int nType, const char* fmt, ...);
CString GetFilePath();

typedef struct ClickPoint
{
public:

	BOOL ChkMeasurement[10];
	int CaseMeasurement[10];

	CPoint FirstPoint[10];
	CPoint SecondPoint[10];
	CPoint ThirdPoint[10];
};


typedef struct RecipeName
{
public:
	bool bChkEmpty[100];
	int nNum[100];
	CString strRecipeName[100];
};


typedef struct CameraParameter
{
public:
	CString strName[5];

	int nExposureTime[5];
	int nLight[5];

	double dCenterX[5];
	double dCenterY[5];
};


typedef struct AlignParameter
{
public:
	int nBinaryLow[4];
	int nOpen[4];
	int nClose[4];

	CPoint ROIStart[4];
	CPoint ROIEnd[4];

	CPoint AlignPoint[4];
};

typedef struct EdgeAlignParameter
{
public:
	//CPoint StartPoint[4];
	//CPoint EndPoint[4];

	//// 전처리 관련
	//int nBinaryLow[4];
	//int nOpen[4];
	//int nClose[4];

	//CPoint AlignPoint[4];	// 각 카메라의 ALIGN POINT

	CPoint EdgeStart[4];
	CPoint EdgeEnd[4];

	BOOL ChkFind[4];
	BOOL ChkMistake[4];

	CPoint ClickPoint[4];

	CPoint FirstPoint[4];
	CPoint SecondPoint[4];

	double Slope[4];
};


typedef struct MarkAlignParameter
{
public:
	//CPoint StartPoint[4];
	//CPoint EndPoint[4];

	//int nBinaryLow[4];
	//int nOpen[4];
	//int nClose[4];

	//CPoint AlignPoint[4];	// 각 카메라의 ALIGN POINT

	CPoint MarkStart[4];
	CPoint MarkEnd[4];

	BOOL ChkFind[4];
	int nChkFindMark[4];

	BOOL ChkManualFind[4];
	int nChkManualMark[4];

	CPoint ClickPoint[4];

	CPoint FirstPoint[4];
	CPoint SecondPoint[4];
};



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#endif //PCH_H

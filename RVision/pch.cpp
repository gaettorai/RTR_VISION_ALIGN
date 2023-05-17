// pch.cpp: 미리 컴파일된 헤더에 해당하는 소스 파일

#include "pch.h"

ClickPoint stMeasure;
RecipeName stRecipe;
CameraParameter stCamera;
AlignParameter	stAlign;
EdgeAlignParameter stEdgeAlign;
MarkAlignParameter stMarkAlign;


// 미리 컴파일된 헤더를 사용하는 경우 컴파일이 성공하려면 이 소스 파일이 필요합니다.
CCriticalSection g_criticalLog;
CCriticalSection g_criticalExe;

void LogWrite(int nType, const char* fmt, ...)
{
	g_criticalLog.Lock();

	static _TCHAR szLog[5096];
	//CString szLog;
	FILE* fp = NULL;
	CTime tm = CTime::GetCurrentTime();

	CString strLog = _T("");
	CString strPath = _T("");

	SYSTEMTIME cur_time;

	if (fmt == NULL)
	{
		g_criticalLog.Unlock();
		return;
	}

	ZeroMemory(szLog, 5096);
	//swprintf(szLog, fmt);
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, fmt, strlen(fmt),szLog, 5096);
	
	strPath.Format(_T("%s\\VisionLog\\%s"), _T("D:"), tm.Format(_T("%Y_%m_%d.log")));

	_bstr_t gg(strPath);

	fopen_s(&fp, gg, "a+");

	GetLocalTime(&cur_time);

	strLog.Format(_T("%04d-%02d-%02d %02d:%02d:%02d:%03ld_"), 
		cur_time.wYear, cur_time.wMonth, cur_time.wDay,cur_time.wHour, cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds);

	if (fp != NULL)
	{
		switch (nType)
		{
		case NORMAL:
			strLog = strLog + _T("[NORMAL]  :  ");
			break;

		case NG:
			strLog = strLog + _T("[ERROR]  :  ");
			break;

		case END:
			strLog = strLog + _T("[END]  :  ");
			break; 

		case ALIGNMENT:
			strLog += _T("[ALIGNMENT]  :  ");
			break;

		case REVIEW:
			strLog += _T("[REVIEW]  :  ");
			break;

		case FIELDCORRECTION:
			strLog += _T("[FIELD CORRECTION]  :  ");
			break;

		case LASERCALIBRATION:
			strLog += _T("[LASER CALIBRATION]  :  ");
			break;
		}

		strLog += szLog;
	
		CStringA csAFullAddr = CStringA(strLog);
		const char* cFullAddr = csAFullAddr;
		char* cpFullAddr = const_cast<char*>(cFullAddr);

		//const char* strMessage = (char*)(LPCTSTR)strLog;
		//fputs(fmt, fp);
		fprintf(fp, "%s\r", cpFullAddr);
		fflush(fp);
		fclose(fp);
	}

	else
	{
		CString strErrorMsg;
		DWORD dwErrNo = GetLastError();

		strErrorMsg.Format(_T("LOG FILE Open Fail : Code = [%d],"), dwErrNo);
	}

	g_criticalLog.Unlock();
}

CString GetFilePath()
{
	g_criticalExe.Lock();

	static TCHAR pBuf[256] = { 0 , };

	memset(pBuf, NULL, sizeof(pBuf));

	//GetModuleFileName
	CString strMsg;
	return strMsg;
}
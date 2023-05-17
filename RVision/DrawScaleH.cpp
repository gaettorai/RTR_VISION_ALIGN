// DrawScaleH.cpp: 구현 파일
//

#include "pch.h"
#include "RVision.h"
#include "DrawScaleH.h"
#include "afxdialogex.h"


// DrawScaleH 대화 상자

IMPLEMENT_DYNAMIC(DrawScaleH, CDialogEx)

DrawScaleH::DrawScaleH(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRAW_SCALE_H, pParent)
{

}

DrawScaleH::~DrawScaleH()
{
}

void DrawScaleH::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DrawScaleH, CDialogEx)
END_MESSAGE_MAP()


// DrawScaleH 메시지 처리기

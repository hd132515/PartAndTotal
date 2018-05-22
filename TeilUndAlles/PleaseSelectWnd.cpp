// PleaseSelectWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TeilUndAlles.h"
#include "PleaseSelectWnd.h"
#include "afxdialogex.h"


// CPleaseSelectWnd 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPleaseSelectWnd, CDialogEx)

CPleaseSelectWnd::CPleaseSelectWnd(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SELECT_OBJ, pParent)
{

}

CPleaseSelectWnd::~CPleaseSelectWnd()
{
}

void CPleaseSelectWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPleaseSelectWnd, CDialogEx)
END_MESSAGE_MAP()


// CPleaseSelectWnd 메시지 처리기입니다.

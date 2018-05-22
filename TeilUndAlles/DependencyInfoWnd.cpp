// DependencyInfoWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TeilUndAlles.h"
#include "DependencyInfoWnd.h"
#include "afxdialogex.h"


// CDependencyInfoWnd 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDependencyInfoWnd, CDialogEx)

CDependencyInfoWnd::CDependencyInfoWnd(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DEPENDENCY_DETAIL, pParent)
{

}

CDependencyInfoWnd::~CDependencyInfoWnd()
{
}

void CDependencyInfoWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDependencyInfoWnd, CDialogEx)
END_MESSAGE_MAP()


// CDependencyInfoWnd 메시지 처리기입니다.

// DependencyInfoWnd.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TeilUndAlles.h"
#include "DependencyInfoWnd.h"
#include "afxdialogex.h"


// CDependencyInfoWnd ��ȭ �����Դϴ�.

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


// CDependencyInfoWnd �޽��� ó�����Դϴ�.

// PleaseSelectWnd.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TeilUndAlles.h"
#include "PleaseSelectWnd.h"
#include "afxdialogex.h"


// CPleaseSelectWnd ��ȭ �����Դϴ�.

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


// CPleaseSelectWnd �޽��� ó�����Դϴ�.

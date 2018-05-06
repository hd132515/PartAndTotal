// NewNodeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TeilUndAlles.h"
#include "NewNodeDlg.h"
#include "afxdialogex.h"


// CNewNodeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CNewNodeDlg, CDialogEx)

CNewNodeDlg::CNewNodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NEW_NODE, pParent)
{

}

CNewNodeDlg::~CNewNodeDlg()
{
}

void CNewNodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NODE_NAME, edit_nodename);
}


BEGIN_MESSAGE_MAP(CNewNodeDlg, CDialogEx)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CNewNodeDlg 메시지 처리기입니다.


BOOL CNewNodeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CNewNodeDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CNewNodeDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString content;
	edit_nodename.GetWindowTextW(content);
	if (content.GetLength() == 0) {
		AfxMessageBox(L"문제 내용이 없다.");
		return;
	}
	mfc_nodename = content;
	nodename = std::wstring(content);

	CDialogEx::OnOK();
}

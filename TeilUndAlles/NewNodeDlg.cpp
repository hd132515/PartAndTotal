// NewNodeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TeilUndAlles.h"
#include "NewNodeDlg.h"
#include "afxdialogex.h"


// CNewNodeDlg ��ȭ �����Դϴ�.

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


// CNewNodeDlg �޽��� ó�����Դϴ�.


BOOL CNewNodeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CNewNodeDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CNewNodeDlg::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CString content;
	edit_nodename.GetWindowTextW(content);
	if (content.GetLength() == 0) {
		AfxMessageBox(L"���� ������ ����.");
		return;
	}
	mfc_nodename = content;
	nodename = std::wstring(content);

	CDialogEx::OnOK();
}

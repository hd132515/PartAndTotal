// DeleteDependencyDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TeilUndAlles.h"
#include "DeleteDependencyDlg.h"
#include "afxdialogex.h"


// CDeleteDependencyDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDeleteDependencyDlg, CDialogEx)

CDeleteDependencyDlg::CDeleteDependencyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DELETE_DEP, pParent)
{

}

CDeleteDependencyDlg::~CDeleteDependencyDlg()
{
}

void CDeleteDependencyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDeleteDependencyDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SELECTION2, &CDeleteDependencyDlg::OnBnClickedSelection2)
	ON_BN_CLICKED(IDC_SELECTION1, &CDeleteDependencyDlg::OnBnClickedSelection1)
	ON_BN_CLICKED(IDC_CLOSE, &CDeleteDependencyDlg::OnBnClickedClose)
END_MESSAGE_MAP()


// CDeleteDependencyDlg 메시지 처리기입니다.

void CDeleteDependencyDlg::set_dependency(Dependency* _dependency)
{
	dependency = _dependency;
}

BOOL CDeleteDependencyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	CButton* btn_selection1 = (CButton*)GetDlgItem(IDC_SELECTION1);
	CButton* btn_selection2 = (CButton*)GetDlgItem(IDC_SELECTION2);

	CString str;
	str.Format(L"%d -> %d", dependency->getid1(), dependency->getid2());
	btn_selection1->SetWindowTextW(str);
	str.Format(L"%d <- %d", dependency->getid2(), dependency->getid1());
	btn_selection2->SetWindowTextW(str);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDeleteDependencyDlg::OnBnClickedSelection1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	EndDialog(300);
}


void CDeleteDependencyDlg::OnBnClickedSelection2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	EndDialog(301);
}

void CDeleteDependencyDlg::OnBnClickedClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	EndDialog(0);
}

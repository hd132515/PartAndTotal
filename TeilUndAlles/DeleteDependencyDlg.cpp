// DeleteDependencyDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TeilUndAlles.h"
#include "DeleteDependencyDlg.h"
#include "afxdialogex.h"


// CDeleteDependencyDlg ��ȭ �����Դϴ�.

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


// CDeleteDependencyDlg �޽��� ó�����Դϴ�.

void CDeleteDependencyDlg::set_dependency(Dependency* _dependency)
{
	dependency = _dependency;
}

BOOL CDeleteDependencyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	CButton* btn_selection1 = (CButton*)GetDlgItem(IDC_SELECTION1);
	CButton* btn_selection2 = (CButton*)GetDlgItem(IDC_SELECTION2);

	CString str;
	str.Format(L"%d -> %d", dependency->getid1(), dependency->getid2());
	btn_selection1->SetWindowTextW(str);
	str.Format(L"%d <- %d", dependency->getid2(), dependency->getid1());
	btn_selection2->SetWindowTextW(str);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CDeleteDependencyDlg::OnBnClickedSelection1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	EndDialog(300);
}


void CDeleteDependencyDlg::OnBnClickedSelection2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	EndDialog(301);
}

void CDeleteDependencyDlg::OnBnClickedClose()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	EndDialog(0);
}

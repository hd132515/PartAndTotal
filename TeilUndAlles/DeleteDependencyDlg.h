#pragma once

#include "Dependency.h"

// CDeleteDependencyDlg ��ȭ �����Դϴ�.

class CDeleteDependencyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteDependencyDlg)

public:
	CDeleteDependencyDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDeleteDependencyDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETE_DEP };
#endif

private:
	Dependency* dependency;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	void set_dependency(Dependency* dependency);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSelection2();
	afx_msg void OnBnClickedSelection1();
	afx_msg void OnBnClickedClose();
};

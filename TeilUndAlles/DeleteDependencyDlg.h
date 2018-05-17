#pragma once

#include "Dependency.h"

// CDeleteDependencyDlg 대화 상자입니다.

class CDeleteDependencyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteDependencyDlg)

public:
	CDeleteDependencyDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDeleteDependencyDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETE_DEP };
#endif

private:
	Dependency* dependency;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void set_dependency(Dependency* dependency);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSelection2();
	afx_msg void OnBnClickedSelection1();
	afx_msg void OnBnClickedClose();
};

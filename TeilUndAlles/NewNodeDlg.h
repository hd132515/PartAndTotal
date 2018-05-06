#pragma once
#include "afxwin.h"
#include <string>

// CNewNodeDlg 대화 상자입니다.

class CNewNodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewNodeDlg)

public:
	CNewNodeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CNewNodeDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_NODE };
#endif
private:
	CEdit edit_nodename;
public:
	CString mfc_nodename;
	std::wstring nodename;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnOK();
};

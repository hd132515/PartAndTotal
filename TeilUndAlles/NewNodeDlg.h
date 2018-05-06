#pragma once
#include "afxwin.h"
#include <string>

// CNewNodeDlg ��ȭ �����Դϴ�.

class CNewNodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewNodeDlg)

public:
	CNewNodeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CNewNodeDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_NODE };
#endif
private:
	CEdit edit_nodename;
public:
	CString mfc_nodename;
	std::wstring nodename;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnOK();
};

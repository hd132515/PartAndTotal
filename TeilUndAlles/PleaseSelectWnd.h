#pragma once


// CPleaseSelectWnd ��ȭ �����Դϴ�.

class CPleaseSelectWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CPleaseSelectWnd)

public:
	CPleaseSelectWnd(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPleaseSelectWnd();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECT_OBJ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

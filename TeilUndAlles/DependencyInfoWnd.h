#pragma once


// CDependencyInfoWnd ��ȭ �����Դϴ�.

class CDependencyInfoWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CDependencyInfoWnd)

public:
	CDependencyInfoWnd(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDependencyInfoWnd();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEPENDENCY_DETAIL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

#pragma once


// CDependencyInfoWnd 대화 상자입니다.

class CDependencyInfoWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CDependencyInfoWnd)

public:
	CDependencyInfoWnd(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDependencyInfoWnd();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEPENDENCY_DETAIL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};

#pragma once


// CPleaseSelectWnd 대화 상자입니다.

class CPleaseSelectWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CPleaseSelectWnd)

public:
	CPleaseSelectWnd(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPleaseSelectWnd();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECT_OBJ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};

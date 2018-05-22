#pragma once
#include "ATLComTime.h"
#include "Node.h"


// CDetailInfoWnd 대화 상자입니다.

class CTeilUndAllesDoc;

class CDetailInfoWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CDetailInfoWnd)

public:
	CDetailInfoWnd(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDetailInfoWnd();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DETIALINFORMATIONVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	CTeilUndAllesDoc* pDoc;
	Node* selected_node;
public:
	UINT m_id;
	CString m_strnodename;
	CString m_strnodedesc;
	COleDateTime m_datedue;
	BOOL m_checkcomplete;

	void select_node(CTeilUndAllesDoc* pDoc, Node* _selected_node);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

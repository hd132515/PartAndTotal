#pragma once
#include "ATLComTime.h"
#include "Node.h"


// CDetailInfoWnd ��ȭ �����Դϴ�.

class CTeilUndAllesDoc;

class CDetailInfoWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CDetailInfoWnd)

public:
	CDetailInfoWnd(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDetailInfoWnd();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DETIALINFORMATIONVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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

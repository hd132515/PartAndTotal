#pragma once


// CDetailInfoPane

#include "Node.h"
#include "Dependency.h"

#include "DetailInfoWnd.h"
#include "PleaseSelectWnd.h"
#include "DependencyInfoWnd.h"

class CTeilUndAllesDoc;

class CDetailInfoPane : public CDockablePane
{
	DECLARE_DYNAMIC(CDetailInfoPane)

public:
	CDetailInfoPane();
	virtual ~CDetailInfoPane();

private:
public:
	CPleaseSelectWnd psw;
	CDetailInfoWnd niw;
	CDependencyInfoWnd diw;
public:
	void not_selected();
	void view_info_selected_node(CTeilUndAllesDoc* pDoc, Node* node);
	void view_info_selected_dep(CTeilUndAllesDoc* pDoc, Dependency* dependency);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};



// DetailInfoPane.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TeilUndAlles.h"
#include "DetailInfoPane.h"
#include "resource.h"
#include "TeilUndAllesDoc.h"


// CDetailInfoPane

IMPLEMENT_DYNAMIC(CDetailInfoPane, CDockablePane)

CDetailInfoPane::CDetailInfoPane() : psw(this), niw(this), diw(this)
{

}

CDetailInfoPane::~CDetailInfoPane()
{
}


BEGIN_MESSAGE_MAP(CDetailInfoPane, CDockablePane)
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CDetailInfoPane 메시지 처리기입니다.



int CDetailInfoPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	psw.Create(IDD_SELECT_OBJ, this);
	niw.Create(IDD_DETIALINFORMATIONVIEW, this);
	diw.Create(IDD_DEPENDENCY_DETAIL, this);

	not_selected();

	return 0;
}

void CDetailInfoPane::not_selected()
{
	niw.ShowWindow(SW_HIDE);
	diw.ShowWindow(SW_HIDE);
	psw.ShowWindow(SW_SHOW);
}

void CDetailInfoPane::view_info_selected_node(CTeilUndAllesDoc* pDoc, Node* node)
{
	niw.select_node(pDoc, node);

	psw.ShowWindow(SW_HIDE);
	diw.ShowWindow(SW_HIDE);
	niw.ShowWindow(SW_SHOW);
}

void CDetailInfoPane::view_info_selected_dep(CTeilUndAllesDoc* pDoc, Dependency* node)
{
	psw.ShowWindow(SW_HIDE);
	niw.ShowWindow(SW_HIDE);
	diw.ShowWindow(SW_SHOW);
}

void CDetailInfoPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	psw.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);
	diw.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);
	niw.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);
}

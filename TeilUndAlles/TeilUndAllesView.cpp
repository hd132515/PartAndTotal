
// TeilUndAllesView.cpp : CTeilUndAllesView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "TeilUndAlles.h"
#endif

#include "MainFrm.h"
#include "TeilUndAllesDoc.h"
#include "TeilUndAllesView.h"

#include "AbstractGraphicInterface.h"
#include <chrono>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTeilUndAllesView

IMPLEMENT_DYNCREATE(CTeilUndAllesView, CView)

BEGIN_MESSAGE_MAP(CTeilUndAllesView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTeilUndAllesView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_NEW_NODE, &CTeilUndAllesView::OnNewNode)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_REMOVE_NODE, &CTeilUndAllesView::OnRemoveNode)
	ON_COMMAND(ID_NEW_DEPENDENCY, &CTeilUndAllesView::OnNewDependency)
	ON_COMMAND(ID_REMOVE_DEPENDENCY, &CTeilUndAllesView::OnRemoveDependency)
	ON_COMMAND(ID_MODIFY_DEPENDENCY, &CTeilUndAllesView::OnModifyDependency)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CTeilUndAllesView 생성/소멸

CTeilUndAllesView::CTeilUndAllesView() : editing_mode(EditingMode::NONE), dragging(false)
{
	// TODO: 여기에 생성 코드를 추가합니다.

	dep_info.srcid = dep_info.dstid = -1;
}

CTeilUndAllesView::~CTeilUndAllesView()
{
}

BOOL CTeilUndAllesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CTeilUndAllesView 그리기

void CTeilUndAllesView::OnDraw(CDC* pDC)
{
	auto start = std::chrono::high_resolution_clock::now();

	CTeilUndAllesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CBitmap bitmap;
	CBitmap* pOldBmp;
	CDC MemDC;

	CRect cRect;
	this->GetClientRect(&cRect);

	bitmap.CreateCompatibleBitmap(pDC, cRect.right, cRect.bottom);
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp = MemDC.SelectObject(&bitmap);
	MemDC.PatBlt(0, 0, cRect.right, cRect.bottom, WHITENESS);


	auto set_dependencygi = pDoc->get_set_dependencygi();
	for (auto dependency : set_dependencygi)
	{
		dependency.second->draw_dependency(&MemDC);
	}

	auto set_nodegi = pDoc->get_set_nodegi();
	for (auto node : set_nodegi)
	{
		node.second->draw_node(&MemDC);
	}


	pDC->BitBlt(0, 0, cRect.right, cRect.bottom, &MemDC, 0, 0, SRCCOPY);

	pDC->SelectObject(pOldBmp);
	bitmap.DeleteObject();
	ReleaseDC(&MemDC);
	DeleteDC(MemDC);

	std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
	CString str;
	str.Format(L"%f", elapsed.count());
	//AfxMessageBox(str);
}


// CTeilUndAllesView 인쇄


void CTeilUndAllesView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTeilUndAllesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTeilUndAllesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTeilUndAllesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CTeilUndAllesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	if (editing_mode != EditingMode::NONE)
	{
		dep_info.srcid = dep_info.dstid = -1;
		editing_mode = EditingMode::NONE;
	}
	else
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}
	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

void CTeilUndAllesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTeilUndAllesView 진단

#ifdef _DEBUG
void CTeilUndAllesView::AssertValid() const
{
	CView::AssertValid();
}

void CTeilUndAllesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTeilUndAllesDoc* CTeilUndAllesView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTeilUndAllesDoc)));
	return (CTeilUndAllesDoc*)m_pDocument;
}
#endif //_DEBUG

void CTeilUndAllesView::draw_prenode(CPoint& pt)
{
	RECT rect = {
		pt.x - NODE_WIDTH / 2,
		pt.y - NODE_HEIGHT / 2,
		pt.x + NODE_WIDTH / 2,
		pt.y + NODE_HEIGHT / 2,
	};
	GetDC()->Ellipse(&rect);
}



// CTeilUndAllesView 메시지 처리기

void CTeilUndAllesView::OnNewNode()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	editing_mode = EditingMode::CREATE_NODE;
}

void CTeilUndAllesView::add_node(CTeilUndAllesDoc* pDoc, CPoint& pt)
{
	pDoc->add_node(pt);
	pDoc->SetModifiedFlag();
	pDoc->UpdateAllViews(NULL);

	editing_mode = EditingMode::NONE;
}


void CTeilUndAllesView::OnRemoveNode()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	editing_mode = EditingMode::REMOVE_NODE;
}

void CTeilUndAllesView::remove_node(CTeilUndAllesDoc* pDoc)
{
	if (selected != NULL && 
		typeid(*selected) == typeid(NodeGI) && 
		AfxMessageBox(L"진짜 제거?", MB_OKCANCEL) == IDOK)
	{
		pDoc->remove_selected_node();
		pDoc->SetModifiedFlag();
		pDoc->UpdateAllViews(NULL);
	}

	editing_mode = EditingMode::NONE;
}

void CTeilUndAllesView::OnNewDependency()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	editing_mode = EditingMode::CREATE_DEP;
}

void CTeilUndAllesView::new_dependency(CTeilUndAllesDoc* pDoc)
{
	NodeGI* nodegi = NULL;
	if ((nodegi = dynamic_cast<NodeGI*>(selected)) != NULL)
	{
		if (dep_info.srcid == -1)
		{
			dep_info.srcid = nodegi->get_node()->getid();
			return;
		}

		if (dep_info.dstid == -1)
		{
			dep_info.dstid = nodegi->get_node()->getid();
		}

		if (dep_info.srcid != -1 && dep_info.dstid != -1)
		{
			pDoc->add_dependency(dep_info.srcid, dep_info.dstid);
			pDoc->SetModifiedFlag();
			pDoc->UpdateAllViews(NULL);
			editing_mode = EditingMode::NONE;
			dep_info.srcid = dep_info.dstid = -1;
		}
	}
}

void CTeilUndAllesView::OnRemoveDependency()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	editing_mode = EditingMode::REMOVE_DEP;
}

void CTeilUndAllesView::remove_dependency(CTeilUndAllesDoc* pDoc)
{
	if (selected != NULL &&
		typeid(*selected) == typeid(DependencyGI) && 
		AfxMessageBox(L"진짜 제거?", MB_OKCANCEL) == IDOK)
	{
		pDoc->remove_selected_dependency();
		pDoc->UpdateAllViews(NULL);
		editing_mode = EditingMode::NONE;
	}
}

void CTeilUndAllesView::OnModifyDependency()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	editing_mode = EditingMode::MODIFY_DEP;
}

void CTeilUndAllesView::modify_dependency(CPoint& pt)
{
}



BOOL CTeilUndAllesView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (editing_mode == EditingMode::CREATE_NODE ||
		editing_mode == EditingMode::REMOVE_NODE || 
		editing_mode == EditingMode::CREATE_DEP ||
		editing_mode == EditingMode::REMOVE_DEP)
	{
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		return TRUE;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}


void CTeilUndAllesView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	dragging = false;
	CTeilUndAllesDoc* pDoc = GetDocument();
	switch (editing_mode)
	{
	case EditingMode::CREATE_NODE:
		add_node(pDoc, point);
		break;
	case EditingMode::REMOVE_NODE:
		remove_node(pDoc);
		break;
	case EditingMode::CREATE_DEP:
		new_dependency(pDoc);
		break;
	case EditingMode::REMOVE_DEP:
		remove_dependency(pDoc);
		break;
	case EditingMode::MODIFY_DEP:
		break;
	}

	CView::OnLButtonUp(nFlags, point);
}


void CTeilUndAllesView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CTeilUndAllesDoc* pDoc = GetDocument();

	dragging = true;
	if (editing_mode == EditingMode::NONE || 
		editing_mode == EditingMode::REMOVE_NODE ||
		editing_mode == EditingMode::CREATE_DEP ||
		editing_mode == EditingMode::REMOVE_DEP)
	{
		CMainFrame* mainframe = (CMainFrame*)AfxGetMainWnd();
		selected = pDoc->select_interface(point);
		if (selected == NULL)
		{
			mainframe->get_detail_info_pane()->not_selected();
		}
		else
		{
			auto type = typeid(*selected).hash_code();
			if (type == typeid(NodeGI).hash_code())
			{
				mainframe->get_detail_info_pane()->view_info_selected_node(pDoc, ((NodeGI*)selected)->get_node());
			}
			else if (type == typeid(DependencyGI).hash_code())
			{
				mainframe->get_detail_info_pane()->view_info_selected_dep(pDoc, ((DependencyGI*)selected)->get_dependency());
			}
		}
		pDoc->UpdateAllViews(NULL);
	}

	CView::OnLButtonDown(nFlags, point);
}


void CTeilUndAllesView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CTeilUndAllesDoc* pDoc = GetDocument();
	if (dragging)
	{
		if(pDoc->try_dragging(point))
			Invalidate();
	}

	CView::OnMouseMove(nFlags, point);
}



void CTeilUndAllesView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	/*CTeilUndAllesDoc* pDoc = GetDocument();
	for (int i = 0; i < 100; i++)
	{
		CPoint point((NODE_WIDTH+30)*((i%10)+1), (NODE_HEIGHT+15)*((i/10)+1));
		pDoc->add_node(point);
	}*/
}


BOOL CTeilUndAllesView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return FALSE;
	//return CView::OnEraseBkgnd(pDC);
}


// TeilUndAllesView.cpp : CTeilUndAllesView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "TeilUndAlles.h"
#endif

#include "TeilUndAllesDoc.h"
#include "TeilUndAllesView.h"
#include "NewNodeDlg.h"

#include <chrono>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTeilUndAllesView

IMPLEMENT_DYNCREATE(CTeilUndAllesView, CView)

BEGIN_MESSAGE_MAP(CTeilUndAllesView, CView)
	// ǥ�� �μ� ����Դϴ�.
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

// CTeilUndAllesView ����/�Ҹ�

CTeilUndAllesView::CTeilUndAllesView() : editing_mode(EditingMode::NONE), dragging(false)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

	dep_info.srcid = dep_info.dstid = -1;
}

CTeilUndAllesView::~CTeilUndAllesView()
{
}

BOOL CTeilUndAllesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CTeilUndAllesView �׸���

void CTeilUndAllesView::OnDraw(CDC* pDC)
{
	auto start = std::chrono::high_resolution_clock::now();

	CTeilUndAllesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

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
		dependency->draw_main_line(&MemDC);
		dependency->draw_direction(&MemDC);
	}

	auto set_nodegi = pDoc->get_set_nodegi();
	for (auto node : set_nodegi)
	{
		node->drawNode(&MemDC);
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


// CTeilUndAllesView �μ�


void CTeilUndAllesView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTeilUndAllesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CTeilUndAllesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CTeilUndAllesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CTeilUndAllesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTeilUndAllesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTeilUndAllesView ����

#ifdef _DEBUG
void CTeilUndAllesView::AssertValid() const
{
	CView::AssertValid();
}

void CTeilUndAllesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTeilUndAllesDoc* CTeilUndAllesView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
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



// CTeilUndAllesView �޽��� ó����

void CTeilUndAllesView::OnNewNode()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	editing_mode = EditingMode::CREATE_NODE;
}

void CTeilUndAllesView::add_node(CTeilUndAllesDoc* pDoc, CPoint& pt)
{
	draw_prenode(pt);

	CNewNodeDlg dlg;
	INT_PTR res = dlg.DoModal();

	if (res == IDOK)
	{
		pDoc->add_node(dlg.nodename, pt);
		pDoc->SetModifiedFlag();
		pDoc->UpdateAllViews(NULL);
	}
	else
		Invalidate();

	editing_mode = EditingMode::NONE;
}


void CTeilUndAllesView::OnRemoveNode()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	editing_mode = EditingMode::REMOVE_NODE;
}

void CTeilUndAllesView::remove_node(CTeilUndAllesDoc* pDoc)
{
	int res;
	if (!(res = pDoc->validate_selection()))
	{
		AfxMessageBox(L"validate_selection ���� ����");
	}
	else if (res == 1)
	{
		if (AfxMessageBox(L"��¥ ����?", MB_OKCANCEL) == IDOK)
		{
			pDoc->remove_selected_node();
			pDoc->SetModifiedFlag();
			pDoc->UpdateAllViews(NULL);
		}
	}

	editing_mode = EditingMode::NONE;
}

void CTeilUndAllesView::OnNewDependency()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	editing_mode = EditingMode::CREATE_DEP;
}

void CTeilUndAllesView::new_dependency(CTeilUndAllesDoc* pDoc)
{
	if (dep_info.srcid == -1)
	{
		dep_info.srcid = pDoc->get_selected_node()->getNode()->getid();
		return;
	}
	
	if (dep_info.dstid == -1)
	{
		dep_info.dstid = pDoc->get_selected_node()->getNode()->getid();
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

void CTeilUndAllesView::OnRemoveDependency()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	editing_mode = EditingMode::REMOVE_DEP;
}

void CTeilUndAllesView::remove_dependency(CPoint& pt)
{
}

void CTeilUndAllesView::OnModifyDependency()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	editing_mode = EditingMode::MODIFY_DEP;
}

void CTeilUndAllesView::modify_dependency(CPoint& pt)
{
}



BOOL CTeilUndAllesView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (editing_mode == EditingMode::CREATE_NODE ||
		editing_mode == EditingMode::REMOVE_NODE || 
		editing_mode == EditingMode::CREATE_DEP)
	{
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		return TRUE;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}


void CTeilUndAllesView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
		break;
	case EditingMode::MODIFY_DEP:
		break;
	}

	CView::OnLButtonUp(nFlags, point);
}


void CTeilUndAllesView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CTeilUndAllesDoc* pDoc = GetDocument();

	dragging = true;
	if (editing_mode == EditingMode::NONE || 
		editing_mode == EditingMode::REMOVE_NODE ||
		editing_mode == EditingMode::CREATE_DEP)
	{
		pDoc->select_node(point);
		pDoc->UpdateAllViews(NULL);
	}

	CView::OnLButtonDown(nFlags, point);
}


void CTeilUndAllesView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
	CTeilUndAllesDoc* pDoc = GetDocument();
	for (int i = 0; i < 25; i++)
	{
		CPoint point((NODE_WIDTH+30)*((i%5)+1), (NODE_HEIGHT+15)*((i/5)+1));
		pDoc->add_node(std::wstring(L"node")+std::to_wstring(i+1), point);
	}
	
	for (int i = 0; i < 24; i+=1)
	{
		for (int j = i + 1; j < 25; j+=1)
		{
			pDoc->add_dependency(i, j);
		}
	}
}


BOOL CTeilUndAllesView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	return FALSE;
	//return CView::OnEraseBkgnd(pDC);
}

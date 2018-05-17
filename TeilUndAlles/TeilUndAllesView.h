
// TeilUndAllesView.h : CTeilUndAllesView 클래스의 인터페이스
//

#pragma once

class AbstractGraphicInterface;

enum class EditingMode {
	NONE,
	CREATE_NODE,
	REMOVE_NODE,
	CREATE_DEP,
	REMOVE_DEP,
	MODIFY_DEP
};

struct DependencyInfo
{
	UINT srcid;
	UINT dstid;
};

class CTeilUndAllesView : public CView
{
protected: // serialization에서만 만들어집니다.
	CTeilUndAllesView();
	DECLARE_DYNCREATE(CTeilUndAllesView)

private:
	EditingMode editing_mode;
	DependencyInfo dep_info;
	bool dragging;
	AbstractGraphicInterface* selected;

// 특성입니다.
public:
	CTeilUndAllesDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CTeilUndAllesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void draw_prenode(CPoint& pt);

	void add_node(CTeilUndAllesDoc* pDoc, CPoint& pt);
	void remove_node(CTeilUndAllesDoc* pDoc);
	void new_dependency(CTeilUndAllesDoc* pDoc);
	void remove_dependency(CTeilUndAllesDoc* pDoc);
	void modify_dependency(CPoint& pt);

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNewNode();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRemoveNode();
	afx_msg void OnNewDependency();
	afx_msg void OnRemoveDependency();
	afx_msg void OnModifyDependency();
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // TeilUndAllesView.cpp의 디버그 버전
inline CTeilUndAllesDoc* CTeilUndAllesView::GetDocument() const
   { return reinterpret_cast<CTeilUndAllesDoc*>(m_pDocument); }
#endif


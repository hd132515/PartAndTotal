
// TeilUndAllesDoc.h : CTeilUndAllesDoc 클래스의 인터페이스
//


#pragma once

#include <set>
#include "NodeGI.h"
#include "Project.h"
#include "NewNodeDlg.h"


class CTeilUndAllesDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CTeilUndAllesDoc();
	DECLARE_DYNCREATE(CTeilUndAllesDoc)

private:
	Project project;
	std::set<NodeGI*> set_nodegi;
	NodeGI* selectedNodeGI;

// 특성입니다.
public:

// 작업입니다.
public:
	void add_node(std::wstring nodename, CPoint& pt);
	bool select_node(CPoint& pt);
	int validate_selection();
	void remove_selected_node();

	void add_dependency(UINT srcid, UINT dstid);

	bool try_dragging(CPoint& pt);


public:
	Project& getProject();
	NodeGI* get_selected_node();
	std::set<NodeGI*>& get_set_nodegi();

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CTeilUndAllesDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

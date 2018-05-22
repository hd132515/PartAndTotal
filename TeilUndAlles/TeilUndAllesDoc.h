
// TeilUndAllesDoc.h : CTeilUndAllesDoc 클래스의 인터페이스
//


#pragma once

#include <unordered_map>
#include "NodeGI.h"
#include "DependencyGI.h"
#include "Project.h"


class CTeilUndAllesDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CTeilUndAllesDoc();
	DECLARE_DYNCREATE(CTeilUndAllesDoc)

private:
	Project project;
	std::unordered_map<UINT, NodeGI*> set_nodegi;
	std::unordered_map<UINT, DependencyGI*> set_dependencygi;
	std::set<UINT> used_id;
	AbstractGraphicInterface* selected_obj;

private:
	UINT possible_gi_id();

// 특성입니다.
public:

// 작업입니다.
public:
	void add_node(CPoint& pt);
	void remove_selected_node();

	void add_dependency(UINT srcid, UINT dstid);
	void remove_selected_dependency();
	
	bool try_dragging(CPoint& pt);

	AbstractGraphicInterface* select_interface(CPoint& pt);

	std::unordered_map<UINT, NodeGI*>& get_set_nodegi();
	std::unordered_map<UINT, DependencyGI*>& get_set_dependencygi();

	void export_graphic_interface(unsigned char** buffer_pointer, UINT* buffer_length);
	void import_graphic_interface(unsigned char* buffer);

public:
	Project& getProject();

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
public:
	virtual void DeleteContents();
};

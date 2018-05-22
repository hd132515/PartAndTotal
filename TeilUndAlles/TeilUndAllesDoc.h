
// TeilUndAllesDoc.h : CTeilUndAllesDoc Ŭ������ �������̽�
//


#pragma once

#include <unordered_map>
#include "NodeGI.h"
#include "DependencyGI.h"
#include "Project.h"


class CTeilUndAllesDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
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

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
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

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CTeilUndAllesDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual void DeleteContents();
};

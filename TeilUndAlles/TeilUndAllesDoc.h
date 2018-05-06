
// TeilUndAllesDoc.h : CTeilUndAllesDoc Ŭ������ �������̽�
//


#pragma once

#include <set>
#include "NodeGI.h"
#include "Project.h"
#include "NewNodeDlg.h"


class CTeilUndAllesDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CTeilUndAllesDoc();
	DECLARE_DYNCREATE(CTeilUndAllesDoc)

private:
	Project project;
	std::set<NodeGI*> set_nodegi;
	NodeGI* selectedNodeGI;

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
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
};


// TeilUndAllesDoc.cpp : CTeilUndAllesDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "TeilUndAlles.h"
#endif

#include "TeilUndAllesDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTeilUndAllesDoc

IMPLEMENT_DYNCREATE(CTeilUndAllesDoc, CDocument)

BEGIN_MESSAGE_MAP(CTeilUndAllesDoc, CDocument)
END_MESSAGE_MAP()


// CTeilUndAllesDoc ����/�Ҹ�

CTeilUndAllesDoc::CTeilUndAllesDoc() : selectedNodeGI(NULL)
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CTeilUndAllesDoc::~CTeilUndAllesDoc()
{
	for (auto nodegi : set_nodegi)
	{
		delete nodegi;
	}
	set_nodegi.clear();
}

BOOL CTeilUndAllesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CTeilUndAllesDoc serialization

void CTeilUndAllesDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CTeilUndAllesDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CTeilUndAllesDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CTeilUndAllesDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CTeilUndAllesDoc ����

#ifdef _DEBUG
void CTeilUndAllesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTeilUndAllesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTeilUndAllesDoc ���

void CTeilUndAllesDoc::add_node(std::wstring nodename, CPoint& pt)
{
	Node* nodeentry = project.add_node(nodename);
	if (nodeentry == NULL)
	{
		AfxMessageBox(L"���� ���� ��尡 �̹� ����.");
	}
	else
		set_nodegi.insert(new NodeGI(pt, nodeentry));
}

bool CTeilUndAllesDoc::select_node(CPoint& pt)
{
	selectedNodeGI = NULL;
	for (auto itr = set_nodegi.begin(); itr != set_nodegi.end(); itr++)
	{
		RECT drawArea = (*itr)->getDrawArea();
		if (selectedNodeGI == NULL)
		{
			if (PtInRect(&drawArea, pt))
			{
				selectedNodeGI = (*itr);
				selectedNodeGI->setSelected();
			}
			else
				(*itr)->setSelected(false);
		}
		else
			(*itr)->setSelected(false);
	}

	return (selectedNodeGI != NULL);
}


// return
//  this function returns 1 if there are several selected GIs, -1 if selectedNodeGI is null, 0 if well selected.
int CTeilUndAllesDoc::validate_selection()
{
	int cnt = 0;
	for (auto itr = set_nodegi.begin(); itr != set_nodegi.end(); itr++)
	{
		if ((*itr)->isSelected())
		{
			cnt++;
		}
	}
	if (cnt == 1 && selectedNodeGI != NULL)
		return 1;

	if (cnt == 0 && selectedNodeGI == NULL)
		return 2;

	return 0;
}

void CTeilUndAllesDoc::remove_selected_node()
{
	UINT nodeid = (selectedNodeGI->getNode()->getid());
	if (project.remove_node(nodeid) < 0) {
		AfxMessageBox(L"���� ����");
		return;
	}

	delete selectedNodeGI;
	set_nodegi.erase(selectedNodeGI);
	selectedNodeGI = NULL;
}

void CTeilUndAllesDoc::add_dependency(UINT srcid, UINT dstid)
{
	project.structuring_dependence(StructuringType::CREATE, srcid, dstid);
}

bool CTeilUndAllesDoc::try_dragging(CPoint& pt)
{
	if (selectedNodeGI != NULL)
	{
		selectedNodeGI->dragging(pt);
		return true;
	}
	
	return false;
}

Project& CTeilUndAllesDoc::getProject()
{
	return project;
}

NodeGI* CTeilUndAllesDoc::get_selected_node()
{
	return selectedNodeGI;
}

std::set<NodeGI*>& CTeilUndAllesDoc::get_set_nodegi()
{
	return set_nodegi;
}

// TeilUndAllesDoc.cpp : CTeilUndAllesDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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


// CTeilUndAllesDoc 생성/소멸

CTeilUndAllesDoc::CTeilUndAllesDoc() : selectedNodeGI(NULL)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

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

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CTeilUndAllesDoc serialization

void CTeilUndAllesDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CTeilUndAllesDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CTeilUndAllesDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CTeilUndAllesDoc 진단

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


// CTeilUndAllesDoc 명령

void CTeilUndAllesDoc::add_node(std::wstring nodename, CPoint& pt)
{
	Node* nodeentry = project.add_node(nodename);
	if (nodeentry == NULL)
	{
		AfxMessageBox(L"같은 문제 노드가 이미 있음.");
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
		AfxMessageBox(L"개발 문제");
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
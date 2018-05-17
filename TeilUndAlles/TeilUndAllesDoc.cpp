
// TeilUndAllesDoc.cpp : CTeilUndAllesDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "TeilUndAlles.h"
#endif

#include "TeilUndAllesDoc.h"
#include "DeleteDependencyDlg.h"
#include "TeilUndAllesView.h"
#include "FrontendFileStructure.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTeilUndAllesDoc

IMPLEMENT_DYNCREATE(CTeilUndAllesDoc, CDocument)

BEGIN_MESSAGE_MAP(CTeilUndAllesDoc, CDocument)
END_MESSAGE_MAP()


// CTeilUndAllesDoc 생성/소멸

CTeilUndAllesDoc::CTeilUndAllesDoc() : selected_obj(NULL)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CTeilUndAllesDoc::~CTeilUndAllesDoc()
{
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
		unsigned char *project_data;
		UINT project_length;

		unsigned char *gi_data;
		UINT gi_length;

		project.export_project_to_buffer(&project_data, &project_length);
		
		export_graphic_interface(&gi_data, &gi_length);

		ar.Write(project_data, project_length);
		ar.Write(gi_data, gi_length);
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

int CTeilUndAllesDoc::possible_gi_id()
{
	UINT possible_id = 0;
	while(true)
	{
		if (used_id.find(possible_id) == used_id.end())break;
		possible_id++;
	}
	used_id.insert(possible_id);

	return possible_id;
}

void CTeilUndAllesDoc::add_node(std::wstring nodename, CPoint& pt)
{
	Node* nodeentry = project.add_node(nodename);
	if (nodeentry == NULL)
	{
		AfxMessageBox(L"같은 문제 노드가 이미 있음.");
	}
	else
	{
		NodeGI* node_gi = new NodeGI(possible_gi_id(), pt, nodeentry);
		set_nodegi.insert(node_gi);
	}
}

void CTeilUndAllesDoc::remove_selected_node()
{
	NodeGI* selectedNodeGI = NULL;
	if ((selectedNodeGI = dynamic_cast<NodeGI*>(selected_obj)) != NULL)
	{
		UINT nodeid = (selectedNodeGI->get_node()->getid());
		if (project.remove_node(nodeid) < 0) {
			AfxMessageBox(L"개발 문제");
			return;
		}

		used_id.erase(selectedNodeGI->get_id());
		delete selectedNodeGI;
		set_nodegi.erase(selectedNodeGI);
	}
}

void CTeilUndAllesDoc::add_dependency(UINT srcid, UINT dstid)
{
	Dependency* new_dependency;
	int res = project.structuring_dependency(StructuringType::CREATE, srcid, dstid, &new_dependency);
	if (res == 2)
	{
		DependencyGI* new_gi;
		if (new_dependency != NULL)
			new_gi = new DependencyGI(possible_gi_id(), new_dependency);
		else {
			AfxMessageBox(L"프로그래밍 버그, new_dependency = NULL");
			return;
		}


		for (auto node : set_nodegi)
		{
			UINT nodeid = node->get_node()->getid();
			if(nodeid == new_dependency->getid1())
				new_gi->set_pointer_for_id1(&node->get_point());
			else if(nodeid == new_dependency->getid2())
				new_gi->set_pointer_for_id2(&node->get_point());
		}

		set_dependencygi.insert(new_gi);
	}
}

void CTeilUndAllesDoc::remove_selected_dependency()
{
	DependencyGI* selectedDependencyGI = NULL;
	if ((selectedDependencyGI = dynamic_cast<DependencyGI*>(selected_obj)) != NULL)
	{
		Dependency* selected = selectedDependencyGI->get_dependency();

		UINT srcid, dstid;
		if (selected->has1to2() && selected->has2to1())
		{
			CDeleteDependencyDlg pDlg;
			pDlg.set_dependency(selected);

			int res = pDlg.DoModal();
			switch (res)
			{
			case 300:
				srcid = selected->getid1();
				dstid = selected->getid2();
				break;
			case 301:
				srcid = selected->getid2();
				dstid = selected->getid1();
				break;
			case 0:
				return;
			}
		}
		else if (selected->has1to2())
		{
			srcid = selected->getid1();
			dstid = selected->getid2();
		}
		else if (selected->has2to1())
		{
			srcid = selected->getid2();
			dstid = selected->getid1();
		}

		if (project.structuring_dependency(StructuringType::REMOVE, srcid, dstid, NULL) == 1)
		{
			used_id.erase(selectedDependencyGI->get_id());
			delete selectedDependencyGI;
			set_dependencygi.erase(selectedDependencyGI);
		}
	}
}

bool CTeilUndAllesDoc::try_dragging(CPoint& pt)
{
	if (selected_obj != NULL)
	{
		NodeGI* selected = dynamic_cast<NodeGI*>(selected_obj);
		if(selected != NULL) selected->dragging(pt);
		return true;
	}
	
	return false;
}

AbstractGraphicInterface* CTeilUndAllesDoc::select_interface(CPoint& pt)
{
	if (selected_obj != NULL)
	{
		selected_obj->init_selection();
		selected_obj = NULL;
	}

	for (auto nodegi : set_nodegi)
	{
		if (nodegi->select_interface(pt))
		{
			selected_obj = nodegi;
			return selected_obj;
		}
	}

	for (auto dependencygi : set_dependencygi)
	{
		if (dependencygi->select_interface(pt))
		{
			selected_obj = dependencygi;
			return selected_obj;
		}
	}

	return NULL;
}

void CTeilUndAllesDoc::export_graphic_interface(unsigned char** buffer_pointer, UINT* buffer_length)
{
	if (buffer_pointer == NULL || buffer_pointer == NULL)
	{
		AfxMessageBox(L"export graphic interface 함수 잘못 이용됨.");
		return;
	}
	GraphicInterfaceLayerHeader header;
	NodeGIDescriptor* nodegi_table = new NodeGIDescriptor[set_nodegi.size()];
	DependencyGIDescriptor* dependencygi_table = new DependencyGIDescriptor[set_dependencygi.size()];

	UINT header_length = sizeof(GraphicInterfaceLayerHeader);
	UINT nodegi_table_length = sizeof(NodeGIDescriptor) * set_nodegi.size();
	UINT dependencygi_table_length = sizeof(DependencyGIDescriptor) * set_dependencygi.size();

	header.gen_header.layertype = GI_FILE;
	header.gen_header.layerlength = header_length + nodegi_table_length + dependencygi_table_length;
	header.number_of_nodes = set_nodegi.size();
	header.number_of_dependency = set_dependencygi.size();
	header.selected_interface_id = selected_obj->get_id();

	int cnt = 0;
	for (auto nodegi : set_nodegi)
	{
		nodegi_table[cnt].id = nodegi->get_id();
		nodegi_table[cnt].node_id = nodegi->get_node()->getid();
		nodegi_table[cnt].x = nodegi->get_point().x;
		nodegi_table[cnt].y = nodegi->get_point().y;
		cnt++;
	}

	cnt = 0;
	for (auto dependencygi : set_dependencygi)
	{
		dependencygi_table[cnt].id = dependencygi->get_id();
		dependencygi_table[cnt].dependency_id = dependencygi->get_dependency()->getid();
	}

	unsigned char* layer_buffer = new unsigned char[header.gen_header.layerlength];
	unsigned int buffer_pos = 0;

	memcpy(layer_buffer + buffer_pos, (void*)&header, header_length);
	buffer_pos += header_length;

	memcpy(layer_buffer + buffer_pos, nodegi_table, nodegi_table_length);
	buffer_pos += nodegi_table_length;

	memcpy(layer_buffer + buffer_pos, dependencygi_table, dependencygi_table_length);
	buffer_pos += dependencygi_table_length;

	delete[] nodegi_table;
	delete[] dependencygi_table;

	*buffer_pointer = layer_buffer;
	*buffer_length = buffer_pos;
}

Project& CTeilUndAllesDoc::getProject()
{
	return project;
}

std::set<DependencyGI*>& CTeilUndAllesDoc::get_set_dependencygi()
{
	return set_dependencygi;
}

std::set<NodeGI*>& CTeilUndAllesDoc::get_set_nodegi()
{
	return set_nodegi;
}

void CTeilUndAllesDoc::DeleteContents()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	for (auto nodegi : set_nodegi)
	{
		delete nodegi;
	}
	for (auto dependencygi : set_dependencygi)
	{
		delete dependencygi;
	}

	CDocument::DeleteContents();
}

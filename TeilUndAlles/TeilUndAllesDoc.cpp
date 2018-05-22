
// TeilUndAllesDoc.cpp : CTeilUndAllesDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "TeilUndAlles.h"
#endif

#include "TeilUndAllesDoc.h"
#include "DeleteDependencyDlg.h"
#include "TeilUndAllesView.h"

#include "GraphFileStructure.h"
#include "FrontendFileStructure.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTeilUndAllesDoc

IMPLEMENT_DYNCREATE(CTeilUndAllesDoc, CDocument)

BEGIN_MESSAGE_MAP(CTeilUndAllesDoc, CDocument)
END_MESSAGE_MAP()


// CTeilUndAllesDoc ����/�Ҹ�

CTeilUndAllesDoc::CTeilUndAllesDoc() : selected_obj(NULL)
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CTeilUndAllesDoc::~CTeilUndAllesDoc()
{
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
		unsigned char *project_data;
		UINT project_length;

		unsigned char *gi_data;
		UINT gi_length;

		project.export_project_to_buffer(&project_data, &project_length);
		
		export_graphic_interface(&gi_data, &gi_length);

		ar.Write(project_data, project_length);
		ar.Write(gi_data, gi_length);

		delete[] project_data;
		delete[] gi_data;
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
		CFile* file = ar.GetFile();
		while (true)
		{
			LayerHeader gen_header;
			if (!file->Read((void*)&gen_header, sizeof(LayerHeader)))break;
			file->Seek(-(int)(sizeof(LayerHeader)), CFile::current);

			unsigned char* buffer = new unsigned char[gen_header.layerlength];
			file->Read(buffer, gen_header.layerlength);

			switch (gen_header.layertype)
			{
			case GRAPH_FILE:
				project.import_project_from_buffer(buffer);
				break;
			case GI_FILE:
				import_graphic_interface(buffer);
				break;
			}

			delete[] buffer;
		}
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

UINT CTeilUndAllesDoc::possible_gi_id()
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

void CTeilUndAllesDoc::add_node(CPoint& pt)
{
	Node* nodeentry = project.add_node(L"");
	if (nodeentry == NULL)
	{
		AfxMessageBox(L"���� ���� ��尡 �̹� ����.");
	}
	else
	{
		UINT id = possible_gi_id();
		NodeGI* node_gi = new NodeGI(id, pt, nodeentry);
		set_nodegi[id] = node_gi;
	}
}

void CTeilUndAllesDoc::remove_selected_node()
{
	NodeGI* selectedNodeGI = NULL;
	if ((selectedNodeGI = dynamic_cast<NodeGI*>(selected_obj)) != NULL)
	{
		UINT nodeid = (selectedNodeGI->get_node()->getid());

		//delete all dependency connected with the selected node
		std::vector<std::unordered_map<UINT, DependencyGI*>::iterator> deleting_list;
		for (auto itr = set_dependencygi.begin(); itr != set_dependencygi.end(); itr++)
		{
			Dependency* dep_entry = itr->second->get_dependency();
			if (dep_entry->getid1() == nodeid || dep_entry->getid2() == nodeid)
			{
				deleting_list.push_back(itr);
			}
		}

		for (auto itr : deleting_list)
		{
			set_dependencygi.erase(itr);
		}

		if (project.remove_node(nodeid) < 0) {
			AfxMessageBox(L"���� ����");
			return;
		}

		UINT id = selectedNodeGI->get_id();
		used_id.erase(id);
		delete selectedNodeGI;
		set_nodegi.erase(id);
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
			AfxMessageBox(L"���α׷��� ����, new_dependency = NULL");
			return;
		}


		for (auto node : set_nodegi)
		{
			UINT nodeid = node.second->get_node()->getid();
			if(nodeid == new_dependency->getid1())
				new_gi->set_pointer_for_id1(&node.second->get_point());
			else if(nodeid == new_dependency->getid2())
				new_gi->set_pointer_for_id2(&node.second->get_point());
		}

		set_dependencygi[new_gi->get_id()] = new_gi;
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
			UINT id = selectedDependencyGI->get_id();
			used_id.erase(id);
			delete selectedDependencyGI;
			set_dependencygi.erase(id);
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
		if (nodegi.second->select_interface(pt))
		{
			selected_obj = nodegi.second;
			return selected_obj;
		}
	}

	for (auto dependencygi : set_dependencygi)
	{
		if (dependencygi.second->select_interface(pt))
		{
			selected_obj = dependencygi.second;
			return selected_obj;
		}
	}

	return NULL;
}

std::unordered_map<UINT, NodeGI*>& CTeilUndAllesDoc::get_set_nodegi()
{
	return set_nodegi;
}

std::unordered_map<UINT, DependencyGI*>& CTeilUndAllesDoc::get_set_dependencygi()
{
	return set_dependencygi;
}

void CTeilUndAllesDoc::export_graphic_interface(unsigned char** buffer_pointer, UINT* buffer_length)
{
	if (buffer_pointer == NULL || buffer_pointer == NULL)
	{
		AfxMessageBox(L"export graphic interface �Լ� �߸� �̿��.");
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
	header.selected_interface_id = selected_obj == NULL ? -1 : selected_obj->get_id();

	int cnt = 0;
	for (auto nodegi : set_nodegi)
	{
		nodegi_table[cnt].id = nodegi.second->get_id();
		nodegi_table[cnt].node_id = nodegi.second->get_node()->getid();
		nodegi_table[cnt].x = nodegi.second->get_point().x;
		nodegi_table[cnt].y = nodegi.second->get_point().y;
		cnt++;
	}

	cnt = 0;
	for (auto dependencygi : set_dependencygi)
	{
		dependencygi_table[cnt].id = dependencygi.second->get_id();
		dependencygi_table[cnt].dependency_id = dependencygi.second->get_dependency()->getid();
		cnt++;
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

void CTeilUndAllesDoc::import_graphic_interface(unsigned char* buffer)
{
	unsigned int buffer_pos = 0;
	GraphicInterfaceLayerHeader* header = (GraphicInterfaceLayerHeader*)(buffer+buffer_pos);
	buffer_pos += sizeof(GraphicInterfaceLayerHeader);

	NodeGIDescriptor* nodegi_table = (NodeGIDescriptor*)(buffer + buffer_pos);
	buffer_pos += sizeof(NodeGIDescriptor) * header->number_of_nodes;

	DependencyGIDescriptor* dependencygi_table = (DependencyGIDescriptor*)(buffer + buffer_pos);
	buffer_pos += sizeof(DependencyGIDescriptor) * header->number_of_dependency;


	// creation of nodes
	for (int i = 0; i < header->number_of_nodes; i++)
	{
		NodeGI* new_node = NodeGI::deserialize(nodegi_table + i,
			project.get_node_from_id(nodegi_table[i].node_id),
			header->selected_interface_id == nodegi_table[i].id);

		set_nodegi[new_node->get_id()] = new_node;
		used_id.insert(new_node->get_id());
	}

	// creation of dependency
	for (int i = 0; i < header->number_of_dependency; i++)
	{
		DependencyGI* new_dep = DependencyGI::deserialize(dependencygi_table + i,
			project.get_dependency(dependencygi_table[i].dependency_id),
			header->selected_interface_id == dependencygi_table[i].id);

		Dependency* entry = new_dep->get_dependency();
		for (auto node : set_nodegi)
		{
			UINT nodeid = node.second->get_node()->getid();
			if (nodeid == entry->getid1())
				new_dep->set_pointer_for_id1(&node.second->get_point());
			else if (nodeid == entry->getid2())
				new_dep->set_pointer_for_id2(&node.second->get_point());
		}

		set_dependencygi[new_dep->get_id()] = new_dep;
		used_id.insert(new_dep->get_id());
	}
}

Project& CTeilUndAllesDoc::getProject()
{
	return project;
}

void CTeilUndAllesDoc::DeleteContents()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	for (auto nodegi : set_nodegi)
	{
		delete nodegi.second;
	}
	for (auto dependencygi : set_dependencygi)
	{
		delete dependencygi.second;
	}

	CDocument::DeleteContents();
}

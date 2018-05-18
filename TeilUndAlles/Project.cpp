#include "stdafx.h"
#include "Project.h"
#include "GraphFileStructure.h"
#include <vector>


Project::Project() : node_auto_increment(0), dep_auto_increment(0)
{
}

Project::~Project()
{
	for (auto node : all_nodes_by_id)
	{
		delete node.second;
	}
	all_nodes_by_id.clear();
	all_nodes_by_name.clear();

	for (auto dependency : all_dependencies)
	{
		delete dependency.second;
	}
	all_dependencies.clear();
}

Node* Project::add_node(std::wstring nodename)
{
	auto finder = all_nodes_by_name.find(nodename);
	if (finder != all_nodes_by_name.end()) return NULL;

	while (true)
	{
		auto id_finder = all_nodes_by_id.find(node_auto_increment);
		if (id_finder == all_nodes_by_id.end()) break;
		node_auto_increment++;
	}

	Node* new_node = new Node(node_auto_increment, nodename);
	all_nodes_by_id[node_auto_increment] = new_node;
	all_nodes_by_name[nodename] = new_node;

	return new_node;
}

void Project::remove_all_dependency_for_node(UINT nodeid)
{
	std::vector<std::unordered_map<UINT, Dependency*>::iterator> all_dependencies_deleted;
	for (auto itr = all_dependencies.begin(); itr != all_dependencies.end(); itr++)
	{
		if(itr->second->getid1() == nodeid || itr->second->getid2() == nodeid)
			all_dependencies_deleted.push_back(itr);
	}

	for (auto itr : all_dependencies_deleted)
	{
		all_dependencies.erase(itr);
	}
}

int Project::remove_node(std::wstring nodename)
{
	auto name_finder = all_nodes_by_name.find(nodename);
	if (name_finder == all_nodes_by_name.end()) return -1;

	UINT id = name_finder->second->getid();
	remove_all_dependency_for_node(id);

	delete name_finder->second;
	all_nodes_by_name.erase(nodename);
	all_nodes_by_id.erase(id);

	return 0;
}

int Project::remove_node(UINT id)
{
	auto id_finder = all_nodes_by_id.find(id);
	if (id_finder == all_nodes_by_id.end()) return -1;

	Node* node = id_finder->second;
	std::wstring nodename = node->getnodename();
	remove_all_dependency_for_node(id);

	all_nodes_by_name.erase(nodename);
	all_nodes_by_id.erase(id);
	delete node;

	return 0;
}

int Project::structuring_dependency(StructuringType type, std::wstring src_nodename, std::wstring dst_nodename, Dependency** created)
{
	auto src_finder = all_nodes_by_name.find(src_nodename);
	if (src_finder == all_nodes_by_name.end()) return -1;

	auto dst_finder = all_nodes_by_name.find(dst_nodename);
	if (dst_finder == all_nodes_by_name.end()) return -2;


	UINT srcid = src_finder->second->getid();
	UINT dstid = dst_finder->second->getid();

	return structuring_dependency(type, srcid, dstid, created);
}

int Project::structuring_dependency(StructuringType type, UINT srcid, UINT dstid, Dependency** created)
{
	auto src_finder = all_nodes_by_id.find(srcid);
	if (src_finder == all_nodes_by_id.end()) return -1;
	
	auto dst_finder = all_nodes_by_id.find(dstid);
	if (dst_finder == all_nodes_by_id.end()) return -2;


	if (type == StructuringType::CREATE)
	{
		Dependency* dependency = new Dependency(dep_auto_increment, srcid, dstid);

		int flag = 0;
		for (auto dependency_entry : all_dependencies)
		{
			if (*(dependency_entry.second) == *dependency)
			{
				delete dependency;
				dependency = dependency_entry.second;
				flag = 1;
				break;
			}
		}
		if (!flag)
		{
			all_dependencies[dep_auto_increment++] = (dependency);
		}
		dependency->construct_direction(DirectionConstruct::CREATE, srcid, dstid);
		if (created != NULL) *created = dependency;
		if (!flag) return 2;
	}
	else if (type == StructuringType::REMOVE)
	{
		Dependency dependency(0, srcid, dstid);
		int flag = 0;
		for (auto dependency_entry : all_dependencies)
		{
			if (*dependency_entry.second == dependency)
			{
				dependency_entry.second->construct_direction(DirectionConstruct::REMOVE, srcid, dstid);
				if (dependency_entry.second->has_no_direction())
				{
					all_dependencies.erase(dependency_entry.second->getid());
					delete dependency_entry.second;
					return 1;
				}
			}
		}
	}

	return 0;
}

int Project::modify_dependency(ModifyingType type, std::wstring src_nodename, std::wstring dst_nodename, std::wstring changed)
{
	auto elem_checker = all_nodes_by_name.find(changed);
	if (elem_checker == all_nodes_by_name.end()) return -3;

	int res = structuring_dependency(StructuringType::REMOVE, src_nodename, dst_nodename, NULL);
	if (res) return res;

	if (type == ModifyingType::SRC)
		res = structuring_dependency(StructuringType::CREATE, changed, dst_nodename, NULL);
	else if (type == ModifyingType::DST)
		res = structuring_dependency(StructuringType::CREATE, src_nodename, dst_nodename, NULL);

	if (res) return res;

	return 0;
}

int Project::modify_dependency(ModifyingType type, UINT srcid, UINT dstid, UINT changed)
{
	auto elem_checker = all_nodes_by_id.find(changed);
	if (elem_checker == all_nodes_by_id.end()) return -3;

	int res = structuring_dependency(StructuringType::REMOVE, srcid, dstid, NULL);
	if (res) return res;

	if (type == ModifyingType::SRC)
		res = structuring_dependency(StructuringType::CREATE, changed, dstid, NULL);
	else if (type == ModifyingType::DST)
		res = structuring_dependency(StructuringType::CREATE, srcid, changed, NULL);

	if (res) return res;

	return 0;
}

Node* Project::get_node_from_name(std::wstring nodename)
{
	if (all_nodes_by_name.find(nodename) == all_nodes_by_name.end()) return NULL;

	return all_nodes_by_name[nodename];
}

Node* Project::get_node_from_id(UINT id)
{
	if (all_nodes_by_id.find(id) == all_nodes_by_id.end()) return NULL;
	return all_nodes_by_id[id];
}

Dependency* Project::get_dependency(UINT id)
{
	if (all_dependencies.find(id) == all_dependencies.end()) return NULL;
	return all_dependencies[id];
}


int Project::export_project_to_buffer(unsigned char** buffer_pointer, UINT* length)
{
	GraphProjectLayerHeader header;
	NodeDescriptor* node_table = new NodeDescriptor[all_nodes_by_id.size()];
	DependencyDescriptor* dependency_table = new DependencyDescriptor[all_dependencies.size()];

	uint_32 header_len = sizeof(GraphProjectLayerHeader);
	uint_32 node_table_len = sizeof(NodeDescriptor) * all_nodes_by_id.size();
	uint_32 dependency_table_len = sizeof(DependencyDescriptor) * all_dependencies.size();

	uint_32 core_data_len = header_len + node_table_len + dependency_table_len;

	header.gen_header.layertype = GRAPH_FILE;
	header.gen_header.layerlength = 0;						//unknown
	header.number_of_nodes = all_nodes_by_id.size();
	header.number_of_dependency = all_dependencies.size();

	uint_32 relative_string_pos = 0;
	uint_32 relative_data_pos = 0;
	int node_cnt = 0;
	for (auto node : all_nodes_by_id)
	{
		std::wstring nodename = node.second->getnodename();

		node_table[node_cnt].node_id = node.second->getid();
		node_table[node_cnt].location_of_name = relative_string_pos;
		node_table[node_cnt].location_of_gen_data = relative_data_pos;
		
		relative_string_pos += (nodename.length()+1)*sizeof(wchar_t); //include delimiter
		relative_data_pos += node.second->general_data.get_serializing_length();

		node_cnt++;
	}

	uint_32 total_string_table_len = relative_string_pos;
	uint_32 total_data_table_len = relative_data_pos;

	header.gen_header.layerlength = header_len + node_table_len + dependency_table_len + total_string_table_len + total_data_table_len;


	unsigned char *string_table = new unsigned char[total_string_table_len];
	unsigned char *general_data_table = new unsigned char[total_data_table_len];

	relative_string_pos = 0;
	relative_data_pos = 0;
	node_cnt = 0;
	for (auto node : all_nodes_by_id)
	{
		node_table[node_cnt].location_of_name += core_data_len;
		node_table[node_cnt++].location_of_gen_data += core_data_len + total_string_table_len;

		std::wstring nodename = node.second->getnodename();
		int namelength = sizeof(wchar_t) * nodename.length();
		memcpy(string_table + relative_string_pos, nodename.c_str(), namelength);
		relative_string_pos += namelength;
		*((wchar_t*)(string_table + relative_string_pos)) = 0;
		relative_string_pos += sizeof(wchar_t);

		unsigned char* gen_data;
		int datalength = node.second->general_data.get_serializing_length();
		if (node.second->general_data.serialize_all(&gen_data) == -1) return -1;
		memcpy(general_data_table + relative_data_pos, gen_data, datalength);
		relative_data_pos += datalength;
		delete gen_data;
	}


	int dependency_cnt = 0;
	for (auto dependency : all_dependencies)
	{
		Dependency* depen = dependency.second;
		dependency_table[dependency_cnt].id = depen->getid();
		dependency_table[dependency_cnt].node_id1 = depen->getid1();
		dependency_table[dependency_cnt].node_id2 = depen->getid2();
		dependency_table[dependency_cnt].direction = depen->get_direction();
		dependency_cnt++;
	}

	unsigned char* layer_buffer = new unsigned char[header.gen_header.layerlength];
	unsigned int buffer_pos = 0;
	memcpy(layer_buffer+buffer_pos, (void*)&header, header_len);
	buffer_pos += header_len;

	memcpy(layer_buffer+buffer_pos, node_table, node_table_len);
	buffer_pos += node_table_len;

	memcpy(layer_buffer + buffer_pos, dependency_table, dependency_table_len);
	buffer_pos += dependency_table_len;

	memcpy(layer_buffer + buffer_pos, string_table, total_string_table_len);
	buffer_pos += total_string_table_len;

	memcpy(layer_buffer + buffer_pos, general_data_table, total_data_table_len);
	buffer_pos += total_data_table_len;

	delete[] node_table;
	delete[] dependency_table;
	delete[] string_table;
	delete[] general_data_table;

	*buffer_pointer = layer_buffer;
	*length = buffer_pos;

	return 0;
}

int Project::import_project_from_buffer(unsigned char* buffer)
{
	unsigned int buffer_pos = 0;

	GraphProjectLayerHeader *header = (GraphProjectLayerHeader*)(buffer+buffer_pos);
	buffer_pos += sizeof(GraphProjectLayerHeader);

	NodeDescriptor* nodes_table = (NodeDescriptor*)(buffer + buffer_pos);
	buffer_pos += sizeof(NodeDescriptor) * header->number_of_nodes;

	DependencyDescriptor* dependency_table = (DependencyDescriptor*)(buffer + buffer_pos);
	buffer_pos += sizeof(DependencyDescriptor) * header->number_of_dependency;


	// creation of nodes
	for (int i = 0; i < header->number_of_nodes; i++)
	{
		Node* new_node = Node::deserialize_from_descriptor(nodes_table + i, buffer);
		if (new_node == NULL) return -1;

		all_nodes_by_id[new_node->getid()] = new_node;
		all_nodes_by_name[new_node->getnodename()] = new_node;
	}

	// creation of dependencies
	for (int i = 0; i < header->number_of_dependency; i++)
	{
		Dependency* new_dependency = Dependency::deserialize_from_descriptor(dependency_table + i);
		if (new_dependency == NULL) return -1;

		all_dependencies[new_dependency->getid()] = new_dependency;
	}
	
	
	return 0;
}
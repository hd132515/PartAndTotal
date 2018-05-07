#include "stdafx.h"
#include "Project.h"
#include <vector>

Dependency::Dependency()
{
}

Dependency::Dependency(UINT _srcid, UINT _dstid) : srcid(_srcid), dstid(_dstid)
{
}

bool Dependency::operator <(const Dependency& dependency) const
{
	return (srcid < dependency.srcid) || (srcid == dependency.srcid && dstid < dependency.dstid);
}

Project::Project() : auto_id_counter(0)
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
}

// parameters
// * std::wstring nodename : the name of node to be added in project
// return value
// * NULL : if there is a node whose name is <nodename>.
// * Node* [not null] : the new node pointer
Node* Project::add_node(std::wstring nodename)
{
	auto finder = all_nodes_by_name.find(nodename);
	if (finder == all_nodes_by_name.end()) return NULL;

	while (true)
	{
		auto id_finder = all_nodes_by_id.find(auto_id_counter);
		if (id_finder != all_nodes_by_id.end()) break;
		auto_id_counter++;
	}

	Node* new_node = new Node(auto_id_counter, nodename);
	all_nodes_by_id[auto_id_counter] = new_node;
	all_nodes_by_name[nodename] = new_node;
}

// parameters
// * Node* node : the node being removed
void Project::remove_all_dependency_for_node(UINT nodeid)
{
	std::vector<std::set<Dependency>::iterator> all_dependencies_deleted;
	for (auto itr = all_dependencies.begin(); itr != all_dependencies.end(); itr++)
	{
		if (itr->srcid == nodeid)
			all_dependencies_deleted.push_back(itr);
	}

	for (auto itr : all_dependencies_deleted)
	{
		all_dependencies.erase(itr);
	}
}

// parameters
// * std::wstring nodename : the name of node to be removed in this project
// return value
// * -1 : the node whose name is <nodename> is not existing node in this project.
// * 0 : success
int Project::remove_node(std::wstring nodename)
{
	auto name_finder = all_nodes_by_name.find(nodename);
	if (name_finder == all_nodes_by_name.end()) return -1;

	UINT id = name_finder->second->getid();
	remove_all_dependency_for_node(id);

	delete name_finder->second;
	all_nodes_by_name.erase(nodename);
	all_nodes_by_id.erase(id);
}

// parameters
// * UINT id : the identifier of node to be removed in this project
// return value
// * -1 : the node whose identifier is <id> is not existing node in this project.
// * 0 : success
int Project::remove_node(UINT id)
{
	auto id_finder = all_nodes_by_id.find(id);
	if (id_finder == all_nodes_by_id.end()) return -1;

	std::wstring nodename = id_finder->second->getnodename();
	remove_all_dependency_for_node(id);

	delete id_finder->second;
	all_nodes_by_name.erase(nodename);
	all_nodes_by_id.erase(id);
}

// parameters
// * StructuringType type : dependency can be structured by two ways. One wat is creating, otherwise remove.
// * std::wstring src_nodename : the name of a node that is sub problem node
// * std::wstring dst_nodename : the name of a node that is main problem node
// return value
// * 2 : not existing dependency to remove
// * 1 : already existing dependency to create
// * 0 : success
// * -1 : the first parameter is not a identifier of existing node.
// * -2 : the second parameter is not a identifier of existing node.
int Project::structuring_dependency(StructuringType type, std::wstring src_nodename, std::wstring dst_nodename)
{
	auto src_finder = all_nodes_by_name.find(src_nodename);
	if (src_finder == all_nodes_by_name.end()) return -1;

	auto dst_finder = all_nodes_by_name.find(dst_nodename);
	if (dst_finder == all_nodes_by_name.end()) return -2;


	UINT srcid = src_finder->second->getid();
	UINT dstid = dst_finder->second->getid();
	if (type == StructuringType::CREATE)
	{
		auto emplace_info = all_dependencies.emplace(srcid, dstid);
		if (!emplace_info.second) return 1;
		last_created_dependency = *emplace_info.first;
	}
	else if (type == StructuringType::REMOVE)
	{
		auto erased = all_dependencies.erase(Dependency(srcid, srcid));
		if (erased == 0)  return 2;
	}

	return 0;
}

// parameters
// * StructuringType type : dependency can be structured by two ways. One wat is creating, otherwise remove.
// * UINT srcid : the identifier of node that is sub problem node
// * UINT dstid : the identifier of node that is main problem node
// return value
// * 2 : not existing dependency to remove
// * 1 : already existing dependency to create
// * 0 : success
// * -1 : the first parameter is not a identifier of existing node.
// * -2 : the second parameter is not a identifier of existing node.
int Project::structuring_dependency(StructuringType type, UINT srcid, UINT dstid)
{
	auto src_finder = all_nodes_by_id.find(srcid);
	if (src_finder == all_nodes_by_id.end()) return -1;
	
	auto dst_finder = all_nodes_by_id.find(dstid);
	if (dst_finder == all_nodes_by_id.end()) return -2;

	if (type == StructuringType::CREATE)
	{
		auto emplace_info = all_dependencies.emplace(srcid, dstid);
		if (!emplace_info.second) return 1;
		last_created_dependency.srcid = srcid;
		last_created_dependency.dstid = dstid;
	}
	else if (type == StructuringType::REMOVE)
	{
		auto erased = all_dependencies.erase(Dependency(srcid, srcid));
		if (erased == 0)  return 2;
	}

	return 0;
}

// parameters
// * std::wstring src_nodename : the name of sub-problem node to be changed
// * std::wstring dst_nodename : the name of main-problem node
// * std::wstring changed : the name of sub-problem node replcaing
// return value
// * 1 : no dependency between <src_nodename> and <dst_nodename>
// * 0 : success
// * -1 : there is a no node whose name is <src_nodename>
// * -2 : there is a no node whose name is <dst_nodename>
// * -3 : there is a no node whose name is <changed>
int Project::modify_dependency(ModifyingType type, std::wstring src_nodename, std::wstring dst_nodename, std::wstring changed)
{
	auto elem_checker = all_nodes_by_name.find(changed);
	if (elem_checker == all_nodes_by_name.end()) return -3;

	int res = structuring_dependency(StructuringType::REMOVE, src_nodename, dst_nodename);
	if (res) return res;

	if (type == ModifyingType::SRC)
		res = structuring_dependency(StructuringType::CREATE, changed, dst_nodename);
	else if (type == ModifyingType::DST)
		res = structuring_dependency(StructuringType::CREATE, src_nodename, dst_nodename);

	if (res) return res;

	return 0;
}

// parameters
// * UINT srcid : the identifier of sub-problem node to be changed
// * UINT dstid : the identifier of main-problem node
// * UINT changed : the identifier of sub-problem node replacing
// return value
// * -1 : there is a no node whose identifier is <srcid>
// * -2 : there is a no node whose identifier is <dstid>
// * -3 : there is a no node whose identifier is <changed>
// * 0 ; success
int Project::modify_dependency(ModifyingType type, UINT srcid, UINT dstid, UINT changed)
{
	auto elem_checker = all_nodes_by_id.find(changed);
	if (elem_checker == all_nodes_by_id.end()) return -3;

	int res = structuring_dependency(StructuringType::REMOVE, srcid, dstid);
	if (res) return res;

	if (type == ModifyingType::SRC)
		res = structuring_dependency(StructuringType::CREATE, changed, dstid);
	else if (type == ModifyingType::DST)
		res = structuring_dependency(StructuringType::CREATE, srcid, changed);

	if (res) return res;

	return 0;
}

Dependency Project::get_last_created_dependency()
{
	return last_created_dependency;
}

// parameters
// * std::wstring nodename : the name of node to get
// return value
//  return NULL if there is a no node whose name is <nodename>, otherwise node pointer
Node* Project::get_node_from_name(std::wstring nodename)
{
	if (all_nodes_by_name.find(nodename) == all_nodes_by_name.end()) return NULL;

	return all_nodes_by_name[nodename];
}

// parameters
// * std::wstring nodename : the name of node to get
// return value
//  return NULL if there is a no node whose name is <nodename>, otherwise node pointer
Node* Project::get_node_from_id(UINT id)
{
	if (all_nodes_by_id.find(id) == all_nodes_by_id.end()) return NULL;
	return all_nodes_by_id[id];
}
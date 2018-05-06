#include "stdafx.h"
#include "Project.h"

Project::Project() : auto_id_counter(0)
{
}

Project::~Project()
{
	for (auto node : all_nodes)
	{
		delete node;
	}
}

// parameters
// * std::wstring nodename : the name of node to be added in project
// return value
// * NULL : if nodename is already existing nodename in all nodes
// * New node pointer : success to add node
Node* Project::add_node(std::wstring nodename)
{
	auto uq_name_check = all_names.insert(nodename);
	if (!uq_name_check.second) return NULL;

	while (true)
	{
		auto uq_id_check = all_ids.insert(auto_id_counter++);
		if (uq_name_check.second) {
			Node* newnode = new Node(auto_id_counter - 1, nodename);
			all_nodes.insert(newnode);
			return newnode;
		}
	}
}

// parameters
// * Node* node : the node being removed
void Project::remove_all_dependency_for_node(Node* node)
{
	auto inbound = node->getInbound();
	auto outbound = node->getOutbound();

	for (auto outnode : outbound)
	{
		structuring_dependence(StructuringType::REMOVE, node->getid(), outnode);
	}

	for (auto innode : inbound)
	{
		structuring_dependence(StructuringType::REMOVE, innode, node->getid());
	}
}

// parameters
// * std::wstring nodename : the name of node to be removed in this project
// return value
// * -1 : the node whose name is <nodename> is not existing node in this project.
// * 0 : success
int Project::remove_node(std::wstring nodename)
{
	auto removed = all_names.erase(nodename);
	if (removed == 0) return -1;
	else {
		for (auto itr = all_nodes.begin(); itr != all_nodes.end(); itr++)
		{
			if ((*itr)->getnodename() == nodename)
			{
				all_ids.erase((*itr)->getid());
				remove_all_dependency_for_node(*itr);
				delete (*itr);
				all_nodes.erase(itr);
				return 0;
			}
		}
		return -1;
	}
}

// parameters
// * UINT id : the identifier of node to be removed in this project
// return value
// * -1 : the node whose identifier is <id> is not existing node in this project.
// * 0 : success
int Project::remove_node(UINT id)
{
	auto removed = all_ids.erase(id);
	if (removed == 0) return -1;
	else {
		for (auto itr = all_nodes.begin(); itr != all_nodes.end(); itr++)
		{
			if ((*itr)->getid() == id)
			{
				all_names.erase((*itr)->getnodename());
				remove_all_dependency_for_node(*itr);
				delete (*itr);
				all_nodes.erase(itr);
				return 0;
			}
		}
		return -1;
	}
}

// parameters
// * StructuringType type : dependence can be structured by two ways. One wat is creating, otherwise remove.
// * std::wstring src_nodename : the name of a node that is sub problem node
// * std::wstring dst_nodename : the name of a node that is main problem node
// return value
// * -1 : first parameter is the name of non-existing node.
// * -2 : second parameter is the name of non-existing node.
// * 0 : success
int Project::structuring_dependence(StructuringType type, std::wstring src_nodename, std::wstring dst_nodename)
{
	auto elem_checker = all_names.find(src_nodename);
	if (elem_checker == all_names.end()) return -1;

	elem_checker = all_names.find(dst_nodename);
	if (elem_checker == all_names.end()) return -2;

	Node *source = NULL, *destination = NULL;
	for (auto itr = all_nodes.begin(); itr != all_nodes.end(); itr++)
	{
		std::wstring nodename = (*itr)->getnodename();

		if (nodename == src_nodename)
		{
			source = *itr;
		}
		else if (nodename == dst_nodename)
		{
			destination = *itr;
		}

		if (source != NULL && destination != NULL)
			break;
	}

	if (type == StructuringType::CREATE)
	{
		source->add_outbound_node(destination->getid());
		destination->add_inbound_node(source->getid());
	}
	else if (type == StructuringType::REMOVE)
	{
		source->remove_outbound_node(destination->getid());
		destination->remove_inbound_node(source->getid());
	}

	return 0;
}

// parameters
// * StructuringType type : dependence can be structured by two ways. One wat is creating, otherwise remove.
// * UINT srcid : the identifier of node that is sub problem node
// * UINT dstid : the identifier of node that is main problem node
// return value
// * -1 : the first parameter is not a identifier of existing node.
// * -2 : the second parameter is not a identifier of existing node.
// * 0 : success
int Project::structuring_dependence(StructuringType type, UINT srcid, UINT dstid)
{
	auto elem_checker = all_ids.find(srcid);
	if (elem_checker == all_ids.end()) return -1;

	elem_checker = all_ids.find(dstid);
	if (elem_checker == all_ids.end()) return -2;


	int task_checker = 0;
	for (auto itr = all_nodes.begin(); itr != all_nodes.end(); itr++)
	{
		UINT id = (*itr)->getid();

		if (id == srcid)
		{
			if (type == StructuringType::CREATE)
				(*itr)->add_outbound_node(dstid);
			else if (type == StructuringType::REMOVE)
				(*itr)->remove_outbound_node(dstid);
			task_checker++;
		}
		else if (id == dstid)
		{
			if (type == StructuringType::CREATE)
				(*itr)->add_inbound_node(srcid);
			else if (type == StructuringType::REMOVE)
				(*itr)->remove_inbound_node(srcid);
			task_checker++;
		}

		if (task_checker == 2)
			return 0;
	}

	return -1;
}

// parameters
// * std::wstring src_nodename : the name of sub-problem node to be changed
// * std::wstring dst_nodename : the name of main-problem node
// * std::wstring changed : the name of sub-problem node replcaing
// return value
// * -1 : there is a no node whose name is <src_nodename>
// * -2 : there is a no node whose name is <dst_nodename>
// * -3 : there is a no node whose name is <changed>
// * 0 : success
int Project::modify_dependence(ModifyingType type, std::wstring src_nodename, std::wstring dst_nodename, std::wstring changed)
{
	auto elem_checker = all_names.find(changed);
	if (elem_checker == all_names.end()) return -3;

	int res = structuring_dependence(StructuringType::REMOVE, src_nodename, dst_nodename);
	if (res) return res;

	if (type == ModifyingType::SRC)
		res = structuring_dependence(StructuringType::CREATE, changed, dst_nodename);
	else if (type == ModifyingType::DST)
		res = structuring_dependence(StructuringType::CREATE, src_nodename, dst_nodename);

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
int Project::modify_dependence(ModifyingType type, UINT srcid, UINT dstid, UINT changed)
{
	auto elem_checker = all_ids.find(changed);
	if (elem_checker == all_ids.end()) return -3;

	int res = structuring_dependence(StructuringType::REMOVE, srcid, dstid);
	if (res) return res;

	if (type == ModifyingType::SRC)
		res = structuring_dependence(StructuringType::CREATE, changed, dstid);
	else if (type == ModifyingType::DST)
		res = structuring_dependence(StructuringType::CREATE, srcid, changed);

	if (res) return res;

	return 0;
}

// parameters
// * std::wstring nodename : the name of node to get
// return value
//  return NULL if there is a no node whose name is <nodename>, otherwise node pointer
const Node* Project::get_node_from_name(std::wstring nodename)
{
	auto elem_checker = all_names.find(nodename);
	if (elem_checker == all_names.end()) return NULL;

	for (auto node : all_nodes)
	{
		if (node->getnodename() == nodename)
			return node;
	}

	return NULL;
}

// parameters
// * std::wstring nodename : the name of node to get
// return value
//  return NULL if there is a no node whose name is <nodename>, otherwise node pointer
const Node* Project::get_node_from_id(UINT id)
{
	auto elem_checker = all_ids.find(id);
	if (elem_checker == all_ids.end()) return NULL;

	for (auto node : all_nodes)
	{
		if (node->getid() == id)
			return node;
	}

	return NULL;
}
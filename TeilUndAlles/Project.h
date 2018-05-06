#pragma once

#include <set>
#include "Node.h"

enum class StructuringType
{
	CREATE, REMOVE
};

enum class ModifyingType
{
	SRC, DST
};

class Project
{
public:
	Project();
	~Project();

	//member variables' area
private:
	UINT auto_id_counter;
	std::set<Node*> all_nodes;
	std::set<UINT> all_ids;
	std::set<std::wstring> all_names;
protected:
public:
	
	//member functions' area
private:
	void remove_all_dependency_for_node(Node* node);
protected:
public:
	Node* add_node(std::wstring nodename);
	int remove_node(std::wstring nodename);
	int remove_node(UINT id);

	int structuring_dependence(StructuringType type, std::wstring src_nodename, std::wstring dst_nodename);
	int structuring_dependence(StructuringType type, UINT srcid, UINT dstid);

	int modify_dependence(ModifyingType type, std::wstring src_nodename, std::wstring dst_nodename, std::wstring changed);
	int modify_dependence(ModifyingType type, UINT srcid, UINT dstid, UINT changed);

	const Node* get_node_from_name(std::wstring nodename);
	const Node* get_node_from_id(UINT id);
};
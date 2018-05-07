#pragma once

#include <unordered_map>
#include "Node.h"

enum class StructuringType
{
	CREATE, REMOVE
};

enum class ModifyingType
{
	SRC, DST
};

struct Dependency
{
	Dependency();
	Dependency(UINT _srcid, UINT _dstid);
	UINT srcid;
	UINT dstid;
	bool Dependency::operator <(const Dependency& dependency) const;
};

class Project
{
public:
	Project();
	~Project();

	//member variables' area
private:
	UINT auto_id_counter;
	std::unordered_map<UINT, Node*> all_nodes_by_id;
	std::unordered_map<std::wstring, Node*> all_nodes_by_name;
	std::set<Dependency> all_dependencies;

	Dependency last_created_dependency;
protected:
public:
	
	//member functions' area
private:
	void remove_all_dependency_for_node(UINT nodeid);
protected:
public:
	Node* add_node(std::wstring nodename);
	int remove_node(std::wstring nodename);
	int remove_node(UINT id);

	int structuring_dependency(StructuringType type, std::wstring src_nodename, std::wstring dst_nodename);
	int structuring_dependency(StructuringType type, UINT srcid, UINT dstid);

	int modify_dependency(ModifyingType type, std::wstring src_nodename, std::wstring dst_nodename, std::wstring changed);
	int modify_dependency(ModifyingType type, UINT srcid, UINT dstid, UINT changed);

	Dependency get_last_created_dependency();

	Node* get_node_from_name(std::wstring nodename);
	Node* get_node_from_id(UINT id);
};
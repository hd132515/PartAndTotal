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
	// parameters
	// * Node* node : the node being removed
	void remove_all_dependency_for_node(UINT nodeid);
protected:
public:
	// parameters
	// * std::wstring nodename : the name of node to be added in project
	// return value
	// * NULL : if there is a node whose name is <nodename>.
	// * Node* [not null] : the new node pointer
	Node* add_node(std::wstring nodename);



	// parameters
	// * std::wstring nodename : the name of node to be removed in this project
	// return value
	// * -1 : the node whose name is <nodename> is not existing node in this project.
	// * 0 : success
	int remove_node(std::wstring nodename);

	// parameters
	// * UINT id : the identifier of node to be removed in this project
	// return value
	// * -1 : the node whose identifier is <id> is not existing node in this project.
	// * 0 : success
	int remove_node(UINT id);




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
	int structuring_dependency(StructuringType type, std::wstring src_nodename, std::wstring dst_nodename);

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
	int structuring_dependency(StructuringType type, UINT srcid, UINT dstid);




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
	int modify_dependency(ModifyingType type, std::wstring src_nodename, std::wstring dst_nodename, std::wstring changed);

	// parameters
	// * UINT srcid : the identifier of sub-problem node to be changed
	// * UINT dstid : the identifier of main-problem node
	// * UINT changed : the identifier of sub-problem node replacing
	// return value
	// * -1 : there is a no node whose identifier is <srcid>
	// * -2 : there is a no node whose identifier is <dstid>
	// * -3 : there is a no node whose identifier is <changed>
	// * 0 ; success
	int modify_dependency(ModifyingType type, UINT srcid, UINT dstid, UINT changed);

	Dependency get_last_created_dependency();



	// parameters
	// * std::wstring nodename : the name of node to get
	// return value
	//  return NULL if there is a no node whose name is <nodename>, otherwise node pointer
	Node* get_node_from_name(std::wstring nodename);


	// parameters
	// * std::wstring nodename : the name of node to get
	// return value
	//  return NULL if there is a no node whose name is <nodename>, otherwise node pointer
	Node* get_node_from_id(UINT id);
};
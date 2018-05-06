#pragma once

#include <string>
#include <set>

class Node
{
public:
	Node(UINT _id, std::wstring _nodename);
	~Node();
	
	//member variable's area
private:
	UINT id;
	std::wstring nodename;
	std::set<UINT> inbound_nodes;
	std::set<UINT> outbound_nodes;

	bool cleared;
protected:
public:

	//member function's area
private:
protected:
public:
	void add_inbound_node(UINT id);
	void add_outbound_node(UINT id);

	void remove_inbound_node(UINT id);
	void remove_outbound_node(UINT id);

	void modify_inbound_node(UINT sourceId, UINT destId);
	void modify_outbound_node(UINT sourceId, UINT destId);

	void setid(UINT _id);
	void setnodename(std::wstring _nodename);

	UINT getid();
	std::wstring getnodename();

	std::set<UINT>& getInbound();
	std::set<UINT>& getOutbound();
};
#pragma once

#include <string>
#include <set>

#include "BasicType.h"
#include "Dictionary.h"
#include "GraphFileStructure.h"


class Node
{
public:
	static Node* deserialize_from_descriptor(NodeDescriptor* descriptor, unsigned char* buffer);
	Node(UINT _id, std::wstring _nodename);
	~Node();
	
	//member variable's area
private:
	UINT id;
	std::wstring nodename;

	bool cleared;
protected:
public:
	Dictionary general_data;

	//member function's area
private:
protected:
public:
	void setid(UINT _id);
	void setnodename(std::wstring _nodename);

	UINT getid();
	std::wstring getnodename();

	bool operator <(const Node& dependency) const;

};
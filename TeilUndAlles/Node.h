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

	bool cleared;
protected:
public:

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
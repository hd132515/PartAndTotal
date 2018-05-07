#include "stdafx.h"
#include "Node.h"

Node::Node(UINT _id, std::wstring _nodename) : id(_id), nodename(_nodename)
{
}

Node::~Node()
{
}

void Node::setid(UINT _id)
{
	id = _id;
}

void Node::setnodename(std::wstring _nodename)
{
	nodename = _nodename;
}

UINT Node::getid()
{
	return id;
}

std::wstring Node::getnodename()
{
	return nodename;
}

bool Node::operator <(const Node& dependency) const
{
	return id < dependency.id && wcscmp(nodename.c_str(), dependency.nodename.c_str()) < 0;
}
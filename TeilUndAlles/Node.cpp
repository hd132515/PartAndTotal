#include "stdafx.h"
#include "Node.h"

Node* Node::deserialize_from_descriptor(NodeDescriptor* descriptor, unsigned char* buffer)
{
	UINT id = descriptor->node_id;
	std::wstring name = (wchar_t*)(buffer + descriptor->location_of_name);

	Node* new_node = new Node(descriptor->node_id, name);
	if (new_node->general_data.deserialize_all(buffer + descriptor->location_of_gen_data))return NULL;

	return new_node;
}

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
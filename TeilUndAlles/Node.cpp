#include "stdafx.h"
#include "Node.h"

Node::Node(UINT _id, std::wstring _nodename) : id(_id), nodename(_nodename)
{
}

Node::~Node()
{
}


void Node::add_inbound_node(UINT id)
{
	inbound_nodes.insert(id);
}

void Node::add_outbound_node(UINT id)
{
	outbound_nodes.insert(id);
}

void Node::remove_inbound_node(UINT id)
{
	inbound_nodes.erase(id);
}

void Node::remove_outbound_node(UINT id)
{
	outbound_nodes.erase(id);
}

void Node::modify_inbound_node(UINT sourceId, UINT destId)
{
	remove_inbound_node(sourceId);
	add_inbound_node(destId);
}

void Node::modify_outbound_node(UINT sourceId, UINT destId)
{
	remove_outbound_node(sourceId);
	add_outbound_node(destId);
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

std::set<UINT>& Node::getInbound()
{
	return inbound_nodes;
}

std::set<UINT>& Node::getOutbound()
{
	return outbound_nodes;
}
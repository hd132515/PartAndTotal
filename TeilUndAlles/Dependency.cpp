#include "stdafx.h"
#include "Dependency.h"


Dependency::Dependency(UINT _id, UINT _id1, UINT _id2) : id(_id), direction(0)
{
	if (_id1 > _id2)
	{
		node_id2 = _id1;
		node_id1 = _id2;
	}
	else
	{
		node_id1 = _id1;
		node_id2 = _id2;
	}
}

int Dependency::construct_direction(DirectionConstruct type, UINT srcid, UINT dstid)
{
	bool criterion1 = srcid == node_id1;
	bool criterion2 = srcid == node_id2;
	bool criterion3 = dstid == node_id1;
	bool criterion4 = dstid == node_id2;

	if (criterion1 && criterion4)
	{
		if (type == DirectionConstruct::CREATE)
			direction |= ID1_TO_ID2;
		else if (type == DirectionConstruct::REMOVE)
			direction ^= ID1_TO_ID2;
		return 0;
	}
	if (criterion2 && criterion3)
	{
		if (type == DirectionConstruct::CREATE)
			direction |= ID2_TO_ID1;
		else if (type == DirectionConstruct::REMOVE)
			direction ^= ID2_TO_ID1;
		return 0;
	}
	return -1;
}


bool Dependency::has1to2()
{
	return (bool)(direction & ID1_TO_ID2);
}

bool Dependency::has2to1()
{
	return (bool)(direction & ID2_TO_ID1);
}

bool Dependency::has_no_direction()
{
	return !has1to2() && !has2to1();
}

UINT Dependency::getid()
{
	return id;
}

UINT Dependency::getid1()
{
	return node_id1;
}

UINT Dependency::getid2()
{
	return node_id2;
}

bool Dependency::operator==(const Dependency& dependency)
{
	return node_id1 == dependency.node_id1 && node_id2 == dependency.node_id2;
}

BYTE Dependency::get_direction()
{
	return direction;
}
#pragma once


#define ID1_TO_ID2 0b00000001
#define ID2_TO_ID1 0b00000010

enum class DirectionConstruct
{
	CREATE, REMOVE
};

class Dependency
{
public:
	Dependency(UINT _id, UINT _id1, UINT _id2);

private:
	UINT id;
	UINT node_id1;
	UINT node_id2;
	BYTE direction;

public:
	int construct_direction(DirectionConstruct type, UINT srcid, UINT dstid);

	bool has1to2();
	bool has2to1();
	bool has_no_direction();

	UINT getid();
	UINT getid1();
	UINT getid2();

	bool operator==(const Dependency& dependency);

	BYTE get_direction();
};
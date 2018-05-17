#pragma once

#include "FileStructure.h"

#define GRAPH_FILE 0

struct GraphProjectLayerHeader
{
	LayerHeader gen_header;
	uint_16 number_of_nodes;
	uint_16 number_of_dependency;
};

struct NodeDescriptor
{
	uint_32 node_id;
	uint_32 location_of_name;
	uint_32 location_of_gen_data;
};

struct DependencyDescriptor
{
	uint_32 id;
	uint_32 node_id1;
	uint_32 node_id2;
	uint_8 direction;
};
#pragma once

#include "FileStructure.h"

#define GI_FILE 1

struct GraphicInterfaceLayerHeader
{
	LayerHeader gen_header;
	uint_32 number_of_nodes;
	uint_32 number_of_dependency;
	uint_32 selected_interface_id;
};

struct NodeGIDescriptor
{
	uint_32 id;
	uint_32 node_id;
	uint_32 x;
	uint_32 y;
};

struct DependencyGIDescriptor
{
	uint_32 id;
	uint_32 dependency_id;
};
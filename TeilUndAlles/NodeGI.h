#pragma once

#include <list>
#include "AbstractGraphicInterface.h"
#include "Node.h"

#define NODE_WIDTH 120
#define NODE_HEIGHT 60

struct NodeGIDescriptor;

enum class DependencyDirection
{
	DIR_OUT, DIR_IN
};

class NodeGI : public AbstractGraphicInterface
{
public:
	NodeGI(int _id, CPoint& _pt, Node* _nodeentry);
	~NodeGI();

	//member variables' area
private:
	Node* nodeentry;
	CPoint pt;
	RECT drawArea;
protected:
public:

	//member functions' area
private:
public:
	void draw_node(CDC* pCDC);
	void dragging(CPoint& pt);

	RECT get_draw_area();
	CPoint& get_point();
	Node* get_node();

	virtual void selection_method(CPoint& pt);
};
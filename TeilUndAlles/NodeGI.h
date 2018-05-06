#pragma once

#include <list>
#include "Node.h"

#define NODE_WIDTH 120
#define NODE_HEIGHT 60

#define ARROW_LINE_LENGTH 15
#define ARROW_LINE_DISPLACEMENT (ARROW_LINE_LENGTH * 2)

enum class DependencyDirection
{
	DIR_OUT, DIR_IN
};

class NodeGI
{
public:
	NodeGI(CPoint& _pt, Node* _nodeentry);
	~NodeGI();

	//member variables' area
private:
	Node* nodeentry;
	CPoint pt;
	RECT drawArea;
	bool selected;
protected:
public:

	//member functions' area
private:
public:
	void drawNode(CDC* pCDC);
	void drawMainDependencyLine(CDC* pCDC, CPoint& other_node_pt);
	void drawDependencyDirection(CDC* pCDC, DependencyDirection direction, CPoint& other_node_pt);
	void dragging(CPoint& pt);
	
	void setSelected(bool _selected = true);

	RECT getDrawArea();
	CPoint& getPoint();
	Node* getNode();
	bool isSelected();
};
#include "stdafx.h"
#include "NodeGI.h"

// description
//  the constructor of NodeGI class
// parameters
//  * CPoint& pt : the position of the new node in View area
//  * Node* _nodeentry : the node entry is initialized properly [not null]
// return
//  NodeGI class
NodeGI::NodeGI(CPoint& _pt, Node* _nodeentry) : nodeentry(_nodeentry), pt(_pt), selected(false)
{
	int x0 = pt.x - NODE_WIDTH / 2;
	int y0 = pt.y - NODE_HEIGHT / 2;
	int x1 = pt.x + NODE_WIDTH / 2;
	int y1 = pt.y + NODE_HEIGHT / 2;
	drawArea.left = x0;
	drawArea.top = y0;
	drawArea.right = x1;
	drawArea.bottom = y1;
}

// description
//  the destructor of NodeGI class
// parameters
// return
NodeGI::~NodeGI()
{
}

void NodeGI::drawNode(CDC* pCDC)
{
	CString text(nodeentry->getnodename().c_str());

	if (!selected)
	{
		pCDC->Ellipse(&drawArea);
	}
	else
	{
		CPen pen(PS_SOLID, 3, RGB(0, 0, 0));
		CPen* oldPen = pCDC->SelectObject(&pen);
		pCDC->Ellipse(&drawArea);
		pCDC->SelectObject(oldPen);
	}
	pCDC->DrawText(text, &drawArea, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);
}

void NodeGI::drawMainDependencyLine(CDC* pCDC, CPoint& other_node_pt)
{
	pCDC->MoveTo(pt.x, pt.y);
	pCDC->LineTo(other_node_pt.x, other_node_pt.y);
}

void NodeGI::drawDependencyDirection(CDC* pCDC, DependencyDirection direction, CPoint& other_node_pt)
{
	CPoint arrowline1[] = { { 0, 0 },{ -(LONG)(ARROW_LINE_LENGTH*(sqrt(3) / 2.)), -ARROW_LINE_LENGTH / 2 } };
	CPoint arrowline2[] = { { 0, 0 },{ -(LONG)(ARROW_LINE_LENGTH*(sqrt(3) / 2.)),  ARROW_LINE_LENGTH / 2 } };
	CPoint transformed1, transformed2;

	CSize displ = other_node_pt - pt;
	CSize logical_displ = displ;
	logical_displ.cy *= -1;
	
	double displ_length = sqrt(logical_displ.cx * logical_displ.cx + logical_displ.cy * logical_displ.cy);
	double cos_displ = logical_displ.cx / displ_length;
	double sin_displ = logical_displ.cy / displ_length;
	if (direction == DependencyDirection::DIR_IN)
	{
		cos_displ *= -1.0;
		sin_displ *= -1.0;
	}

	transformed1.x = (LONG)(arrowline1[1].x*cos_displ + arrowline1[1].y*sin_displ);
	transformed1.y = (LONG)(-arrowline1[1].x*sin_displ + arrowline1[1].y*cos_displ);
	arrowline1[1] = transformed1;

	transformed2.x = (LONG)(arrowline2[1].x*cos_displ + arrowline2[1].y*sin_displ);
	transformed2.y = (LONG)(-arrowline2[1].x*sin_displ + arrowline2[1].y*cos_displ);
	arrowline2[1] = transformed2;

	CPoint mainline_midpoint = (pt + other_node_pt);
	mainline_midpoint.x /= 2;
	mainline_midpoint.y /= 2;

	CSize position_displ;
	position_displ.cx = (LONG)(displ.cx * ARROW_LINE_DISPLACEMENT/displ_length);
	position_displ.cy = (LONG)(displ.cy * ARROW_LINE_DISPLACEMENT/displ_length);
	if (direction == DependencyDirection::DIR_IN)
	{
		position_displ.cx *= -1;
		position_displ.cy *= -1;
	}

	CPoint arrow_position = mainline_midpoint + position_displ;
	arrowline1[0] += arrow_position;
	arrowline1[1] += arrow_position;
	arrowline2[0] += arrow_position;
	arrowline2[1] += arrow_position;

	pCDC->MoveTo(arrowline1[0].x, arrowline1[0].y);
	pCDC->LineTo(arrowline1[1].x, arrowline1[1].y);

	pCDC->MoveTo(arrowline2[0].x, arrowline2[0].y);
	pCDC->LineTo(arrowline2[1].x, arrowline2[1].y);
}

void NodeGI::dragging(CPoint& _pt)
{
	pt = _pt;
	int x0 = pt.x - NODE_WIDTH / 2;
	int y0 = pt.y - NODE_HEIGHT / 2;
	int x1 = pt.x + NODE_WIDTH / 2;
	int y1 = pt.y + NODE_HEIGHT / 2;
	drawArea.left = x0;
	drawArea.top = y0;
	drawArea.right = x1;
	drawArea.bottom = y1;
}

void NodeGI::setSelected(bool _selected)
{
	selected = _selected;
}

RECT NodeGI::getDrawArea()
{
	return drawArea;
}

CPoint& NodeGI::getPoint()
{
	return pt;
}

Node* NodeGI::getNode()
{
	return nodeentry;
}

bool NodeGI::isSelected()
{
	return selected;
}
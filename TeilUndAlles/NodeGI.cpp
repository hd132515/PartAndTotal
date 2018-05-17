#include "stdafx.h"
#include "NodeGI.h"

// description
//  the constructor of NodeGI class
// parameters
//  * CPoint& pt : the position of the new node in View area
//  * Node* _nodeentry : the node entry is initialized properly [not null]
// return
//  NodeGI class
NodeGI::NodeGI(int _id, CPoint& _pt, Node* _nodeentry) :
	AbstractGraphicInterface(_id),
	nodeentry(_nodeentry), pt(_pt)
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

void NodeGI::draw_node(CDC* pCDC)
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

RECT NodeGI::get_draw_area()
{
	return drawArea;
}

CPoint& NodeGI::get_point()
{
	return pt;
}

Node* NodeGI::get_node()
{
	return nodeentry;
}

void NodeGI::selection_method(CPoint& pt)
{
	if (PtInRect(&drawArea, pt))
	{
		selected = true;
	}
	else selected = false;
}
#include "stdafx.h"
#include "DependencyGI.h"


DependencyGI::DependencyGI(int _id, Dependency* _dependency_entry) :
	AbstractGraphicInterface(_id),
	dependency_entry(_dependency_entry), id1pt(NULL), id2pt(NULL)
{
}

DependencyGI::~DependencyGI()
{
}

void DependencyGI::set_pointer_for_id1(CPoint* _id1pt)
{
	id1pt = _id1pt;
}

void DependencyGI::set_pointer_for_id2(CPoint* _id2pt)
{
	id2pt = _id2pt;
}


void DependencyGI::draw_dependency(CDC* pCDC)
{
	CPen pen(PS_SOLID, 3, RGB(0, 0, 0)); 
	CPen* oldPen = NULL;

	if (selected)
	{
		oldPen = pCDC->SelectObject(&pen);
	}

	pCDC->MoveTo(id1pt->x, id1pt->y);
	pCDC->LineTo(id2pt->x, id2pt->y);


	if (dependency_entry->has1to2())
		draw_a_to_b_dir(pCDC, *id1pt, *id2pt);
	if (dependency_entry->has2to1())
		draw_a_to_b_dir(pCDC, *id2pt, *id1pt);
	
	if (selected)
	{
		pCDC->SelectObject(oldPen);
	}
}

void DependencyGI::draw_a_to_b_dir(CDC* pCDC, CPoint& a, CPoint& b)
{
	CPoint arrowline1[] = { { 0, 0 },{ -(LONG)(ARROW_LINE_LENGTH*(sqrt(3) / 2.)), -ARROW_LINE_LENGTH / 2 } };
	CPoint arrowline2[] = { { 0, 0 },{ -(LONG)(ARROW_LINE_LENGTH*(sqrt(3) / 2.)),  ARROW_LINE_LENGTH / 2 } };
	CPoint transformed1, transformed2;

	CSize displ = b - a;
	CSize logical_displ = displ;
	logical_displ.cy *= -1;

	double displ_length = sqrt(logical_displ.cx * logical_displ.cx + logical_displ.cy * logical_displ.cy);
	double cos_displ = logical_displ.cx / displ_length;
	double sin_displ = logical_displ.cy / displ_length;

	transformed1.x = (LONG)(arrowline1[1].x*cos_displ + arrowline1[1].y*sin_displ);
	transformed1.y = (LONG)(-arrowline1[1].x*sin_displ + arrowline1[1].y*cos_displ);
	arrowline1[1] = transformed1;

	transformed2.x = (LONG)(arrowline2[1].x*cos_displ + arrowline2[1].y*sin_displ);
	transformed2.y = (LONG)(-arrowline2[1].x*sin_displ + arrowline2[1].y*cos_displ);
	arrowline2[1] = transformed2;

	CPoint mainline_midpoint = (a + b);
	mainline_midpoint.x /= 2;
	mainline_midpoint.y /= 2;

	CSize position_displ;
	position_displ.cx = (LONG)(displ.cx * ARROW_LINE_DISPLACEMENT / displ_length);
	position_displ.cy = (LONG)(displ.cy * ARROW_LINE_DISPLACEMENT / displ_length);

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

Dependency* DependencyGI::get_dependency()
{
	return dependency_entry;
}

CPoint DependencyGI::get_point1()
{
	return *id1pt;
}

CPoint DependencyGI::get_point2()
{
	return *id2pt;
}

void DependencyGI::selection_method(CPoint& pt)
{
	CPoint pt1 = *id1pt;
	CPoint pt2 = *id2pt;
	if (pt1.x <= pt.x && pt.x <= pt2.x || pt2.x <= pt.x && pt.x <= pt1.x)
	{
		CSize displ = (pt1 - pt2);
		CPoint normal_vector(displ.cy, -displ.cx);
		double c = -(normal_vector.x * pt1.x + normal_vector.y * pt1.y);
		double len = abs(normal_vector.x * pt.x + normal_vector.y * pt.y + c) / sqrt(normal_vector.x * normal_vector.x + normal_vector.y * normal_vector.y);
		if (len < SELECTION_RANGE)
		{
			selected = true;
		}
		else
			selected = false;
	}
	else selected = false;
}
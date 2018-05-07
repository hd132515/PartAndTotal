#include "stdafx.h"
#include "DependencyGI.h"


DependencyGI::DependencyGI(UINT _id1, UINT _id2) : direction(0), id1pt(NULL), id2pt(NULL)
{
	if (_id1 > _id2)
	{
		id1 = _id2;
		id2 = _id1;
	}
	else
	{
		id1 = _id1;
		id2 = _id2;
	}
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

// parameters
// return
// * -1 : invalid srcid or dstid
// * 0 : success
int DependencyGI::add_dependency(Dependency& dependency)
{
	bool criterion1 = dependency.srcid == id1;
	bool criterion2 = dependency.srcid == id2;
	bool criterion3 = dependency.dstid == id1;
	bool criterion4 = dependency.dstid == id2;

	if (criterion1 && criterion4)
	{
		direction |= ID1_TO_ID2;
		return 0;
	}
	if (criterion2 && criterion3)
	{
		direction |= ID2_TO_ID1;
		return 0;
	}

	return -1;
}

void DependencyGI::draw_main_line(CDC* pCDC)
{
	pCDC->MoveTo(id1pt->x, id1pt->y);
	pCDC->LineTo(id2pt->x, id2pt->y);
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

void DependencyGI::draw_direction(CDC* pCDC)
{
	if (direction & ID1_TO_ID2)
		draw_a_to_b_dir(pCDC, *id1pt, *id2pt);
	if (direction & ID2_TO_ID1)
		draw_a_to_b_dir(pCDC, *id2pt, *id1pt);
}

UINT DependencyGI::getid1()
{
	return id1;
}

UINT DependencyGI::getid2()
{
	return id2;
}

bool DependencyGI::operator ==(const DependencyGI& dependency)
{
	return id1 == dependency.id1 && id2 == dependency.id2;
}
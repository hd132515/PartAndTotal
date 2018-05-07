#pragma once

#include <vector>
#include "Project.h"

#define ID1_TO_ID2 0b00000001
#define ID2_TO_ID1 0b00000010

#define ARROW_LINE_LENGTH 15
#define ARROW_LINE_DISPLACEMENT (ARROW_LINE_LENGTH * 2)

class DependencyGI
{
public:
	DependencyGI(UINT _id1, UINT _id2);
	~DependencyGI();

	//member variables' area
private:
	UINT id1;
	UINT id2;
	BYTE direction;

	CPoint* id1pt;
	CPoint* id2pt;
protected:
public:

	//member functions' area
private:
	void draw_a_to_b_dir(CDC* pCDC, CPoint& a, CPoint& b);
protected:
public:
	void set_pointer_for_id1(CPoint* _id1pt);
	void set_pointer_for_id2(CPoint* _id2pt);

	int add_dependency(Dependency& dependency);

	void draw_main_line(CDC* pCDC);
	void draw_direction(CDC* pCDC);

	UINT getid1();
	UINT getid2();

	bool operator == (const DependencyGI& dependency);
};
#pragma once

#include <vector>
#include "AbstractGraphicInterface.h"
#include "Dependency.h"

#define ARROW_LINE_LENGTH 15
#define ARROW_LINE_DISPLACEMENT (int)(ARROW_LINE_LENGTH)

#define SELECTION_RANGE 15

struct DependencyGIDescriptor;

class DependencyGI : public AbstractGraphicInterface
{
public:
	static DependencyGI* deserialize(DependencyGIDescriptor* desc, Dependency* dep, bool selected);
	DependencyGI(int _id, Dependency* _dependency_entry);
	~DependencyGI();

	//member variables' area
private:
	Dependency* dependency_entry;
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

	void draw_dependency(CDC* pCDC);

	Dependency* get_dependency();

	CPoint get_point1();
	CPoint get_point2();

	virtual void selection_method(CPoint& pt);
};
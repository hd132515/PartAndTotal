#include "stdafx.h"
#include "AbstractGraphicInterface.h"

AbstractGraphicInterface::AbstractGraphicInterface(int _id) : id(_id), selected(false)
{
}

AbstractGraphicInterface::~AbstractGraphicInterface()
{
}

void AbstractGraphicInterface::init_selection()
{
	selected = false;
}

bool AbstractGraphicInterface::select_interface(CPoint& pt)
{
	selection_method(pt);
	return selected;
}

bool AbstractGraphicInterface::is_selected()
{
	return selected;
}

UINT AbstractGraphicInterface::get_id()
{
	return id;
}
#pragma once


class AbstractGraphicInterface
{
protected:
	AbstractGraphicInterface(int _id);
public:
	~AbstractGraphicInterface();
private:
	//member variables' area
protected:
	UINT id;
	bool selected;
public:

	//member functions' area
private:
protected:
	virtual void selection_method(CPoint& pt) = 0;
public:
	void init_selection();
	bool select_interface(CPoint& pt);
	bool is_selected();

	UINT get_id();
};
#include"Cell.h"

Cell::Cell(int left, int top, int right, int bottom, int price, PLAYER_TYPE master, CELL_TYPE cellType)
{
	this->left = left; this->top = top; this->right = right; this->bottom = bottom;
	this->master = master;
	this->cellType = cellType;
}

void Cell::changeValue(int left, int top, int right, int bottom,PLAYER_TYPE master, CELL_TYPE cellType)
{
	this->left = left; this->top = top; this->right = right; this->bottom = bottom;
	this->master = master;
	switch (cellType)
	{
	case ExpensivePrice:	case NormalPrice:	case CheapPrice:
		price = cellPrice[cellType];
		break;
	default:
		break;
	}
	this->cellType = cellType;
}

Cell & Cell::operator=(const Cell & other)
{
	left = other.left; top = other.top; right = other.right; bottom = other.bottom;
	master = other.master; cellType = other.cellType;
	return *this;
}

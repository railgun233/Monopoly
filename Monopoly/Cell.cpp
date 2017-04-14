#include"Cell.h"

Cell::Cell(int left, int top, int right, int bottom, int price, PLAYER_TYPE master, CELL_TYPE cellType)
{
	this->left = left; this->top = top; this->right = right; this->bottom = bottom;
	this->master = master;
	this->cellType = cellType;
}

void Cell::updateData(CELL_TYPE cellType, int price)
{
	this->cellType = cellType;
	this->price = price;
}

void Cell::updatePlayer(PLAYER_TYPE master)
{
	this->master = master;
}

#include"Cell.h"

Cell::Cell(int left, int top, int right, int bottom, int price, Master master, Quality quality)
{
	this->left = left; this->top = top; this->right = right; this->bottom = bottom;
	this->master = master;
	this->quality = quality;
}

void Cell::updateData(Quality quality, int price)
{
	this->quality = quality;
	this->price = price;
}

void Cell::updatePlayer(Master master)
{
	this->master = master;
}

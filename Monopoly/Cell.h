//地图上可供行走的格子
#pragma once
#include"global.h"

class Scene;

class Cell
{
public:
	int left;                              //一旦构造，这四个值不能修改
	int top;
	int right;
	int bottom;

	int price;
	PLAYER_TYPE master;                   //属于谁，若无主则为0
	CELL_TYPE cellType;                   //空地还是有属性的地

	Cell(int left,int top,int right,int bottom,int price,PLAYER_TYPE master=Player_Empty,CELL_TYPE cellType=Cell_Empty);
	Cell() :left(0), top(0),right(0), bottom(0), price(0), master(Player_Empty), cellType(Cell_Empty){}
	~Cell(){}

	void updateData(CELL_TYPE cellType,int price);
	void updatePlayer(PLAYER_TYPE master);
	void changeValue
	(int left, int top, int right, int bottom,PLAYER_TYPE master = Player_Empty, CELL_TYPE cellType = Cell_Empty);
	Cell& operator=(const Cell& other);

	friend class Scene;
};
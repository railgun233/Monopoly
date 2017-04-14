//地图上可供行走的格子
#pragma once
#include"global.h"

class Scene;

typedef	int Master;
typedef int Quality;

enum {Cell_No=0}Cell_Sign;

class Cell
{
public:
	int left;                        //一旦构造，这四个值不能修改
	int top;
	int right;
	int bottom;

	int price;
	Master master;                   //属于谁，若无主则为0
	Quality quality;                 //空地还是有属性的地

	Cell(int left,int top,int right,int bottom,int price,Master master=Player_No,Quality quality=Cell_No);
	~Cell(){}

	void updateData(Quality quality,int price);
	void updatePlayer(Master master);

	friend class Scene;
};
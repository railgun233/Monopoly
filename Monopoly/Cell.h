//��ͼ�Ͽɹ����ߵĸ���
#pragma once
#include"global.h"

class Scene;

class Cell
{
public:
	int left;                              //һ�����죬���ĸ�ֵ�����޸�
	int top;
	int right;
	int bottom;

	int price;
	PLAYER_TYPE master;                   //����˭����������Ϊ0
	CELL_TYPE cellType;                   //�յػ��������Եĵ�

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
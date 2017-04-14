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

	int number;                           //���ӵı��
	int price;
	PLAYER_TYPE master;                   //����˭����������Ϊ0
	CELL_TYPE cellType;                   //�յػ��������Եĵ�

	Cell(int left,int top,int right,int bottom,int price,PLAYER_TYPE master=Player_No,CELL_TYPE cellType=Cell_Empty);
	~Cell(){}

	void updateData(CELL_TYPE cellType,int price);
	void updatePlayer(PLAYER_TYPE master);

	friend class Scene;
};
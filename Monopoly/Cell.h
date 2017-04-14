//��ͼ�Ͽɹ����ߵĸ���
#pragma once
#include"global.h"

class Scene;

typedef	int Master;
typedef int Quality;

enum {Cell_No=0}Cell_Sign;

class Cell
{
public:
	int left;                        //һ�����죬���ĸ�ֵ�����޸�
	int top;
	int right;
	int bottom;

	int price;
	Master master;                   //����˭����������Ϊ0
	Quality quality;                 //�յػ��������Եĵ�

	Cell(int left,int top,int right,int bottom,int price,Master master=Player_No,Quality quality=Cell_No);
	~Cell(){}

	void updateData(Quality quality,int price);
	void updatePlayer(Master master);

	friend class Scene;
};
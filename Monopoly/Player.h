//����࣬������Һ͵�����Ҷ���Ӵ���̳�
#pragma once
#include"global.h"
class Player
{
public:
	wchar_t name;
	PLAYER_SIGN sign;
	int money;

	Player();
	~Player();
	virtual void moveTo();
	virtual void updateData();
	virtual void getMoney();
};
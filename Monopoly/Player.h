//玩家类，人类玩家和电脑玩家都会从此类继承
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
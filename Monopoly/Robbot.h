#pragma once
#include"Player.h"

class Robbot:Player
{
public:
	Robbot();
	~Robbot();

	virtual void moveTo();
	virtual void updateData();
	virtual void getMoney();
	void decide();
};
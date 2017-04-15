#pragma once
#include"Player.h"

class robot:public Player
{
public:
	robot() :Player() {}
	robot(wchar_t* name_, PLAYER_TYPE sign_, PLAYER_POS pos_, MONEY money_)
		: Player(name_, sign_, pos_, money_) {}
	~robot(){}

	void moveTo(PLAYER_POS newPos) {}
	void decide(){}
};
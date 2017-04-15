//»À¿‡ÕÊº“
#pragma once
#include"Player.h"

class RealPlayer:Player
{
public:
	RealPlayer() :Player(){}
	RealPlayer(wchar_t* name_, PLAYER_TYPE sign_, PLAYER_POS pos_, MONEY money_)
		:Player(name_,sign_,pos_,money_){}
	~RealPlayer(){}

	void moveTo(PLAYER_POS newPos) {}
};
//玩家类:人类玩家和电脑玩家都会从此类继承
#pragma once
#include"global.h"

class Cell;

class Player
{
public:
	wchar_t name[StringMaxLength];
	PLAYER_TYPE sign;
	PLAYER_POS pos;
	MONEY money;

	int left, top, right, bottom;

	Player():name(L""),sign(Player_Empty),pos(0),money(0),left(0),top(0),right(0),bottom(0){}
	Player(wchar_t* name_, PLAYER_TYPE sign_, PLAYER_POS pos_, MONEY money_);
	~Player(){}

	//当不需要改变位置时pos_传值为-1,现在不允许使用-1这个值
	void changeValue(wchar_t* name_,PLAYER_TYPE sign_,PLAYER_POS pos_,MONEY money); 
	void updateData(MONEY newMoney) { money = newMoney; }

	void moveTo(PLAYER_POS newPos);
	void colliderCell();
	void buyCell();
	void directBuy();
	void printCellAndPlayerMessage();

	void operator++();
	void operator=(Player& other);
};
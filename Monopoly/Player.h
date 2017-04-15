//�����:������Һ͵�����Ҷ���Ӵ���̳�
#pragma once
#include"global.h"

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

	void changeValue(wchar_t* name_,PLAYER_TYPE sign_,PLAYER_POS pos_,MONEY money); //������Ҫ�ı�λ��ʱpos_��ֵΪ-1
	void updateData(MONEY newMoney) { money = newMoney; }

	void moveTo(PLAYER_POS newPos);
};
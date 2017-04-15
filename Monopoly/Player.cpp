#include"Player.h"
#include"EasyScene.h"
#include"Manager.h"
#include"Cell.h"

Player::Player(wchar_t * name_, PLAYER_TYPE sign_, PLAYER_POS pos_, MONEY money_)
{
	wcscat(name, name_);
	sign = sign_; money = money_;
	pos = pos_;
	left = (easyScene->cellManager)->cellList[pos].left + SpaceBetweenPlayerAndCell;
	top = (easyScene->cellManager)->cellList[pos].top + SpaceBetweenPlayerAndCell;
	right = (easyScene->cellManager)->cellList[pos].right - SpaceBetweenPlayerAndCell;
	bottom = (easyScene->cellManager)->cellList[pos].bottom - SpaceBetweenPlayerAndCell;
}

void Player::changeValue(wchar_t * name_, PLAYER_TYPE sign_, PLAYER_POS pos_, MONEY money_)
{
	wcscpy(name, name_);
	sign = sign_; money = money_;

	if (pos_ != -1)
	{
		pos = pos_;
		left = easyScene->cellManager->cellList[pos].left + SpaceBetweenPlayerAndCell;
		top = easyScene->cellManager->cellList[pos].top + SpaceBetweenPlayerAndCell;
		right = easyScene->cellManager->cellList[pos].right - SpaceBetweenPlayerAndCell;
		bottom = easyScene->cellManager->cellList[pos].bottom - SpaceBetweenPlayerAndCell;
	}
}

void Player::moveTo(PLAYER_POS newPos)
{
	changeValue(name, sign, newPos, money);
}

void Player::operator++()
{
	if (pos < CellCount)
		++pos;
	else
		pos = 0;
	moveTo(pos);
}

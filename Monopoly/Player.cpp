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
	if (pos != pos_)
	{
		pos = pos_;
		left = easyScene->cellManager->cellList[pos].left + SpaceBetweenPlayerAndCell;
		top = easyScene->cellManager->cellList[pos].top + SpaceBetweenPlayerAndCell;
		right = easyScene->cellManager->cellList[pos].right - SpaceBetweenPlayerAndCell;
		bottom = easyScene->cellManager->cellList[pos].bottom - SpaceBetweenPlayerAndCell;
	}
}
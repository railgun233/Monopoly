#include"Player.h"
#include"RealPlayer.h"
#include"Robot.h"
#include"EasyScene.h"
#include"Manager.h"
#include"Cell.h"
#include"Button.h"


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
	colliderCell();
}

void Player::colliderCell()
{
	if ((easyScene->cellManager->cellList[pos].cellType == Cell_Empty)
		|| (easyScene->cellManager->cellList[pos].master) == sign
		|| (easyScene->cellManager->cellList[pos].master)==Player_Empty)
		return;
	else                                 //到了添加新的格子属性后再在这里添加else if
	{
		int price_ = easyScene->cellManager->cellList[pos].price/10;
		PLAYER_TYPE type_ = easyScene->cellManager->cellList[pos].master;
		money -= price_;
		for (int i = 0; i < playerManager->realPlayerCount; ++i)
		{
			if ((playerManager->realPlayerList)[i].sign == type_)
			{
				(playerManager->realPlayerList)[i].money += price_;
				return;
			}
		}

		for (int i = 0; i < playerManager->robotCount; ++i)
		{
			if (playerManager->robotList[i].sign == type_)
			{
				playerManager->robotList[i].money += price_;
				return;
			}
		}
	}
}

void Player::buyCell()
{
	int price = easyScene->cellManager->cellList[pos].price;
	if (easyScene->cellManager->cellList[pos].cellType<=Cell_Empty
		&&easyScene->cellManager->cellList[pos].master == Player_Empty
		&&price <= money)
	{
		easyScene->paint();
		hWnd = GetConsoleWindow();
		hdc = GetDC(hWnd);

		SetTextColor(hdc, RGB(255, 255, 255));          //设置文本颜色、背景色、大小
		SetBkColor(hdc, RGB(0, 0, 255));
		SelectObject(hdc, fontArr[fontSize_20]);
		SelectObject(hdc, brushArr[BlueBrush]);

		auto fn = [&](Button *button) {                    //懒得想函数名，直接用lambda表达式
			Rectangle(hdc, button->x1, button->y1, button->x2, button->y2);
		};

		//绘制"购买"按钮
		fn(ButtonList[Btn_Buy]);
		TextOut(hdc, ButtonList[Btn_Buy]->x1 + 20, ButtonList[Btn_Buy]->y1 + 12,
			Button_Name[Btn_Buy], wcslen(Button_Name[Btn_Buy]));

		//绘制"取消"按钮
		fn(ButtonList[Btn_CancelBuy]);
		TextOut(hdc, ButtonList[Btn_CancelBuy]->x1 + 20, ButtonList[Btn_CancelBuy]->y1 + 12,
			Button_Name[Btn_CancelBuy], wcslen(Button_Name[Btn_CancelBuy]));

		printCellAndPlayerMessage();

		while (TRUE)
		{
			if (CLICKBUY)
			{
				directBuy();
				CLICKBUY = 0;
				break;
			}
			else if (NOTBUY)
			{
				NOTBUY = 0;
				break;
			}
		}
	}
}

void Player::directBuy()
{
	easyScene->cellManager->cellList[pos].master = sign;
	money -= easyScene->cellManager->cellList[pos].price;
}

void Player::printCellAndPlayerMessage()
{
	hWnd = GetConsoleWindow(); hdc = GetDC(hWnd);
	SetTextColor(hdc, RGB(255, 255, 255));          //设置文本颜色、背景色、大小
	SetBkColor(hdc, RGB(0, 0, 255));
	SelectObject(hdc, fontArr[fontSize_20]);

	wchar_t text_0[] = L"土地价钱:";
	char text_1[10];
	itoa(easyScene->cellManager->cellList[pos].price, text_1, 10);
	wchar_t text_2[] = L"现有金钱:";
	char text_3[10];
	itoa(money, text_3, 10);

	TextOut(hdc, cellAndPlayerText_x, cellAndPlayerText_y, text_0, wcslen(text_0));
	TextOutA(hdc, cellAndPlayerText_x + 100, cellAndPlayerText_y, text_1, strlen(text_1));
	TextOut(hdc, cellAndPlayerText_x, cellAndPlayerText_y+30, text_2, wcslen(text_2));
	TextOutA(hdc, cellAndPlayerText_x + 100, cellAndPlayerText_y+30, text_3, strlen(text_3));
	ReleaseDC(hWnd, hdc);
}

void Player::operator++()
{
	if (pos < CellCount-1)
		++pos;
	else
		pos = 0;
	moveTo(pos);
}

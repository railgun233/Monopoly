#include "Manager.h"
#include"Button.h"
#include"Cell.h"
#include"Player.h"
#include"RealPlayer.h"
#include"Robot.h"

void ButtonManager::getMessage()
{
	BUTTON_TYPE button = isButton();
	rectMessage(button);
	Mouse_State = Mouse_Empty;
}

void ButtonManager::rectMessage(BUTTON_TYPE button)
{
	switch (button)
	{
	case Btn_Start:
		BEINGPLAY = TRUE;
		break;
	case Btn_Buy:
		CLICKBUY = 1;
		break;
	case Btn_CancelBuy:
		NOTBUY = 1;
		break;
	default:
		break;
	}
}

BUTTON_TYPE ButtonManager::isButton()
{
	for (int i = 0; i < ButtonCount; ++i)
		if (ButtonList[i]->inButton(mousePos))
			return BUTTON_TYPE(i);
	return Btn_Empty;
}

CellManager::CellManager(int size)
{
	cellList = new Cell[size];
}

CellManager::~CellManager()
{
	delete cellList;
}

PlayerManager::PlayerManager(int realPlayerCount_, int robotPlayerCount_)
{
	playerCount = realPlayerCount_ + robotPlayerCount_;
	realPlayerCount = realPlayerCount_;
	robotCount = robotPlayerCount_;
	realPlayerList = new RealPlayer[realPlayerCount_];
	robotList = new robot[robotPlayerCount_];

	createPlayer();
}

PlayerManager::~PlayerManager()
{
	delete[] realPlayerList; delete[]robotList;
}

void PlayerManager::createPlayer()
{
	//电脑玩家
	int j = Player_robot1;
	for (int i = 0; i < robotCount; ++i)
		robotList[i].changeValue(PlayerName[j+i], PLAYER_TYPE(j+i), 0, initialMoney);

	//人类玩家
	j = Player_First;
	for (int i =0; i < realPlayerCount; ++i)
		realPlayerList[i].changeValue(PlayerName[j+i], PLAYER_TYPE(j+i), 0, initialMoney);
}

void PlayerManager::deletePlayer(PLAYER_TYPE type)
{
	for (int i = 0; i < realPlayerCount; ++i)
	{
		if (type == realPlayerList[i].sign)             //同样破坏了网络版的基础
		{
			GAMEOVER = true;
			return;
		}
	}

	for (int i = 0; i < robotCount; ++i)
	{
		if (type == robotList[i].sign)
		{
			deletePlayer(i);
			return;
		}
	}
}

void PlayerManager::deletePlayer(int n)
{
	PLAYER_TYPE type = robotList[n].sign;

	robot* temp= new robot[robotCount - 1];
	int j = 0;
	for (int i = 0; i < robotCount; ++i)
		if (i != n)
		{
			temp[j] = robotList[i];
			++j;
		}
	delete[]robotList;
	robotList = temp;
	--robotCount;
	--playerCount;

	hWnd = GetConsoleWindow();
	hdc = GetDC(hWnd);

	SelectObject(hdc, fontArr[fontSize_20]);
	SetTextColor(hdc, RGB(0, 255, 0));
	SetBkColor(hdc, RGB(0, 0, 0));

	wchar_t text[15];
	wcscpy(text, PlayerName[type]);
	wcscat(text, L"已破产");
	TextOut(hdc, buyMessageText_x, buyMessageText_y, text, wcslen(text));
}

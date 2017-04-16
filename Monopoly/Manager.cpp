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
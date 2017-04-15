#include "Manager.h"
#include"Button.h"
#include"Cell.h"
#include"Player.h"
#include"RealPlayer.h"
#include"Robbot.h"

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
		{
			HDC hdc = GetDC(hWnd);
			Ellipse(hdc, 50, 50, 100, 100);
			ReleaseDC(hWnd, hdc);
		}
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

PlayerManager::PlayerManager(int realPlayerCount_, int robbotPlayerCount_)
{
	playerCount = realPlayerCount_ + robbotPlayerCount_;
	realPlayerCount = realPlayerCount_;
	robbotCount = robbotPlayerCount_;
	realPlayerList = new RealPlayer[realPlayerCount_];
	robbotList = new Robbot[robbotPlayerCount_];
}

PlayerManager::~PlayerManager()
{
	delete[] realPlayerList; delete[]robbotList;
}

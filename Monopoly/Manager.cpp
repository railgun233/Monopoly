#include "Manager.h"

ButtonManager::ButtonManager()
{

}

ButtonManager::~ButtonManager()
{

}

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
	case Btn_Empty:
		break;
	case Btn_Start:
		break;
	default:
		break;
	}
}

void ButtonManager::addButton(BUTTON_TYPE button_type, Button *button)
{
	buttonList.insert({ button_type, button });
}

BUTTON_TYPE ButtonManager::isButton()
{
	for (auto iter = buttonList.begin(); iter != buttonList.end(); ++iter)
	{
		if ((*iter).second->inButton(mousePos))
			return (*iter).first;
	}
	return BUTTON_TYPE::Btn_Empty;
}

CellManager::CellManager()
{

}

CellManager::~CellManager()
{

}

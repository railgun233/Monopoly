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
	case Btn_Start:
		{
			HDC hdc = GetDC(hWnd);
			Ellipse(hdc, 50, 50, 100, 100);
			ReleaseDC(hWnd, hdc);
		}
		break;
	case Btn_Empty:
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

CellManager::CellManager()
{

}

CellManager::~CellManager()
{

}

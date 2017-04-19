#include "Robot.h"
#include"EasyScene.h"
#include"Cell.h"
#include"Manager.h"
#include"AI.h"

AI_TYPE robot::chooseAI()
{
	switch (sign)
	{
	case Player_robot1:
		return AI_Rude;
	case Player_robot2:
		return AI_Cautious;
	case Player_robot3:
		return AI_Smart;
	default:
		return AI_Rude;
	}
}

void robot::buy()
{
	int price = easyScene->cellManager->cellList[pos].price;
	if (easyScene->cellManager->cellList[pos].cellType < Cell_Empty
		&&easyScene->cellManager->cellList[pos].master == Player_Empty
		&&price <= money)
	{
		AI_TYPE type = chooseAI();
		if (AI_Engine->toBuy(type))
			directBuy();
	}
}

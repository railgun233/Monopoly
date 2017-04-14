//管理游戏角色与按钮，性质跟GameEngine差不多
#pragma once
#include<list>
using std::list;
#include"global.h"
#include"Button.h"

class Player;
class Cell;
class EasyScene;

class PlayerManager
{
public:
	int playerCount;
	list<Player*> existPlayerList;
};
extern PlayerManager *playerManager;

class ButtonManager
{
public:
	ButtonManager();
	~ButtonManager();

	void getMessage();                             //模仿Windows的消息队列，依次取出消息直至消息有适配对象
	void rectMessage(BUTTON_TYPE button);          //分为两个模块实现，取消息，应激
	BUTTON_TYPE isButton();
};
extern ButtonManager* buttonManager;

class CellManager
{
private:
	list<Cell*> cellList;

public:
	CellManager();
	~CellManager();

	friend class EasyScene;
};
//管理游戏角色与按钮，性质跟GameEngine差不多
#pragma once
#include<map>
using std::map;
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
	map<PLAYER_SIGN, Player*> existPlayerList;
};
static PlayerManager *playerManager;

class ButtonManager
{
public:
	map<BUTTON_TYPE, Button*> buttonList;

	ButtonManager();
	~ButtonManager();

	void getMessage();           //模仿Windows的消息队列，依次取出消息直至消息有适配对象
	void rectMessage(BUTTON_TYPE button);          //分为两个模块实现，取消息，应激
	void addButton(BUTTON_TYPE,Button*);
	BUTTON_TYPE isButton();
};
static ButtonManager* buttonManager;

class CellManager
{
private:
	list<Cell*> cellList;

public:
	CellManager();
	~CellManager();

	friend class EasyScene;
};
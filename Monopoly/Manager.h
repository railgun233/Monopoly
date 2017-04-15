//管理游戏角色与按钮，性质跟GameEngine差不多
//一使用标准库的容器就出现各种毛病，索性全用动态数组来实现，还能提高点效率
#pragma once
#include"global.h"

class EasyScene;
class Cell;
class RealPlayer;
class robot;

class PlayerManager
{
public:
	int playerCount;
	int realPlayerCount;
	int robotCount;

	RealPlayer* realPlayerList;
	robot* robotList;

	PlayerManager(int realPlayerCount_, int robotPlayerCount_);
	~PlayerManager();

	void createPlayer();
};
extern PlayerManager *playerManager;

class ButtonManager
{
public:
	ButtonManager(){}
	~ButtonManager(){}

	void getMessage();                             //模仿Windows的消息队列，依次取出消息直至消息有适配对象
	void rectMessage(BUTTON_TYPE button);          //分为两个模块实现，取消息，应激
	BUTTON_TYPE isButton();
};
extern ButtonManager* buttonManager;

class CellManager
{
private:
	Cell* cellList;

public:
	CellManager(int size);
	~CellManager();

	friend class EasyScene;
	friend class Player;
	friend class RealPlayer;
	friend class robot;
};
//������Ϸ��ɫ�밴ť�����ʸ�GameEngine���
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

	void getMessage();           //ģ��Windows����Ϣ���У�����ȡ����Ϣֱ����Ϣ���������
	void rectMessage(BUTTON_TYPE button);          //��Ϊ����ģ��ʵ�֣�ȡ��Ϣ��Ӧ��
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
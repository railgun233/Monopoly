//������Ϸ��ɫ�밴ť�����ʸ�GameEngine���
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

	void getMessage();                             //ģ��Windows����Ϣ���У�����ȡ����Ϣֱ����Ϣ���������
	void rectMessage(BUTTON_TYPE button);          //��Ϊ����ģ��ʵ�֣�ȡ��Ϣ��Ӧ��
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
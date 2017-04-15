//������Ϸ��ɫ�밴ť�����ʸ�GameEngine���
//һʹ�ñ�׼��������ͳ��ָ���ë��������ȫ�ö�̬������ʵ�֣�������ߵ�Ч��
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

	void getMessage();                             //ģ��Windows����Ϣ���У�����ȡ����Ϣֱ����Ϣ���������
	void rectMessage(BUTTON_TYPE button);          //��Ϊ����ģ��ʵ�֣�ȡ��Ϣ��Ӧ��
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
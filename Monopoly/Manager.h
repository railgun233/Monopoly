//������Ϸ��ɫ�밴ť�����ʸ�GameEngine���
//һʹ�ñ�׼��������ͳ��ָ���ë��������ȫ�ö�̬������ʵ�֣�������ߵ�Ч��
#pragma once
#include"global.h"

class EasyScene;
class Cell;
class RealPlayer;
class Robbot;

class PlayerManager
{
public:
	int playerCount;
	int realPlayerCount;
	int robbotCount;

	RealPlayer* realPlayerList;
	Robbot* robbotList;

	PlayerManager(int realPlayerCount_, int robbotPlayerCount_);
	~PlayerManager();
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
	friend class Robbot;
};
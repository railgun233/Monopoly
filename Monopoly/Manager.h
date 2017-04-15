//������Ϸ��ɫ�밴ť�����ʸ�GameEngine���
//һʹ�ñ�׼��������ͳ��ָ���ë��������ȫ�ö�̬������ʵ�֣�������ߵ�Ч��
#pragma once
#include"global.h"
#include"Button.h"
#include"Cell.h"

class Player;
class EasyScene;

class PlayerManager
{
public:
	int playerCount;
	Player* existPlayerList;
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
	Cell* cellList;

public:
	CellManager(int size);
	~CellManager();

	friend class EasyScene;
};
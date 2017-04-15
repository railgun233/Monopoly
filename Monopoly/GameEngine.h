//��Ϊ��Ϸ�����壬��ϵ��������
#pragma once
#include"global.h"

class Scene;
class PlayerManager;

//��������ʹ�õ�����ģ������������ˣ��浽Ҫ����ʱ��Ҳ�������ϸ�ھ��ܽ����
//ע�⣬ֻ�ɴ�����ֻ������һ��GameEngine����
class GameEngine
{
private:
	Scene* scene;
	PlayerManager* player_manager;

public:
	GameEngine();
	~GameEngine();
	void initialize();                                //�������ݲ�����һЩ����
	void loadScene(Scene*, PlayerManager*);           //���س���
	void run();                                       //����
	void over();                                      //������Ϸ
};
static GameEngine *gameEngine;
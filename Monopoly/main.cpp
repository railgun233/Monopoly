#include"GameEngine.h"

int main()
{
	RUNGAME = 1; LEAVEGAME = 0;

	gameEngine = new GameEngine();                //�ⲿ��staticָ��������ڶ�Ӧ���������������ֻ�ܴ���һ��
	playerManager = new PlayerManager();
	buttonManager = new ButtonManager();
	easyScene = new EasyScene();                  //Scene�������Manager��ĺ��湹��

	//��ʼ��Ϸ����


	gameEngine->initialize();
	while (!LEAVEGAME)
	{
		gameEngine->loadScene(easyScene,playerManager);
		gameEngine->run();
	}

	//������Ϸ����


	delete gameEngine;
	delete easyScene;
	delete playerManager;
	delete buttonManager;
	return 0;
}
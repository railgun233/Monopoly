#include"GameEngine.h"

int main()
{
	RUNGAME = 1; LEAVEGAME = 0;

	gameEngine = new GameEngine();                //这部分static指针变量都在对应的类后面声明，且只能存在一个
	playerManager = new PlayerManager();
	buttonManager = new ButtonManager();
	easyScene = new EasyScene();                  //Scene类必须在Manager类的后面构造

	//开始游戏界面


	gameEngine->initialize();
	while (!LEAVEGAME)
	{
		gameEngine->loadScene(easyScene,playerManager);
		gameEngine->run();
	}

	//结束游戏界面


	delete gameEngine;
	delete easyScene;
	delete playerManager;
	delete buttonManager;
	return 0;
}
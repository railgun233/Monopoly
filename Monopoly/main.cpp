#include"game.h"

//原本打算增加选择电脑玩家数量的选项的，后来发现寻找配色困难，直接去掉了
//同理，网络部分也不容易完成(在不重写一部分场景代码的情况下，当然，主要是因为懒)
//在我的设想里，对于这个游戏,网络版的话只要有一端充当"服务器端"，每回合传输新数据即可
const int RealPlayerCount=1;	const int robotPlayerCount=3;

int main()
{
	//开始游戏界面


	//初始化所有线程间的关联数据
	CLICKBUY = 0; NOTBUY = 0;

	gameEngine = new GameEngine();                //这些类基本都是只能存在一个
	ListenThreadState = PAUSE;                    //先暂停监听线程
	gameEngine->initialize(); 

	buttonManager = new ButtonManager();          //严格来讲它的声明位置是无关紧要的
	AI_Engine = new AI();
	easyScene = new EasyScene();
	playerManager = new PlayerManager(RealPlayerCount, robotPlayerCount);    //要在easyScene之后声明,但要在绘图之前

	ListenThreadState = RUN;

	gameEngine->loadScene(easyScene,playerManager);
	gameEngine->run();
	
	//结束游戏界面


	delete gameEngine;
	delete easyScene;
	delete buttonManager;
	delete playerManager;
	return 0;
}
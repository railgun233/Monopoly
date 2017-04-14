#include"GameEngine.h"
/******************************************乱七八糟的变量全在这定义了*************************************************/
/***********************************若想了解变量的详情可前往global.h**************************************************/
//标志性全局变量
BOOL RUNGAME;	BOOL LEAVEGAME;
//设置类全局变量
short ConsoleBufferWidth;	short ConsoleBufferHeight;
int WindowWidth;	int WindowHeight;
//句柄全局变量
HANDLE hListenThread;	BOOL ListenThreadState;
HWND hWnd;	HDC	 hdc;
HANDLE hOutput;	HANDLE hInput;
HPEN hRedPen;
//一般全局变量
POINT mousePos;		MOUSE_STATE Mouse_State;
Button** ButtonList;	ButtonManager* buttonManager;	PlayerManager *playerManager;
/*********************************************************************************************************************/

int main()
{
	RUNGAME = 1; LEAVEGAME = 0;

	gameEngine = new GameEngine();                //这些类基本都是只能存在一个
	ListenThreadState = PAUSE;
	gameEngine->initialize();                     //先暂停监听线程

	playerManager = new PlayerManager();
	buttonManager = new ButtonManager();

	easyScene = new EasyScene();                  //Scene类必须在Manager类的后面构造
	ListenThreadState = RUN;
	//开始游戏界面


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
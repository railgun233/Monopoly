#include"game.h"
/******************************************乱七八糟的变量全在这定义了*************************************************/
/***********************************若想了解变量的详情可前往global.h**************************************************/
//标志性全局变量
BOOL RUNGAME;	BOOL LEAVEGAME;
//设置类全局变量
short ConsoleBufferWidth;	short ConsoleBufferHeight;	wchar_t ConsoleTitle[StringMaxLength];
int WindowWidth;	int WindowHeight;	int CellCount; 
int RealPlayerCount;	int RobbotPlayerCount;
//句柄全局变量
HANDLE hListenThread;	BOOL ListenThreadState;
HWND hWnd;	HDC	 hdc;
HANDLE hOutput;	HANDLE hInput;
HPEN hRedPen;	HGDIOBJ hWhitePen;
HBRUSH hBlueBrush;	HGDIOBJ hBlackBrush;
//一般全局变量
POINT mousePos;		MOUSE_STATE Mouse_State;
Button** ButtonList;	
ButtonManager* buttonManager;	PlayerManager *playerManager;	EasyScene *easyScene;
/*********************************************************************************************************************/

int main()
{
	//开始游戏界面
	//在这个阶段要让玩家输入RealPlayerCount和RobbotPlayerCount，否则后续的构造不成功

	RUNGAME = 1; LEAVEGAME = 0;

	gameEngine = new GameEngine();                //这些类基本都是只能存在一个
	ListenThreadState = PAUSE;
	gameEngine->initialize();                     //先暂停监听线程

	buttonManager = new ButtonManager();

	easyScene = new EasyScene();                  //Scene类必须在Manager类的后面构造
	ListenThreadState = RUN;

	while (!LEAVEGAME)
	{
		gameEngine->loadScene(easyScene,playerManager);
		gameEngine->run();
	}

	//结束游戏界面


	delete gameEngine;
	delete easyScene;
	delete buttonManager;
	return 0;
}
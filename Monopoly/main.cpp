#include"game.h"
/******************************************乱七八糟的变量全在这定义了*************************************************/
/***********************************若想了解变量的详情可前往global.h**************************************************/
//标志性全局变量
BOOL RUNGAME;	BOOL LEAVEGAME;		BOOL IF_SLEEP;	int SLEEP_TIME = 50;
BOOL BEINGPLAY;	BOOL REPAINT;	BOOL CLICKBUY;	BOOL NOTBUY;
int DiceNumber;
//设置类全局变量
short ConsoleBufferWidth;	short ConsoleBufferHeight;	wchar_t ConsoleTitle[StringMaxLength];
int WindowWidth;	int WindowHeight;	int CellCount; 
int RealPlayerCount;	int robotPlayerCount;	int initialMoney;
int cellAndPlayerText_x, cellAndPlayerText_y;                         //格子的信息与玩家金钱显示文本的起始位置
int DicePos_x, DicePos_y;
int cellPrice[cellPriceCount];
wchar_t PlayerName[MaxPlayerCount][StringMaxLength];
//句柄全局变量
HANDLE hListenThread;	BOOL ListenThreadState;
HWND hWnd;	HDC	 hdc;
HANDLE hOutput;	HANDLE hInput;
HPEN penArr[penCount]; HBRUSH brushArr[brushCount];	HFONT fontArr[fontCount];
//一般全局变量
POINT mousePos;		MOUSE_STATE Mouse_State;
Button** ButtonList;	
ButtonManager* buttonManager;	PlayerManager *playerManager;	EasyScene *easyScene;
const wchar_t* Button_Name[] = { L"掷骰子",L"购买" };
/*********************************************************************************************************************/

int main()
{
	//开始游戏界面


	//在这个阶段要让玩家输入RealPlayerCount和robotPlayerCount，否则后续的构造不成功
	RealPlayerCount = 1; robotPlayerCount = 3;

	RUNGAME = 1; LEAVEGAME = 0; IF_SLEEP = 0; CLICKBUY = 0; NOTBUY = 0;

	gameEngine = new GameEngine();                //这些类基本都是只能存在一个
	ListenThreadState = PAUSE;
	gameEngine->initialize();                     //先暂停监听线程

	buttonManager = new ButtonManager();          //严格来讲它的声明位置是无关紧要的
	easyScene = new EasyScene();
	playerManager = new PlayerManager(RealPlayerCount, robotPlayerCount);    //要在easyScene之后声明,但要在绘图之前

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
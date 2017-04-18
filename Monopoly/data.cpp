#include<Windows.h>
#include"global.h"
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
int initialMoney;
int cellAndPlayerText_x, cellAndPlayerText_y;                         //格子的信息与玩家金钱显示文本的起始位置
int DicePos_x, DicePos_y;
int cellPrice[cellPriceCount];
wchar_t PlayerName[MaxPlayerCount][StringMaxLength];
//句柄全局变量
HANDLE hListenThread;	BOOL ListenThreadState;
HWND hWnd;	HDC	 hdc;
HANDLE hOutput;	HANDLE hInput;
HPEN penArr[penCount]; HBRUSH brushArr[brushCount];	HFONT fontArr[fontCount]; HBRUSH lightBrushArr[brushCount];
//一般全局变量
POINT mousePos;		MOUSE_STATE Mouse_State;
Button** ButtonList;
ButtonManager* buttonManager;	PlayerManager *playerManager;	EasyScene *easyScene;
AI* AI_Engine;
const wchar_t* Button_Name[] = { L"掷骰子",L"购买" ,L"取消" };

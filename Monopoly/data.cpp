#include<Windows.h>
#include"global.h"
#include"game.h"

/***********************************若想了解变量的详情可前往global.h**************************************************/
//标志性全局变量
int SLEEP_TIME = 50;
BOOL BEINGPLAY;	BOOL GAMEOVER;	BOOL CLICKBUY;	BOOL NOTBUY;
int DiceNumber;
//设置类全局变量
short ConsoleBufferWidth;	short ConsoleBufferHeight;	wchar_t ConsoleTitle[StringMaxLength];
int WindowWidth;	int WindowHeight;	
int CellCount;	int initialMoney;
int cellAndPlayerText_x, cellAndPlayerText_y;
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
wchar_t ruleText[128];	wchar_t promptText[128];
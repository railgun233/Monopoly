#include<Windows.h>
#include"global.h"
#include"game.h"

/***********************************�����˽�����������ǰ��global.h**************************************************/
//��־��ȫ�ֱ���
int SLEEP_TIME = 50;
BOOL BEINGPLAY;	BOOL GAMEOVER;	BOOL CLICKBUY;	BOOL NOTBUY;
int DiceNumber;
//������ȫ�ֱ���
short ConsoleBufferWidth;	short ConsoleBufferHeight;	wchar_t ConsoleTitle[StringMaxLength];
int WindowWidth;	int WindowHeight;	
int CellCount;	int initialMoney;
int cellAndPlayerText_x, cellAndPlayerText_y;
int DicePos_x, DicePos_y;
int cellPrice[cellPriceCount];
wchar_t PlayerName[MaxPlayerCount][StringMaxLength];
//���ȫ�ֱ���
HANDLE hListenThread;	BOOL ListenThreadState;
HWND hWnd;	HDC	 hdc;
HANDLE hOutput;	HANDLE hInput;
HPEN penArr[penCount]; HBRUSH brushArr[brushCount];	HFONT fontArr[fontCount]; HBRUSH lightBrushArr[brushCount];
//һ��ȫ�ֱ���
POINT mousePos;		MOUSE_STATE Mouse_State;
Button** ButtonList;
ButtonManager* buttonManager;	PlayerManager *playerManager;	EasyScene *easyScene;
AI* AI_Engine;
const wchar_t* Button_Name[] = { L"������",L"����" ,L"ȡ��" };
wchar_t ruleText[128];	wchar_t promptText[128];
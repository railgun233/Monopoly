#include<Windows.h>
#include"global.h"
#include"game.h"

/******************************************���߰���ı���ȫ���ⶨ����*************************************************/
/***********************************�����˽�����������ǰ��global.h**************************************************/
//��־��ȫ�ֱ���
BOOL RUNGAME;	BOOL LEAVEGAME;		BOOL IF_SLEEP;	int SLEEP_TIME = 50;
BOOL BEINGPLAY;	BOOL REPAINT;	BOOL CLICKBUY;	BOOL NOTBUY;
int DiceNumber;
//������ȫ�ֱ���
short ConsoleBufferWidth;	short ConsoleBufferHeight;	wchar_t ConsoleTitle[StringMaxLength];
int WindowWidth;	int WindowHeight;	int CellCount;
int initialMoney;
int cellAndPlayerText_x, cellAndPlayerText_y;                         //���ӵ���Ϣ����ҽ�Ǯ��ʾ�ı�����ʼλ��
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

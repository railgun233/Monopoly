//被大多数类引用到的函数和常量在此头文件声明
//注意变量的声明方式，防止重定义
#pragma once
#include<Windows.h>
#include<deque>													  //用于MessageBar,但在这个程序里，我并不是太信任标准库
using std::deque;

const int deltaTime = 250;										  //每帧的时间
/***************************************类型定义*******************************************************/
enum PLAYER_TYPE												//用于标志Player的身份，玩家还是电脑，且有序号
	{Player_robot1 = 2, Player_robot2 = 3, Player_robot3 = 4, Player_First = 5, Player_Second = 6,  Player_Empty = 0};

enum BUTTON_TYPE												  //按键类型(按下了哪个按键)
	{Btn_Start = 0, Btn_Buy=1,Btn_CancelBuy=2,Btn_Empty = 100};

enum MOUSE_STATE												  //鼠标标志位
{Mouse_Empty = 0, Mouse_LeftClick = 1, Mouse_RightClick = 2}; extern MOUSE_STATE Mouse_State;

enum AI_TYPE { AI_Rude = 0, AI_Cautious = 1, AI_Smart = 2 };      //AI类型

//格子的价格类型或特殊属性,为方便起见，有特殊属性的格子不可买卖
//下方的Cell_CannotBuy用于占位,补充代码时删去
enum CELL_TYPE
{ ExpensivePrice = 0, NormalPrice = 1, CheapPrice = 2, Cell_Empty = 100,Cell_CannotBuy=101,Cell_RandomEvent=102 };
const int RandomEventChoice = 5;
const int cellPriceCount=3; extern int cellPrice[cellPriceCount];

typedef int PLAYER_POS;											  //标记Player在哪个格子上
typedef int MONEY;

//画笔、画刷资源定义
const int ThinPen = 2;
const int MiddlePen = 5;
const int ThickPen = 8;

	//我的想法是:根据Player_Type来画格子和玩家，格子的颜色浅一点，玩家的调到最深
	//因此深色画刷和浅色画刷当然要相互对应
	//出于偷懒，不创建太多画刷了
enum Pen{WhiteThinPen=0,RedThinPen=1,BlueThinPen=2,GreenThinPen=3,YellowThinPen=4,PinkThinPen=5};
enum Brush{WhiteBrush=0,BlackBrush=1,RedBrush=2,BlueBrush=3,GreenBrush=4,YellowBrush=5,PinkBrush=6};//浅色的也是这个顺序
enum Font{fontSize_20=0,fontSize_50=1};

//数字之间要对得上，这是本程序里为数不多的硬编码了
const int penCount = 6;	const int brushCount = 7;	const int fontCount = 2;
extern HPEN penArr[penCount];	extern HBRUSH brushArr[brushCount];
extern HFONT fontArr[fontCount];	extern HBRUSH lightBrushArr[brushCount];
/********************************标志性全局变量(状态)部分**********************************************/
extern HANDLE hListenThread;
extern BOOL ListenThreadState;									//用于特殊情形下暂停监听线程

/*************************************全局变量部分*****************************************************/
//界面设置
extern short ConsoleBufferWidth;
extern short ConsoleBufferHeight;
extern int WindowWidth;
extern int WindowHeight;

//句柄等
extern HWND hWnd;												//窗口句柄
extern HDC	hdc;												//设备句柄
extern HANDLE hOutput;											//窗口输出句柄
extern HANDLE hInput;											//窗口输入句柄
extern POINT mousePos;

//全局常量
const bool PAUSE = 0;
const bool RUN = 1;
const int Bankrupt = -1;
const int ButtonCount = 3;										//按钮的数量
const int MaxPlayerCount = 10;									//最大玩家数量
const int StringMaxLength = 32;									//最大字符串长度，包括标题和角色名
const int SpaceBetweenPlayerAndCell = 10;						//玩家在格子上的空隙
extern int cellAndPlayerText_x, cellAndPlayerText_y;            //格子的信息与玩家金钱显示文本的起始位置
extern wchar_t ConsoleTitle[StringMaxLength];					//控制台窗口标题
extern int CellCount;											//格子的数量
extern wchar_t PlayerName[MaxPlayerCount][StringMaxLength];     //玩家的名字
extern int initialMoney;                                        //初始金钱
const wchar_t PlayerInfoBarTitle[] = L"玩家信息";
extern int DicePos_x, DicePos_y;                                //骰子数出现的位置
extern int SLEEP_TIME;					//这两个参数作为线程控制主线程的绘画程序是否休眠的关键
extern BOOL BEINGPLAY;		extern BOOL GAMEOVER;	extern int DiceNumber;
extern BOOL CLICKBUY;	extern BOOL NOTBUY;
const int MessageCount = 4;	extern int nowMessageCount; extern deque<wchar_t*> messageList;

extern int buyMessageText_x, buyMessageText_y;
extern const wchar_t* Button_Name[];
extern wchar_t ruleText[128];	extern wchar_t promptText[128];
/**************************************函数部分********************************************************/
void createListenThread();
DWORD WINAPI ListenThread(LPVOID param);						//线程函数，用于监听按键、鼠标信息
void hideCursor();												//隐藏光标
int playDice();
void addMessageToBar(wchar_t* msg, int l);						//添加消息至消息栏
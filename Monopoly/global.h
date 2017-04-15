//被大多数类引用到的函数和常量在此头文件声明
//注意变量的声明方式，防止重定义
#pragma once
#include<Windows.h>

/***************************************类型定义*******************************************************/
enum PLAYER_TYPE                                      //用于标志Player的身份，玩家还是电脑，且有序号
	{Player_robot1 = 0, Player_robot2 = 1, Player_robot3 = 2, Player_First = 8, Player_Second = 9,  Player_Empty = 100};
enum BUTTON_TYPE                                      //按键类型(按下了哪个按键)
	{Btn_Start = 0, Btn_Empty = 100};
enum MOUSE_STATE                                      //鼠标标志位
{Mouse_Empty = 0, Mouse_LeftClick = 1, Mouse_RightClick = 2}; extern MOUSE_STATE Mouse_State;
enum CELL_TYPE { Cell_Empty = 0 };                    //格子的类型
typedef int PLAYER_POS;                                //标记Player在哪个格子上
typedef int MONEY;
/********************************标志性全局变量(状态)部分**********************************************/
extern BOOL RUNGAME;
extern BOOL LEAVEGAME;

extern HANDLE hListenThread;
extern BOOL ListenThreadState;   //用于特殊情形下暂停监听线程

/*************************************全局变量部分*****************************************************/
//界面设置
extern short ConsoleBufferWidth;
extern short ConsoleBufferHeight;
extern int WindowWidth;
extern int WindowHeight;

//句柄等
extern HWND hWnd;                    //窗口句柄
extern HDC	hdc;					//设备句柄
extern HANDLE hOutput;               //窗口输出句柄
extern HANDLE hInput;                //窗口输入句柄
extern POINT mousePos;

//画笔与画刷
const static int ThinPen=2;
const static int MiddlePen = 5;
const static int ThickPen = 8;
extern HPEN hRedPen;	extern HGDIOBJ hWhitePen;
extern HBRUSH hBlueBrush;	extern HGDIOBJ hBlackBrush;

//全局常量
const bool PAUSE = 0;
const bool RUN = 1;
const int ButtonCount = 1;										//按钮的数量
const int MaxPlayerCount = 10;									//最大玩家数量
const int StringMaxLength = 32;									//最大字符串长度，包括标题和角色名
const int SpaceBetweenPlayerAndCell = 10;						//玩家在格子上的空隙
extern wchar_t ConsoleTitle[StringMaxLength];					//控制台窗口标题
extern int CellCount;											//格子的数量
extern wchar_t PlayerName[MaxPlayerCount][StringMaxLength];     //玩家的名字
extern int initialMoney;                                        //初始金钱

const wchar_t PlayerInfoBarTitle[] = L"玩家信息";
/**************************************函数部分********************************************************/
void createListenThread();
DWORD WINAPI ListenThread(LPVOID param);           //线程函数，用于监听按键、鼠标信息
void hideCursor();                                 //隐藏光标
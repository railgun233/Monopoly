//被大多数类引用到的函数和常量在此头文件声明
//注意变量的声明方式，防止重定义
#pragma once
#include<Windows.h>

/***************************************类型定义*******************************************************/
enum PLAYER_SIGN                                      //用于标志Player的身份，玩家还是电脑，且有序号
	{Player_No = 0, Player_First = 1, Player_Second = 2, Player_Robot1 = 10, Player_Robot2 = 11, Player_Robot3 = 12};
enum BUTTON_TYPE                                      //按键类型(按下了哪个按键)
	{ Btn_Empty = 0, Btn_Start = 1 };
enum MOUSE_STATE                                      //鼠标标志位
	{ Mouse_Empty = 0, Mouse_LeftClick = 1, Mouse_RightClick = 2 }static Mouse_State;

/********************************标志性全局变量(状态)部分**********************************************/
static BOOL RUNGAME = 0;
static BOOL LEAVEGAME = 0;

static HANDLE hListenThread;
static BOOL ListenThreadState = 1;     //用于特殊情形下暂停监听线程

/*************************************全局变量部分*****************************************************/
//界面设置
static short ConsoleBufferWidth;
static short ConsoleBufferHeight;
static int WindowWidth;
static int WindowHeight;

static HWND hWnd;                    //窗口句柄
//static HDC	 hdc;                 //设备句柄，保守起见，不设为全局变量，凡是涉及DC的都应慎重
static HANDLE hOutput;               //窗口输出句柄
static HANDLE hInput;                //窗口输入句柄
static POINT mousePos;

//画笔与画刷
const static int ThinPen=2;
const static int MiddlePen = 5;
const static int ThickPen = 8;
static HPEN hRedPen;

/**************************************函数部分********************************************************/
void createListenThread();
DWORD WINAPI ListenThread(LPVOID param);           //线程函数，用于监听按键、鼠标信息
void hideCursor();                                 //隐藏光标
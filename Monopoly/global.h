//������������õ��ĺ����ͳ����ڴ�ͷ�ļ�����
//ע�������������ʽ����ֹ�ض���
#pragma once
#include<Windows.h>

/***************************************���Ͷ���*******************************************************/
enum PLAYER_SIGN                                      //���ڱ�־Player����ݣ���һ��ǵ��ԣ��������
	{Player_No = 0, Player_First = 1, Player_Second = 2, Player_Robot1 = 10, Player_Robot2 = 11, Player_Robot3 = 12};
enum BUTTON_TYPE                                      //��������(�������ĸ�����)
	{ Btn_Empty = 0, Btn_Start = 1 };
enum MOUSE_STATE                                      //����־λ
	{ Mouse_Empty = 0, Mouse_LeftClick = 1, Mouse_RightClick = 2 }static Mouse_State;

/********************************��־��ȫ�ֱ���(״̬)����**********************************************/
static BOOL RUNGAME = 0;
static BOOL LEAVEGAME = 0;

static HANDLE hListenThread;
static BOOL ListenThreadState = 1;     //����������������ͣ�����߳�

/*************************************ȫ�ֱ�������*****************************************************/
//��������
static short ConsoleBufferWidth;
static short ConsoleBufferHeight;
static int WindowWidth;
static int WindowHeight;

static HWND hWnd;                    //���ھ��
//static HDC	 hdc;                 //�豸������������������Ϊȫ�ֱ����������漰DC�Ķ�Ӧ����
static HANDLE hOutput;               //����������
static HANDLE hInput;                //����������
static POINT mousePos;

//�����뻭ˢ
const static int ThinPen=2;
const static int MiddlePen = 5;
const static int ThickPen = 8;
static HPEN hRedPen;

/**************************************��������********************************************************/
void createListenThread();
DWORD WINAPI ListenThread(LPVOID param);           //�̺߳��������ڼ��������������Ϣ
void hideCursor();                                 //���ع��
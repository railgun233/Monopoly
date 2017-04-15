//������������õ��ĺ����ͳ����ڴ�ͷ�ļ�����
//ע�������������ʽ����ֹ�ض���
#pragma once
#include<Windows.h>

/***************************************���Ͷ���*******************************************************/
enum PLAYER_TYPE                                      //���ڱ�־Player����ݣ���һ��ǵ��ԣ��������
	{Player_Empty = 0, Player_First = 1, Player_Second = 2, Player_Robot1 = 10, Player_Robot2 = 11, Player_Robot3 = 12};
enum BUTTON_TYPE                                      //��������(�������ĸ�����)
	{Btn_Start = 0, Btn_Empty = 100};
enum MOUSE_STATE                                      //����־λ
{Mouse_Empty = 0, Mouse_LeftClick = 1, Mouse_RightClick = 2}; extern MOUSE_STATE Mouse_State;
enum CELL_TYPE { Cell_Empty = 0 };                    //���ӵ�����

/********************************��־��ȫ�ֱ���(״̬)����**********************************************/
extern BOOL RUNGAME;
extern BOOL LEAVEGAME;

extern HANDLE hListenThread;
extern BOOL ListenThreadState;   //����������������ͣ�����߳�

/*************************************ȫ�ֱ�������*****************************************************/
//��������
extern short ConsoleBufferWidth;
extern short ConsoleBufferHeight;
extern int WindowWidth;
extern int WindowHeight;

//�����
extern HWND hWnd;                    //���ھ��
extern HDC	hdc;					//�豸���
extern HANDLE hOutput;               //����������
extern HANDLE hInput;                //����������
extern POINT mousePos;

//�����뻭ˢ
const static int ThinPen=2;
const static int MiddlePen = 5;
const static int ThickPen = 8;
extern HPEN hRedPen;	extern HGDIOBJ hWhitePen;
extern HBRUSH hBlueBrush;	extern HGDIOBJ hBlackBrush;

//ȫ�ֳ���
const bool PAUSE = 0;
const bool RUN = 1;
const int ButtonCount = 1;
extern int CellCount;
/**************************************��������********************************************************/
void createListenThread();
DWORD WINAPI ListenThread(LPVOID param);           //�̺߳��������ڼ��������������Ϣ
void hideCursor();                                 //���ع��
//������������õ��ĺ����ͳ����ڴ�ͷ�ļ�����
//ע�������������ʽ����ֹ�ض���
#pragma once
#include<Windows.h>
const int deltaTime = 200;
/***************************************���Ͷ���*******************************************************/
enum PLAYER_TYPE                                      //���ڱ�־Player����ݣ���һ��ǵ��ԣ��������
	{Player_robot1 = 0, Player_robot2 = 1, Player_robot3 = 2, Player_First = 8, Player_Second = 9,  Player_Empty = 100};
enum BUTTON_TYPE                                      //��������(�������ĸ�����)
	{Btn_Start = 0, Btn_Empty = 100};
enum MOUSE_STATE                                      //����־λ
{Mouse_Empty = 0, Mouse_LeftClick = 1, Mouse_RightClick = 2}; extern MOUSE_STATE Mouse_State;
enum CELL_TYPE { Cell_Empty = 0 };                    //���ӵ�����
typedef int PLAYER_POS;                                //���Player���ĸ�������
typedef int MONEY;

//���ʡ���ˢ��Դ����
const static int ThinPen = 2;
const static int MiddlePen = 5;
const static int ThickPen = 8;

enum Pen{WhiteThinPen=0,RedThinPen=1,BlueThinPen=2,GreenThinPen=3,YellowThinPen=4,PinkThinPen=5};
enum Brush{WhiteBrush=0,BlackBrush=1,RedBrush=2,BlueBrush=3,GreenBrush=4,YellowBrush=5,PinkBrush=6};
const static int penCount = 6;	const static int brushCount = 7;
extern HPEN penArr[penCount];	extern HBRUSH brushArr[brushCount]; //����Ҫ�뻭�ʡ���ˢ������Ӧ������Ϊ�������Ӳ������

/********************************��־��ȫ�ֱ���(״̬)����**********************************************/
extern BOOL RUNGAME;
extern BOOL LEAVEGAME;

extern HANDLE hListenThread;
extern BOOL ListenThreadState;   //����������������ͣ�����߳�

extern PLAYER_TYPE nowPlayer;
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

//ȫ�ֳ���
const bool PAUSE = 0;
const bool RUN = 1;
const int ButtonCount = 1;										//��ť������
const int MaxPlayerCount = 10;									//����������
const int StringMaxLength = 32;									//����ַ������ȣ���������ͽ�ɫ��
const int SpaceBetweenPlayerAndCell = 10;						//����ڸ����ϵĿ�϶
extern wchar_t ConsoleTitle[StringMaxLength];					//����̨���ڱ���
extern int CellCount;											//���ӵ�����
extern wchar_t PlayerName[MaxPlayerCount][StringMaxLength];     //��ҵ�����
extern int initialMoney;                                        //��ʼ��Ǯ
extern int DiceBox_x1, DiceBox_y1, DiceBox_x2, DiceBox_y2;      //�����ӿ��λ��
const wchar_t PlayerInfoBarTitle[] = L"�����Ϣ";

extern BOOL IF_SLEEP;	extern int SLEEP_TIME;        //������������Ϊ�߳̿������̵߳Ļ滭�����Ƿ����ߵĹؼ�
extern BOOL BEINGPLAY;		extern BOOL REPAINT;	extern int DiceNumber;
/**************************************��������********************************************************/
void createListenThread();
DWORD WINAPI ListenThread(LPVOID param);           //�̺߳��������ڼ��������������Ϣ
void hideCursor();                                 //���ع��
int playDice();

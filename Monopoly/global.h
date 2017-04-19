//������������õ��ĺ����ͳ����ڴ�ͷ�ļ�����
//ע�������������ʽ����ֹ�ض���
#pragma once
#include<Windows.h>
#include<deque>													  //����MessageBar,�������������Ҳ�����̫���α�׼��
using std::deque;

const int deltaTime = 250;										  //ÿ֡��ʱ��
/***************************************���Ͷ���*******************************************************/
enum PLAYER_TYPE												//���ڱ�־Player����ݣ���һ��ǵ��ԣ��������
	{Player_robot1 = 2, Player_robot2 = 3, Player_robot3 = 4, Player_First = 5, Player_Second = 6,  Player_Empty = 0};

enum BUTTON_TYPE												  //��������(�������ĸ�����)
	{Btn_Start = 0, Btn_Buy=1,Btn_CancelBuy=2,Btn_Empty = 100};

enum MOUSE_STATE												  //����־λ
{Mouse_Empty = 0, Mouse_LeftClick = 1, Mouse_RightClick = 2}; extern MOUSE_STATE Mouse_State;

enum AI_TYPE { AI_Rude = 0, AI_Cautious = 1, AI_Smart = 2 };      //AI����

//���ӵļ۸����ͻ���������,Ϊ������������������Եĸ��Ӳ�������
//�·���Cell_CannotBuy����ռλ,�������ʱɾȥ
enum CELL_TYPE
{ ExpensivePrice = 0, NormalPrice = 1, CheapPrice = 2, Cell_Empty = 100,Cell_CannotBuy=101,Cell_RandomEvent=102 };
const int RandomEventChoice = 5;
const int cellPriceCount=3; extern int cellPrice[cellPriceCount];

typedef int PLAYER_POS;											  //���Player���ĸ�������
typedef int MONEY;

//���ʡ���ˢ��Դ����
const int ThinPen = 2;
const int MiddlePen = 5;
const int ThickPen = 8;

	//�ҵ��뷨��:����Player_Type�������Ӻ���ң����ӵ���ɫǳһ�㣬��ҵĵ�������
	//�����ɫ��ˢ��ǳɫ��ˢ��ȻҪ�໥��Ӧ
	//����͵����������̫�໭ˢ��
enum Pen{WhiteThinPen=0,RedThinPen=1,BlueThinPen=2,GreenThinPen=3,YellowThinPen=4,PinkThinPen=5};
enum Brush{WhiteBrush=0,BlackBrush=1,RedBrush=2,BlueBrush=3,GreenBrush=4,YellowBrush=5,PinkBrush=6};//ǳɫ��Ҳ�����˳��
enum Font{fontSize_20=0,fontSize_50=1};

//����֮��Ҫ�Ե��ϣ����Ǳ�������Ϊ�������Ӳ������
const int penCount = 6;	const int brushCount = 7;	const int fontCount = 2;
extern HPEN penArr[penCount];	extern HBRUSH brushArr[brushCount];
extern HFONT fontArr[fontCount];	extern HBRUSH lightBrushArr[brushCount];
/********************************��־��ȫ�ֱ���(״̬)����**********************************************/
extern HANDLE hListenThread;
extern BOOL ListenThreadState;									//����������������ͣ�����߳�

/*************************************ȫ�ֱ�������*****************************************************/
//��������
extern short ConsoleBufferWidth;
extern short ConsoleBufferHeight;
extern int WindowWidth;
extern int WindowHeight;

//�����
extern HWND hWnd;												//���ھ��
extern HDC	hdc;												//�豸���
extern HANDLE hOutput;											//����������
extern HANDLE hInput;											//����������
extern POINT mousePos;

//ȫ�ֳ���
const bool PAUSE = 0;
const bool RUN = 1;
const int Bankrupt = -1;
const int ButtonCount = 3;										//��ť������
const int MaxPlayerCount = 10;									//����������
const int StringMaxLength = 32;									//����ַ������ȣ���������ͽ�ɫ��
const int SpaceBetweenPlayerAndCell = 10;						//����ڸ����ϵĿ�϶
extern int cellAndPlayerText_x, cellAndPlayerText_y;            //���ӵ���Ϣ����ҽ�Ǯ��ʾ�ı�����ʼλ��
extern wchar_t ConsoleTitle[StringMaxLength];					//����̨���ڱ���
extern int CellCount;											//���ӵ�����
extern wchar_t PlayerName[MaxPlayerCount][StringMaxLength];     //��ҵ�����
extern int initialMoney;                                        //��ʼ��Ǯ
const wchar_t PlayerInfoBarTitle[] = L"�����Ϣ";
extern int DicePos_x, DicePos_y;                                //���������ֵ�λ��
extern int SLEEP_TIME;					//������������Ϊ�߳̿������̵߳Ļ滭�����Ƿ����ߵĹؼ�
extern BOOL BEINGPLAY;		extern BOOL GAMEOVER;	extern int DiceNumber;
extern BOOL CLICKBUY;	extern BOOL NOTBUY;
const int MessageCount = 4;	extern int nowMessageCount; extern deque<wchar_t*> messageList;

extern int buyMessageText_x, buyMessageText_y;
extern const wchar_t* Button_Name[];
extern wchar_t ruleText[128];	extern wchar_t promptText[128];
/**************************************��������********************************************************/
void createListenThread();
DWORD WINAPI ListenThread(LPVOID param);						//�̺߳��������ڼ��������������Ϣ
void hideCursor();												//���ع��
int playDice();
void addMessageToBar(wchar_t* msg, int l);						//�����Ϣ����Ϣ��
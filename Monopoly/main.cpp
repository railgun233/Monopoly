#include"game.h"
/******************************************���߰���ı���ȫ���ⶨ����*************************************************/
/***********************************�����˽�����������ǰ��global.h**************************************************/
//��־��ȫ�ֱ���
BOOL RUNGAME;	BOOL LEAVEGAME;
//������ȫ�ֱ���
short ConsoleBufferWidth;	short ConsoleBufferHeight;	wchar_t ConsoleTitle[StringMaxLength];
int WindowWidth;	int WindowHeight;	int CellCount; 
int RealPlayerCount;	int robotPlayerCount;	int initialMoney;
wchar_t PlayerName[MaxPlayerCount][StringMaxLength];
//���ȫ�ֱ���
HANDLE hListenThread;	BOOL ListenThreadState;
HWND hWnd;	HDC	 hdc;
HANDLE hOutput;	HANDLE hInput;
HPEN hRedPen;	HGDIOBJ hWhitePen;
HBRUSH hBlueBrush;	HGDIOBJ hBlackBrush;
//һ��ȫ�ֱ���
POINT mousePos;		MOUSE_STATE Mouse_State;
Button** ButtonList;	
ButtonManager* buttonManager;	PlayerManager *playerManager;	EasyScene *easyScene;
/*********************************************************************************************************************/

int main()
{
	//��ʼ��Ϸ����
	//������׶�Ҫ���������RealPlayerCount��robotPlayerCount����������Ĺ��첻�ɹ�
	RealPlayerCount = 1; robotPlayerCount = 3;

	RUNGAME = 1; LEAVEGAME = 0;

	gameEngine = new GameEngine();                //��Щ���������ֻ�ܴ���һ��
	ListenThreadState = PAUSE;
	gameEngine->initialize();                     //����ͣ�����߳�

	buttonManager = new ButtonManager();          //�ϸ�������������λ�����޹ؽ�Ҫ��
	easyScene = new EasyScene();
	playerManager = new PlayerManager(RealPlayerCount, robotPlayerCount);    //Ҫ��easyScene֮������,��Ҫ�ڻ�ͼ֮ǰ

	ListenThreadState = RUN;

	while (!LEAVEGAME)
	{
		gameEngine->loadScene(easyScene,playerManager);
		gameEngine->run();
	}

	//������Ϸ����


	delete gameEngine;
	delete easyScene;
	delete buttonManager;
	return 0;
}
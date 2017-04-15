#include"game.h"
/******************************************���߰���ı���ȫ���ⶨ����*************************************************/
/***********************************�����˽�����������ǰ��global.h**************************************************/
//��־��ȫ�ֱ���
BOOL RUNGAME;	BOOL LEAVEGAME;
//������ȫ�ֱ���
short ConsoleBufferWidth;	short ConsoleBufferHeight;	wchar_t ConsoleTitle[StringMaxLength];
int WindowWidth;	int WindowHeight;	int CellCount; 
int RealPlayerCount;	int RobbotPlayerCount;
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
	//������׶�Ҫ���������RealPlayerCount��RobbotPlayerCount����������Ĺ��첻�ɹ�

	RUNGAME = 1; LEAVEGAME = 0;

	gameEngine = new GameEngine();                //��Щ���������ֻ�ܴ���һ��
	ListenThreadState = PAUSE;
	gameEngine->initialize();                     //����ͣ�����߳�

	buttonManager = new ButtonManager();

	easyScene = new EasyScene();                  //Scene�������Manager��ĺ��湹��
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
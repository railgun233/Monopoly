#include"GameEngine.h"
/******************************************���߰���ı���ȫ���ⶨ����*************************************************/
/***********************************�����˽�����������ǰ��global.h**************************************************/
//��־��ȫ�ֱ���
BOOL RUNGAME;	BOOL LEAVEGAME;
//������ȫ�ֱ���
short ConsoleBufferWidth;	short ConsoleBufferHeight;
int WindowWidth;	int WindowHeight;
//���ȫ�ֱ���
HANDLE hListenThread;	BOOL ListenThreadState;
HWND hWnd;	HDC	 hdc;
HANDLE hOutput;	HANDLE hInput;
HPEN hRedPen;
//һ��ȫ�ֱ���
POINT mousePos;		MOUSE_STATE Mouse_State;
Button** ButtonList;	ButtonManager* buttonManager;	PlayerManager *playerManager;
/*********************************************************************************************************************/

int main()
{
	RUNGAME = 1; LEAVEGAME = 0;

	gameEngine = new GameEngine();                //��Щ���������ֻ�ܴ���һ��
	ListenThreadState = PAUSE;
	gameEngine->initialize();                     //����ͣ�����߳�

	playerManager = new PlayerManager();
	buttonManager = new ButtonManager();

	easyScene = new EasyScene();                  //Scene�������Manager��ĺ��湹��
	ListenThreadState = RUN;
	//��ʼ��Ϸ����


	while (!LEAVEGAME)
	{
		gameEngine->loadScene(easyScene,playerManager);
		gameEngine->run();
	}

	//������Ϸ����


	delete gameEngine;
	delete easyScene;
	delete playerManager;
	delete buttonManager;
	return 0;
}
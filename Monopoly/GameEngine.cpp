#include "GameEngine.h"
#include"EasyScene.h"
#include"Manager.h"
#include<fstream>
using std::ifstream;
using std::wifstream;

GameEngine::GameEngine()
{
	/********************************��ȫ�ֱ�������ʼ��*****************************/
	hWnd = GetConsoleWindow();
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetCursorPos(&mousePos);                       //ʱ���μ�ʹ��mousePosǰҪ��תΪ�ͻ�������

	createListenThread();

	//���ع��
	hideCursor();
}

GameEngine::~GameEngine()
{
	CloseHandle(hWnd);
	CloseHandle(hOutput);
	CloseHandle(hInput);
	CloseHandle(hListenThread);
}

void GameEngine::initialize()
{
	/*****************************************��ȡ���ݲ���**************************************************/
	char discard;                                 //��Ȼ�ж�ȡ�������ַ���Ӧ���޹ؽ�Ҫ
	ifstream input("data/GameEngineData.txt");

	//��ȡ���ڻ�������С�봰�ڴ�С
	while (input >> discard && (discard != '#'))
		continue;
	input >> ConsoleBufferWidth >> ConsoleBufferHeight >> WindowWidth >> WindowHeight;

	//��ȡEasyScene��Ӧ��CellCount�Ĵ�С
	while (input >> discard && (discard != '#'))
		continue;
	input >> CellCount;

	//��ȡ��ʼ��Ǯ
	while (input >> discard && (discard != '#'))
		continue;
	input >> initialMoney;

	input.close();
	/****************************************���ַ���ȡ����**************************************************/
	wchar_t wdiscard;
	wifstream winput("data/ChineseString.txt");
	winput.imbue(std::locale("chs"));
	
	//��ȡ����̨�ı���
	while (winput >> wdiscard && (wdiscard != '#'))
		continue;
	winput >> ConsoleTitle;

	winput.close();

	/*********************************��ȡ������*********************************************/
	winput.open("data/PlayerName.txt");
	winput.imbue(std::locale("chs"));
	while (winput >> wdiscard && (wdiscard != '#'))
		continue;

	for (int i = 0; i < MaxPlayerCount; ++i)
		winput >> PlayerName[i];
	winput.close();
	/********************************************��������**************************************************/
	SetConsoleTitle(ConsoleTitle);
	COORD bufferSize = { ConsoleBufferWidth,ConsoleBufferHeight };
	SetConsoleScreenBufferSize(hOutput, bufferSize);                            //�ı仺������С
	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, WindowWidth, WindowHeight, NULL);    //�ı䴰�ڴ�С

	//RECT rect_;                                           //����������ֻ���ڲ���ʱ�ڻ�ȡ���������ֵ(����ʱʹ��)
	//GetWindowRect(hWnd, &rect_);
}

void GameEngine::loadScene(Scene *scene, PlayerManager *player_manager)
{
	this->scene = scene; this->player_manager = player_manager;
}

void GameEngine::run()
{
	this->scene->run();
}

void GameEngine::over()
{
	RUNGAME = 0; LEAVEGAME = 1;
}

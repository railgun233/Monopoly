#include "GameEngine.h"
#include"EasyScene.h"
#include"Manager.h"
#include<fstream>
using std::ifstream;
using std::wifstream;

GameEngine::GameEngine()
{
	/********************************将全局变量都初始化*****************************/
	hWnd = GetConsoleWindow();
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetCursorPos(&mousePos);                       //时刻牢记使用mousePos前要先转为客户区坐标

	createListenThread();

	//隐藏光标
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
	/*****************************************读取数据部分**************************************************/
	char discard;                                 //虽然有读取到中文字符但应该无关紧要
	ifstream input("data/GameEngineData.txt");

	//读取窗口缓冲区大小与窗口大小
	while (input >> discard && (discard != '#'))
		continue;
	input >> ConsoleBufferWidth >> ConsoleBufferHeight >> WindowWidth >> WindowHeight;

	//读取EasyScene对应的CellCount的大小
	while (input >> discard && (discard != '#'))
		continue;
	input >> CellCount;

	//读取初始金钱
	while (input >> discard && (discard != '#'))
		continue;
	input >> initialMoney;

	input.close();
	/****************************************宽字符读取部分**************************************************/
	wchar_t wdiscard;
	wifstream winput("data/ChineseString.txt");
	winput.imbue(std::locale("chs"));
	
	//读取控制台的标题
	while (winput >> wdiscard && (wdiscard != '#'))
		continue;
	winput >> ConsoleTitle;

	winput.close();

	/*********************************读取人物名*********************************************/
	winput.open("data/PlayerName.txt");
	winput.imbue(std::locale("chs"));
	while (winput >> wdiscard && (wdiscard != '#'))
		continue;

	for (int i = 0; i < MaxPlayerCount; ++i)
		winput >> PlayerName[i];
	winput.close();
	/********************************************操作部分**************************************************/
	SetConsoleTitle(ConsoleTitle);
	COORD bufferSize = { ConsoleBufferWidth,ConsoleBufferHeight };
	SetConsoleScreenBufferSize(hOutput, bufferSize);                            //改变缓冲区大小
	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, WindowWidth, WindowHeight, NULL);    //改变窗口大小

	//RECT rect_;                                           //这两个函数只用在测试时期获取需调整的数值(调试时使用)
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

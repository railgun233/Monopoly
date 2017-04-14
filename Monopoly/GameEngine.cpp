#include "GameEngine.h"
#include<fstream>
using std::fstream;

GameEngine::GameEngine()
{
	/********************************将全局变量都初始化*****************************/
	hWnd = GetConsoleWindow();
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetCursorPos(&mousePos);                       //时刻牢记使用mousePos前要先转为客户区坐标
	ScreenToClient(hWnd, &mousePos);

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
	fstream input("data/GameEngineData.txt");
	while (input >> discard && (discard != '#'))
		continue;
	input >> ConsoleBufferWidth >> ConsoleBufferHeight >> WindowWidth >> WindowHeight;
	input.close();

	/********************************************操作部分**************************************************/
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

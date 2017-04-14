#include "GameEngine.h"
#include<fstream>
using std::fstream;

GameEngine::GameEngine()
{
	/********************************��ȫ�ֱ�������ʼ��*****************************/
	hWnd = GetConsoleWindow();
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetCursorPos(&mousePos);                       //ʱ���μ�ʹ��mousePosǰҪ��תΪ�ͻ�������
	ScreenToClient(hWnd, &mousePos);

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
	fstream input("data/GameEngineData.txt");
	while (input >> discard && (discard != '#'))
		continue;
	input >> ConsoleBufferWidth >> ConsoleBufferHeight >> WindowWidth >> WindowHeight;
	input.close();

	/********************************************��������**************************************************/
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

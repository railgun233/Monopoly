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

	/**********************************����ˢ��������Դ��ʼ��*******************************/
	penArr[WhiteThinPen] = CreatePen(PS_SOLID, ThinPen, RGB(255, 255, 255));
	penArr[RedThinPen] = CreatePen(PS_SOLID, ThinPen, RGB(255, 0, 0));
	penArr[BlueThinPen] = CreatePen(PS_SOLID, ThinPen, RGB(0, 0, 255));
	penArr[GreenThinPen] = CreatePen(PS_SOLID, ThinPen, RGB(0, 255, 0));
	penArr[YellowThinPen] = CreatePen(PS_SOLID, ThinPen, RGB(255, 255, 0));
	penArr[PinkThinPen] = CreatePen(PS_SOLID, ThinPen, RGB(255, 0, 255));

	brushArr[WhiteBrush] = CreateSolidBrush(RGB(255, 255, 255));
	brushArr[BlackBrush] = CreateSolidBrush(RGB(0, 0, 0));
	brushArr[RedBrush] = CreateSolidBrush(RGB(255, 0, 0));
	brushArr[BlueBrush] = CreateSolidBrush(RGB(0, 0, 255));
	brushArr[GreenBrush] = CreateSolidBrush(RGB(0, 255, 0));

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

	//��ȡ�����ӵĿ��λ��
	while (input >> discard && (discard != '#'))
		continue;
	input >> DiceBox_x1 >> DiceBox_y1 >> DiceBox_x2 >> DiceBox_y2;

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

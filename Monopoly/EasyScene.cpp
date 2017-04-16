#include"global.h"
#include "EasyScene.h"
#include"Manager.h"
#include"Cell.h"
#include"Button.h"
#include"Player.h"
#include"RealPlayer.h"
#include"Robot.h"

using std::fstream;

EasyScene::EasyScene()
{
	cellManager = new CellManager(CellCount);
	loadData();
	REPAINT = FALSE;
}

EasyScene::~EasyScene()
{
	delete[]cellManager;
}

void EasyScene::loadData()  //读取数据的操作尽量在游戏准备阶段全部完成，尤其是我们的文本包含太多垃圾数据的情况下
{
	/*************************读取数据**************************/
	fstream input("data/drawEasyScene.txt");
	char discard;                                       //用于读取无用的字符并丢弃

	//读取左边界面与右边操作栏的分隔线
	while (input >> discard && (discard != '#'))
		continue;
	input >> line1_x >> line1_y1 >> line1_y2;

	//读取消息栏与游戏界面的分隔线
	while (input >> discard && (discard != '#'))
		continue;
	input >> line2_y >> line2_x1 >> line2_x2;

	//读取右栏里按钮栏和玩家栏的分隔线
	while (input >> discard && (discard != '#'))
		continue;
	input >> line3_y >> line3_x1 >> line3_x2;

	//读取玩家信息栏标题的初始坐标，文本的初始坐标
	while (input >> discard && (discard != '#'))
		continue;
	input >> PlayerInfoBarTitle_x >> PlayerInfoBarTitle_y >> PlayerInfoBar_x >> PlayerInfoBar_y;

	//读取第一个按钮:掷骰子按钮
	while (input >> discard && (discard != '#'))
		continue;
	input >> startBtn_x1 >> startBtn_y1 >> startBtn_x2 >> startBtn_y2;

	//关闭文件
	input.close();

	/*************************读取格子***********************/
	input.open("data/EasySceneCell.txt", std::iostream::in);
	while (input >> discard && (discard != '#'))
		continue;
	for (int i = 0; i < CellCount; ++i)             //将格子的数据导入CellManager
	{
		int left, top, right, bottom, price, master, celltype;
		input >> left >> top >> right >> bottom >> price >> master >> celltype;
		(cellManager->cellList[i]).changeValue(left, top, right, bottom, price, (PLAYER_TYPE)master, (CELL_TYPE)celltype);
	}

	/*************************数据对接*************************/
	//按钮的创建，之所以不使用for循环而采用一个一个输入是有原因的
	Button *button_start_ = new Button({ startBtn_x1, startBtn_y1, startBtn_x2, startBtn_y2 });
	ButtonList=new Button*[ButtonCount]
	{
		button_start_
	};
}

void EasyScene::paint()
{
	hdc= GetDC(hWnd);
	POINT point;
	/****************************************静止部分的绘制*******************************************/
	//绘制左右栏分隔线
	SelectObject(hdc, penArr[PinkThinPen]);
	MoveToEx(hdc, line1_x, line1_y1, &point);
	LineTo(hdc, line1_x, line1_y2);
	//绘制消息栏与游戏界面的分隔线
	MoveToEx(hdc, line2_x1, line2_y, &point);
	LineTo(hdc, line2_x2, line2_y);
	//绘制右栏里按钮栏和玩家栏的分隔线
	MoveToEx(hdc, line3_x1, line3_y, &point);
	LineTo(hdc, line3_x2, line3_y);

	/******************************************按钮的绘制**********************************************/
	drawButton();

	/*******************************************绘制格子***********************************************/
	drawCell();

	/****************************************绘制骰子框***********************************************/
	Rectangle(hdc, DiceBox_x1, DiceBox_y1, DiceBox_x2, DiceBox_y2);

	/****************************************绘制玩家************************************************/
	drawPlayer();

	/***************************************绘制玩家信息栏*******************************************/
	drawPlayerInfoBar();

	ReleaseDC(hWnd, hdc);
}

void EasyScene::run()            //此函数内的代码很大部分都只是为了测试动态效果而写，需重写
{
	paint();
	HBRUSH hClear = CreateSolidBrush(RGB(0, 0, 0));
	RECT rect = { WindowWidth,WindowHeight };
	while (RUNGAME)
	{
		if (REPAINT)                //界面不改变的情况下就不进行重绘，要进行重绘最短时间是deltaTime
		{
			hdc = GetDC(hWnd);
			FillRect(hdc, &rect, hClear);
			Sleep(deltaTime);
			paint();
			ReleaseDC(hWnd, hdc);
			REPAINT = FALSE;
		}
		if (BEINGPLAY)
		{
			allStartMove();
			BEINGPLAY = FALSE;
		}
	}
}

void EasyScene::allStartMove()
{
	for (int i = 0; i < playerManager->realPlayerCount; ++i)
	{
		DiceNumber = playDice();
		Sleep(1500);
		movePlayer(DiceNumber, playerManager->realPlayerList[i].sign);
	}
	for (int i = 0; i < playerManager->robotCount; ++i)
	{
		DiceNumber = playDice();
		Sleep(1500);
		movePlayer(DiceNumber, playerManager->robotList[i].sign);
	}
}

void EasyScene::MessageBar()
{

}

void EasyScene::drawCell()
{
	hdc = GetDC(hWnd);
	for (int i = 0; i < CellCount; ++i)             //不敢使用迭代器了，此前在Button处使用过，全线崩溃
	{
		Rectangle(hdc, cellManager->cellList[i].left, cellManager->cellList[i].top,
			cellManager->cellList[i].right, cellManager->cellList[i].bottom);
	}
	ReleaseDC(hWnd, hdc);
}

void EasyScene::drawButton()
{
	hdc = GetDC(hWnd);
	SelectObject(hdc, penArr[WhiteThinPen]);
	SelectObject(hdc, brushArr[BlackBrush]);

	auto fn=[&](Button *button){                    //懒得想函数名，直接用lambda表达式
		Rectangle(hdc, button->x1, button->y1, button->x2, button->y2);
	};

	for (int i = 0; i < ButtonCount; ++i)
		fn(ButtonList[i]);
	ReleaseDC(hWnd, hdc);
}

void EasyScene::drawPlayer()
{
	hWnd = GetConsoleWindow();
	hdc = GetDC(hWnd);
	SelectObject(hdc, brushArr[BlueBrush]);
	Brush brush = Brush(2);
	for (int i = 0; i < playerManager->realPlayerCount; ++i)
	{
		SelectObject(hdc, brushArr[brush]);
		brush = Brush(brush + 1);
		Ellipse(hdc,
			playerManager->realPlayerList[i].left,
			playerManager->realPlayerList[i].top,
			playerManager->realPlayerList[i].right,
			playerManager->realPlayerList[i].bottom
			);
	}
	for (int i = 0; i < playerManager->robotCount; ++i)
	{
		SelectObject(hdc, brushArr[brush]);
		brush = Brush(brush + 1);
		Ellipse(hdc,
			playerManager->robotList[i].left,
			playerManager->robotList[i].top,
			playerManager->robotList[i].right,
			playerManager->robotList[i].bottom
			);
	}
	ReleaseDC(hWnd, hdc);
}

void EasyScene::drawPlayerInfoBar()
{
	hWnd = GetConsoleWindow();
	hdc = GetDC(hWnd);
	char moneyNumber[10];
	SetTextColor(hdc, RGB(255, 0, 0));
	SetBkColor(hdc, RGB(0, 0, 0));

	//绘制标题
	TextOut(hdc, PlayerInfoBarTitle_x, PlayerInfoBarTitle_y, PlayerInfoBarTitle, wcslen(PlayerInfoBarTitle));

	int iX = PlayerInfoBar_x, iY = PlayerInfoBar_y;
	wchar_t text1[] = L"人类玩家"; wchar_t text2[] = L"电脑玩家";
	for (int i = 0; i < playerManager->realPlayerCount; ++i)       //人类玩家
	{
		_itoa((playerManager->realPlayerList)[i].money, moneyNumber, 10);    //10代表十进制
		TextOut(hdc, iX, iY, text1, wcslen(text1));
		TextOut(hdc, iX + 80, iY,
			((playerManager->realPlayerList)[i].name), wcslen(((playerManager->realPlayerList)[i].name)));
		TextOutA(hdc, iX + 150, iY, moneyNumber, strlen(moneyNumber));
		iY += 20;
	}

	for (int i = 0; i < playerManager->robotCount; ++i)            //机器人玩家
	{
		_itoa((playerManager->robotList)[i].money, moneyNumber, 10);
		TextOut(hdc, iX, iY, text2, wcslen(text2));
		TextOut(hdc, iX + 80, iY,
			((playerManager->robotList)[i].name), wcslen(((playerManager->robotList)[i].name)));
		TextOutA(hdc, iX + 150, iY, moneyNumber, strlen(moneyNumber));
		iY += 20;
	}
}

void EasyScene::movePlayer(int n,PLAYER_TYPE type)
{
	hWnd = GetConsoleWindow();
	HBRUSH hClear = CreateSolidBrush(RGB(0, 0, 0));
	RECT rect = { WindowWidth,WindowHeight };
	
	auto fn=[&](Player* player){
		for (int j = 0; j < n; ++j){
			++(*player);
			hdc = GetDC(hWnd);
			FillRect(hdc, &rect, hClear);
			paint();
			Sleep(deltaTime);
		}
	};

	for (int i = 0; i < playerManager->realPlayerCount;++i)
		if (playerManager->realPlayerList[i].sign == type)
		{
			fn(&(playerManager->realPlayerList[i]));
			return;
		}

	for (int i = 0; i < playerManager->robotCount;++i)
		if (playerManager->robotList[i].sign == type)
		{
			fn(&(playerManager->robotList[i]));
			return;
		}
}

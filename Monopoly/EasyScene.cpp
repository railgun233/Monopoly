#include "EasyScene.h"
using std::fstream;

EasyScene::EasyScene()
{
	loadData();
}

void EasyScene::loadData()  //读取数据的操作尽量在游戏准备阶段全部完成，尤其是我们的文本包含太多垃圾数据的情况下
{
	/*************************读取数据**************************/
	char discard;
	fstream input("data/drawEasyScene.txt");

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

	//读取第一个按钮:掷骰子按钮
	while (input >> discard && (discard != '#'))
		continue;
	input >> startBtn_x1 >> startBtn_y1 >> startBtn_x2 >> startBtn_y2;

	//关闭文件
	input.close();

	/*************************数据对接*************************/
	//Button_Start = new Button(startBtn_x1, startBtn_y1, startBtn_x2, startBtn_y2);
	//buttonManager->addButton(Btn_Start, Button_Start);

	/**************************绘图前的准备********************************/
	//载入画笔、画刷资源
	hRedPen = CreatePen(PS_SOLID, ThinPen, RGB(255, 0, 0));
}

void EasyScene::paint()
{
	HDC hdc= GetDC(hWnd);
	POINT point;
	/****************************************静止部分的绘制*******************************************/
	//绘制左右栏分隔线
	SelectObject(hdc, hRedPen);
	MoveToEx(hdc, line1_x, line1_y1, &point);
	LineTo(hdc, line1_x, line1_y2);
	//绘制消息栏与游戏界面的分隔线
	MoveToEx(hdc, line2_x1, line2_y, &point);
	LineTo(hdc, line2_x2, line2_y);
	//绘制右栏里按钮栏和玩家栏的分隔线
	MoveToEx(hdc, line3_x1, line3_y, &point);
	LineTo(hdc, line3_x2, line3_y);

	/******************************************按钮的绘制**********************************************/
	/*drawButton();*/

	ReleaseDC(hWnd, hdc);
}

void EasyScene::run()
{
	hWnd = GetConsoleWindow();
	paint();
	while (RUNGAME)
		;
}

void EasyScene::loadPlayer()
{

}

void EasyScene::MessageBar()
{

}

void EasyScene::drawCell()
{

}

void EasyScene::drawButton()
{
	auto iter = (buttonManager->buttonList).begin();
	auto end = (buttonManager->buttonList).end();
	HDC hdc = GetDC(hWnd);

	auto fn=[&](Button* button){                //懒得想函数名，直接用lambda表达式
		Rectangle(hdc, button->x1, button->y1, button->x2, button->y2);
	};

	while (iter != end)                         //不在Button类里面添加绘制操作是为了减少频繁构造与析构的开销
	{
		fn(iter->second);
		++iter;
	}

	ReleaseDC(hWnd, hdc);
}

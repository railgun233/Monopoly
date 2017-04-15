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
}

EasyScene::~EasyScene()
{
	delete[]cellManager;
}

void EasyScene::loadData()  //��ȡ���ݵĲ�����������Ϸ׼���׶�ȫ����ɣ����������ǵ��ı�����̫���������ݵ������
{
	/*************************��ȡ����**************************/
	fstream input("data/drawEasyScene.txt");
	char discard;                                       //���ڶ�ȡ���õ��ַ�������

	//��ȡ��߽������ұ߲������ķָ���
	while (input >> discard && (discard != '#'))
		continue;
	input >> line1_x >> line1_y1 >> line1_y2;

	//��ȡ��Ϣ������Ϸ����ķָ���
	while (input >> discard && (discard != '#'))
		continue;
	input >> line2_y >> line2_x1 >> line2_x2;

	//��ȡ�����ﰴť����������ķָ���
	while (input >> discard && (discard != '#'))
		continue;
	input >> line3_y >> line3_x1 >> line3_x2;

	//��ȡ�����Ϣ������ĳ�ʼ���꣬�ı��ĳ�ʼ����
	while (input >> discard && (discard != '#'))
		continue;
	input >> PlayerInfoBarTitle_x >> PlayerInfoBarTitle_y >> PlayerInfoBar_x >> PlayerInfoBar_y;

	//��ȡ��һ����ť:�����Ӱ�ť
	while (input >> discard && (discard != '#'))
		continue;
	input >> startBtn_x1 >> startBtn_y1 >> startBtn_x2 >> startBtn_y2;

	//�ر��ļ�
	input.close();

	/*************************��ȡ����***********************/
	input.open("data/EasySceneCell.txt", std::iostream::in);
	while (input >> discard && (discard != '#'))
		continue;
	for (int i = 0; i < CellCount; ++i)             //�����ӵ����ݵ���CellManager
	{
		int left, top, right, bottom, price, master, celltype;
		input >> left >> top >> right >> bottom >> price >> master >> celltype;
		(cellManager->cellList[i]).changeValue(left, top, right, bottom, price, (PLAYER_TYPE)master, (CELL_TYPE)celltype);
	}

	/*************************���ݶԽ�*************************/
	//��ť�Ĵ�����֮���Բ�ʹ��forѭ��������һ��һ����������ԭ���
	Button *button_start_ = new Button({ startBtn_x1, startBtn_y1, startBtn_x2, startBtn_y2 });
	ButtonList=new Button*[ButtonCount]
	{
		button_start_
	};

	/**************************��ͼǰ��׼��********************************/
	//���뻭�ʡ���ˢ��Դ
	hWhitePen = GetStockObject(WHITE_PEN);
	hRedPen = CreatePen(PS_SOLID, ThinPen, RGB(255, 0, 0));
	hBlackBrush = GetStockObject(BLACK_BRUSH);
	hBlueBrush = CreateSolidBrush(RGB(0, 255, 0));
}

void EasyScene::paint()
{
	hdc= GetDC(hWnd);
	POINT point;
	/****************************************��ֹ���ֵĻ���*******************************************/
	//�����������ָ���
	SelectObject(hdc, hRedPen);
	MoveToEx(hdc, line1_x, line1_y1, &point);
	LineTo(hdc, line1_x, line1_y2);
	//������Ϣ������Ϸ����ķָ���
	MoveToEx(hdc, line2_x1, line2_y, &point);
	LineTo(hdc, line2_x2, line2_y);
	//���������ﰴť����������ķָ���
	MoveToEx(hdc, line3_x1, line3_y, &point);
	LineTo(hdc, line3_x2, line3_y);

	/******************************************��ť�Ļ���**********************************************/
	drawButton();

	/*******************************************���Ƹ���***********************************************/
	drawCell();

	/***************************************���������Ϣ��*******************************************/
	char moneyNumber[10];
	SetTextColor(hdc, RGB(255, 0, 0));
	SetBkColor(hdc, RGB(0, 0, 0));

	//���Ʊ���
	TextOut(hdc, PlayerInfoBarTitle_x, PlayerInfoBarTitle_y, PlayerInfoBarTitle, wcslen(PlayerInfoBarTitle));

	int iX = PlayerInfoBar_x, iY = PlayerInfoBar_y;
	wchar_t text1[] = L"�������"; wchar_t text2[] = L"�������";
	for (int i = 0; i < playerManager->realPlayerCount; ++i)
	{
		_itoa((playerManager->realPlayerList)[i].money, moneyNumber, 10);    //10����ʮ����
		TextOut(hdc, iX, iY, text1, wcslen(text1));
		TextOut(hdc, iX+80, iY,
			((playerManager->realPlayerList)[i].name), wcslen(((playerManager->realPlayerList)[i].name)));
		TextOutA(hdc, iX+150, iY, moneyNumber, strlen(moneyNumber));
		iY += 20;
	}

	for (int i = 0; i < playerManager->robotCount; ++i)
	{
		_itoa((playerManager->robotList)[i].money, moneyNumber, 10);    //10����ʮ����
		TextOut(hdc, iX, iY, text2, wcslen(text2));
		TextOut(hdc, iX + 80, iY,
			((playerManager->robotList)[i].name), wcslen(((playerManager->robotList)[i].name)));
		TextOutA(hdc, iX + 150, iY, moneyNumber, strlen(moneyNumber));
		iY += 20;
	}

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
	hdc = GetDC(hWnd);
	for (int i = 0; i < CellCount; ++i)             //����ʹ�õ������ˣ���ǰ��Button��ʹ�ù���ȫ�߱���
	{
		Rectangle(hdc, cellManager->cellList[i].left, cellManager->cellList[i].top,
			cellManager->cellList[i].right, cellManager->cellList[i].bottom);
	}
}

void EasyScene::drawButton()
{
	hdc = GetDC(hWnd);
	SelectObject(hdc, hWhitePen);
	SelectObject(hdc, hBlackBrush);

	auto fn=[&](Button *button){                    //�����뺯������ֱ����lambda���ʽ
		Rectangle(hdc, button->x1, button->y1, button->x2, button->y2);
	};

	for (int i = 0; i < ButtonCount; ++i)
		fn(ButtonList[i]);
	ReleaseDC(hWnd, hdc);
}

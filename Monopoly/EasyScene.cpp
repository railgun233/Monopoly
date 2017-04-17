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

	//��ȡ��Ϣ���������ʼ���꣬�ı�����ʼ����
	while (input >> discard && (discard != '#'))
		continue;
	input >> MessageBarTitle_x >> MessageBarTitle_y >> MessageBarText_x >> MessageBarText_y;
	
	//��ȡ��һ����ť:�����Ӱ�ť
	while (input >> discard && (discard != '#'))
		continue;
	input >> startBtn_x1 >> startBtn_y1 >> startBtn_x2 >> startBtn_y2;

	//��ȡ�ڶ�����ť:����ť
	while (input >> discard && (discard != '#'))
		continue;
	input >> buyBtn_x1 >> buyBtn_y1 >> buyBtn_x2 >> buyBtn_y2;

	//��ȡ��ť��:ȡ����ť
	while (input >> discard && (discard != '#'))
		continue;
	input >> cancelBuyBtn_x1 >> cancelBuyBtn_y1 >> cancelBuyBtn_x2 >> cancelBuyBtn_y2;

	//�ر��ļ�
	input.close();

	/*************************��ȡ����***********************/
	input.open("data/EasySceneCell.txt", std::iostream::in);

	//��ȡ���ӵĲ�ͬ��Ǯ
	while (input >> discard && (discard != '#'))
		continue;
	input >> cellPrice[ExpensivePrice] >> cellPrice[NormalPrice] >> cellPrice[CheapPrice];

	while (input >> discard && (discard != '#'))
		continue;
	for (int i = 0; i < CellCount; ++i)             //�����ӵ����ݵ���CellManager
	{
		int left, top, right, bottom, master, celltype;
		input >> left >> top >> right >> bottom >> master >> celltype;
		(cellManager->cellList[i]).changeValue(left, top, right, bottom,(PLAYER_TYPE)master,(CELL_TYPE)celltype);
	}

	input.close();
	/*************************���ݶԽ�*************************/
	//��ť�Ĵ�����֮���Բ�ʹ��forѭ��������һ��һ����������ԭ���
	Button *button_start_ = new Button({ startBtn_x1, startBtn_y1, startBtn_x2, startBtn_y2 });
	Button *button_buy_ = new Button({ buyBtn_x1,buyBtn_y1,buyBtn_x2,buyBtn_y2 });
	Button *button_cancel_buy_ = new Button({ cancelBuyBtn_x1,cancelBuyBtn_y1,cancelBuyBtn_x2,cancelBuyBtn_y2 });
	ButtonList=new Button*[ButtonCount]{
		button_start_,button_buy_,button_cancel_buy_
	};
}

void EasyScene::paint()
{
	hdc= GetDC(hWnd);
	POINT point;
	/****************************************��ֹ���ֵĻ���*******************************************/
	//�����������ָ���
	SelectObject(hdc, penArr[PinkThinPen]);
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

	/****************************************�������************************************************/
	drawPlayer();

	/***************************************���������Ϣ��*******************************************/
	drawPlayerInfoBar();

	/****************************************������Ϣ��*********************************************/
	showMessageBar();

	ReleaseDC(hWnd, hdc);
}

void EasyScene::run()            //�˺����ڵĴ���ܴ󲿷ֶ�ֻ��Ϊ�˲��Զ�̬Ч����д������д
{
	paint();
	HBRUSH hClear = CreateSolidBrush(RGB(0, 0, 0));
	RECT rect = { WindowWidth,WindowHeight };
	while (RUNGAME)
	{
		if (REPAINT)                //���治�ı������¾Ͳ������ػ棬Ҫ�����ػ����ʱ����deltaTime
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

void EasyScene::showMessageBar()
{
	hWnd = GetConsoleWindow();
	hdc = GetDC(hWnd);
	SetTextColor(hdc, RGB(0, 255, 0));
	SetBkColor(hdc, RGB(0, 0, 0));

	wchar_t title[] = L"��Ϣ��¼";
	TextOut(hdc, MessageBarTitle_x, MessageBarTitle_y, title, 4);

	int iX = MessageBarText_x, iY = MessageBarText_y;
	for (int i = 0; i < nowMessageCount-1; ++i)
	{
		TextOut(hdc, iX, iY, messageList[i], wcslen(messageList[i]));
		iY += 20;
	}

	if (nowMessageCount > 0)
	{
		SetTextColor(hdc, RGB(0, 0, 255));              //���һ����Ϣ����ɫ����Ϊ�������Ĳ�ͬ
		TextOut(hdc, iX, iY, messageList[nowMessageCount - 1], wcslen(messageList[nowMessageCount - 1]));
	}
}

void EasyScene::drawCell()
{
	hdc = GetDC(hWnd);
	for (int i = 0; i < CellCount; ++i)             //����ʹ�õ������ˣ���ǰ��Button��ʹ�ù���ȫ�߱���
	{
		SelectObject(hdc, lightBrushArr[cellManager->cellList[i].master]);
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
	SetTextColor(hdc, RGB(255, 255, 255));          //�����ı���ɫ������ɫ����С
	SetBkColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, fontArr[fontSize_50]);

	auto fn=[&](Button *button){                    //�����뺯������ֱ����lambda���ʽ
		Rectangle(hdc, button->x1, button->y1, button->x2, button->y2);
	};

	//����"������"��ť
	fn(ButtonList[Btn_Start]);
	TextOut(hdc, ButtonList[Btn_Start]->x1 + 10, ButtonList[Btn_Start]->y1 + 10,
		Button_Name[Btn_Start], wcslen(Button_Name[Btn_Start]));

	ReleaseDC(hWnd, hdc);
}

void EasyScene::drawPlayer()
{
	hWnd = GetConsoleWindow();
	hdc = GetDC(hWnd);

	for (int i = 0; i < playerManager->realPlayerCount; ++i)
	{
		SelectObject(hdc, brushArr[playerManager->realPlayerList[i].sign]);
		Ellipse(hdc,
			playerManager->realPlayerList[i].left,
			playerManager->realPlayerList[i].top,
			playerManager->realPlayerList[i].right,
			playerManager->realPlayerList[i].bottom
			);
	}

	for (int i = 0; i < playerManager->robotCount; ++i)
	{
		SelectObject(hdc, brushArr[playerManager->robotList[i].sign]);
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
	SetTextColor(hdc, RGB(255, 0, 0));         //�ı����óɺ�ɫ���������óɺ�ɫ
	SelectObject(hdc, fontArr[fontSize_20]);   //���������С
	SetBkColor(hdc, RGB(0, 0, 0));

	//���Ʊ���
	TextOut(hdc, PlayerInfoBarTitle_x, PlayerInfoBarTitle_y, PlayerInfoBarTitle, wcslen(PlayerInfoBarTitle));

	int iX = PlayerInfoBar_x, iY = PlayerInfoBar_y;
	wchar_t text1[] = L"�������"; wchar_t text2[] = L"�������";
	for (int i = 0; i < playerManager->realPlayerCount; ++i)       //�������
	{
		_itoa((playerManager->realPlayerList)[i].money, moneyNumber, 10);    //10����ʮ����
		TextOut(hdc, iX, iY, text1, wcslen(text1));
		TextOut(hdc, iX + 100, iY,
			((playerManager->realPlayerList)[i].name), wcslen(((playerManager->realPlayerList)[i].name)));
		TextOutA(hdc, iX + 180, iY, moneyNumber, strlen(moneyNumber));
		iY += 30;
	}

	for (int i = 0; i < playerManager->robotCount; ++i)            //���������
	{
		_itoa((playerManager->robotList)[i].money, moneyNumber, 10);
		TextOut(hdc, iX, iY, text2, wcslen(text2));
		TextOut(hdc, iX + 100, iY,
			((playerManager->robotList)[i].name), wcslen(((playerManager->robotList)[i].name)));
		TextOutA(hdc, iX + 180, iY, moneyNumber, strlen(moneyNumber));
		iY += 30;
	}
}

void EasyScene::movePlayer(int n,PLAYER_TYPE type)
{
	hWnd = GetConsoleWindow();
	HBRUSH hClear = CreateSolidBrush(RGB(0, 0, 0));
	RECT rect = { WindowWidth,WindowHeight };
	
	auto addmessage = [&](Player* player) {
		wchar_t la[] = L"�ƶ����";
		int size = wcslen(player->name) + 5;
		wchar_t *ps = new wchar_t[size];
		wcscpy(ps, player->name);
		wcscat(ps, la);
		addMessageToBar(ps, size);
	};

	auto fn=[&](Player* player){
		for (int j = 0; j < n; ++j){
			++(*player);
			hdc = GetDC(hWnd);
			FillRect(hdc, &rect, hClear);
			paint();
			Sleep(deltaTime);
		}
		addmessage(player);
		paint();
	};

	//Ϊ�˿���չ�ԣ���Ϊ����������˽ӿڣ���������Ϊʡ��ֱ�Ӱ�����ӿ��ƻ��ˣ�ע��!
	for (int i = 0; i < playerManager->realPlayerCount;++i)   
		if (playerManager->realPlayerList[i].sign == type)
		{
			fn(&(playerManager->realPlayerList[i]));
			playerManager->realPlayerList[i].buyCell();
			return;
		}

	for (int i = 0; i < playerManager->robotCount;++i)
		if (playerManager->robotList[i].sign == type)
		{
			fn(&(playerManager->robotList[i]));
			return;
		}
}

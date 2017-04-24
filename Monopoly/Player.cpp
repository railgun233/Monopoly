#include"Player.h"
#include"RealPlayer.h"
#include"Robot.h"
#include"EasyScene.h"
#include"Manager.h"
#include"Cell.h"
#include"Button.h"
//�ѹ���������ʾ����Player�����RealPlayer�����ҵ�һ��ʧ��
//���ǣ����øģ���������

Player::Player(wchar_t * name_, PLAYER_TYPE sign_, PLAYER_POS pos_, MONEY money_)
{
	wcscat(name, name_);
	sign = sign_; money = money_;
	pos = pos_;
	left = (easyScene->cellManager)->cellList[pos].left + SpaceBetweenPlayerAndCell;
	top = (easyScene->cellManager)->cellList[pos].top + SpaceBetweenPlayerAndCell;
	right = (easyScene->cellManager)->cellList[pos].right - SpaceBetweenPlayerAndCell;
	bottom = (easyScene->cellManager)->cellList[pos].bottom - SpaceBetweenPlayerAndCell;
}

void Player::changeValue(wchar_t * name_, PLAYER_TYPE sign_, PLAYER_POS pos_, MONEY money_)
{
	wcscpy(name, name_);
	sign = sign_; money = money_;

	if (pos_ != -1)
	{
		pos = pos_;
		left = easyScene->cellManager->cellList[pos].left + SpaceBetweenPlayerAndCell;
		top = easyScene->cellManager->cellList[pos].top + SpaceBetweenPlayerAndCell;
		right = easyScene->cellManager->cellList[pos].right - SpaceBetweenPlayerAndCell;
		bottom = easyScene->cellManager->cellList[pos].bottom - SpaceBetweenPlayerAndCell;
	}
}

void Player::moveTo(PLAYER_POS newPos)
{
	changeValue(name, sign, newPos, money);
	colliderCell();
}

void Player::colliderCell()
{
	if ((easyScene->cellManager->cellList[pos].cellType == Cell_Empty)
		|| (easyScene->cellManager->cellList[pos].master) == sign)
		return;
	else if (easyScene->cellManager->cellList[pos].cellType==Cell_RandomEvent)   //����¼�
	{
		int choice = rand() % RandomEventChoice;               //����5������¼������һ��Ϊ���¼�

		HBRUSH hClear = CreateSolidBrush(RGB(0, 0, 0));
		RECT rect = { WindowWidth,WindowHeight };

		switch (choice)
		{
		case 0:                                                //��Ǯ�����¼�
		{
			wchar_t text[50];
			wcscpy(text, PlayerName[sign]);
			wchar_t eve[] = L"�ڹ������������߸�,������";
			int __money__ = money / 3;
			wchar_t ent[5];	char entt[5];
			_itoa(__money__, entt, 10);
			mbstowcs(ent, entt, 5);
			wcscat(text, eve);	wcscat(text, ent);

			money -= __money__;

			hdc = GetDC(hWnd);
			FillRect(hdc, &rect, hClear);
			easyScene->paint();

			hdc = GetDC(hWnd);
			SelectObject(hdc, fontArr[fontSize_20]);
			SetTextColor(hdc, RGB(0, 255, 0));
			SetBkColor(hdc, RGB(0, 0, 0));
			TextOut(hdc, buyMessageText_x-30, buyMessageText_y, text, wcslen(text));
			Sleep(3000);
			return;
		}
		case 1:
		{
			wchar_t text[50];
			wcscpy(text, PlayerName[sign]);
			wchar_t eve[] = L"�������̹���·��������";
			int __money__ = money / 3;
			wchar_t ent[5];	char entt[5];
			_itoa(__money__, entt, 10);
			mbstowcs(ent, entt, 5);
			wcscat(text, eve);	wcscat(text, ent);

			money += __money__;

			hdc = GetDC(hWnd);
			FillRect(hdc, &rect, hClear);
			easyScene->paint();

			hdc = GetDC(hWnd);
			SelectObject(hdc, fontArr[fontSize_20]);
			SetTextColor(hdc, RGB(0, 255, 0));
			SetBkColor(hdc, RGB(0, 0, 0));
			TextOut(hdc, buyMessageText_x - 30, buyMessageText_y, text, wcslen(text));
			Sleep(3000);
			return;
		}
		case 2:
		{
			wchar_t text[50];
			wcscpy(text, PlayerName[sign]);
			wchar_t eve[] = L"�������٣�������";
			int __money__ = money/2;
			wchar_t ent[5];	char entt[5];
			_itoa(__money__, entt, 10);
			mbstowcs(ent, entt, 5);
			wcscat(text, eve);	wcscat(text, ent);

			money -= __money__;

			hdc = GetDC(hWnd);
			FillRect(hdc, &rect, hClear);
			easyScene->paint();

			hdc = GetDC(hWnd);
			SelectObject(hdc, fontArr[fontSize_20]);
			SetTextColor(hdc, RGB(0, 255, 0));
			SetBkColor(hdc, RGB(0, 0, 0));
			TextOut(hdc, buyMessageText_x - 30, buyMessageText_y, text, wcslen(text));
			Sleep(3000);
			return;
		}
		case 3:
		{
			wchar_t text[50];
			wcscpy(text, PlayerName[sign]);
			wchar_t eve[] = L"��������ۼ��ߣ���������";
			int __money__ = money / 2;
			wchar_t ent[5];	char entt[5];
			_itoa(__money__, entt, 10);
			mbstowcs(ent, entt, 5);
			wcscat(text, eve);	wcscat(text, ent);

			money += __money__;

			hdc = GetDC(hWnd);
			FillRect(hdc, &rect, hClear);
			easyScene->paint();

			hdc = GetDC(hWnd);
			SelectObject(hdc, fontArr[fontSize_20]);
			SetTextColor(hdc, RGB(0, 255, 0));
			SetBkColor(hdc, RGB(0, 0, 0));
			TextOut(hdc, buyMessageText_x - 30, buyMessageText_y, text, wcslen(text));
			Sleep(3000);
			return;
		}
		default:
			return;
		}
	}
	else if ((easyScene->cellManager->cellList[pos].master) == Player_Empty)
		return;
	else                                 //��������µĸ������Ժ������������else if
	{
		int price_ = easyScene->cellManager->cellList[pos].price/10;
		PLAYER_TYPE type_ = easyScene->cellManager->cellList[pos].master;
		int temp = money;
		money -= price_;
		if (money < 0)
		{
			price_ = temp;
			money = Bankrupt;
		}

		for (int i = 0; i < playerManager->realPlayerCount; ++i)    
		{
			if ((playerManager->realPlayerList)[i].sign == type_)
			{
				(playerManager->realPlayerList)[i].money += price_;
				return;
			}
		}

		for (int i = 0; i < playerManager->robotCount; ++i)
		{
			if (playerManager->robotList[i].sign == type_)
			{
				playerManager->robotList[i].money += price_;
				return;
			}
		}
	}
}

void Player::buyCell()
{
	int price = easyScene->cellManager->cellList[pos].price;
	if (easyScene->cellManager->cellList[pos].cellType<Cell_Empty
		&&easyScene->cellManager->cellList[pos].master == Player_Empty
		&&price <= money)
	{
		easyScene->paint();
		hWnd = GetConsoleWindow();
		hdc = GetDC(hWnd);

		SetTextColor(hdc, RGB(255, 255, 255));          //�����ı���ɫ������ɫ����С
		SetBkColor(hdc, RGB(0, 0, 255));
		SelectObject(hdc, fontArr[fontSize_20]);
		SelectObject(hdc, brushArr[BlueBrush]);

		auto fn = [&](Button *button) {                    //�����뺯������ֱ����lambda���ʽ
			Rectangle(hdc, button->x1, button->y1, button->x2, button->y2);
		};

		//����"����"��ť
		fn(ButtonList[Btn_Buy]);
		TextOut(hdc, ButtonList[Btn_Buy]->x1 + 20, ButtonList[Btn_Buy]->y1 + 12,
			Button_Name[Btn_Buy], wcslen(Button_Name[Btn_Buy]));

		//����"ȡ��"��ť
		fn(ButtonList[Btn_CancelBuy]);
		TextOut(hdc, ButtonList[Btn_CancelBuy]->x1 + 20, ButtonList[Btn_CancelBuy]->y1 + 12,
			Button_Name[Btn_CancelBuy], wcslen(Button_Name[Btn_CancelBuy]));

		printCellAndPlayerMessage();

		while (TRUE)
		{
			if (CLICKBUY)
			{
				directBuy();
				CLICKBUY = 0;
				break;
			}
			else if (NOTBUY)
			{
				NOTBUY = 0;
				break;
			}
		}
	}
}

void Player::directBuy()
{
	easyScene->cellManager->cellList[pos].master = sign;
	money -= easyScene->cellManager->cellList[pos].price;

	hWnd = GetConsoleWindow();
	hdc = GetDC(hWnd);
	//��ʾ��Ӧ�Ĺ�����Ϣ
	SelectObject(hdc, fontArr[fontSize_20]);
	SetTextColor(hdc, RGB(0, 255, 0));          //�����ı���ɫ������ɫ����С
	SetBkColor(hdc, RGB(0, 0, 0));

	wchar_t text[50];
	wcscpy(text, PlayerName[sign]);
	wcscat(text, L"������һ������");
	TextOut(hdc, buyMessageText_x, buyMessageText_y, text, wcslen(text));
	Sleep(1200);
}

void Player::printCellAndPlayerMessage()
{
	hWnd = GetConsoleWindow(); hdc = GetDC(hWnd);
	SetTextColor(hdc, RGB(255, 255, 255));          //�����ı���ɫ������ɫ����С
	SetBkColor(hdc, RGB(0, 0, 255));
	SelectObject(hdc, fontArr[fontSize_20]);

	wchar_t text_0[] = L"���ؼ�Ǯ:";
	char text_1[10];
	itoa(easyScene->cellManager->cellList[pos].price, text_1, 10);
	wchar_t text_2[] = L"���н�Ǯ:";
	char text_3[10];
	itoa(money, text_3, 10);

	TextOut(hdc, cellAndPlayerText_x, cellAndPlayerText_y, text_0, wcslen(text_0));
	TextOutA(hdc, cellAndPlayerText_x + 100, cellAndPlayerText_y, text_1, strlen(text_1));
	TextOut(hdc, cellAndPlayerText_x, cellAndPlayerText_y+30, text_2, wcslen(text_2));
	TextOutA(hdc, cellAndPlayerText_x + 100, cellAndPlayerText_y+30, text_3, strlen(text_3));
	ReleaseDC(hWnd, hdc);
}

void Player::operator++()
{
	if (pos < CellCount-1)
		++pos;
	else
		pos = 0;
	moveTo(pos);
}

void Player::operator=(Player &other)
{
	wcscpy(name, other.name);
	sign = other.sign;pos = other.pos;money = other.money;
	left = other.left; top = other.top; right = other.right; bottom=other.bottom;
}

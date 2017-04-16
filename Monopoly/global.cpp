#include "global.h"
#include"Manager.h"
#include<ctime>

void createListenThread()
{
	HANDLE hListenThread = CreateThread(NULL, NULL, ListenThread, NULL, CREATE_SUSPENDED, NULL);   //创建完先暂停线程
	SetThreadPriority(hListenThread, THREAD_PRIORITY_ABOVE_NORMAL);                               //将线程优先级设置成高于普通线程
	ResumeThread(hListenThread);                                                                  //唤醒线程
	ListenThreadState = 1;
}

//可能存在隐患，需测试，若无法保证完美运行，需加入线程同步机制
DWORD WINAPI ListenThread(LPVOID param)
{
	DWORD eventNumber;                                //这两个变量只是占位用的
	INPUT_RECORD record;
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	while (!LEAVEGAME)
	{
		if (ListenThreadState)
		{
			if (ReadConsoleInput(hInput, &record, 1, &eventNumber))
			{
				if (record.EventType == MOUSE_EVENT&&record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
				{
					GetCursorPos(&mousePos);
					//ScreenToClient(hWnd, &mousePos);
					Mouse_State = Mouse_LeftClick;      //处理完click消息后记得恢复鼠标状态
					buttonManager->getMessage();
				}
			}
		}
	}
	return 0;
}

void hideCursor()
{
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo = {1,FALSE};
	SetConsoleCursorInfo(hOutput, &cursorInfo);
}

int playDice()
{
	hWnd = GetConsoleWindow();
	hdc = GetDC(hWnd);
	srand((unsigned)time(NULL));
	int diceNumber = rand() % 4 + rand()%3+1;
	char text[2];
	itoa(diceNumber,text,10);
	SetTextColor(hdc, RGB(255, 0, 0));
	TextOutA(hdc, DiceBox_x1+20, DiceBox_y2-20,text,2);
	int i = GetLastError();
	return diceNumber;
}

#include "global.h"
#include"Manager.h"
#include<ctime>
deque<wchar_t*> messageList;
int nowMessageCount;

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
					ScreenToClient(hWnd, &mousePos);
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

	SetTextColor(hdc, RGB(255, 0, 255));          //设置文本颜色、背景色、大小
	SetBkColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, fontArr[fontSize_50]);

	TextOutA(hdc, DicePos_x, DicePos_y-20,text,2);
	return diceNumber;
}

void addMessageToBar(wchar_t * msg, int l)
{
	if (nowMessageCount < MessageCount)
	{
		messageList[nowMessageCount] = new wchar_t[l + 1];
		wcscpy(messageList[nowMessageCount], msg);
		++nowMessageCount;
	}
	else
	{
		delete [](messageList[0]);
		for (int i = 0; i < MessageCount-1; ++i)
			messageList[i] = messageList[i + 1];
		messageList[nowMessageCount-1]= new wchar_t[l + 1];
		wcscpy(messageList[nowMessageCount-1], msg);
	}
}

//作为其中一个游戏场景
#pragma once
#include<fstream>
#include"Scene.h"
class CellManager;

class EasyScene:public Scene
{
private:
	int line1_x,line1_y1,line1_y2;											//line1为左边界面和右边操作栏的分隔线
	int line2_y, line2_x1, line2_x2;										//line2为消息栏与游戏界面的分隔线
	int line3_y, line3_x1, line3_x2;										//line3为右栏里按钮栏和玩家栏的分隔线
	int PlayerInfoBarTitle_x, PlayerInfoBarTitle_y;							//玩家信息栏标题的起始位置
	int PlayerInfoBar_x, PlayerInfoBar_y;									//玩家信息栏文本的起始位置
	int MessageBarTitle_x, MessageBarTitle_y;								//消息栏标题的起始位置
	int MessageBarText_x, MessageBarText_y;									//消息栏文本的起始位置
	int ruleText_x, ruleText_y;                                             //规则文本的起始位置
	int promptText_x, promptText_y;                                         //提示文本的起始位置
	int startBtn_x1, startBtn_y1, startBtn_x2, startBtn_y2;					//开始按钮
	int buyBtn_x1, buyBtn_y1, buyBtn_x2, buyBtn_y2;							//购买按钮
	int cancelBuyBtn_x1, cancelBuyBtn_y1, cancelBuyBtn_x2, cancelBuyBtn_y2; //取消按钮

public:
	CellManager *cellManager;
	EasyScene();
	~EasyScene();

	void loadData();                                  //所有Cell的数据也是在这里导入

	void paint();                                     //绘制界面
	void showMessageBar();                            //用于绘制消息栏，显示各个玩家的实时消息

	void drawCell();
	void drawButton();
	void drawPlayer();
	void drawPlayerInfoBar();

	void movePlayer(int n, PLAYER_TYPE type);

	void run();                                       //运行
	void allStartMove();                              //可以视为开启帧动画
};
extern EasyScene *easyScene;
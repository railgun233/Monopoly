//作为其中一个游戏场景
#pragma once
#include<fstream>
#include"Scene.h"
#include"Manager.h"

class EasyScene:public Scene
{
private:
	int line1_x,line1_y1,line1_y2;                                        //line1为左边界面和右边操作栏的分隔线
	int line2_y, line2_x1, line2_x2;                                      //line2为消息栏与游戏界面的分隔线
	int line3_y, line3_x1, line3_x2;                                      //line3为右栏里按钮栏和玩家栏的分隔线
	int startBtn_x1, startBtn_y1, startBtn_x2, startBtn_y2;               //开始按钮

public:
	EasyScene();
	~EasyScene(){}

	void loadData();                                  //所有Cell的数据也是在这里导入
	void paint();                                     //绘制界面
	void run();                                       //运行
	void loadPlayer();                                //载入玩家数据
	void MessageBar();                                //用于绘制消息栏，显示各个玩家的实时消息
	void drawCell();
	void drawButton();
};
static EasyScene *easyScene;
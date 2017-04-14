#pragma once
#include"global.h"

//关于button类的一点设想:原本想先完成动态创建按钮这个功能的，但最终决定完成游戏的大部分功能后再考虑实现这一点
//实现方式可参考Qt的信号与槽机制
class Button
{
public:
	int x1, y1, x2, y2;                         //对角横纵坐标

	Button(int x_1, int y_1, int x_2, int y_2) :x1(x_1), y1(y_1), x2(x_2), y2(y_2){}
	~Button(){}

	bool inButton(POINT mouse) {
		return (mouse.x >= x1) && (mouse.x<=x2) && (mouse.y>=y1) && (mouse.y <= y2);
	}
};
static Button *Button_Start;                  //变量名与常量名特别容易混淆，老哥悠着点

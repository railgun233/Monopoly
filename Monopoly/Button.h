#pragma once
#include"global.h"

//����button���һ������:ԭ��������ɶ�̬������ť������ܵģ������վ��������Ϸ�Ĵ󲿷ֹ��ܺ��ٿ���ʵ����һ��
//ʵ�ַ�ʽ�ɲο�Qt���ź���ۻ���
class Button
{
public:
	int x1, y1, x2, y2;                         //�ԽǺ�������

	Button(int x_1, int y_1, int x_2, int y_2) :x1(x_1), y1(y_1), x2(x_2), y2(y_2){}
	~Button(){}

	bool inButton(POINT mouse) {
		return (mouse.x >= x1) && (mouse.x<=x2) && (mouse.y>=y1) && (mouse.y <= y2);
	}
};
static Button *Button_Start;                  //�������볣�����ر����׻������ϸ����ŵ�

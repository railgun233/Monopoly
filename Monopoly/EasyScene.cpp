#include "EasyScene.h"
using std::fstream;

EasyScene::EasyScene()
{
	loadData();
}

void EasyScene::loadData()  //��ȡ���ݵĲ�����������Ϸ׼���׶�ȫ����ɣ����������ǵ��ı�����̫���������ݵ������
{
	/*************************��ȡ����**************************/
	char discard;
	fstream input("data/drawEasyScene.txt");

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

	//��ȡ��һ����ť:�����Ӱ�ť
	while (input >> discard && (discard != '#'))
		continue;
	input >> startBtn_x1 >> startBtn_y1 >> startBtn_x2 >> startBtn_y2;

	//�ر��ļ�
	input.close();

	/*************************���ݶԽ�*************************/
	//Button_Start = new Button(startBtn_x1, startBtn_y1, startBtn_x2, startBtn_y2);
	//buttonManager->addButton(Btn_Start, Button_Start);

	/**************************��ͼǰ��׼��********************************/
	//���뻭�ʡ���ˢ��Դ
	hRedPen = CreatePen(PS_SOLID, ThinPen, RGB(255, 0, 0));
}

void EasyScene::paint()
{
	HDC hdc= GetDC(hWnd);
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

	auto fn=[&](Button* button){                //�����뺯������ֱ����lambda���ʽ
		Rectangle(hdc, button->x1, button->y1, button->x2, button->y2);
	};

	while (iter != end)                         //����Button��������ӻ��Ʋ�����Ϊ�˼���Ƶ�������������Ŀ���
	{
		fn(iter->second);
		++iter;
	}

	ReleaseDC(hWnd, hdc);
}

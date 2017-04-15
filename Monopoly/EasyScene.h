//��Ϊ����һ����Ϸ����
#pragma once
#include<fstream>
#include"Scene.h"
class CellManager;

class EasyScene:public Scene
{
private:
	int line1_x,line1_y1,line1_y2;                                        //line1Ϊ��߽�����ұ߲������ķָ���
	int line2_y, line2_x1, line2_x2;                                      //line2Ϊ��Ϣ������Ϸ����ķָ���
	int line3_y, line3_x1, line3_x2;                                      //line3Ϊ�����ﰴť����������ķָ���
	int PlayerInfoBarTitle_x, PlayerInfoBarTitle_y;                       //�����Ϣ���������ʼλ��
	int PlayerInfoBar_x, PlayerInfoBar_y;                                 //�����Ϣ���ı�����ʼλ��
	int startBtn_x1, startBtn_y1, startBtn_x2, startBtn_y2;               //��ʼ��ť

public:
	CellManager *cellManager;
	EasyScene();
	~EasyScene();

	void loadData();                                  //����Cell������Ҳ�������ﵼ��

	void paint();                                     //���ƽ���
	void MessageBar();                                //���ڻ�����Ϣ������ʾ������ҵ�ʵʱ��Ϣ

	void drawCell();
	void drawButton();
	void drawPlayer();
	void drawPlayerInfoBar();

	void movePlayer(int n, PLAYER_TYPE type);

	void run();                                       //����
};
extern EasyScene *easyScene;
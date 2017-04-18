#include"game.h"

//ԭ����������ѡ��������������ѡ��ģ���������Ѱ����ɫ���ѣ�ֱ��ȥ����
//ͬ�����粿��Ҳ���������(�ڲ���дһ���ֳ������������£���Ȼ����Ҫ����Ϊ��)
//���ҵ���������������Ϸ,�����Ļ�ֻҪ��һ�˳䵱"��������"��ÿ�غϴ��������ݼ���
const int RealPlayerCount=1;	const int robotPlayerCount=3;

int main()
{
	//��ʼ��Ϸ����


	//��ʼ�������̼߳�Ĺ�������
	CLICKBUY = 0; NOTBUY = 0;

	gameEngine = new GameEngine();                //��Щ���������ֻ�ܴ���һ��
	ListenThreadState = PAUSE;                    //����ͣ�����߳�
	gameEngine->initialize(); 

	buttonManager = new ButtonManager();          //�ϸ�������������λ�����޹ؽ�Ҫ��
	AI_Engine = new AI();
	easyScene = new EasyScene();
	playerManager = new PlayerManager(RealPlayerCount, robotPlayerCount);    //Ҫ��easyScene֮������,��Ҫ�ڻ�ͼ֮ǰ

	ListenThreadState = RUN;

	gameEngine->loadScene(easyScene,playerManager);
	gameEngine->run();
	
	//������Ϸ����


	delete gameEngine;
	delete easyScene;
	delete buttonManager;
	delete playerManager;
	return 0;
}
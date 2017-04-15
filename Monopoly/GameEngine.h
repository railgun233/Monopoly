//作为游戏的主体，联系各个部分
#pragma once
#include"global.h"

class Scene;
class PlayerManager;

//本来打算使用单例类的，后来想想算了，真到要崩的时候也不是这点细节就能解决的
//注意，只可存在且只能声明一个GameEngine对象
class GameEngine
{
private:
	Scene* scene;
	PlayerManager* player_manager;

public:
	GameEngine();
	~GameEngine();
	void initialize();                                //导入数据并进行一些处理
	void loadScene(Scene*, PlayerManager*);           //加载场景
	void run();                                       //运行
	void over();                                      //结束游戏
};
static GameEngine *gameEngine;
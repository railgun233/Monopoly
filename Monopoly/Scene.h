//作为抽象基类，游戏场景都将从此类继承
#pragma once
#include<list>
using std::list;

class Cell;

class Scene
{
protected:
	list<Cell*> cellList;

public:
	Scene(){}
	~Scene(){}

	virtual void loadData() = 0;
	virtual void run() = 0;
	virtual void paint() = 0;
	virtual void loadPlayer() = 0;
};
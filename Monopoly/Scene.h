//��Ϊ������࣬��Ϸ���������Ӵ���̳�
#pragma once
#include<list>
using std::list;

class Cell;

class Scene
{
public:
	Scene(){}
	~Scene(){}

	virtual void loadData() = 0;
	virtual void run() = 0;
	virtual void paint() = 0;
};
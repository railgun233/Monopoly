#pragma once
#include"global.h"

class AI
{
private:
	bool rudeAI();
	bool cautiousAI() { return true; }
	bool smartAI() { return true; }

public:
	AI(){}
	~AI(){}

	bool toBuy(AI_TYPE type);
};
extern AI* AI_Engine;

inline bool AI::rudeAI()
{
	return true;
}

inline bool AI::toBuy(AI_TYPE type)
{
	switch (type)
	{
	case AI_Rude:
		return rudeAI();
	case AI_Cautious:
		return cautiousAI();
	case AI_Smart:
		return smartAI();
	default:
		return rudeAI();
	}
}
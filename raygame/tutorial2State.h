#pragma once
#include "gameState.h"

class tutorial2State : public gameState
{
	std::string txt;
	door d;

public:
	tutorial2State();

	void update();
	void draw();

	GameStates next();
};


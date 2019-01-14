#pragma once
#include "gameState.h"

class tutorial3State : public gameState
{
	std::string txt;
	door d;

public:
	tutorial3State();

	void update();
	void draw();

	GameStates next();
};
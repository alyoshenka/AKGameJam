#pragma once
#include "gameState.h"

class testState : public gameState
{
public:

	goblin g;

	testState();

	void update();
	void draw();

	GameStates next();
};

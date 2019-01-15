#pragma once
#include "gameState.h"

class jump1State : public gameState
{
public:
	jump1State();

	void update();
	void draw();

	GameStates next();
};

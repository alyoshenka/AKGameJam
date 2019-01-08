#pragma once
#include "gameState.h"

class tutorial2State : public gameState
{


public:
	tutorial2State();
	~tutorial2State();

	void update();
	void draw();

	GameStates next();
};


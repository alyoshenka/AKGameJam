#pragma once
#include "gameState.h"

// starting place (not opening menu yet)
class menuState : public gameState
{
	door startDoor;

public:
	menuState();
	~menuState();

	void update();
	void draw();

	GameStates next();
};


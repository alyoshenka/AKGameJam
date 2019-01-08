#pragma once
#include "gameState.h"
class gameOverState : public gameState
{
public:
	gameOverState();
	~gameOverState();

	void draw();
	void update();
};


#pragma once
#include "gameState.h"

#include <string>

class tutorial1State : public gameState
{

	std::string txt;

	chest c;
	door d;

public:
	tutorial1State();
	~tutorial1State();

	void update();
	void draw();

	GameStates next();
};


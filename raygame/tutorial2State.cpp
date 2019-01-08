#include "tutorial2State.h"



tutorial2State::tutorial2State()
{
	reset();

	p.pos = { 100, 100 };
}


tutorial2State::~tutorial2State()
{
}

void tutorial2State::update()
{
	check();
}

void tutorial2State::draw()
{
	drawFloor();

	p.draw();
}

GameStates tutorial2State::next()
{
	if (p.curHealth <= 0)
	{
		return GameStates::LOSE;
	}

	return GameStates::TUTORIAL2;
}

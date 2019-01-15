#include "jump1State.h"

jump1State::jump1State()
{
	reset();

	p.pos = { 100, floor.height - 100 };
}

void jump1State::update()
{
	check();

	p.update(collisions, colUsed);

	next();
}

void jump1State::draw()
{

	drawAll();

	p.draw();
}

GameStates jump1State::next()
{
	if (p.curHealth <= 0)
	{
		return GameStates::LOSE;
	}

	return GameStates::JUMP1;
}

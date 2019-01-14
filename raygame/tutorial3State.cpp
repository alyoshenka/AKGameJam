#include "tutorial3State.h"

tutorial3State::tutorial3State()
{
	reset();

	p.pos = { 100, 100 };
	d.setPosition({ 600, 300 });
}

void tutorial3State::update()
{
	check();

	p.update(collisions, colUsed);

	updateDemons(&p);
	updateChests(&p);
	d.update(&p);

	next();
}

void tutorial3State::draw()
{
	DrawText(txt.c_str(), 32, 16, 30, WHITE);

	drawAll();

	d.draw();

	p.draw();
}

GameStates tutorial3State::next()
{
	if (p.curHealth <= 0)
	{
		return GameStates::LOSE;
	}

	return GameStates::TUTORIAL3;
}

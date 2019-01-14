#include "tutorial2State.h"

tutorial2State::tutorial2State()
{
	reset();

	p.pos = { 100, 100 };

	txt = "Click LEFT MOUSE button for distance attack";

	demonCnt = 6;
	demons[0].active = true;
	demons[1].active = true;
	demons[2].active = true;
	demons[3].active = false;
	demons[4].active = false;
	demons[5].active = false;

	demons[0].setPosition({ 330, 150 });
	demons[1].setPosition({ 330, 350 });
	demons[2].setPosition({ 150, 350 });
	demons[3].setPosition({ 570, 100 });
	demons[4].setPosition({ 750, 100 });
	demons[5].setPosition({ 570, 280 });

	for (int i = 0; i < demonCnt; i++)
	{
		demons[i].canAttack = false;
	}

	wallCnt = 1;
	walls[0] = wall(560, 350, 368, 16);
	collisions[colUsed++] = walls[0].rec;

	d.setPosition({ 785, 360 });
	d.title = "next room";
}

void tutorial2State::update()
{
	check();

	p.update(collisions, colUsed);

	for (int i = 0; i < demonCnt; i++)
	{
		demons[i].update(&p);
	}

	// if first 3 done
	if (!demons[0].alive && !demons[1].alive && !demons[2].alive)
	{
		demons[3].active = true;
		demons[4].active = true;
		demons[5].active = true;
		txt = "Use MOUSE RIGHT for melee (close range) attacks";
	}

	bool readyForNext = false;
	// what is a better way to check this?
	if (!readyForNext && !demons[3].alive && !demons[4].alive && !demons[5].alive)
	{
		readyForNext = true;
	}

	if (readyForNext)
	{
		d.update(&p);
	}

	next();
}

void tutorial2State::draw()
{

	DrawText(txt.c_str(), 32, 16, 30, WHITE);

	drawAll();

	d.draw();

	p.draw();
}

GameStates tutorial2State::next()
{
	if (p.curHealth <= 0)
	{
		return GameStates::LOSE;
	}

	if (d.ready)
	{
		return GameStates::TUTORIAL3;
	}

	return GameStates::TUTORIAL2;
}

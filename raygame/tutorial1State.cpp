#include "tutorial1State.h"

tutorial1State::tutorial1State()
{
	reset();

	p.pos = { 100, 100 };

	wallCnt = 6;
	walls = new wall[wallCnt];

	// setup level
	walls[0] = wall(110, 270, 16, 96);
	walls[1] = wall(560, 270, 16, 96);
	walls[2] = wall(416, 352, 16, 96);

	walls[5] = wall(32, 163, 660, 16);
	walls[3] = wall(560, 350, 368, 16);
	walls[4] = wall(110, 352, 300, 16);

	colUsed = 0;
	for (int i = 0; i < wallCnt; i++)
	{
		collisions[colUsed++] = walls[i].rec;
	}	

	c.setPosition({ 350, 400 });
	chests[chestCnt++] = c;

	txt = "Use the WASD keys to move";

	d.setPosition({ 785, 360 });

	collisions[colUsed++] = c.rec;
}

tutorial1State::~tutorial1State()
{
}

void tutorial1State::update()
{
	check();

	p.update(collisions, colCnt);

	// THERE IS A BETTER WAY TO CHECK I KNOW
	// check for mvmt
	if (p.pos.x > 200 && p.pos.y > 190)
	{
		txt = "Collect gold from chests";
	}
	// check gold
	if (p.gold > 0)
	{
		txt = "Go through the door to the next room";
	}

	updateChests(&p);
	d.update(&p);

	next();
}

void tutorial1State::draw()
{
	DrawText(txt.c_str(), 32, 16, 30, WHITE); 

	drawAll();
	d.draw();

	p.draw();
}

GameStates tutorial1State::next()
{
	if (p.curHealth <= 0)
	{
		return GameStates::LOSE;
	}

	if (d.ready)
	{
		return GameStates::TUTORIAL2;
	}

	return GameStates::TUTORIAL1;
}

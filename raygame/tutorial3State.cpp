#include "tutorial3State.h"

tutorial3State::tutorial3State()
{
	reset();
	p.canThrow = false;
	p.canStab = false;

	d.setPosition({ 600, 250 });

	txt = "Watch out for the demon's attacks! You cannot shoot them in this level"; // rearrange 2 & 3

	demonCnt = 7;
	demons[0].setPosition({ 330, 80 });
	demons[1].setPosition({ 550, 90 });
	demons[2].setPosition({ 700, 110 });
	demons[3].setPosition({ 820, 225 });
	demons[4].setPosition({ 750, 400 });
	demons[5].setPosition({ 480, 370 });
	demons[6].setPosition({ 125, 400 });
	demons[6].setPosition({ 180, 225 });

	wallCnt = 3;
	walls[0] = { 32, 170, 700, 16 };
	walls[1] = { 742, 170, 16, 150 };
	walls[2] = { 176, 320, 580, 16};

	collisions[colUsed++] = walls[0].rec;
	collisions[colUsed++] = walls[1].rec;
	collisions[colUsed++] = walls[2].rec;
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
	DrawText(txt.c_str(), 32, 16, 20, WHITE);

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

	if (d.ready)
	{
		return GameStates::JUMP1;
	}

	return GameStates::TUTORIAL3;
}

#include "menuState.h"

menuState::menuState()
{
	p.pos = { 100, 100 };

	startDoor.setPos({ 200.0f, (float)startDoor.closed.height });
	startDoor.title = "Start Game";
}

menuState::~menuState()
{
}

void menuState::update()
{
	p.update(collisions, colCnt);
	startDoor.update(&p);

	// update state
	next();
}

void menuState::draw()
{
	drawFloor();

	// render order

	startDoor.draw();
	p.draw();

	// menu stuff
	// DrawText("GAME NAME HERE", 250, 250, 40, WHITE);
	// std::string coords = std::to_string((int)GetMouseX()) + ", " + std::to_string((int)GetMouseY());
	// DrawText(coords.c_str(), GetMouseX() - 30, GetMouseY() - 20, 10, WHITE);
}

GameStates menuState::next()
{
	// update
	if (startDoor.ready)
	{
		return GameStates::TUTORIAL1;
	}

	// else stay same
	return GameStates::MAINMENU;
}

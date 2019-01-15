#include "testState.h"

testState::testState()
{
	reset();
}

void testState::update()
{
	check();
	p.update(collisions, colCnt);
	g.update(p);
	next();
}

void testState::draw()
{
	drawAll();
	g.draw();
	p.draw();
}

GameStates testState::next()
{
	return GameStates::TEST;
}

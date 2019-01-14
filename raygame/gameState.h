#pragma once

#include <cassert>

#include "raylib.h"

#include "player.h"
#include "door.h"
#include "chest.h"
#include "demon.h"
#include "wall.h"

// states
enum State 
{
	MainMenu = 0,
	Tutorial1,
	GameOver
};

// what are the potential drawbacks of this implementation?

// use floor tiles to spell name
// render order
// organize all the shit
// redo state machine because i can't think through things well
// drawFloor and randomizeFloorTiles in parent
// texture manager -> later
// separate weapon classes -> array of weapons?
// dynamic array to manage demon recs
// fuck how do pointers work
// we could always just move the collision boxes...
// resetDemons(pos) + health

// pass player around to enemy classes with pointers
// to modify values

enum GameStates {
	NONE,
	MAINMENU,
	TUTORIAL1,
	TUTORIAL2,
	TUTORIAL3,
	LOSE
};

// this singleton class manages the use of
// the current game state
class gameState
{

public:
	Texture2D * floorTiles;
	int floorTileCnt;
	// bounds
	Rectangle floor;
	Rectangle * collisions;
	int colCnt;
	int colUsed;

	wall * walls;
	int maxWall;
	int wallCnt;
	demon * demons;
	int maxDem;
	int demonCnt;
	chest * chests;
	int maxChest;
	int chestCnt;

	player p;

	gameState();
	~gameState();

	virtual void update();
	virtual void draw();
	virtual GameStates next() { return NONE; };

	void drawFloor();
	// resets alloc vars
	void reset();
	// if outside alloc
	void check();

	void updateDemons(player * p);
	void updateChests(player * p);
	// RENDER ORDER!!
	void drawWalls();
	void drawDemons();
	void drawChests();
	void drawAll();
};

// only ONE place where everything is tied together
void setupGameState(gameState *&ptr, GameStates newState);

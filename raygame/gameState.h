#pragma once

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
	Room1,
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

// this singleton class manages the use of
// the current game state
class gameState
{
	// prevents outside use
	gameState();

	State state;

	// state functions
	void mainMenu();
	void room1();
	void gameOver();

	// init functions (put in ctor later)
	void initRoom1();

	player guy;
	Rectangle floor;
	// backgrounds
	Texture2D * floors;
	int floorCnt;
	door startDoor;
	door creditsDoor;
	chest testChest;
	wall w;

	Rectangle * collisions;
	int colsLen;
	// num
	int colsUsed;

	demon * demons;
	chest * chests;
	door * doors;
	// max per level
	int demonCnt;
	int chestCnt;
	int doorCnt;
	// used
	int demonIdx;
	int chestIdx;
	int doorIdx;

public:

	~gameState();
	// use to init
	static gameState & getInstance();

	State getState();
	void setState(State _state);

	// main application function
	void go();
	void drawFloor();
	void deleteCollision(Rectangle  & r);
};


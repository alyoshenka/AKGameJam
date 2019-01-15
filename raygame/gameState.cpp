#include "gameState.h"

#include "menuState.h"
#include "tutorial1State.h"
#include "tutorial2State.h"
#include "tutorial3State.h"
#include "jump1State.h"

#include "testState.h"

#include "gameOverState.h"

void setupGameState(gameState *& ptr, GameStates newState)
{
	switch (newState) {
	case GameStates::NONE: ptr = new gameState(); break;
	case GameStates::MAINMENU: ptr = new menuState(); break;
	case GameStates::TUTORIAL1: ptr = new tutorial1State(); break;
	case GameStates::TUTORIAL2: ptr = new tutorial2State(); break;
	case GameStates::TUTORIAL3: ptr = new tutorial3State(); break;
	case GameStates::JUMP1: ptr = new jump1State(); break;
	case GameStates::TEST: ptr = new testState(); break;
	case GameStates::LOSE: ptr = new gameOverState(); break;

	default: assert(false && "Invalid state specified");
	}
}

gameState::gameState()
{
	floorTileCnt = 1;
	floorTiles = new Texture2D[floorTileCnt];
	floorTiles[0] = LoadTexture("assets/floor_1.png");
	floor = { 32, 32, GetScreenWidth() - 64.0f, GetScreenHeight() - 96.0f };
	colCnt = 100; // ?????????????
	colUsed = 0;
	collisions = new Rectangle[colCnt];
	r = { 0.0f, 0.0f, 32.0f, (float)GetScreenHeight() };
	l = r;
	l.x = GetScreenWidth() - 32;
	t = {0.0f, 0.0f, (float)GetScreenWidth(), 64.0f };
	b = t;
	b.y = GetScreenHeight() - 96;

	collisions[0] = l;
	collisions[1] = r;
	collisions[2] = t;
	collisions[3] = b;


	// max alloc?
	walls = new wall[20];
	demons = new demon[10];
	chests = new chest[5];
}

gameState::~gameState()
{
	for (int i = 0; i < floorTileCnt; i++)
	{
		UnloadTexture(floorTiles[i]);
	}
	// delete[] floorTiles;
	delete[] collisions;
}

void gameState::update()
{
}

void gameState::draw()
{
}

void gameState::drawFloor()
{
	// walls
	// corners
	int border = 32;
	for (int y = border * 2; y < GetScreenHeight() - border * 3; y += 16)
	{
		for (int x = border; x < GetScreenWidth() - border; x += 16)
		{
			DrawTexture(floorTiles[0], x, y, WHITE);
		}
	}
}

void gameState::reset()
{
	wallCnt = 0;
	colUsed = 4;
	demonCnt = 0;
	chestCnt = 0;

	p.reset();
}

void gameState::check()
{
	std::string probs = "";
	bool prob = false;

	if (wallCnt >= maxWall)
	{
		probs += " wall";
		prob = true;
	}
	if (demonCnt >= maxDem)
	{
		probs += " demon";
		prob = true;
	}
	if (chestCnt >= maxChest)
	{
		probs += " chest";
		prob = true;
	}

	if (prob)
	{
		probs += " exceeds max allocation";
		assert(probs.c_str());
	}
}

void gameState::updateDemons(player * p)
{
	for (int i = 0; i < demonCnt; i++)
	{
		demons[i].update(p);
	}
}

void gameState::updateChests(player * p)
{
	for (int i = 0; i < chestCnt; i++)
	{
		chests[i].update(p);
	}
}

void gameState::drawWalls()
{
	for (int i = 0; i < wallCnt; i++)
	{
		walls[i].draw();
	}
}

void gameState::drawDemons()
{
	for (int i = 0; i < demonCnt; i++)
	{
		demons[i].draw();
	}
}

void gameState::drawChests()
{
	for (int i = 0; i < chestCnt; i++)
	{
		chests[i].draw();
	}
}

void gameState::drawAll()
{
	drawFloor();
	drawWalls();
	drawDemons();
	drawChests();
}

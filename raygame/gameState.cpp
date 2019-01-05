#include "gameState.h"

gameState::gameState()
{
	// init
	state = MainMenu;

	floor = { 32, 32, GetScreenWidth() - 64.0f, GetScreenHeight() - 96.0f};

	floorCnt = 8;
	// tl, tr, bl, br, l, r, floor
	floors = new Texture2D[floorCnt];
	floors[0] = LoadTexture("assets/floor_1.png");
	floors[1] = LoadTexture("assets/floor_2.png");
	floors[2] = LoadTexture("assets/floor_3.png");
	floors[3] = LoadTexture("assets/floor_4.png");
	floors[4] = LoadTexture("assets/floor_5.png");
	floors[5] = LoadTexture("assets/floor_6.png");
	floors[6] = LoadTexture("assets/floor_7.png");
	floors[7] = LoadTexture("assets/floor_8.png");

	startDoor.pos = { 200.0f, (float)startDoor.closed.height };
	startDoor.text = "Start Game";
	creditsDoor.pos = { 600.0f, (float)creditsDoor.closed.height };
	creditsDoor.text = "Credits";
	testChest.pos = { 200, 100 };
	w.pos = {50, 200};
	w.update(16 * 3, 16);

	// temp fix
	testChest.rec.y = testChest.pos.y;
	testChest.rec.x = testChest.pos.x;

	colsLen = 100;
	colsUsed = 0;
	collisions = new Rectangle[colsLen];

	collisions[0] = testChest.rec;
	// walls
	Rectangle l = {0, 0, 32, GetScreenHeight()};
	collisions[2] = l;
	l.x = GetScreenWidth() - l.width;
	collisions[3] = l;
	Rectangle t = {0, 0, GetScreenWidth(), 64};
	collisions[4] = t;
	t.height = 96;
	t.y = GetScreenHeight() - t.height;
	collisions[1] = t;

	collisions[5] = w.rec;

	colsUsed = 6;

	demonCnt = 3;
	doorCnt = 3;
	chestCnt = 3;
	demonIdx = 3;
	doorIdx = 3;
	chestIdx = 3;
	demons = new demon[demonCnt];
	doors = new door[doorCnt];
	chests = new chest[chestCnt];
}

void gameState::mainMenu()
{
	// update
	if (guy.curHealth <= 0)
	{
		state = GameOver;
	}

	if (startDoor.ready)
	{
		// init next state
		guy.frozen = false;
		guy.pos = { 100, 100 };
		initRoom1();
		state = Room1;

		// because he was freezing
		return;
	}

	// update order?
	startDoor.update(&guy);
	creditsDoor.update(&guy);
	testChest.update(&guy);

	guy.update(collisions, colsUsed);

	BeginDrawing();

	// draw
	ClearBackground(BLACK);

	drawFloor();

	// render order

	startDoor.draw();
	creditsDoor.draw();
	testChest.draw();
	w.draw();

	guy.draw();

	// menu stuff
	// DrawText("GAME NAME HERE", 250, 250, 40, WHITE);
	std::string coords = std::to_string((int)GetMouseX()) + ", " + std::to_string((int)GetMouseY());
	DrawText(coords.c_str(), GetMouseX() - 30, GetMouseY() - 20, 10, WHITE);

	EndDrawing();
}

void gameState::room1()
{
	// update
	if (guy.curHealth <= 0)
	{
		state = GameOver;
	}

	for (int i = 0; i < demonIdx; i++)
	{
		if (demons[i].update(&guy))
		{
			deleteCollision(demons[i].rec);
		}

		chests[i].update(&guy);
	}

	guy.update(collisions, colsUsed);

	BeginDrawing();

	// draw
	ClearBackground(BLACK);

	drawFloor();

	for (int i = 0; i < demonIdx; i++)
	{
		demons[i].draw();

		chests[i].draw();
	}

	guy.draw();

	EndDrawing();
}

void gameState::gameOver()
{
	// update
	if (IsKeyPressed(KEY_SPACE))
	{
		state = MainMenu;
	}

	BeginDrawing();

	// draw
	ClearBackground(GREEN);

	EndDrawing();
}

void gameState::initRoom1()
{
	// "clear"
	colsUsed = 0;

	// change if demonCnt != chestCnt
	for (int i = 0; i < demonCnt; i++)
	{
		demons[i].pos.x = GetRandomValue(floor.x, floor.x + floor.width - demons[i].idleAnim[0].width);
		demons[i].pos.y = GetRandomValue(floor.y, floor.y + floor.height - demons[i].idleAnim[0].height);

		chests[i].pos.x = GetRandomValue(floor.x, floor.x + floor.width - chests[i].fullAnim[0].width);
		chests[i].pos.y = GetRandomValue(floor.y, floor.y + floor.height - chests[i].fullAnim[0].height);

		// get rec in position
		// (jank)
		demons[i].update(&guy);
		chests[i].update(&guy);

		collisions[colsUsed++] = demons[i].rec;
		collisions[colsUsed++] = chests[i].rec;
	}
}

gameState::~gameState()
{
	for (int i = 0; i < floorCnt; i++)
	{
		UnloadTexture(floors[i]);
	}

	// delete[] walls;
	// delete[] demons;
	// delete[] doors;
	// delete[] chests;
	// delete[] collisions;
}

gameState & gameState::getInstance()
{
	static gameState instance;
	return instance;
}

State gameState::getState()
{
	return state;
}

void gameState::setState(State _state)
{
	state = _state;
}

void gameState::go()
{
	switch (state)
	{
	case 0:
		mainMenu();
		break;
	case 1:
		room1();
		break;
	case 2:
		gameOver();
		break;
	default:
		// no idea how tf
		break;
	}
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
			DrawTexture(floors[0], x, y, WHITE);
		}
	}
}

void gameState::deleteCollision(Rectangle & r)
{
	for (int i = 0; i < colsUsed - 1; i++)
	{
		if (&collisions[i] == &r)
		{
			collisions[colsUsed--] = collisions[i];
			return;
		}
	}

	// fencepost (?)
	if (&collisions[colsUsed] == &r)
	{
		colsUsed--;
	}
}

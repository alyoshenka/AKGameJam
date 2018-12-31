#include "door.h"

door::door()
{
	closed = LoadTexture("assets/doors_all.png");
	left = LoadTexture("assets/doors_frame_left.png");
	right = LoadTexture("assets/doors_frame_right.png");
	top = LoadTexture("assets/doors_frame_top.png");
	open = LoadTexture("assets/doors_leaf_open.png");

	colBase = LoadTexture("assets/column_base.png");
	colMid = LoadTexture("assets/column_mid.png");
	colTop = LoadTexture("assets/column_top.png");

	pos = { 0, 0 };
	isEntered = false;
	elapsedTime = 0.0f;
	transitionTime = 1.0f;
	text = "insert text here";
	ready = false;

	rec = {pos.x + open.width / 2, pos.y - open.height / 2, 
		(float)open.width / 3, (float)open.height};
}

door::~door()
{
	UnloadTexture(closed);
	UnloadTexture(left);
	UnloadTexture(right);
	UnloadTexture(top);
	UnloadTexture(open);

	UnloadTexture(colBase);
	UnloadTexture(colMid);
	UnloadTexture(colTop);
}

void door::update(player * p)
{
	if (CheckCollisionRecs(p->rec, rec))
	{
		p->frozen = true;
		isEntered = true;		
	}
	else
	{
		isEntered = false;
	}

	if (isEntered)
	{
		elapsedTime += GetFrameTime();
	}

	if (elapsedTime >= transitionTime)
	{
		// go to next state
		elapsedTime = 0.0f;
		ready = true;
	}

	rec.x = pos.x + colMid.width + left.width + open.width / 2;
	rec.y = pos.y - open.height / 2;
}

void door::draw()
{
	if (! isEntered)
	{
		int mod = 3;
		DrawTexture(closed, pos.x + colMid.width, pos.y - mod, WHITE);		
	}
	else
	{
		// open door is dumb		
		DrawTexture(top, pos.x + left.width + colMid.width, pos.y - top.height, WHITE);
		DrawTexture(left, pos.x + colMid.width, pos.y, WHITE);
		DrawTexture(right, pos.x + left.width + open.width - 1 + colMid.width, pos.y, WHITE);
		DrawTexture(open, pos.x + left.width + colMid.width, pos.y, WHITE);
	}

	int mod = 3;
	drawCol(pos.x + mod, pos.y);
	drawCol(pos.x + colMid.width + left.width + open.width + right.width - mod, pos.y);

	int sz = 5;
	DrawText(text.c_str(), pos.x + sz * 3, pos.y - sz * 3, sz, WHITE);
}

void door::drawCol(int x, int y)
{
	DrawTexture(colTop, x, y, WHITE);
	DrawTexture(colMid, x, y + colTop.height, WHITE);
	DrawTexture(colBase, x, y + colTop.height + colMid.height, WHITE);
}

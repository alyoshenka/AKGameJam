#include "wall.h"

wall::wall()
{
	walls[0] = LoadTexture("assets/walls/wall_left.png");
	walls[1] = LoadTexture("assets/walls/wall_mid.png");
	walls[2] = LoadTexture("assets/walls/wall_right.png");
	walls[3] = LoadTexture("assets/walls/wall_side_front_left.png");
	walls[4] = LoadTexture("assets/walls/wall_side_front_right.png");
	walls[5] = LoadTexture("assets/walls/wall_side_mid_left.png");
	walls[6] = LoadTexture("assets/walls/wall_side_mid_right.png");
	walls[7] = LoadTexture("assets/walls/wall_side_top_left.png");
	walls[8] = LoadTexture("assets/walls/wall_side_top_right.png");
	walls[9] = LoadTexture("assets/walls/wall_top_left.png");
	walls[10] = LoadTexture("assets/walls/wall_top_mid.png");
	walls[11] = LoadTexture("assets/walls/wall_top_right.png");

	pos = {0, 0};
	w = 0;
	h = 0;
	rec = {pos.x, pos.y, (float)w, (float)h};
}

wall::~wall()
{
	for (int i = 0; i < cnt; i++)
	{
		UnloadTexture(walls[i]);
	}
}

void wall::update(int _w, int _h)
{
	// width > ?

	w = _w;
	h = _h;
	rec.width = w;
	rec.height = h;
}

void wall::draw()
{
	int curX = pos.x;
	int curY = pos.y;
	DrawTexture(walls[7], curX, curY, WHITE);
	curY += walls[7].height;
	DrawTexture(walls[5], curX, curY, WHITE);
	curY += walls[5].height;
	DrawTexture(walls[3], curX, curY, WHITE);
	curX += walls[5].width;
	curY = pos.y;
}

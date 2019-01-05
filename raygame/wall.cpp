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
	w = 16.0f * 3;
	h = 16.0f;
	rec = {pos.x, pos.y + 1.5f * h, w, h / 2.0f};
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
	rec.height = h / 2.0f;

	rec.x = pos.x;
	rec.y = pos.y + 1.5f * h;
}

void wall::draw()
{
	DrawTexture(walls[9], pos.x, pos.y, WHITE);
	DrawTexture(walls[0], pos.x, pos.y + walls[0].height, WHITE);
	DrawTexture(walls[10], pos.x + walls[0].width, pos.y, WHITE);
	DrawTexture(walls[1], pos.x + walls[0].width, pos.y + walls[0].height, WHITE);
	DrawTexture(walls[11], pos.x + walls[0].width * 2, pos.y, WHITE);
	DrawTexture(walls[2], pos.x + walls[0].width * 2, pos.y + walls[0].height, WHITE);
}

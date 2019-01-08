#include "wall.h"

wall::wall()
{
	walls[0] = LoadTexture("assets/walls/wall_top_mid.png");
	walls[1] = LoadTexture("assets/walls/wall_mid.png");

	pos = {0, 0};
	w = 16.0f * 3;
	h = 16.0f;
	rec = {pos.x, pos.y, w, h};
}

wall::wall(float _x, float _y, float _w, float _h) : wall()
{
	pos.x = _x;
	pos.y = _y;

	w = _w;
	h = _h;

	w += (int)w % 16;
	h += (int)h % 16;

	update(w, h);
	// rec = { pos.x, pos.y + 1.5f * h, w, h / 2.0f };
}

wall::~wall()
{
	for (int i = 0; i < cnt; i++)
	{
		// UnloadTexture(walls[i]);
	}
}

void wall::update(int _w, int _h)
{
	// width > ?

	w = _w;
	h = _h;

	rec.width = w;
	rec.height = h;

	rec.x = pos.x;
	rec.y = pos.y + 16;
}

void wall::draw()
{

	int t = pos.x;

	// top layer
	while (t < pos.x + w)
	{
		DrawTexture(walls[0], t, pos.y, WHITE);
		t += 16;
	}

	for (int y = pos.y + 16; y <= pos.y + h; y += 16)
	{
		for (int x = pos.x; x < pos.x + w; x += 16)
		{
			DrawTexture(walls[1], x, y, WHITE);
		}
	}

}

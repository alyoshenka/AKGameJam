#pragma once
#include "raylib.h"

struct wall
{
	// always 12
	static const int cnt = 12;
	Texture2D walls[cnt];

	float w;
	float h;

	Vector2 pos;
	Rectangle rec;

	wall();
	~wall();

	void update(int _w, int _h);
	void draw();
};

#pragma once
#include "raylib.h"

struct wall
{
	// always 12
	static const int cnt = 2;
	Texture2D walls[cnt];

	float w;
	float h;

	Vector2 pos;
	Rectangle rec;

	wall();
	wall(float _x, float _y, float _w, float _h);
	~wall();

	void update(int _w, int _h);
	void draw();
};

#pragma once
#include "raylib.h"
#include <string>

#include "player.h"

struct door
{
private:
	Vector2 pos;
public:
	Texture2D closed;
	Texture2D left;
	Texture2D right;
	Texture2D top;
	Texture2D open;
	
	Texture2D colBase;
	Texture2D colMid;
	Texture2D colTop;

	// State next;
	bool isEntered;
	float elapsedTime;
	float transitionTime;
	std::string title;
	// ready for next state
	bool ready;

	// door col
	Rectangle rec;

	door();
	~door();

	void update(player * p);
	void draw();
	void drawCol(int x, int y);
	void setPosition(Vector2 _pos);
};


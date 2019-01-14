#pragma once
#include "raylib.h"
#include "player.h"

// check coin anim

struct chest
{

private:
	Vector2 pos;
public:

	Texture2D * fullAnim;
	Texture2D * emptyAnim;
	Texture2D * coinAnim;
	// number of frames
	int animLen;
	int curFrame;
	int coinAnimLen;
	int coinCurFrame;
	float coinElapsedTime;
	bool drawingCoinFlip;

	int gold;
	bool isOpen;
	float frameTime;
	float elapsedTime;

	Rectangle rec;

	chest();
	~chest();

	void update(player * p);
	void draw();
	void setPosition(Vector2 pos);
};


#pragma once
#include "raylib.h"
#include "player.h"

// check coin anim

struct chest
{
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

	Vector2 pos;
	int gold;
	bool isOpen;
	float frameTime;
	float elapsedTime;

	Rectangle rec;

	chest();
	~chest();

	void update(player * p);
	void draw();
};


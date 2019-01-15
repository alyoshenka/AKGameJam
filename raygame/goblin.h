#pragma once
#include "raylib.h"
#include "player.h"

struct goblin
{
private:
	Vector2 pos;
	Vector2 dest;

	static const int animCnt = 4;
	Texture2D idleAnim[animCnt];
	Texture2D runAnim[animCnt];
	int curFrame;
	float frameTime;
	float elapsedFrameTime;

	bool isMoving;

	float speed;

public:
	goblin();
	~goblin();

	void update(player & p);
	void draw();
	void drawHealthBar();

	int curHealth;
	int maxHealth;
	int attackP;
};

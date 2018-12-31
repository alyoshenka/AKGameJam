#pragma once
#include "raylib.h"
#include "player.h"

// name your variables the same way!!

// he a Big Boi
struct demon
{

	Vector2 pos;
	Texture2D * idleAnim;
	int animLen;
	int curFrame;
	float animFrameTime;
	float animElapsedTime;

	int attackP;
	float attackR;
	float attackMaxR;
	float attackTime;
	float attackElapsedTime;
	bool isAttacking;
	float attackSpeed;
	bool recharging;

	int health;
	bool hitByStaff;

	bool alive;

	Rectangle rec;
	Vector2 center;

	demon();
	~demon();
	
	// true if died this turn
	bool update(player * p);
	void draw();
};



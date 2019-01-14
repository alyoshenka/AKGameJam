#pragma once
#include "raylib.h"
#include "player.h"

// name your variables the same way!!

// he a Big Boi
struct demon
{
private:
	Vector2 pos;

public:

	Texture2D * idleAnim;
	int animLen;
	int curFrame;
	float animFrameTime;
	float animElapsedTime;

	bool canAttack;
	int attackP;
	float attackR;
	float attackMaxR;
	float attackTime;
	float attackElapsedTime;
	bool isAttacking;
	float attackSpeed;
	bool recharging;

	int curHealth;
	int maxHealth;
	bool hitByStaff;

	bool alive;
	bool active;

	Rectangle rec;
	Vector2 center;

	demon();
	~demon();
	
	// true if died this turn
	bool update(player * p);
	void draw();
	void drawHealthBar();
	void setPosition(Vector2 _pos);
};



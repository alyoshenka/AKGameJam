#pragma once
#include "raylib.h"
#include "math.h"
#include <string>
#include <vector>
#include <iostream>

// make left and right run anims - need photoshop
// fix shooting offset
// put in center
// fix staff - ps
// directional melee?
// staff cooldown

struct player
{
	enum state 
	{
		idle = 0,
		run
		// lRun
		// rRun
	};

	struct bulletData
	{
		Vector2 pos;
		// deg, (1, 0) = 0deg
		float angle;
	};

	// sprite info
	Texture2D * idleSprites;
	Texture2D * runSprites;
	Texture2D bulletSprite;
	bulletData * bullets;
	Texture2D staff;
	int spriteCnt;
	int curSprite;
	// time per sprite
	float animSpeed;
	// elapsed animation time
	float animTime;

	// player vals
	float speed;
	Vector2 pos;
	Vector2 center;
	state curState;
	// deg
	float fov;
	int curHealth;
	int maxHealth;
	int gold;

	bool frozen;

	// combat
	// knives
	int bulletP;
	int bulletCnt;
	int maxShots;
	float bulletSpeed;
	// staff
	int staffP;
	// deg
	float staffRot;
	bool staffIsRotating;
	bool staffIsHolding;
	float staffRotSpeed;
	float staffHoldTime;
	float staffElapsedTime;

	Rectangle rec;

	player();
	~player();

	void update(Rectangle * cols, int len);
	void draw();
	void drawStats();

	bool checkCollision(Rectangle * cols, int len);
};


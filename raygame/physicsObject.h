#pragma once
#include "raylib.h"

struct physicsObject
{
private:
	// the bounding box of the thing being acted upon
	Rectangle obj;

public:

	physicsObject();

	Vector2 velocity;
	Vector2 acceleration;
	// downwards acceleration
	float gravity;

	bool onGround;

	// one big update
	void update();

	// allllll the little updates

	void applyGravity();
};

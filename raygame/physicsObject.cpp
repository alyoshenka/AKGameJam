#include "physicsObject.h"

physicsObject::physicsObject()
{
	velocity = { 0, 0 };
	acceleration = { 0, 0 };
	gravity = 9.8f; // this will change

	onGround = false; // start with freeFall?

}

void physicsObject::update()
{
	applyGravity();

	obj.x += velocity.x;
	obj.y += velocity.y;
}

void physicsObject::applyGravity()
{
	if (!onGround)
	{
		velocity.y -= gravity;
	}
}

#include "goblin.h"

goblin::goblin()
{
	idleAnim[0] = LoadTexture("assets/goblin/goblin_idle_anim_f0.png");
	idleAnim[1] = LoadTexture("assets/goblin/goblin_idle_anim_f1.png");
	idleAnim[2] = LoadTexture("assets/goblin/goblin_idle_anim_f2.png");
	idleAnim[3] = LoadTexture("assets/goblin/goblin_idle_anim_f3.png");

	runAnim[0] = LoadTexture("assets/goblin/goblin_run_anim_f0.png");
	runAnim[1] = LoadTexture("assets/goblin/goblin_run_anim_f1.png");
	runAnim[2] = LoadTexture("assets/goblin/goblin_run_anim_f2.png");
	runAnim[3] = LoadTexture("assets/goblin/goblin_run_anim_f3.png");

	pos = { 200, 200 };
	dest = { 0, 0 };
	curFrame = 0;
	elapsedFrameTime = 0.0f;
	frameTime = 0.5f;

	isMoving = false; // change to true

	speed = 1.0f;
}

goblin::~goblin()
{
	for (int i = 0; i < animCnt; i++)
	{
		UnloadTexture(idleAnim[i]);
		UnloadTexture(runAnim[i]);
	}
}

void goblin::update(player & p)
{
	dest = p.pos;

	// move towards

	elapsedFrameTime += GetFrameTime();
	if (elapsedFrameTime >= frameTime)
	{
		elapsedFrameTime = 0.0f;
		curFrame++;
		if (curFrame >= animCnt)
		{
			curFrame = 0;
		}
	}
}

void goblin::draw()
{
	Texture2D curSprite = idleAnim[curFrame];
	if (isMoving)
	{
		curSprite = runAnim[curFrame];
	}

	DrawTextureV(curSprite, pos, WHITE);
}

void goblin::drawHealthBar()
{
}

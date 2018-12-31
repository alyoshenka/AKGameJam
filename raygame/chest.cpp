#include "chest.h"

chest::chest()
{
	animLen = 3;
	coinAnimLen = 5;
	fullAnim = new Texture2D[animLen];
	emptyAnim = new Texture2D[animLen];
	coinAnim = new Texture2D[coinAnimLen];
	fullAnim[0] = LoadTexture("assets/chest_full_open_anim_f0.png");
	fullAnim[1] = LoadTexture("assets/chest_full_open_anim_f1.png");
	fullAnim[2] = LoadTexture("assets/chest_full_open_anim_f2.png");
	emptyAnim[0] = LoadTexture("assets/chest_empty_open_anim_f0.png");
	emptyAnim[1] = LoadTexture("assets/chest_empty_open_anim_f1.png");
	emptyAnim[2] = LoadTexture("assets/chest_empty_open_anim_f2.png");
	coinAnim[0] = LoadTexture("assets/coin_anim_f0.png");
	coinAnim[1] = LoadTexture("assets/coin_anim_f1.png");
	coinAnim[2] = LoadTexture("assets/coin_anim_f2.png");
	coinAnim[3] = LoadTexture("assets/coin_anim_f3.png");
	coinAnim[4] = coinAnim[0];

	curFrame = 0;
	coinCurFrame = 0;
	pos = { 0.0f, 0.0f };
	gold = 5;
	isOpen = false;
	frameTime = 0.05f;
	elapsedTime = 0.0f;
	coinElapsedTime = 0.0f;
	drawingCoinFlip = false;

	rec = { pos.x, pos.y, (float)fullAnim[0].width, (float)fullAnim[0].height };
}

chest::~chest()
{
	for (int i = 0; i < animLen; i++)
	{
		UnloadTexture(fullAnim[i]);
		UnloadTexture(emptyAnim[i]);
		UnloadTexture(coinAnim[i]);
	}
	UnloadTexture(coinAnim[3]);

	// delete[] fullAnim;
	// delete[] emptyAnim;
	// delete[] coinAnim;
}

void chest::update(player * p)
{
	// iterate frame
	if (isOpen && curFrame < animLen - 1)
	{
		elapsedTime += GetFrameTime();
		if (elapsedTime >= frameTime)
		{
			elapsedTime = 0.0f;
			curFrame++;
		}
	}
	if (!isOpen && curFrame > 0)
	{
		elapsedTime += GetFrameTime();
		if (elapsedTime >= frameTime)
		{
			elapsedTime = 0.0f;
			curFrame--;
		}
	}

	// coin anim
	if (drawingCoinFlip)
	{
		coinElapsedTime += GetFrameTime();
		if (coinElapsedTime >= frameTime * 2)
		{
			coinElapsedTime = 0.0f;
			if (coinCurFrame < coinAnimLen - 1)
			{
				coinCurFrame++;
			}
			else
			{
				drawingCoinFlip = false;
			}
		}
	}

	if (CheckCollisionRecs(rec, p->rec))
	{
		isOpen = true;
		// take gold
		if (curFrame == animLen - 1 && gold > 0)
		{
			drawingCoinFlip = true;
			p->gold += gold;
			gold = 0;
		}
	}
	else
	{
		isOpen = false;
	}

	rec.x = pos.x;
	rec.y = pos.y;
}

void chest::draw()
{
	Texture2D cur = fullAnim[0];
	if (gold > 0)
	{
		cur = fullAnim[curFrame];
	}
	else {
		cur = emptyAnim[curFrame];
	}

	DrawTextureV(cur, pos, WHITE);

	int yOffset = 3;
	// bad practice but whatever
	if (coinCurFrame == 1 || coinCurFrame == 3)
	{
		yOffset *= 2;
	}
	if (coinCurFrame == 2)
	{
		yOffset *= 3;
	}

	if (drawingCoinFlip)
	{
		DrawTexture(coinAnim[coinCurFrame], pos.x + 5, pos.y - yOffset, WHITE);
	}
}


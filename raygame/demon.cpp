#include "demon.h"

demon::demon()
{
	animLen = 4;
	idleAnim = new Texture2D[animLen];
	idleAnim[0] = LoadTexture("assets/demon/big_demon_idle_anim_f0.png");
	idleAnim[1] = LoadTexture("assets/demon/big_demon_idle_anim_f1.png");
	idleAnim[2] = LoadTexture("assets/demon/big_demon_idle_anim_f2.png");
	idleAnim[3] = LoadTexture("assets/demon/big_demon_idle_anim_f3.png");

	curFrame = 0;
	animFrameTime = 0.2f;
	animElapsedTime = 0.0f;

	canAttack = true;
	attackP = 10;
	attackR = 0.0f;
	attackMaxR = 100.0f;
	attackTime = 5.0f;
	attackElapsedTime = GetRandomValue(0, 2000) / 2000.0f;
	isAttacking = false;
	attackSpeed = 100.0f;
	recharging = false;

	maxHealth = 10;
	curHealth = maxHealth;
	hitByStaff = false;

	alive = true;
	active = true;

	rec = {pos.x, pos.y, (float)idleAnim[0].width, (float)idleAnim[0].height};
	center = { pos.x + idleAnim[0].width / 2, pos.y + idleAnim[0].height / 2 };
}

demon::~demon()
{
	for (int i = 0; i < animLen; i++)
	{
		UnloadTexture(idleAnim[i]);
	}

	// delete[] idleAnim;
}

bool demon::update(player * p)
{
	if (!alive || !active)
	{
		// technically should be true but only want to delete collision once
		return false;
	}

	animElapsedTime += GetFrameTime();
	if (animElapsedTime >= animFrameTime)
	{
		animElapsedTime = 0.0f;
		curFrame++;
		// wrap
		if (curFrame > animLen - 1)
		{
			curFrame = 0;
		}
	}

	attackElapsedTime += GetFrameTime();
	if (attackElapsedTime >= attackTime && canAttack)
	{
		attackElapsedTime = 0.0f;
		isAttacking = true;
	}

	if (isAttacking)
	{
		attackR += attackSpeed * GetFrameTime();
		if (attackR > attackMaxR)
		{
			attackR = 0;
			isAttacking = false;
		}
	}

	// attack
	if (CheckCollisionCircleRec({ pos.x + idleAnim[0].width / 2,
		pos.y + idleAnim[0].height / 2 }, attackR, p->rec))
	{
		if (!recharging)
		{
			p->curHealth -= attackP;
			recharging = true;
			// bump back
			p->frozen = true;
		}

		// temp fix!!!!!
		float x = (pos.x - idleAnim[0].width / 2)
			- (p->pos.x - p->idleSprites[0].width / 2);
		float y = (pos.y - idleAnim[0].height / 2)
			- (p->pos.y - p->idleSprites[0].height / 2);
		float angleBetween = atan(y / x);
		// int mod = 1;
		if (x < 0) // xor
		{
			// because negatives
			angleBetween += PI;
		}

		p->pos.x -= cos(angleBetween) * GetFrameTime() * attackSpeed;
		p->pos.y -= sin(angleBetween) * GetFrameTime() * attackSpeed;

		
		// if outside radius after move
		if (! CheckCollisionCircleRec(center, attackMaxR, p->rec))
		{
			// check after
			p->frozen = false;
			// recharging = false;
		}
	} 
	else
	{
		recharging = false;
	}

	// player weapons
	for (int i = 0; i < p->bulletCnt * p->maxShots; i++)
	{
		Rectangle b = { p->bullets[i].pos.x, p->bullets[i].pos.y, 
			p->bulletSprite.height, p->bulletSprite.height};

		if (CheckCollisionRecs(rec, b))
		{
			p->bullets[i].pos = {-100, -100};
			curHealth -= p->bulletP;
			std::cout << curHealth << std::endl;
		}
	}

	// if no attack vars
	if (! p->staffIsRotating && ! p->staffIsHolding)
	{
		// reset hit test
		hitByStaff = false;
	}

	// if collision && has not been hit by staff this staff rotation
	// fuck this jank ass if statement
	if (CheckCollisionCircleRec(p->center, p->staff.height, rec) && 
		! hitByStaff && (p->staffIsRotating || p->staffIsHolding))
	{
		hitByStaff = true;
		curHealth -= p->staffP;

		std::cout << curHealth << std::endl;
	}

	// if died this turn
	if (curHealth <= 0)
	{
		alive = false;
		pos = { -100, -100 };	
		return true;
	}

	return false;
}

void demon::draw()
{
	if (!alive || !active)
	{
		return;
	}

	if (isAttacking)
	{
		Color c = BLUE;
		c.a = 50;
		DrawCircle(pos.x + idleAnim[0].width / 2, pos.y + idleAnim[0].height / 2,
			attackR, c);
	}
	DrawTextureV(idleAnim[curFrame], pos, WHITE);
	drawHealthBar();
}

void demon::drawHealthBar()
{
	Color c = GREEN;
	float percent = (float)curHealth / maxHealth;
	// add more points for bosses
	if (percent <= 0.5)
	{
		c = ORANGE;
	}
	Vector2 hbPos = pos;
	// float barSize = 5;
	hbPos.y += rec.height + 5;
	// base
	DrawRectangleV(hbPos, { rec.width, 9 }, BLACK);
	// health
	DrawRectangle(hbPos.x + 2, hbPos.y + 2, (rec.width - 4) * percent, 5, c);
}

void demon::setPosition(Vector2 _pos)
{
	pos = _pos;
	rec.x = pos.x;
	rec.y = pos.y;
	center = { pos.x + idleAnim[0].width / 2, pos.y + idleAnim[0].height / 2 };
}





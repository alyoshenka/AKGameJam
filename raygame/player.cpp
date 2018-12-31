#include "player.h"

player::player()
{
	spriteCnt = 4;

	idleSprites = new Texture2D[spriteCnt];
	runSprites = new Texture2D[spriteCnt];

	idleSprites[0] = LoadTexture("assets/elf_m_idle_anim_f0.png");
	idleSprites[1] = LoadTexture("assets/elf_m_idle_anim_f1.png");
	idleSprites[2] = LoadTexture("assets/elf_m_idle_anim_f2.png");
	idleSprites[3] = LoadTexture("assets/elf_m_idle_anim_f3.png");

	runSprites[0] = LoadTexture("assets/elf_m_run_anim_f0.png");
	runSprites[1] = LoadTexture("assets/elf_m_run_anim_f1.png");
	runSprites[2] = LoadTexture("assets/elf_m_run_anim_f2.png");
	runSprites[3] = LoadTexture("assets/elf_m_run_anim_f3.png");

	bulletSprite = LoadTexture("assets/weapon_knife.png");
	staff = LoadTexture("assets/weapon_green_magic_staff.png");

	curSprite = 0;
	animSpeed = 0.2;
	animTime = 0.0f;
	speed = 200.0f;
	pos = { 100.0f, 100.0f };
	center = {pos.x + idleSprites[0].width / 2, pos.y + idleSprites[0].height / 2};
	curState = idle;
	maxHealth = 100;
	curHealth = maxHealth;
	fov = 5.0f;
	bulletCnt = 1;
	maxShots = 10;
	bulletSpeed = 200.0f;
	bullets = new bulletData[bulletCnt * maxShots];
	for (int i = 0; i < bulletCnt * maxShots; i++)
	{
		// use this val to indicate unused
		bullets[i].pos = { -100, -100 };
		bullets[i].angle = 0.0f;
	}
	bulletP = 5;
	gold = 0;

	frozen = false;

	staffRot = 0.0f;
	staffIsRotating = false;
	staffIsHolding = false;
	staffRotSpeed = 1000.0f;
	staffHoldTime = 0.1f;
	staffElapsedTime = 0.0f;
	staffP = 5;

	rec = {pos.x, pos.y, (float)idleSprites[0].width, 
		(float)idleSprites[0].height};
}

player::~player()
{
	for (int i = 0; i < spriteCnt; i++)
	{
		UnloadTexture(idleSprites[i]);
		UnloadTexture(runSprites[i]);
	}

	UnloadTexture(bulletSprite);
	UnloadTexture(staff);

	// delete[] idleSprites;
	// delete[] runSprites;
	// delete[] bullets;
}

void player::update(Rectangle * cols, int len)
{
	// for collision
	Vector2 prevPos = pos;

	animTime += GetFrameTime();

	if (animTime > animSpeed)
	{
		animTime = 0.0f;
		curSprite++;
		if (curSprite > spriteCnt - 1)
		{
			// wrap
			curSprite = 0;
		}
	}

	Vector2 delta{ 0, 0 };
	// movement
	if (IsKeyDown(KEY_W) && ! frozen)
	{
		delta.y -= speed;
		curState = run;
	}
	if (IsKeyDown(KEY_S) && ! frozen)
	{
		delta.y += speed;
		curState = run;
	}
	if (IsKeyDown(KEY_A) && ! frozen)
	{
		delta.x -= speed;
		curState = run;
	}
	if (IsKeyDown(KEY_D) && ! frozen)
	{
		delta.x += speed;
		curState = run;
	}	

	// normalize
	float magnitude = sqrt(delta.x * delta.x + delta.y * delta.y);
	if (magnitude != 0)
	{
		float normalizingFactor = speed * GetFrameTime() / magnitude;
		delta.x *= normalizingFactor;
		delta.y *= normalizingFactor;
	}
	else
	{
		curState = idle;
	}

	pos.x += delta.x;
	pos.y += delta.y;

	// walls
	if (pos.x < 0)
	{
		pos.x = 0;
	}
	if (pos.x + idleSprites[0].width > GetScreenWidth())
	{
		pos.x = GetScreenWidth() - idleSprites[0].width;
	}
	if (pos.y < 0)
	{
		pos.y = 0;

	}
	if (pos.y + idleSprites[0].height > GetScreenHeight())
	{
		pos.y = GetScreenHeight() - idleSprites[0].height;
	}

	// shooting
	if (IsKeyPressed(KEY_P))
	{
		// check for unused
		for (int i = 0; i < maxShots; i++)
		{
			int pad = 100;
			// if out of bounds
			// check first in bullet section
			if (bullets[i * bulletCnt].pos.x <= -pad ||		
				bullets[i * bulletCnt].pos.x >= GetScreenWidth() + pad ||
				bullets[i * bulletCnt].pos.y <= -pad ||
				bullets[i * bulletCnt].pos.y >= GetScreenHeight() + pad)
			{
				// use
				// get cw-most angle
				float x = GetMouseX() - (pos.x - idleSprites[0].width / 2);
				float y = GetMouseY() - (pos.y - idleSprites[0].height / 2);
				float angleBetween = atan(y / x);
				// int mod = 1;
				if (x < 0) // xor
				{
					// because negatives
					angleBetween += PI;
				}				
				// get cw-most angle
				// angleBetween -= (fov / bulletCnt * 2) * PI / 180; // weird offset?

				for (int j = i * bulletCnt; j < bulletCnt + i * bulletCnt; j++)
				{
					// init bulletCnt bullets
					bullets[j].pos = { pos.x + idleSprites[0].width / 2,
									   pos.y + idleSprites[0].height / 2 };
					bullets[j].angle = angleBetween;
					angleBetween += (fov / bulletCnt) * (PI / 180);
				}
				// only shoot once
				break;
			}
			// else nothing
		}
	}

	if (IsKeyPressed(KEY_O))
	{
		staffIsHolding = true;
	}

	if (staffIsHolding)
	{
		staffElapsedTime += GetFrameTime();
		if (staffElapsedTime >= staffHoldTime)
		{
			// reset
			staffElapsedTime = 0.0f;
			staffIsHolding = false;
			staffIsRotating = true;
		}
	}

	if (staffIsRotating)
	{
		staffRot += staffRotSpeed * GetFrameTime();
	}

	// compteled one revolution
	if (staffRot >= 360.0f)
	{
		staffRot = 0.0f;
		staffIsRotating = false;
		staffIsHolding = false;
	}

	// update bullet pos
	for (int i = 0; i < maxShots; i++)
	{
		int pad = 100;
		// only update in use
		if (bullets[i * bulletCnt].pos.x > -pad &&
			bullets[i * bulletCnt].pos.x < GetScreenWidth() + pad &&
			bullets[i * bulletCnt].pos.y > -pad &&		
			bullets[i * bulletCnt].pos.y < GetScreenHeight() + pad)
		{
			for (int j = i * bulletCnt; j < bulletCnt + i * bulletCnt; j++)
			{
				bullets[j].pos.x += cos(bullets[j].angle) * bulletSpeed * GetFrameTime();
				bullets[j].pos.y += sin(bullets[j].angle) * bulletSpeed * GetFrameTime();
			}			
		}
	}

	// health bounds
	if (curHealth < 0)
	{
		curHealth = 0;
	}
	if (curHealth > maxHealth)
	{
		curHealth = maxHealth;
	}

	// if check collision
	// pos = prevpos
	// for bullets
	// if collision
	// pos = outofbounds
	if (checkCollision(cols, len))
	{
		pos = prevPos;
	}

	rec.x = pos.x;
	rec.y = pos.y;
	center = { pos.x + idleSprites[0].width / 2, pos.y + idleSprites[0].height / 2 };
}

void player::draw()
{
	// bullets
	for (int i = 0; i < bulletCnt * maxShots; i++)
	{
		int pad = 100;
		// only used
		if ((bullets[i].pos.x > -pad ||
			bullets[i].pos.x < GetScreenWidth() + pad) &&
			(bullets[i].pos.y > -pad ||			
			bullets[i].pos.y < GetScreenHeight() + pad))
		{
			// DrawTextureV(bulletSprite, bullets[i].pos, WHITE);
			DrawTextureEx(bulletSprite, bullets[i].pos, 
				bullets[i].angle * (180 / PI) + 90, 1.0f, WHITE);
		}
	}

	// melee
	if (staffIsRotating || staffIsHolding)
	{
		Color w = WHITE;
		w.a = 30;
		Color b = BLUE;
		b.a = 100;
		DrawCircle(pos.x + idleSprites[0].width / 2,
			pos.y + idleSprites[0].height / 2, staff.height, w);
		DrawTextureEx(staff, { pos.x + idleSprites[0].width / 2,
			pos.y + idleSprites[0].height / 2 }, staffRot, 1.0f, WHITE);
	}

	// choose which sprite to use
	Texture2D s;

	switch (curState) { // do differently
	case 0:
		s = idleSprites[curSprite];
		break;
	case 1:
		s = runSprites[curSprite];
		break;
	default:
		s = idleSprites[0];
		break;
	}

	DrawTextureV(s, pos, WHITE);

	drawStats();
}

void player::drawStats()
{
	float healthPercent = (float)curHealth / maxHealth;
	Color barC = BLUE; // to test
	if (healthPercent >= 0.6f)
	{
		barC = GREEN;
	} 
	else if (healthPercent >= 0.4f)
	{
		barC = YELLOW;
	}
	else if (healthPercent >= 0.2f)
	{
		barC = ORANGE;
	}
	else
	{
		barC = RED;
	}

	int offset = 32;
	int a = 5;
	Rectangle border = {offset, GetScreenHeight() - offset * 2.25, offset * 20, offset * 1.5};
	Rectangle bar = {offset + a, border.y + a, (border.width - a * 2) * healthPercent, border.height - a * 2};
	DrawRectangleRec(border, DARKBLUE);
	DrawRectangleRec(bar, barC);
	std::string healthS = std::to_string(curHealth) + "  /  " + std::to_string(maxHealth);
	DrawText(healthS.c_str(), border.x + border.width / 2 - offset * 3, border.y + offset / 3, 30, WHITE);

	std::string gs = "Gold: " + std::to_string(gold);
	DrawText(gs.c_str(), border.x + border.width + offset, border.y, offset * 1.25, WHITE);
}

bool player::checkCollision(Rectangle * cols, int len)
{
	// collide with bottom
	float w = idleSprites[0].width / 2;
	float h = idleSprites[0].height / 4;
	Rectangle playerRec = {pos.x + w / 2, pos.y + h * 3, w, h};

	for (int i = 0; i < len; i++)
	{
		if (CheckCollisionRecs(cols[i], playerRec))
		{
			return true;
		}
	}

	return false;
}


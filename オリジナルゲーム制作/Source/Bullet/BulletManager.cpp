#include "BulletManager.h"
#include "StraightBullet.h"

void InitBullet()
{
	// Še’e‚ğ‰Šú‰»
	// ’¼ü’e
	InitStraightBullet();
}

void LoadBullet()
{
	// Še’e‚ğƒ[ƒh
	// ’¼ü’e
	LoadStraightBullet();
}

void StepBullet()
{
	// Še’e‚ğƒXƒeƒbƒv
	// ’¼ü’e
	StepStraightBullet();
}

void UpdateBullet()
{
	// Še’e‚ğXV
	// ’¼ü’e
	UpdateStraightBullet();
}

void DrawBullet()
{
	// Še’e‚ğ•`‰æ
	// ’¼ü’e
	DrawStraightBullet();
}

void FinBullet()
{
	// Še’e‚ğI—¹
	// ’¼ü’e
	FinStraightBullet();
}


void RequestFireBullet(StraightBulletType type, int life, float posX, float posY, float moveX, float moveY, float radius, BulletCollisionTag tag)
{
	//’¼ü’e”­Ë
	FireStraightBullet(type, life, posX, posY, moveX, moveY, radius, tag);
}
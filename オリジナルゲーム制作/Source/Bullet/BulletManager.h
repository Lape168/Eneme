#pragma once
#include "BulletParameter.h"

// ’e‘S‘Ì‚Ìˆ—
void InitBullet();
void LoadBullet();
void StepBullet();
void UpdateBullet();
void DrawBullet();
void FinBullet();

// ’e”­Ë
void RequestFireBullet(StraightBulletType type, int life, float posX, float posY, float moveX, float moveY, float radius, BulletCollisionTag tag);